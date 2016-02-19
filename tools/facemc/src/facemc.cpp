//---------------------------------------------------------------------------//
//!
//! \file   facemc.cpp
//! \author Alex Robinson
//! \brief  main facemc executable
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <signal.h>

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

  int return_val = facemcCore( argc, argv );

  return return_val;
}

//---------------------------------------------------------------------------//
// end facemc.cpp
//---------------------------------------------------------------------------//
