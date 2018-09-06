//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingHelper_def.hpp
//! \author Alex Robinson
//! \brief  Logging helper class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOGGING_HELPER_DEF_HPP
#define UTILITY_LOGGING_HELPER_DEF_HPP

// Boost Includes
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/core.hpp>

namespace Utility{

// Add a global log filter
template<typename FilterExpression>
inline void LoggingHelper::addGlobalLogFilter( FilterExpression expr )
{
  boost::log::core::get()->set_filter( expr );
}

// Add standard log sinks using the requested output streams
template<template<typename,typename...> class STLCompliantArray>
void LoggingHelper::addStandardLogSinks(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
          const bool asynchronous )
{
  LoggingHelper::addStandardErrorLogSink( os_array, asynchronous );
  LoggingHelper::addStandardWarningLogSink( os_array, asynchronous );
  LoggingHelper::addStandardNotificationLogSink( os_array, asynchronous );
}

// Add a standard error log sink using the requested output streams
template<template<typename,typename...> class STLCompliantArray>
void LoggingHelper::addStandardErrorLogSink(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
          const bool asynchronous )
{
  // Set up the error log sink backend
  boost::shared_ptr<FancyTextSinkBackend>
    error_sink_backend( new FancyTextSinkBackend );

  for( size_t i = 0; i < os_array.size(); ++i )
    error_sink_backend->add_stream( os_array[i] );

  // Set up the error log sink
  if( asynchronous )
    LoggingHelper::initializeAndAddErrorLogSink<FancyTextAsyncSink>( error_sink_backend );
  else
    LoggingHelper::initializeAndAddErrorLogSink<FancyTextSyncSink>( error_sink_backend );
}

// Add a standard warning log sink using the requested output streams
template<template<typename,typename...> class STLCompliantArray>
void LoggingHelper::addStandardWarningLogSink(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
          const bool asynchronous )
{
  // Set up the warning log sink backend
  boost::shared_ptr<FancyTextSinkBackend>
    warning_sink_backend( new FancyTextSinkBackend );

  for( size_t i = 0; i < os_array.size(); ++i )
    warning_sink_backend->add_stream( os_array[i] );

  // Set up the warning log sink
  if( asynchronous )
    LoggingHelper::initializeAndAddWarningLogSink<FancyTextAsyncSink>( warning_sink_backend );
  else
    LoggingHelper::initializeAndAddWarningLogSink<FancyTextSyncSink>( warning_sink_backend );
}

// Add a standard notification log sink using the requested output streams
template<template<typename,typename...> class STLCompliantArray>
void LoggingHelper::addStandardNotificationLogSink(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
          const bool asynchronous )
{
  // Set up the notification log sink backend
  boost::shared_ptr<FancyTextSinkBackend>
    notification_sink_backend( new FancyTextSinkBackend );

  for( size_t i = 0; i < os_array.size(); ++i )
    notification_sink_backend->add_stream( os_array[i] );

  // Set up the notification log sink
  if( asynchronous )
  {
    LoggingHelper::initializeAndAddNotificationLogSink<FancyTextAsyncSink>(
                                                   notification_sink_backend );
  }
  else
  {
    LoggingHelper::initializeAndAddNotificationLogSink<FancyTextSyncSink>(
                                                   notification_sink_backend );
  }
}

// Initialize and add error log sink
template<typename Sink>
void LoggingHelper::initializeAndAddErrorLogSink(
                  const boost::shared_ptr<FancyTextSinkBackend>& sink_backend )
{
  // Add some dynamic formatting to the sink backend
  sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatErrorLogKeywords );
  
  // Set up the error sink
  boost::shared_ptr<Sink> error_sink( new Sink( sink_backend ) );

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
          << "\n\n"
         ] );

  // Register the error sink with the logging core
  boost::log::core::get()->add_sink( error_sink );
}

// Initialize and add warning log sink
template<typename Sink>
void LoggingHelper::initializeAndAddWarningLogSink(
                  const boost::shared_ptr<FancyTextSinkBackend>& sink_backend )
{
  // Add some dynamic formatting to the sink backend
  sink_backend->addBasicDynamicFormattingOp( &DynamicOutputFormatter::formatWarningLogKeywords );

  // Set up the warning sink
  boost::shared_ptr<Sink> warning_sink( new Sink( sink_backend ) );

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
        << "\n\n" );

  // Register the warning sink with the logging core
  boost::log::core::get()->add_sink( warning_sink );
}

// Initialize and add notification log sink
template<typename Sink>
void LoggingHelper::initializeAndAddNotificationLogSink(
                  const boost::shared_ptr<FancyTextSinkBackend>& sink_backend )
{
  // Add some dynamic formatting to the sink backend
  sink_backend->addDynamicFormattingOp( &DynamicOutputFormatter::boldWhiteKeyword, ".*: " );

  // Set up the notification sink
  boost::shared_ptr<Sink> notification_sink( new Sink( sink_backend ) );

  // Set the notification sink filter
  notification_sink->set_filter( record_type_log_attr <= Utility::NOTIFICATION_RECORD );
  
  notification_sink->set_formatter(
        boost::log::expressions::stream
        << boost::log::expressions::if_( boost::log::expressions::has_attr( tag_log_attr ) && tag_log_attr != FRENSIE_LOG_PARTIAL_NOTIFICATION_TAG )
        [
         boost::log::expressions::stream << tag_log_attr << ": "
        ]
        << boost::log::expressions::smessage
        << boost::log::expressions::if_( (boost::log::expressions::has_attr( tag_log_attr ) && tag_log_attr != FRENSIE_LOG_PARTIAL_NOTIFICATION_TAG ) || !boost::log::expressions::has_attr( tag_log_attr ) )
        [
         boost::log::expressions::stream << "\n\n"
        ] );

  // Register the notification sink with the logging core
  boost::log::core::get()->add_sink( notification_sink );
}

// Add a tag to the logger
template<typename Logger>
inline void LoggingHelper::addTagToLogger( const std::string& tag,
                                           Logger& logger )
{
  logger.add_attribute( "Tag",
                        boost::log::attributes::constant<std::string>( tag ) );
}
  
} // end Utility namespace

#endif // end UTILITY_LOGGING_HELPER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_LoggingHelper_def.hpp
//---------------------------------------------------------------------------//
