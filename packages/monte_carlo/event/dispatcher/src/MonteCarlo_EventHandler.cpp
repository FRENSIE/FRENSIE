//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler.cpp
//! \author Alex Robinson
//! \brief  Event handler class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <numeric>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
EventHandler::EventHandler()
  : d_model(),
    d_simulation_completion_criterion( ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( Utility::QuantityTraits<double>::inf() ) ),
    d_number_of_committed_histories( 1, 0 ),
    d_number_of_committed_histories_from_last_snapshot( 1, 0 ),
    d_simulation_timer( Utility::GlobalMPISession::createTimer() ),
    d_snapshot_timer( Utility::GlobalMPISession::createTimer() ),
    d_elapsed_simulation_time( 0.0 ),
    d_estimators(),
    d_particle_trackers(),
    d_particle_history_observers( {d_simulation_completion_criterion} )
{ /* ... */ }

// Constructor
EventHandler::EventHandler(
                    const MonteCarlo::SimulationGeneralProperties& properties )
  : EventHandler( std::shared_ptr<const Geometry::Model>(), properties )
{ /* ... */ }

// Constructor (filled model)
EventHandler::EventHandler(
           const std::shared_ptr<const MonteCarlo::FilledGeometryModel>& model,
           const MonteCarlo::SimulationGeneralProperties& properties )
  : EventHandler( (std::shared_ptr<const Geometry::Model>)(*model),
                  properties )
{ /* ... */ }

// Constructor (model)
/*! \details The model will be stored and used to check the validity of
 * estimator entities when an estimator is added.
 */
EventHandler::EventHandler(
                    const std::shared_ptr<const Geometry::Model>& model,
                    const MonteCarlo::SimulationGeneralProperties& properties )
  : d_model( model ),
    d_simulation_completion_criterion( EventHandler::createDefaultCompletionCriterion( properties ) ),
    d_number_of_committed_histories( 1, 0 ),
    d_number_of_committed_histories_from_last_snapshot( 1, 0 ),
    d_simulation_timer( Utility::GlobalMPISession::createTimer() ),
    d_snapshot_timer( Utility::GlobalMPISession::createTimer() ),
    d_elapsed_simulation_time( 0.0 ),
    d_estimators(),
    d_particle_trackers(),
    d_particle_history_observers( {d_simulation_completion_criterion} )
{
  if( model )
  {
    // Get the cell estimator data from the model
    if( model->hasCellEstimatorData() )
    {
      Geometry::Model::CellEstimatorIdDataMap cell_estimator_data_map;

      model->getCellEstimatorData( cell_estimator_data_map );

      Geometry::Model::CellEstimatorIdDataMap::const_iterator
        cell_estimator_data_it = cell_estimator_data_map.begin();

      uint32_t cell_estimator_counter = 0;

      while( cell_estimator_data_it != cell_estimator_data_map.end() )
      {
        this->createAndRegisterCellEstimator(
                               cell_estimator_data_it->first,
                               Utility::get<0>(cell_estimator_data_it->second),
                               Utility::get<1>(cell_estimator_data_it->second),
                               Utility::get<2>(cell_estimator_data_it->second),
                               *d_model );

        ++cell_estimator_counter;
        ++cell_estimator_data_it;
      }

      if( cell_estimator_counter > 0 )
      {
        FRENSIE_LOG_NOTIFICATION( "Created " << cell_estimator_counter <<
                                  " cell estimators from geometry model data." );
      }
    }

    // Get the surface estimator data from the model
    if( model->isAdvanced() )
    {
      const Geometry::AdvancedModel& advanced_model =
        dynamic_cast<const Geometry::AdvancedModel&>( *model );

      if( advanced_model.hasSurfaceEstimatorData() )
      {
        Geometry::AdvancedModel::SurfaceEstimatorIdDataMap
          surface_estimator_data_map;

        advanced_model.getSurfaceEstimatorData( surface_estimator_data_map );

        Geometry::AdvancedModel::SurfaceEstimatorIdDataMap::const_iterator
          surface_estimator_data_it = surface_estimator_data_map.begin();

        uint32_t surface_estimator_counter = 0;

        while( surface_estimator_data_it != surface_estimator_data_map.end() )
        {
          this->createAndRegisterSurfaceEstimator(
                            surface_estimator_data_it->first,
                            Utility::get<0>(surface_estimator_data_it->second),
                            Utility::get<1>(surface_estimator_data_it->second),
                            Utility::get<2>(surface_estimator_data_it->second),
                            *d_model );

          ++surface_estimator_counter;
          ++surface_estimator_data_it;
        }

        if( surface_estimator_counter > 0 )
        {
          FRENSIE_LOG_NOTIFICATION( "Created " << surface_estimator_counter <<
                                    " surface estimators from geometry model "
                                    "data." );
        }
      }
    }
  }
}

