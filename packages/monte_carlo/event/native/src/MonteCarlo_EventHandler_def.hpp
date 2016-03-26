//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler_def.hpp
//! \author Alex Robinson
//! \brief  Event handler class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_HANDLER_DEF_HPP
#define MONTE_CARLO_ESTIMATOR_HANDLER_DEF_HPP

// Boost Includes
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Add an entity observer to the handler
/*! \details The observer will be registered with the appropriate dispatchers.
 * It is important to pass a pointer to the class that maintains the event
 * tags associated with the observer (so that automatic dispatcher 
 * registration can occur).
 */
template<typename ObserverType, typename EntityHandle>
void EventHandler::addEntityEventObserver( 
                               const std::shared_ptr<ObserverType>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{
  // Make sure the observer is valid
  testPrecondition( observer.get() );
  // Make sure at least one entity id is specified
  testPrecondition( entity_ids.size() > 0 );
  // Make sure the observer id is unique
  testPrecondition( d_particle_history_observers.find( observer->getId() ) ==
                    d_particle_history_observers.end() );
  
  // Register the observer with the particle event dispatchers
  this->registerObserver( observer, entity_ids );

  // Add the observer to the map
  d_particle_history_observers[observer->getId()] = observer;
}

// Add a global observer to the handler
/*! \details The estimator will be registered with the appropriate dispatchers.
 */
template<typename ObserverType>
void EventHandler::addGlobalEventObserver( 
                                const std::shared_ptr<ObserverType>& observer )
{
  // Make sure observer is valid
  testPrecondition( observer.get() );
  // Make sure the observer id is unique
  testPrecondition( d_particle_history_observers.find( observer->getId() ) ==
                    d_particle_history_observers.end() );
 
  // Register the estimator with the particle global event dispatchers
  this->registerGlobalObserver( observer );

  // Add the estimator to the master list
  d_particle_history_observers[observer->getId()] = observer;
}

// Register an observer with the appropriate dispatcher
template<typename Observer, typename EntityHandle>
void EventHandler::registerObserver( 
                               const std::shared_ptr<Observer>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;

  ObserverRegistrationHelper<BeginEventTagIterator,
                             EndEventTagIterator>::registerObserverWithTag(
                                                                  *this,
								  observer,
								  entity_ids );
}

// Register a global observer with the appropriate dispatcher
template<typename Observer>
void EventHandler::registerGlobalObserver( 
                                    const std::shared_ptr<Observer>& observer )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;

  ObserverRegistrationHelper<BeginEventTagIterator,
			   EndEventTagIterator>::registerGlobalObserverWithTag(
                                                                    *this,
								    observer );
}

// Register the obs. with dispatchers associated with BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer, typename EntityHandle>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                               EventHandler& event_handler,
                               const std::shared_ptr<Observer>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{
  event_handler.registerObserverWithTag( 
                   observer,
                   entity_ids,
                   typename boost::mpl::deref<BeginEventTagIterator>::type() );

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,
                             EndEventTagIterator>::registerObserverWithTag(
                                                                 event_handler,
                                                                 observer,
                                                                 entity_ids );
}

// End registration iteration
template<typename EndEventTagIterator>
template<typename Observer, typename EntityHandle>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                               EventHandler& event_handler,
			       const std::shared_ptr<Observer>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids )
{ /* ... */ }

// Register the global observer with the global dispatcher associated with
// BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerGlobalObserverWithTag( 
                                    EventHandler& event_handler,
                                    const std::shared_ptr<Observer>& observer )
{
  event_handler.registerGlobalObserverWithTag( 
                   observer,
                   typename boost::mpl::deref<BeginEventTagIterator>::type() );

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,
			     EndEventTagIterator>::registerGlobalObserverWithTag(
                                                                 event_handler,
                                                                 observer );
}

// End global registration iteration
template<typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerGlobalObserverWithTag( 
                                     EventHandler& event_handler,
                                     const std::shared_ptr<Observer>& observer)
{ /* ... */ }

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EVENT_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler_def.hpp
//---------------------------------------------------------------------------//
