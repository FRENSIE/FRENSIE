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
template<typename Material>
class StandardAdjointParticleCollisionHandler : public StandardParticleCollisionHandler<Material>
{
  // Typedef for base type
  typedef StandardParticleCollisionHandler<Material> BaseType;
  
  // Typedef for this type
  typedef StandardAdjointParticleCollisionHandler<Material> ThisType;

public:

  //! Typedef for the material type
  typedef typename BaseType::MaterialType MaterialType;

  //! Typedef for the reaction enum type
  typedef typename BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef typename BaseType::ParticleStateType ParticleStateType;

  //! Constructor
  StandardAdjointParticleCollisionHandler(
                                       const bool analogue_collisions = true );

  //! Destructor
  virtual ~StandardAdjointParticleCollisionHandler()
  { /* ... */ }

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const final override;

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const final override;

  //! Get the adjoint weight factor
  double getAdjointWeightFactor( const ParticleStateType& particle ) const;

  //! Get the adjoint weight factor
  double getAdjointWeightFactor(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const;

  //! Get the adjoint weight factor
  double getAdjointWeightFactorQuick( const ParticleStateType& particle ) const;

  //! Get the adjoint weight factor
  double getAdjointWeightFactorQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const;
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
