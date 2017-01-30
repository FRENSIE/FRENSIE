//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorParticleStateWrapper.hpp
//! \author Alex Robinson
//! \brief  The estimator particle state wrapper
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_PARTICLE_STATE_WRAPPER_HPP
#define MONTE_CARLO_ESTIMATOR_PARTICLE_STATE_WRAPPER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The estimator particle state wrapper
 * \details This is a light weight wrapper around the particle state class
 * that allows extra information relevant to estimators to be stored. A
 * raw pointer to the particle state class will be used so it is important
 * that the wrapper class be destroyed before the particle state.
 */
class EstimatorParticleStateWrapper
{

public:

  //! Constructor
  EstimatorParticleStateWrapper();

  //! Particle state constructor
  EstimatorParticleStateWrapper( const ParticleState& particle );

  //! Destructor
  ~EstimatorParticleStateWrapper()
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

#endif // end MONTE_CARLO_ESTIMATOR_PARTICLE_STATE_WRAPPER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorParticleStateWrapper.hpp
//---------------------------------------------------------------------------//
