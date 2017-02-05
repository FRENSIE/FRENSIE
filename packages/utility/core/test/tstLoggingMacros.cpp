//---------------------------------------------------------------------------//
//!
//! \file   tstLoggingMacros.cpp
//! \author Alex Robinson
//! \brief  Logging macros unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_error )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Add the standard log attributes
  FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( cout );

  // Log an error
  FRENSIE_LOG_ERROR( "testing" );
  //std::cout << os_ptr->str() << std::endl;
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// end tstLoggingMacros.cpp
//---------------------------------------------------------------------------//
