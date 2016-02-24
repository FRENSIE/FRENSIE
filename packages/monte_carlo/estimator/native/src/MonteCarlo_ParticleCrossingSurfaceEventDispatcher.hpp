//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventDispatcher.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The particle crossing surface event dispatcher class
class ParticleCrossingSurfaceEventDispatcher : 
    public ParticleEventDispatcher<Geometry::ModuleTraits::InternalSurfaceHandle,
				   ParticleCrossingSurfaceEventObserver>
{

public:

  //! Constructor
  ParticleCrossingSurfaceEventDispatcher(
	      const Geometry::ModuleTraits::InternalSurfaceHandle surface_id );

  //! Destructor
  ~ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp
//---------------------------------------------------------------------------//
