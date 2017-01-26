//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleDistribution.hpp
//! \author Alex Robinson
//! \brief  Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleDistribution::ParticleDistribution(
                                      const ModuleTraits::InternalROIHandle id,
                                      const std::string& name,
                                      const ParticleType particle_type )
  : d_id( id ),
    d_name( name ),
    d_particle_type( particle_type )
{
  // Make sure that the id is valid
  testPrecondition( id != ModuleTraits::invalid_internal_roi_handle );
  // Make sure that the name is valid
  testPrecondition( name.size() > 0 );
}

// Return the id
ModuleTraits::InternalROIHandle ParticleDistribution::getId() const
{
  return d_id;
}

// Return the name of the region of interest
const std::string& ParticleDistribution::getName() const
{
  return d_name;
}

// Return the particle type that this distribution uses
ParticleType ParticleDistribution::getParticleType() const
{
  return d_particle_type;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.cpp
//---------------------------------------------------------------------------//
