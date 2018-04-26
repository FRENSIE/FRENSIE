//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Electron collision handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectronCollisionHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ElectronCollisionHandler::ElectronCollisionHandler(
                                               const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the macroscopic cross section for a specific reaction
double ElectronCollisionHandler::getMacroscopicReactionCrossSection(
                               const ElectronState& electron,
                               const ElectroatomicReactionType reaction ) const
{
  if( this->isCellVoid( electron.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(electron.getCell())->getMacroscopicReactionCrossSection(
                                                          electron.getEnergy(),
                                                          reaction );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronCollisionHandler.cpp
//---------------------------------------------------------------------------//
