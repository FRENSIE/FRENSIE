//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom core class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
AdjointPhotoatomCore::AdjointPhotoatomCore()
  : d_total_forward_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_line_energy_reactions(),
    d_critical_line_energies(),
    d_grid_searcher()
{ /* ... */ }

// Constructor
/*! \details Care must be taken when setting the critical line energies,
 * scattering reactions and line energy reactions. The critical line energies
 * must correspond to the critical line energies that are being used by the
 * incoherent scattering reactions. In addition, every line energy reaction
 * must have a corresponding critical line energy. Without a critical line 
 * energy the line energy reaction will never occur.
 */
AdjointPhotoatomCore::AdjointPhotoatomCore(
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const Teuchos::ArrayRCP<const double>& critical_line_energies,
      const std::shared_ptr<const PhotoatomicReaction>& total_forward_reaction,
      const ReactionMap& scattering_reactions,
      const ReactionMap& absorption_reactions,
      const LineEnergyReactionMap& line_energy_reactions )
  : d_total_forward_reaction( total_forward_reaction ),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_line_energy_reactions(),
    d_critical_line_energies( critical_line_energies ),
    d_grid_searcher( grid_searcher )
{
  // Make sure the total forward reaction is valid
  testPrecondition( total_forward_reaction.get() != NULL );
  // Make sure the scattering reaction map is valid
  testPrecondition( scattering_reactions.size() +
                    absorption_reactions.size() > 0 );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                                    line_energy_reactions,
                                                    critical_line_energies ) );
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

  // Assign the line energy reactions
  LineEnergyReactionMap::const_iterator line_energy_reaction_it =
    line_energy_reactions.begin();

  while( line_energy_reaction_it != line_energy_reactions.end() )
  {
    reaction_it = line_energy_reaction_it->second.begin();

    while( reaction_it != line_energy_reaction_it->second.end() )
    {
      d_line_energy_reactions[line_energy_reaction_it->first][reaction_it->first] =
        reaction_it->second;

      ++reaction_it;
    }

    ++line_energy_reaction_it;
  }

  // Make sure the reactions have been organized appropriately
  testPostcondition( d_scattering_reactions.size() +
                     d_absorption_reactions.size() > 0 );
}

// Copy constructor
AdjointPhotoatomCore::AdjointPhotoatomCore(
                                         const AdjointPhotoatomCore& instance )
  : d_total_forward_reaction( instance.d_total_forward_reaction ),
    d_scattering_reactions( instance.d_scattering_reactions ),
    d_absorption_reactions( instance.d_absorption_reactions ),
    d_line_energy_reactions( instance.d_line_energy_reactions ),
    d_critical_line_energies( instance.d_critical_line_energies ),
    d_grid_searcher( instance.d_grid_searcher )
{
  // Make sure the total forward reaction is valid
  testPrecondition( instance.d_total_forward_reaction.get() != NULL );
  // Make sure the scattering reaction map is valid
  testPrecondition( instance.d_scattering_reactions.size() +
                    instance.d_absorption_reactions.size() > 0 );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                         instance.d_line_energy_reactions,
                                         instance.d_critical_line_energies ) );
  // Make sure the grid searcher is valid
  testPrecondition( !instance.d_grid_searcher.is_null() );
}

// Assignment operator
AdjointPhotoatomCore& AdjointPhotoatomCore::operator=(
                                         const AdjointPhotoatomCore& instance )
{
  // Make sure the total forward reaction is valid
  testPrecondition( instance.d_total_forward_reaction.get() != NULL );
  // Make sure the scattering reaction map is valid
  testPrecondition( instance.d_scattering_reactions.size() +
                    instance.d_absorption_reactions.size() > 0 );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                         instance.d_line_energy_reactions,
                                         instance.d_critical_line_energies ) );
  // Make sure the grid searcher is valid
  testPrecondition( !instance.d_grid_searcher.is_null() );

  // Avoid self-assignment
  if( this != &instance )
  {
    d_total_forward_reaction = instance.d_total_forward_reaction;
    d_scattering_reactions = instance.d_scattering_reactions;
    d_absorption_reactions = instance.d_absorption_reactions;
    d_line_energy_reactions = instance.d_line_energy_reactions;
    d_critical_line_energies = instance.d_critical_line_energies;
    d_grid_searcher = instance.d_grid_searcher;
  }

  return *this;
}

// Test if all of the reactions share a common energy grid
bool AdjointPhotoatomCore::hasSharedEnergyGrid() const
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
// end MonteCarlo_AdjointPhotoatomCore.cpp
//---------------------------------------------------------------------------//
