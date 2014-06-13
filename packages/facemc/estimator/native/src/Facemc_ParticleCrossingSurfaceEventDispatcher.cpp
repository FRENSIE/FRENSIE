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
  : ParticleEventDispatcher<Geometry::ModuleTraits::InternalSurfaceHandle,
			    ParticleCrossingSurfaceEventObserver>( surface_id )
{ /* ... */ }

// Dispatch the new event ot the observers
void 
ParticleCrossingSurfaceEventDispatcher::dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine )
{
  // Make sure the surface being crossed is valid
  testPrecondition( surface_crossing == this->getId() );

  ObserverIdMap::iterator it = observer_id_map().begin();

  while( it != observer_id_map().end() )
  {
    it->second->updateFromParticleCrossingSurfaceEvent( particle,
							surface_crossing,
							angle_cosine );

    ++it;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventDispatcher.cpp
//---------------------------------------------------------------------------//
