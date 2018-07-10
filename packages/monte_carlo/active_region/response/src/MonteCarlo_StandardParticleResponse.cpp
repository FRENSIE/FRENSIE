//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleResponse.cpp
//! \author Alex Robinson
//! \brief  The standard particle response class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardParticleResponse.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
StandardParticleResponse::StandardParticleResponse(
    const std::string& name,
    const std::shared_ptr<const ParticleResponseFunction>& response_function )
  : ParticleResponse( name ),
    d_response_function( response_function )
{
  // Make sure that the response function pointer is valid
  testPrecondition( response_function.get() );
}

// Constructor
StandardParticleResponse::StandardParticleResponse(
     const std::shared_ptr<const ParticleResponseFunction>& response_function )
  : StandardParticleResponse( response_function->description(),
                              response_function )
{ /* ... */ }

// Evaluate the response function at the desired phase space point
double StandardParticleResponse::evaluate( const ParticleState& particle ) const
{
  return d_response_function->evaluate( particle );
}

// Check if the response function is spatially uniform
bool StandardParticleResponse::isSpatiallyUniform() const
{
  return d_response_function->isSpatiallyUniform();
}

EXPLICIT_CLASS_SERIALIZE_INST( StandardParticleResponse );
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( StandardParticleResponse, MonteCarlo );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleResponse.cpp
//---------------------------------------------------------------------------//
