//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_EventHandler.cpp
//! \author Alex Robinson
//! \brief  Event handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleLeavingCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
EventHandler::EventHandler()
  : d_particle_history_observers()
{ /* ... */ }

// Return the number of estimators that have been added
unsigned EventHandler::getNumberOfObservers() const
{
  return d_particle_history_observers.size();
}

// Check if an observer with the given id exists
unsigned EventHandler::doesObserverExist( const unsigned observer_id ) const
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
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
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
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  ParticleHistoryObserver::setNumberOfHistories( num_histories );
  ParticleHistoryObserver::setStartTime( start_time );
  ParticleHistoryObserver::setEndTime( end_time );
  
  os << "Estimators: " << std::endl;
  
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
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
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
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  ParticleHistoryObservers::iterator it = 
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    it->second->reduceData( comm, root_process );

    ++it;
  }
}

// Export the observer data
void EventHandler::exportObserverData( 
				  const std::string& data_file_name,
				  const unsigned long long last_history_number,
				  const unsigned long long histories_completed,
				  const double start_time,
				  const double end_time,
				  const bool process_data )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  // Initialize the HDF5 file
  {
    EstimatorHDF5FileHandler hdf5_file_handler( 
                     data_file_name,
                     EstimatorHDF5FileHandler::OVERWRITE_ESTIMATOR_HDF5_FILE );
  
    // Set the simulation time
    hdf5_file_handler.setSimulationTime( end_time - start_time );
  
    ParticleHistoryObserver::setStartTime( start_time );
    ParticleHistoryObserver::setEndTime( end_time );
  
    // Set the last history simulated
    hdf5_file_handler.setLastHistorySimulated( last_history_number );
  
    // Set the number of histories simulated
    hdf5_file_handler.setNumberOfHistoriesSimulated( histories_completed );
  
    ParticleHistoryObserver::setNumberOfHistories( histories_completed );
  }
  
  // Export the data in each estimator
  ParticleHistoryObservers::iterator it = 
    d_particle_history_observers.begin();
  
  while( it != d_particle_history_observers.end() )
  {
    it->second->exportData( data_file_name, process_data );

    ++it;
  }
}

// Update the observers from a particle generation event
/*! \details This event refers to the creation of a new source particle and
 * not the creation of secondaries.
 */ 
void EventHandler::updateObserversFromParticleGenerationEvent(
                                                const ParticleState& particle )
{
  ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
							  particle,
							  particle.getCell() );
}

// Update the observers from a particle entering cell event
void EventHandler::updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
                                                               particle,
                                                               cell_entering );
}

// Update the observers from a particle leaving cell event
void EventHandler::updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent(
                                                                particle,
                                                                cell_leaving );
}

// Update the observers from a particle subtrack ending in cell event
void EventHandler::updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time )
{
  ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
						    particle,
						    cell_leaving,
						    particle_subtrack_length );
}

// Update the observers from a particle colliding in cell event
void EventHandler::updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section )
{
  ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
						 particle,
						 particle.getCell(),
						 inverse_total_cross_section );
}

// Update the observers from a surface intersection event
void updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
          const double surface_normal[3] )
{
  // Make sure the surface normal is valid
  testPrecondition( Utility::validDirection( surface_normal ) );

  double angle_cosine = Utility::calculateCosineOfAngleBetweenVectors(
						       particle.getDirection(),
						       surface_normal );

  ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
							      particle,
							      surface_crossing,
							      angle_cosine );
}

// Update the global estimators from a collision event
void updateObserversFromParticleCollidingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
								   particle,
								   start_point,
								   end_point );
}

// Update the global estimators from a domain exit event
void updateObserversFromParticleLeavingDomainGlobalEvent(
                                                 const ParticleState& particle,
                                                 const double start_point[3],
                                                 const double end_point[3] )
{
  ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
								   particle,
								   start_point,
								   end_point );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler.cpp
//---------------------------------------------------------------------------//
