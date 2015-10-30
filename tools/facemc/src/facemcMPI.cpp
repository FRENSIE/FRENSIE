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

// FRENSIE Includes
#include "facemcCore.hpp"

// The signal handler
void signalHandlerWrapper(int signal)
{
  if( !facemc_manager.is_null() )
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

  int return_val = facemcCore( argc, argv );

  return return_val;
}

//---------------------------------------------------------------------------//
// end facemcMPI.cpp
//---------------------------------------------------------------------------//
