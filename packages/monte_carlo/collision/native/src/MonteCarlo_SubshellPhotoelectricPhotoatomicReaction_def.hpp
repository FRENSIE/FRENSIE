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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellPhotoelectricPhotoatomicReaction(
                   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const SubshellType interaction_subshell,
		   const double binding_energy )
  : PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>( 
						      incoming_energy_grid,
						      cross_section,
						      threshold_energy_index ),
    d_interaction_subshell( interaction_subshell ),
    d_binding_energy( binding_energy ),
    d_reaction_type( convertSubshellEnumToPhotoatomicReactionEnum( 
						       interaction_subshell ) )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon, 
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // End the photon history
  photon.setAsGone();

  // The interaction subshell is not taken into account in this reaction
  shell_of_interaction = d_interaction_subshell;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction_type;
}

// Get the interaction subshell (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
SubshellType SubshellPhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshell() const
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
