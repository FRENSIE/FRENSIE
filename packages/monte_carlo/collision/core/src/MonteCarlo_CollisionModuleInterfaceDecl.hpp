//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Collision module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_MODULE_INTERFACE_DECL_HPP
#define MONTE_CARLO_COLLISION_MODULE_INTERFACE_DECL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_PositronatomicReactionType.hpp"

/*! \defgroup collision_module Collision Module
 * \ingroup physics_simulation_modules
 */

namespace MonteCarlo{

//! The struct that provides the default collision handler compile time error
template<typename CollisionHandler>
struct UndefinedCollisionHandler
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline void notDefined() { return CollisionHandler::this_collision_handler_is_missing_an_interface_specialization(); }
};

/*! \brief  Default collision module interface class
 * \ingroup collision_module
 */
template<typename CollisionHandler>
class CollisionModuleInterface
{

public:

  //! The external material handle class (used within the collision handler)
  typedef int ExternalMaterialHandle;

  //! The internal material handle class (used within FRENSIE)
  typedef ModuleTraits::InternalMaterialHandle InternalMaterialHandle;

  //! The value of an invalid external material handle
  static const ExternalMaterialHandle invalid_external_material_handle = 0;

  //! Set the collision handler instance
  static inline void setHandlerInstance(
                   const std::shared_ptr<CollisionHandler>& collision_handler )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Check if a cell is void
  static inline bool isCellVoid(
			 const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Get the total macroscopic cross section of a material
  template<typename ParticleStateType>
  static inline double getMacroscopicTotalCrossSection(
                                            const ParticleStateType& particle )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Get the total forward macroscopic cross section of a material
  template<typename ParticleStateType>
  static inline double getMacroscopicTotalForwardCrossSection(
                                            const ParticleStateType& particle )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Sample the optical path length traveled by a particle before a collision
  static inline double sampleOpticalPathLength()
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Collide with the material in a cell
  template<typename ParticleStateType>
  static inline void collideWithCellMaterial( ParticleStateType& particle,
					      ParticleBank& bank )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

};

//! Set the collision handler instance
template<typename CollisionHandler>
inline void setCollisionHandlerInstance(
          const std::shared_ptr<CollisionHandler>& collision_handler_instance )
{
  CollisionModuleInterface<CollisionHandler>::setHandlerInstance(
						  collision_handler_instance );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
