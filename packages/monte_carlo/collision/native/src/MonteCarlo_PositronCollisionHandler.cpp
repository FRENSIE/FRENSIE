//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronCollisionHandler.cpp
//! \author Luke Kersting
//! \brief  Positron collision handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PositronCollisionHandler.hpp"
#include "MonteCarlo_PositronCollisionHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PositronCollisionHandler::PositronCollisionHandler(
                                               const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the macroscopic cross section for a specific reaction
double PositronCollisionHandler::getMacroscopicReactionCrossSection(
                               const PositronState& positron,
                               const PositronatomicReactionType reaction ) const
{
  if( this->isCellVoid( positron.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(positron.getCell())->getMacroscopicReactionCrossSection(
                                                          positron.getEnergy(),
                                                          reaction );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronCollisionHandler.cpp
//---------------------------------------------------------------------------//
