//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCollidingInCellEventObserver.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event observer base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleCollidingInCellEventObserver.hpp"
#include "Facemc_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleCollidingInCellEventObserver::ParticleCollidingInCellEventObserver(
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
    this->registerWithParticleCollidingInCellEventDispatcher( cell_ids );
}

// Destructor
ParticleCollidingInCellEventObserver::~ParticleCollidingInCellEventObserver()
{
  if( d_is_registered )
      ParticleCollidingInCellEventDispatcherDB::detachObserver( d_id );
}

// Register the observer
void ParticleCollidingInCellEventObserver::registerWithParticleCollidingInCellEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids )
{
  if( !d_is_registered )
  {
    for( unsigned i = 0u; i < cell_ids.size(); ++i )
    {
      ParticleCollidingInCellEventDispatcherDB::attachObserver( cell_ids[i],
								d_id,
								this );
    }
    
    d_is_registered = true;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventObserver.cpp
//---------------------------------------------------------------------------//
