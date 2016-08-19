//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TripletProductionPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The triplet production photoatomic reaction class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::TripletProductionPhotoatomicReaction(
                   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
                   const Teuchos::ArrayRCP<const double>& cross_section,
                   const unsigned threshold_energy_index,
                   const bool use_detailed_electron_emission_physics )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index )
{
  this->initializeInteractionModels( use_detailed_electron_emission_physics );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::TripletProductionPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const bool use_detailed_electron_emission_physics )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
						       incoming_energy_grid,
						       cross_section,
						       threshold_energy_index,
						       grid_searcher )
{
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );

  this->initializeInteractionModels( use_detailed_electron_emission_physics );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return d_interaction_model_emission();
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 2u;
  else
    return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
                               PhotonState& photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  // Make sure it is energetically possible for this reaction to occur
  testPrecondition( photon.getEnergy() >= this->getThresholdEnergy() );

  d_interaction_model( photon, bank );

  // The shell of interaction, which will be important for triplet production
  // is currently ignored
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

// The basic triplet production model
/*! \details Simplified Model: Assume that both outgoing electrons and the
 * positron are emitted with the mean emission energy (E_mean = E_kinetic/3). 
 * All three particles will be emitted in the direction of the original photon.
 * The positron will be immediately annihilated but the annihilation will not 
 * occur in-flight (isotropic emission of annihilation photons in lab system). 
 */
template<typename InterpPolicy, bool processed_cross_section>
void TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteraction(
                                                           PhotonState& photon,
                                                           ParticleBank& bank )
{
  // Handle the generated electron and the ejected orbital electron
  {
    Teuchos::RCP<ParticleState> electron_1(
				     new ElectronState( photon, true, true ) );

    Teuchos::RCP<ParticleState> electron_2(
                                     new ElectronState( photon, true, true ) );

    const double total_available_kinetic_energy = photon.getEnergy() -
      2*Utility::PhysicalConstants::electron_rest_mass_energy;

    const double mean_electron_kinetic_energy =
      total_available_kinetic_energy/3;

    electron_1->setEnergy( mean_electron_kinetic_energy );
  
    bank.push( electron_1 );

    // Electron 2 is emitted in the direction of the incoming photon
    electron_2->setEnergy( mean_electron_kinetic_energy );

    bank.push( electron_2 );
  }

  // Handle the annihilation photons
  {
    // Sample an isotropic outgoing angle for the annihilation photon
    double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    // Sample the azimuthal angle
    double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Set the new energy
    photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

    // Set the new direction of the annihilation photon
    photon.rotateDirection( angle_cosine, azimuthal_angle );

    // Reset the collision number since this is technically a new photon
    photon.resetCollisionNumber();

    // Create the second annihilation photon
    Teuchos::RCP<PhotonState> annihilation_photon(
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
}

// The detailed triplet production model
/*! \todo Implement the detailed pair production model.
 */
template<typename InterpPolicy, bool processed_cross_section>
void TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::detailedInteraction(
                                                           PhotonState& photon,
                                                           ParticleBank& bank )
{
  THROW_EXCEPTION( std::runtime_error,
                   "Error: The detailed triplet production model has not been "
                   "implemented yet!" );
}
  
// The number of photons emitted from triplet production using simple model
template<typename InterpPolicy, bool processed_cross_section>
unsigned TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteractionPhotonEmission()
{
  return 2u;
}

// The number of photons emitted from triplet production using detailed model
template<typename InterpPolicy, bool processed_cross_section>
unsigned TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::detailedInteractionPhotonEmission()
{
  return 0u;
}

// Initialize interaction models
template<typename InterpPolicy, bool processed_cross_section>
void TripletProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::initializeInteractionModels(
                            const bool use_detailed_electron_emission_physics )
{
  // Note: Detailed electron emission is not currently supported. Positron
  //       transport must be implemented first
  d_interaction_model = basicInteraction;
  d_interaction_model_emission = basicInteractionPhotonEmission;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TripletProductionPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
