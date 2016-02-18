//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher database base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_EVENT_DISPATCHER_DB_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

namespace MonteCarlo{

//! The particle event dispatcher database base class
template<typename Dispatcher>
class ParticleEventDispatcherDB
{
  
public:

  //! Get the appropriate dispatcher for the given cell id
  static Teuchos::RCP<Dispatcher>& getDispatcher(
		       const typename Dispatcher::EntityHandleType entity_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
	  const typename Dispatcher::EntityHandleType entity_id,
          const ModuleTraits::InternalEventObserverHandle estimator_id,
	  const std::shared_ptr<typename Dispatcher::ObserverType>& observer );
  
  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		const typename Dispatcher::EntityHandleType entity_id,
		const ModuleTraits::InternalEventObserverHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		const ModuleTraits::InternalEventObserverHandle estimator_id );

  //! Detach all observers
  static void detachAllObservers();

protected:
  
  // Typedef for the dispatcher map
  typedef typename boost::unordered_map<typename Dispatcher::EntityHandleType,
					Teuchos::RCP<Dispatcher> >
  DispatcherMap;

  //! Get the master map
  static DispatcherMap& master_disp_map();

private:

  // Constructor
  ParticleEventDispatcherDB();

  static DispatcherMap master_map;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleEventDispatcherDB_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_PARTICLE_EVENT_DISPATCHER_DP_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
