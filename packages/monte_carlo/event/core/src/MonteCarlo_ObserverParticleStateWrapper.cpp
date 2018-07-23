//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverParticleStateWrapper.cpp
//! \author Alex Robinson
//! \brief  The estimator particle state wrapper class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
ObserverParticleStateWrapper::ObserverParticleStateWrapper()
  : d_particle( NULL ),
    d_angle_cosine( 0.0 ),
    d_state_start_time( 0.0 ),
    d_state_end_time( 0.0 )
{ /* ... */ }

// Particle state constructor
ObserverParticleStateWrapper::ObserverParticleStateWrapper(
                                                const ParticleState& particle )
  : d_particle( &particle ),
    d_angle_cosine( 0.0 ),
    d_state_start_time( particle.getTime() ),
    d_state_end_time( particle.getTime() )
{ /* ... */ }

// Return the particle state
const ParticleState& ObserverParticleStateWrapper::getParticleState() const
{
  // Make sure the particle state is valid
  testPrecondition( d_particle );

  return *d_particle;
}

// Set the angle cosine
void ObserverParticleStateWrapper::setAngleCosine( const double angle_cosine )
{
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );

  d_angle_cosine = angle_cosine;
}

// Return the angle cosine
double ObserverParticleStateWrapper::getAngleCosine() const
{
  return d_angle_cosine;
}

// Calculate the state times using particle time as track start time
void ObserverParticleStateWrapper::calculateStateTimesUsingParticleTimeAsStartTime(
                                                    const double track_length )
{
  // Make sure that the track length is valid
  testPrecondition( track_length > 0.0 );

  d_state_start_time = d_particle->getTime();
  d_state_end_time = d_state_start_time + track_length/d_particle->getSpeed();
}

// Calculate the state times using particle time as track end time
void ObserverParticleStateWrapper::calculateStateTimesUsingParticleTimeAsEndTime(
                                                    const double track_length )
{
  // Make sure that the track length is valid
  testPrecondition( track_length > 0.0 );

  d_state_end_time = d_particle->getTime();
  d_state_start_time = d_state_end_time - track_length/d_particle->getSpeed();
}

// Set the state start time
void ObserverParticleStateWrapper::setStartTime( const double time )
{
  // Make sure that the time is valid
  testPrecondition( time >= 0.0 );
  
  d_state_start_time = time;
}

// Set the state end time
void ObserverParticleStateWrapper::setEndTime( const double time )
{
  // Make sure that the time is valid
  testPrecondition( time >= 0.0 );
  
  d_state_end_time = time;
}

// Get the state start time
double ObserverParticleStateWrapper::getStartTime() const
{
  return d_state_start_time;
}

// Get the state end time
double ObserverParticleStateWrapper::getEndTime() const
{
  return d_state_end_time;
}

// Get the state time duration
double ObserverParticleStateWrapper::getTimeDuration() const
{
  // Make sure that the duration is valid
  testPrecondition( d_state_end_time <= d_state_end_time );
  
  return d_state_end_time - d_state_start_time;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverParticleStateWrapper.cpp
//---------------------------------------------------------------------------//
