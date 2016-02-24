//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventDispatcherDB_def.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher database base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DB_DEF_HPP
#define MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DB_DEF_HPP

namespace MonteCarlo{

// Initialize the static member data
template<typename Dispatcher>
typename ParticleEventDispatcherDB<Dispatcher>::DispatcherMap
ParticleEventDispatcherDB<Dispatcher>::master_map;

// Get the appropriate dispatcher for the given cell id
template<typename Dispatcher>
inline Dispatcher& 
ParticleEventDispatcherDB<Dispatcher>::getDispatcher(
		        const typename Dispatcher::EntityHandleType entity_id )
{
  typename DispatcherMap::iterator it = 
    ParticleEventDispatcherDB<Dispatcher>::master_map.find( entity_id );

  if( it != ParticleEventDispatcherDB<Dispatcher>::master_map.end() )
    return *(it->second);
  else
  {
    std::shared_ptr<Dispatcher>& new_dispatcher = 
      ParticleEventDispatcherDB<Dispatcher>::master_map[entity_id];

    new_dispatcher.reset( new Dispatcher( entity_id ) );

    return *new_dispatcher;
  }
}

// Attach an observer to the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcherDB<Dispatcher>::attachObserver(
	   const typename Dispatcher::EntityHandleType entity_id,
           const ModuleTraits::InternalEventObserverHandle estimator_id,
           const std::shared_ptr<typename Dispatcher::ObserverType>& observer )
{
  ParticleEventDispatcherDB<Dispatcher>::getDispatcher(entity_id).attachObserver(
								  estimator_id,
								  observer );
}
  
// Detach an observer from the appropriate dispatcher
template<typename Dispatcher>
inline void ParticleEventDispatcherDB<Dispatcher>::detachObserver(
		 const typename Dispatcher::EntityHandleType entity_id,
		 const ModuleTraits::InternalEventObserverHandle estimator_id )
{
  ParticleEventDispatcherDB<Dispatcher>::getDispatcher(entity_id).detachObserver( 
								estimator_id );
}

// Detach the observer from all dispatchers
template<typename Dispatcher>
inline void ParticleEventDispatcherDB<Dispatcher>::detachObserver(
		 const ModuleTraits::InternalEventObserverHandle estimator_id )
{
  typename DispatcherMap::iterator it = 
    ParticleEventDispatcherDB<Dispatcher>::master_map.begin();

  while( it != ParticleEventDispatcherDB<Dispatcher>::master_map.end() )
  {
    it->second->detachObserver( estimator_id );

    ++it;
  }
}

// Get the master map
template<typename Dispatcher>
inline typename ParticleEventDispatcherDB<Dispatcher>::DispatcherMap&
ParticleEventDispatcherDB<Dispatcher>::master_disp_map()
{
  return ParticleEventDispatcherDB<Dispatcher>::master_map;
}

// Detach all observers
template<typename Dispatcher>
void ParticleEventDispatcherDB<Dispatcher>::detachAllObservers()
{
  ParticleEventDispatcherDB<Dispatcher>::master_map.clear();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_DB_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcherDB_def.hpp
//---------------------------------------------------------------------------//
