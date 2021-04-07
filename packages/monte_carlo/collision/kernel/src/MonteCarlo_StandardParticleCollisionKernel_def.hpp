//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleCollisionKernel_def.hpp
//! \author Alex Robinson
//! \brief  The standard particle collision kernel class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_COLLISION_KERNEL_DEF_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_COLLISION_KERNEL_DEF_HPP

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename _FilledGeometryModelType>
StandardParticleCollisionKernel<_FilledGeometryModelType>::StandardParticleCollisionKernel(
                          const std::shared_ptr<const FilledGeometryModelType>&
                          filled_geometry_model,
                          const bool analogue_collisions )
  : d_filled_geometry_model( filled_geometry_model ),
    d_collision_method()
{
  // Make sure that the geometry model is valid
  testPrecondition( d_filled_geometry_model.get() );
  
  // Assign the collision method
  if( analogue_collisions )
  {
    d_collision_method = std::bind<void>(
                                    &ThisType::collideWithCellMaterialAnalogue,
                                    std::cref( *this ),
                                    std::placeholders::_1,
                                    std::placeholders::_2 );
  }
  else
  {
    d_collision_method = std::bind<void>(
                                &ThisType::collideWithCellMaterialSurvivalBias,
                                std::cref( *this ),
                                std::placeholders::_1,
                                std::placeholders::_2 );
  }
}

// Get the cell material
template<typename _FilledGeometryModelType>
auto StandardParticleCollisionKernel<_FilledGeometryModelType>::getCellMaterial( const ParticleStateType& particle ) const -> const MaterialType&
{
  // Make sure the cell is not void
  testPrecondition( !d_filled_geometry_model->isCellVoid( particle.getCell() ) );

  return *d_filled_geometry_model->getMaterial( particle.getCell() );
}

// Collide with the material in a cell
template<typename _FilledGeometryModelType>
void StandardParticleCollisionKernel<_FilledGeometryModelType>::collideWithCellMaterial(
                                                   ParticleStateType& particle,
                                                   ParticleBank& bank ) const
{
  d_collision_method( particle, bank );
}

// Collide with the material in a cell (analogue)
template<typename _FilledGeometryModelType>
void StandardParticleCollisionKernel<_FilledGeometryModelType>::collideWithCellMaterialAnalogue(
                                                   ParticleStateType& particle,
                                                   ParticleBank& bank ) const
{
  this->getCellMaterial( particle ).collideAnalogue( particle, bank );
}

// Collide with the material in a cell (survival bias)
template<typename _FilledGeometryModelType>
void StandardParticleCollisionKernel<_FilledGeometryModelType>::collideWithCellMaterialSurvivalBias(
                                                   ParticleStateType& particle,
                                                   ParticleBank& bank ) const
{
  this->getCellMaterial( particle ).collideSurvivalBias( particle, bank );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_COLLISION_KERNEL_DEF_HPP


//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleCollisionKernel_def.hpp
//---------------------------------------------------------------------------//
