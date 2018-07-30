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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Add an estimator to the handler
/*! \details The estimators will be registered with the appropriate 
 * dispatchers. It is important to pass a pointer to the class that maintains
 * the event tags associated with the observer (so that automatic dispatcher
 * registration can occur).
 */
template<typename EstimatorType>
void EventHandler::addEstimator( const std::shared_ptr<EstimatorType>& estimator )
{
  // Make sure the observer is valid
  testPrecondition( estimator.get() );
  // Make sure the observer id is unique
  testPrecondition( d_particle_history_observers.find( estimator ) ==
                    d_particle_history_observers.end() );

  EstimatorRegistrationHelper<EstimatorType>::registerEstimator( *this, estimator );

  // Add the observer to set
  d_particle_history_observers.insert( estimator );
}

// Struct for registering estimator
template<typename EstimatorType>
void EventHandler::EstimatorRegistrationHelper<EstimatorType>::registerEstimator(
                              EventHandler& event_handler,
                              const std::shared_ptr<EstimatorType>& estimator )
{
  std::set<uint64_t> entity_ids;

  estimator->getEntityIds( entity_ids );

  std::set<ParticleType> particle_types = estimator->getParticleTypes();

  event_handler.registerObserver( estimator, entity_ids, particle_types );
}

// Struct for registering estimator
template<typename T>
void EventHandler::EstimatorRegistrationHelper<MeshTrackLengthFluxEstimator<T> >::registerEstimator(
           EventHandler& event_handler,
           const std::shared_ptr<MeshTrackLengthFluxEstimator<T> >& estimator )
{
  std::set<ParticleType> particle_types = estimator->getParticleTypes();

  event_handler.registerGlobalObserver( estimator, particle_types );
}

// Register an observer with the appropriate dispatcher
template<typename Observer>
void EventHandler::registerObserver( const std::shared_ptr<Observer>& observer,
                                     const std::set<uint64_t>& entity_ids )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;

  ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                                                                  *this,
								  observer,
								  entity_ids );
}

// Register an observer with the appropriate dispatcher
template<typename Observer>
void EventHandler::registerObserver( const std::shared_ptr<Observer>& observer,
                                     const std::set<uint64_t>& entity_ids,
                                     const std::set<ParticleType>& particle_types )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;

  ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                                                              *this,
                                                              observer,
                                                              entity_ids,
                                                              particle_types );
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

  ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerGlobalObserverWithTag(
                                                                    *this,
								    observer );
}

// Register a global observer with the appropriate dispatcher
template<typename Observer>
void EventHandler::registerGlobalObserver(
                                 const std::shared_ptr<Observer>& observer,
                                 const std::set<ParticleType>& particle_types )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;

  ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerGlobalObserverWithTag(
                                                              *this,
                                                              observer,
                                                              particle_types );
}

// Register the obs. with dispatchers associated with BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                                     EventHandler& event_handler,
                                     const std::shared_ptr<Observer>& observer,
                                     const std::set<uint64_t>& entity_ids )
{
  event_handler.registerObserverWithTag(
                   observer,
                   entity_ids,
                   typename boost::mpl::deref<BeginEventTagIterator>::type() );

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,EndEventTagIterator>::registerObserverWithTag(
                                                                 event_handler,
                                                                 observer,
                                                                 entity_ids );
}

// End registration iteration
template<typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                               EventHandler& event_handler,
			       const std::shared_ptr<Observer>& observer,
                               const std::set<uint64_t>& entity_ids )
{ /* ... */ }

// Register the obs. with dispatchers associated with BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                                 EventHandler& event_handler,
                                 const std::shared_ptr<Observer>& observer,
                                 const std::set<uint64_t>& entity_ids,
                                 const std::set<ParticleType>& particle_types )
{
  event_handler.registerObserverWithTag(
                   observer,
                   entity_ids,
                   particle_types,
                   typename boost::mpl::deref<BeginEventTagIterator>::type() );

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,EndEventTagIterator>::registerObserverWithTag(
                                                              event_handler,
                                                              observer,
                                                              entity_ids,
                                                              particle_types );
}

// End registration iteration
template<typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                               EventHandler& event_handler,
			       const std::shared_ptr<Observer>& observer,
                               const std::set<uint64_t>& entity_ids,
                               const std::set<ParticleType>& particle_types )
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

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,EndEventTagIterator>::registerGlobalObserverWithTag(
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

// Register the global observer with the global dispatcher associated with
// BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerGlobalObserverWithTag(
                                 EventHandler& event_handler,
                                 const std::shared_ptr<Observer>& observer,
                                 const std::set<ParticleType>& particle_types )
{
  event_handler.registerGlobalObserverWithTag(
                   observer,
                   particle_types,
                   typename boost::mpl::deref<BeginEventTagIterator>::type() );

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,EndEventTagIterator>::registerGlobalObserverWithTag(
                                                                 event_handler,
                                                                 observer );
}

// End global registration iteration
template<typename EndEventTagIterator>
template<typename Observer>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerGlobalObserverWithTag(
                                 EventHandler& event_handler,
                                 const std::shared_ptr<Observer>& observer,
                                 const std::set<ParticleType>& particle_types )
{ /* ... */ }

// Serialize the observer
template<typename Archive>
void EventHandler::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCollidingInCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCrossingSurfaceEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingInCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleGoneGlobalEventHandler );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_estimators );
  ar & BOOST_SERIALIZATION_NVP( d_particle_trackers );
  ar & BOOST_SERIALIZATION_NVP( d_particle_history_observers );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EVENT_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler_def.hpp
//---------------------------------------------------------------------------//
