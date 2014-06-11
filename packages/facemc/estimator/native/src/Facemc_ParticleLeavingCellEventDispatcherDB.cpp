//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher database class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleLeavingCellEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
ParticleLeavingCellEventDispatcherDB::DispatcherMap
ParticleLeavingCellEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
Teuchos::RCP<ParticleLeavingCellEventDispatcher>& 
ParticleLeavingCellEventDispatcherDB::getDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
{
  DispatcherMap::iterator it = 
    ParticleLeavingCellEventDispatcherDB::master_map.find( cell_id );

  if( it != ParticleLeavingCellEventDispatcherDB::master_map.end() )
    return it->second;
  else
  {
    Teuchos::RCP<ParticleLeavingCellEventDispatcher>& new_dispatcher = 
      ParticleLeavingCellEventDispatcherDB::master_map[cell_id];

    new_dispatcher.reset( new ParticleLeavingCellEventDispatcher( cell_id ) );

    return new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
void ParticleLeavingCellEventDispatcherDB::attachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id,
		    Teuchos::RCP<ParticleLeavingCellEventObserver>& observer )
{
  ParticleLeavingCellEventDispatcherDB::getDispatcher(cell_id)->attachObserver(
								  estimator_id,
								  observer );
}

// Detach an observer from the appropriate dispatcher
void ParticleLeavingCellEventDispatcherDB::detachObserver(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id,
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  ParticleLeavingCellEventDispatcherDB::getDispatcher(cell_id)->detachObserver(
								estimator_id );
}

// Detach the observer from all dispatchers
void ParticleLeavingCellEventDispatcherDB::detachObserver(
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  DispatcherMap::iterator it = 
    ParticleLeavingCellEventDispatcherDB::master_map.begin();

  while( it != ParticleLeavingCellEventDispatcherDB::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
