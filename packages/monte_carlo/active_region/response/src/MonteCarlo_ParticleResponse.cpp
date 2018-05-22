//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleResponse.cpp
//! \author Alex Robinson
//! \brief  Particle response base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleResponse.hpp"
#include "Utility_ToString.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the default response function
const std::shared_ptr<const ParticleResponse>
ParticleResponse::s_default_response( new ParticleResponse( std::numeric_limits<size_t>::max(), "default" ) );

// Basic Constructor
ParticleResponse::ParticleResponse( const size_t id )
  : ParticleResponse( id, std::string( "particle response " ) + Utility::toString( id ) )
{ /* ... */ }
  
// Constructor
ParticleResponse::ParticleResponse( const size_t id, const std::string& name )
  : d_id( id ),
    d_name( name )
{ 
  // Make sure that the name is valid
  testPrecondition( name.size() > 0 );
}

// Destructor
ParticleResponse::~ParticleResponse()
{ /* ... */ }
  
// Return the id
size_t ParticleResponse::getId() const
{
  return d_id;
}

// Return the name of the response function
const std::string& ParticleResponse::getName() const
{
  return d_name;
}

// Evaluate the response function at the desired phase space point
double ParticleResponse::evaluate( const ParticleState& ) const
{
  return 1.0;
}

// Check if the response function is spatially uniform
bool ParticleResponse::isSpatiallyUniform() const
{
  return true;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponse.cpp
//---------------------------------------------------------------------------//
