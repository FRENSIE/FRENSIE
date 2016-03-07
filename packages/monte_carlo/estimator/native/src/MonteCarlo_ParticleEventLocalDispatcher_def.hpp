//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventLocalDispatcher_def.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher base class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_DEF_HPP
#define MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename EntityHandle, typename Observer>
ParticleEventLocalDispatcher<EntityHandle,Observer>::ParticleEventLocalDispatcher(
						 const EntityHandle entity_id )
  : d_entity_id( entity_id )
{ /* ... */ }

// Attach an observer to the dispatcher
template<typename EntityHandle, typename Observer>
void ParticleEventLocalDispatcher<EntityHandle,Observer>::attachObserver(
			    const ModuleTraits::InternalEventObserverHandle id,
                            const std::shared_ptr<Observer>& observer )
{
  // Make sure the observer has not been attached yet
  testPrecondition( d_observer_map.find( id ) == d_observer_map.end() );
  
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
template<typename EntityHandle, typename Observer>
void ParticleEventLocalDispatcher<EntityHandle,Observer>::detachObserver(
			   const ModuleTraits::InternalEventObserverHandle id )
{
  d_observer_map.erase( id );
}

// Get the entity id corresponding to this particle event dispatcher
template<typename EntityHandle, typename Observer>
inline EntityHandle 
ParticleEventLocalDispatcher<EntityHandle,Observer>::getId() const
{
  return d_entity_id;
}

// Get the number of attached observers
template<typename EntityHandle, typename Observer>
unsigned 
ParticleEventLocalDispatcher<EntityHandle,Observer>::getNumberOfObservers() const
{
  return d_observer_map.size();
}

// Get the observer map
template<typename EntityHandle, typename Observer>
inline typename ParticleEventLocalDispatcher<EntityHandle,Observer>::ObserverIdMap&
ParticleEventLocalDispatcher<EntityHandle,Observer>::observer_id_map()
{
  return d_observer_map;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventLocalDispatcher_def.hpp
//---------------------------------------------------------------------------//
