//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionElectroatomicReaction.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The void absorption electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"

namespace MonteCarlo{

// Return the reaction type
ElectroatomicReactionType VoidAbsorptionElectroatomicReaction::getReactionType() const
{
  return TOTAL_ABSORPTION_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
void VoidAbsorptionElectroatomicReaction::react( ElectronState&,
                                                 ParticleBank&,
                                                 Data::SubshellType& ) const
{ /* ... */ }
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
