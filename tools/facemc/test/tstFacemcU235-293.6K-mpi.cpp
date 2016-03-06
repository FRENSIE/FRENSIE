//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcU235-293.6K-mpi.cpp
//! \author Alex Robinson
//! \brief  facemc executable mpi verification test for U-235 at 293.6K
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_DefaultSerialComm.hpp>
#include <Teuchos_DefaultMpiComm.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "tstFacemcU235-293.6K.hpp"
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
  
  int return_value = facemcCore( argc, argv, comm );
  
  // Test the simulation results
  bool success;

  if( return_value == 0 )
    success = testSimulationResults( "FacemcU235-293.6K-mpi.h5" );
  else // Bad return value
    success = false;
      
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
// end tstFacemcU235-293.6K-mpi.cpp
//---------------------------------------------------------------------------//
