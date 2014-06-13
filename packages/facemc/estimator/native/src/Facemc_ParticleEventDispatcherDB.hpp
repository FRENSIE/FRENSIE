//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher database base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

namespace Facemc{

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
		const ModuleTraits::InternalEstimatorHandle estimator_id,
		Teuchos::RCP<typename Dispatcher::ObserverType>& observer );
  
  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		    const typename Dispatcher::EntityHandleType entity_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

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

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Facemc_ParticleEventDispatcherDB_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_PARTICLE_EVENT_DISPATCHER_DP_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
