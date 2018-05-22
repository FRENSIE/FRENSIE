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

// FRENSIE Includes
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Utility_Set.hpp"

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

  //! Basic Constructor
  ParticleResponse( const size_t id );

  //! Constructor
  ParticleResponse( const size_t id, const std::string& name );

private:

  //! Default constructor
  ParticleResponse()
  { /* ... */ }

  // The default response
  static const std::shared_ptr<const ParticleResponse> s_default_response;

  // The response id
  UniqueIdManager<ParticleResponse,size_t> d_id;

  // The response name
  std::string d_name;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_RESPONSE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponse.hpp
//---------------------------------------------------------------------------//
