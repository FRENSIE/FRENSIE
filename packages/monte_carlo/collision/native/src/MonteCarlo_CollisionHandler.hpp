//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_HANDLER_HPP
#define MONTE_CARLO_COLLISION_HANDLER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronCollisionHandler.hpp"
#include "MonteCarlo_PhotonCollisionHandler.hpp"
#include "MonteCarlo_AdjointPhotonCollisionHandler.hpp"
#include "MonteCarlo_ElectronCollisionHandler.hpp"

namespace MonteCarlo{

/*! The collision handler class
 * \details The collision handler class has been designed as a mix-in class
 * so that it is easier to add new events. In addition, the individual
 * collision handlers are better abstracted and easier to maintain when there
 * is a handler for each one.
 */
class CollisionHandler : public NeutronCollisionHandler,
                         public PhotonCollisionHandler,
                         public AdjointPhotonCollisionHandler,
                         public ElectronCollisionHandler
{

public:

  //! Constructor
  CollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  ~CollisionHandler()
  { /* ... */ }

  //! Add a material to the collision handler
  void addMaterial(
	      const Teuchos::RCP<NeutronMaterial>& neutron_material,
	      const Teuchos::RCP<PhotonMaterial>& photon_material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material );

  using NeutronCollisionHandler::addMaterial;
  using PhotonCollisionHandler::addMaterial;
  using AdjointPhotonCollisionHandler::addMaterial;
  using ElectronCollisionHandler::addMaterial;

  //! Check if a cell is void
  bool isCellVoid( const Geometry::ModuleTraits::InternalCellHandle cell,
                   const MonteCarlo::ParticleType particle_type );

  using NeutronCollisionHandler::getMacroscopicTotalCrossSection;
  using PhotonCollisionHandler::getMacroscopicTotalCrossSection;
  using AdjointPhotonCollisionHandler::getMacroscopicTotalCrossSection;
  using ElectronCollisionHandler::getMacroscopicTotalCrossSection;

  using NeutronCollisionHandler::getMacroscopicTotalForwardCrossSection;
  using PhotonCollisionHandler::getMacroscopicTotalForwardCrossSection;
  using AdjointPhotonCollisionHandler::getMacroscopicTotalForwardCrossSection;
  using ElectronCollisionHandler::getMacroscopicTotalForwardCrossSection;

  using NeutronCollisionHandler::collideWithCellMaterial;
  using PhotonCollisionHandler::collideWithCellMaterial;
  using AdjointPhotonCollisionHandler::collideWithCellMaterial;
  using ElectronCollisionHandler::collideWithCellMaterial;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandler.hpp
//---------------------------------------------------------------------------//
