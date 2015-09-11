//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  The batched distributed particle simulation manager class def.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// Trilinos Includes
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Tuple.hpp>

// MPI Includes
#ifdef HAVE_FRENSIE_MPI
#endif

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "FRENSIE_mpi_config.hpp"

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
	    const unsigned long long start_history,
	    const unsigned long long previously_completed_histories,
	    const double previous_run_time )
  : ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>( number_of_histories, start_history, 0ull, previous_run_time ),
    d_comm( comm ),
    d_root_process( root_process ),
    d_initial_histories_completed( previously_completed_histories )
{
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  // Make sure the communicator is valid
  testPrecondition( !comm.is_null() );
}

// Run the simulation set up by the user
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::runSimulation()
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );

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
  this->setStartTime( ::MPI_Wtime() );

  if( d_comm->getRank() == d_root_process )
    this->coordinateWorkers();
  else
    this->work();

  // Calculate the total work done
  this->calculateTotalWorkDone();

  // Wait for all processes to finish their tasks
  d_comm->barrier();

  // Perform a reduction of the estimator data on the root process
  EMI::reduceEstimatorData( d_comm, d_root_process );

  // Set the end time
  this->setEndTime( ::MPI_Wtime() );

  if( d_comm->getRank() == d_root_process )
    std::cout << "done." << std::endl;

#else
  if( d_comm->getRank() == d_root_process )
  {
    std::cout << "The simulation cannot be run without building with MPI!"
	      << std::endl;
  }
#endif // end HAVE_FRENSIE_MPI
}

// Coordinate the workers (master only)
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::coordinateWorkers()
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  // Make sure the root process is calling this function
  testPrecondition( d_comm->getRank() == d_root_process );

  // Cast the communicator to an MpiComm object
  Teuchos::RCP<const Teuchos::MpiComm<unsigned long long> > mpi_comm = 
    Teuchos::rcp_dynamic_cast<const Teuchos::MpiComm<unsigned long long> >( 
								      d_comm );
  // The number of batches that need to be run
  unsigned long long number_of_batches = 25*mpi_comm->getSize();
  
  // The size of each batch (except possibly the last batch)
  unsigned long long batch_size = 
    this->getNumberOfHistories()/number_of_batches;

  // The current batch number
  unsigned batch_number = 0;

  // The batch info (start history, end history + 1)
  Teuchos::Tuple<unsigned long long,2> batch_info;

  // The idle worker info
  Teuchos::RCP<const Teuchos::CommStatus<unsigned long long> > 
    idle_worker_info;
  
  // The root process will handle all batch requests and data collection
  while( true )
  {
    // All batches complete - tell workers to stop
    if( batch_number == number_of_batches )
    {
      this->tellWorkersToStop( *mpi_comm );

      break;
    }
    // Check for an idle worker to assign the next batch to
    else if( this->isIdleWorkerPresent( *mpi_comm, idle_worker_info ) )
    {  
      // Set the batch start history
      batch_info[0] = batch_number*batch_size;
      
      // Set the batch end history
      batch_info[1] = batch_info[0] + batch_size;
      
      // Check if the size of the last batch is correct
      if( batch_number == number_of_batches - 1 )
      {
	batch_info[1] += 
	  this->getNumberOfHistories()-number_of_batches*batch_size;
      }
      
      this->assignWorkToIdleWorker( *mpi_comm, *idle_worker_info, batch_info );
      
      // Increment the batch number
      ++batch_number;
    }
  }  
#endif // end HAVE_FRENSIE_MPI
}

