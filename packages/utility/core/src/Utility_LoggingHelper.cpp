//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingHelper.cpp
//! \author Alex Robinson
//! \brief  Logging helper class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/clock.hpp>

// FRENSIE Includes
#include "Utility_LoggingHelper.hpp"

// Declare hidden global attributes
BOOST_LOG_ATTRIBUTE_KEYWORD( line_id_log_attr,
                             FRENSIE_LOG_LINE_ID_ATTR_KEYWORD,
                             unsigned int );
BOOST_LOG_ATTRIBUTE_KEYWORD( scope_log_attr,
                             FRENSIE_LOG_SCOPE_ATTR_KEYWORD,
                             boost::log::attributes::named_scope::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( thread_id_log_attr,
                             FRENSIE_LOG_THREAD_ID_ATTR_KEYWORD,
                             boost::log::attributes::current_thread_id::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( proc_id_log_attr,
                             FRENSIE_LOG_PROCESS_ID_ATTR_KEYWORD,
                             boost::log::attributes::current_process_id::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( time_stamp_log_attr,
                             FRENSIE_LOG_TIME_STAMP_ATTR_KEYWORD,
                             boost::log::attributes::local_clock::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( chrono_log_attr,
                             FRENSIE_LOG_CHRONO_ATTR_KEYWORD,
                             boost::log::attributes::timer::value_type );

namespace Utility{

// Add standard global attributes
/*! \details The following attributes will be registered globally: 
 * ThreadID, Scope.
 */
void LoggingHelper::addStandardGlobalAttributes()
{
  boost::shared_ptr<boost::log::core> core = boost::log::core::get();

  core->add_global_attribute( FRENSIE_LOG_THREAD_ID_ATTR_KEYWORD,
                              boost::log::attributes::current_thread_id() );
  core->add_global_attribute( FRENSIE_LOG_SCOPE_ATTR_KEYWORD,
                              boost::log::attributes::named_scope() );
}

// Add standard log sinks using the requested output stream
void LoggingHelper::addStandardLogSinks(
                                    const boost::shared_ptr<std::ostream>& os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardLogSinks( os_array );
}

// Add standard log sinks using the requested console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardLogSinks( std::ostream& console_os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardLogSinks( os_array );
}

// Add a standard error log sink using the requested output stream
void LoggingHelper::addStandardErrorLogSink(
                                    const boost::shared_ptr<std::ostream>& os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardErrorLogSink( os_array );
}

// Add a standard error log sink using the console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardErrorLogSink( std::ostream& console_os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardErrorLogSink( os_array );
}
  
// Add a standard warning log sink using the requested output stream
void LoggingHelper::addStandardWarningLogSink(
                                    const boost::shared_ptr<std::ostream>& os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardWarningLogSink( os_array );
}

// Add a standard warning log sink using the requested console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardWarningLogSink( std::ostream& console_os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardWarningLogSink( os_array );
}
  
// Add a standard notification log sink using the requested output stream
void LoggingHelper::addStandardNotificationLogSink(
                                    const boost::shared_ptr<std::ostream>& os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardNotificationLogSink( os_array );
}

// Add a standard notification log sink using the requested console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardNotificationLogSink( std::ostream& console_os )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardNotificationLogSink( os_array );
}

// Remove all log sinks
void LoggingHelper::removeAllLogSinks()
{
  boost::log::core::get()->remove_all_sinks();
}

// Initialize and add error log sink
void LoggingHelper::initializeAndAddErrorLogSink(
                  const boost::shared_ptr<FancyTextSinkBackend>& sink_backend )
{
  // Add some dynamic formatting to the sink backend
  sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatErrorLogKeywords );
  
  // Set up the error sink
  boost::shared_ptr<FancyTextSink> error_sink(
                                           new FancyTextSink( sink_backend ) );

  error_sink->set_filter( record_type_log_attr == Utility::ERROR_RECORD );
    
  // Set the error record format
  error_sink->set_formatter(
        boost::log::expressions::stream
        << boost::log::expressions::if_( boost::log::expressions::has_attr( tag_log_attr ) && tag_log_attr == FRENSIE_LOG_NESTED_ERROR_TAG )
        [
          boost::log::expressions::stream
          << FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG
          << boost::log::expressions::smessage << "\n"
        ].else_
        [
          boost::log::expressions::stream
          << boost::log::expressions::if_( boost::log::expressions::has_attr( tag_log_attr ) )
          [
           boost::log::expressions::stream << tag_log_attr << " "
          ]
          << FRENSIE_LOG_ERROR_MSG << boost::log::expressions::smessage << "\n"
          << FRENSIE_LOG_LOCATION_MSG
          << boost::log::expressions::format_named_scope(
                                 FRENSIE_LOG_SCOPE_ATTR_KEYWORD,
                                 boost::log::keywords::format =
                                 "%f" FRENSIE_LOG_FILE_LINE_SEP "%l",
                                 boost::log::keywords::depth = 1,
                                 boost::log::keywords::incomplete_marker = "" )
          << "\n"
          << FRENSIE_LOG_STACK_MSG << FRENSIE_LOG_STACK_DELIMINATOR 
          << boost::log::expressions::format_named_scope(
                                           FRENSIE_LOG_SCOPE_ATTR_KEYWORD,
                                           boost::log::keywords::format = "%n",
                                           boost::log::keywords::delimiter =
                                           FRENSIE_LOG_STACK_DELIMINATOR )
          << "\n"
         ] );

  // Register the error sink with the logging core
  boost::log::core::get()->add_sink( error_sink );
}

