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
#include <boost/log/expressions/formatters/named_scope.hpp>

// FRENSIE Includes
#include "FRENSIE_config.hpp"
#include "Utility_LogRecordType.hpp"

namespace Utility{

//! Add global attributes
void addGlobalAttributes();

//! Add standard log sinks using the requested output stream
void addStandardLogSinks( const boost::shared_ptr<std::ostream>& os );

//! Add an error log sink using the requestd output stream
void addErrorLogSink( const boost::shared_ptr<std::ostream>& os );

//! Add a warning log sink using the requested output stream
void addWarningLogSink( const boost::shared_ptr<std::ostream>& os );

//! Add a notification log sink using the requested output stream
void addNotificationLogSink( const boost::shared_ptr<std::ostream>& os );

//! Add a details log sink using the requested output stream
void addDetailsLogSink( const boost::shared_ptr<std::ostream>& os );

//! Add a pedantic details log sink using the requested output stream
void addPedanticDetailsLogSink( const boost::shared_ptr<std::ostream>& os );
  
} // end Utility namespace

//! \brief Add the standard global attributes to the log
#define FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES()    \
  Utility::addGlobalAttributes()

/*! \brief Create a log using the requested ostream object (wrapped in a 
 * boost::shared_ptr).
 */
#define FRENSIE_SETUP_STANDARD_LOGS( boost_os_ptr )       \
  Utility::addStandardLogSinks( boost_os_ptr )

/*! Create a log using the requested console object
 * 
 * Only use std::cout, std::cerr and std::clog objects.
 */
#define FRENSIE_SETUP_STANDARD_LOGS_WITH_CONSOLE( os )                  \
  Utility::addGlobalAttributes();                                       \
  boost::shared_ptr<std::ostream> os_ptr( &os, boost::null_deleter() ); \
  Utility::addStandardLogSinks( os_ptr )

/*! \brief Create an error log using the requested ostream object (wrapped in a
 * boost::shared_ptr).
 */
#define FRENSIE_SETUP_ERROR_LOG( boost_os_ptr ) \
  Utility::addErrorLogSink( boost_os_ptr )

/*! \brief Crate an error log using the requested console object
 *
 * Only use std::cout, std::cerr and std::clog objects.
 */
#define FRENSIE_SETUP_ERROR_LOG_WITH_CONSOLE( os )      \
  boost::shared_ptr<std::ostream> os##_ptr( &std::os, boost::null_deleter() );\
  Utility::addErrorLogSink( os##_ptr )

/*! \brief Add a global logging filter.
 *
 * This can be used to ignore any records that don't satisfy the expression.
 */
#define FRENSIE_SET_GLOBAL_LOG_FILTER( filter_expr )    \
  boost::log::core::get()->add_filter( filter_expr )

//! Never call this macro directly
#define __FRENSIE_LOG_MSG__( type, msg )                         \
  BOOST_LOG_FUNCTION();                                                 \
  boost::log::sources::severity_logger<Utility::LogRecordType> slg;      \
  BOOST_LOG_SEV( slg, type ) << msg

//! Never call this macro directly
#define __FRENSIE_LOG_SCOPE_MSG__( type, scope, msg )    \
  BOOST_LOG_NAMED_SCOPE( scope );                               \
  boost::log::sources::severity_logger<Utility::LogRecordType> slg;      \
  BOOST_LOG_SEV( slg, type ) << msg

/*! Log an error
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_ERROR( msg )            \
  __FRENSIE_LOG_MSG__( Utility::ERROR_RECORD, msg )

//! Log an error in the scope
#define FRENSIE_LOG_SCOPE_ERROR( scope, msg )   \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::ERROR_RECORD, scope, msg )

/*! Log a warning
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_WARNING( msg )              \
  __FRENSIE_LOG_MSG__( Utility::WARNING_RECORD, msg )

//! Log a warning in the scope
#define FRENSIE_LOG_SCOPE_WARNING( scope, msg )   \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::WARNING_RECORD, scope, msg )

/*! Log a notification
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_NOTIFICATION( msg )         \
  __FRENSIE_LOG_MSG__( Utility::NOTIFICATION_RECORD, msg )

//! Log a notification in the scope
#define FRENSIE_LOG_SCOPE_NOTIFICATION( scope, msg )    \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::NOTIFICATION_RECORD, scope, msg )

#if HAVE_FRENSIE_DETAILED_LOGGING

/*! Log details
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_DETAILS( msg )              \
  __FRENSIE_LOG_DETAILS__( Utility::DETAILS_RECORD, msg )

//! Log details in the scope
#define FRENSIE_LOG_SCOPE_DETAILS( scope, msg ) \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::DETAILS_RECORD, scope, msg )

/*! Log pedantic details
 * \details This macro will attempt to deduce the function scope.
 */
#define FRENSIE_LOG_PEDANTIC_DETAILS( msg )             \
  __FRENSIE_LOG_MSG__( Utility::PEDANTIC_DETAILS_RECORD, msg )

//! Log pedantic details in the scope
#define FRENSIE_LOG_SCOPE_PEDANTIC_DETAILS( msg )               \
  __FRENSIE_LOG_SCOPE_MSG__( Utility::PEDANTIC_DETAILS_RECORD, msg )

#else // HAVE_FRENSIE_DETAILED_LOGGING

#define FRENSIE_LOG_DETAILS( msg )
#define FRENSIE_LOG_SCOPE_DETAILS( scope, msg )
#define FRENSIE_LOG_PEDANTIC_DETAILS( msg )
#define FRENSIE_LOG_SCOPE_PEDANTIC_DETAILS( scope, msg )

#endif // end HAVE_FRENSIE_DETAILED_LOGGING

#endif // end UTILITY_LOGGING_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_LoggingMacros.hpp
//---------------------------------------------------------------------------//
