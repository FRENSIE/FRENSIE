//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleCrossingSurfaceEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle crossing surface event dispatcher class
class ParticleCrossingSurfaceEventDispatcher
{

public:

  //! Constructor
  ParticleCrossingSurfaceEventDispatcher(
	      const Geometry::ModuleTraits::InternalSurfaceHandle surface_id );

  //! Destructor
  ~ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver(
		const ModuleTraits::InternalEstimatorHandle id,
	        Teuchos::RCP<ParticleCrossingSurfaceEventObserver>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const ModuleTraits::InternalEstimatorHandle id );

  //! Dispatch the new event ot the observers
  void dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );

  //! Get the surface id corresponding to this particle crossing surface disp.
  Geometry::ModuleTraits::InternalSurfaceHandle getSurfaceId() const;

private:

  // The surface handle for which particle crossing surface events will be disp
  Geometry::ModuleTraits::InternalSurfaceHandle d_surface_id;

  // The observer map
  typedef boost::unordered_map<ModuleTraits::InternalEstimatorHandle,
			   Teuchos::RCP<ParticleCrossingSurfaceEventObserver> >
  ObserverIdMap;

  ObserverIdMap d_observer_map;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventDispatcher.hpp
//---------------------------------------------------------------------------//
