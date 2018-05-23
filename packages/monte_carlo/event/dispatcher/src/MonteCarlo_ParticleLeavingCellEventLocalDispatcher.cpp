//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleLeavingCellEventLocalDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleLeavingCellEventLocalDispatcher::ParticleLeavingCellEventLocalDispatcher(
		     const Geometry::ModuleTraits::InternalCellHandle cell_id )
  : ParticleEventLocalDispatcher<Geometry::ModuleTraits::InternalCellHandle,
                                 ParticleLeavingCellEventObserver>( cell_id )
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleLeavingCellEventLocalDispatcher::dispatchParticleLeavingCellEvent(
	        const ParticleState& particle,
	        const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  // Make sure the cell being entered is valid
  testPrecondition( cell_leaving == this->getId() );

  ObserverIdMap::iterator it = observer_id_map().begin();

  while( it != observer_id_map().end() )
  {
    it->second->updateFromParticleLeavingCellEvent( particle, cell_leaving );

    ++it;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
