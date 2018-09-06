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

// Return the differential cross section
double VoidAbsorptionElectroatomicReaction::getDifferentialCrossSection(
                                                           const double,
                                                           const double ) const
{
  return 0.0;
}

// Simulate the reaction
void VoidAbsorptionElectroatomicReaction::react(
                            ElectronState&,
                            ParticleBank&,
                            Data::SubshellType& subshell_of_interaction ) const
{ 
  subshell_of_interaction = Data::UNKNOWN_SUBSHELL;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
