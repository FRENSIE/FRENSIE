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
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_LogRecordType.hpp"

// Declare public global attributes
BOOST_LOG_ATTRIBUTE_KEYWORD( record_type_log_attr, "Severity", Utility::LogRecordType );
BOOST_LOG_ATTRIBUTE_KEYWORD( tag_log_attr, "Tag", std::string );

namespace Utility{

//! The logging helper class
class LoggingHelper
{

private:

  // Typedef for basic text sink backend type
  typedef boost::log::sinks::text_ostream_backend BasicTextSinkBackend;

  // Typedef for the basic text sink type
  typedef boost::log::sinks::synchronous_sink<BasicTextSinkBackend> BasicTextSink;

  // Typedef for fancy text sink backend type
  typedef Utilaity::FancyTextOStreamBackend FancyTextSinkBackend;

  // Typedef for the fancy text sink type
  typedef boost::log::sinks::synchronous_sink<FancyTextSinkBackend> FancyTextSink;

public:

  //! Typedef for the standard logger type
typedef boost::log::sources::severity_logger<Utility::LogRecordType> StandardLoggerType;

  //! Add standard global attributes
  static void addStandardGlobalAttributes();

  //! Add a global log filter
  template<typename FilterExpression>
  static void addGlobalLogFilter( FilterExpression expr );

  //! Add standard log sinks using the requested output stream
  static void addStandardLogSinks( const boost::shared_ptr<std::ostream>& os );

  //! Add standard log sinks using the requested console stream
  static void addStandardLogSinks( std::ostream& console_os );

  //! Add standard log sinks using the requested output streams
  template<template<typename,...> class STLCompliantArray>
  static void addStandardLogSinks(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array );

  //! Add a standard error log sink using the requested output stream
  static void addStandardErrorLogSink(
                                   const boost::shared_ptr<std::ostream>& os );

  //! Add a standard error log sink using the console stream
  static void addStandardErrorLogSink( std::ostream& console_os );
  
  //! Add a standard error log sink using the requested output streams
  template<template<typename,...> class STLCompliantArray>
  static void addStandardErrorLogSink(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array );

  //! Add a standard warning log sink using the requested output stream
  static void addStandardWarningLogSink(
                                   const boost::shared_ptr<std::ostream>& os );

  //! Add a standard warning log sink using the requested console stream
  static void addStandardWarningLogSink( std::ostream& console_os );
  
  //! Add a standard warning log sink using the requested output streams
  template<template<typename,...> class STLCompliantArray>
  static void addStandardWarningLogSink(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array );

  //! Add a standard notification log sink using the requested output stream
  static void addStandardNotificationLogSink(
                                   const boost::shared_ptr<std::ostream>& os );

  //! Add a standard notification log sink using the requested console stream
  static void addStandardNotificationLogSink( std::ostream& console_os );

  //! Add a standard notification log sink using the requested output streams
  template<template<typename,...> class STLCompliantArray>
  static void addStandardNotificationLogSink(
         const STLCompliantArray<boost::shared_ptr<std::ostream> >& os_array );

  //! Add a tag to the logger
  template<typename Logger>
  static void addTagToLogger( const std::string& tag, Logger& logger );

private:

  //! Initialize and add error log sink
  static void initializeAndAddErrorLogSink(
                 const boost::shared_ptr<FancyTextSinkBackend>& sink_backend );

  //! Initialize and add warning log sink
  static void initializeAndAddWarningLogSink(
                 const boost::shared_ptr<FancyTextSinkBackend>& sink_backend );

  //! Initialize and add notification log sink
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

