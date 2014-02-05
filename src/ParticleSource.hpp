//---------------------------------------------------------------------------//
//!
//! \file   ParticleSource.hpp
//! \author Alex Robinson
//! \brief  Particle source declaration.hpp
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_SOURCE_HPP
#define PARTICLE_SOURCE_HPP

// FACEMC Includes
#include "BasicParticleState.hpp"

namespace FACEMC{

//! The particle source base class
class ParticleSource
{

public:

  //! Constructor
  ParticleSource()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSource()
  { /* ... */ }

  //! Sample a particle state from the source
  virtual void sampleParticleState( BasicParticleState& particle ) = 0;

  //! Return the sampling efficiency from the source
  virtual double getSamplingEfficiency() const = 0;
};

} // end FACEMC namespace

#endif // end PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end ParticleSource.hpp
//---------------------------------------------------------------------------//
