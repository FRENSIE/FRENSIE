//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleGenerationEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Source event dispatcher singleton class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleGenerationEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleGenerationEventDispatcher::ParticleGenerationEventDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : d_cell_id( cell_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void ParticleGenerationEventDispatcher::attachObserver(
		      const ModuleTraits::InternalEstimatorHandle id,
		      Teuchos::RCP<ParticleGenerationEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void ParticleGenerationEventDispatcher::detachObserver( 
			       const ModuleTraits::InternalEstimatorHandle id )
{
  d_observer_map.erase( id );
}

// Set a new event and dispatch to the observers
void ParticleGenerationEventDispatcher::dispatchParticleGenerationEvent(
					        const ParticleState& particle )
{
  // Make sure the particle state is valid
  testPrecondition( particle.getCell() == d_cell_id );
  
  ObserverIdMap::iterator it = d_observer_map.begin();
  
  while( it != d_observer_map.end() )
  {
    it->second->updateFromParticleGenerationEvent( particle );

    ++it;
  }
}

// Get the cell id corresponding to this source event dispatcher
Geometry::ModuleTraits::InternalCellHandle 
ParticleGenerationEventDispatcher::getCellId() const
{
  return d_cell_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleGenerationEventDispatcher.cpp
//---------------------------------------------------------------------------//
