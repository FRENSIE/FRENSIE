//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The pair production photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::PairProductionPhotoatomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const bool use_detailed_electron_emission_physics )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
						       incoming_energy_grid,
						       cross_section,
						       threshold_energy_index )
{
  if( use_detailed_electron_emission_physics )
  {
    d_interaction_model = detailedInteraction;
    d_interaction_model_emission = detailedInteractionPhotonEmission;
  }
  else
  {
    d_interaction_model = basicInteraction;
    d_interaction_model_emission = basicInteractionPhotonEmission;
  }
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return d_interaction_model_emission();
  else
    return 0u;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
						     PhotonState& photon,
						     ParticleBank& bank ) const
{
  // Make sure it is energetically possible for this reaction to occur
  testPrecondition( photon.getEnergy() >= this->getThresholdEnergy() );

  d_interaction_model( photon, bank );
}

// The basic pair production model
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteraction( 
							   PhotonState& photon,
							   ParticleBank& bank )
{
  // Sample an isotropic outgoing angle for the annihilation photon 
  double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();
 
  // Sample the azimuthal angle
  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

  double outgoing_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle( angle_cosine,
							 azimuthal_angle,
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
  
// The detailed pair production model
/*! \todo Implement the detailed pair production model.
 */
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::detailedInteraction( 
							   PhotonState& photon,
							   ParticleBank& bank )
{
  basicInteraction( photon, bank );
}

// The number of photons emitted from pair production using simple model
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteractionPhotonEmission()
{
  return 2u;
}

// The number of photons emitted from pair production using detailed model
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::detailedInteractionPhotonEmission()
{
  return 0u;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
