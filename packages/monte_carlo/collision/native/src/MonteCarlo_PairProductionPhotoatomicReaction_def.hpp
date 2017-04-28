//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The pair production photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::PairProductionPhotoatomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const bool use_detailed_electron_emission_physics )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
{
  this->initializeInteractionModels( use_detailed_electron_emission_physics );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::PairProductionPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const bool use_detailed_electron_emission_physics )
  : BaseType( incoming_energy_grid,
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
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return d_interaction_model_emission();
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
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
				     Data::SubshellType& shell_of_interaction ) const
{
  // Make sure it is energetically possible for this reaction to occur
  testPrecondition( photon.getEnergy() >= this->getThresholdEnergy() );

  d_interaction_model( photon, bank );

  // The shell of interaction, which will be important for triplet production
  // is currently ignored
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

// The basic pair production model
/*! \details Simplified Model: Assume that the outgoing electron is emitted at
 * the mean emission angle (theta_mean = m_e*c^2/E_mean), w.r.t the original
 * photon direction, with the mean emission energy (E_mean = E_kinetic/2).
 * The positron will also be emitted at the mean emission angle and with the
 * remaining energy (E_mean). It will be immediately annihilated but
 * the annihilation will not occur in-flight (isotropic emission of
 * annihilation photons in lab system). 
 */
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteraction(
							   PhotonState& photon,
							   ParticleBank& bank )
{
  Teuchos::RCP<ParticleState> electron(
				     new ElectronState( photon, true, true ) );

  const double total_available_kinetic_energy = photon.getEnergy() -
    2*Utility::PhysicalConstants::electron_rest_mass_energy;

  const double mean_electron_kinetic_energy =
    total_available_kinetic_energy/2;

  double mean_emission_angle_cosine =
    cos( Utility::PhysicalConstants::electron_rest_mass_energy/
         mean_electron_kinetic_energy );

  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  electron->setEnergy( mean_electron_kinetic_energy );
  electron->rotateDirection( mean_emission_angle_cosine,
                             azimuthal_angle );

  bank.push( electron );

  // Change the photon's direction based on the initial direction of the
  // emitted positron (to conserve momentum we must rotate the
  // azimuthal angle by pi)
  azimuthal_angle = fmod( azimuthal_angle + Utility::PhysicalConstants::pi,
                          2*Utility::PhysicalConstants::pi );
  photon.rotateDirection( mean_emission_angle_cosine, azimuthal_angle );

  // Sample an isotropic outgoing angle for the annihilation photon
  double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the azimuthal angle
  azimuthal_angle = 2*Utility::PhysicalConstants::pi*
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

// The detailed pair production model
/*! \todo Implement the detailed pair production model.
 */
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::detailedInteraction(
							   PhotonState& photon,
							   ParticleBank& bank )
{
  THROW_EXCEPTION( std::runtime_error,
                   "Error: The detailed pair production model has not been "
                   "implemented yet!" );
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

// Initialize interaction models
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::initializeInteractionModels(
                            const bool use_detailed_electron_emission_physics )
{
  // Note: Detailed electron emission is not currently supported. Positron
  //       transport must be implemented first
  d_interaction_model = basicInteraction;
  d_interaction_model_emission = basicInteractionPhotonEmission;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
