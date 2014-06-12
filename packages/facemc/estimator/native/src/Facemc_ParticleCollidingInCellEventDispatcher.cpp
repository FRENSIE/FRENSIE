//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCollidingInCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleCollidingInCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleCollidingInCellEventDispatcher::ParticleCollidingInCellEventDispatcher(
	             const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : d_cell_id( cell_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void ParticleCollidingInCellEventDispatcher::attachObserver(
		 const ModuleTraits::InternalEstimatorHandle id,
		 Teuchos::RCP<ParticleCollidingInCellEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void ParticleCollidingInCellEventDispatcher::detachObserver( 
			       const ModuleTraits::InternalEstimatorHandle id )
{
  d_observer_map.erase( id );
}

// Dispatch the new event to the observers
void 
ParticleCollidingInCellEventDispatcher::dispatchParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section )
{
  // Make sure the cell being collided in is valid
  testPrecondition( cell_of_collision == d_cell_id );

  ObserverIdMap::iterator it = d_observer_map.begin();

  while( it != d_observer_map.end() )
  {
    it->second->updateFromParticleCollidingInCellEvent( 
						 particle, 
						 cell_of_collision,
						 inverse_total_cross_section );

    ++it;
  }
}

// Get the cell id corresponding to this particle entering cell event disp.
Geometry::ModuleTraits::InternalCellHandle
ParticleCollidingInCellEventDispatcher::getCellId() const
{
  return d_cell_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
