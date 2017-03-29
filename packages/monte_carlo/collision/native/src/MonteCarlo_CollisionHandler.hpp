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

  //! Add a material to the collision handler (neutron-photon mode)
  void addMaterial(
          const Teuchos::RCP<const NeutronMaterial>& neutron_material,
          const Teuchos::RCP<const PhotonMaterial>& photon_material,
          const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
          cells_containing_material );

  //! Add a material to the collision handler (photon-electron mode)
  void addMaterial(
              const Teuchos::RCP<const PhotonMaterial>& photon_material,
              const Teuchos::RCP<const ElectronMaterial>& electron_material,
              const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
              cells_containing_material );

  //! Add a material to the collision handler (neutron-photon-electron mode)
  void addMaterial(
              const Teuchos::RCP<const NeutronMaterial>& neutron_material,
              const Teuchos::RCP<const PhotonMaterial>& photon_material,
              const Teuchos::RCP<const ElectronMaterial>& electron_material,
              const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
              cells_containing_material );

  //! Add a material to the collision handler (neutron mode)
  using NeutronCollisionHandler::addMaterial;

  //! Add a material to the collision handler (photon mode)
  using PhotonCollisionHandler::addMaterial;

  //! Add a material to the collision handler (adjoint photon mode)
  using AdjointPhotonCollisionHandler::addMaterial;

  //! Add a material to the collision handler (electron mode)
  using ElectronCollisionHandler::addMaterial;

  //! Check if a cell is void (as experienced by the given particle type)
  bool isCellVoid( const Geometry::ModuleTraits::InternalCellHandle cell,
                   const MonteCarlo::ParticleType particle_type );

  //! Get the total macroscopic cross section of a material for neutrons
  using NeutronCollisionHandler::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for photons
  using PhotonCollisionHandler::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for adjoint photons
  using AdjointPhotonCollisionHandler::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for electrons
  using ElectronCollisionHandler::getMacroscopicTotalCrossSection;

  //! Get the total forward macroscopic cs of a material for neutrons
  using NeutronCollisionHandler::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for photons
  using PhotonCollisionHandler::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for adjoint photons
  using AdjointPhotonCollisionHandler::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for adjoint electrons
  using ElectronCollisionHandler::getMacroscopicTotalForwardCrossSection;

  //! Have a neutron collide with the material in a cell
  using NeutronCollisionHandler::collideWithCellMaterial;

  //! Have a photon collide with the material in a cell
  using PhotonCollisionHandler::collideWithCellMaterial;

  //! Have an adjoint photon collide with the material in a cell
  using AdjointPhotonCollisionHandler::collideWithCellMaterial;

  //! Have an electron collide with the material in a cell
  using ElectronCollisionHandler::collideWithCellMaterial;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandler.hpp
//---------------------------------------------------------------------------//
