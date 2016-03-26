//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventDispatcher_def.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher database base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DEF_HPP
#define MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DEF_HPP

namespace MonteCarlo{

// Constructor
template<typename Dispatcher>
ParticleEventDispatcher<Dispatcher>::ParticleEventDispatcher()
  : d_dispatcher_map()
{ /* ... */ }

// Get the appropriate local dispatcher for the given entity id
template<typename Dispatcher>
inline Dispatcher& 
ParticleEventDispatcher<Dispatcher>::getLocalDispatcher(
		        const typename Dispatcher::EntityHandleType entity_id )
{
  typename DispatcherMap::iterator it = d_dispatcher_map.find( entity_id );

  if( it != d_dispatcher_map.end() )
    return *(it->second);
  else
  {
    std::shared_ptr<Dispatcher>& new_dispatcher = 
      d_dispatcher_map[entity_id];

    new_dispatcher.reset( new Dispatcher( entity_id ) );

    return *new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::attachObserver(
	   const typename Dispatcher::EntityHandleType entity_id,
           const ModuleTraits::InternalEventObserverHandle observer_id,
           const std::shared_ptr<typename Dispatcher::ObserverType>& observer )
{
  this->getLocalDispatcher( entity_id ).attachObserver( observer_id, observer);
}
  
// Detach an observer from the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::detachObserver(
		 const typename Dispatcher::EntityHandleType entity_id,
		 const ModuleTraits::InternalEventObserverHandle observer_id )
{
  this->getLocalDispatcher( entity_id ).detachObserver( observer_id );
}

// Detach the observer from all dispatchers
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::detachObserver(
		 const ModuleTraits::InternalEventObserverHandle observer_id )
{
  typename DispatcherMap::iterator it = d_dispatcher_map.begin();

  while( it != d_dispatcher_map.end() )
  {
    it->second->detachObserver( observer_id );

    ++it;
  }
}

// Get the dispatcher map
template<typename Dispatcher>
inline typename ParticleEventDispatcher<Dispatcher>::DispatcherMap&
ParticleEventDispatcher<Dispatcher>::dispatcher_map()
{
  return d_dispatcher_map;
}

// Detach all observers
template<typename Dispatcher>
void ParticleEventDispatcher<Dispatcher>::detachAllObservers()
{
  d_dispatcher_map.clear();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcher_def.hpp
//---------------------------------------------------------------------------//
