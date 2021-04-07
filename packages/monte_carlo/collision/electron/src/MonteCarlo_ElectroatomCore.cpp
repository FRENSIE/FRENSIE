//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  The electroatom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomCore.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
const bool ElectroatomCore::s_default_absorption_reaction_types_set =
  ElectroatomCore::setDefaultAbsorptionReactionTypes();

// Set the default absorption reaction types
bool ElectroatomCore::setDefaultAbsorptionReactionTypes()
{
  ElectroatomCore::ReactionEnumTypeSet absorption_reaction_types;

  absorption_reaction_types.insert( POSITRON_ANNIHILATION_ELECTROATOMIC_REACTION );

  ElectroatomCore::BaseType::setAbsorptionReactionTypes( absorption_reaction_types );

  return true;
}

// Default constructor
ElectroatomCore::ElectroatomCore()
  : BaseType()
{ /* ... */ }

// Advanced constructor
/*! \details It is assumed that the scattering, absorption and miscellaneous
 * reactions have already been organized appropriately. The total and total
 * absorption cross sections should have been created from the scattering
 * and absorption reactions.
 */
ElectroatomCore::ElectroatomCore(
      const std::shared_ptr<const ElectroatomicReaction>& total_reaction,
      const std::shared_ptr<const ElectroatomicReaction>& total_absorption_reaction,
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
ElectroatomCore::ElectroatomCore( const ElectroatomCore& instance )
  : BaseType( instance )
{ /* ... */ }

// Assignment Operator
ElectroatomCore& ElectroatomCore::operator=( const ElectroatomCore& instance )
{
  // Avoid self-assignment
  if( this != &instance )
    BaseType::operator=( instance );

  return *this;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomCore.cpp
//---------------------------------------------------------------------------//

