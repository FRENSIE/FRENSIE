//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CollisionModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Collision module interface specialization for the native hander
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_COLLISION_MODULE_INTERFACE_NATIVE_HPP
#define FACEMC_COLLISION_MUDULE_INTERFACE_NATIVE_HPP

// FRENSIE Includes
#include "Facemc_CollisionModuleInterfaceDecl.hpp"
#include "Facemc_CollisionHandler.hpp"

/*! Native handler specialization of the collision module interface class
 * \ingroup collision_module
 */
template<>
class CollisionModuleInterface<Facemc::CollisionHandler>
{
  //! The external material handle class (used within the collision handler)
  typedef ModuleTraits::InternalMaterialHandle ExternalMaterialHandle;

  //! The internal material handle class (used within FRENSIE)
  typedef ModuleTraits::InternalMaterialHandle InternalMaterialHandle;

  //! The value of an invalie external material handle
  static const ExternalMaterialHandle invalid_external_material_handle = 
    ModuleTraits::invalid_internal_material_handle;

  //! Set the collision handler instance
  static void setHandlerInstance(
	     const Teuchos::RCP<Facemc::CollisionHandler>& collision_handler );

  //! Check if a cell is void
  static bool isCellVoid(
		       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection(
					       const ParticleState& particle );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( ParticleState& particle,
				       ParticleBank& bank,
				       const bool analogue );
};

// Set the collision handler instance
/* \detials The Facemc::CollisionHandler is a singleton class
 */ 
inline void 
CollisionModuleInterface<Facemc::CollisionHandler>::setHandlerInstance(
	      const Teuchos::RCP<Facemc::CollisionHandler>& collision_handler )
{ /* ... */ }

// Check if a cell is void
inline bool CollisionModuleInterface<Facemc::CollisionHandler>::isCellVoid(
		        const Geometry::ModuleTraits::InternalCellHandle cell )
{
  return Facemc::CollisionHandler::isCellVoid( cell );
}

// Get the total macroscopic cross section of a material
inline double 
CollisionModuleInterface<Facemc::CollisionHandler>::getMacroscopicTotalCrossSection(
					        const ParticleState& particle )
{
  return Facemc::CollisionHandler::getMacroscopicTotalCrossSection( particle );
}

// Collide with the material in a cell
inline void 
CollisionModuleInterface<Facemc::CollisionHandler>::collideWithCellMaterial( 
						       ParticleState& particle,
						       ParticleBank& bank,
						       const bool analogue )
{
  return Facemc::CollisionHandler::collideWithCellMaterial( particle,
							    bank,
							    analogue );
}

#endif // end FACEMC_COLLISION_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end Facemc_CollisionModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
