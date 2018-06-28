//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverParticleStateWrapper.hpp
//! \author Alex Robinson
//! \brief  The observer particle state wrapper
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PARTICLE_STATE_WRAPPER_HPP
#define MONTE_CARLO_OBSERVER_PARTICLE_STATE_WRAPPER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The observer particle state wrapper
 * \details This is a light weight wrapper around the particle state class
 * that allows extra information relevant to certain observers to be stored. A
 * raw pointer to the particle state class will be used so it is important
 * that the wrapper class be destroyed before the particle state.
 */
class ObserverParticleStateWrapper
{

public:

  //! Constructor
  ObserverParticleStateWrapper();

  //! Particle state constructor
  ObserverParticleStateWrapper( const ParticleState& particle );

  //! Destructor
  ~ObserverParticleStateWrapper()
  { /* ... */ }

  //! Return the particle state
  const ParticleState& getParticleState() const;

  //! Set the angle cosine
  void setAngleCosine( const double angle_cosine );

  //! Return the angle cosine
  double getAngleCosine() const;

  //! Calculate the state times using particle time as track start time
  void calculateStateTimesUsingParticleTimeAsStartTime(
                                                   const double track_length );

  //! Calculate the state times using particle time as track end time
  void calculateStateTimesUsingParticleTimeAsEndTime(
                                                   const double track_length );

  //! Set the state start time
  void setStartTime( const double time );

  //! Set the state end time
  void setEndTime( const double time ); 

  //! Get the state start time
  double getStartTime() const;

  //! Get the state end time
  double getEndTime() const;

  //! Get the state time duration
  double getTimeDuration() const;

private:

  // The particle state
  const ParticleState* d_particle;

  // The angle cosine
  double d_angle_cosine;

  // The state start time
  double d_state_start_time;

  // The state end time
  double d_state_end_time;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PARTICLE_STATE_WRAPPER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverParticleStateWrapper.hpp
//---------------------------------------------------------------------------//
