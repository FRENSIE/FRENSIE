//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StateSource.hpp
//! \author Alex Robinson
//! \brief  State source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STATE_SOURCE_HPP
#define FACEMC_STATE_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FACEMC Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleStateCore.hpp"

namespace MonteCarlo{

/*! The state source class
 * \details This class takes an array of particle states and assigns one of
 * the states in the array to the particle state of interest. This is similar
 * to the surface source in MCNP (but more general).
 */
class StateSource : public ParticleSource
{
  
public:

  //! Constructor
  StateSource( 
	     const Teuchos::ArrayRCP<ParticleStateCore>& raw_particle_states );

  //! Destructor
  ~StateSource()
  { /* ... */ }

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank );

  //! Return the sampling efficiency from the source 
  double getSamplingEfficiency() const;

private:

  // Compare two particle state cores
  static bool compareCores( const ParticleStateCore& core_a,
			    const ParticleStateCore& core_b );

  // The possible states
  Teuchos::ArrayRCP<ParticleStateCore> d_raw_particle_states;

  // The next index
  unsigned d_next_index;
};

} // end MonteCarlo namespace

#endif // end FACEMC_STATE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StateSource.hpp
//---------------------------------------------------------------------------//

