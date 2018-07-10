//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FullPhaseSpaceParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Full phase-space particle response function class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
FullPhaseSpaceParticleResponseFunction::FullPhaseSpaceParticleResponseFunction(
             const std::shared_ptr<const ParticleDistribution>& particle_dist )
  : d_particle_dist( particle_dist )
{
  // Make sure that the particle distribution pointer is valid
  testPrecondition( particle_dist.get() );
}

// Evaluate the response function at the desired phase space point
double FullPhaseSpaceParticleResponseFunction::evaluate( const ParticleState& particle ) const
{
  return d_particle_dist->evaluate( particle );
}

// Check if the response function is spatially uniform
bool FullPhaseSpaceParticleResponseFunction::isSpatiallyUniform() const
{
  return d_particle_dist->isSpatiallyUniform();
}

// Get a description of the response function
std::string FullPhaseSpaceParticleResponseFunction::description() const
{
  return std::string("f_\"") + d_particle_dist->getName() + "\"(particle)";
}

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::FullPhaseSpaceParticleResponseFunction );
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( FullPhaseSpaceParticleResponseFunction, MonteCarlo );

//---------------------------------------------------------------------------//
// end MonteCarlo_FullPhaseSpaceParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
