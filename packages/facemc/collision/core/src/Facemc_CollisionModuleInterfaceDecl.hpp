//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CollisionModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Collision module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_COLLISION_MODULE_INTERFACE_DECL_HPP
#define FACEMC_COLLISION_MODULE_INTERFACE_DECL_HPP

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ParticleBank.hpp"

/*! \defgroup collision_module Collision Module
 * \ingroup physics_simulation_modules
 */

namespace Facemc{

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

  //! The value of an invalie external material handle
  static const ExternalMaterialHandle invalid_external_material_handle = 0;

  //! Set the collision handler instance
  static inline void setHandlerInstance(
		      const Teuchos::RCP<CollisionHandler>& collision_handler )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Check if a cell is void
  static inline bool isCellVoid(
			const Geometry::ModuleTraits::InternalCellHandle cell )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Get the total macroscopic cross section of a material
  static inline double getMacroscopicTotalCrossSection(
					        const ParticleState& particle )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Collide with the material in a cell
  static inline void collideWithCellMaterial( ParticleState& particle,
					      ParticleBank& bank,
					      const bool analogue ) 
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }
};

//! Set the collision handler instance
template<typename CollisionHandler>
inline void setCollisionHandlerInstance(
	     const Teuchos::RCP<CollisionHandler>& collision_handler_instance )
{
  CollisionModuleInterface<CollisionHandler>::setHHandlerInstance( 
						  collision_handler_instance );
}

} // end Facemc namespace

#endif // end FACEMC_COLLISION_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end Facemc_CollisionModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
