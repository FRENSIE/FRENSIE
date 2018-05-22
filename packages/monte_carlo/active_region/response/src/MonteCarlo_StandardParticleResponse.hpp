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
    const size_t id,
    const std::string& name,
    const std::shared_ptr<const ParticleResponseFunction>& response_function );

  //! Constructor
  StandardParticleResponse(
    const size_t id,
    const std::shared_ptr<const ParticleResponseFunction>& response_function );

  //! Destructor
  ~StandardParticleResponse()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

private:

  // The response function
  std::shared_ptr<const ParticleResponseFunction> d_response_function;
};

  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_RESPONSE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleResponse.hpp
//---------------------------------------------------------------------------//
