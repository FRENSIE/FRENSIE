//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverRegistrationHelpers.hpp
//! \author Alex Robinson
//! \brief  Event dispatcher helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_OBSERVER_REGISTRATION_HELPERS_HPP
#define FACEMC_OBSERVER_REGISTRATION_HELPERS_HPP

// Boost Includes
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/contains.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleLeavingCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"

namespace MonteCarlo{

//! Struct for iterating through all observer event tags
template<typename BeginEventTagIterator, typename EndEventTagIterator>
struct ObserverRegistrationHelper
{
  //! Register the observer with dispatchers associated with BeginEventTag tag
  template<typename Observer, typename EntityHandle>
  static void registerObserverWithTag(
			      Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids );

  /*! Register the global observer with the global dispatcher associated with
   * BeginEventTag tag
   */
  template<typename Observer>
  static void registerGlobalObserverWithTag( Teuchos::RCP<Observer>& observer);
};

//! Struct for ending iteration through all event tags
template<typename EndEventTagIterator>
struct ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>
{
  //! End registration iteration
  template<typename Observer, typename EntityHandle>
  static void registerObserverWithTag(
			      Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids );

  //! End global registration iteration
  template<typename Observer>
  static void registerGlobalObserverWithTag( Teuchos::RCP<Observer>& observer);
};

//! Register an observer with the appropriate dispatcher
template<typename Observer, typename EntityHandle>
void registerObserver( Teuchos::RCP<Observer>& observer,
		       const Teuchos::Array<EntityHandle>& entity_ids );

//! Register a global observer with the appropriate dispatcher
template<typename Observer>
void registerGlobalObserver( Teuchos::RCP<Observer>& observer );

/*! Register an observer with the appropriate particle colliding in cell event 
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
void registerObserver( Teuchos::RCP<Observer>& observer,
		       const Teuchos::Array<EntityHandle>& entity_ids,
		       ParticleCollidingInCellEventObserver::EventTag );

/*! Register an observer with the appropriate particle crossing surface event
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleCrossingSurfaceEventObserver::EventTag );

/*! Register an observer with the appropriate particle entering cell event
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleEnteringCellEventObserver::EventTag );

/*! Register an observer with the appropriate particle leaving cell event
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleLeavingCellEventObserver::EventTag );

/*! Register an observer with the appropriate particle subtrack ending in cell
 * event dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( 
			 Teuchos::RCP<Observer>& observer,
			 const Teuchos::Array<EntityHandle>& entity_ids,
			 ParticleSubtrackEndingInCellEventObserver::EventTag );

/*! Register a global observer with the appropraite particle subtrack ending
 * global event dispatcher
 */
template<typename Observer>
inline void registerGlobalObserver( 
			 Teuchos::RCP<Observer>& observer,
			 ParticleSubtrackEndingGlobalEventObserver::EventTag );

} // end MonteCarlo namespace

//! Macro for simple registering of observers
#define REGISTER_OBSERVER_WITH_DISPATCHERS( observer, entity_ids ) \
  MonteCarlo::registerObserver( observer, entity_ids ) 

//! Macro for simple registering of global observers
#define REGISTER_GLOBAL_OBSERVER_WITH_DISPATCHERS( observer ) \
  MonteCarlo::registerGlobalObserver( observer )

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ObserverRegistrationHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_OBSERVER_REGISTRATION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverRegistrationHelpers.hpp
//---------------------------------------------------------------------------//
