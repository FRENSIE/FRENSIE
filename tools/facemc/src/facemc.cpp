//---------------------------------------------------------------------------//
//!
//! \file   facemc.cpp
//! \author Alex Robinson
//! \brief  main facemc executable
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <signal.h>

// Trilinos Includes
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

  // Create the communicator
  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm(
                                 new Teuchos::SerialComm<unsigned long long> );

  return facemcCore( argc, argv, comm );
}

//---------------------------------------------------------------------------//
// end facemc.cpp
//---------------------------------------------------------------------------//
