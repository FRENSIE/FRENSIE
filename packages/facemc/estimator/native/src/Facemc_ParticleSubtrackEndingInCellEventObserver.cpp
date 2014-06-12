//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSubtrackEndingInCellEventObserver.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event observer base class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "Facemc_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
ParticleSubtrackEndingInCellEventObserver::ParticleSubtrackEndingInCellEventObserver(
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
    this->registerWithParticleSubtrackEndingInCellEventDispatcher( cell_ids );
}

// Destructor
ParticleSubtrackEndingInCellEventObserver::~ParticleSubtrackEndingInCellEventObserver()
{
  if( d_is_registered )
      ParticleSubtrackEndingInCellEventDispatcherDB::detachObserver( d_id );
}

// Register the observer
void ParticleSubtrackEndingInCellEventObserver::registerWithParticleSubtrackEndingInCellEventDispatcher(
   const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids )
{
  if( !d_is_registered )
  {
    for( unsigned i = 0u; i < cell_ids.size(); ++i )
    {
      ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
								   cell_ids[i],
								   d_id,
								   this );
    }
    
    d_is_registered = true;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSubtrackEndingInCellEventObserver.cpp
//---------------------------------------------------------------------------//
