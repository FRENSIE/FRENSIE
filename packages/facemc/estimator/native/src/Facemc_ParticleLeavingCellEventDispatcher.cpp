//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleLeavingCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleLeavingCellEventDispatcher::ParticleLeavingCellEventDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : d_cell_id( cell_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void ParticleLeavingCellEventDispatcher::attachObserver(
		     const ModuleTraits::InternalEstimatorHandle id,
		     Teuchos::RCP<ParticleLeavingCellEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void ParticleLeavingCellEventDispatcher::detachObserver( 
			       const ModuleTraits::InternalEstimatorHandle id )
{
  d_observer_map.erase( id );
}

// Dispatch the new event to the observers
void ParticleLeavingCellEventDispatcher::dispatchParticleLeavingCellEvent(
	        const ParticleState& particle,
	        const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  // Make sure the cell being entered is valid
  testPrecondition( cell_leaving == d_cell_id );

  ObserverIdMap::iterator it = d_observer_map.begin();

  while( it != d_observer_map.end() )
  {
    it->second->updateFromParticleLeavingCellEvent( particle, cell_leaving );

    ++it;
  }
}

// Get the cell id corresponding to this particle leaving cell event disp.
Geometry::ModuleTraits::InternalCellHandle
ParticleLeavingCellEventDispatcher::getCellId() const
{
  return d_cell_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
