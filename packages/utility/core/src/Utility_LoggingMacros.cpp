//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingMacros.cpp
//! \author Alex Robinson
//! \brief  Logging macro helper function definitions
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/clock.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_FancyTextOStreamBackend.hpp"

// Declare global attributes
BOOST_LOG_ATTRIBUTE_KEYWORD( record_type_log_attr, "Severity", Utility::LogRecordType );
BOOST_LOG_ATTRIBUTE_KEYWORD( line_id_log_attr, "LineID", unsigned int );
BOOST_LOG_ATTRIBUTE_KEYWORD( tag_log_attr, "Tag", std::string );
BOOST_LOG_ATTRIBUTE_KEYWORD( scope_log_attr, "Scope", boost::log::attributes::named_scope::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( thread_id_log_attr, "ThreadID", boost::log::attributes::current_thread_id::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( proc_id_log_attr, "ProcessID", boost::log::attributes::current_process_id::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( time_stamp_log_attr, "TimeStamp", boost::log::attributes::local_clock::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( chrono_log_attr, "Chrono", boost::log::attributes::timer::value_type );

// Make typedefs for the most common sink types
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> BasicTextSink;
typedef boost::log::sinks::synchronous_sink<Utility::FancyTextOStreamBackend> FancyTextSink;

namespace Utility{

// Add global attributes
/*! \details The following attributes will be registered globally: 
 * LineID, ThreadID, TimeStamp, Scope.
 */
void addGlobalAttributes()
{
  boost::shared_ptr<boost::log::core> core = boost::log::core::get();

  core->add_global_attribute( "LineID", boost::log::attributes::counter<unsigned>(0) );
  core->add_global_attribute( "ThreadID", boost::log::attributes::current_thread_id() );
  core->add_global_attribute( "TimeStamp", boost::log::attributes::local_clock() );
  core->add_global_attribute( "Scope", boost::log::attributes::named_scope() );
}

// This method should never be called directly
void addStandardLogSinks( const boost::shared_ptr<std::ostream>& os )
{
  
}

// Add an error log sink using the requestd output stream
void addErrorLogSink( const boost::shared_ptr<std::ostream>& os )
{
  // Set up the error sink backend
  boost::shared_ptr<FancyTextOStreamBackend>
    error_sink_backend( new FancyTextOStreamBackend );

  error_sink_backend->add_stream( os );

  error_sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatStandardErrorKeywords );
  error_sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatStandardFilenameKeywords );
  error_sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldCyanKeyword, "Location:" );
  error_sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldCyanKeyword, "Stack:" );

  // Set up the error sink
  boost::shared_ptr<FancyTextSink> error_sink(
                                     new FancyTextSink( error_sink_backend ) );

  error_sink->set_filter( record_type_log_attr == Utility::ERROR_RECORD );
    
  // Set the error record format
  error_sink->set_formatter(
        boost::log::expressions::stream
        << "Error: "
        << boost::log::expressions::smessage
        << boost::log::expressions::format_named_scope(
             "Scope",
             boost::log::keywords::format = "\nLocation: %f:%l\nStack: %n" ) );

  // Register the error sink with the logging core
  boost::log::core::get()->add_sink( error_sink );
}

// // Add a warning log sink using the requested output stream
// void addWarningLogSink( const boost::shared_ptr<std::ostream>& os )
// {
//   boost::shared_ptr<BasicTextSink> warning_sink = boost::make_shared<BasicTextSink>();

//   // Add the stream to write the warning log to
//   warning_sink->locked_backend()->add_stream( os );

//   // Set the warning sink filter
//   warning_sink->set_filter( record_type_log_attr == WARNING_RECORD );
  
//   warning_sink->set_formatter(
//         boost::log::expressions::stream
//         << record_type_log_attr << " from thread " << thread_id_log_attr << " at "
//         << boost::log::expressions::format_named_scope( "Scope", "%f:%l)" )
//         << ": " << boost::log::expressions::smessage );

//   // Register the warning sink with the logging core
//   boost::log::core::get()->add_sink( warning_sink );
// }

// // Add a notification log sink using the requested output stream
// void addNotificationLogSink( const boost::shared_ptr<std::ostream>& os )
// {
//   boost::shared_ptr<BasicTextSink> notification_sink =
//     boost::make_shared<BasicTextSink>();

//   // Add the stream to write the notification log to
//   notification_sink->locked_backend()->add_stream( os );

//   // Set the notification sink filter
//   notification_sink->set_filter( record_type_log_attr == NOTIFICATION_RECORD );
  
//   notification_sink->set_formatter(
//         boost::log::expressions::stream
//         << record_type_log_attr << " from thread " << thread_id_log_attr << " at "
//         << boost::log::expressions::format_named_scope( "Scope", "%f:%l)" )
//         << ": " << boost::log::expressions::smessage );

//   // Register the notification sink with the logging core
//   boost::log::core::get()->add_sink( notification_sink );
// }

// // Add a details log sink using the requested output stream
// void addDetailsLogSink( const boost::shared_ptr<std::ostream>& os )
// {
//   boost::shared_ptr<BasicTextSink> details_sink = boost::make_shared<BasicTextSink>();

//   // Add the stream to write the details log to
//   details_sink->locked_backend()->add_stream( os );

//   // Set the details sink filter
//   details_sink->set_filter( record_type_log_attr == DETAILS_RECORD );
  
//   details_sink->set_formatter(
//         boost::log::expressions::stream
//         << record_type_log_attr << " from thread " << thread_id_log_attr << " at "
//         << boost::log::expressions::format_named_scope( "Scope", "%f:%l)" )
//         << ": " << boost::log::expressions::smessage );

//   // Register the details sink with the logging core
//   boost::log::core::get()->add_sink( details_sink );
// }

// // Add a pedantic details log sink using the requested output stream
// void addPedanticDetailsLogSink( const boost::shared_ptr<std::ostream>& os )
// {
//   boost::shared_ptr<BasicTextSink> pedantic_details_sink = boost::make_shared<BasicTextSink>();

//   // Add the stream to write the pedantic details log to
//   pedantic_details_sink->locked_backend()->add_stream( os );

//   // Set the pedantic details sink filter
//   pedantic_details_sink->set_filter( record_type_log_attr == PEDANTIC_DETAILS_RECORD );
  
//   pedantic_details_sink->set_formatter(
//         boost::log::expressions::stream
//         << record_type_log_attr << " from thread " << thread_id_log_attr << " at "
//         << boost::log::expressions::format_named_scope( "Scope", "%f:%l)" )
//         << ": " << boost::log::expressions::smessage );

//   // Register the pedantic details sink with the logging core
//   boost::log::core::get()->add_sink( pedantic_details_sink );
// }
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LoggingMacros.cpp
//---------------------------------------------------------------------------//
