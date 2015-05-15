//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MasslessParticleState.hpp
//! \author Alex Robinson
//! \brief  Massless particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MASSLESS_PARTICLE_STATE_HPP
#define MONTE_CARLO_MASSLESS_PARTICLE_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The massless particle state class
class MasslessParticleState : public ParticleState
{

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  MasslessParticleState( const historyNumberType history_number,
		 const ParticleType type );

  //! Copy constructor (with possible creation of new generation)
  MasslessParticleState( const ParticleState& existing_base_state,
		 const ParticleType new_type,
		 const bool increment_generation_number,
		 const bool reset_collision_number );

  //! Core constructor
  MasslessParticleState( const ParticleStateCore& core );

  //! Destructor
  virtual ~MasslessParticleState()
  { /* ... */ }

  //! Return the speed of the particle (cm/s)
  double getSpeed() const;

private:

  //! Calculate the time to traverse a distance
  ParticleState::timeType calculateTraversalTime( const double distance) const;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MASSLESS_PARTICLE_STATE_HPP
