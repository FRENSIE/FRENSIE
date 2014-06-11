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

  static void attachObserver(
	        const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id,
	        ParticleCrossingSurfaceEventObserver* observer );

  //! Detach the observer from the appropriate dispatcher
  static void detachObserver(
		const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

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

// Attach an observer
/*! \details A non-owning Teuchos::RCP willl be constructed from the raw
 * pointer. This function should be used from inside of observer constructors.
 * The observer destructor should call the detachObserver method to avoid
 * null pointer dereferencing in the dispatchers.
 */
inline void ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
	        const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id,
	        ParticleCrossingSurfaceEventObserver* observer )
{
  Teuchos::RCP<ParticleCrossingSurfaceEventObserver> safe_observer( observer,
								    false );

  ParticleCrossingSurfaceEventDispatcherDB::attachObserver( surface_id,
							    estimator_id,
							    safe_observer );
}

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
