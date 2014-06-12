//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSubtrackEndingInCellEventDisptacherDB.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher database def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
ParticleSubtrackEndingInCellEventDispatcherDB::DispatcherMap
ParticleSubtrackEndingInCellEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
Teuchos::RCP<ParticleSubtrackEndingInCellEventDispatcher>& 
ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
{
  DispatcherMap::iterator it = 
    ParticleSubtrackEndingInCellEventDispatcherDB::master_map.find( cell_id );

  if( it != ParticleSubtrackEndingInCellEventDispatcherDB::master_map.end() )
    return it->second;
  else
  {
    Teuchos::RCP<ParticleSubtrackEndingInCellEventDispatcher>& new_dispatcher =
      ParticleSubtrackEndingInCellEventDispatcherDB::master_map[cell_id];

    new_dispatcher.reset( 
		 new ParticleSubtrackEndingInCellEventDispatcher( cell_id ) );

    return new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
void ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
	    const Geometry::ModuleTraits::InternalCellHandle cell_id,
	    const ModuleTraits::InternalEstimatorHandle estimator_id,
	    Teuchos::RCP<ParticleSubtrackEndingInCellEventObserver>& observer )
{
  ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher(cell_id)->attachObserver(
								  estimator_id,
								  observer );
}
  
// Detach an observer from the appropriate dispatcher
void ParticleSubtrackEndingInCellEventDispatcherDB::detachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher(cell_id)->detachObserver(
								estimator_id );
}

// Detach the observer from all dispatchers
void ParticleSubtrackEndingInCellEventDispatcherDB::detachObserver(
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  DispatcherMap::iterator it = 
    ParticleSubtrackEndingInCellEventDispatcherDB::master_map.begin();

  while( it != ParticleSubtrackEndingInCellEventDispatcherDB::master_map.end())
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

// Detach all observers
void ParticleSubtrackEndingInCellEventDispatcherDB::detachAllObservers()
{
  ParticleSubtrackEndingInCellEventDispatcherDB::master_map.clear();
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSubtrackEndingInCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
