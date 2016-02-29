//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending global event dispatcher
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleSubtrackEndingGlobalEventDispatcher::ParticleSubtrackEndingGlobalEventDispatcher()
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  ObserverIdMap::iterator it = this->observer_id_map().begin();

  while( it != this->observer_id_map().end() )
  {
    it->second->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                             start_point,
                                                             end_point );

    ++it;
  }
}

} // end namespace MonteCarlo

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.cpp
//---------------------------------------------------------------------------//
