//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleCrossingSurfaceEventDispatcher.hpp"

namespace Facemc{

//! The particle crossing surface event dispatcher database class
class ParticleCrossingSurfaceEventDispatcherDB
{

public:

  //! Get the appropriate dispatcher for the given surface id
  static Teuchos::RCP<ParticleCrossingSurfaceEventDispatcher>& getDispatcher(
	      const Geometry::ModuleTraits::InternalSurfaceHandle surface_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id,
	        Teuchos::RCP<ParticleCrossingSurfaceEventObserver>& observer );

  //! Detach the observer from the appropriate dispatcher
  static void detachObserver(
		const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach all observers
  static void detachAllObservers();

  //! Dispatch the particle crossing surface event to the observers
  static void dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );

private:

  // Constructor
  ParticleCrossingSurfaceEventDispatcherDB();

  // Typedef for the dispatcher map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,
			 Teuchos::RCP<ParticleCrossingSurfaceEventDispatcher> >
  DispatcherMap;

  static DispatcherMap master_map;
};

// Dispatch the particle crossing surface event to the observers
inline void
ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine )
{
  DispatcherMap::iterator it = 
    ParticleCrossingSurfaceEventDispatcherDB::master_map.find( 
							    surface_crossing );

  if( it != ParticleCrossingSurfaceEventDispatcherDB::master_map.end() )
  {
    it->second->dispatchParticleCrossingSurfaceEvent( particle,
						      surface_crossing,
						      angle_cosine );
  }
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
