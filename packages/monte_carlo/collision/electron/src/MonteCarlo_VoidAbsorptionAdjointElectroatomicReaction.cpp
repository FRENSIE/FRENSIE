//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The void absorption adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

// Return the reaction type
AdjointElectroatomicReactionType VoidAbsorptionAdjointElectroatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
void VoidAbsorptionAdjointElectroatomicReaction::react(
                            AdjointElectronState&,
                            ParticleBank&,
                            Data::SubshellType& subshell_of_interaction ) const
{
  subshell_of_interaction = Data::UNKNOWN_SUBSHELL;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
