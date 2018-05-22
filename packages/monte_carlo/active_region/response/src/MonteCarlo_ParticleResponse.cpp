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

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleResponse.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ToStringTraits.hpp"
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

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( ParticleResponse );
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ParticleResponse, MonteCarlo );


//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponse.cpp
//---------------------------------------------------------------------------//