// Create a default simulation completion criterion
std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
EventHandler::createDefaultCompletionCriterion(
                    const MonteCarlo::SimulationGeneralProperties& properties )
{
  if( properties.getNumberOfHistories() > 0 )
  {
    if( properties.getSimulationWallTime() < Utility::QuantityTraits<double>::inf() )
    {
      return ParticleHistorySimulationCompletionCriterion::createMixedCriterion(
                                          properties.getNumberOfHistories(),
                                          properties.getSimulationWallTime() );
    }
    else
    {
      return ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion(
                                           properties.getNumberOfHistories() );
    }
  }
  else
  {
    if( properties.getSimulationWallTime() == Utility::QuantityTraits<double>::inf() )
    {
      FRENSIE_LOG_TAGGED_WARNING( "EventHandler",
                                  "The simulation completion criterion can "
                                  "never be met!" );
    }

    return ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( properties.getSimulationWallTime() );
  }
}

// Create and register cell estimator
void EventHandler::createAndRegisterCellEstimator(
                                  const uint32_t estimator_id,
                                  const Geometry::EstimatorType estimator_type,
                                  const Geometry::ParticleType particle_type,
                                  const Geometry::Model::CellIdArray& cells,
                                  const Geometry::Model& model )
{
  switch( estimator_type )
  {
    case Geometry::CELL_PULSE_HEIGHT_ESTIMATOR:
    {
      std::shared_ptr<WeightMultipliedCellPulseHeightEstimator> estimator(
                    new WeightMultipliedCellPulseHeightEstimator( estimator_id,
                                                                  1.0,
                                                                  cells ) );

      // Set the particle type
      this->setParticleTypes( particle_type, estimator );

      this->addEstimator( estimator );

      break;
    }

    case Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR:
    {
      std::shared_ptr<WeightMultipliedCellTrackLengthFluxEstimator> estimator(
                new WeightMultipliedCellTrackLengthFluxEstimator( estimator_id,
                                                                  1.0,
                                                                  cells,
                                                                  model ) );

      // Set the particle type
      this->setParticleTypes( particle_type, estimator );

      this->addEstimator( estimator );

      break;
    }

    case Geometry::CELL_COLLISION_FLUX_ESTIMATOR:
    {
      std::shared_ptr<WeightMultipliedCellCollisionFluxEstimator> estimator(
                  new WeightMultipliedCellCollisionFluxEstimator( estimator_id,
                                                                  1.0,
                                                                  cells,
                                                                  model ) );

      // Set the particle type
      this->setParticleTypes( particle_type, estimator );

      this->addEstimator( estimator );

      break;
    }

    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "The cell estimator type (" << estimator_type <<
                       ") encountered in the model is not supported!" );
    }
  }
}

