//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleCollisionKernel.hpp
//! \author Alex Robinson
//! \brief  The standard particle collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_COLLISION_KERNEL_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_COLLISION_KERNEL_HPP

// Std Lib Includes
#include <unordered_map>
#include <functional>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The standard particle collision kernel class
template<typename _FilledGeometryModelType>
class StandardParticleCollisionKernel
{
  // Typedef for this type
  typedef StandardParticleCollisionKernel<_FilledGeometryModelType> ThisType;

public:

  //! Typedef for the filled geometry model type
  typedef _FilledGeometryModelType FilledGeometryModelType;

  //! Typedef for the material type
  typedef typename FilledGeometryModelType::MaterialType MaterialType;
  
  //! Typedef for the reaction enum type
  typedef typename FilledGeometryModelType::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef typename FilledGeometryModelType::ParticleStateType ParticleStateType;

  //! Constructor
  StandardParticleCollisionKernel(
                          const std::shared_ptr<const FilledGeometryModelType>&
                          filled_geometry_model,
                          const bool analogue_collisions = true );

  //! Destructor
  virtual ~StandardParticleCollisionKernel()
  { /* ... */ }

  //! Collide with the material in a cell
  virtual void collideWithCellMaterial( ParticleStateType& particle,
                                        ParticleBank& bank ) const;

protected:

  //! Get the cell material
  const MaterialType& getCellMaterial( const ParticleStateType& particle ) const;

private:

  //! Collide with the material in a cell (analogue)
  void collideWithCellMaterialAnalogue( ParticleStateType& particle,
                                        ParticleBank& bank ) const;

  //! Collide with the material in a cell (survival bias)
  void collideWithCellMaterialSurvivalBias( ParticleStateType& particle,
                                            ParticleBank& bank ) const;

  // The filled geometry model
  std::shared_ptr<const FilledGeometryModelType> d_filled_geometry_model;

  // The collision method function pointer
  std::function<void(ParticleStateType&,ParticleBank&)>
  d_collision_method;

  
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardParticleCollisionKernel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PARTICLE_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleCollisionKernel.hpp
//---------------------------------------------------------------------------//
