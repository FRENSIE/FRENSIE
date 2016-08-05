//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellPhotoelectricPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The subshell photoelectric photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellPhotoelectricPhotoatomicReaction(
                   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const Data::SubshellType interaction_subshell,
		   const double binding_energy )
  : PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>(
						      incoming_energy_grid,
						      cross_section,
						      threshold_energy_index ),
    d_interaction_subshell( interaction_subshell ),
    d_binding_energy( binding_energy ),
    d_reaction_type( convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum(
						       interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellPhotoelectricPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const Data::SubshellType interaction_subshell,
       const double binding_energy )
  : PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>(
						      incoming_energy_grid,
						      cross_section,
						      threshold_energy_index,
						      grid_searcher ),
    d_interaction_subshell( interaction_subshell ),
    d_binding_energy( binding_energy ),
    d_reaction_type( convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum(
						       interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell !=Data::UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure he grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Simulate the reaction
/*! \details The electron is assumed to be emitted isotropically. Please review
 * the validity of this model and update if necessary.
 */
template<typename InterpPolicy, bool processed_cross_section>
void SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  // Make sure the photon energy is valid
  testPrecondition( photon.getEnergy() > d_binding_energy );

  // Create the emitted electron
  Teuchos::RCP<ParticleState> electron(
				     new ElectronState( photon, true, true ) );

  electron->setEnergy( photon.getEnergy() - d_binding_energy );

  // Sample an isotropic outgoing angle for the emitted angle
  double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the azimuthal angle
  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  electron->rotateDirection( angle_cosine, azimuthal_angle );

  bank.push( electron );

  // End the photon history
  photon.setAsGone();

  // Set the interaction subshell
  shell_of_interaction = d_interaction_subshell;

  // Make sure the scattering angle cosine is valid
  testPostcondition( angle_cosine >= -1.0 );
  testPostcondition( angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPostcondition( azimuthal_angle >= 0.0 );
  testPostcondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction_type;
}

// Get the interaction subshell (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
Data::SubshellType SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshell() const
{
  return d_interaction_subshell;
}

// Get the subshell binding energy (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
double SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshellBindingEnergy() const
{
  return d_binding_energy;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellPhotoelectricPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
