//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic constructor without doppler broadening
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const SubshellType interaction_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
                                                      incoming_energy_grid,
						      cross_section,
                                                      threshold_energy_index ),
    d_scattering_distribution( interaction_subshell,
			       binding_energy,
			       occupation_number ),
    d_reaction_type( convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
						       interaction_subshell ) )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
}

// Constructor without doppler broadening
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const SubshellType interaction_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
                                                      incoming_energy_grid,
						      cross_section,
                                                      threshold_energy_index,
						      grid_searcher ),
    d_scattering_distribution( interaction_subshell,
			       binding_energy,
			       occupation_number ),
    d_reaction_type( convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
						       interaction_subshell ) )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Basic constructor for doppler broadening
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const SubshellType interaction_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
       const Teuchos::RCP<const Utility::OneDDistribution>& compton_profile )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
                                                      incoming_energy_grid,
						      cross_section,
                                                      threshold_energy_index ),
    d_scattering_distribution( interaction_subshell,
			       binding_energy,
			       occupation_number,
			       compton_profile ),
    d_reaction_type( convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
						       interaction_subshell ) )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  // Make sure the compton profile is valid
  testPrecondition( !compton_profile.is_null() );
}

// Constructor for doppler broadening
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const SubshellType interaction_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
       const Teuchos::RCP<const Utility::OneDDistribution>& compton_profile )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
                                                      incoming_energy_grid,
						      cross_section,
                                                      threshold_energy_index,
						      grid_searcher ),
    d_scattering_distribution( interaction_subshell,
			       binding_energy,
			       occupation_number,
			       compton_profile ),
    d_reaction_type( convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
						       interaction_subshell ) )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  // Make sure the compton profile is valid
  testPrecondition( !compton_profile.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( 
						    const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction_type;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     PhotonState& photon, 
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution.scatterPhoton( photon, bank, shell_of_interaction);

  photon.incrementCollisionNumber();
}

// Get the interaction subshell (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
inline SubshellType SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshell() const
{
  return d_scattering_distribution.getSubshell();
}

// Get the subshell binding energy (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
inline double SubshellIncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshellBindingEnergy() const
{
  return d_scattering_distribution.getBindingEnergy();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
