//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcWater-293.6K-mpi.cpp
//! \author Alex Robinson
//! \brief  facemc executable mpi verification test for Water at 293.6K
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_DefaultSerialComm.hpp>
#include <Teuchos_DefaultMpiComm.hpp>
#include <Teuchos_CommHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "tstFacemcWater-293.6K.hpp"
#include "facemcCore.hpp"

int main( int argc, char** argv )
{
  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  // Create the communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm;
  
  if( Teuchos::GlobalMPISession::mpiIsInitialized() )
    comm.reset( new Teuchos::MpiComm<unsigned long long>( MPI_COMM_WORLD ) );
  else
    comm.reset( new Teuchos::SerialComm<unsigned long long> );
  
  int local_return_value = facemcCore( argc, argv, comm );
  
  // Test the simulation results (with root process only)
  if( comm->getRank() == 0 )
  {
    bool local_success;
    
    if( local_return_value == 0 )
      local_success = testSimulationResults( "FacemcWater-293.6K-mpi.h5" );
    else // Bad return value
      local_success = false;

    local_return_value = (local_success ? 0 : 1 );
  }

  // Reduce the simulation results
  int return_value;

  Teuchos::reduceAll( *comm,
                      Teuchos::REDUCE_SUM,
                      local_return_value,
                      Teuchos::inOutArg( return_value ) );

  bool success = (return_value == 0 ? true : false );
      
  if( comm->getRank() == 0 )
  {
    if( success )
      std::cout << "\nEnd Result: TEST PASSED" << std::endl;
    else
      std::cout << "\nEnd Result: TEST FAILED" << std::endl;
  }
  
  comm->barrier();

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstFacemcWater-293.6K-mpi.cpp
//---------------------------------------------------------------------------//
