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
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/clock.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_FancyTextOStreamBackend.hpp"

// Declare hidden global attributes
BOOST_LOG_ATTRIBUTE_KEYWORD( line_id_log_attr, "LineID", unsigned int );
BOOST_LOG_ATTRIBUTE_KEYWORD( scope_log_attr, "Scope", boost::log::attributes::named_scope::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( thread_id_log_attr, "ThreadID", boost::log::attributes::current_thread_id::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( proc_id_log_attr, "ProcessID", boost::log::attributes::current_process_id::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( time_stamp_log_attr, "TimeStamp", boost::log::attributes::local_clock::value_type );
BOOST_LOG_ATTRIBUTE_KEYWORD( chrono_log_attr, "Chrono", boost::log::attributes::timer::value_type );

// Make typedefs for the most common sink types
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> BasicTextSink;
typedef boost::log::sinks::synchronous_sink<Utility::FancyTextOStreamBackend> FancyTextSink;

namespace Utility{

// Add standard global attributes
/*! \details The following attributes will be registered globally: 
 * ThreadID, Scope.
 */
void addStandardGlobalAttributes()
{
  boost::shared_ptr<boost::log::core> core = boost::log::core::get();

  //core->add_global_attribute( "LineID", boost::log::attributes::counter<unsigned>(0) );
  core->add_global_attribute( "ThreadID", boost::log::attributes::current_thread_id() );
  //core->add_global_attribute( "TimeStamp", boost::log::attributes::local_clock() );
  core->add_global_attribute( "Scope", boost::log::attributes::named_scope() );
}

// This method should never be called directly
void addStandardLogSinks( const boost::shared_ptr<std::ostream>& os )
{
  addStandardErrorLogSink( os );
  addStandardWarningLogSink( os );
  addStandardNotificationLogSink( os );
}

// Add an error log sink using the requestd output stream
void addStandardErrorLogSink( const boost::shared_ptr<std::ostream>& os )
{
  // Set up the error sink backend
  boost::shared_ptr<FancyTextOStreamBackend>
    error_sink_backend( new FancyTextOStreamBackend );

  error_sink_backend->add_stream( os );

  error_sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldRedKeyword, "\\S*\\s*Error:" );
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
        << boost::log::expressions::if_( boost::log::expressions::has_attr<std::string>( "Tag" ) )
        [
         boost::log::expressions::stream << tag_log_attr << " "
        ]
        << "Error: "
        << boost::log::expressions::smessage
        << "\n  "
        << boost::log::expressions::format_named_scope(
             "Scope",
             boost::log::keywords::format = "Location: %f:%l\n  Stack: %n" )
        << "\n" );

  // Register the error sink with the logging core
  boost::log::core::get()->add_sink( error_sink );
}

// Add a warning log sink using the requested output stream
void addStandardWarningLogSink( const boost::shared_ptr<std::ostream>& os )
{
  // Set up the warning sink backend
  boost::shared_ptr<FancyTextOStreamBackend>
    warning_sink_backend( new FancyTextOStreamBackend );

  warning_sink_backend->add_stream( os );

  warning_sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldMagentaKeyword, "\\S*\\s*Warning:" );
  warning_sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatStandardFilenameKeywords );
  warning_sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldCyanKeyword, "Location:" );

  // Set up the warning sink
  boost::shared_ptr<FancyTextSink> warning_sink(
                                   new FancyTextSink( warning_sink_backend ) );

  warning_sink->set_filter( record_type_log_attr == Utility::WARNING_RECORD );
    
  // Set the warning record format
  warning_sink->set_formatter(
        boost::log::expressions::stream
        << boost::log::expressions::if_( boost::log::expressions::has_attr<std::string>( "Tag" ) )
        [
         boost::log::expressions::stream << tag_log_attr << " "
        ]
        << "Warning: "
        << boost::log::expressions::smessage
        << "\n  "
        << boost::log::expressions::format_named_scope(
               "Scope", boost::log::keywords::format = "Location: %f:%l" )
        << "\n" );

  // Register the warning sink with the logging core
  boost::log::core::get()->add_sink( warning_sink );
}

// Add a notification log sink using the requested output stream
void addStandardNotificationLogSink(
                                    const boost::shared_ptr<std::ostream>& os )
{
  // Set up the notification sink backend
  boost::shared_ptr<FancyTextOStreamBackend>
    notification_sink_backend( new FancyTextOStreamBackend );

  notification_sink_backend->add_stream( os );

  notification_sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldWhiteKeyword, "\\S+\\s*: " );

  // Set up the notification sink
  boost::shared_ptr<FancyTextSink> notification_sink(
                              new FancyTextSink( notification_sink_backend ) );

  // Set the notification sink filter
  notification_sink->set_filter( record_type_log_attr <= Utility::NOTIFICATION_RECORD );
  
  notification_sink->set_formatter(
        boost::log::expressions::stream
        << boost::log::expressions::if_( boost::log::expressions::has_attr<std::string>( "Tag" ) )
        [
         boost::log::expressions::stream << tag_log_attr << ": "
        ]
        << boost::log::expressions::smessage << "\n" );

  // Register the notification sink with the logging core
  boost::log::core::get()->add_sink( notification_sink );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LoggingMacros.cpp
//---------------------------------------------------------------------------//
