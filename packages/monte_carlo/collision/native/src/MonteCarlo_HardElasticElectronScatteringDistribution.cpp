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
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{
// Constructor 
HardElasticElectronScatteringDistribution::HardElasticElectronScatteringDistribution(
    const int atomic_number,
    const ElasticDistribution& elastic_scattering_distribution)
  : d_atomic_number( atomic_number ),
    d_elastic_scattering_distribution( elastic_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );

  // Cutoff angle cosine between the distribution and analytical function
  cutoff_angle_cosine = 0.999999;
}

// Randomly scatter the electron
void HardElasticElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank,
                                SubshellType& shell_of_interaction ) const
{
  // angle cosine the electron scatters into
  double scattering_angle_cosine;

  // The distribution to be sampled
  Teuchos::RCP<Utility::OneDDistribution> sampling_dist;

  // Energy is below the lowest grid point
  if( electron.getEnergy() < d_elastic_scattering_distribution.front().first )
  {
    sampling_dist    = d_elastic_scattering_distribution.front().second;
  }
  // Energy is above the highest grid point
  else if( electron.getEnergy() >= d_elastic_scattering_distribution.back().first )
  {
    sampling_dist    = d_elastic_scattering_distribution.back().second;
  }
  // Energy is inbetween two grid point
  else
  {
    ElasticDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;
    
    lower_bin_boundary = d_elastic_scattering_distribution.begin();
    upper_bin_boundary = d_elastic_scattering_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_bin_boundary,
							  upper_bin_boundary,
							  electron.getEnergy() );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = ( electron.getEnergy() - lower_bin_boundary->first )/
      (upper_bin_boundary->first - lower_bin_boundary->first);
     
    double random_number_1 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
     
    // Sample from the upper energy bin
    if( random_number_1 < interpolation_fraction )
    {
      sampling_dist = upper_bin_boundary->second;
    }
    // Sample from the lower energy bin
    else
    {
      sampling_dist = lower_bin_boundary->second;
    }
  }

  double random_number_2 = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();

  // evaluate the cutoff CDF for applying the analytical screening function
  double cutoff_cdf_value = sampling_dist->evaluateCDF( cutoff_angle_cosine );

  // Sample from the distribution
  if( cutoff_cdf_value > random_number_2 )
  {
    scattering_angle_cosine = sampling_dist->sample( cutoff_angle_cosine );
//! \todo Write a Histogram function to sample from the corresponding CDF in a subrange
//    scattering_angle_cosine = sampling_dist->sample( );
  }
  // Sample from the analytical function
  else
  {
    scattering_angle_cosine = 
      evaluateScreenedScatteringAngle( electron.getEnergy() );
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
std::cout << " elastic called" << std::endl;
  // Set the new direction
  electron.setDirection( outgoing_electron_direction );
}


// Evaluate the screening angle at the given electron energy
double HardElasticElectronScatteringDistribution::evaluateScreeningAngle(
                                              const double energy ) const
{
  // get the momentum of the electron in units of electron_rest_mass * speed of light
  double electron_momentum = Utility::calculateDimensionlessRelativisticMomentum( 
                           Utility::PhysicalConstants::electron_rest_mass_energy,
                           energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta = Utility::calculateDimensionlessRelativisticSpeed( 
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

 double arg1 = 1.0/( Utility::PhysicalConstants::inverse_fine_structure_constant*
                     0.885 * electron_momentum );

 double arg2 = d_atomic_number/
          ( Utility::PhysicalConstants::inverse_fine_structure_constant * beta );

 // Calculate the screening angle
 return arg1*arg1/4.0 * pow(d_atomic_number, 2.0/3.0)*( 1.13 + 3.76*arg2*arg2 );
}

// Evaluate the scattering angle from the analytical function
double HardElasticElectronScatteringDistribution::evaluateScreenedScatteringAngle(
                                                  const double energy ) const                                                
{
  double random_number_3 = 
                      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  // evaluate the screening angle at the given electron energy
  double screening_angle = evaluateScreeningAngle( energy );

 // Calculate the screened scattering angle
  double arg = (1.0 - random_number_3)/( screening_angle + 0.000001 );

  return screening_angle + 1.0 - 1.0/(arg + random_number_3/screening_angle);
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
