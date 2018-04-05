//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
AdjointElectroatomCore::AdjointElectroatomCore()
  : d_total_forward_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_grid_searcher()
{ /* ... */ }

// Constructor
AdjointElectroatomCore::AdjointElectroatomCore(
      const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher,
      const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
      const ReactionMap& scattering_reactions,
      const ReactionMap& absorption_reactions )
  : d_total_forward_reaction( total_forward_reaction ),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_grid_searcher( grid_searcher )
{
  // Make sure the total forward reaction is valid
  testPrecondition( total_forward_reaction.get() != NULL );
  // Make sure the scattering reaction map is valid
  testPrecondition( scattering_reactions.size() +
                    absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !d_grid_searcher.is_null() );

  // Assign the scattering reactions
  ReactionMap::const_iterator reaction_it =
    scattering_reactions.begin();

  while( reaction_it != scattering_reactions.end() )
  {
    d_scattering_reactions.insert( *reaction_it );

    ++reaction_it;
  }

  // Assign the absorption reactions
  reaction_it = absorption_reactions.begin();

  while( reaction_it != absorption_reactions.end() )
  {
    d_absorption_reactions.insert( *reaction_it );

    ++reaction_it;
  }

  // Make sure the reactions have been organized appropriately
  testPostcondition( d_scattering_reactions.size() +
                     d_absorption_reactions.size() > 0 );
}

// Copy constructor
AdjointElectroatomCore::AdjointElectroatomCore(
                                        const AdjointElectroatomCore& instance )
  : d_total_forward_reaction( instance.d_total_forward_reaction ),
    d_scattering_reactions( instance.d_scattering_reactions ),
    d_absorption_reactions( instance.d_absorption_reactions ),
    d_grid_searcher( instance.d_grid_searcher )
{
  // Make sure the total forward reaction is valid
  testPrecondition( instance.d_total_forward_reaction.get() != NULL );
  // Make sure the scattering reaction map is valid
  testPrecondition( instance.d_scattering_reactions.size() +
                    instance.d_absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !instance.d_grid_searcher.is_null() );
}

// Assignment operator
AdjointElectroatomCore& AdjointElectroatomCore::operator=(
                                        const AdjointElectroatomCore& instance )
{
  // Make sure the total forward reaction is valid
  testPrecondition( instance.d_total_forward_reaction.get() != NULL );
  // Make sure the scattering reaction map is valid
  testPrecondition( instance.d_scattering_reactions.size() +
                    instance.d_absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !instance.d_grid_searcher.is_null() );

  // Avoid self-assignment
  if( this != &instance )
  {
    d_total_forward_reaction = instance.d_total_forward_reaction;
    d_scattering_reactions = instance.d_scattering_reactions;
    d_absorption_reactions = instance.d_absorption_reactions;
    d_grid_searcher = instance.d_grid_searcher;
  }

  return *this;
}

// Test if all of the reactions share a common energy grid
bool AdjointElectroatomCore::hasSharedEnergyGrid() const
{
  ConstReactionMap::const_iterator reaction_it =
    d_scattering_reactions.begin();

  while( reaction_it != d_scattering_reactions.end() )
  {
    if( !d_total_forward_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  reaction_it = d_absorption_reactions.begin();

  while( reaction_it != d_absorption_reactions.end() )
  {
    if( !d_total_forward_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  return true;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomCore.cpp
//---------------------------------------------------------------------------//

