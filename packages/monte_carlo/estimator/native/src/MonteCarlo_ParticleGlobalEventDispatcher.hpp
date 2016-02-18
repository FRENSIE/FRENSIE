//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGlobalEventDispatcher.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle global event dispatcher base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

//! The particle global event dispatcher base class
template<typename Observer>
class ParticleGlobalEventDispatcher
{

public:

  //! Typedef for Observer type
  typedef Observer ObserverType;

  //! Attach an observer to the dispatcher
  static void attachObserver( 
                            const ModuleTraits::InternalEventObserverHandle id,
                            const std::shared_ptr<Observer>& observer );

  //! Detach an observer from the dispatcher
  static void detachObserver( 
                          const ModuleTraits::InternalEventObserverHandle id );

  //! Detach all observers
  static void detachAllObservers();

  //! Get the number of attached observers
  static unsigned getNumberOfObservers();

protected:

  // The observer map
  typedef typename boost::unordered_map<ModuleTraits::InternalEventObserverHandle,
					std::shared_ptr<Observer> > ObserverIdMap;

  // Get the oberver map
  static ObserverIdMap& observer_id_map();

private:

  // Constructor
  ParticleGlobalEventDispatcher();

  static ObserverIdMap d_observer_map;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleGlobalEventDispatcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGlobalEventDispatcher.hpp
//---------------------------------------------------------------------------//
