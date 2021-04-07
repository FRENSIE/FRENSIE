//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The void absorption adjoint photoatomic reaction definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_VoidAbsorptionAdjointPhotoatomicReaction.hpp"

namespace MonteCarlo{

// Return the reaction type
AdjointPhotoatomicReactionType VoidAbsorptionAdjointPhotoatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION;
}

// Simulation the reaction
void VoidAbsorptionAdjointPhotoatomicReaction::react( AdjointPhotonState&,
                                                      ParticleBank&,
                                                      Data::SubshellType& ) const
{ /* ... */ }

// Simulate the reaction and track the number of sampling trials
void VoidAbsorptionAdjointPhotoatomicReaction::react(
                                   AdjointPhotonState&,
                                   ParticleBank&,
                                   Data::SubshellType& subshell_of_interaction,
                                   Counter& ) const
{ 
  subshell_of_interaction = Data::UNKNOWN_SUBSHELL;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
