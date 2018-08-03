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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename Observer>
ParticleGlobalEventDispatcher<Observer>::ParticleGlobalEventDispatcher()
  : d_observer_sets()
{ /* ... */ }

// Attach an observer to the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::attachObserver(
                                  const std::set<ParticleType>& particle_types,
                                  const std::shared_ptr<Observer>& observer )
{
  for( auto&& particle_type : particle_types )
    d_observer_sets[particle_type].insert( observer );
}
  
// Attach an observer to the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::attachObserver(
                                    const std::shared_ptr<Observer>& observer )
{
  for( int i = ParticleType_START; i < ParticleType_END; ++i )
    d_observer_sets[i].insert( observer );
}

// Detach an observer from the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::detachObserver(
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

// Get the number of attached observers
template<typename Observer>
size_t ParticleGlobalEventDispatcher<Observer>::getNumberOfObservers(
                                       const ParticleType particle_type ) const
{
  typename std::map<int,ObserverSet>::const_iterator
    particle_observer_sets_it = d_observer_sets.find( particle_type );

  if( particle_observer_sets_it != d_observer_sets.end() )
    return particle_observer_sets_it->second.size();
  else
    return 0;
}

// Detach an observer from the dispatcher
template<typename Observer>
void ParticleGlobalEventDispatcher<Observer>::detachAllObservers()
{
  d_observer_sets.clear();
}

// Check if there is an observer set for the particle type
template<typename Observer>
inline bool ParticleGlobalEventDispatcher<Observer>::hasObserverSet(
                                       const ParticleType particle_type ) const
{
  return d_observer_sets.find( particle_type ) != d_observer_sets.end();
}

// Get the observer id map
template<typename Observer>
inline auto ParticleGlobalEventDispatcher<Observer>::getObserverSet(
                             const ParticleType particle_type ) -> ObserverSet&
{
  return d_observer_sets[particle_type];
}

// Serialize the observer
template<typename Observer>
template<typename Archive>
void ParticleGlobalEventDispatcher<Observer>::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_observer_sets );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGlobalEventDispatcher_def.hpp
//---------------------------------------------------------------------------//
