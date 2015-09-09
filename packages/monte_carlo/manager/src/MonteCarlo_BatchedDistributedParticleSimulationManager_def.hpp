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
	    const unsigned number_of_histories,
	    const unsigned start_history,
	    const unsigned previously_completed_histories,
	    const double previous_run_time )
  : ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>( number_of_histories, start_history, previously_completed_histories, previous_run_time ),
    d_comm( comm ),
    d_root_process( root_process )
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

  if( d_comm->getRank() == d_root_process )
  {
    std::cout << "Starting simulation ... ";
    std::cout.flush();
  }

  // Set up the random number generator for the number of threads requested
  Utility::RandomNumberGenerator::createStreams();

  // Enable geometry thread support
  ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::GMI::enableThreadSupport(
	         Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  // Enable estimator thread support
  ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::EMI::enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  // Cast the communicator to an MpiComm object
  Teuchos::RCP<const Teuchos::MpiComm<unsigned long long> > mpi_comm = 
    Teuchos::rcp_dynamic_cast<const Teuchos::MpiComm<unsigned long long> >( 
								      d_comm );
  mpi_comm->barrier();

  // Set the start time
  this->setStartTime( ::MPI_Wtime() );

  // The number of batches that need to be run
  unsigned long long number_of_batches = 25*mpi_comm->getSize();
  
  // The size of each batch (except possibly the last batch)
  unsigned long long batch_size = 
    this->getNumberOfHistories()/number_of_batches;

  // The current batch number
  unsigned batch_number = 0;

  // The batch info array that will be passed to workers
  unsigned long long batch_info[2];
  
  // The MPI error code
  int return_value;
  
  while( true )
  {
    // The root process will handle all batch requests and data collection
    if( mpi_comm->getRank() == d_root_process )
    {
      // All batches complete - send quit message to workers
      if( batch_number == number_of_batches )
      {
	for( int i = 0; i < mpi_comm->getSize(); ++i )
	{
	  if( i != d_root_process )
	  {
	    int message;
	    
	    // The recv request
	    MPI_Request raw_recv_request;
	    
	    return_value = ::MPI_Irecv( &message,
					1,
					MPI_INT,
					i,
					mpi_comm->getTag(),
					*mpi_comm->getRawMpiComm(),
					&raw_recv_request );

	    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			      std::runtime_error,
			      "Error: unable to get receive message on root "
			      "process " << d_root_process << " from worker "
			      "process " << i << "! "
			      "MPI_Irecv failed with the following error: "
			      << Teuchos::mpiErrorCodeToString(return_value) );
	    
	    // The quit message
	    unsigned long long quit = 1;

	    // The send request
	    MPI_Request raw_send_request;

	    return_value = ::MPI_Isend( &quit,
					1,
					MPI_UNSIGNED_LONG_LONG,
					i,
					mpi_comm->getTag(),
					*mpi_comm->getRawMpiComm(),
					&raw_send_request );

	    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
				std::runtime_error,
				"Error: unable to send batch info from "
				"root process " << d_root_process << 
				"to worker process " << i << "! "
				"MPI_Isend failed with the following error: "
				<< Teuchos::mpiErrorCodeToString(return_value));
	  }
	}

	break;
      }
      // Keep assigning batches to workers until all have been completed
      else
      {
	// Probe for an idle worker
	int* message_waiting = NULL;
	MPI_Status raw_status;
	
	return_value = MPI_Iprobe( MPI_ANY_SOURCE,
				   mpi_comm->getTag(),
				   *mpi_comm->getRawMpiComm(),
				   message_waiting,
				   &raw_status );
	
	TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			    std::runtime_error,
			    "Error: unable to perform mpi probe in "
			    "batched distributed particle simulation manager! "
			    "MPI_Probe failed with the following error: "
			    << Teuchos::mpiErrorCodeToString( return_value ) );
	
	// Idle worker found - assign it a new batch
	if( message_waiting )
	{
	  int worker_rank = raw_status.MPI_SOURCE;
	  int message_tag = raw_status.MPI_TAG;
	  int message;
	  
	  // Initiate handshake with worker
	  return_value = ::MPI_Recv( &message,
				     1,
				     MPI_INT,
				     worker_rank,
				     message_tag,
				     *mpi_comm->getRawMpiComm(),
				     MPI_STATUS_IGNORE );
	  
	  TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			      std::runtime_error,
			      "Error: unable to get receive message on root "
			      "process " << d_root_process << " from worker "
			      "process " << worker_rank << "! "
			      "MPI_Recv failed with the following error: "
			      << Teuchos::mpiErrorCodeToString(return_value) );

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
	  
	  // Pass new start history to worker
	  return_value = ::MPI_Send( batch_info,
				     2,
				     MPI_UNSIGNED_LONG_LONG,
				     worker_rank,
				     mpi_comm->getTag(),
				     *mpi_comm->getRawMpiComm() );
	  
	  TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
			      std::runtime_error,
			      "Error: unable to send batch info from "
			      "root process " << d_root_process << "to worker "
			      "process " << worker_rank << "! "
			      "MPI_Send failed with the following error: "
			      << Teuchos::mpiErrorCodeToString(return_value) );
	  
	  // Increment the batch number
	  ++batch_number;
	}
      }
    }
    // The workers
    else
    {    
      int ready_for_work = 1;
      
      // Humbly request a new batch - wait patiently until you get one
      return_value = ::MPI_Send( &ready_for_work, 
				 1,
				 MPI_INT,
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
      
      // You've been given a new batch to work on!
      return_value = ::MPI_Recv( batch_info,
				 2,
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
  }

  // Wait for all processes to get to this point
  mpi_comm->barrier();

  // Perform a reduction of the estimator data on the root process
  ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::EMI::reduceData( d_comm, d_root_process );

  // Set the end time
  this->setEndTime( ::MPI_Wtime() );

  if( d_comm->getRank() == d_root_process )
    std::cout << "done." << std::endl;
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
    ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::signalHandler( signal );
  }
}

} // end MonteCarlo namespace

#endif // end FACEMC_BATCHED_DISTRIBUTED_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BatchedDistributedParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
