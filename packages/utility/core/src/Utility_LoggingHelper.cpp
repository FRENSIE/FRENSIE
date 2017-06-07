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
                                     const boost::shared_ptr<std::ostream>& os,
                                     const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardLogSinks( os_array, asynchronous );
}

// Add standard log sinks using the requested console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardLogSinks( std::ostream& console_os,
                                         const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardLogSinks( os_array, asynchronous );
}

// Add a standard error log sink using the requested output stream
void LoggingHelper::addStandardErrorLogSink(
                                    const boost::shared_ptr<std::ostream>& os,
                                    const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardErrorLogSink( os_array, asynchronous );
}

// Add a standard error log sink using the console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardErrorLogSink( std::ostream& console_os,
                                             const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardErrorLogSink( os_array, asynchronous );
}
  
// Add a standard warning log sink using the requested output stream
void LoggingHelper::addStandardWarningLogSink(
                                    const boost::shared_ptr<std::ostream>& os,
                                    const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardWarningLogSink( os_array, asynchronous );
}

// Add a standard warning log sink using the requested console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardWarningLogSink( std::ostream& console_os,
                                               const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardWarningLogSink( os_array, asynchronous );
}
  
// Add a standard notification log sink using the requested output stream
void LoggingHelper::addStandardNotificationLogSink(
                                    const boost::shared_ptr<std::ostream>& os,
                                    const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = os;

  LoggingHelper::addStandardNotificationLogSink( os_array, asynchronous );
}

// Add a standard notification log sink using the requested console stream
/*! \details Only use std::cout, std::cerr or std::clog (unless you
 * know what you are doing!).
 */
void LoggingHelper::addStandardNotificationLogSink( std::ostream& console_os,
                                                    const bool asynchronous )
{
  std::vector<boost::shared_ptr<std::ostream> > os_array( 1 );
  os_array[0] = boost::shared_ptr<std::ostream>( &console_os, boost::null_deleter() );

  LoggingHelper::addStandardNotificationLogSink( os_array, asynchronous );
}

// Remove all log sinks
void LoggingHelper::removeAllLogSinks()
{
  boost::log::core::get()->remove_all_sinks();
}

// Flush all sinks
void LoggingHelper::flushAllLogSinks()
{
  boost::log::core::get()->flush();
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LoggingHelper.cpp
//---------------------------------------------------------------------------//
