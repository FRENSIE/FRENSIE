//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventObserver.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event observer base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleCrossingSurfaceEventObserver.hpp"
#include "Facemc_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleCrossingSurfaceEventObserver::ParticleCrossingSurfaceEventObserver(
           const ModuleTraits::InternalEstimatorHandle id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
           const bool auto_register_with_dispatchers )
  : d_id( id ),
    d_is_registered( false )
{
  // Make sure at least one surface id has been specified
  testPrecondition( surface_ids.size() > 0 );
  
  // Attach this observer to the source event dispatcher corresponding to
  // each surface id if requested
  if( auto_register_with_dispatchers )
    this->registerWithParticleCrossingSurfaceEventDispatcher( surface_ids );
}

// Destructor
ParticleCrossingSurfaceEventObserver::~ParticleCrossingSurfaceEventObserver()
{
  if( d_is_registered )
    ParticleCrossingSurfaceEventDispatcherDB::detachObserver( d_id );
}

// Register the observer
void ParticleCrossingSurfaceEventObserver::registerWithParticleCrossingSurfaceEventDispatcher(
	   const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids )
{
  if( !d_is_registered )
  {
    for( unsigned i = 0u; i < surface_ids.size(); ++i )
    {
      ParticleCrossingSurfaceEventDispatcherDB::attachObserver( surface_ids[i],
								d_id,
								this );
    }

    d_is_registered = true;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventObserver.cpp
//---------------------------------------------------------------------------//
