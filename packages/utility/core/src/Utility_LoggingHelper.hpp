//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingHelper.hpp
//! \author Alex Robinson
//! \brief  Logging helper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOGGING_HELPER_HPP
#define UTILITY_LOGGING_HELPER_HPP

// Std Lib Includes
#include <iostream>
#include <vector>
#include <string>

// Boost Includes
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>

// FRENSIE Includes
#include "Utility_LogRecordType.hpp"
#include "Utility_FancyTextOStreamBackend.hpp"
#include "Utility_LoggingStaticConstants.hpp"

// Declare public global attributes
BOOST_LOG_ATTRIBUTE_KEYWORD( record_type_log_attr,
                             FRENSIE_LOG_RECORD_TYPE_ATTR_KEYWORD,
                             Utility::LogRecordType );
BOOST_LOG_ATTRIBUTE_KEYWORD( tag_log_attr,
                             FRENSIE_LOG_TAG_ATTR_KEYWORD,
                             std::string );

/*! \defgroup frensie_logging FRENSIE Logging.
 *
 * FRENSIE Logging is done through a series of macros that are designed to
 * hide the implementation details of the logs and also allow for certain
 * log details to be ignored with no associated overhead (see the
 * Logging Macros). 
 *
 * For those that are interest about the implementation of FRENSIE logging,
 * please note that we have simply wrapped much of the boost::log interface.
 * Some features that we deemed to be unnecessary for FRENSIE have been
 * hidden by our wrapper interface. We have also simplified the log setup
 * somewhat with our interface. As mentioned above, our interface also
 * allows for certain logging features to be turned off at configure time,
 * which can be important for performance since logging does incur some
 * overhead.
 */

namespace Utility{

/*! The logging helper class
 *
 * This class is primarily used as a backend for the FRENSIE logging
 * methods that cannot be inlined (e.g. log setup methods, logger attribute
 * methods, filter setting methods, etc.).
 * \ingroup frensie_logging
 */
class LoggingHelper
{

private:

  // Typedef for basic text sink backend type
  typedef boost::log::sinks::text_ostream_backend BasicTextSinkBackend;

  // Typedef for fancy text sink backend type
  typedef FancyTextOStreamBackend FancyTextSinkBackend;

  // Typedef for the basic text asynchronous sink type
  typedef boost::log::sinks::asynchronous_sink<BasicTextSinkBackend> BasicTextAsyncSink;

  // Typedef for the basic text synchronous sink type
  typedef boost::log::sinks::synchronous_sink<BasicTextSinkBackend>  BasicTextSyncSink;

  // Typedef for the fancy text asynchronous sink type
  typedef boost::log::sinks::asynchronous_sink<FancyTextSinkBackend> FancyTextAsyncSink;

  // Typedef for the fancy text synchronous sink type
  typedef boost::log::sinks::synchronous_sink<FancyTextSinkBackend> FancyTextSyncSink;

public:

  //! Typedef for the standard logger type
typedef boost::log::sources::severity_logger<Utility::LogRecordType> StandardLoggerType;

  //! Add standard global attributes
  static void addStandardGlobalAttributes();

  //! Add a global log filter
  template<typename FilterExpression>
  static void addGlobalLogFilter( FilterExpression expr );

  //! Add standard log sinks using the requested output stream
  static void addStandardLogSinks( const boost::shared_ptr<std::ostream>& os,
                                   const bool asynchronous = true );

  //! Add standard log sinks using the requested console stream
  static void addStandardLogSinks( std::ostream& console_os,
                                   const bool asynchronous = true );

  //! Add standard log sinks using the requested output streams
  template<template<typename,typename...> class STLCompliantArray>
  static void addStandardLogSinks(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
         const bool asynchronous = true );

  //! Add a standard error log sink using the requested output stream
  static void addStandardErrorLogSink(
                                   const boost::shared_ptr<std::ostream>& os,
                                   const bool asynchronous = true );

  //! Add a standard error log sink using the console stream
  static void addStandardErrorLogSink( std::ostream& console_os,
                                       const bool asynchronous = true );
  
  //! Add a standard error log sink using the requested output streams
  template<template<typename,typename...> class STLCompliantArray>
  static void addStandardErrorLogSink(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
         const bool asynchronous = true );

  //! Add a standard warning log sink using the requested output stream
  static void addStandardWarningLogSink(
                                   const boost::shared_ptr<std::ostream>& os,
                                   const bool asynchronous = true );

  //! Add a standard warning log sink using the requested console stream
  static void addStandardWarningLogSink( std::ostream& console_os,
                                         const bool asynchronous = true );
  
  //! Add a standard warning log sink using the requested output streams
  template<template<typename,typename...> class STLCompliantArray>
  static void addStandardWarningLogSink(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
         const bool asynchronous = true );

  //! Add a standard notification log sink using the requested output stream
  static void addStandardNotificationLogSink(
                                   const boost::shared_ptr<std::ostream>& os,
                                   const bool asynchronous = true );

  //! Add a standard notification log sink using the requested console stream
  static void addStandardNotificationLogSink( std::ostream& console_os,
                                              const bool asynchronous = true );

  //! Add a standard notification log sink using the requested output streams
  template<template<typename,typename...> class STLCompliantArray>
  static void addStandardNotificationLogSink(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array,
         const bool asynchronous = true );

  //! Remove all log sinks
  static void removeAllLogSinks();

  //! Flush all sinks
  static void flushAllLogSinks();

  //! Add a tag to the logger
  template<typename Logger>
  static void addTagToLogger( const std::string& tag, Logger& logger );

private:

  // Initialize and add error log sink
  template<typename Sink>
  static void initializeAndAddErrorLogSink(
                 const boost::shared_ptr<FancyTextSinkBackend>& sink_backend );

  // Initialize and add warning log sink
  template<typename Sink>
  static void initializeAndAddWarningLogSink(
                 const boost::shared_ptr<FancyTextSinkBackend>& sink_backend );

  // Initialize and add notification log sink
  template<typename Sink>
  static void initializeAndAddNotificationLogSink(
                 const boost::shared_ptr<FancyTextSinkBackend>& sink_backend );
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_LoggingHelper_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_LOGGING_HELPER_HPP

//---------------------------------------------------------------------------//
// end Utility_LoggingHelper.hpp
//---------------------------------------------------------------------------//

