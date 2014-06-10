//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleGenerationEventObserver.hpp
//! \author Alex Robinson
//! \brief  Source event observer base class
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_ParticleGenerationEventObserver.hpp"
#include "Facemc_ParticleGenerationEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleGenerationEventObserver::ParticleGenerationEventObserver( 
   const ModuleTraits::InternalEstimatorHandle id,
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
   const bool auto_register_with_dispatchers )
  : d_id( id ),
    d_is_registered( false )
{
  // Make sure at least one cell id has been specified
  testPrecondition( cell_ids.size() > 0 );
  
  // Attach this observer to the source event dispatcher corresponding to
  // each cell id if requested
  if( auto_register_with_dispatchers )
    this->registerWithParticleGenerationEventDispatcher( cell_ids );
}

//! Register the observer
void 
ParticleGenerationEventObserver::registerWithParticleGenerationEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids )
{
  if( !d_is_registered )
  {
    for( unsigned i = 0u; i < cell_ids.size(); ++i )
    {
      ParticleGenerationEventDispatcherDB::attachObserver( cell_ids[i], 
							   d_id, 
							   this );
    }
    
    d_is_registered = true;
  }
}

// Destructor
ParticleGenerationEventObserver::~ParticleGenerationEventObserver()
{
  if( d_is_registered )
    ParticleGenerationEventDispatcherDB::detachObserver( d_id );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleGenerationEventObserver.hpp
//---------------------------------------------------------------------------//
