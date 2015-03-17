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
#include "MonteCarlo_ElectronState.hpp"
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

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return PAIR_PRODUCTION_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure it is energetically possible for this reaction to occur
  testPrecondition( photon.getEnergy() >= this->getThresholdEnergy() );

  d_interaction_model( photon, bank );

  photon.incrementCollisionNumber();

  // The shell of interaction, which will be important for triplet production
  // is currently ignored
  shell_of_interaction = UNKNOWN_SUBSHELL;
}

// The basic pair production model
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteraction( 
							   PhotonState& photon,
							   ParticleBank& bank )
{
  // Assume that the outgoing electron is emitted in the same direction
  // as the original photon with the net kinetic energy (not correct!)
  Teuchos::RCP<ParticleState> electron(
				     new ElectronState( photon, true, true ) );

  electron->setEnergy( photon.getEnergy() - 
		     2*Utility::PhysicalConstants::electron_rest_mass_energy );
  
  bank.push( electron );

  // Sample an isotropic outgoing angle for the annihilation photon 
  double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();
 
  // Sample the azimuthal angle
  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Set the new energy
  photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  // Set the new direction
  photon.rotateDirection( angle_cosine, azimuthal_angle );

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

  // Make sure the scattering angle cosine is valid
  testPostcondition( angle_cosine >= -1.0 );
  testPostcondition( angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPostcondition( azimuthal_angle >= 0.0 );
  testPostcondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
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
