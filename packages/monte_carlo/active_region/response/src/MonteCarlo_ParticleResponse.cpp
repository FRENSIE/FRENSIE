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
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Initialize the default response function
const std::shared_ptr<const ParticleResponse>
ParticleResponse::s_default_response( new ParticleResponse( std::numeric_limits<size_t>::max(), "default" ) );

// Initialize the response function id set
std::set<size_t> ParticleResponse::s_id_set;

// Constructor
ParticleResponse::ParticleResponse( const size_t id, const std::string& name )
  : d_id( id ),
    d_name( name )
{ 
  TEST_FOR_EXCEPTION( s_id_set.find( id ) != s_id_set.end(),
                      std::runtime_error,
                      "The particle response id " << id << " is already in "
                      "use!" );

  s_id_set.insert( id );
}

// Destructor
ParticleResponse::~ParticleResponse()
{
  s_id_set.erase( d_id );
}
  
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
