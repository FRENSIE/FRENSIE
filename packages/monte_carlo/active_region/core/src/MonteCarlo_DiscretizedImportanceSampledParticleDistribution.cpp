//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizedImportanceSampledParticleDistribution.cpp
//! \author Philip Britt
//! \brief  Discretized Importance Sampled Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DiscretizedImportanceSampledParticleDistribution.hpp"

namespace MonteCarlo{

// Default constructor
ParticleDistribution::ParticleDistribution()
  : ParticleDistribution( "particle distribution" )
{ /* ... */ }
  
// Constructor
ParticleDistribution::ParticleDistribution( const std::string& name )
  : d_name( name )
{
  // Make sure that the name is valid
  testPrecondition( name.size() > 0 );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DiscretizedImportanceSampledParticleDistribution.cpp
//---------------------------------------------------------------------------//
