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
inline Dispatcher& ParticleEventDispatcher<Dispatcher>::getLocalDispatcher(
                                                     const uint64_t entity_id )
{
  typename DispatcherMap::iterator it = d_dispatcher_map.find( entity_id );

  if( it != d_dispatcher_map.end() )
    return *(it->second);
  else
  {
    std::unique_ptr<Dispatcher>& new_dispatcher =
      d_dispatcher_map[entity_id];

    new_dispatcher.reset( new Dispatcher( entity_id ) );

    return *new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::attachObserver(
	   const uint64_t entity_id,
           const std::set<ParticleType>& particle_types,
           const std::shared_ptr<typename Dispatcher::ObserverType>& observer )
{
  this->getLocalDispatcher( entity_id ).attachObserver( particle_types,
                                                        observer );
}

// Attach an observer to the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::attachObserver(
	   const uint64_t entity_id,
           const std::shared_ptr<typename Dispatcher::ObserverType>& observer )
{
  this->getLocalDispatcher( entity_id ).attachObserver( observer );
}

// Detach an observer from the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::detachObserver(
           const uint64_t entity_id,
           const std::shared_ptr<typename Dispatcher::ObserverType>& observer )
{
  this->getLocalDispatcher( entity_id ).detachObserver( observer );
}

// Detach the observer from all dispatchers
template<typename Dispatcher>
inline void ParticleEventDispatcher<Dispatcher>::detachObserver(
           const std::shared_ptr<typename Dispatcher::ObserverType>& observer )
{
  typename DispatcherMap::iterator it = d_dispatcher_map.begin();

  while( it != d_dispatcher_map.end() )
  {
    it->second->detachObserver( observer );

    ++it;
  }
}

// Detach all observers
template<typename Dispatcher>
void ParticleEventDispatcher<Dispatcher>::detachAllObservers()
{
  d_dispatcher_map.clear();
}

// Get the dispatcher map
template<typename Dispatcher>
inline auto ParticleEventDispatcher<Dispatcher>::getDispatcherMap() -> DispatcherMap&
{
  return d_dispatcher_map;
}

// Serialize the observer
template<typename Dispatcher>
template<typename Archive>
void ParticleEventDispatcher<Dispatcher>::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_dispatcher_map );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcher_def.hpp
//---------------------------------------------------------------------------//
