//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Material particle response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"

namespace MonteCarlo{

//! The material particle response function class
template<typename Material>
class MaterialParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! The filled geometry model constructor
  MaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::InternalCellHandle cell,
                       const typename Material::ReactionEnumType reaction );

  //! Destructor
  ~MaterialParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

private:

  // Constructor
  MaterialParticleResponseFunction()
  { /* ... */ }

  // The filled geometry model
  std::shared_ptr<const FilledGeometryModel> d_model;

  // The material
  std::shared_ptr<const Material> d_material;

  // The reaction
  typename Material::ReactionEnumType d_reaction;
};

//! The neutron material particle response function
typedef MaterialParticleResponseFunction<NeutronMaterial> NeutronMaterialParticleResponseFunction;

//! The photon material particle response function
typedef MaterialParticleResponseFunction<PhotonMaterial> PhotonMaterialParticleResponseFunction;

//! The electron material particle response function
typedef MaterialParticleResponseFunction<ElectronMaterial> ElectronMaterialParticleResponseFunction;

//! The positron material particle response function
typedef MaterialParticleResponseFunction<PositronMaterial> PositronMaterialParticleResponseFunction;

//! The adjoint photon material particle response function
typedef MaterialParticleResponseFunction<AdjointPhotonMaterial> AdjointPhotonMaterialParticleResponseFunction;

//! The adjoint electron material particle response function
typedef MaterialParticleResponseFunction<AdjointElectronMaterial> AdjointElectronMaterialParticleResponseFunction;
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_MaterialParticleResponseFunction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
