//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Source event dispatcher database definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_SourceEventDispatcherDB.hpp"
#include "Facemc_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
SourceEventDispatcherDB::DispatcherMap SourceEventDispatcherDB::master_map;

// Get the appropriate dispatcher for the given cell id
/*! \details If a dispatcher for the cell id does not exist it will be created.
 */
Teuchos::RCP<SourceEventDispatcher>& SourceEventDispatcherDB::getDispatcher(
		  const Geometry::ModuleInterface::InternalCellHandle cell_id )
{
  DispatcherMap::iterator it = 
    SourceEventDispatcherDB::master_map.find( cell_id );

  if( it != SourceEventDispatcherDB::master_map.end() )
    return it->second;
  else
  {
    SourceEventDispatcherDB::master_map[cell_id] = 
      Teuchos::rcp( new SourceEventDispatcher( cell_id ) );

    return SourceEventDispatcherDB::master_map[cell_id];
  }
}

// Attach an observer to the appropriate dispatcher
void SourceEventDispatcherDB::attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const Estimator::idType estimator_id,
		      const Teuchos::RCP<SourceEventObserver>& observer )
{
  SourceEventDispatcherDB::getDispatcher( cell_id )->attachObserver( 
								 estimator_id,
								 observer );
}

// Detach the observer from the appropriate dispatcher
void SourceEventDispatcherDB::detachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const Estimator::idType estimator_id )
{
  SourceEventDispatcherDB::getDispatcher( cell_id )->detachObserver( 
								estimator_id );
}

// Detach the observer from all dispatchers
void SourceEventDispatcherDB::detachObserver( 
					 const Estimator::idType estimator_id )
{
  DispatcherMap::iterator it = SourceEventDispatcherDB::master_map.begin();

  while( it != SourceEventDispatcherDB::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_SourceEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
