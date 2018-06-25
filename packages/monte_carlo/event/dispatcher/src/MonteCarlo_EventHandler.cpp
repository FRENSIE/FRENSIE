//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler.cpp
//! \author Alex Robinson
//! \brief  Event handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ParticleHistoryObserverHDF5FileHandler.hpp"
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
EventHandler::EventHandler()
{ /* ... */ }

// Return the number of estimators that have been added
unsigned EventHandler::getNumberOfObservers() const
{
  return d_particle_history_observers.size();
}

// Check if an observer with the given id exists
bool EventHandler::doesObserverExist(
                      const ParticleHistoryObserver::idType observer_id ) const
{
  return d_particle_history_observers.find( observer_id ) !=
    d_particle_history_observers.end();
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
    it->second->enableThreadSupport( num_threads );

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
    if( it->second->hasUncommittedHistoryContribution() )
      it->second->commitHistoryContribution();

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
  ParticleHistoryObserver::setStartTime( start_time );
  ParticleHistoryObserver::setEndTime( end_time );

  os << "Observers: " << std::endl;

  ParticleHistoryObservers::const_iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    os << *(it->second) << std::endl;

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
    it->second->resetData();

    ++it;
  }
}

// Reduce the observer data on all processes in comm and collect on the root
void EventHandler::reduceObserverData(
	    const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
	    const int root_process )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    it->second->reduceData( comm, root_process );

    ++it;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler.cpp
//---------------------------------------------------------------------------//
