//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

//! The particle event dispatcher base class
template<typename EntityHandle, typename Observer>
class ParticleEventLocalDispatcher
{

public:

  //! Typedef for EntityHandle type
  typedef EntityHandle EntityHandleType;
  
  //! Typedef for Observer type
  typedef Observer ObserverType;

  //! Constructor
  ParticleEventLocalDispatcher( const EntityHandle entity_id );

  //! Destructor
  virtual ~ParticleEventLocalDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver( const ModuleTraits::InternalEventObserverHandle id,
		       const std::shared_ptr<Observer>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const ModuleTraits::InternalEventObserverHandle id );

  //! Get the entity id corresponding to this particle event dispatcher
  EntityHandle getId() const;

  //! Get the number of attached observers
  unsigned getNumberOfObservers() const;

protected:

  // The observer map
  typedef typename boost::unordered_map<ModuleTraits::InternalEventObserverHandle,
					std::shared_ptr<Observer> > ObserverIdMap;


  // Get the observer map
  ObserverIdMap& observer_id_map();
  
private:

  // The entity id for which the particle event will be dispatched
  EntityHandle d_entity_id;

  ObserverIdMap d_observer_map;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleEventLocalDispatcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
