//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron hard elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace MonteCarlo{

//! Constructor
HardElasticElectronScatteringDistribution::HardElasticElectronScatteringDistribution(
ElasticDistribution& elastic_scattering_distribution,
//const Teuchos::RCP<double>& interpolation_weights )
WeightArray& interpolation_weights )
  : d_elastic_scattering_distribution( elastic_scattering_distribution ),
    d_interpolation_weights( interpolation_weights )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
}
// /*
//! Randomly scatter the electron
void HardElasticElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank) const
{
  // Make sure the energy is valid
  testPrecondition( electron.getEnergy() > 0 );
  testPrecondition( electron.getEnergy() < std::numeric_limits<double>::infinity() );

  double scattering_angle_cosine;

  // Check if energy is outside the grid
  if( electron.getEnergy() >= d_elastic_scattering_distribution.front().first )
  {
    scattering_angle_cosine = d_elastic_scattering_distribution.front().second->sample();
  }
  else if( electron.getEnergy() <= d_elastic_scattering_distribution.back().first )
  {  
    scattering_angle_cosine = d_elastic_scattering_distribution.back().second->sample();
  }
  else
  {
    // Find the upper and lower bins of the elastic scattering distribution at given energy
    ElasticDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_elastic_scattering_distribution.begin();
    upper_bin_boundary = d_elastic_scattering_distribution.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( lower_bin_boundary,
                                                                            upper_bin_boundary,
                                                                            electron.getEnergy());

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Find the upper and lower bins of the interpolation weights at given energy
    WeightArray::const_iterator lower_interpolation_weight, upper_interpolation_weight;

    lower_interpolation_weight = d_interpolation_weights.begin();
    upper_interpolation_weight = d_interpolation_weights.end();

    lower_interpolation_weight = Utility::Search::binaryLowerBound<Utility::FIRST>
                                 ( lower_interpolation_weight,
                                   upper_interpolation_weight,
                                   electron.getEnergy());

    //! \todo get bin index to call the proper interpolation weight
    // Calculate the interpolation fraction
    double interpolation_fraction = 
           ( log( electron.getEnergy() )        - lower_interpolation_weight->second ) /
           ( upper_interpolation_weight->second - lower_interpolation_weight->second );

    double random_num = Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_num < interpolation_fraction )
    {
      scattering_angle_cosine = upper_bin_boundary->second->sample();
    }
    else
    {
      scattering_angle_cosine = lower_bin_boundary->second->sample();
    }
  }
    // Calculate the outgoing direction
   double outgoing_electron_direction[3];

    Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   scattering_angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   outgoing_electron_direction );

    // Make sure the scattering angle cosine is valid
    testPostcondition( scattering_angle_cosine >= -1.0 );
    testPostcondition( scattering_angle_cosine <= 1.0 );

    // Set the new direction
    electron.setDirection( outgoing_electron_direction );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
