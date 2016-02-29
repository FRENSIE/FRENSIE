//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionModuleInterface_Native.hpp
//! \author Alex Robinson
//! \brief  Collision module interface specialization for the native handler
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_MODULE_INTERFACE_NATIVE_HPP
#define MONTE_CARLO_COLLISION_MUDULE_INTERFACE_NATIVE_HPP

// FRENSIE Includes
#include "MonteCarlo_CollisionModuleInterfaceDecl.hpp"
#include "MonteCarlo_CollisionHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"

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

  //! The value of an invalie external material handle
  static const ExternalMaterialHandle invalid_external_material_handle;

  //! Set the collision handler instance
  static void setHandlerInstance(
                  const std::shared_ptr<CollisionHandler>& collision_handler );

  //! Check if a cell is void
  static bool isCellVoid(const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type );

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection( const NeutronState& particle);

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection( const PhotonState& particle);

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection( const ElectronState& particle);

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
					  const NeutronState& particle,
					  const NuclearReactionType reaction );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
				      const PhotonState& particle,
				      const PhotoatomicReactionType reaction );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
				     const PhotonState& particle,
				     const PhotonuclearReactionType reaction );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
				      const ElectronState& particle,
				      const ElectroatomicReactionType reaction );

  //! Sample the optical path length traveled by a particle before a collision
  static double sampleOpticalPathLength();

  //! Collide with the material in a cell
  static void collideWithCellMaterial( NeutronState& particle,
				       ParticleBank& bank,
				       const bool analogue );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( PhotonState& particle,
				       ParticleBank& bank,
				       const bool analogue );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( ElectronState& particle,
				       ParticleBank& bank,
				       const bool analogue );
};

// Set the collision handler instance
/* \detials The MonteCarlo::CollisionHandler is a singleton class
 */ 
inline void 
CollisionModuleInterface<CollisionHandler>::setHandlerInstance(
                   const std::shared_ptr<CollisionHandler>& collision_handler )
{ /* ... */ }

// Check if a cell is void
inline bool CollisionModuleInterface<CollisionHandler>::isCellVoid(
			 const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type )
{
  return CollisionHandler::isCellVoid( cell, particle_type );
}

// Get the total macroscopic cross section of a material
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicTotalCrossSection(
					        const NeutronState& particle )
{
  return CollisionHandler::getMacroscopicTotalCrossSection( particle );
}

// Get the total macroscopic cross section of a material
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicTotalCrossSection(
					   const PhotonState& particle )
{
  return CollisionHandler::getMacroscopicTotalCrossSection( particle );
}

// Get the total macroscopic cross section of a material
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicTotalCrossSection(
					   const ElectronState& particle )
{
  return CollisionHandler::getMacroscopicTotalCrossSection( particle );
}

// Get the macroscopic cross section for a specific reaction
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicReactionCrossSection(
					   const NeutronState& particle,
					   const NuclearReactionType reaction )
{
  return CollisionHandler::getMacroscopicReactionCrossSection( particle,
                                                               reaction );
}

// Get the macroscopic cross section for a specific reaction
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicReactionCrossSection(
				       const PhotonState& particle,
				       const PhotoatomicReactionType reaction )
{
  return CollisionHandler::getMacroscopicReactionCrossSection( particle,
							       reaction );
}

// Get the macroscopic cross section for a specific reaction
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicReactionCrossSection(
				      const PhotonState& particle,
				      const PhotonuclearReactionType reaction )
{
  return CollisionHandler::getMacroscopicReactionCrossSection( particle,
							       reaction );
}

// Get the macroscopic cross section for a specific reaction
inline double 
CollisionModuleInterface<CollisionHandler>::getMacroscopicReactionCrossSection(
				       const ElectronState& particle,
				       const ElectroatomicReactionType reaction )
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
						       NeutronState& particle,
						       ParticleBank& bank,
						       const bool analogue )
{
  CollisionHandler::collideWithCellMaterial( particle,
					     bank,
					     analogue );
}

// Collide with the material in a cell
inline void 
CollisionModuleInterface<CollisionHandler>::collideWithCellMaterial( 
						       PhotonState& particle,
						       ParticleBank& bank,
						       const bool analogue )
{
  CollisionHandler::collideWithCellMaterial( particle,
                                             bank,
                                             analogue );
}

// Collide with the material in a cell
inline void 
CollisionModuleInterface<CollisionHandler>::collideWithCellMaterial( 
						       ElectronState& particle,
						       ParticleBank& bank,
						       const bool analogue )
{
  CollisionHandler::collideWithCellMaterial( particle,
                                             bank,
                                             analogue );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_MODULE_INTERFACE_NATIVE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionModuleInterface_Native.hpp
//---------------------------------------------------------------------------//
