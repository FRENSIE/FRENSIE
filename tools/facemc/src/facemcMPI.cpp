//---------------------------------------------------------------------------//
//!
//! \file   facemcMPI.cpp
//! \author Alex Robinson
//! \brief  main facemc-mpi executable
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <signal.h>

// Trilinos Includes
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_DefaultMpiComm.hpp>
#include <Teuchos_DefaultSerialComm.hpp>

// FRENSIE Includes
#include "facemcCore.hpp"

// The signal handler
void signalHandlerWrapper(int signal)
{
  if( facemc_manager.get() )
    facemc_manager->signalHandler(signal);
}

// Main facemc function
int main( int argc, char** argv )
{
  // Assign the signal handler
  void (*handler)(int);
  handler = signal(SIGINT,signalHandlerWrapper);

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  // Create the communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm;
  
  if( Teuchos::GlobalMPISession::mpiIsInitialized() )
    comm.reset( new Teuchos::MpiComm<unsigned long long>( MPI_COMM_WORLD ) );
  else
    comm.reset( new Teuchos::SerialComm<unsigned long long>() );

  return facemcCore( argc, argv, comm );
}

//---------------------------------------------------------------------------//
// end facemcMPI.cpp
//---------------------------------------------------------------------------//
