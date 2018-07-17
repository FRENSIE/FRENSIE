//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialComponentParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Material component particle response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"

namespace MonteCarlo{

//! The material component particle response function class
template<typename Material>
class MaterialComponentParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Constructor
  MaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const typename Material::ReactionEnumType reaction );

  //! Destructor
  ~MaterialComponentParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

  //! Get a description of the response function
  std::string description() const override;

protected:

  //! Default Constructor
  MaterialComponentParticleResponseFunction()
  { /* ... */ }

  //! Constructor (do not check reaction type)
  MaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const typename Material::ReactionEnumType reaction,
                       const int );

  //! Return the scattering center
  const typename Material::ScatteringCenterType& getScatteringCenter() const;

  //! Return the scattering center name
  const std::string& getScatteringCenterName() const;

  //! Return the scattering center number density
  double getScatteringCenterNumberDensity() const;

  //! Evaluate the response function at the desired phase space point (impl.)
  double evaluateImpl( const ParticleState& particle ) const;

  //! Create a description of the response function
  template<typename ReactionEnumType>
  std::string createDescription( const ReactionEnumType reaction ) const;

private:

  // Get the material
  const Material& getMaterial() const;

  // Set the material component
  void setMaterialComponent();

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

  // The material component name
  std::string d_material_component_name;

  // The material component
  std::shared_ptr<const typename Material::ScatteringCenterType> d_material_component;

  // The material component number density
  double d_material_component_number_density;
};

//! The neutron material particle response function
typedef MaterialComponentParticleResponseFunction<NeutronMaterial> NeutronMaterialComponentParticleResponseFunction;

//! The electron material particle response function
typedef MaterialComponentParticleResponseFunction<ElectronMaterial> ElectronMaterialComponentParticleResponseFunction;

//! The positron material particle response function
typedef MaterialComponentParticleResponseFunction<PositronMaterial> PositronMaterialComponentParticleResponseFunction;

//! The adjoint photon material particle response function
typedef MaterialComponentParticleResponseFunction<AdjointPhotonMaterial> AdjointPhotonMaterialComponentParticleResponseFunction;

//! The adjoint electron material particle response function
typedef MaterialComponentParticleResponseFunction<AdjointElectronMaterial> AdjointElectronMaterialComponentParticleResponseFunction;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( MaterialComponentParticleResponseFunction, MonteCarlo, 0 );  

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_MaterialComponentParticleResponseFunction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialComponentParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
