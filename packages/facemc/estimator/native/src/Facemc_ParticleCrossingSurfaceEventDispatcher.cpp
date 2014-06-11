//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{
  
// Constructor
ParticleCrossingSurfaceEventDispatcher::ParticleCrossingSurfaceEventDispatcher(
	       const Geometry::ModuleTraits::InternalSurfaceHandle surface_id )
  : d_surface_id( surface_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void ParticleCrossingSurfaceEventDispatcher::attachObserver(
		 const ModuleTraits::InternalEstimatorHandle id,
		 Teuchos::RCP<ParticleCrossingSurfaceEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void ParticleCrossingSurfaceEventDispatcher::detachObserver( 
			       const ModuleTraits::InternalEstimatorHandle id )
{
  d_observer_map.erase( id );
}

// Dispatch the new event ot the observers
void 
ParticleCrossingSurfaceEventDispatcher::dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine )
{
  // Make sure the surface being crossed is valid
  testPrecondition( surface_crossing == d_surface_id );

  ObserverIdMap::iterator it = d_observer_map.begin();

  while( it != d_observer_map.end() )
  {
    it->second->updateFromParticleCrossingSurfaceEvent( particle,
							surface_crossing,
							angle_cosine );

    ++it;
  }
}

// Get the surface id corresponding to this particle crossing surface disp.
Geometry::ModuleTraits::InternalSurfaceHandle 
ParticleCrossingSurfaceEventDispatcher::getSurfaceId() const
{
  return d_surface_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventDispatcher.cpp
//---------------------------------------------------------------------------//
