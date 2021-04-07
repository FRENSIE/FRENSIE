//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterialComponentParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Photon material component particle response function class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_PhotonMaterialComponentParticleResponseFunction.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor (photoatomic reaction)
PhotonMaterialComponentParticleResponseFunction::PhotonMaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const PhotoatomicReactionType reaction )
  : BaseType( model, cell, component_name, reaction ),
    d_use_photonuclear_reaction_type( false ),
    d_photonuclear_reaction( GAMMA__TOTAL_REACTION ),
    d_evaluation_method()
{
  this->setEvaluationMethod();
}

// Constructor (photonuclear reaction)
PhotonMaterialComponentParticleResponseFunction::PhotonMaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const PhotonuclearReactionType reaction )
  : BaseType( model, cell, component_name, TOTAL_PHOTOATOMIC_REACTION, 0 ),
    d_use_photonuclear_reaction_type( true ),
    d_photonuclear_reaction( reaction ),
    d_evaluation_method()
{
  typename PhotonMaterial::PhotonuclearReactionEnumTypeSet
    available_reaction_types;

  this->getScatteringCenter().getReactionTypes( available_reaction_types );

  // Make sure that the scattering center has cross section data for the
  // reaction type of interest
  TEST_FOR_EXCEPTION( !available_reaction_types.count( reaction ),
                      std::runtime_error,
                      "The photon material component "
                      << this->getScatteringCenterName() << " of the material "
                      "in cell " << cell << " has no cross section data "
                      "available for reaction " << reaction << "! The "
                      "following reactions are available: "
                      << available_reaction_types );

  this->setEvaluationMethod();
}

// Evaluate the response function at the desired phase space point
double PhotonMaterialComponentParticleResponseFunction::evaluate(
                                          const ParticleState& particle ) const
{
  return d_evaluation_method( particle );
}

// Evaluate the photonuclear reaction cross section
double PhotonMaterialComponentParticleResponseFunction::evaluatePhotonuclearReactionCrossSection( const ParticleState& particle ) const
{
  // Make sure that the particle type is valid
  testPrecondition( particle.getParticleType() == PHOTON );

  return this->getScatteringCenterNumberDensity()*
    this->getScatteringCenter().getReactionCrossSection( particle.getEnergy(),
                                                         d_photonuclear_reaction );
}

// Get a description of the response function
std::string PhotonMaterialComponentParticleResponseFunction::description() const
{
  if( d_use_photonuclear_reaction_type )
    return this->createDescription( d_photonuclear_reaction );
  else
    return BaseType::description();
}

// Set the evaluation method
void PhotonMaterialComponentParticleResponseFunction::setEvaluationMethod()
{
  if( d_use_photonuclear_reaction_type )
  {
    d_evaluation_method =
      std::bind<double>( &PhotonMaterialComponentParticleResponseFunction::evaluatePhotonuclearReactionCrossSection,
                         std::cref( *this ),
                         std::placeholders::_1 );
  }
  else
  {
    d_evaluation_method = std::bind<double>( &PhotonMaterialComponentParticleResponseFunction::evaluateImpl,
                                             std::cref( *this ),
                                             std::placeholders::_1 );
  }
}

EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::PhotonMaterialComponentParticleResponseFunction );
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( PhotonMaterialComponentParticleResponseFunction, MonteCarlo );

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterialComponentParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
