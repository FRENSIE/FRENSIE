//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomCore.cpp
//! \author Luke Kersting
//! \brief  The positron-atom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PositronatomCore.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
const bool PositronatomCore::s_default_absorption_reaction_types_set =
  PositronatomCore::setDefaultAbsorptionReactionTypes();

// Set the default scattering reaction types
bool PositronatomCore::setDefaultAbsorptionReactionTypes()
{
  PositronatomCore::ReactionEnumTypeSet absorption_reaction_types;

  absorption_reaction_types.insert( POSITRON_ANNIHILATION_POSITRONATOMIC_REACTION );

  PositronatomCore::BaseType::setAbsorptionReactionTypes( absorption_reaction_types );

  return true;
}

// Default constructor
PositronatomCore::PositronatomCore()
  : BaseType()
{ /* ... */ }

// Advanced constructor
/*! \details It is assumed that the scattering, absorption and miscellaneous
 * reactions have already been organized appropriately. The total and total
 * absorption cross sections should have been created from the scattering
 * and absorption reactions.
 */
PositronatomCore::PositronatomCore(
      const std::shared_ptr<const PositronatomicReaction>& total_reaction,
      const std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstReactionMap& miscellaneous_reactions,
      const std::shared_ptr<const AtomicRelaxationModel> relaxation_model,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher )
  : BaseType( total_reaction,
              total_absorption_reaction,
              scattering_reactions,
              absorption_reactions,
              miscellaneous_reactions,
              relaxation_model,
              grid_searcher )
{ /* ... */ }

// Copy constructor
PositronatomCore::PositronatomCore( const PositronatomCore& instance )
  : BaseType( instance )
{ /* ... */ }

//! Assignment Operator
PositronatomCore& PositronatomCore::operator=( const PositronatomCore& instance )
{
  // Avoid self-assignment
  if( this != &instance )
    BaseType::operator=( instance );

  return *this;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomCore.cpp
//---------------------------------------------------------------------------//

