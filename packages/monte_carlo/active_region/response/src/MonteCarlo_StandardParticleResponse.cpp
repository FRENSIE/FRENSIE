//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleResponse.cpp
//! \author Alex Robinson
//! \brief  The standard particle response class definition
//!
//---------------------------------------------------------------------------//

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
#include "MonteCarlo_StandardParticleResponse.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
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

// Constructor
StandardParticleResponse::StandardParticleResponse(
     const size_t id,
     const std::shared_ptr<const ParticleResponseFunction>& response_function )
  : StandardParticleResponse( id,
                              response_function->description(),
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

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( StandardParticleResponse );
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( StandardParticleResponse, MonteCarlo );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleResponse.cpp
//---------------------------------------------------------------------------//
