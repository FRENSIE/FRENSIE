//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventHandler.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event handler definition
//! 
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventHandler.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace MonteCarlo{

//! Constructor
ParticleCrossingSurfaceEventHandler::ParticleCrossingSurfaceEventHandler()
  : d_particle_crossing_surface_event_dispatcher()
{ /* ... */ }

// Return the particle crossing surface event dispatcher
ParticleCrossingSurfaceEventDispatcher&
ParticleCrossingSurfaceEventHandler::getParticleCrossingSurfaceEventDispatcher()
{
  return d_particle_crossing_surface_event_dispatcher;
}

// Return the particle crossing surface event dispatcher
const ParticleCrossingSurfaceEventDispatcher&
ParticleCrossingSurfaceEventHandler::getParticleCrossingSurfaceEventDispatcher() const
{
  return d_particle_crossing_surface_event_dispatcher;
}

// Update the observers from a surface intersection event
void ParticleCrossingSurfaceEventHandler::updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] )
{
  // Make sure the surface normal is valid
  testPrecondition( Utility::validDirection( surface_normal ) );

  double angle_cosine = Utility::calculateCosineOfAngleBetweenVectors(
						       particle.getDirection(),
						       surface_normal );

  d_particle_crossing_surface_event_dispatcher.dispatchParticleCrossingSurfaceEvent(
							      particle,
							      surface_crossing,
							      angle_cosine );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventHandler.cpp
//---------------------------------------------------------------------------//
