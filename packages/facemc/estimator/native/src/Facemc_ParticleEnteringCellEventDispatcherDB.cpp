//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleEnteringCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleEnteringCellEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
ParticleEnteringCellEventDispatcherDB::DispatcherMap
ParticleEnteringCellEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
Teuchos::RCP<ParticleEnteringCellEventDispatcher>& 
ParticleEnteringCellEventDispatcherDB::getDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
{
  DispatcherMap::iterator it = 
    ParticleEnteringCellEventDispatcherDB::master_map.find( cell_id );

  if( it != ParticleEnteringCellEventDispatcherDB::master_map.end() )
    return it->second;
  else
  {
    Teuchos::RCP<ParticleEnteringCellEventDispatcher>& new_dispatcher = 
      ParticleEnteringCellEventDispatcherDB::master_map[cell_id];

    new_dispatcher.reset( new ParticleEnteringCellEventDispatcher( cell_id ) );

    return new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
void ParticleEnteringCellEventDispatcherDB::attachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id,
		    Teuchos::RCP<ParticleEnteringCellEventObserver>& observer )
{
  ParticleEnteringCellEventDispatcherDB::getDispatcher(cell_id)->attachObserver(
								  estimator_id,
								  observer );
}

// Detach an observer from the appropriate dispatcher
void ParticleEnteringCellEventDispatcherDB::detachObserver(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id,
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  ParticleEnteringCellEventDispatcherDB::getDispatcher(cell_id)->detachObserver(
								estimator_id );
}

// Detach the observer from all dispatchers
void ParticleEnteringCellEventDispatcherDB::detachObserver(
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  DispatcherMap::iterator it = 
    ParticleEnteringCellEventDispatcherDB::master_map.begin();

  while( it != ParticleEnteringCellEventDispatcherDB::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

// Detach all observers
void ParticleEnteringCellEventDispatcherDB::detachAllObservers()
{
  ParticleEnteringCellEventDispatcherDB::master_map.clear();
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleEnteringCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
