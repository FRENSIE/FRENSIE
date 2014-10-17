//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron hard scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! Constructor
HardElasticElectronScatteringDistribution::HardElasticElectronScatteringDistribution(
const Teuchos::RCP<Utility::OneDDistribution>& elastic_scattering_distribution,
const Teuchos::RCP<double>& interpolation_weights )
  : d_elastic_scattering_distribution( elastic_scattering_distribution ),
    d_interpolation_weights( interpolation_weights )
{
  // Make sure the array is valid
  testPrecondition( !elastic_scattering_distribution.is_null() );
}
/*
//! Randomly scatter the electron
void HardElasticElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank) const
{
  // Make sure the energy is valid
  testPrecondition( electron.getEnergy() > 0 );
  testPrecondition( electron.getEnergy() < std::numeric_limits<double>::infinity() );

  double outgoing_energy;

  // Check if energy is outside the grid
  if( electron.getEnergy() >= d_elastic_scattering_distribution.front().first 
                and energy <= d_elastic_scattering_distribution.back().first )
  {
    ElasticDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_elastic_scattering_distribution.begin();
    upper_bin_boundary = d_elastic_scattering_distribution.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( lower_bin_boundary,
                                                                            upper_bin_boundary,
                                                                            electron.getEnergy());

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    //! \todo get bin index to call the proper interpolation weight
/*
    // Calculate the interpolation fraction
    double interpolation_fraction = ( log( electron.getEnergy() ) - log( lower_bin_boundary->first ) )/
                                    ( log( upper_bin_boundary->first ) - log( lower_bin_boundary->first ) );

    double random_num = Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_num < interpolation_fraction )
    {
      energy_prime = upper_bin_boundary->second->sample( outgoing_index );
    }
    else
    {
      energy_prime = lower_bin_boundary->second->sample( outgoing_index );
    }

  }

}
*/
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
