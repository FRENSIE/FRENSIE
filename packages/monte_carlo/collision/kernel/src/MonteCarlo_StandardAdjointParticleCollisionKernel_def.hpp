//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleCollisionKernel_def.hpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle collision kernel class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_KERNEL_DEF_HPP
#define MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_KERNEL_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Collide with the material in a cell
/*! \details Before the collision occurs, the particle's weight will be
 * multiplied by the adjoint weight factor. If the particle is a probe and
 * its energy corresponds to a line energy reaction, one of the line
 * energy reactions defined at the energy will be sampled instead of the
 * normal (continuous) reactions.
 */
template<typename _FilledGeometryModelType>
void StandardAdjointParticleCollisionKernel<_FilledGeometryModelType>::collideWithCellMaterial(
                                                   ParticleStateType& particle,
                                                   ParticleBank& bank ) const
{
  const MaterialType& cell_material = this->getCellMaterial( particle );

  bool collision_complete = false;

  // Check if a line energy reaction should occur
  if( particle.isProbe() )
  {
    if( cell_material.doesEnergyHaveLineEnergyReaction(particle.getEnergy()) )
    {
      double weight_factor =
        cell_material.getAdjointLineEnergyWeightFactor(particle.getEnergy());

      if ( weight_factor > 0.0 )
      {
        // Multiply the particle weight by the adjoint weight factor for this
        // line energy before the collision
        particle.multiplyWeight( weight_factor );

        cell_material.collideAtLineEnergy( particle, bank );

        collision_complete = true;
      }
      else
        particle.setAsGone();
    }
  }

  if( !collision_complete )
  {
    double weight_factor =
      cell_material.getAdjointWeightFactor( particle.getEnergy() );

    if ( weight_factor > 0.0 )
    {
      // Multiply the particle weight by the adjoint weight factor before the
      // collision
      particle.multiplyWeight( weight_factor );

      BaseType::collideWithCellMaterial( particle, bank );
    }
    else
      particle.setAsGone();
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_KERNEL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleCollisionKernel_def.hpp
//---------------------------------------------------------------------------//
