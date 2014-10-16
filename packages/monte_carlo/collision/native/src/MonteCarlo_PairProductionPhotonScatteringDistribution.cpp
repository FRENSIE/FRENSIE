//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_PairProductionPhotonScatteringDistribution.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The pair production photon scattering distribution
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PairProductionPhotonScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Randomly scatter the photon
void PairProductionPhotonScatteringDistribution::scatterPhoton( 
					 PhotonState& photon, 
					 ParticleBank& bank,
					 unsigned& shell_of_interaction ) const
{
  // Sample an isotropic outgoing angle for the annihilation photon 
  double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

  double outgoing_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
							angle_cosine,
							sampleAzimuthalAngle(),
							photon.getDirection(),
							outgoing_direction );

  // Set the new energy
  photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  // Set the new direction
  photon.setDirection( outgoing_direction );

  // Reset the collision number since this is technically a new photon
  photon.resetCollisionNumber();

  // Create the second annihilation photon
  Teuchos::RCP<ParticleState> annihilation_photon(
				       new PhotonState( photon, true, true ) );
  
  // Reverse the direction of the second annihilation photon
  annihilation_photon->setDirection( -annihilation_photon->getXDirection(),
				     -annihilation_photon->getYDirection(),
				     -annihilation_photon->getZDirection() );
  
  // Bank the annihilation photon
  bank.push( annihilation_photon );

  // Increment the original photon generation number
  photon.incrementGenerationNumber();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
