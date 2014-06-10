//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleGenerationEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Source event dispatcher database definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleGenerationEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
ParticleGenerationEventDispatcherDB::DispatcherMap 
ParticleGenerationEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
/*! \details If a dispatcher for the cell id does not exist it will be created.
 */
Teuchos::RCP<ParticleGenerationEventDispatcher>& 
ParticleGenerationEventDispatcherDB::getDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
{
  DispatcherMap::iterator it = 
    ParticleGenerationEventDispatcherDB::master_map.find( cell_id );

  if( it != ParticleGenerationEventDispatcherDB::master_map.end() )
    return it->second;
  else
  {
    Teuchos::RCP<ParticleGenerationEventDispatcher>& new_dispatcher =
      ParticleGenerationEventDispatcherDB::master_map[cell_id];

    new_dispatcher.reset( new ParticleGenerationEventDispatcher( cell_id ) );

    return new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
void ParticleGenerationEventDispatcherDB::attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      Teuchos::RCP<ParticleGenerationEventObserver>& observer )
{
  ParticleGenerationEventDispatcherDB::getDispatcher(cell_id)->attachObserver( 
								 estimator_id,
								 observer );
}

// Detach the observer from the appropriate dispatcher
void ParticleGenerationEventDispatcherDB::detachObserver(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id,
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  ParticleGenerationEventDispatcherDB::getDispatcher(cell_id)->detachObserver( 
								estimator_id );
}

// Detach the observer from all dispatchers
void ParticleGenerationEventDispatcherDB::detachObserver( 
		     const ModuleTraits::InternalEstimatorHandle estimator_id )
{
  DispatcherMap::iterator it = 
    ParticleGenerationEventDispatcherDB::master_map.begin();

  while( it != ParticleGenerationEventDispatcherDB::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleGenerationEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
