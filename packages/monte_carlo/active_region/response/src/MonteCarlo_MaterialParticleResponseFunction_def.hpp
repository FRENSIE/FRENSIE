//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialParticleResponseFunction_def.hpp
//! \author Alex Robinson
//! \brief  Material particle response function class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_DEF_HPP
#define MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

//! Constructor (do not check reaction type)
template<typename Material>
MaterialParticleResponseFunction<Material>::MaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const typename Material::ReactionEnumType reaction,
                       const int )
  : d_model( model ),
    d_cell( cell ),
    d_reaction( reaction ),
    d_material()
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );

  // Make sure that the cell of interest is not void
  TEST_FOR_EXCEPTION( model->isCellVoid<typename Material::ParticleStateType>( cell ),
                      std::runtime_error,
                      "There is no material associated with cell "
                      << cell << "!" );

  // Set the material
  this->setMaterial();
}

// Constructor
template<typename Material>
MaterialParticleResponseFunction<Material>::MaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const typename Material::ReactionEnumType reaction )
  : MaterialParticleResponseFunction( model, cell, reaction, 0 )
{
  typename Material::ReactionEnumTypeSet available_reaction_types;

  d_material->getReactionTypes( available_reaction_types );

  // Make sure that the material has cross section data for the reaction type
  // of interest
  TEST_FOR_EXCEPTION( !available_reaction_types.count( reaction ),
                      std::runtime_error,
                      "The material in cell " << cell << " has no cross "
                      "section data available for reaction " << reaction <<
                      "! The following reactions are available: "
                      << available_reaction_types );
}

// Evaluate the response function at the desired phase space point
template<typename Material>
double MaterialParticleResponseFunction<Material>::evaluate( const ParticleState& particle ) const
{
  return this->evaluateImpl( particle );
}

// Evaluate the response function at the desired phase space point
template<typename Material>
inline double MaterialParticleResponseFunction<Material>::evaluateImpl( const ParticleState& particle ) const
{
  // Make sure that the particle type is valid
  testPrecondition( particle.getParticleType() == Material::ParticleStateType::type );
  
  return d_material->getMacroscopicReactionCrossSection( particle.getEnergy(),
                                                         d_reaction );
}

// Check if the response function is spatially uniform
template<typename Material>
bool MaterialParticleResponseFunction<Material>::isSpatiallyUniform() const
{
  return true;
}

// Get a description of the response function
template<typename Material>
std::string MaterialParticleResponseFunction<Material>::description() const
{
  return this->createDescription( d_reaction );
}

// Return the material
template<typename Material>
const Material& MaterialParticleResponseFunction<Material>::getMaterial() const
{
  return *d_material;
}

// Create a description of the response function
template<typename Material>
template<typename ReactionEnumType>
std::string MaterialParticleResponseFunction<Material>::createDescription(
                                        const ReactionEnumType reaction ) const
{
  return std::string("f_cell_") + Utility::toString( d_cell ) + "_mat_\"" +
    Utility::toString( reaction ) + "\"(E)";
}

// Set the material
template<typename Material>
void MaterialParticleResponseFunction<Material>::setMaterial()
{
  const typename Details::FilledGeometryModelUpcastHelper<typename Material::ParticleStateType>::UpcastType& upcast_model = *d_model;

  d_material = upcast_model.getMaterial( d_cell );
}

// Save the data to an archive
template<typename Material>
template<typename Archive>
void MaterialParticleResponseFunction<Material>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_cell );
  ar & BOOST_SERIALIZATION_NVP( d_reaction );
}

// Load the data from an archive
template<typename Material>
template<typename Archive>
void MaterialParticleResponseFunction<Material>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_model );
  ar & BOOST_SERIALIZATION_NVP( d_cell );
  ar & BOOST_SERIALIZATION_NVP( d_reaction );

  // Set the material
  this->setMaterial();
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( NeutronMaterialParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ElectronMaterialParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PositronMaterialParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointPhotonMaterialParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointElectronMaterialParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

#endif // end MONTE_CARLO_MATERIAL_PARTICLE_RESPONSE_FUNCTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialParticleResponseFunction_def.hpp
//---------------------------------------------------------------------------//
