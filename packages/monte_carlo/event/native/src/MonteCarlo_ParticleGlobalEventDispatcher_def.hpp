//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGlobalEventDispatcher_def.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle global event dispatcher base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_DEF_HPP
#define MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename Observer>
ParticleGlobalEventDispatcher<Observer>::ParticleGlobalEventDispatcher()
  : d_observer_map()
{ /* ... */ }

// Attach an observer to the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::attachObserver(
			    const ModuleTraits::InternalEventObserverHandle id,
                            const std::shared_ptr<Observer>& observer  )
{
  // Make sure the observer has not been attached yet
  testPrecondition( d_observer_map.find( id ) == d_observer_map.end() );
  
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::detachObserver(
			   const ModuleTraits::InternalEventObserverHandle id )
{
  d_observer_map.erase( id );
}

// Get the number of attached observers
template<typename Observer>
unsigned ParticleGlobalEventDispatcher<Observer>::getNumberOfObservers()
{
  return d_observer_map.size();
}

// Detach an observer from the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::detachAllObservers()
{
  d_observer_map.clear();
}

// Get the observer id map
template<typename Observer>
typename ParticleGlobalEventDispatcher<Observer>::ObserverIdMap& 
ParticleGlobalEventDispatcher<Observer>::observer_id_map()
{
  return d_observer_map;
}


} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGlobalEventDispatcher_def.hpp
//---------------------------------------------------------------------------//
