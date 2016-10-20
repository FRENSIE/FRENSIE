//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAdjointParticleCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  The standard adjoint particle collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_HANDLER_HPP
#define MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The standard adjoint particle collision handler class
template<typename DerivedHandlerTypeTraits>
class StandardAdjointParticleCollisionHandler : public StandardParticleCollisionHandler<DerivedHandlerTypeTraits>
{

private:

  // Typedef for this type
  typedef StandardAdjointParticleCollisionHandler<DerivedHandlerTypeTraits> ThisType;

  // Typedef for base type
  typedef StandardParticleCollisionHandler<DerivedHandlerTypeTraits> BaseType;

public:

  //! Constructor
  StandardAdjointParticleCollisionHandler(
                                       const bool analogue_collisions = true );

  //! Destructor
  virtual ~StandardAdjointParticleCollisionHandler()
  { /* ... */ }

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSection(
       const typename DerivedHandlerTypeTraits::ParticleType& particle ) const;

  //! Collide with the material in a cell
  void collideWithCellMaterial(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardAdjointParticleCollisionHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ADJOINT_PARTICLE_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAdjointParticleCollisionHandler.hpp
//---------------------------------------------------------------------------//
