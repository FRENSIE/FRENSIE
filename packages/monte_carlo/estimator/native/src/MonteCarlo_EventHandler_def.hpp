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
#include <boost/mpl/contains.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverRegistrationHelpers.hpp"
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
  event_handler.registerObserver( 
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
  event_handler.registerGlobalObserver( 
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
  
// Register an observer with the appropriate particle colliding in cell event
// dispatcher
template<typename Observer, typename EntityHandle>
void EventHandler::registerObserver( 
                               const std::shared_ptr<Observer>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids,
                               ParticleCollidingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the correct event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCollidingInCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleCollidingInCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleCollidingInCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_colliding_in_cell_event_dispatcher.attachObserver(
                                                             entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

// Register an observer with the appropriate particle crossing surface event
// dispatcher
template<typename Observer, typename EntityHandle>
void EventHandler::registerObserver( 
                               const std::shared_ptr<Observer>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids,
                               ParticleCrossingSurfaceEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCrossingSurfaceEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleCrossingSurfaceEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleCrossingSurfaceEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_crossing_surface_event_dispatcher.attachObserver(
                                                             entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

// Register an observer with the appropriate particle entering cell event
// dispatcher
template<typename Observer, typename EntityHandle>
void EventHandler::registerObserver( 
                                const std::shared_ptr<Observer>& observer,
                                const Teuchos::Array<EntityHandle>& entity_ids,
                                ParticleEnteringCellEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleEnteringCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleEnteringCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleEnteringCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_entering_cell_event_dispatcher.attachObserver(entity_ids[i],
							     observer->getId(),
                                                             observer_base );
  }
}

// Register an observer with the appropriate particle leaving cell event
// dispatcher
template<typename Observer, typename EntityHandle>
void EventHandler::registerObserver( 
                                const std::shared_ptr<Observer>& observer,
                                const Teuchos::Array<EntityHandle>& entity_ids,
                                ParticleLeavingCellEventObserver::EventTag )
{
  // Make sure the observer has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleLeavingCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleLeavingCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleLeavingCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_leaving_cell_event_dispatcher.attachObserver( entity_ids[i],
                                                             observer->getId(),
                                                             observer_base );
  }
}

// Register an observer with the appropriate particle subtrack ending in cell
// event dispatcher
template<typename Observer, typename EntityHandle>
void EventHandler::registerObserver( 
                          const std::shared_ptr<Observer>& observer,
                          const Teuchos::Array<EntityHandle>& entity_ids,
                          ParticleSubtrackEndingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingInCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleSubtrackEndingInCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleSubtrackEndingInCellEventObserver>( 
								    observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_subtrack_ending_in_cell_event_dispatcher.attachObserver(
							     entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

// Register a global observer with the appropriate particle subtrack ending
// global event dispatcher
template<typename Observer>
void EventHandler::registerGlobalObserver( 
			 const std::shared_ptr<Observer>& observer,
			 ParticleSubtrackEndingGlobalEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingGlobalEventObserver::EventTag>::value));

  std::shared_ptr<ParticleSubtrackEndingGlobalEventObserver> observer_base = 
    observer;

  d_particle_subtrack_ending_global_event_dispatcher.attachObserver(
							     observer->getId(),
							     observer_base );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EVENT_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler_def.hpp
//---------------------------------------------------------------------------//
