//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BatchedDistributedStandardParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  Batched distributed standard particle simulation manager class def
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define MONTE_CARLO_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<ParticleModeType mode>
BatchedDistributedStandardParticleSimulationManager<mode>::BatchedDistributedStandardParticleSimulationManager(
                 const std::string& simulation_name,
                 const std::string& archive_type,
                 const std::shared_ptr<const FilledGeometryModel>& model,
                 const std::shared_ptr<ParticleSource>& source,
                 const std::shared_ptr<EventHandler>& event_handler,
                 const std::shared_ptr<PopulationControl> population_controller,
                 const std::shared_ptr<const CollisionForcer> collision_forcer,
                 const std::shared_ptr<const SimulationProperties>& properties,
                 const uint64_t next_history,
                 const uint64_t rendezvous_number,
                 const bool use_single_rendezvous_file,
                 const std::shared_ptr<const Utility::Communicator>& comm )
  : StandardParticleSimulationManager<mode>( simulation_name,
                                             archive_type,
                                             model,
                                             source,
                                             event_handler,
                                             population_controller,
                                             collision_forcer,
                                             properties,
                                             next_history,
                                             rendezvous_number,
                                             use_single_rendezvous_file ),
  d_comm( comm ),
  d_batches_per_rendezvous( 0 )
{
  // Make sure that the communicator pointer is valid
  testPrecondition( comm.get() );
  // Make sure that the communicator is not a serial communicator
  testPrecondition( comm->size() > 1 );

  // Calculate the batch size
  d_batches_per_rendezvous =
    properties->getNumberOfBatchesPerProcessor()*(comm->size()-1);

  // Calculate the batch size
  uint64_t batch_size =
    this->getRendezvousBatchSize()/d_batches_per_rendezvous;

  TEST_FOR_EXCEPTION( batch_size == 0,
                      std::runtime_error,
                      "A batch size of 0 has been calculated! The batch size "
                      "properties must be changed so that a batch size of at "
                      "least 1 is calculated." );

  this->setBatchSize( batch_size );
}

// Run the simulation set up by the user with the ability to interrupt
/*! \details Distributed simulations cannot be interrupted. The
 * runSimulation method will be called after issuing a warning.
 */
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::runInterruptibleSimulation()
{
  if( d_comm->rank() == 0 )
  {
    FRENSIE_LOG_WARNING( "Distributed simulations cannot be interrupted!" );
  }

  this->runSimulation();
}

