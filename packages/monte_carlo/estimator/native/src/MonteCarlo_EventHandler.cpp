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
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
EventHandler::EventHandler()
  : d_particle_history_observers(),
    d_particle_entering_cell_event_dispatcher(),
    d_particle_leaving_cell_event_dispatcher(),
    d_particle_subtrack_ending_in_cell_event_dispatcher(),
    d_particle_colliding_in_cell_event_dispatcher(),
    d_particle_crossing_surface_event_dispatcher(),
    d_particle_subtrack_ending_global_event_dispatcher()
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
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );

  hdf5_file->openHDF5FileAndOverwrite( data_file_name );

  // Create a particle history observer HDF5 file handler
  {
    ParticleHistoryObserverHDF5FileHandler pho_hdf5_file_handler( hdf5_file );
  
    // Set the simulation time
    pho_hdf5_file_handler.setSimulationTime( end_time - start_time );
  
    ParticleHistoryObserver::setStartTime( start_time );
    ParticleHistoryObserver::setEndTime( end_time );
  
    // Set the last history simulated
    pho_hdf5_file_handler.setLastHistorySimulated( last_history_number );
  
    // Set the number of histories simulated
    pho_hdf5_file_handler.setNumberOfHistoriesSimulated( histories_completed );
  
    ParticleHistoryObserver::setNumberOfHistories( histories_completed );
  }
  
  // Export the data in each estimator
  ParticleHistoryObservers::iterator it = 
    d_particle_history_observers.begin();
  
  while( it != d_particle_history_observers.end() )
  {
    it->second->exportData( hdf5_file, process_data );

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
  d_particle_entering_cell_event_dispatcher.dispatchParticleEnteringCellEvent(
							  particle,
							  particle.getCell() );
}

// Update the observers from a particle entering cell event
void EventHandler::updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  d_particle_entering_cell_event_dispatcher.dispatchParticleEnteringCellEvent(
                                                               particle,
                                                               cell_entering );
}

// Update the observers from a particle leaving cell event
void EventHandler::updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  d_particle_leaving_cell_event_dispatcher.dispatchParticleLeavingCellEvent(
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
  d_particle_subtrack_ending_in_cell_event_dispatcher.dispatchParticleSubtrackEndingInCellEvent(
						    particle,
						    cell_of_subtrack,
						    particle_subtrack_length );
}

// Update the observers from a particle colliding in cell event
void EventHandler::updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section )
{
  d_particle_colliding_in_cell_event_dispatcher.dispatchParticleCollidingInCellEvent(
						 particle,
						 particle.getCell(),
						 inverse_total_cross_section );
}

// Update the observers from a surface intersection event
void EventHandler::updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
          const double surface_normal[3] )
{
  // Make sure the surface normal is valid
  testPrecondition( Utility::validDirection( surface_normal ) );

  double angle_cosine = Utility::calculateCosineOfAngleBetweenVectors(
						       particle.getDirection(),
						       surface_normal );

  d_particle_crossing_surface_event_dispatcher.dispatchParticleCrossingSurfaceEvent(
							      particle,
							      surface_crossing,
							      angle_cosine );
}

// Update the global estimators from a collision event
void EventHandler::updateObserversFromParticleCollidingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  d_particle_subtrack_ending_global_event_dispatcher.dispatchParticleSubtrackEndingGlobalEvent(
								   particle,
								   start_point,
								   end_point );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler.cpp
//---------------------------------------------------------------------------//