// Initialize and add warning log sink
void LoggingHelper::initializeAndAddWarningLogSink(
                  const boost::shared_ptr<FancyTextSinkBackend>& sink_backend )
{
  // Add some dynamic formatting to the sink backend
  sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatWarningLogKeywords );

  // Set up the warning sink
  boost::shared_ptr<FancyTextSink> warning_sink(
                                           new FancyTextSink( sink_backend ) );

  warning_sink->set_filter( record_type_log_attr == Utility::WARNING_RECORD );
    
  // Set the warning record format
  warning_sink->set_formatter(
        boost::log::expressions::stream
        << boost::log::expressions::if_( boost::log::expressions::has_attr( tag_log_attr ) )
        [
         boost::log::expressions::stream << tag_log_attr << " "
        ]
        << FRENSIE_LOG_WARNING_MSG << boost::log::expressions::smessage << "\n"
        << FRENSIE_LOG_LOCATION_MSG
        << boost::log::expressions::format_named_scope(
                                 FRENSIE_LOG_SCOPE_ATTR_KEYWORD,
                                 boost::log::keywords::format =
                                 "%f" FRENSIE_LOG_FILE_LINE_SEP "%l",
                                 boost::log::keywords::depth = 1,
                                 boost::log::keywords::incomplete_marker = "" )
        << "\n" );

  // Register the warning sink with the logging core
  boost::log::core::get()->add_sink( warning_sink );
}

// Initialize and add notification log sink
void LoggingHelper::initializeAndAddNotificationLogSink(
                  const boost::shared_ptr<FancyTextSinkBackend>& sink_backend )
{
  // Add some dynamic formatting to the sink backend
  sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldWhiteKeyword, ".*: " );

  // Set up the notification sink
  boost::shared_ptr<FancyTextSink> notification_sink(
                                           new FancyTextSink( sink_backend ) );

  // Set the notification sink filter
  notification_sink->set_filter( record_type_log_attr <= Utility::NOTIFICATION_RECORD );
  
  notification_sink->set_formatter(
        boost::log::expressions::stream
        << boost::log::expressions::if_( boost::log::expressions::has_attr( tag_log_attr ) )
        [
         boost::log::expressions::stream << tag_log_attr << ": "
        ]
        << boost::log::expressions::smessage << "\n" );

  // Register the notification sink with the logging core
  boost::log::core::get()->add_sink( notification_sink );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LoggingHelper.cpp
//---------------------------------------------------------------------------//
