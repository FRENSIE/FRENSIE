//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronCollisionHandler.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron collision handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronCollisionHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronCollisionHandler::AdjointElectronCollisionHandler(
                                               const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the macroscopic cross section for a specific reaction
double AdjointElectronCollisionHandler::getMacroscopicReactionCrossSection(
                        const AdjointElectronState& adjoint_electron,
                        const AdjointElectroatomicReactionType reaction ) const
{
  if( this->isCellVoid( adjoint_electron.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(adjoint_electron.getCell())->getMacroscopicReactionCrossSection(
                                                    adjoint_electron.getEnergy(),
                                                    reaction );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronCollisionHandler.cpp
//---------------------------------------------------------------------------//
