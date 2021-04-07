//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingMacros.hpp
//! \author Alex Robinson
//! \brief  Macros that should be used for logging program execution info
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOGGING_MACROS_HPP
#define UTILITY_LOGGING_MACROS_HPP

// FRENSIE Includes
#include "FRENSIE_config.hpp"
#include "Utility_LoggingHelper.hpp"
#include "Utility_LoggingStaticConstants.hpp"

/*! \defgroup logging_macros Logging Macros.
 *
 * These macros are designed to allow for easy logging of errors, warnings
 * and notifications without having to worry about how the logs are
 * set up. Thread safety is already taken care of so these macros can 
 * be used inside of methods that will be used in a multithreaded environment.
 * There are also some standard log setup methods. Note that there is
 * overhead associated with logging so it is generally advised that 
 * performance critical code avoid unnecessary logging. To address the issue
 * of logging info in performance critical code the LOG_DETAILS and 
 * LOG_PEDANTIC_DETAILS macros have been provided. These macros can be
 * disabled with the build system option FRENSIE_ENABLE_DETAILED_LOGGING=OFF.
 * When this option is turned off the detailed logging info and their 
 * associated overhead will be eliminated. The FRENSIE_LOG_SCOPE and
 * FRENSIE_LOG_SCOPE_NAME macros can be used to construct a stack trace.
 * They will also be disabled if the build system option
 * FRENSIE_ENABLE_DETAILED_LOGGING is set to OFF.
 * \ingroup frensie_logging
 */

/*! \brief Add the standard global attributes to the log
 * \ingroup logging_macros
 */
