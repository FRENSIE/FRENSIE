//---------------------------------------------------------------------------//
//!
//! \file   StateSource.hpp
//! \author Alex Robinson
//! \brief  State source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef STATE_SOURCE_HPP
#define STATE_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "ParticleSource.hpp"

namespace FACEMC{

/*! The state source class
 * \details This class takes an array of particle states and assigns one of
 * the states in the array to the particle state of interest. This is similar
 * to the surface source in MCNP (but more general).
 */
class StateSource : public ParticleSource
{
  
public:

  //! Constructor
  StateSource( const Teuchos::Array<BasicParticleState>& particle_states );

  //! Destructor
  ~StateSource()
  { /* ... */ }

  //! Sample a particle state from the source
  void sampleParticleState( BasicParticleState& particle );

  //! Return the sampling efficiency from the source 
  double getSamplingEfficiency() const = 0;

private:

  // The possible states
  Teuchos::Array<BasicParticleState>& d_particle_states;

  // The index of the next state to assign
  unsigned d_next_state_index;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end StateSource.hpp
//---------------------------------------------------------------------------//

