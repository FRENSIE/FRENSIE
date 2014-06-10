//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Source event dispatcher singleton class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_SourceEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
SourceEventDispatcher::SourceEventDispatcher(
		       const GeometryModuleTraits::InternalCellHandle cell_id )
  : d_cell_id( cell_id )
{ /* ... */ }

// Attach an observer to the dispatcher
void SourceEventDispatcher::attachObserver(
			    const Estimator::idType id,
			    const Teuchos::RCP<SourceEventObserver>& observer )
{
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
void SourceEventDispatcher::detachObserver( const Estimator::idType id )
{
  d_observer_map.erase( id );
}

// Set a new event and dispatch to the observers
void SourceEventDispatcher::dispatchSourceEvent( const ParticleState& particle)
{
  // Make sure the particle state is valid
  testPrecondition( particle.getCell() == d_cell_id );
  
  ObserverIdMap::iterator it = d_observer_map.begin();
  
  while( it != d_observer_map.end() )
  {
    it->second->update( particle );

    ++it;
  }
}

// Get the cell id corresponding to this source event dispatcher
Geometry::ModuleTraits::InternalCellHandle 
SourceEventDispatcher::getCellId() const
{
  return d_cell_id;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_SourceEventDispatcher.cpp
//---------------------------------------------------------------------------//
