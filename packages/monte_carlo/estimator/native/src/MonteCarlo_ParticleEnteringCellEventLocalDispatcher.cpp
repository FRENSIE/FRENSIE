//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleEnteringCellEventLocalDispatcher::ParticleEnteringCellEventLocalDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : ParticleEventLocalDispatcher<Geometry::ModuleTraits::InternalCellHandle,
                                 ParticleEnteringCellEventObserver>( cell_id )
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleEnteringCellEventLocalDispatcher::dispatchParticleEnteringCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  // Make sure the cell being entered is valid
  testPrecondition( cell_entering == this->getId() );

  ObserverIdMap::iterator it = observer_id_map().begin();

  while( it != observer_id_map().end() )
  {
    it->second->updateFromParticleEnteringCellEvent( particle, cell_entering );

    ++it;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
