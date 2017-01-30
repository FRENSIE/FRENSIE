//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorParticleStateWrapper.cpp
//! \author Alex Robinson
//! \brief  The estimator particle state wrapper class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
EstimatorParticleStateWrapper::EstimatorParticleStateWrapper()
  : d_particle( NULL ),
    d_angle_cosine( 0.0 ),
    d_state_start_time( 0.0 ),
    d_state_end_time( 0.0 )
{ /* ... */ }

// Particle state constructor
EstimatorParticleStateWrapper::EstimatorParticleStateWrapper(
                                                const ParticleState& particle )
  : d_particle( &particle ),
    d_angle_cosine( 0.0 ),
    d_state_start_time( particle.getTime() ),
    d_state_end_time( particle.getTime() )
{ /* ... */ }

// Return the particle state
const ParticleState& EstimatorParticleStateWrapper::getParticleState() const
{
  // Make sure the particle state is valid
  testPrecondition( d_particle );

  return *d_particle;
}

// Set the angle cosine
void EstimatorParticleStateWrapper::setAngleCosine( const double angle_cosine )
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );

  d_angle_cosine = angle_cosine;
}

// Return the angle cosine
double EstimatorParticleStateWrapper::getAngleCosine() const
{
  return d_angle_cosine;
}

// Calculate the state times using particle time as track start time
void EstimatorParticleStateWrapper::calculateStateTimesUsingParticleTimeAsStartTime(
                                                    const double track_length )
{
  // Make sure that the track length is valid
  testPrecondition( track_length > 0.0 );

  d_state_start_time = d_particle->getTime();
  d_state_end_time = d_state_start_time + track_length/d_particle->getSpeed();
}

// Calculate the state times using particle time as track end time
void EstimatorParticleStateWrapper::calculateStateTimesUsingParticleTimeAsEndTime(
                                                    const double track_length )
{
  // Make sure that the track length is valid
  testPrecondition( track_length > 0.0 );

  d_state_end_time = d_particle->getTime();
  d_state_start_time = d_state_end_time - track_length/d_particle->getSpeed();
}

// Get the state start time
double EstimatorParticleStateWrapper::getStartTime() const
{
  return d_state_start_time;
}

// Get the state end time
double EstimatorParticleStateWrapper::getEndTime() const
{
  return d_state_end_time;
}

// Get the state time duration
double EstimatorParticleStateWrapper::getTimeDuration() const
{
  return d_state_start_time - d_state_end_time;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorParticleStateWrapper.cpp
//---------------------------------------------------------------------------//
