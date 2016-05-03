//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoelectricPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The photoelectric photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::PhotoelectricPhotoatomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
						       incoming_energy_grid,
						       cross_section,
						       threshold_energy_index )
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
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::PhotoelectricPhotoatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
  : StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>(
						       incoming_energy_grid,
						       cross_section,
						       threshold_energy_index,
						       grid_searcher )
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
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */ 
template<typename InterpPolicy, bool processed_cross_section>
unsigned PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
/*! \details This does not include electrons from atomic relaxation.
 */ 
template<typename InterpPolicy, bool processed_cross_section>
unsigned PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void 
PhotoelectricPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon, 
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // End the photon history
  photon.setAsGone();

  // The interaction subshell is not taken into account in this reaction
  shell_of_interaction = UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOELECTRIC_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoelectricPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
