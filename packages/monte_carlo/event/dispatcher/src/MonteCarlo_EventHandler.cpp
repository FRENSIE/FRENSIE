//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler.cpp
//! \author Alex Robinson
//! \brief  Event handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
EventHandler::EventHandler()
{ /* ... */ }

// Add a particle tracker to the handler
void EventHandler::addParticleTracker(
                     const std::shared_ptr<ParticleTracker>& particle_tracker )
{
  this->registerGlobalObserver( particle_tracker );
}

// Return the number of estimators that have been added
size_t EventHandler::getNumberOfEstimators() const
{
  return d_estimators.size();
}

// Return the number of particle trackers
size_t EventHandler::getNumberOfParticleTrackers() const
{
  return d_particle_trackers.size();
}

// Check if an estimator with the given id exists
bool EventHandler::doesEstimatorExist( const uint32_t estimator_id ) const
{
  return d_estimators.find( estimator_id ) != d_estimators.end();
}

// Return the estimator
Estimator& EventHandler::getEstimator( const uint32_t estimator_id )
{
  TEST_FOR_EXCEPTION( !this->doesEstimatorExist( estimator_id ),
                      std::runtime_error,
                      "Estimator " << estimator_id << " has not been "
                      "registered with the event handler!" );

  return *d_estimators.find( estimator_id )->second;
}

// Return the estimator
const Estimator& EventHandler::getEstimator( const uint32_t estimator_id ) const
{
  TEST_FOR_EXCEPTION( !this->doesEstimatorExist( estimator_id ),
                      std::runtime_error,
                      "Estimator " << estimator_id << " has not been "
                      "registered with the event handler!" );

  return *d_estimators.find( estimator_id )->second;
}

// Check if a particle tracker with the given id exists
bool EventHandler::doesParticleTrackerExist( const uint32_t particle_tracker_id ) const
{
  return d_particle_trackers.find( particle_tracker_id ) !=
    d_particle_trackers.end();
}

// Return the particle tracker
ParticleTracker& EventHandler::getParticleTracker( const uint32_t particle_tracker_id )
{
  TEST_FOR_EXCEPTION( !this->doesParticleTrackerExist( particle_tracker_id ),
                      std::runtime_error,
                      "Particle tracker " << particle_tracker_id <<
                      " has not been registered with the event handler!" );

  return *d_particle_trackers.find( particle_tracker_id )->second;
}

// Return the particle tracker
const ParticleTracker& EventHandler::getParticleTracker( const uint32_t particle_tracker_id ) const
{
  TEST_FOR_EXCEPTION( !this->doesParticleTrackerExist( particle_tracker_id ),
                      std::runtime_error,
                      "Particle tracker " << particle_tracker_id <<
                      " has not been registered with the event handler!" );

  return *d_particle_trackers.find( particle_tracker_id )->second;
}

// Enable support for multiple threads
/*! \details This should only be called after all of the estimators have been
 * added.
 */
void EventHandler::enableThreadSupport( const unsigned num_threads )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    (*it)->enableThreadSupport( num_threads );

    ++it;
  }
}

// Commit the estimator history contributions
void EventHandler::commitObserverHistoryContributions()
{
  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    if( (*it)->hasUncommittedHistoryContribution() )
      (*it)->commitHistoryContribution();

    ++it;
  }
}

// Print the estimators
void EventHandler::printObserverSummaries( std::ostream& os,
                                           const double num_histories,
                                           const double start_time,
                                           const double end_time ) const
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  ParticleHistoryObserver::setNumberOfHistories( num_histories );
  ParticleHistoryObserver::setElapsedTime( end_time - start_time );

  os << "Observers: " << std::endl;

  ParticleHistoryObservers::const_iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    os << *(*it) << std::endl;

    ++it;
  }
}

// Reset observer data
void EventHandler::resetObserverData()
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    (*it)->resetData();

    ++it;
  }
}

// Reduce the observer data on all processes in comm and collect on the root
void EventHandler::reduceObserverData( const Utility::Communicator& comm,
                                       const int root_process )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    (*it)->reduceData( comm, root_process );

    ++it;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler.cpp
//---------------------------------------------------------------------------//
