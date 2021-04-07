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
#include "Utility_GlobalMPISession.hpp"
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

  ParticleHistoryObservers::iterator observer_it =
    std::find( d_particle_history_observers.begin(),
               d_particle_history_observers.end(),
               estimator );
  
  if( observer_it == d_particle_history_observers.end() )
  {
    // Make sure that the particle types have been set
    TEST_FOR_EXCEPTION( estimator->getParticleTypes().empty(),
                        std::runtime_error,
                        "The estimator particle type(s) must be set before "
                        "adding them to the event handler!" );
    
    EstimatorRegistrationHelper<EstimatorType>::registerEstimator( *this, estimator );

    // Add the estimator to the map
    d_estimators[estimator->getId()] = estimator;
    
    // Add the observer to the set
    d_particle_history_observers.push_back( estimator );
  }
}

// Struct for registering estimator
template<typename EstimatorType>
void EventHandler::EstimatorRegistrationHelper<EstimatorType>::registerEstimator(
                              EventHandler& event_handler,
                              const std::shared_ptr<EstimatorType>& estimator )
{
  std::set<Estimator::EntityId> entity_ids;
  estimator->getEntityIds( entity_ids );
    
  if( estimator->isCellEstimator() )
  {
    event_handler.verifyValidEstimatorCellIds( estimator->getId(),
                                               entity_ids );
  }
  else
  {
    event_handler.verifyValidEstimatorSurfaceIds( estimator->getId(),
                                                  entity_ids );
  }

  std::set<ParticleType> particle_types = estimator->getParticleTypes();

  event_handler.registerObserver( estimator, entity_ids, particle_types );
}

template<typename T>
void EventHandler::EstimatorRegistrationHelper<MeshTrackLengthFluxEstimator<T> >::registerEstimator(
           EventHandler& event_handler,
           const std::shared_ptr<MeshTrackLengthFluxEstimator<T> >& estimator )
{
  std::set<ParticleType> particle_types = estimator->getParticleTypes();
  
  event_handler.registerGlobalObserver( estimator, particle_types );
}

// Register an observer with the appropriate dispatcher
template<typename Observer, typename InputEntityId>
void EventHandler::registerObserver( const std::shared_ptr<Observer>& observer,
                                     const std::set<InputEntityId>& entity_ids )
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
template<typename Observer, typename InputEntityId>
void EventHandler::registerObserver( const std::shared_ptr<Observer>& observer,
                                     const std::set<InputEntityId>& entity_ids,
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
template<typename Observer, typename InputEntityId>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                                     EventHandler& event_handler,
                                     const std::shared_ptr<Observer>& observer,
                                     const std::set<InputEntityId>& entity_ids )
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
template<typename Observer, typename InputEntityId>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                               EventHandler& event_handler,
			       const std::shared_ptr<Observer>& observer,
                               const std::set<InputEntityId>& entity_ids )
{ /* ... */ }

// Register the obs. with dispatchers associated with BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer, typename InputEntityId>
void EventHandler::ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                                 EventHandler& event_handler,
                                 const std::shared_ptr<Observer>& observer,
                                 const std::set<InputEntityId>& entity_ids,
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
template<typename Observer, typename InputEntityId>
void EventHandler::ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::registerObserverWithTag(
                               EventHandler& event_handler,
			       const std::shared_ptr<Observer>& observer,
                               const std::set<InputEntityId>& entity_ids,
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

// Save the data to an archive
template<typename Archive>
void EventHandler::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCollidingInCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCrossingSurfaceEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingInCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleGoneGlobalEventHandler );

  // Save the local data (ignore the model, snapshot counters)
  ar & BOOST_SERIALIZATION_NVP( d_simulation_completion_criterion );

  uint64_t number_of_committed_histories =
    this->getNumberOfCommittedHistories();
  
  ar & BOOST_SERIALIZATION_NVP( number_of_committed_histories );

  double elapsed_time = this->getElapsedTime();
  
  ar & BOOST_SERIALIZATION_NVP( elapsed_time );
  ar & BOOST_SERIALIZATION_NVP( d_estimators );
  ar & BOOST_SERIALIZATION_NVP( d_particle_trackers );
  ar & BOOST_SERIALIZATION_NVP( d_particle_history_observers );
}

// Load the data to an archive
template<typename Archive>
void EventHandler::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCollidingInCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCrossingSurfaceEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingInCellEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventHandler );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleGoneGlobalEventHandler );

  // Load the local data (ignore the model)
  ar & BOOST_SERIALIZATION_NVP( d_simulation_completion_criterion );

  uint64_t number_of_committed_histories;
  
  ar & BOOST_SERIALIZATION_NVP( number_of_committed_histories );

  d_number_of_committed_histories.resize( 1 );
  d_number_of_committed_histories.front() = number_of_committed_histories;

  if( number_of_committed_histories > 0 )
    ParticleHistoryObserver::setNumberOfHistories( number_of_committed_histories );

  d_number_of_committed_histories_from_last_snapshot.resize( 1 );
  d_number_of_committed_histories_from_last_snapshot[0] = 0;

  ar & boost::serialization::make_nvp( "elapsed_time", d_elapsed_simulation_time );  

  if( d_elapsed_simulation_time > 0.0 )
    ParticleHistoryObserver::setElapsedTime( d_elapsed_simulation_time );

  d_number_of_committed_histories_from_last_snapshot.resize( 1, 0 );

  d_simulation_timer = Utility::GlobalMPISession::createTimer();
  d_snapshot_timer = Utility::GlobalMPISession::createTimer();
  
  ar & BOOST_SERIALIZATION_NVP( d_estimators );
  ar & BOOST_SERIALIZATION_NVP( d_particle_trackers );
  ar & BOOST_SERIALIZATION_NVP( d_particle_history_observers );
}

} // end MonteCarlo namespace

EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, EventHandler );

#endif // end MONTE_CARLO_EVENT_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler_def.hpp
//---------------------------------------------------------------------------//
