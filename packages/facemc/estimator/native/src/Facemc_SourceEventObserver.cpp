//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceEventObserver.hpp
//! \author Alex Robinson
//! \brief  Source event observer base class
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_SourceEventObserver.hpp"
#include "Facemc_SourceEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
SourceEventObserver::SourceEventObserver( 
   const Estimator::idType id,
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids )
  : d_id( id )
{
  // Make sure at least one cell id has been specified
  testPrecondition( cell_ids.size() > 0 );
  
  // Attach this observer to the source event dispatcher corresponding to
  // each cell id
  for( unsigned i = 0u; i < cell_ids.size(); ++i )
    SourceEventDispatcherDB::attachObserver( cell_ids[i], id, this );
}

// Destructor
SourceEventObserver::~SourceEventObserver()
{
  SourceEventDispatcherDB::detachObserver( estimator_id );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_SourceEventObserver.hpp
//---------------------------------------------------------------------------//
