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

// Return the differential cross section
double VoidAbsorptionPositronatomicReaction::getDifferentialCrossSection(
                                                           const double,
                                                           const double ) const
{
  return 0.0;
}

// Simulate the reaction
void VoidAbsorptionPositronatomicReaction::react(
                               PositronState&,
                               ParticleBank&,
                               Data::SubshellType& shell_of_interaction ) const
{ 
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
