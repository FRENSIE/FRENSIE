//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSubtrackEndingInCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleSubtrackEndingInCellEventDispatcher::ParticleSubtrackEndingInCellEventDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : d_cell_id( cell_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void ParticleSubtrackEndingInCellEventDispatcher::attachObserver(
	    const ModuleTraits::InternalEstimatorHandle id,
	    Teuchos::RCP<ParticleSubtrackEndingInCellEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void ParticleSubtrackEndingInCellEventDispatcher::detachObserver( 
			       const ModuleTraits::InternalEstimatorHandle id )
{
  d_observer_map.erase( id );
}

// Dispatch the new event to the observers
void ParticleSubtrackEndingInCellEventDispatcher::dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
	     const double track_length )
{
  // Make sure the cell being collided with is valid
  testPrecondition( cell_of_subtrack == d_cell_id );

  ObserverIdMap::iterator it = d_observer_map.begin();

  while( it != d_observer_map.end() )
  {
    it->second->updateFromParticleSubtrackEndingInCellEvent(
							    particle,
							    cell_of_subtrack,
							    track_length );

    ++it;
  }
}

// Get the cell id corresponding to this particle entering cell event disp.
Geometry::ModuleTraits::InternalCellHandle 
ParticleSubtrackEndingInCellEventDispatcher::getCellId() const
{
  return d_cell_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSubtrackEndingInCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
