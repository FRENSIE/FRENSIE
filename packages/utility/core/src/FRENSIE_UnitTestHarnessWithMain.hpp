//---------------------------------------------------------------------------//
//!
//! \file   FRENSIE_UnitTestHarnessWithMain.hpp
//! \author Alex Robinson
//! \brief  The FRENSIE unit test harness header with a default main function
//!         provided
//!
//---------------------------------------------------------------------------//

#ifndef FRENSIE_UNIT_TEST_HARNESS_WITH_MAIN_HPP
#define FRENSIE_UNIT_TEST_HARNESS_WITH_MAIN_HPP

// Std Lib Includes
#include <csignal>

// FRENSIE Includes
#include "FRENSIE_UnitTestHarnessWithMain.hpp"

//! A custom signal handler for seg faults
void SegFaultSignalHandler( int signal )      
{                                             
  throw std::logic_error( "Seg Fault Detected!" ); 
}                                                  

//! The default main function for running FRENSIE unit tests
int main( int argc, char** argv )                  
{                                                  
  signal( SIGSEGV, &SegFaultSignalHandler );
  
  Utility::UnitTestManager& unit_test_manager =
    Utility::UnitTestManager::getInstance();

  return unit_test_manager.runUnitTests( &argc, &argv );
}

#endif // end FRENSIE_UNIT_TEST_HARNESS_WITH_MAIN_HPP

//---------------------------------------------------------------------------//
// end FRENSIE_UnitTestHarnessWithMain.hpp
//---------------------------------------------------------------------------//