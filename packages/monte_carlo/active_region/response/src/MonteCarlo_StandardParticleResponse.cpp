//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleResponse.cpp
//! \author Alex Robinson
//! \brief  The standard particle response class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardParticleResponse.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StandardParticleResponse::StandardParticleResponse(
    const size_t id,
    const std::string& name,
    const std::shared_ptr<const ParticleResponseFunction>& response_function )
  : ParticleResponse( id, name ),
    d_response_function( response_function )
{
  // Make sure that the response function pointer is valid
  testPrecondition( response_function.get() );
}

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
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleResponse.cpp
//---------------------------------------------------------------------------//
