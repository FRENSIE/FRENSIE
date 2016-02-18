//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventDispatcher_def.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher base class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_EVENT_DISPATCHER_DEF_HPP
#define FACEMC_PARTICLE_EVENT_DISPATCHER_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename EntityHandle, typename Observer>
ParticleEventDispatcher<EntityHandle,Observer>::ParticleEventDispatcher(
						 const EntityHandle entity_id )
  : d_entity_id( entity_id )
{ /* ... */ }

// Attach an observer to the dispatcher
template<typename EntityHandle, typename Observer>
void ParticleEventDispatcher<EntityHandle,Observer>::attachObserver(
			    const ModuleTraits::InternalEventObserverHandle id,
                            Teuchos::RCP<Observer>& observer )
{
  // Make sure the observer has not been attached yet
  testPrecondition( d_observer_map.find( id ) == d_observer_map.end() );
  
  if( d_observer_map.find( id ) == d_observer_map.end() )
    d_observer_map[id] = observer;
}

// Detach an observer from the dispatcher
template<typename EntityHandle, typename Observer>
void ParticleEventDispatcher<EntityHandle,Observer>::detachObserver(
			   const ModuleTraits::InternalEventObserverHandle id )
{
  d_observer_map.erase( id );
}

// Get the entity id corresponding to this particle event dispatcher
template<typename EntityHandle, typename Observer>
inline EntityHandle 
ParticleEventDispatcher<EntityHandle,Observer>::getId() const
{
  return d_entity_id;
}

// Get the number of attached observers
template<typename EntityHandle, typename Observer>
unsigned 
ParticleEventDispatcher<EntityHandle,Observer>::getNumberOfObservers() const
{
  return d_observer_map.size();
}

// Get the observer map
template<typename EntityHandle, typename Observer>
inline typename ParticleEventDispatcher<EntityHandle,Observer>::ObserverIdMap&
ParticleEventDispatcher<EntityHandle,Observer>::observer_id_map()
{
  return d_observer_map;
}

} // end MonteCarlo namespace

#endif // end FACEMC_PARTICLE_EVENT_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcher_def.hpp
//---------------------------------------------------------------------------//
