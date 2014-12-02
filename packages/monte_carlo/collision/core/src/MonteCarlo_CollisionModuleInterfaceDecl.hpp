//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionModuleInterfaceDecl.hpp
//! \author Alex Robinson
//! \brief  Collision module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_MODULE_INTERFACE_DECL_HPP
#define MONTE_CARLO_COLLISION_MODULE_INTERFACE_DECL_HPP

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"

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

  //! The value of an invalie external material handle
  static const ExternalMaterialHandle invalid_external_material_handle = 0;

  //! Set the collision handler instance
  static inline void setHandlerInstance(
		      const Teuchos::RCP<CollisionHandler>& collision_handler )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Check if a cell is void
  static inline bool isCellVoid(
			 const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Get the total macroscopic cross section of a material
  static inline double getMacroscopicTotalCrossSection(
						 const NeutronState& particle )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}

  //! Get the total macroscopic cross section of a material
  static inline double getMacroscopicTotalCrossSection(
						 const PhotonState& particle )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); return 0;}
  
  //! Get the macroscopic cross section for a specific reaction
  static inline double getMacroscopicReactionCrossSection(
					   const NeutronState& particle,
					   const NuclearReactionType reaction )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Get the macroscopic cross section for a specific reaction
  static inline double getMacroscopicReactionCrossSection(
				       const PhotonState& particle,
				       const PhotoatomicReactionType reaction )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Get the macroscopic cross section for a specific reaction
  static inline double getMacroscopicReactionCrossSection(
				      const PhotonState& particle,
				      const PhotonuclearReactionType reaction )
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Sample the optical path length traveled by a particle before a collision
  static inline double sampleOpticalPathLength()
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Collide with the material in a cell
  static inline void collideWithCellMaterial( NeutronState& particle,
					      ParticleBank& bank,
					      const bool analogue ) 
  { (void)UndefinedCollisionHandler<CollisionHandler>::notDefined(); }

  //! Collide with the material in a cell
  static inline void collideWithCellMaterial( PhotonState& particle,
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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//
