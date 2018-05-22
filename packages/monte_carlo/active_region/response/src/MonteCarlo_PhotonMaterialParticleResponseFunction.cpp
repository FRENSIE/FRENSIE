//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterialParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Photon material particle response function class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonMaterialParticleResponseFunction.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor (photoatomic reaction)
PhotonMaterialParticleResponseFunction::PhotonMaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::InternalCellHandle cell,
                       const PhotoatomicReactionType reaction )
  : BaseType( model, cell, reaction ),
    d_use_photonuclear_reaction_type( false ),
    d_photonuclear_reaction( GAMMA__TOTAL_REACTION ),
    d_evaluation_method( std::bind<double>( &BaseType::evaluate,
                                            std::cref( *this ),
                                            std::placeholders::_1 ) )
{ /* ... */ }

// Constructor (photonuclear reaction)
PhotonMaterialParticleResponseFunction::PhotonMaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::InternalCellHandle cell,
                       const PhotonuclearReactionType reaction )
  : BaseType( model, cell, TOTAL_PHOTOATOMIC_REACTION, 0 ),
    d_use_photonuclear_reaction_type( true ),
    d_photonuclear_reaction( reaction ),
    d_evaluation_method( std::bind<double>( &PhotonMaterialParticleResponseFunction::evaluate,
                                            std::cref( *this ),
                                            std::placeholders::_1 ) )
{
  typename PhotonMaterial::PhotonuclearReactionEnumTypeSet
    available_reaction_types;

  this->getMaterial().getReactionTypes( available_reaction_types );

  // Make sure that the material has cross section data for the reaction type
  // of interest
  TEST_FOR_EXCEPTION( !available_reaction_types.count( reaction ),
                      std::runtime_error,
                      "The photon material in cell " << cell << " has no "
                      "cross section data available for reaction "
                      << reaction << "! The following reactions are "
                      "available: " << available_reaction_types );
}

// Evaluate the response function at the desired phase space point
double PhotonMaterialParticleResponseFunction::evaluate(
                                          const ParticleState& particle ) const
{
  return d_evaluation_method( particle );
}

// Get a description of the response function
std::string PhotonMaterialParticleResponseFunction::description() const
{
  if( d_use_photonuclear_reaction_type )
    return this->createDescription( d_photonuclear_reaction );
  else
    return BaseType::description();
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterialParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
