//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleResponse.hpp
//! \author Alex Robinson
//! \brief  Standard particle response class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_RESPONSE_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_RESPONSE_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleResponse.hpp"
#include "MonteCarlo_ParticleResponseFunction.hpp"

namespace MonteCarlo{

//! The standard particle response class
class StandardParticleResponse : public ParticleResponse
{

public:

  //! Constructor
  StandardParticleResponse(
    const std::string& name,
    const std::shared_ptr<const ParticleResponseFunction>& response_function );

  //! Constructor
  StandardParticleResponse(
    const std::shared_ptr<const ParticleResponseFunction>& response_function );

  //! Destructor
  ~StandardParticleResponse()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

private:

  //! Default constructor
  StandardParticleResponse()
  { /* ... */ }

  // Serialize the particle response
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The response function
  std::shared_ptr<const ParticleResponseFunction> d_response_function;
};

// Serialize the particle response
template<typename Archive>
void StandardParticleResponse::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponse );

  // Serialize the local member data
  ar & BOOST_SERIALIZATION_NVP( d_response_function );
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardParticleResponse, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardParticleResponse, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, StandardParticleResponse );

#endif // end MONTE_CARLO_STANDARD_PARTICLE_RESPONSE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleResponse.hpp
//---------------------------------------------------------------------------//
