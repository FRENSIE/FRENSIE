//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  The photoatom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotoatomCore.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the static member data
const boost::unordered_set<PhotoatomicReactionType>
PhotoatomCore::absorption_reaction_types =
  PhotoatomCore::setDefaultAbsorptionReactionTypes();

// Set the default absorption reaction types
boost::unordered_set<PhotoatomicReactionType>
PhotoatomCore::setDefaultAbsorptionReactionTypes()
{
  boost::unordered_set<PhotoatomicReactionType> tmp_absorption_reaction_types;
  tmp_absorption_reaction_types.insert(
				    TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			       K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			     P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			     P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  tmp_absorption_reaction_types.insert(
			      Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  return tmp_absorption_reaction_types;
}

// Default constructor
PhotoatomCore::PhotoatomCore()
  : d_total_reaction(),
    d_total_absorption_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_miscellaneous_reactions(),
    d_relaxation_model(),
    d_grid_searcher()
{ /* ... */ }

// Advanced constructor
/*! \details It is assumed that the scattering, absorption and miscellaneous
 * reactions have already been organized appropriately. The total and total
 * absorption cross sections should have been created from the scattering
 * and absorption reactions.
 */
PhotoatomCore::PhotoatomCore(
      const Teuchos::RCP<const PhotoatomicReaction>& total_reaction,
      const Teuchos::RCP<const PhotoatomicReaction>& total_absorption_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstReactionMap& miscellaneous_reactions,
      const Teuchos::RCP<const AtomicRelaxationModel>& relaxation_model,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
  : d_total_reaction( total_reaction ),
    d_total_absorption_reaction( total_absorption_reaction ),
    d_scattering_reactions( d_scattering_reactions ),
    d_absorption_reactions( absorption_reactions ),
    d_miscellaneous_reactions( miscellaneous_reactions ),
    d_relaxation_model( relaxation_model ),
    d_grid_searcher( grid_searcher )
{
  // Make sure the total reaction is valid
  testPrecondition( !total_reaction.is_null() );
  // Make sure the absorption reaction is valid
  testPrecondition( !total_absorption_reaction.is_null() );
  // Make sure the scattering reactions map is valid
  testPrecondition( scattering_reactions.size() > 0 );
  // Make sure the absorption reactions map is valid
  testPrecondition( absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !relaxation_model.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !d_grid_searcher.is_null() );
}

//! Copy constructor
PhotoatomCore::PhotoatomCore( const PhotoatomCore& instance )
  : d_total_reaction( instance.d_total_reaction ),
    d_total_absorption_reaction( instance.d_total_absorption_reaction ),
    d_scattering_reactions( instance.d_scattering_reactions ),
    d_absorption_reactions( instance.d_absorption_reactions ),
    d_miscellaneous_reactions( instance.d_miscellaneous_reactions ),
    d_relaxation_model( instance.d_relaxation_model ),
    d_grid_searcher( instance.d_grid_searcher )
{
  // Make sure the total reaction is valid
  testPrecondition( !instance.d_total_reaction.is_null() );
  // Make sure the absorption reaction is valid
  testPrecondition( !instance.d_total_absorption_reaction.is_null() );
  // Make sure the scattering and absorption reaction maps are valid
  testPrecondition( instance.d_scattering_reactions.size() +
		    instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !instance.d_relaxation_model.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !instance.d_grid_searcher.is_null() );
}

//! Assignment Operator
PhotoatomCore& PhotoatomCore::operator=( const PhotoatomCore& instance )
{
  // Make sure the total reaction is valid
  testPrecondition( !instance.d_total_reaction.is_null() );
  // Make sure the absorption reaction is valid
  testPrecondition( !instance.d_total_absorption_reaction.is_null() );
  // Make sure the scattering and absorption reaction maps are valid
  testPrecondition( instance.d_scattering_reactions.size() +
		    instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !instance.d_relaxation_model.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !instance.d_grid_searcher.is_null() );

  // Avoid self-assignment
  if( this != &instance )
  {
    d_total_reaction = instance.d_total_reaction;
    d_total_absorption_reaction = instance.d_total_absorption_reaction;
    d_scattering_reactions = instance.d_scattering_reactions;
    d_absorption_reactions = instance.d_absorption_reactions;
    d_relaxation_model = instance.d_relaxation_model;
    d_grid_searcher = instance.d_grid_searcher;
  }

  return *this;
}

// Test if all of the reactions share a common energy grid
bool PhotoatomCore::hasSharedEnergyGrid() const
{
  if( !d_total_reaction->isEnergyGridShared( *d_total_absorption_reaction ) )
    return false;

  ConstReactionMap::const_iterator reaction_it =
    d_scattering_reactions.begin();

  while( reaction_it != d_scattering_reactions.end() )
  {
    if( !d_total_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  reaction_it = d_absorption_reactions.begin();

  while( reaction_it != d_absorption_reactions.end() )
  {
    if( !d_total_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  return true;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomCore.cpp
//---------------------------------------------------------------------------//
