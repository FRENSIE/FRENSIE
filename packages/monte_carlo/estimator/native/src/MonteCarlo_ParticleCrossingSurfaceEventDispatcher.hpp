//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle crossing surface event dispatcher database class
 * \ingroup particle_crossing_surface_event
 */
class ParticleCrossingSurfaceEventDispatcher : public ParticleEventDispatcher<ParticleCrossingSurfaceEventLocalDispatcher>
{

public:

  //! Constructor
  ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle crossing surface event to the observers
  void dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );
};

// Dispatch the particle crossing surface event to the observers
inline void
ParticleCrossingSurfaceEventDispatcher::dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine )
{
  DispatcherMap::iterator it = this->dispatcher_map().find( surface_crossing );

  if( it != this->dispatcher_map().end() )
  {
    it->second->dispatchParticleCrossingSurfaceEvent( particle,
						      surface_crossing,
						      angle_cosine );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp
//---------------------------------------------------------------------------//
