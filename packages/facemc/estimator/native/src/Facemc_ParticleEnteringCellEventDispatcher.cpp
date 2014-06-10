//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleEnteringCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleEnteringCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleEnteringCellEventDispatcher::ParticleEnteringCellEventDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : d_cell_id( cell_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void ParticleEnteringCellEventDispatcher::attachObserver(
		    const ModuleTraits::InternalEstimatorHandle id,
		    Teuchos::RCP<ParticleEnteringCellEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void ParticleEnteringCellEventDispatcher::detachObserver(
			       const ModuleTraits::InternalEstimatorHandle id )
{
  d_observer_map.erase( id );
}

// Dispatch the new event to the observers
void ParticleEnteringCellEventDispatcher::dispatchParticleEnteringCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  // Make sure the cell being entered is valid
  testPrecondition( cell_entering == d_cell_id );

  ObserverIdMap::iterator it = d_observer_map.begin();

  while( it != d_observer_map.end() )
  {
    it->second->updateFromParticleEnteringCellEvent( particle, cell_entering );

    ++it;
  }
}

// Get the cell id corresponding to this particle entering cell event disp.
Geometry::ModuleTraits::InternalCellHandle 
ParticleEnteringCellEventDispatcher::getCellId() const
{
  return d_cell_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleEnteringCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
