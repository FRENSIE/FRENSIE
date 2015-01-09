//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGlobalEventDispatcher.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle global event dispatcher base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

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

  //! Constructor
  ParticleGlobalEventDispatcher()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleGlobalEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver( const ModuleTraits::InternalEstimatorHandle id,
		       Teuchos::RCP<Observer>& observer );

  //! Detach an observer from the dispatcher
  EntityHandle getId() const;

  //! Get the number of attached observers
  unsigned getNumberOfObservers() const;

protected:

  // The observer map
  typedef typename boost::unordered_map<ModuleTraits::InternalEstimatorHandle,
					Teuchos::RCP<Observer> > ObserverIdMap;

  // Get the oberver map
  ObserverIdMap& observer_id_map();

private:

  ObserverIdMap d_observer_map;
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