// Create and register surface estimator
void EventHandler::createAndRegisterSurfaceEstimator(
                       const uint32_t estimator_id,
                       const Geometry::EstimatorType estimator_type,
                       const Geometry::ParticleType particle_type,
                       const Geometry::AdvancedModel::SurfaceIdArray& surfaces,
                       const Geometry::Model& model )
{
  switch( estimator_type )
  {
    case Geometry::SURFACE_CURRENT_ESTIMATOR:
    {
      std::shared_ptr<WeightMultipliedSurfaceCurrentEstimator> estimator(
                     new WeightMultipliedSurfaceCurrentEstimator( estimator_id,
                                                                  1.0,
                                                                  surfaces ) );

      // Set the particle type
      this->setParticleTypes( particle_type, estimator );

      this->addEstimator( estimator );

      break;
    }

    case Geometry::SURFACE_FLUX_ESTIMATOR:
    {
      std::shared_ptr<WeightMultipliedSurfaceFluxEstimator> estimator(
          new WeightMultipliedSurfaceFluxEstimator( estimator_id,
                                                    1.0,
                                                    surfaces,
                                                    model ) );

      // Set the particle type
      this->setParticleTypes( particle_type, estimator );

      this->addEstimator( estimator );

      break;
    }

    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "The surface estimator type (" << estimator_type <<
                       ") encountered in the model is not supported!" );
    }
  }
}

// Set the particle type in a created estimator
void EventHandler::setParticleTypes(
                                  const Geometry::ParticleType particle_type,
                                  const std::shared_ptr<Estimator>& estimator )
{
  switch( particle_type )
  {
    case Geometry::NEUTRON:
    {
      estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::NEUTRON} ) );
      break;
    }

    case Geometry::PHOTON:
    {
      estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );
      break;
    }

    case Geometry::ELECTRON:
    {
      estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );
      break;
    }

    case Geometry::ADJOINT_NEUTRON:
    {
      estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ADJOINT_NEUTRON} ) );
      break;
    }

    case Geometry::ADJOINT_PHOTON:
    {
      estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ADJOINT_PHOTON} ) );
      break;
    }

    case Geometry::ADJOINT_ELECTRON:
    {
      estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ADJOINT_ELECTRON} ) );
      break;
    }

    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "The particle type (" << particle_type <<
                       ") encountered in the model is not supported!" );
    }
  }
}

// Set a custom simulation completion criterion
void EventHandler::setSimulationCompletionCriterion(
           const std::shared_ptr<ParticleHistorySimulationCompletionCriterion>&
           criterion )
{
  if( criterion )
  {
    d_simulation_completion_criterion = criterion;

    this->updateSimulationCompletionCriterionObserver( d_simulation_completion_criterion );
  }
}

// Set a simulation completion criterion
void EventHandler::setSimulationCompletionCriterion( const uint64_t number_of_histories )
{
  this->setSimulationCompletionCriterion( ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( number_of_histories ) );
}

// Set a simulation completion criterion
void EventHandler::setSimulationCompletionCriterion( const double wall_time )
{
  this->setSimulationCompletionCriterion( ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( wall_time ) );
}

// Set a simulation completion criterion
void EventHandler::setSimulationCompletionCriterion(
                                            const uint64_t number_of_histories,
                                            const double wall_time )
{
  this->setSimulationCompletionCriterion( ParticleHistorySimulationCompletionCriterion::createMixedCriterion( number_of_histories, wall_time ) );
}

// Set a simulation completion criterion
void EventHandler::setSimulationCompletionCriterion(
                    const MonteCarlo::SimulationGeneralProperties& properties )
{
  this->setSimulationCompletionCriterion( this->createDefaultCompletionCriterion( properties ) );
}

// Update the simulation completion criterion observer
void EventHandler::updateSimulationCompletionCriterionObserver( const std::shared_ptr<ParticleHistorySimulationCompletionCriterion>& observer )
{
  // Make sure that the observer is valid
  testPrecondition( observer.get() );

  d_particle_history_observers.front() = observer;
}

// Check if the simulation is complete
bool EventHandler::isSimulationComplete() const
{
  return d_simulation_completion_criterion->isSimulationComplete();
}

