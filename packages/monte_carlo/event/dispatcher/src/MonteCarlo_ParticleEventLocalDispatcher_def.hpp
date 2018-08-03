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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename Observer>
ParticleEventLocalDispatcher<Observer>::ParticleEventLocalDispatcher()
{ /* ... */ }

// Constructor
template<typename Observer>
ParticleEventLocalDispatcher<Observer>::ParticleEventLocalDispatcher(
						     const uint64_t entity_id )
  : d_entity_id( entity_id ),
    d_observer_sets()
{ /* ... */ }

// Attach an observer to the dispatcher
template<typename Observer>
void ParticleEventLocalDispatcher<Observer>::attachObserver(
                                  const std::set<ParticleType>& particle_types,
                                  const std::shared_ptr<Observer>& observer )
{
  for( auto&& particle_type : particle_types )
    d_observer_sets[particle_type].insert( observer );
}

// Attach an observer to the dispatcher
template<typename Observer>
void ParticleEventLocalDispatcher<Observer>::attachObserver(
                                    const std::shared_ptr<Observer>& observer )
{
  for( int i = ParticleType_START; i < ParticleType_END; ++i )
    d_observer_sets[i].insert( observer );
}

// Detach an observer from the dispatcher
template<typename Observer>
void ParticleEventLocalDispatcher<Observer>::detachObserver(
                                    const std::shared_ptr<Observer>& observer )
{
  typename std::map<int,ObserverSet>::iterator particle_observer_sets_it =
    d_observer_sets.begin();

  while( particle_observer_sets_it != d_observer_sets.end() )
  {
    particle_observer_sets_it->second.erase( observer );

    ++particle_observer_sets_it;
  }
}

// Detach all observers
template<typename Observer>
void ParticleEventLocalDispatcher<Observer>::detachAllObservers()
{
  d_observer_sets.clear();
}

// Get the entity id corresponding to this particle event dispatcher
template<typename Observer>
inline uint64_t ParticleEventLocalDispatcher<Observer>::getEntityId() const
{
  return d_entity_id;
}

// Get the number of attached observers
template<typename Observer>
size_t ParticleEventLocalDispatcher<Observer>::getNumberOfObservers(
                                       const ParticleType particle_type ) const
{
  typename std::map<int,ObserverSet>::const_iterator
    particle_observer_sets_it = d_observer_sets.find( particle_type );

  if( particle_observer_sets_it != d_observer_sets.end() )
    return particle_observer_sets_it->second.size();
  else
    return 0;
}

// Check if there is an observer set for the particle type
template<typename Observer>
inline bool ParticleEventLocalDispatcher<Observer>::hasObserverSet(
                                       const ParticleType particle_type ) const
{
  return d_observer_sets.find( particle_type ) != d_observer_sets.end();
}

// Get the observer map
template<typename Observer>
inline auto ParticleEventLocalDispatcher<Observer>::getObserverSet(
                            const ParticleType particle_types ) -> ObserverSet&
{
  return d_observer_sets[particle_types];
}

// Serialize the observer
template<typename Observer>
template<typename Archive>
void ParticleEventLocalDispatcher<Observer>::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_entity_id );
  ar & BOOST_SERIALIZATION_NVP( d_observer_sets );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventLocalDispatcher_def.hpp
//---------------------------------------------------------------------------//
