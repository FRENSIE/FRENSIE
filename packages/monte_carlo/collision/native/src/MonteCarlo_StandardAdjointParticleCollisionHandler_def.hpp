//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleCollisionHandler_def.hpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle collision handler class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_HANDLER_DEF_HPP
#define MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_HANDLER_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename DerivedHandlerTypeTraits>
StandardAdjointParticleCollisionHandler<DerivedHandlerTypeTraits>::StandardAdjointParticleCollisionHandler( const bool analogue_collisions )
  : BaseType( analogue_collisions )
{ /* ... */ }

// Get the total forward macroscopic cross section of a material
template<typename DerivedHandlerTypeTraits>
double StandardAdjointParticleCollisionHandler<DerivedHandlerTypeTraits>::getMacroscopicTotalForwardCrossSection(
        const typename DerivedHandlerTypeTraits::ParticleType& particle ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  return this->getMaterial(particle.getCell())->getMacroscopicTotalForwardCrossSection(
                                                        particle.getEnergy() );
}

// Collide with the material in a cell
/*! \details Before the collision occurs, the particle's weight will be 
 * multiplied by the adjoint weight factor. If the particle's energy 
 * corresponds to a line energy reaction with the material, one of the line
 * energy reactions defined at the energy will be sampled instead of the
 * normal (continuous) reactions.
 */ 
template<typename DerivedHandlerTypeTraits>
void StandardAdjointParticleCollisionHandler<DerivedHandlerTypeTraits>::collideWithCellMaterial(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  bool collision_complete = false;

  // Get the cell material
  const typename DerivedHandlerTypeTraits::MaterialType& material =
      *this->getMaterial( particle.getCell() );

  // Check if a line energy reaction should occur
  if( particle.isProbe() )
  {
    if( material.doesEnergyHaveLineEnergyReaction( particle.getEnergy() ) )
    {
      // Multiply by the adjoint weight factor for this line energy
      particle.multiplyWeight(
             material.getAdjointLineEnergyWeightFactor(particle.getEnergy()) );
      
      material.collideAtLineEnergy( particle, bank );

      collision_complete = true;
    }
  }

  if( !collision_complete )
  {
    // Mutliply the particle weight by the adjoint weight factor
    particle.multiplyWeight(
                       material.getAdjointWeightFactor(particle.getEnergy()) );
    
    BaseType::collideWithCellMaterial( particle, bank );
  }
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleCollisionHandler_def.hpp
//---------------------------------------------------------------------------//
