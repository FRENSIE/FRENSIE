//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher database base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

namespace MonteCarlo{

//! The particle event dispatcher database base class
template<typename Dispatcher>
class ParticleEventDispatcher
{
  
public:

  // Constructor
  ParticleEventDispatcher();

  // Destructor
  virtual ~ParticleEventDispatcher()
  { /* ... */ }

  //! Get the appropriate local dispatcher for the given entity id
  Dispatcher& getLocalDispatcher(
		       const typename Dispatcher::EntityHandleType entity_id );

  //! Attach an observer to the appropriate dispatcher
  void attachObserver(
	  const typename Dispatcher::EntityHandleType entity_id,
          const ModuleTraits::InternalEventObserverHandle observer_id,
	  const std::shared_ptr<typename Dispatcher::ObserverType>& observer );
  
  //! Detach an observer from the appropriate local dispatcher
  void detachObserver(
		const typename Dispatcher::EntityHandleType entity_id,
		const ModuleTraits::InternalEventObserverHandle observer_id );

  //! Detach the observer from all local dispatchers
  void detachObserver(
		const ModuleTraits::InternalEventObserverHandle observer_id );

  //! Detach all observers
  void detachAllObservers();

protected:
  
  // Typedef for the dispatcher map
  typedef typename boost::unordered_map<typename Dispatcher::EntityHandleType,
					std::shared_ptr<Dispatcher> >
  DispatcherMap;

  //! Get the dispatcher map
  DispatcherMap& dispatcher_map();

private:

  DispatcherMap d_dispatcher_map;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleEventDispatcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcher.hpp
//---------------------------------------------------------------------------//
