//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingHelper_def.hpp
//! \author Alex Robinson
//! \brief  Logging helper class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOGGING_HELPER_DEF_HPP
#define UTILITY_LOGGING_HELPER_DEF_HPP

namespace Utility{

// Add a global log filter
template<typename FilterExpression>
inline void LoggingHelper::addGlobalLogFilter( FilterExpression expr )
{
  boost::log::core::get()->add_filter( expr );
}

// Add standard log sinks using the requested output streams
template<template<typename,...> class STLCompliantArray>
void LoggingHelper::addStandardLogSinks(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array )
{
  
}

// Add a standard error log sink using the requested output streams
template<template<typename,...> class STLCompliantArray>
void LoggingHelper::addStandardErrorLogSink(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array )
{
  // Set up the error log sink backend
  boost::shared_ptr<FancyTextSinkBackend>
    error_sink_backend( new FancyTextSinkBackend );

  for( size_t i = 0; i < os_array.size(); ++i )
    error_sink_backend->add_stream( os_array[i] );

  // Set up the error log sink
  LoggingHelper::initializeAndAddErrorLogSink( error_sink_backend );
}

// Add a standard warning log sink using the requested output streams
template<template<typename,...> class STLCompliantArray>
void LoggingHelper::addStandardWarningLogSink(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array )
{
  // Set up the warning log sink backend
  boost::shared_ptr<FancyTextSinkBackend>
    warning_sink_backend( new FancyTextSinkBackend );

  for( size_t i = 0; i < os_array.size(); ++i )
    warning_sink_backend->add_stream( os_array[i] );

  // Set up the warning log sink
  LoggingHelper::initializeAndAddWarningLogSink( warning_sink_backend );
}

// Add a standard notification log sink using the requested output streams
template<template<typename,...> class STLCompliantArray>
void LoggingHelper::addStandardNotificationLogSink(
          const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array )
{
  // Set up the notification log sink backend
  boost::shared_ptr<FancyTextSinkBackend>
    notification_sink_backend( new FancyTextSinkBackend );

  for( size_t i = 0; i < os_array.size(); ++i )
    notification_sink_backend->add_stream( os_array[i] );

  // Set up the notification log sink
  LoggingHelper::initializeAndAddNotificationLogSink(
                                                   notification_sink_backend );
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
