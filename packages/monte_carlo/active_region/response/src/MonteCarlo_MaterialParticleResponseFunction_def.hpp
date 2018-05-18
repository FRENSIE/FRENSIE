//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialParticleResponseFunction_def.hpp
//! \author Alex Robinson
//! \brief  Material particle response function class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The filled geometry model constructor
template<typename Material>
MaterialParticleResponseFunction<Material>::MaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::InternalCellHandle cell,
                       const typename Material::ReactionEnumType reaction )
  : d_model( model ),
    d_material(),
    d_reaction( reaction )
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );
  
  TEST_FOR_EXCEPTION( model->isCellVoid<typename Material::ParticleStateType>( cell ),
                      std::runtime_error,
                      "There is no material associated with cell "
                      << cell << "!" );
  
  const typename Details::FilledGeometryModelUpcastHelper<typename Material::ParticleStateType>::UpcastType& upcast_model = *model;

  d_material = upcast_model.getMaterial( cell );
}

// Evaluate the response function at the desired phase space point
template<typename Material>
double MaterialParticleResponseFunction<Material>::evaluate( const ParticleState& particle ) const
{
  return d_material->getMacroscopicReactionCrossSection( particle.getEnergy(),
                                                         d_reaction );
}

// Check if the response function is spatially uniform
template<typename Material>
bool MaterialParticleResponseFunction<Material>::isSpatiallyUniform() const
{
  return true;
}
  
} // end MonteCarlo namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::NeutronMaterial> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PhotonMaterial> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::ElectronMaterial> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::PositronMaterial> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointPhotonMaterial> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MaterialParticleResponseFunction<MonteCarlo::AdjointElectronMaterial> );

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialParticleResponseFunction_def.hpp
//---------------------------------------------------------------------------//
