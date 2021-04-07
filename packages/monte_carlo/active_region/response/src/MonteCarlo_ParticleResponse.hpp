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
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The particle response base class
class ParticleResponse
{

public:

  //! Constructor
  ParticleResponse( const std::string& name );

  //! Destructor
  virtual ~ParticleResponse();

  //! Get the default response (always evaluates to 1.0)
  static std::shared_ptr<const ParticleResponse> getDefault();

  //! Return the name of the response function
  const std::string& getName() const;

  //! Evaluate the response at the desired phase space point
  virtual double evaluate( const ParticleState& particle ) const = 0;

  //! Check if the response is spatially uniform
  virtual bool isSpatiallyUniform() const = 0;

protected:

  //! Default constructor
  ParticleResponse()
  { /* ... */ }

private:

  // Serialize the particle response
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The response name
  std::string d_name;
};

// Serialize the particle response
template<typename Archive>
void ParticleResponse::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_name );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleResponse, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ParticleResponse, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleResponse );

namespace Utility{

//! Specialization of Utility::TypeNameTraits for MonteCarlo::ParticleResponse
template<>
struct TypeNameTraits<MonteCarlo::ParticleResponse>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "ParticleResponse"; }
};

} // end Utility namespace

#endif // end MONTE_CARLO_PARTICLE_RESPONSE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponse.hpp
//---------------------------------------------------------------------------//
