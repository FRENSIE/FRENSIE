//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSource.hpp
//! \author Alex Robinson
//! \brief  Particle source declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SOURCE_HPP
#define FACEMC_PARTICLE_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// Facemc Includes
#include "Facemc_ParticleBank.hpp"

namespace Facemc{

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

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSource.hpp
//---------------------------------------------------------------------------//
