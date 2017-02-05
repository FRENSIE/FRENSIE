//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingMacros.hpp
//! \author Alex Robinson
//! \brief  Macros that should be used for logging program execution info
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOGGING_MACROS_HPP
#define UTILITY_LOGGING_MACROS_HPP

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/expressions/keyword.hpp>

// FRENSIE Includes
#include "FRENSIE_config.hpp"
#include "Utility_LogRecordType.hpp"

namespace Utility{

//! Typedef for the standard logger type
typedef boost::log::sources::severity_logger<Utility::LogRecordType> StandardLoggerType;

//! Add standard global attributes
void addStandardGlobalAttributes();

//! Add standard log sinks using the requested output stream
void addStandardLogSinks( const boost::shared_ptr<std::ostream>& os );

//! Add a standard error log sink using the requestd output stream
void addStandardErrorLogSink( const boost::shared_ptr<std::ostream>& os );

//! Add a standard warning log sink using the requested output stream
void addStandardWarningLogSink( const boost::shared_ptr<std::ostream>& os );

//! Add a standard notification log sink using the requested output stream
void addStandardNotificationLogSink( const boost::shared_ptr<std::ostream>& os );
  
} // end Utility namespace

// Declare public global attributes
BOOST_LOG_ATTRIBUTE_KEYWORD( record_type_log_attr, "Severity", Utility::LogRecordType );
BOOST_LOG_ATTRIBUTE_KEYWORD( tag_log_attr, "Tag", std::string );

//! \brief Add the standard global attributes to the log
#define FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES()    \
  Utility::addStandardGlobalAttributes()

/*! \brief Add a global logging filter.
 *
 * This can be used to ignore any records that don't satisfy the expression.
 * Examples:
 *  <ol>
 *   <li> record_type_log_attr >= Utility::WARNING_RECORD </li>
 *   <li> record_type_log_attr == Utility::NOTIFICATION_RECORD ||
 *        record_type_log_attr == Utility::ERROR_RECORD </li>
 *   <li> record_type_log_attr < Utility::NOTIFICATION_RECORD ||
 *        record_type_log_attr >= Utility::WARNING_RECORD </li>
 *  </ol>
 */
#define FRENSIE_SET_GLOBAL_LOG_FILTER( filter_expr )    \
  boost::log::core::get()->add_filter( filter_expr )

/*! \brief Create a log using the requested ostream object (wrapped in a 
 * boost::shared_ptr).
 */
#define FRENSIE_SETUP_STANDARD_LOGS( boost_os_ptr )       \
  Utility::addStandardLogSinks( boost_os_ptr )

/*! Create a log using the requested console object
 * 
 * Only use cout, cerr and clog objects (without the std:: namespace).
 */
