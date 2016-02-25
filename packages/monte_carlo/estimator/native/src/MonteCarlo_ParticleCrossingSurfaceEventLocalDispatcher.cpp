//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{
  
// Constructor
ParticleCrossingSurfaceEventLocalDispatcher::ParticleCrossingSurfaceEventLocalDispatcher(
	       const Geometry::ModuleTraits::InternalSurfaceHandle surface_id )
  : ParticleEventLocalDispatcher<Geometry::ModuleTraits::InternalSurfaceHandle,
                                 ParticleCrossingSurfaceEventObserver>( surface_id )
{ /* ... */ }

// Dispatch the new event ot the observers
void 
ParticleCrossingSurfaceEventLocalDispatcher::dispatchParticleCrossingSurfaceEvent(
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
