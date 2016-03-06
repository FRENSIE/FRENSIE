//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcH1-2500K-mpi.cpp
//! \author Alex Robinson
//! \brief  facemc executable mpi verification test for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_DefaultSerialComm.hpp>
#include <Teuchos_DefaultMpiComm.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "tstFacemcH1-2500K.hpp"
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
    success = testSimulationResults( "FacemcH1-2500K-mpi.h5" );
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
// end tstFacemcH1-2500K-mpi.cpp
//---------------------------------------------------------------------------//
