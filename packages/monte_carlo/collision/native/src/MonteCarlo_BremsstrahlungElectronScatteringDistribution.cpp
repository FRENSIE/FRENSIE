//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{
// Constructor with simple analytical photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.size() > 0 );

  // Use simple analytical photon angular distribution
  d_angular_distribution_func = boost::bind<double>( 
		    &BremsstrahlungElectronScatteringDistribution::SampleSimpleAngle,
		    boost::cref( *this ),
		    _1,
            _2 );
}

// Constructor with detailed tabular photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution,
    const Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
    const double lower_cutoff_energy,
    const double upper_cutoff_energy )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution ),
    d_angular_distribution( angular_distribution ),
    d_lower_cutoff_energy( upper_cutoff_energy ),
    d_upper_cutoff_energy( lower_cutoff_energy )
{
  // Make sure the arraies are valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.size() > 0 );
  testPrecondition( !d_angular_distribution.is_null() );

  // Use detailed photon angular distribution
  d_angular_distribution_func = boost::bind<double>( 
		    &BremsstrahlungElectronScatteringDistribution::SampleDetailedAngle,
		    boost::cref( *this ),
		    _1,
            _2 );
}

// Randomly scatter the electron
void BremsstrahlungElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank,
                                SubshellType& shell_of_interaction ) const
{
  // energy of the bremsstrahlung photon
  double photon_energy;

  // Incoming electron energy
  double incoming_energy = electron.getEnergy();

  // Sample knock-on electron energy
  photon_energy = sampleTwoDDistribution( electron.getEnergy(),
                                     d_bremsstrahlung_scattering_distribution );

  // Set the new energy
  electron.setEnergy( electron.getEnergy() - photon_energy );

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  // Create new photon
  Teuchos::RCP<PhotonState> bremsstrahlung_photon( 
                           new PhotonState( electron, true, true ) );

  // Set photon energy
  bremsstrahlung_photon->setEnergy( photon_energy );

  // Sample the photon outgoing angle cosine
  double angle_cosine;

  angle_cosine = d_angular_distribution_func( incoming_energy, photon_energy );

  // Sample the photon outgoing direction
  double outgoing_photon_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   outgoing_photon_direction );

  // Set photon direction
  bremsstrahlung_photon->setDirection( outgoing_photon_direction );

  // Bank the photon
  bank.push( bremsstrahlung_photon );
}

// Sample the outgoing photon direction from the analytical function
double BremsstrahlungElectronScatteringDistribution::SampleSimpleAngle( 
                                                   double& electron_energy, 
                                                   double& photon_energy ) const 
{
  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta = Utility::calculateDimensionlessRelativisticSpeed( 
                  Utility::PhysicalConstants::electron_rest_mass_energy,
                  electron_energy );

  double scaled_random_number = 
    2.0 * Utility::RandomNumberGenerator::getRandomNumber<double>();
  
  double parameter = -( 1.0 + beta );
                 
  return ( scaled_random_number        + parameter )/ 
         ( scaled_random_number * beta + parameter ); 
}

// Sample the detailed outgoing photon direction
double BremsstrahlungElectronScatteringDistribution::SampleDetailedAngle( 
                                                   double& electron_energy, 
                                                   double& photon_energy ) const
{
    if ( electron_energy < d_upper_cutoff_energy )
  {
    return SampleSimpleAngle( electron_energy, photon_energy );
  }
  else if ( electron_energy > d_lower_cutoff_energy )
  {
    return d_angular_distribution->evaluate( photon_energy );
  }
  else
  {
    return SampleSimpleAngle( electron_energy, photon_energy );
  } 
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
