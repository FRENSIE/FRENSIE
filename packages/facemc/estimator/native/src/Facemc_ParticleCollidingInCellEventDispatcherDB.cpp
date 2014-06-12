//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_ParticleCollidingInCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
ParticleCollidingInCellEventDispatcherDB::DispatcherMap
ParticleCollidingInCellEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
Teuchos::RCP<ParticleCollidingInCellEventDispatcher>& 
ParticleCollidingInCellEventDispatcherDB::getDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
{
  DispatcherMap::iterator it = 
    ParticleCollidingInCellEventDispatcherDB::master_map.find( cell_id );

  if( it != ParticleCollidingInCellEventDispatcherDB::master_map.end() )
    return it->second;
  else
  {
    Teuchos::RCP<ParticleCollidingInCellEventDispatcher>& new_dispatcher = 
      ParticleCollidingInCellEventDispatcherDB::master_map[cell_id];

    new_dispatcher.reset( 
		       new ParticleCollidingInCellEventDispatcher( cell_id ) );

    return new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
void ParticleCollidingInCellEventDispatcherDB::attachObserver(
		 const Geometry::ModuleTraits::InternalCellHandle cell_id,
		 const ModuleTraits::InternalEstimatorHandle estimator_id,
		 Teuchos::RCP<ParticleCollidingInCellEventObserver>& observer )
{
  ParticleCollidingInCellEventDispatcherDB::getDispatcher(cell_id)->attachObserver(
								  estimator_id,
								  observer );
}
  
// Detach an observer from the appropriate dispatcher
void ParticleCollidingInCellEventDispatcherDB::detachObserver(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id,
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  ParticleCollidingInCellEventDispatcherDB::getDispatcher(cell_id)->detachObserver(
								estimator_id );
}

// Detach the observer from all dispatchers
void ParticleCollidingInCellEventDispatcherDB::detachObserver(
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  DispatcherMap::iterator it = 
    ParticleCollidingInCellEventDispatcherDB::master_map.begin();

  while( it != ParticleCollidingInCellEventDispatcherDB::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

// Detach all observers
void ParticleCollidingInCellEventDispatcherDB::detachAllObservers()
{
  ParticleCollidingInCellEventDispatcherDB::master_map.clear();
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