// Tell workers to stop working
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::tellWorkersToStop(
			 const Teuchos::MpiComm<unsigned long long>& mpi_comm )
	       
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  // Make sure the root process is calling this function
  testPrecondition( mpi_comm.getRank() == d_root_process );

  // The number of histories completed by each worker
  Teuchos::Array<unsigned long long> worker_histories_completed( 
							  mpi_comm.getSize() );

  // The request for each worker
  Teuchos::Array<MPI_Request> requests;

  // The MPI error code return
  int return_value;

  for( int i = 0; i < mpi_comm.getSize(); ++i )
  {
    if( i != d_root_process )
    {
      // The recv request
      MPI_Request raw_recv_request;
      
      return_value = ::MPI_Irecv( &worker_histories_completed[i],
				  1,
				  MPI_UNSIGNED_LONG_LONG,
				  i,
				  mpi_comm.getTag(),
				  *mpi_comm.getRawMpiComm(),
				  &raw_recv_request );

      TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			  std::runtime_error,
			  "Error: unable to get receive message on root "
			  "process " << d_root_process << " from worker "
			  "process " << i << "! "
			  "MPI_Irecv failed with the following error: "
			  << Teuchos::mpiErrorCodeToString(return_value) );

      requests.push_back( raw_recv_request );
      
      // The stop message
      unsigned long long stop = 1;
      
      // The send request
      MPI_Request raw_stop_request;
	  
      return_value = ::MPI_Isend( &stop,
				  1,
				  MPI_UNSIGNED_LONG_LONG,
				  i,
				  mpi_comm.getTag(),
				  *mpi_comm.getRawMpiComm(),
				  &raw_stop_request );
      
      TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			  std::runtime_error,
			  "Error: unable to send batch info from "
			  "root process " << d_root_process << 
			  "to worker process " << i << "! "
			  "MPI_Isend failed with the following error: "
			  << Teuchos::mpiErrorCodeToString(return_value));

      // Save the stop request
      requests.push_back( raw_stop_request );
    }
  }
  
  // Wait until all workers have responded to the stop request to
  // ensure that the work completed by each worker is up-to-date
  return_value = ::MPI_Waitall( requests.size(),
				requests.getRawPtr(),
				MPI_STATUSES_IGNORE );

  TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
		      std::runtime_error,
		      "Error: the root process " << d_root_process <<
		      " was unable to wait for the worker process to stop! "
		      "MPI_Waitall failed with the following error: "
		      << Teuchos::mpiErrorCodeToString(return_value) );
  
#endif // end HAVE_FRENSIE_MPI
}

// Check for idle worker
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
bool BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::isIdleWorkerPresent(
		  const Teuchos::MpiComm<unsigned long long>& mpi_comm,
		  Teuchos::RCP<const Teuchos::CommStatus<unsigned long long> >&
		  idle_worker_info )
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  // Make sure the root process is calling this function
  testPrecondition( mpi_comm.getRank() == d_root_process );
  
  // Probe for an idle worker
  int waiting = false;
  MPI_Status raw_status;
      
  int return_value = MPI_Iprobe( MPI_ANY_SOURCE,
				 mpi_comm.getTag(),
				 *mpi_comm.getRawMpiComm(),
				 &waiting,
				 &raw_status );
  
  TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
		      std::runtime_error,
		      "Error: unable to perform mpi probe in "
		      "batched distributed particle simulation manager! "
		      "MPI_Probe failed with the following error: "
		      << Teuchos::mpiErrorCodeToString( return_value ) );

  // Set the idle worker info
  if( waiting )
  {
    idle_worker_info.reset( 
		new Teuchos::MpiCommStatus<unsigned long long>( raw_status ) );
  }

  return waiting;
#endif // end HAVE_FRENSIE_MPI
}

// Assign work to idle workers
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::assignWorkToIdleWorker(
	    const Teuchos::MpiComm<unsigned long long>& mpi_comm,
	    const Teuchos::CommStatus<unsigned long long>& c_idle_worker_info,
	    const Teuchos::Tuple<unsigned long long,2>& task )
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  // Make sure the root process is calling this function
  testPrecondition( mpi_comm.getRank() == d_root_process );
  // Make sure the task is valid
  testPrecondition( task[1] > task[0] );

  // Note: the Teuchos::CommStatus object does not declare the getter functions
  // const (possible bug)
  Teuchos::CommStatus<unsigned long long>& idle_worker_info = 
    const_cast<Teuchos::CommStatus<unsigned long long>&>( c_idle_worker_info );

  unsigned long long message;
	
  // Contact the idle worker
  int return_value = ::MPI_Recv( &message,
				 1,
				 MPI_UNSIGNED_LONG_LONG,
				 idle_worker_info.getSourceRank(),
				 idle_worker_info.getTag(),
				 *mpi_comm.getRawMpiComm(),
				 MPI_STATUS_IGNORE );
  
  TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
		      std::runtime_error,
		      "Error: unable to get receive message on root "
		      "process " << d_root_process << " from worker "
		      "process " << idle_worker_info.getSourceRank() << "! "
		      "MPI_Recv failed with the following error: "
		      << Teuchos::mpiErrorCodeToString(return_value) );
	
  // Assign the task to the worker
  return_value = ::MPI_Send( task.getRawPtr(),
			     task.size(),
			     MPI_UNSIGNED_LONG_LONG,
			     idle_worker_info.getSourceRank(),
			     mpi_comm.getTag(),
			     *mpi_comm.getRawMpiComm() );
	
  TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
		      std::runtime_error,
		      "Error: unable to send batch info from "
		      "root process " << d_root_process << "to worker "
		      "process " << idle_worker_info.getSourceRank() << "! "
		      "MPI_Send failed with the following error: "
		      << Teuchos::mpiErrorCodeToString(return_value) );