// Add a particle tracker to the handler
void EventHandler::addParticleTracker(
                     const std::shared_ptr<ParticleTracker>& particle_tracker )
{
  // Make sure the observer is valid
  testPrecondition( particle_tracker.get() );

  ParticleHistoryObservers::iterator observer_it =
    std::find( d_particle_history_observers.begin(),
               d_particle_history_observers.end(),
               particle_tracker );

  if( observer_it == d_particle_history_observers.end() )
  {
    this->registerGlobalObserver( particle_tracker );

    // Add the tracker to the map
    d_particle_trackers[particle_tracker->getId()] = particle_tracker;

    // Add the observer to the set
    d_particle_history_observers.push_back( particle_tracker );
  }
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

  d_number_of_committed_histories.resize( num_threads, 0 );
  d_number_of_committed_histories_from_last_snapshot.resize( num_threads, 0 );
}

// Update observers from particle simulation started event
void EventHandler::updateObserversFromParticleSimulationStartedEvent()
{
  d_simulation_completion_criterion->start();
  d_simulation_timer->start();
  d_snapshot_timer->start();
}

// Update observers from particle simulation stopped event
void EventHandler::updateObserversFromParticleSimulationStoppedEvent()
{
  d_simulation_completion_criterion->stop();
  d_simulation_timer->stop();
  d_snapshot_timer->stop();

  ParticleHistoryObserver::setElapsedTime( this->getElapsedTime() );
  ParticleHistoryObserver::setNumberOfHistories( this->getNumberOfCommittedHistories() );
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

  ++d_number_of_committed_histories[Utility::OpenMPProperties::getThreadId()];
  ++d_number_of_committed_histories_from_last_snapshot[Utility::OpenMPProperties::getThreadId()];
}

// Take a snapshot of the observer states
void EventHandler::takeSnapshotOfObserverStates()
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  double additional_sampling_time =
    this->getElapsedTimeSinceLastSnapshot();

  uint64_t num_additional_histories =
    this->getNumberOfCommittedHistoriesSinceLastSnapshot();

  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();
  
  while( it != d_particle_history_observers.end() )
  {
    (*it)->takeSnapshot( num_additional_histories,
                         additional_sampling_time );

    ++it;
  }

  // Reset the counters
  this->resetNumberOfCommittedHistoriesSinceLastSnapshot();
  this->resetElapsedTimeSinceLastSnapshot();
}

// Log the observer summaries
void EventHandler::logObserverSummaries() const
{
  std::ostringstream oss;

  this->printObserverSummaries( oss );

  FRENSIE_LOG_NOTIFICATION( oss.str() );
}

// Print the estimators
void EventHandler::printObserverSummaries( std::ostream& os ) const
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  os << "Number of committed histories: "
     << this->getNumberOfCommittedHistories() << "\n";

  os << "Simulation time (s): " << this->getElapsedTime() << "\n";

  os << "Observers: \n";

  ParticleHistoryObservers::const_iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    os << *(*it) << "\n";

    ++it;
  }

  os.flush();
}

// Reset observer data
void EventHandler::resetObserverData()
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  // Reset the committed histories
  for( size_t i = 0; i < d_number_of_committed_histories.size(); ++i )
    d_number_of_committed_histories[i] = 0;

  // Reset the observers
  ParticleHistoryObservers::iterator it =
    d_particle_history_observers.begin();

  while( it != d_particle_history_observers.end() )
  {
    (*it)->resetData();

    ++it;
  }
}

// Reduce the observer data on all processes in comm and collect on the root
/*! \details A Snapshot must be taken before the reduction to ensure that the
 * snapshot data stays in sync with the current data.
 */
