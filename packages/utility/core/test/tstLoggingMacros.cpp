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

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_ERROR( "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_error )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_ERROR( "Tag", "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a scope error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_scope_error )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged scope error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_scope_error )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Tag", "testing" );

  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a warning can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_warning )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_WARNING_LOG( os_ptr );
  FRENSIE_SETUP_WARNING_LOG_WITH_CONSOLE( cout );

  // Log a warning
  std::cout << std::endl;
  FRENSIE_LOG_WARNING( "testing" );

  // Check that the warning was logged
  TEST_ASSERT( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged warning can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_warning )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_WARNING_LOG( os_ptr );
  FRENSIE_SETUP_WARNING_LOG_WITH_CONSOLE( cout );

  // Log a warning
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_WARNING( "Tag", "testing" );

  // Check that the warning was logged
  TEST_ASSERT( os_ptr->str().find( "Tag Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a notification can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_notification )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( cout );

  // Log a notification
  std::cout << std::endl;
  FRENSIE_LOG_NOTIFICATION( "testing" );

  // Check that the notification was logged
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged notification can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_notification )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( cout );

  // Log a notification
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Tag", "testing" );

  // Check that the notification was logged
  TEST_ASSERT( os_ptr->str().find( "Tag: testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_detail )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( cout );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_DETAILS( "testing detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "testing detail" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a tagged detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_detail )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( cout );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_DETAILS( "Tag", "testing detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Tag: testing detail" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a pedantic detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_pedantic_detail )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( cout );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing extra detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "testing extra detail" ) <
               os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a tagged pedantic detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_pedantic_detail )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( cout );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Tag", "testing extra detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Tag: testing extra detail" ) <
               os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that all of the logs can be set simultaneously
TEUCHOS_UNIT_TEST( LoggingMacros, setup_all_logs )
{
  // Make sure that all sinks have been removed from the log
  boost::log::core::get()->remove_all_sinks();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_STANDARD_LOGS( os_ptr );
  FRENSIE_SETUP_STANDARD_LOGS_WITH_CONSOLE( cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_ERROR( "testing" );
  FRENSIE_LOG_TAGGED_ERROR( "Tag", "testing" );
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Tag", "testing" );
  FRENSIE_LOG_WARNING( "testing" );
  FRENSIE_LOG_TAGGED_WARNING( "Tag", "testing" );
  FRENSIE_LOG_NOTIFICATION( "testing" );
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Tag", "testing" );
  FRENSIE_LOG_DETAILS( "testing" );
  FRENSIE_LOG_TAGGED_DETAILS( "Tag", "testing" );
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing" );
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Tag", "testing" );
}

//---------------------------------------------------------------------------//
// Check that a global filter can be set
TEUCHOS_UNIT_TEST( LoggingMacros, set_global_filter )
{
  
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::GlobalMPISession mpi_session( &argc, &argv );

  // Add the standard log attributes
  FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES();

  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstLoggingMacros.cpp
//---------------------------------------------------------------------------//
