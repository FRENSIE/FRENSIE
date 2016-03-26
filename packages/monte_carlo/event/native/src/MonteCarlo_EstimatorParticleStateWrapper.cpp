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
    d_angle_cosine( 0.0 )
{ /* ... */ }

// Particle state constructor
EstimatorParticleStateWrapper::EstimatorParticleStateWrapper( 
                                                const ParticleState& particle )
  : d_particle( &particle ),
    d_angle_cosine( 0.0 )
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorParticleStateWrapper.cpp
//---------------------------------------------------------------------------//
