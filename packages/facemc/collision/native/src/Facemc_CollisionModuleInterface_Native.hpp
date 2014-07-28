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
#include "Utility_RandomNumberGenerator.hpp"

namespace Facemc{

/*! Native handler specialization of the collision module interface class
 * \ingroup collision_module
 */
template<>
class CollisionModuleInterface<CollisionHandler>
{
  
public:
  
  //! The external material handle class (used within the collision handler)
  typedef ModuleTraits::InternalMaterialHandle ExternalMaterialHandle;

  //! The internal material handle class (used within FRENSIE)
  typedef ModuleTraits::InternalMaterialHandle InternalMaterialHandle;

  //! The value of an invalie external material handle
  static const ExternalMaterialHandle invalid_external_material_handle;

  //! Set the collision handler instance
  static void setHandlerInstance(
	             const Teuchos::RCP<CollisionHandler>& collision_handler );

  //! Check if a cell is void
  static bool isCellVoid(
		       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection(
					       const ParticleState& particle );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
					  const ParticleState& particle,
					  const NuclearReactionType reaction );

  //! Sample the optical path length traveled by a particle before a collision
  static double sampleOpticalPathLength();

  //! Collide with the material in a cell
  static void collideWithCellMaterial( ParticleState& particle,
				       ParticleBank& bank,
				       const bool analogue );
};


// Initialize static member data
const CollisionModuleInterface<CollisionHandler>::ExternalMaterialHandle 
CollisionModuleInterface<CollisionHandler>::invalid_external_material_handle = 
  ModuleTraits::invalid_internal_material_handle;

// Set the collision handler instance
/* \detials The Facemc::CollisionHandler is a singleton class
 */ 
inline void 
CollisionModuleInterface<CollisionHandler>::setHandlerInstance(
	      const Teuchos::RCP<CollisionHandler>& collision_handler )
{ /* ... */ }

// Check if a cell is void
inline bool CollisionModuleInterface<CollisionHandler>::isCellVoid(
		        const Geometry::ModuleTraits::InternalCellHandle cell )
{
  return CollisionHandler::isCellVoid( cell );
}

// Get the total macroscopic cross section of a material
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicTotalCrossSection(
					        const ParticleState& particle )
{
  return CollisionHandler::getMacroscopicTotalCrossSection( particle );
}

//! Get the macroscopic cross section for a specific reaction
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicReactionCrossSection(
					   const ParticleState& particle,
					   const NuclearReactionType reaction )
{
  return CollisionHandler::getMacroscopicReactionCrossSection( particle,
							       reaction );
}

// Sample the optical path length traveled by a particle before a collision
inline double 
CollisionModuleInterface<CollisionHandler>::sampleOpticalPathLength()
{
  return -log( Utility::RandomNumberGenerator::getRandomNumber<double>() );
}

// Collide with the material in a cell
inline void 
CollisionModuleInterface<CollisionHandler>::collideWithCellMaterial( 
						       ParticleState& particle,
						       ParticleBank& bank,
						       const bool analogue )
{
  CollisionHandler::collideWithCellMaterial( particle,
					     bank,
					     analogue );
}

} // end Facemc namespace

#endif // end FACEMC_COLLISION_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end Facemc_CollisionModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
