//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database class decl.\
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
ParticleCrossingSurfaceEventDispatcherDB::DispatcherMap
ParticleCrossingSurfaceEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
Teuchos::RCP<ParticleCrossingSurfaceEventDispatcher>& 
ParticleCrossingSurfaceEventDispatcherDB::getDispatcher(
	       const Geometry::ModuleTraits::InternalSurfaceHandle surface_id )
{
  DispatcherMap::iterator it = 
    ParticleCrossingSurfaceEventDispatcherDB::master_map.find( surface_id );

  if( it != ParticleCrossingSurfaceEventDispatcherDB::master_map.end() )
      return it->second;
  else
  {
    Teuchos::RCP<ParticleCrossingSurfaceEventDispatcher>& new_dispatcher = 
      ParticleCrossingSurfaceEventDispatcherDB::master_map[surface_id];

    new_dispatcher.reset( new ParticleCrossingSurfaceEventDispatcher( 
								surface_id ) );

    return new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
void ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
		const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id,
	        Teuchos::RCP<ParticleCrossingSurfaceEventObserver>& observer )
{
  ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( surface_id )->attachObserver(
								  estimator_id,
								  observer );
}

// Detach the observer from the appropriate dispatcher
void ParticleCrossingSurfaceEventDispatcherDB::detachObserver(
		const Geometry::ModuleTraits::InternalSurfaceHandle surface_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( surface_id )->detachObserver(
								estimator_id );
}

// Detach the observer from all dispatchers
void ParticleCrossingSurfaceEventDispatcherDB::detachObserver(
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  DispatcherMap::iterator it = 
    ParticleCrossingSurfaceEventDispatcherDB::master_map.begin();

  while( it != ParticleCrossingSurfaceEventDispatcherDB::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

// Detach all observers
void ParticleCrossingSurfaceEventDispatcherDB::detachAllObservers()
{
  ParticleCrossingSurfaceEventDispatcherDB::master_map.clear();
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
