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
#include <vector>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
struct InitFixture{ InitFixture() { FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES(); } };

// Register the InitFixture with the test suite
BOOST_FIXTURE_TEST_SUITE( LoggingMacros, InitFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an error can be logged
BOOST_AUTO_TEST_CASE( log_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( std::cout );

  // Log an error
  FRENSIE_LOG_ERROR( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Check that the error was logged
  BOOST_CHECK( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged error can be logged
BOOST_AUTO_TEST_CASE( log_tagged_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( std::cout );

  // Log an error
  FRENSIE_LOG_TAGGED_ERROR( "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Check that the error was logged
  BOOST_CHECK( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a scope error can be logged
BOOST_AUTO_TEST_CASE( log_scope_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );
  
  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( os_array );

  // Log an error
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Check that the error was logged
  BOOST_CHECK( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged scope error can be logged
BOOST_AUTO_TEST_CASE( log_tagged_scope_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );
  
  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( os_array );

  // Log an error
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the error was logged
  BOOST_CHECK( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that an error can be logged with the provided logger
BOOST_AUTO_TEST_CASE( log_error_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( std::cout );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log an error
  FRENSIE_LOG_ERROR_WITH_LOGGER( custom_logger, "testing" );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Check that the error was logged
  BOOST_CHECK( os_ptr->str().find( "Custom Logger Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a scope error can be logged with the provided logger
BOOST_AUTO_TEST_CASE( log_scope_error_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( std::cout );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log an error
  FRENSIE_LOG_SCOPE_ERROR_WITH_LOGGER( custom_logger, "TestScope", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Check that the error was logged
  BOOST_CHECK( os_ptr->str().find( "Custom Logger Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that an error with the __NESTED__ tag can be logged
BOOST_AUTO_TEST_CASE( log_nested_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( std::cout );

  // Log a nested error
  FRENSIE_LOG_NESTED_ERROR( "Error: testing\n  Location: dummy.hpp:111" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the nested error was logged
  BOOST_CHECK( os_ptr->str().find( "Beginning nested errors..." ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Error: testing" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "dummy.hpp:111" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a warning can be logged
BOOST_AUTO_TEST_CASE( log_warning )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ASYNCHRONOUS_WARNING_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_WARNING_LOG( std::cout );

  // Log a warning
  std::cout << std::endl;
  FRENSIE_LOG_WARNING( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the warning was logged
  BOOST_CHECK( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged warning can be logged
BOOST_AUTO_TEST_CASE( log_tagged_warning )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_WARNING_LOG( os_array );

  // Log a warning
  FRENSIE_LOG_TAGGED_WARNING( "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the warning was logged
  BOOST_CHECK( os_ptr->str().find( "Tag Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a warning can be logged with the provided logger
BOOST_AUTO_TEST_CASE( log_warning_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_WARNING_LOG( os_array );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log a warning
  FRENSIE_LOG_WARNING_WITH_LOGGER( custom_logger, "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the warning was logged
  BOOST_CHECK( os_ptr->str().find( "Custom Logger Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a notification can be logged
BOOST_AUTO_TEST_CASE( log_notification )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG( std::cout );

  // Log a notification
  FRENSIE_LOG_NOTIFICATION( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the notification was logged
  BOOST_CHECK_EQUAL( os_ptr->str(), "testing\n\n" );
}

//---------------------------------------------------------------------------//
// Check that a partial notification can be logged
BOOST_AUTO_TEST_CASE( log_partial_notification )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG( std::cout );

  // Log a partial notification
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "test" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the partial notification was logged
  BOOST_CHECK_EQUAL( os_ptr->str(), "test" );

  FRENSIE_LOG_NOTIFICATION( "ing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the notification was logged
  BOOST_CHECK_EQUAL( os_ptr->str(), "testing\n\n" );
}

//---------------------------------------------------------------------------//
// Check that a tagged notification can be logged
BOOST_AUTO_TEST_CASE( log_tagged_notification )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_array );

  // Log a notification
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the notification was logged
  BOOST_CHECK_EQUAL( os_ptr->str(), "Tag: testing\n\n" );
}

//---------------------------------------------------------------------------//
// Check that a notification can be logged with the provided logger
BOOST_AUTO_TEST_CASE( log_notification_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_array );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log a notification
  FRENSIE_LOG_NOTIFICATION_WITH_LOGGER( custom_logger, "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the notification was logged
  BOOST_CHECK( os_ptr->str().find( "Custom Logger: testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a detail can be logged
BOOST_AUTO_TEST_CASE( log_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG( std::cout );

  // Log a detail
  FRENSIE_LOG_DETAILS( "testing detail" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "testing detail" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a tagged detail can be logged
BOOST_AUTO_TEST_CASE( log_tagged_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_array );

  // Log a detail
  FRENSIE_LOG_TAGGED_DETAILS( "Tag", "testing detail" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "Tag: testing detail" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a detail can be logged with the provided logger
BOOST_AUTO_TEST_CASE( log_detail_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_array );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log a detail
  FRENSIE_LOG_DETAILS_WITH_LOGGER( custom_logger, "testing detail" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "Custom Logger: testing detail" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a pedantic detail can be logged
BOOST_AUTO_TEST_CASE( log_pedantic_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG( std::cout );

  // Log a detail
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing extra detail" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "testing extra detail" ) <
               os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a tagged pedantic detail can be logged
BOOST_AUTO_TEST_CASE( log_tagged_pedantic_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os_array );

  // Log a detail
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Tag", "testing extra detail" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "Tag: testing extra detail" ) <
               os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that all of the logs can be set simultaneously
BOOST_AUTO_TEST_CASE( setup_all_logs )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_STANDARD_ASYNCHRONOUS_LOGS( os_ptr );
  FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS( std::cout );

  // Log an error
  FRENSIE_LOG_ERROR( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_ERROR( "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_WARNING( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_WARNING( "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Tag Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_NOTIFICATION( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Tag", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Tag:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_DETAILS( "testing details" );
  FRENSIE_FLUSH_ALL_LOGS();

#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "testing details" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_DETAILS( "Tag", "testing details" );
  FRENSIE_FLUSH_ALL_LOGS();

#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "Tag:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing details" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing pedantic details" );
  FRENSIE_FLUSH_ALL_LOGS();

#if HAVE_FRENSIE_DETAILED_LOGGING 
  BOOST_CHECK( os_ptr->str().find( "testing pedantic details" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Tag", "testing pedantic details" );
  FRENSIE_FLUSH_ALL_LOGS();

#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "Tag:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing pedantic details" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif
  
  os_ptr->str( "" );
  os_ptr->clear();
}

//---------------------------------------------------------------------------//
// Check that a global filter can be set
BOOST_AUTO_TEST_CASE( set_global_filter )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_STANDARD_ASYNCHRONOUS_LOGS( os_array );

  // Set the global log filter
  FRENSIE_SET_GLOBAL_LOG_FILTER( record_type_log_attr >= Utility::WARNING_RECORD || (boost::log::expressions::has_attr(tag_log_attr) && tag_log_attr == "Important") );

  // Log an error
  FRENSIE_LOG_ERROR( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_ERROR( "Fatal", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Fatal Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Fatal", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Fatal Error:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_WARNING( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_WARNING( "Critical", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Critical Warning:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_NOTIFICATION( "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Important", "testing" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().find( "Important:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_DETAILS( "testing details" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();

  FRENSIE_LOG_TAGGED_DETAILS( "Useless", "testing details" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();

  FRENSIE_LOG_TAGGED_DETAILS( "Important", "testing details" );
  FRENSIE_FLUSH_ALL_LOGS();

#if HAVE_FRENSIE_DETAILED_LOGGING
  BOOST_CHECK( os_ptr->str().find( "Important:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing details" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif
    
  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing pedantic details" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();

  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Useless", "testing pedantic details" );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Important", "testing pedantic details" );
  FRENSIE_FLUSH_ALL_LOGS();

#if HAVE_FRENSIE_DETAILED_LOGGING  
  BOOST_CHECK( os_ptr->str().find( "Important:" ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "testing pedantic details" ) < os_ptr->str().size() );
#else
  BOOST_CHECK( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstLoggingMacros.cpp
//---------------------------------------------------------------------------//
