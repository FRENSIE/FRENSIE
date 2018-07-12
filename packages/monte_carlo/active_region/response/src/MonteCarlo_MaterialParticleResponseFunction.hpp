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

  //! Constructor
  MaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const typename Material::ReactionEnumType reaction );

  //! Destructor
  ~MaterialParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

  //! Get a description of the response function
  std::string description() const override;

protected:

  //! Default Constructor
  MaterialParticleResponseFunction()
  { /* ... */ }

  //! Constructor (do not check reaction type)
  MaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const typename Material::ReactionEnumType reaction,
                       const int );

  //! Return the material
  const Material& getMaterial() const;

  //! Evaluate the response function at the desired phase space point (impl.)
  double evaluateImpl( const ParticleState& particle ) const;

  //! Create a description of the response function
  template<typename ReactionEnumType>
  std::string createDescription( const ReactionEnumType reaction ) const;
  
private:

  // Set the material
  void setMaterial();

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The filled geometry model
  std::shared_ptr<const FilledGeometryModel> d_model;

  // The cell that contains the material
  Geometry::Model::EntityId d_cell;

  // The reaction
  typename Material::ReactionEnumType d_reaction;

  // The material
  std::shared_ptr<const Material> d_material;
};

//! The neutron material particle response function
typedef MaterialParticleResponseFunction<NeutronMaterial> NeutronMaterialParticleResponseFunction;

//! The electron material particle response function
typedef MaterialParticleResponseFunction<ElectronMaterial> ElectronMaterialParticleResponseFunction;

//! The positron material particle response function
typedef MaterialParticleResponseFunction<PositronMaterial> PositronMaterialParticleResponseFunction;

//! The adjoint photon material particle response function
typedef MaterialParticleResponseFunction<AdjointPhotonMaterial> AdjointPhotonMaterialParticleResponseFunction;

//! The adjoint electron material particle response function
typedef MaterialParticleResponseFunction<AdjointElectronMaterial> AdjointElectronMaterialParticleResponseFunction;
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( MaterialParticleResponseFunction, MonteCarlo, 0 );  

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_MaterialParticleResponseFunction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