// Run the simulation set up by the user
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::runSimulation()
{
  // Make sure that all objects are initialized before running the simulation
  Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear();
  
  d_comm->barrier();

  FRENSIE_FLUSH_ALL_LOGS();
  
  if( d_comm->rank() == 0 )
  {
    FRENSIE_LOG_NOTIFICATION( "Simulation started. " );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  d_comm->barrier();

  // Enable thread support
  this->enableThreadSupport();

  if( d_comm->rank() == 0 )
    ParticleSimulationManager::rendezvous();
  
  // Reset data on non-root processes to avoid double counting
  else
    this->resetData();

  d_comm->barrier();

  // The simulation has started
  this->registerSimulationStartedEvent();

  if( d_comm->rank() == 0 )
    this->coordinateWorkers();
  else
    this->work();

  d_comm->barrier();

  // The simulation has finished
  this->registerSimulationStoppedEvent();

  if( d_comm->rank() == 0 )
  {
    FRENSIE_LOG_NOTIFICATION( "Simulation finished. " );
    
    FRENSIE_FLUSH_ALL_LOGS();
  }

  d_comm->barrier();
}

// Coorindate workers
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::coordinateWorkers()
{
  // The current batch number
  uint64_t batch_number = 0;

  // The batch info (start history, end history + 1)
  std::pair<uint64_t,uint64_t> task;

  // The idle worker info
  Utility::Communicator::Status idle_worker_info;

  bool rendezvous_required = false;
  
  while( true )
  {
    if( this->isSimulationComplete() )
    {
      this->stopWorkersAndRecordWork( true, rendezvous_required, batch_number );

      break;
    }
    else if( batch_number == d_batches_per_rendezvous )
    {
      this->stopWorkersAndRecordWork( false, true, batch_number );
      
      // The rendezvous is complete
      rendezvous_required = false;
      
      // Reset the batch number
      batch_number = 0;
      
      continue;
    }
    else if( this->isIdleWorkerPresent( idle_worker_info ) )
    {
      // Set the batch start history
      task.first = this->getNextHistory() + batch_number*this->getBatchSize();
      
      task.second = task.first + this->getBatchSize();

      // Check if the size of the last batch is correct
      if( batch_number == d_batches_per_rendezvous - 1 )
      {
        task.second += this->getRendezvousBatchSize() -
          d_batches_per_rendezvous*this->getBatchSize();
      }

      this->assignWorkToIdleWorker( idle_worker_info, task );

      // Increment the batch number
      ++batch_number;

      // A rendezvous is required
      rendezvous_required = true;
    }
  }
}

// Tell workers to stop working
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::stopWorkersAndRecordWork(
                                                const bool simulation_complete,
                                                const bool rendezvous_required,
                                                const uint64_t batch_number )
{
  // The idle worker messages
  std::vector<int> idle_worker_messages( d_comm->size()-1 );
  
  // The request for each worker
  std::vector<Utility::Communicator::Request> requests;

  // The stop message (0 = rendezvous batch complete - rendezvous,
  //                   1 = simulation complete - rendezvous,
  //                   2 = simulation complete - no rendezvous)
  std::pair<uint64_t,uint64_t> stop_message = std::make_pair( 0, 0 );

  if( simulation_complete )
  {
    stop_message.first += 1;
    stop_message.second += 1;

    if( !rendezvous_required )
    {
      stop_message.first += 1;
      stop_message.second += 1;
    }
  }

  for( int i = 1; i < d_comm->size(); ++i )
  {
    try{
      requests.push_back(
               Utility::ireceive( *d_comm, i, 0, idle_worker_messages[i-1] ) );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Uable to receie message on root process from "
                             "worker process " << i << "!" );
    
    try{
      requests.push_back( Utility::isend( *d_comm, i, 0, stop_message ) );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to send stop message from root process "
                             "to worker process " << i << "!" );
  }

  // Wait for the stop messages to send
  std::vector<Utility::Communicator::Status> statuses( requests.size() );

  Utility::wait( requests, statuses );

  // Increment the next history
  if( batch_number == d_batches_per_rendezvous )
    this->incrementNextHistory( this->getRendezvousBatchSize() );
  else
    this->incrementNextHistory( batch_number*this->getBatchSize() );

  // Rendezvous after rendezvous batch completed
  if( !simulation_complete )
    this->rendezvous();
  
  // Rendezvous after simulation completed (if required)
  else if( rendezvous_required )
    this->rendezvous();
}

// Check for idle worker
template<ParticleModeType mode>
bool BatchedDistributedStandardParticleSimulationManager<mode>::isIdleWorkerPresent( Utility::Communicator::Status& idle_worker_info )
{
  // Probe for an idle worker
  try{
    idle_worker_info = Utility::iprobe<int>( *d_comm );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to probe for idle worker on root "
                           "process!" );

  return idle_worker_info.hasMessageDetails();
}

// Assign work to idle worker
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::assignWorkToIdleWorker(
                         const Utility::Communicator::Status& idle_worker_info,
                         const std::pair<uint64_t,uint64_t>& task )
{
  // Contact the idle worker
  int idle_worker_message;
  
  try{
    Utility::receive( *d_comm,
                      idle_worker_info.source(),
                      idle_worker_info.tag(),
                      idle_worker_message );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to receive message on root process from "
                           "worker process "
                           << idle_worker_info.source() << "!" );

  // Assign the task to the worker
  try{
    Utility::send( *d_comm,
                   idle_worker_info.source(),
                   idle_worker_info.tag(),
                   task );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to send the work task from the root "
                           "process to worker process "
                           << idle_worker_info.source() << "!" );
}

// Complete assigned work
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::work()
{
  std::pair<uint64_t,uint64_t> task;

  int idle_message = 1;
  
  while( true )
  {
    // Tell the root process that a new task can be done
    try{
      Utility::send( *d_comm, 0, 0, idle_message );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Worker process " << d_comm->rank() <<
                             " unable to request work from root process!" );

    // Get the task from the root process
    try{
      Utility::receive( *d_comm, 0, 0, task );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Worker process " << d_comm->rank() <<
                             " unable to receive work from root process!" );

    // Run the simulation batch
    if( task.first != task.second )
      this->runSimulationBatch( task.first, task.second );
    else
    {
      // Rendezvous with the root process
      if( task.first < 2 )
        this->rendezvous();

      // The simulation is complete
      if( task.first > 0 )
        break;
    }
  }
}

// Print the simulation data to the desired stream
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::printSimulationSummary( std::ostream& os ) const
{
  if( d_comm->rank() == 0 )
    ParticleSimulationManager::printSimulationSummary( os );
}

// Log the simulation data
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::logSimulationSummary() const
{
  if( d_comm->rank() == 0 )
    ParticleSimulationManager::logSimulationSummary();
}

// The signal handler
/*! \details The signal handler will do nothing when MPI is used. This is due
 * to the way that the mpiexec program handles signals and signal propagation
 * (see the OpenMPI docs)
 */
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::signalHandler( int signal )
{ /* ... */ }

// Rendezvous (cache state)
template<ParticleModeType mode>
void BatchedDistributedStandardParticleSimulationManager<mode>::rendezvous()
{
  this->reduceData( *d_comm, 0 );

  if( d_comm->rank() == 0 )
    ParticleSimulationManager::rendezvous();

  d_comm->barrier();
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedStandardParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
