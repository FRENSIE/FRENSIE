//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialComponentParticleResponseFunction_def.hpp
//! \author Alex Robinson
//! \brief  Material component particle response function class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_DEF_HPP
#define MONTE_CARLO_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor (do not check reaction type)
template<typename Material>
MaterialComponentParticleResponseFunction<Material>::MaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const typename Material::ReactionEnumType reaction,
                       const int )
  : d_model( model ),
    d_cell( cell ),
    d_reaction( reaction ),
    d_material_component_name( component_name ),
    d_material_component(),
    d_material_component_number_density()
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );

  // Make sure that the cell of interest is not valid
  TEST_FOR_EXCEPTION( model->isCellVoid<typename Material::ParticleStateType>( cell ),
                      std::runtime_error,
                      "There is no material associated with cell "
                      << cell << "!" );

  // Set the material component
  this->setMaterialComponent();
}

// Constructor
template<typename Material>
MaterialComponentParticleResponseFunction<Material>::MaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const typename Material::ReactionEnumType reaction )
  : MaterialComponentParticleResponseFunction( model,
                                               cell,
                                               component_name,
                                               reaction,
                                               0 )
{
  typename Material::ReactionEnumTypeSet available_reaction_types;

  d_material_component->getReactionTypes( available_reaction_types );

  // Make sure that the material component has cross section data for the
  // reaction type of interest
  TEST_FOR_EXCEPTION( !available_reaction_types.count( reaction ),
                      std::runtime_error,
                      "The material component " << d_material_component_name <<
                      " of the material in cell " << cell << " has no cross "
                      "section data available for reaction "
                      << reaction << "! The following reactions are "
                      "available: " << available_reaction_types );
}

// Evaluate the response function at the desired phase space point
template<typename Material>
double MaterialComponentParticleResponseFunction<Material>::evaluate(
                                          const ParticleState& particle ) const
{
  return this->evaluateImpl( particle );
}

// Evaluate the response function at the desired phase space point (impl.)
template<typename Material>
double MaterialComponentParticleResponseFunction<Material>::evaluateImpl(
                                          const ParticleState& particle ) const
{
  // Make sure that the particle type is valid
  testPrecondition( particle.getParticleType() == Material::ParticleStateType::type );

  return d_material_component_number_density*d_material_component->getReactionCrossSection( particle.getEnergy(), d_reaction );
}

// Check if the response function is spatially uniform
template<typename Material>
bool MaterialComponentParticleResponseFunction<Material>::isSpatiallyUniform() const
{
  return true;
}

// Get a description of the response function
template<typename Material>
std::string MaterialComponentParticleResponseFunction<Material>::description() const
{
  return this->createDescription( d_reaction );
}

// Return the scattering center
template<typename Material>
const typename Material::ScatteringCenterType& MaterialComponentParticleResponseFunction<Material>::getScatteringCenter() const
{
  return *d_material_component;
}

// Return the scattering center
template<typename Material>
const std::string& MaterialComponentParticleResponseFunction<Material>::getScatteringCenterName() const
{
  return d_material_component_name;
}

// Return the scattering center number density
template<typename Material>
double MaterialComponentParticleResponseFunction<Material>::getScatteringCenterNumberDensity() const
{
  return d_material_component_number_density;
}

// Create a description of the response function
template<typename Material>
template<typename ReactionEnumType>
std::string MaterialComponentParticleResponseFunction<Material>::createDescription( const ReactionEnumType reaction ) const
{
  return std::string("f_cell_") + Utility::toString( d_cell ) +
    "_mat_component_" + "\"" + d_material_component_name + "\"_\"" +
    Utility::toString( reaction ) + "\"(E)";
}

// Get the material
template<typename Material>
inline const Material& MaterialComponentParticleResponseFunction<Material>::getMaterial() const
{
  return *dynamic_cast<const typename Details::FilledGeometryModelUpcastHelper<typename Material::ParticleStateType>::UpcastType&>( *d_model ).getMaterial( d_cell );
}

// Set the material
template<typename Material>
void MaterialComponentParticleResponseFunction<Material>::setMaterialComponent()
{
  // Get the material
  const Material& material = this->getMaterial();

  // Get the scattering center data
  try{
    d_material_component =
      material.getScatteringCenter( d_material_component_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Material component "
                           << d_material_component_name <<
                           " does not exist!" );

  d_material_component_number_density =
    material.getScatteringCenterNumberDensity( d_material_component_name );
}

// Save the data to an archive
template<typename Material>
template<typename Archive>
void MaterialComponentParticleResponseFunction<Material>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_cell );
  ar & BOOST_SERIALIZATION_NVP( d_reaction );
  ar & BOOST_SERIALIZATION_NVP( d_material_component_name );
}

// Load the data from an archive
template<typename Material>
template<typename Archive>
void MaterialComponentParticleResponseFunction<Material>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_cell );
  ar & BOOST_SERIALIZATION_NVP( d_reaction );
  ar & BOOST_SERIALIZATION_NVP( d_material_component_name );

  // Set the material component
  this->setMaterialComponent();
}
 
} // end MonteCarlo

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( NeutronMaterialComponentParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialComponentParticleResponseFunction<MonteCarlo::NeutronMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ElectronMaterialComponentParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialComponentParticleResponseFunction<MonteCarlo::ElectronMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PositronMaterialComponentParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialComponentParticleResponseFunction<MonteCarlo::PositronMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointPhotonMaterialComponentParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialComponentParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointElectronMaterialComponentParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialComponentParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

#endif // end MONTE_CARLO_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialComponentParticleResponseFunction_def.hpp
//---------------------------------------------------------------------------//
