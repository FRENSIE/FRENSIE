//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleResponse.hpp
//! \author Alex Robinson
//! \brief  Particle response base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_RESPONSE_HPP
#define MONTE_CARLO_PARTICLE_RESPONSE_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_UniqueIdManager.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The particle response base class
class ParticleResponse
{

public:

  //! Destructor
  virtual ~ParticleResponse();

  //! Default response function (always evaluates to 1.0)
  static const std::shared_ptr<const ParticleResponse> getDefault();

  //! Return the id
  size_t getId() const;

  //! Return the name of the response function
  const std::string& getName() const;

  //! Evaluate the response function at the desired phase space point
  virtual double evaluate( const ParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  virtual bool isSpatiallyUniform() const;

protected:

  //! Default constructor
  ParticleResponse()
    : d_id( 0 )
  { /* ... */ }

  //! Basic Constructor
  ParticleResponse( const size_t id );

  //! Constructor
  ParticleResponse( const size_t id, const std::string& name );

private:

  // Serialize the particle response
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The default response
  static const std::shared_ptr<const ParticleResponse> s_default_response;

  // The response id
  UniqueIdManager<ParticleResponse,size_t> d_id;

  // The response name
  std::string d_name;
};

// Serialize the particle response
template<typename Archive>
void ParticleResponse::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_name );
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleResponse, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleResponse, MonteCarlo );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::ParticleResponse );

#endif // end MONTE_CARLO_PARTICLE_RESPONSE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponse.hpp
//---------------------------------------------------------------------------//
