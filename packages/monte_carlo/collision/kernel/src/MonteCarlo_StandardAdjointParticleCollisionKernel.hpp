//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleCollisionKernel.hpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_KERNEL_HPP
#define MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleCollisionKernel.hpp"

namespace MonteCarlo{

//! The standard adjoint particle collision kernel class
template<typename _FilledGeometryModelType>
class StandardAdjointParticleCollisionKernel : public StandardParticleCollisionKernel<_FilledGeometryModelType>
{
  // Typedef for base type
  typedef StandardParticleCollisionKernel<_FilledGeometryModelType> BaseType;
  
  // Typedef for this type
  typedef StandardAdjointParticleCollisionKernel<_FilledGeometryModelType> ThisType;

public:

  //! Typedef for the filled geometry model type
  typedef typename BaseType::FilledGeometryModelType FilledGeometryModelType;

  //! Typedef for the material type
  typedef typename BaseType::MaterialType MaterialType;

  //! Typedef for the reaction enum type
  typedef typename BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef typename BaseType::ParticleStateType ParticleStateType;

  //! Constructor
  using StandardParticleCollisionKernel<_FilledGeometryModelType>::StandardParticleCollisionKernel;  
  
  //! Destructor
  virtual ~StandardAdjointParticleCollisionKernel()
  { /* ... */ }

  //! Collide with the material in a cell
  void collideWithCellMaterial( ParticleStateType& particle,
                                ParticleBank& bank ) const final override;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardAdjointParticleCollisionKernel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleCollisionKernel.hpp
//---------------------------------------------------------------------------//
