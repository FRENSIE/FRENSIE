//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
ParticleSubtrackEndingInCellEventLocalDispatcher::ParticleSubtrackEndingInCellEventLocalDispatcher(
		     const Geometry::Model::EntityId cell_id )
  : ParticleEventLocalDispatcher<Geometry::Model::EntityId,
                                 ParticleSubtrackEndingInCellEventObserver>(cell_id)
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleSubtrackEndingInCellEventLocalDispatcher::dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::Model::EntityId cell_of_subtrack,
	     const double track_length )
{
  // Make sure the cell being collided with is valid
  testPrecondition( cell_of_subtrack == this->getId() );

  ObserverIdMap::iterator it = observer_id_map().begin();

  while( it != observer_id_map().end() )
  {
    it->second->updateFromParticleSubtrackEndingInCellEvent(
							    particle,
							    cell_of_subtrack,
							    track_length );

    ++it;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
