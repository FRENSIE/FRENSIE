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
                                const PhotonuclearReactionType reaction ) const
{
  return this->getMacroscopicReactionCrossSection( photon.getCell(),
                                                   photon.getEnergy(),
                                                   reaction );
}

// Get the macroscopic cross section for a specific reaction
double PhotonCollisionHandler::getMacroscopicReactionCrossSection(
                         const Geometry::ModuleTraits::InternalCellHandle cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
  {
    return this->getMaterial(cell)->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
  }
}

// Get the macroscopic cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
double PhotonCollisionHandler::getMacroscopicReactionCrossSectionQuick(
                                const PhotonState& photon,
                                const PhotonuclearReactionType reaction ) const
{
  return this->getMacroscopicReactionCrossSectionQuick( photon.getCell(),
                                                        photon.getEnergy(),
                                                        reaction );
}

// Get the macroscopic cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
double PhotonCollisionHandler::getMacroscopicReactionCrossSectionQuick(
                         const Geometry::ModuleTraits::InternalCellHandle cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const
{
  // Make sure that the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );
  
  return this->getMaterial(cell)->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonCollisionHandler.cpp
//---------------------------------------------------------------------------//
