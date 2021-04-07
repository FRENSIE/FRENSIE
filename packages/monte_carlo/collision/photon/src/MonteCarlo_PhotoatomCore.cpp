//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  The photoatom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotoatomCore.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
const bool PhotoatomCore::s_default_absorption_reaction_types_set =
  PhotoatomCore::setDefaultAbsorptionReactionTypes();

// Set the default absorption reaction types
bool PhotoatomCore::setDefaultAbsorptionReactionTypes()
{
  PhotoatomCore::ReactionEnumTypeSet absorption_reaction_types;
  
  absorption_reaction_types.insert(
				    TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			       K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			     P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			     P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  absorption_reaction_types.insert(
			      Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  PhotoatomCore::BaseType::setAbsorptionReactionTypes( absorption_reaction_types );

  return true;
}

// Default constructor
PhotoatomCore::PhotoatomCore()
  : BaseType()
{ /* ... */ }

// Advanced constructor
/*! \details It is assumed that the scattering, absorption and miscellaneous
 * reactions have already been organized appropriately. The total and total
 * absorption cross sections should have been created from the scattering
 * and absorption reactions.
 */
PhotoatomCore::PhotoatomCore(
   const std::shared_ptr<const PhotoatomicReaction>& total_reaction,
   const std::shared_ptr<const PhotoatomicReaction>& total_absorption_reaction,
   const ConstReactionMap& scattering_reactions,
   const ConstReactionMap& absorption_reactions,
   const ConstReactionMap& miscellaneous_reactions,
   const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
   const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
   grid_searcher )
  : BaseType( total_reaction,
              total_absorption_reaction,
              scattering_reactions,
              absorption_reactions,
              miscellaneous_reactions,
              relaxation_model,
              grid_searcher )
{ /* ... */ }

// Copy constructor
PhotoatomCore::PhotoatomCore( const PhotoatomCore& instance )
  : BaseType( instance )
{ /* ... */ }

// Assignment Operator
PhotoatomCore& PhotoatomCore::operator=( const PhotoatomCore& instance )
{
  // Avoid self-assignment
  if( this != &instance )
    BaseType::operator=( instance );

  return *this;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomCore.cpp
//---------------------------------------------------------------------------//
