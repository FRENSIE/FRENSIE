//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon collision handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonCollisionHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonCollisionHandler::AdjointPhotonCollisionHandler(
                                               const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the macroscopic cross section for a specific reaction
double AdjointPhotonCollisionHandler::getMacroscopicReactionCrossSection(
                          const AdjointPhotonState& adjoint_photon,
                          const AdjointPhotoatomicReactionType reaction ) const
{
  if( this->isCellVoid( adjoint_photon.getCell() ) )
    return 0.0;
  else
  {
    return this->getMaterial(adjoint_photon.getCell())->getMacroscopicReactionCrossSection(
                                                    adjoint_photon.getEnergy(),
                                                    reaction );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonCollisionHandler.cpp
//---------------------------------------------------------------------------//
