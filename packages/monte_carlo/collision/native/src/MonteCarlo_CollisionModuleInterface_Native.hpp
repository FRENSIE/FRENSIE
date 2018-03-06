//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Collision module interface specialization for the native handler
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_MODULE_INTERFACE_NATIVE_HPP
#define MONTE_CARLO_COLLISION_MODULE_INTERFACE_NATIVE_HPP

// FRENSIE Includes
#include "MonteCarlo_CollisionModuleInterfaceDecl.hpp"
#include "MonteCarlo_CollisionHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"

namespace MonteCarlo{

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

  //! The value of an invalid external material handle
  static const ExternalMaterialHandle invalid_external_material_handle;

  //! Set the collision handler instance
  static void setHandlerInstance(
                  const std::shared_ptr<CollisionHandler>& collision_handler );

  //! Check if a cell is void
  static bool isCellVoid(const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type );

  //! Get the total macroscopic cross section of a material
  template<typename ParticleStateType>
  static double getMacroscopicTotalCrossSection( const ParticleStateType& particle );

   //! Get the total forward macroscopic cross section of a material
  template<typename ParticleStateType>
  static double getMacroscopicTotalForwardCrossSection( const ParticleStateType& particle );

  //! Sample the optical path length traveled by a particle before a collision
  static double sampleOpticalPathLength();

  //! Collide with the material in a cell
  template<typename ParticleStateType>
  static void collideWithCellMaterial( ParticleStateType& particle,
				       ParticleBank& bank );

private:

  // The collision handler instance
  static std::shared_ptr<CollisionHandler> s_collision_handler;
};

// Set the collision handler instance
/* \detials The MonteCarlo::CollisionHandler is a singleton class
 */
inline void
CollisionModuleInterface<CollisionHandler>::setHandlerInstance(
                   const std::shared_ptr<CollisionHandler>& collision_handler )
{
  // Make sure the collision handler is valid
  testPrecondition( collision_handler.get() );

  s_collision_handler = collision_handler;
}

// Check if a cell is void
inline bool CollisionModuleInterface<CollisionHandler>::isCellVoid(
			 const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type )
{
  return s_collision_handler->isCellVoid( cell, particle_type );
}

// Get the total macroscopic cross section of a material
template<typename ParticleStateType>
inline double
CollisionModuleInterface<CollisionHandler>::getMacroscopicTotalCrossSection(
                                            const ParticleStateType& particle )
{
  return s_collision_handler->getMacroscopicTotalCrossSection( particle );
}

// Get the total forward macroscopic cross section of a material
template<typename ParticleStateType>
inline double
CollisionModuleInterface<CollisionHandler>::getMacroscopicTotalForwardCrossSection(
                                            const ParticleStateType& particle )
{
  return s_collision_handler->getMacroscopicTotalForwardCrossSection( particle );
}

// Sample the optical path length traveled by a particle before a collision
inline double
CollisionModuleInterface<CollisionHandler>::sampleOpticalPathLength()
{
  return -log( Utility::RandomNumberGenerator::getRandomNumber<double>() );
}

// Collide with the material in a cell
template<typename ParticleStateType>
inline void
CollisionModuleInterface<CollisionHandler>::collideWithCellMaterial(
                                                   ParticleStateType& particle,
                                                   ParticleBank& bank )
{
  s_collision_handler->collideWithCellMaterial( particle, bank );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
