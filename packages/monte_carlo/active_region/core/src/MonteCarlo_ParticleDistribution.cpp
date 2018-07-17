//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleDistribution.hpp
//! \author Alex Robinson
//! \brief  Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_DesignByContract.hpp"

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

// Return the name of the region of interest
const std::string& ParticleDistribution::getName() const
{
  return d_name;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ParticleDistribution );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.cpp
//---------------------------------------------------------------------------//
