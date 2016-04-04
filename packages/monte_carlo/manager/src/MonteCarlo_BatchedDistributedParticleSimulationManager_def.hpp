//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  The batched distributed particle simulation manager class def.
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define FRENSIE_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// Trilinos Includes
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Utility_CommHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::BatchedDistributedParticleSimulationManager( 
      const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process,
	    const unsigned long long number_of_histories,
	    const unsigned number_of_batches_per_processor,
	    const unsigned long long start_history,
	    const unsigned long long previously_completed_histories,
	    const double previous_run_time )
  : ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>( number_of_histories, start_history, 0ull, previous_run_time ),
    d_comm( comm ),
    d_root_process( root_process ),
    d_initial_histories_completed( previously_completed_histories ),
    d_number_of_batches_per_processor( number_of_batches_per_processor )
{
  // Make sure the communicator is valid
  testPrecondition( !comm.is_null() );
  // Make sure the communicator is for mpi
  testPrecondition( comm->getSize() > 1 );
}

// Run the simulation set up by the user
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::runSimulation()
{
  // Set up the random number generator for the number of threads requested
  Utility::RandomNumberGenerator::createStreams();

  // Enable geometry thread support
  GMI::enableThreadSupport(
	         Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  // Enable estimator thread support
  EMI::enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  d_comm->barrier();

  if( d_comm->getRank() == d_root_process )
  {
    std::cout << "Starting simulation ... ";
    std::cout.flush();
  }

  d_comm->barrier();

  // Set the start time
  this->setStartTime( Teuchos::Time::wallTime() );

  if( d_comm->getRank() == d_root_process )
    this->coordinateWorkers();
  else
    this->work();

  // Perform a reduction of the estimator data on the root process
  EMI::reduceObserverData( d_comm, d_root_process );

  // Set the end time
  this->setEndTime( Teuchos::Time::wallTime() );

  if( d_comm->getRank() == d_root_process )
    std::cout << "done." << std::endl;
}

// Coordinate the workers (master only)
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::coordinateWorkers()
{
  // The number of batches that need to be run (don't count master proc.)
  unsigned long long number_of_batches = 
    d_number_of_batches_per_processor*(d_comm->getSize()-1);
  
  // The size of each batch (except possibly the last batch)
  unsigned long long batch_size = 
    this->getNumberOfHistories()/number_of_batches;

  // The current batch number
  unsigned batch_number = 0;

  // The batch info (start history, end history + 1)
  Teuchos::Tuple<unsigned long long,2> batch_info;

  // The idle worker info
  Teuchos::RCP<Teuchos::CommStatus<unsigned long long> > 
    idle_worker_info;
  
  // The root process will handle all batch requests and data collection
  while( true )
  {
    // All batches complete - tell workers to stop
    if( batch_number == number_of_batches )
    {
      this->stopWorkersAndRecordWork();

      break;
    }
    // Check for an idle worker to assign the next batch to
    else if( this->isIdleWorkerPresent( idle_worker_info ) )
    {  
      // Set the batch start history
      batch_info[0] = batch_number*batch_size;
      
      // Set the batch end history (plus one)
      batch_info[1] = batch_info[0] + batch_size;
      
      // Check if the size of the last batch is correct
      if( batch_number == number_of_batches - 1 )
      {
	batch_info[1] += 
	  this->getNumberOfHistories()-number_of_batches*batch_size;
      }
      
      this->assignWorkToIdleWorker( *idle_worker_info, batch_info );
      
      // Increment the batch number
      ++batch_number;
    }
  }  
}

// Tell workers to stop working
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::stopWorkersAndRecordWork()
	       
{
  // The number of histories completed by each worker
  Teuchos::Array<Teuchos::RCP<unsigned long long> > 
    worker_histories_completed( d_comm->getSize() );
  
  for( unsigned i = 0; i < worker_histories_completed.size(); ++i )
    worker_histories_completed[i].reset( new unsigned long long( 0ull ) );

  // The request for each worker
  Teuchos::Array<Teuchos::RCP<Teuchos::CommRequest<unsigned long long> > > 
    requests;

  // The stop message
  Teuchos::ArrayRCP<const unsigned long long> stop( 2, 1ull );

  for( int i = 0; i < d_comm->getSize(); ++i )
  {
    if( i != d_root_process )
    {
      try{
        requests.push_back( 
              Teuchos::ireceive( *d_comm, worker_histories_completed[i], i ) );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Error: unable to get receive message on root "
                               "process " << d_root_process << " from worker "
                               "process " << i << "! " );
      
      try{
        requests.push_back( Teuchos::isend( *d_comm, stop, i ) );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Error: unable to send batch info from "
                               "root process " << d_root_process << 
                               "to worker process " << i << "! " );
    }
  }
  
  // Wait until all workers have responded to the stop request to
  // ensure that the work completed by each worker is up-to-date
  Teuchos::waitAll( *d_comm, requests() );

  // Calculate the total work completed by all workers
  unsigned long long total_histories_completed = d_initial_histories_completed;

  for( unsigned i = 0; i < worker_histories_completed.size(); ++i )
    total_histories_completed += *worker_histories_completed[i];

  this->setHistoriesCompleted( total_histories_completed );
}

// Check for idle worker
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
bool BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::isIdleWorkerPresent(
     Teuchos::RCP<Teuchos::CommStatus<unsigned long long> >& idle_worker_info )
{  
  // Probe for an idle worker
  bool idle_worker_present = false;

  try{
    idle_worker_present = Utility::iprobe( *d_comm, idle_worker_info );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: unable to probe for idle worker on root "
                           "process " << d_root_process << "!" );

  return idle_worker_present;
}

// Assign work to idle workers
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::assignWorkToIdleWorker(
	    const Teuchos::CommStatus<unsigned long long>& c_idle_worker_info,
	    const Teuchos::Tuple<unsigned long long,2>& task )
{
  // Make sure the task is valid
  testPrecondition( task[1] > task[0] );

  // Note: the Teuchos::CommStatus object does not declare the getter functions
  // const (possible bug)
  Teuchos::CommStatus<unsigned long long>& idle_worker_info = 
    const_cast<Teuchos::CommStatus<unsigned long long>&>( c_idle_worker_info );

  unsigned long long message;
	
  // Contact the idle worker
  try{
    unsigned long long source_rank = 
      Teuchos::receive( *d_comm, idle_worker_info.getSourceRank(), &message );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: unable to get receive message on root "
                           "process " << d_root_process << " from worker "
                           "process " 
                           << idle_worker_info.getSourceRank() << "! " );
  
  // Assign the task to the worker
  try{
    Teuchos::send<unsigned long long>( *d_comm, 
                                       task.size(),
                                       task.getRawPtr(), 
                                       idle_worker_info.getSourceRank() );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: unable to send batch info from "
                           "root process " << d_root_process << "to worker "
                           "process " 
                           << idle_worker_info.getSourceRank() << "! " );
}

// Complete work for the master
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::work()
{
  // The batch info array that will be passed to workers
  Teuchos::Tuple<unsigned long long,2> batch_info;
  
  while( true )
  {
    unsigned long long work_completed = 
      this->getNumberOfHistoriesCompleted();
      
    // Wait patiently for some work...
    try{
      Teuchos::send( *d_comm, work_completed, d_root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: worker process " 
                             << d_comm->getRank() <<
                             " unable to request work from root process "
                             << d_root_process << "! " );
        
    // Job assigned, lets get to it...
    try{
      Teuchos::receive<unsigned long long>( *d_comm, 
                                            d_root_process, 
                                            batch_info.size(),
                                            batch_info.getRawPtr() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: worker process "
                             << d_comm->getRank() <<
                             " unable to receive work from root process "
                             << d_root_process << "! " );
    
    // Run the simulation batch
    if( batch_info[0] < batch_info[1] )
      this->runSimulationBatch( batch_info[0], batch_info[1] );
    // All of the batches are complete
    else
      break;
  }
}

// Print the data in all estimators to the desired stream
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::printSimulationSummary( std::ostream &os ) const
{
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  
  if( d_comm->getRank() == d_root_process )
  {
    ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::printSimulationSummary( os );
  }
}

// Export the simulation data (to an hdf5 file)
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::exportSimulationData( 
                                             const std::string& data_file_name,
                                             std::ostream& os ) const
{
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );

  if( d_comm->getRank() == d_root_process )
  {
    ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::exportSimulationData( data_file_name, os );
  }
}

// Signal handler
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::signalHandler(int signal)
{
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );

  if( d_comm->getRank() == d_root_process )
  {
    //ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::signalHandler( signal );
    
    // Ask the user what to do
    std::cerr << " Status (s), Kill (k)" << std::endl;
    std::string option;
    std::cin >> option;

    if( option.compare( "s" ) == 0 )
    {
      this->printSimulationStateInfo();
    }
    else if( option.compare( "k" ) == 0 )
    {
      exit(0);
    }
  }
}

} // end MonteCarlo namespace

#endif // end FRENSIE_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