#endif // end HAVE_FRENSIE_MPI
}

// Complete work for the master
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::work()
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );
  // Make sure only the worker process call this method
  testPrecondition( d_comm->getRank() != d_root_process );

  Teuchos::RCP<const Teuchos::MpiComm<unsigned long long> > mpi_comm = 
    Teuchos::rcp_dynamic_cast<const Teuchos::MpiComm<unsigned long long> >( 
								      d_comm );
  
  // The batch info array that will be passed to workers
  Teuchos::Tuple<unsigned long long,2> batch_info;
  
  // The MPI error code
  int return_value;
  
  while( true )
  {
    unsigned long long work_completed = 
      this->getNumberOfHistoriesCompleted();
      
    // Humbly request a new batch - wait patiently until you get one
    return_value = ::MPI_Send( &work_completed, 
			       1,
			       MPI_UNSIGNED_LONG_LONG,
			       d_root_process,
			       mpi_comm->getTag(),
			       *mpi_comm->getRawMpiComm() );
      
    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			std::runtime_error,
			"Error: worker process " 
			<< mpi_comm->getRank() <<
			" unable to request work from root process "
			<< d_root_process << "! "
			"MPI_Send failed with the following error: "
			<< Teuchos::mpiErrorCodeToString( return_value ) );
    
    MPI_Status raw_batch_status;
    
    // The master has graciously given you work
    return_value = ::MPI_Recv( batch_info.getRawPtr(),
			       batch_info.size(),
			       MPI_UNSIGNED_LONG_LONG,
			       d_root_process,
			       mpi_comm->getTag(),
			       *mpi_comm->getRawMpiComm(),
			       &raw_batch_status );
    
    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			std::runtime_error,
			"Error: worker process "
			<< mpi_comm->getRank() <<
			" unable to receive work from root process "
			<< d_root_process << "! "
			"MPI_Recv failed with the following error: "
			<< Teuchos::mpiErrorCodeToString( return_value ) );
    
    int exit_condition;
    
    // Check if the exit condition was sent
    return_value = ::MPI_Get_count( &raw_batch_status,
				    MPI_UNSIGNED_LONG_LONG,
				    &exit_condition );
    
    // Run the simulation batch
    if( exit_condition != 1 )
      this->runSimulationBatch( batch_info[0], batch_info[1] );
    // All of the batches are complete
    else
      break;
  }
#endif // end HAVE_FRENSIE_MPI
}

// Calculate the total work done
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::calculateTotalWorkDone()
{
#ifdef HAVE_FRENSIE_MPI
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );

  // Get the mpi comm object
  Teuchos::RCP<const Teuchos::MpiComm<unsigned long long> > mpi_comm = 
    Teuchos::rcp_dynamic_cast<const Teuchos::MpiComm<unsigned long long> >( 
								      d_comm );
  
  unsigned long long histories_completed, total_histories_completed;

  // Calculate the work done by all workers
  if( mpi_comm->getRank() != d_root_process )
    histories_completed = this->getNumberOfHistoriesCompleted();
  else
    histories_completed = d_initial_histories_completed;
  
  int return_value = ::MPI_Reduce( &histories_completed,
				   &total_histories_completed,
				   1,
				   MPI_UNSIGNED_LONG_LONG,
				   MPI_SUM,
				   d_root_process,
				   *mpi_comm->getRawMpiComm() );
    
  // Only the root process will keep track of the total histories completed - 
  // the workers will only keep track of the histories that they have completed
  if( mpi_comm->getRank() == d_root_process )
    this->setHistoriesCompleted( total_histories_completed );

#endif // end HAVE_FRENSIE_MPI
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
void BatchedDistributedParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::exportSimulationData( const std::string& data_file_name ) const
{
  // Make sure the global MPI session has been initialized
  testPrecondition( Teuchos::GlobalMPISession::mpiIsInitialized() );
  testPrecondition( !Teuchos::GlobalMPISession::mpiIsFinalized() );

  if( d_comm->getRank() == d_root_process )
  {
    ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::exportSimulationData( data_file_name );
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

#endif // end FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