void EventHandler::reduceObserverData( const Utility::Communicator& comm,
                                       const int root_process )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure that a snapshot has been taken
  testPrecondition( this->getNumberOfCommittedHistoriesSinceLastSnapshot() == 0 );

  if( comm.size() > 1 )
  {
    // Reduce the number of committed histories
    try{
      if( comm.rank() == root_process )
      {
        uint64_t reduced_num_committed_histories = 0;

        Utility::reduce( comm,
                         this->getNumberOfCommittedHistories(),
                         reduced_num_committed_histories,
                         std::plus<uint64_t>(),
                         root_process );
        
        d_number_of_committed_histories.front() =
          reduced_num_committed_histories;

        for( size_t i = 1; i < d_number_of_committed_histories.size(); ++i )
          d_number_of_committed_histories[i] = 0;
      }
      else
      {
        Utility::reduce( comm,
                         this->getNumberOfCommittedHistories(),
                         std::plus<uint64_t>(),
                         root_process );

        // Reset the number of committed histories
        for( size_t i = 0; i < d_number_of_committed_histories.size(); ++i )
          d_number_of_committed_histories[i] = 0;

        
      }
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "event handler for number of committed "
                             "histories!" );

    comm.barrier();

    // Reduce the observers
    ParticleHistoryObservers::iterator it =
      d_particle_history_observers.begin();

    while( it != d_particle_history_observers.end() )
    {
      (*it)->reduceData( comm, root_process );

      comm.barrier();

      ++it;
    }

    // Reset the snapshot timer (no need to include reduction time)
    this->resetElapsedTimeSinceLastSnapshot();

    comm.barrier();
  }
}

// Get the number of particle histories that have been simulated
uint64_t EventHandler::getNumberOfCommittedHistories() const
{
  return std::accumulate( d_number_of_committed_histories.begin(),
                          d_number_of_committed_histories.end(),
                          0 );
}

// Get the number of particle histories committed since the last snapshot
uint64_t EventHandler::getNumberOfCommittedHistoriesSinceLastSnapshot() const
{
  return std::accumulate( d_number_of_committed_histories_from_last_snapshot.begin(),
                          d_number_of_committed_histories_from_last_snapshot.end(),
                          0 );
}

// Reset the number of committed histories since the last snapshot
void EventHandler::resetNumberOfCommittedHistoriesSinceLastSnapshot()
{
  for( size_t i = 0; i < d_number_of_committed_histories_from_last_snapshot.size(); ++i )
    d_number_of_committed_histories_from_last_snapshot[i] = 0;
}

// Get the elapsed time since the last snapshot
double EventHandler::getElapsedTimeSinceLastSnapshot() const
{
  return d_snapshot_timer->elapsed().count();
}

// Reset the elapsed time since the last snapshot
void EventHandler::resetElapsedTimeSinceLastSnapshot()
{
  d_snapshot_timer->stop();
  d_snapshot_timer->start();
}

// Get the elapsed particle simulation time (s)
double EventHandler::getElapsedTime() const
{
  return d_simulation_timer->elapsed().count() + d_elapsed_simulation_time;
}

// Verify that the estimator cell ids are valid
void EventHandler::verifyValidEstimatorCellIds(
                          const Estimator::Id estimator_id,
                          const std::set<Estimator::EntityId>& cell_ids ) const
{
  if( d_model )
  {
    for( auto&& cell_id : cell_ids )
    {
      TEST_FOR_EXCEPTION( !d_model->doesCellExist( cell_id ),
                          std::runtime_error,
                          "Estimator " << estimator_id << " has a cell id "
                          "assigned (" << cell_id << " that does not exist "
                          "in the model!" );
    }
  }
}

// Verify that the estimator surface ids are valid
void EventHandler::verifyValidEstimatorSurfaceIds(
                       const Estimator::Id estimator_id,
                       const std::set<Estimator::EntityId>& surface_ids ) const
{
  if( d_model )
  {
    TEST_FOR_EXCEPTION( !d_model->isAdvanced(),
                        std::runtime_error,
                        "Surface estimators cannot be assigned because the "
                        "model does not contain surface data!" );

    const Geometry::AdvancedModel& advanced_model =
      dynamic_cast<const Geometry::AdvancedModel&>( *d_model );

    for( auto&& surface_id : surface_ids )
    {
      TEST_FOR_EXCEPTION( !advanced_model.doesSurfaceExist( surface_id ),
                          std::runtime_error,
                          "Estimator " << estimator_id << " has a "
                          "surface id assigned (" << surface_id << " that "
                          "does not exist in the model!" );
    }
  }
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::EventHandler );

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler.cpp
//---------------------------------------------------------------------------//
