//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleSubtrackEndingInCellEventDispatcher::ParticleSubtrackEndingInCellEventDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : ParticleEventDispatcher<Geometry::ModuleTraits::InternalCellHandle,
			    ParticleSubtrackEndingInCellEventObserver>(cell_id)
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleSubtrackEndingInCellEventDispatcher::dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
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
// end MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