#define FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES()    \
  Utility::LoggingHelper::addStandardGlobalAttributes()

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
 *   <li> record_type_log_attr >= Utility::WARNING_RECORD &&
 *        (boost::log::expressions::has_attr(tag_log_attr) &&
 *        tag_attr == "Utility" </li>
 *  </ol>
 * \ingroup logging_macros
 */
#define FRENSIE_SET_GLOBAL_LOG_FILTER( filter_expr )    \
  Utility::LoggingHelper::addGlobalLogFilter( filter_expr )

/*! \brief Create synchronous logs using the requested ostream object. 
 *
 * This object should have one of the following types: 
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS( os )       \
  Utility::LoggingHelper::addStandardLogSinks( os, false )

/*! \brief Create asynchronous logs using the requested ostream object. 
 *
 * This object should have one of the following types: 
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_STANDARD_ASYNCHRONOUS_LOGS( os )       \
  Utility::LoggingHelper::addStandardLogSinks( os, true )

/*! \brief Create a synchronous error log using the requested ostream object.
 *
 * This object should have one of the following types:
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_SYNCHRONOUS_ERROR_LOG( os ) \
  Utility::LoggingHelper::addStandardErrorLogSink( os, false )

/*! \brief Create an asynchronous error log using the requested ostream object.
 *
 * This object should have one of the following types:
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_ASYNCHRONOUS_ERROR_LOG( os ) \
  Utility::LoggingHelper::addStandardErrorLogSink( os, true )

/*! \brief Create a synchronous warning log using the requested ostream object.
 * 
 * This object should have one of the following types:
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_SYNCHRONOUS_WARNING_LOG( os ) \
  Utility::LoggingHelper::addStandardWarningLogSink( os, false );

/*! \brief Create an asynchronous warning log using the requested ostream 
 * object
 * 
 * \details This object should have one of the following types:
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_ASYNCHRONOUS_WARNING_LOG( os ) \
  Utility::LoggingHelper::addStandardWarningLogSink( os, true );

/*! \brief Create a synchronous notification log using the requested ostream
 * object.
 * 
 * \details This object should have one of the following types:
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_SYNCHRONOUS_NOTIFICATION_LOG( os )  \
  Utility::LoggingHelper::addStandardNotificationLogSink( os, false );

/*! \brief Create an asynchronous notification log using the requested ostream
 * object.
 * 
 * \details This object should have one of the following types:
 * <ol>
 *  <li>std::cout </li>
 *  <li>std::cerr </li>
 *  <li>std::clog </li>
 *  <li>boost::shared_ptr<std::ostream> </li>
 *  <li>Array<boost::shared_ptr<std::ostream> > (where Array is any STL
 *      compliant array type). </li>
 * </ol>
 * Note that the console streams can be safely wrapped in a 
 * boost::shared_ptr<std::ostream> object by using the boost::null_deleter()
 * (e.g. boost::shared_ptr<std::ostream> 
 *  wrapped_cout( &std::cout, boost::null_deleter() ); ).
 * \ingroup logging_macros
 */
#define FRENSIE_SETUP_ASYNCHRONOUS_NOTIFICATION_LOG( os )  \
  Utility::LoggingHelper::addStandardNotificationLogSink( os, true );

/*! Remove all logs
 * \ingroup logging_macros
 */
#define FRENSIE_REMOVE_ALL_LOGS( os )           \
  Utility::LoggingHelper::removeAllLogSinks()

/*! Flush all logs
 * \ingroup logging_macros
 */
#define FRENSIE_FLUSH_ALL_LOGS()            \
  Utility::LoggingHelper::flushAllLogSinks()

/*! Add the tag to the logger
 * \ingroup logging_macros
 */
#define FRENSIE_ADD_TAG_TO_LOGGER( tag, logger )        \
  Utility::LoggingHelper::addTagToLogger( tag, logger );

/*! Log the scope
 * \details Use this macro to create a stack trace in the error log. This
 * macro should rarely be called directly (see the 
 * Utility_ExceptionTestMacros.hpp for a usage example).
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_SCOPE()                     \
  BOOST_LOG_FUNCTION()

/*! Log the scope name
 * \details Use this macro to create a stack trace in the error log. This
 * macro should rarely be called directly (see the 
 * Utility_ExceptionTestMacros.hpp for a usage example).
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_SCOPE_NAME( scope )              \
  BOOST_LOG_NAMED_SCOPE( scope )

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
    Utility::LoggingHelper::StandardLoggerType slg;                     \
    __FRENSIE_LOG_MSG_WITH_LOGGER__( type, slg, msg );                  \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_GET_SCOPE__( type, msg )                      \
  {                                                                     \
    Utility::LoggingHelper::StandardLoggerType slg;                     \
    __FRENSIE_LOG_MSG_WITH_LOGGER_GET_SCOPE__( type, slg, msg );        \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_SCOPE_MSG__( type, scope, msg )                   \
  {                                                                     \
    Utility::LoggingHelper::StandardLoggerType slg;                     \
    __FRENSIE_LOG_SCOPE_MSG_WITH_LOGGER__( type, scope, slg, msg );     \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_WITH_TAG__( type, tag, msg )      \
  {                                                         \
    Utility::LoggingHelper::StandardLoggerType slg;         \
    FRENSIE_ADD_TAG_TO_LOGGER( tag, slg );                  \
    __FRENSIE_LOG_MSG_WITH_LOGGER__( type, slg, msg );      \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_MSG_WITH_TAG_GET_SCOPE__( type, tag, msg )        \
  {                                                                     \
    Utility::LoggingHelper::StandardLoggerType slg;                     \
    FRENSIE_ADD_TAG_TO_LOGGER( tag, slg );                              \
    __FRENSIE_LOG_MSG_WITH_LOGGER_GET_SCOPE__( type,slg, msg );         \
  }

//! Never call this macro directly
#define __FRENSIE_LOG_SCOPE_MESSAGE_WITH_TAG__( type, scope, tag, msg ) \
  {                                                                     \
    Utility::LoggingHelper::StandardLoggerType slg;                     \
    FRENSIE_ADD_TAG_TO_LOGGER( tag, slg );                              \
    __FRENSIE_LOG_SCOPE_MSG_WITH_LOGGER__( type, scope, slg, msg );     \
  }

/*! Log an error
 * \details This macro will attempt to deduce the function scope.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ERROR( msg )            \
  __FRENSIE_LOG_MSG_GET_SCOPE__( Utility::ERROR_RECORD, msg )

/*! Log a nested error
 * \details This macro should be used to log nested errors (see the 
 * exception catch macros for an example). Unlike the other error logging
 * macros this macro will only print the message (usually from 
 * exception.what()).
 */
#define FRENSIE_LOG_NESTED_ERROR( msg )         \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::ERROR_RECORD, FRENSIE_LOG_NESTED_ERROR_TAG, msg )

/*! Log a tagged error with the logger
 * \details This macro will attempt to deduce the function scope.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_TAGGED_ERROR( tag, msg )    \
  __FRENSIE_LOG_MSG_WITH_TAG_GET_SCOPE__( Utility::ERROR_RECORD, tag, msg )

/*! Log an error in the scope
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_SCOPE_ERROR( scope, msg )   \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::ERROR_RECORD, scope, msg )

/*! Log a tagged error in the scope
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_TAGGED_SCOPE_ERROR( scope, tag, msg )       \
  __FRENSIE_LOG_SCOPE_MESSAGE_WITH_TAG__( Utility::ERROR_RECORD, scope, tag, msg )

/*! Log an error using the provided logger
 * \details This macro will attempt to deduce the function scope. This method 
 * should be used when a class or function already has a logger created.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ERROR_WITH_LOGGER( logger, msg )    \
  __FRENSIE_LOG_MSG_WITH_LOGGER_GET_SCOPE__( Utility::ERROR_RECORD, logger, msg )

/*! Log an error in the scope using the provided logger
 * \details This method should be used when a class or function already has
 * a logger created.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_SCOPE_ERROR_WITH_LOGGER( logger, scope, msg )       \
  __FRENSIE_LOG_SCOPE_MSG_WITH_LOGGER__( Utility::ERROR_RECORD, scope, logger, msg )

/*! Log a warning
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_WARNING( msg )                      \
  __FRENSIE_LOG_MSG_GET_SCOPE__( Utility::WARNING_RECORD, msg )

/*! Log a tagged warning
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_TAGGED_WARNING( tag, msg )  \
  __FRENSIE_LOG_MSG_WITH_TAG_GET_SCOPE__( Utility::WARNING_RECORD, tag, msg )

/*! Log a warning using the provided logger
 * \details This method should be used when a class or function already has
 * a logger created.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_WARNING_WITH_LOGGER( logger, msg ) \
  __FRENSIE_LOG_MSG_WITH_LOGGER__( Utility::WARNING_RECORD, logger, msg )

/*! Log a notification
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_NOTIFICATION( msg )                         \
  __FRENSIE_LOG_MSG__( Utility::NOTIFICATION_RECORD, msg )

/*! Log a partial notification
 * \details No newline characters will be added to the end of the log entry
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_PARTIAL_NOTIFICATION( msg ) \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::NOTIFICATION_RECORD, FRENSIE_LOG_PARTIAL_NOTIFICATION_TAG, msg )

/*! Log a tagged notification
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_TAGGED_NOTIFICATION( tag, msg )      \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::NOTIFICATION_RECORD, tag, msg )

/*! Log a notification using the provided logger
 * \details This method should be used when a class or function already has
 * a logger created.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_NOTIFICATION_WITH_LOGGER( logger, msg )     \
  __FRENSIE_LOG_MSG_WITH_LOGGER__( Utility::NOTIFICATION_RECORD, logger, msg )



#if HAVE_FRENSIE_DETAILED_LOGGING

/*! Log details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DETAILS( msg )                      \
  __FRENSIE_LOG_MSG__( Utility::DETAILS_RECORD, msg )

/*! Log tagged details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_TAGGED_DETAILS( tag, msg )  \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::DETAILS_RECORD, tag, msg )

/*! Log details using the provided logger
 * \details This method should be used when a class or function already has
 * a logger created.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DETAILS_WITH_LOGGER( logger, msg )  \
  __FRENSIE_LOG_MSG_WITH_LOGGER__( Utility::DETAILS_RECORD, logger, msg )

/*! Log pedantic details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_PEDANTIC_DETAILS( msg )             \
  __FRENSIE_LOG_MSG__( Utility::PEDANTIC_DETAILS_RECORD, msg )

/*! Log tagged pedantic details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( tag, msg )                  \
  __FRENSIE_LOG_MSG_WITH_TAG__( Utility::PEDANTIC_DETAILS_RECORD, tag, msg )

/*! Log pedantic details using the provided logger
 * \details This method should be used when a class or function already has
 * a logger created.
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_PEDANTIC_DETAILS_WITH_LOGGER( logger, msg )         \
  __FRENSIE_LOG_MSG_WITH_LOGGER__( Utility::PEDANTIC_DETAILS_RECORD, logger, msg )

#else // HAVE_FRENSIE_DETAILED_LOGGING

#define FRENSIE_LOG_DETAILS( msg )
#define FRENSIE_LOG_TAGGED_DETAILS( tag, msg )
#define FRENSIE_LOG_DETAILS_WITH_LOGGER( logger, msg )
#define FRENSIE_LOG_PEDANTIC_DETAILS( msg )
#define FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( tag, msg )
#define FRENSIE_LOG_PEDANTIC_DETAILS_WITH_LOGGER( logger, msg )

#endif // end HAVE_FRENSIE_DETAILED_LOGGING

#endif // end UTILITY_LOGGING_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_LoggingMacros.hpp
//---------------------------------------------------------------------------//
