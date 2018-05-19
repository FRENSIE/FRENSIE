//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionPositronatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The void absorption positron-atomic reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"

namespace MonteCarlo{

// Return reaction type
PositronatomicReactionType VoidAbsorptionPositronatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_POSITRONATOMIC_REACTION;
}

// Simulate the reaction
void VoidAbsorptionPositronatomicReaction::react(
       PositronState& positron,
       ParticleBank& bank,
       Data::SubshellType& shell_of_interaction ) const
{ /* ... */ }
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
