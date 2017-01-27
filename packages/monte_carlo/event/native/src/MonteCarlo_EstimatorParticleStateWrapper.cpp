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
    d_reference_time( 0.0 )
{ /* ... */ }

// Particle state constructor
EstimatorParticleStateWrapper::EstimatorParticleStateWrapper(
                                                const ParticleState& particle )
  : d_particle( &particle ),
    d_angle_cosine( 0.0 ),
    d_reference_time( particle.getTime() )
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

// Set the reference time
void EstimatorParticleStateWrapper::setReferenceTime(
                                                  const double reference_time )
{
  // Make sure that the time is valid
  testPrecondition( reference_time >= 0.0 );
  
  d_reference_time = reference_time
}

// Calculate the reference time at the end of a track
void EstimatorParticleStateWrapper::calculateReferenceTimeAtEndOfTrack(
                                                    const double track_length )
{
  // Make sure that the track length is valid
  testPrecondition( track_length > 0.0 );

  d_reference_time = d_particle->getTime() +
    track_length/d_particle->getSpeed();
}

// Calculate the reference time at the beginning of track
void EstimatorParticleStateWrapper::calculateReferenceTimeAtBeginningOfTrack(
                                                    const double track_length )
{
  // Make sure that the track length is valid
  testPrecondition( track_length > 0.0 );

  d_reference_time = d_particle->getTime() -
    track_length/d_particle->getSpeed();
}

// Get the reference time
double EstimatorParticleStateWrapper::getReferenceTime() const
{
  return d_reference_time;
}

// Get the time duration (particle time - reference time)
double EstimatorParticleStateWrapper::getTimeDuration() const
{
  return d_particle->getTime() - d_reference_time;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorParticleStateWrapper.cpp
//---------------------------------------------------------------------------//
