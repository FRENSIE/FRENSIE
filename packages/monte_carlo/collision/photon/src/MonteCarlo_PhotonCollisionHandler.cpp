//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Photon collision handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonCollisionHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhotonCollisionHandler::PhotonCollisionHandler(
                                               const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the macroscopic cross section for a specific reaction
double PhotonCollisionHandler::getMacroscopicReactionCrossSection(
                                 const PhotonState& photon,
                                 const PhotoatomicReactionType reaction ) const
{
  if( this->isCellVoid( photon.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(photon.getCell())->getMacroscopicReactionCrossSection(
                                                           photon.getEnergy(),
                                                           reaction );
  }
}

// Get the macroscopic cross section for a specific reaction
double PhotonCollisionHandler::getMacroscopicReactionCrossSection(
                                const PhotonState& photon,
                                const PhotonuclearReactionType reaction ) const
{
  if( this->isCellVoid( photon.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(photon.getCell())->getMacroscopicReactionCrossSection(
                                                           photon.getEnergy(),
                                                           reaction );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonCollisionHandler.cpp
//---------------------------------------------------------------------------//
