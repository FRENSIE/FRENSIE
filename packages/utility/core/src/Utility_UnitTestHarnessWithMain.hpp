//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestHarnessWithMain.hpp
//! \author Alex Robinson
//! \brief  The FRENSIE unit test harness header with a default main function
//!         provided
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_HARNESS_WITH_MAIN_HPP
#define UTILITY_UNIT_TEST_HARNESS_WITH_MAIN_HPP

// Std Lib Includes
#include <csignal>

// FRENSIE Includes
#include "Utility_UnitTestHarness.hpp"

//! A custom signal handler for seg faults
void SegFaultSignalHandler( int signal )      
{                                             
  throw std::runtime_error( "Seg Fault Detected!" ); 
}  


//! The default main function for running FRENSIE unit tests
int main( int argc, char** argv )                  
{                                                  
  signal( SIGSEGV, &SegFaultSignalHandler );
  
  Utility::UnitTestManager& unit_test_manager =
    Utility::UnitTestManager::getInstance();

  return unit_test_manager.runUnitTests( argc, argv );
}

#endif // end UTILITY_UNIT_TEST_HARNESS_WITH_MAIN_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestHarnessWithMain.hpp
//---------------------------------------------------------------------------//