#define FRENSIE_SETUP_STANDARD_LOGS_WITH_CONSOLE( os )                  \
  boost::shared_ptr<std::ostream>                                       \
    console_##os##_ptr( &std::os, boost::null_deleter() );                \
  Utility::addStandardLogSinks( console_##os##_ptr )

/*! \brief Create an error log using the requested ostream object (wrapped in a
 * boost::shared_ptr).
 */
#define FRENSIE_SETUP_ERROR_LOG( boost_os_ptr ) \
  Utility::addStandardErrorLogSink( boost_os_ptr )

/*! \brief Create an error log using the requested console object
 *
 * Only use cout, cerr and clog objects (without the std:: namespace).
 */
#define FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( os )      \
  boost::shared_ptr<std::ostream>                       \
    error_console_##os##_ptr( &std::os, boost::null_deleter() );    \
  Utility::addStandardErrorLogSink( error_console_##os##_ptr )

/*! \brief Create a warning log using the requested ostream object (wrapped in
 * a boost::shared_ptr).
 */
#define FRENSIE_SETUP_WARNING_LOG( boost_os_ptr ) \
  Utility::addStandardWarningLogSink( boost_os_ptr );

/*! \brief Create a warning log using the requested console object
 *
 * Only use cout, cerr and clog objects (without the std:: namespace).
 */
#define FRENSIE_SETUP_WARNING_LOG_WITH_CONSOLE( os )    \
  boost::shared_ptr<std::ostream>                       \
    warning_console_##os##_ptr( &std::os, boost::null_deleter() );  \
  Utility::addStandardWarningLogSink( warning_console_##os##_ptr )

/*! \brief Create a notification log using the requested ostream object
 * (wrapped in a boost::shared_ptr)
 */
#define FRENSIE_SETUP_NOTIFICATION_LOG( boost_os_ptr )  \
  Utility::addStandardNotificationLogSink( boost_os_ptr );

/*! \brief Create a notification log using the requested console object
 *
 * Only use cout, cerr, clog objects (without the std:: namespace)
 */
#define FRENSIE_SETUP_NOTIFICATION_LOG_WITH_CONSOLE( os )       \
  boost::shared_ptr<std::ostream>                               \
    notification_console_##os##_ptr( &std::os, boost::null_deleter() );     \
  Utility::addStandardNotificationLogSink( notification_console_##os##_ptr )

//! Add the tag to the logger
#define FRENSIE_ADD_TAG_TO_LOGGER( tag, logger )        \
  logger.add_attribute( "Tag", boost::log::attributes::constant<std::string>( tag ) )

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_WITH_LOGGER__( type, logger, msg )    \
  BOOST_LOG_SEV( logger, type ) << msg 

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_WITH_LOGGER_GET_SCOPE__( type, logger, msg )  \
  BOOST_LOG_FUNCTION();                                                 \
  __FRENSIE_LOG_MSG_WITH_LOGGER__( type, logger, msg )

//! Never call this macro directly
#define __FRENSIE_LOG_SCOPE_MSG_WITH_LOGGER__( type, scope, logger, msg ) \
  BOOST_LOG_NAMED_SCOPE( scope );                                       \
  __FRENSIE_LOG_MSG_WITH_LOGGER__( type, logger, msg )

//! Never call this macro directly
#define __FRENSIE_LOG_MSG__( type, msg )                                \
  {                                                                     \
    Utility::StandardLoggerType slg;                                    \
    __FRENSIE_LOG_MSG_WITH_LOGGER__( type, slg, msg );                  \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_GET_SCOPE__( type, msg )                      \
  {                                                                     \
    Utility::StandardLoggerType slg;                                    \
    __FRENSIE_LOG_MSG_WITH_LOGGER_GET_SCOPE__( type, slg, msg );        \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_SCOPE_MSG__( type, scope, msg )                   \
  {                                                                     \
    Utility::StandardLoggerType slg;                                    \
    __FRENSIE_LOG_SCOPE_MSG_WITH_LOGGER__( type, scope, slg, msg );     \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_WITH_TAG__( type, tag, msg )      \
  {                                                         \
    Utility::StandardLoggerType slg;                        \
    FRENSIE_ADD_TAG_TO_LOGGER( tag, slg );                  \
    __FRENSIE_LOG_MSG_WITH_LOGGER__( type, slg, msg );      \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_WITH_TAG_GET_SCOPE__( type, tag, msg )        \
  {                                                                     \
    Utility::StandardLoggerType slg;                                    \
    FRENSIE_ADD_TAG_TO_LOGGER( tag, slg );                              \
    __FRENSIE_LOG_MSG_WITH_LOGGER_GET_SCOPE__( type,slg, msg );         \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_SCOPE_MESSAGE_WITH_TAG__( type, scope, tag, msg ) \
  {                                                                     \
    Utility::StandardLoggerType slg;                                    \
    FRENSIE_ADD_TAG_TO_LOGGER( tag, slg );                              \
    __FRENSIE_LOG_SCOPE_MSG_WITH_LOGGER__( type, scope, slg, msg );     \
  }

/*! Log an error
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_ERROR( msg )            \
  __FRENSIE_LOG_MSG_GET_SCOPE__( Utility::ERROR_RECORD, msg )

/*! Log a tagged error with the logger
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_TAGGED_ERROR( tag, msg )    \
  __FRENSIE_LOG_MSG_WITH_TAG_GET_SCOPE__( Utility::ERROR_RECORD, tag, msg )

//! Log an error in the scope
#define FRENSIE_LOG_SCOPE_ERROR( scope, msg )   \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::ERROR_RECORD, scope, msg )

//! Log a tagged error in the scope
#define FRENSIE_LOG_TAGGED_SCOPE_ERROR( scope, tag, msg )       \
  __FRENSIE_LOG_SCOPE_MESSAGE_WITH_TAG__( Utility::ERROR_RECORD, scope, tag, msg )

//! Log a warning
#define FRENSIE_LOG_WARNING( msg )                      \
  __FRENSIE_LOG_MSG_GET_SCOPE__( Utility::WARNING_RECORD, msg )

//! Log a tagged warning
#define FRENSIE_LOG_TAGGED_WARNING( tag, msg )  \
  __FRENSIE_LOG_MSG_WITH_TAG_GET_SCOPE__( Utility::WARNING_RECORD, tag, msg )

//! Log a notification
#define FRENSIE_LOG_NOTIFICATION( msg )                         \
  __FRENSIE_LOG_MSG__( Utility::NOTIFICATION_RECORD, msg )

//! Log a tagged notification
#define FRENSIE_LOG_TAGGED_NOTIFICATION( tag, msg )      \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::NOTIFICATION_RECORD, tag, msg )

#if HAVE_FRENSIE_DETAILED_LOGGING

//! Log details
#define FRENSIE_LOG_DETAILS( msg )                      \
  __FRENSIE_LOG_MSG__( Utility::DETAILS_RECORD, msg )

//! Log tagged details
#define FRENSIE_LOG_TAGGED_DETAILS( tag, msg )  \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::DETAILS_RECORD, tag, msg )

//! Log pedantic details
#define FRENSIE_LOG_PEDANTIC_DETAILS( msg )             \
  __FRENSIE_LOG_MSG__( Utility::PEDANTIC_DETAILS_RECORD, msg )

//! Log tagged pedantic details
#define FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( tag, msg )                  \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::PEDANTIC_DETAILS_RECORD, tag, msg )

//! Log the scope
#define FRENSIE_LOG_SCOPE() \
  BOOST_LOG_FUNCTION()

//! Log the scope name
#define FRENSIE_LOG_SCOPE_NAME( scope )              \
  BOOST_LOG_NAMED_SCOPE( scope )

#else // HAVE_FRENSIE_DETAILED_LOGGING

#define FRENSIE_LOG_DETAILS( msg )
#define FRENSIE_LOG_TAGGED_DETAILS( tag, msg )
#define FRENSIE_LOG_PEDANTIC_DETAILS( msg )
#define FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( tag, msg )

#define FRENSIE_LOG_SCOPE()
#define FRENSIE_LOG_SCOPE_NAME( scope )

#endif // end HAVE_FRENSIE_DETAILED_LOGGING

#endif // end UTILITY_LOGGING_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_LoggingMacros.hpp
//---------------------------------------------------------------------------//
