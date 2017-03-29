//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Neutron collision handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronCollisionHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NeutronCollisionHandler::NeutronCollisionHandler(
                                               const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the macroscopic cross section for a specific reaction
double NeutronCollisionHandler::getMacroscopicReactionCrossSection(
                                     const NeutronState& neutron,
                                     const NuclearReactionType reaction ) const
{
  if( this->isCellVoid( neutron.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(neutron.getCell())->getMacroscopicReactionCrossSection(
                                                           neutron.getEnergy(),
                                                           reaction );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronCollisionHandler.cpp
//---------------------------------------------------------------------------//
