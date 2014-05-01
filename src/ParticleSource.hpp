//---------------------------------------------------------------------------//
//!
//! \file   ParticleSource.hpp
//! \author Alex Robinson
//! \brief  Particle source declaration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_SOURCE_HPP
#define PARTICLE_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "ParticleBank.hpp"

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
  virtual void sampleParticleState( ParticleBank& bank ) = 0;

  //! Return the sampling efficiency from the source
  virtual double getSamplingEfficiency() const = 0;
};

} // end FACEMC namespace

#endif // end PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end ParticleSource.hpp
//---------------------------------------------------------------------------//
