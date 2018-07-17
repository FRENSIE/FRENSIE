//---------------------------------------------------------------------------//
//!
//! \file   tstGlobalMPISession.cpp
//! \author Alex Robinson
//! \brief  Global MPI session unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <thread>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/core/null_deleter.hpp>

// FRENSIE Includes
#include "Utility_GlobalMPISession.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Template Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<bool,int,double> Types;

//---------------------------------------------------------------------------//
// Test Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Utility::GlobalMPISession> mpi_session;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
struct InitFixture
{
  InitFixture()
  {
    FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES();

    if( !mpi_session.get() )
    {
      mpi_session.reset( new Utility::GlobalMPISession(
                     boost::unit_test::framework::master_test_suite().argc,
                     boost::unit_test::framework::master_test_suite().argv ) );
    }
  }
};

// Register the InitFixture with the test suite
BOOST_TEST_GLOBAL_FIXTURE( InitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if MPI is used
BOOST_AUTO_TEST_CASE( isMPIUsed )
{
#ifdef HAVE_FRENSIE_MPI
  BOOST_CHECK( mpi_session->isMPIUsed() );
  BOOST_CHECK( Utility::GlobalMPISession::isMPIUsed() );
#else
  BOOST_CHECK( !mpi_session->isMPIUsed() );
  BOOST_CHECK( !Utility::GlobalMPISession::isMPIUsed() );
#endif
}

//---------------------------------------------------------------------------//
// Check that an output stream can be initialized
BOOST_AUTO_TEST_CASE( initializeOutputStream )
{
  // Allow all procs to output to the stream
  boost::shared_ptr<std::ostream> oss( new std::ostringstream );

  mpi_session->initializeOutputStream( oss );

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();

  BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(), std::string("Hello from ") + Utility::toString( Utility::GlobalMPISession::rank() ) );

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();

  // Block all procs from outputting to the stream except for the root
  mpi_session->initializeOutputStream( oss, 0, true );

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(),
                       "Hello from 0" );
  }
  else
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().empty() );
  }

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();

  // Restore the stream on all procs
  mpi_session->restoreOutputStream( oss );

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();

  BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(), std::string("Hello from ") + Utility::toString( Utility::GlobalMPISession::rank() ) );

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();

  // Block all procs from outputting to the stream except for the root
  Utility::GlobalMPISession::initializeOutputStream( oss, 0, true );

  {
    boost::shared_ptr<std::ostream> cout_ptr( &std::cout, boost::null_deleter() );
    Utility::GlobalMPISession::initializeOutputStream( cout_ptr, 0, true );
  }

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();
  std::cout << "Hello from " << Utility::GlobalMPISession::rank() << std::endl;

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(),
                       "Hello from 0" );
  }
  else
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().empty() );
  }

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();

  mpi_session->barrier();
  
  // Restore all streams on all procs
  Utility::GlobalMPISession::restoreOutputStreams();

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();
  std::cout << "Hello from " << Utility::GlobalMPISession::rank() << std::endl;
  
  BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(), std::string("Hello from ") + Utility::toString( Utility::GlobalMPISession::rank() ) );
}

//---------------------------------------------------------------------------//
// Check that the error log can be initialized
BOOST_AUTO_TEST_CASE( initializeErrorLog )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the default error log
  boost::shared_ptr<std::ostringstream> oss( new std::ostringstream );

  mpi_session->initializeErrorLog( oss );

  // Log an error
  FRENSIE_LOG_ERROR( "testing on proc " << Utility::GlobalMPISession::rank() );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().find( std::string("testing on proc ") + Utility::toString( Utility::GlobalMPISession::rank() ) ) < dynamic_cast<std::ostringstream*>(oss.get())->str().size() );

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();
  
  // Remove the logs
  FRENSIE_REMOVE_ALL_LOGS();
  
  // Setup error logging on the root process only
  mpi_session->initializeErrorLog( oss, 0, true );

  // Log an error
  FRENSIE_LOG_ERROR( "testing on proc " << Utility::GlobalMPISession::rank() );
  FRENSIE_FLUSH_ALL_LOGS();

  mpi_session->barrier();

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().find( std::string("testing on proc 0") ) < dynamic_cast<std::ostringstream*>(oss.get())->str().size() );
  }
  else
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().empty() );
  }

  mpi_session->restoreOutputStreams();

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();
}

//---------------------------------------------------------------------------//
// Check that the warning log can be initialized
BOOST_AUTO_TEST_CASE( initializeWarningLog )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the default warning log
  boost::shared_ptr<std::ostringstream> oss( new std::ostringstream );

  mpi_session->initializeWarningLog( oss );

  // Log a warning
  FRENSIE_LOG_WARNING( "testing on proc " << Utility::GlobalMPISession::rank() );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().find( std::string("testing on proc ") + Utility::toString( Utility::GlobalMPISession::rank() ) ) < dynamic_cast<std::ostringstream*>(oss.get())->str().size() );

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();
  
  // Remove the logs
  FRENSIE_REMOVE_ALL_LOGS();
  
  // Setup warning logging on the root process only
  mpi_session->initializeWarningLog( oss, 0, true );

  // Log a warning
  FRENSIE_LOG_WARNING( "testing on proc " << Utility::GlobalMPISession::rank() );
  FRENSIE_FLUSH_ALL_LOGS();

  mpi_session->barrier();

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().find( std::string("testing on proc 0") ) < dynamic_cast<std::ostringstream*>(oss.get())->str().size() );
  }
  else
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().empty() );
  }

  mpi_session->restoreOutputStreams();

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();
}

//---------------------------------------------------------------------------//
// Check that the notification log can be initialized
BOOST_AUTO_TEST_CASE( initializeNotificationLog )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the default notification log
  boost::shared_ptr<std::ostringstream> oss( new std::ostringstream );

  mpi_session->initializeNotificationLog( oss );

  // Log a notification
  FRENSIE_LOG_NOTIFICATION( "testing on proc " << Utility::GlobalMPISession::rank() );
  FRENSIE_FLUSH_ALL_LOGS();

  BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().find( std::string("testing on proc ") + Utility::toString( Utility::GlobalMPISession::rank() ) ) < dynamic_cast<std::ostringstream*>(oss.get())->str().size() );

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();
  
  // Remove the logs
  FRENSIE_REMOVE_ALL_LOGS();
  
  // Setup notification logging on the root process only
  mpi_session->initializeNotificationLog( oss, 0, true );

  // Log a notification
  FRENSIE_LOG_NOTIFICATION( "testing on proc " << Utility::GlobalMPISession::rank() );
  FRENSIE_FLUSH_ALL_LOGS();

  mpi_session->barrier();

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().find( std::string("testing on proc 0") ) < dynamic_cast<std::ostringstream*>(oss.get())->str().size() );
  }
  else
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().empty() );
  }

  mpi_session->restoreOutputStreams();

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();
}

//---------------------------------------------------------------------------//
// Check that a timer can be created that is safe to use within the mpi session
BOOST_AUTO_TEST_CASE( createTimer )
{
  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  mpi_session->barrier();
  
  // Start the timer
  timer->start();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  BOOST_CHECK( timer->elapsed().count() >= 0.05 );

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  // Stop the timer
  timer->stop();
  mpi_session->barrier();

  double elapsed_time = timer->elapsed().count();

  BOOST_CHECK( elapsed_time >= 0.1 );

  // Once the timer has stopped the elapsed time should not change
  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  BOOST_CHECK_EQUAL( timer->elapsed().count(), elapsed_time );

  // Resume the timer
  mpi_session->barrier();
  timer->resume();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  timer->stop();
  mpi_session->barrier();

  BOOST_CHECK( timer->elapsed().count() >= 0.15 );

  // Restart the timer
  mpi_session->barrier();
  timer->start();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  timer->stop();
  mpi_session->barrier();

  BOOST_CHECK( timer->elapsed().count() >= 0.05 &&
               timer->elapsed().count() < 0.15 );
}

//---------------------------------------------------------------------------//
// Check that a set of integers can be summed on all processes
BOOST_AUTO_TEST_CASE( sum_int )
{
  int local_int = 1;

  int global_int_sum = Utility::GlobalMPISession::sum( local_int );

  BOOST_CHECK_EQUAL( global_int_sum, Utility::GlobalMPISession::size() );
}

//---------------------------------------------------------------------------//
// Check that a set of doubles can be summed on all processes
BOOST_AUTO_TEST_CASE( sum_double )
{
  double local_double = 0.5;

  double global_double_sum = Utility::GlobalMPISession::sum( local_double );

  BOOST_CHECK_EQUAL( global_double_sum, Utility::GlobalMPISession::size()*0.5 );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be checked as true on all procs
BOOST_AUTO_TEST_CASE( isGloballyTrue )
{
  bool local_bool = true;

  BOOST_CHECK( Utility::GlobalMPISession::isGloballyTrue( local_bool ) );

  if( Utility::GlobalMPISession::rank() == 0 )
    local_bool = false;

  BOOST_CHECK( !Utility::GlobalMPISession::isGloballyTrue( local_bool ) );

  local_bool = false;

  BOOST_CHECK( !Utility::GlobalMPISession::isGloballyTrue( local_bool ) );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be checked as false on all procs
BOOST_AUTO_TEST_CASE( isGloballyFalse )
{
  bool local_bool = false;

  BOOST_CHECK( Utility::GlobalMPISession::isGloballyFalse( local_bool ) );

  if( Utility::GlobalMPISession::rank() == 0 )
    local_bool = true;

  BOOST_CHECK( !Utility::GlobalMPISession::isGloballyFalse( local_bool ) );

  local_bool = true;

  BOOST_CHECK( !Utility::GlobalMPISession::isGloballyFalse( local_bool ) );
}

//---------------------------------------------------------------------------//
// Check that messages can be gathered on a specific process
BOOST_AUTO_TEST_CASE( gatherMessages )
{
  std::ostringstream oss;
  oss << Utility::GlobalMPISession::rank() << "/"
      << Utility::GlobalMPISession::size();

  std::vector<std::string> messages =
    Utility::GlobalMPISession::gatherMessages( 0, oss.str() );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK_EQUAL( messages.size(), Utility::GlobalMPISession::size() );

    for( int i = 0; i < Utility::GlobalMPISession::size(); ++i )
    {
      std::ostringstream local_oss;
      local_oss << i << "/" << Utility::GlobalMPISession::size();
      
      BOOST_CHECK_EQUAL( messages[i], local_oss.str() );
    }
  }
  else
  {
    BOOST_CHECK( messages.empty() );
  }

  if( Utility::GlobalMPISession::size() > 1 )
  {
    messages = Utility::GlobalMPISession::gatherMessages( 1, oss.str() );

    if( Utility::GlobalMPISession::rank() == 1 )
    {
      BOOST_CHECK_EQUAL( messages.size(), Utility::GlobalMPISession::size() );

      for( int i = 0; i < Utility::GlobalMPISession::size(); ++i )
      {
        std::ostringstream local_oss;
        local_oss << i << "/" << Utility::GlobalMPISession::size();
        
        BOOST_CHECK_EQUAL( messages[i], local_oss.str() );
      }
    }
    else
    {
      BOOST_CHECK( messages.empty() );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that bools can be gathered on a specific process
BOOST_AUTO_TEST_CASE_TEMPLATE( gatherData, T, Types )
{
  T local_data;

  if( Utility::GlobalMPISession::rank()%2 == 0 )
    local_data = T(1);
  else
    local_data = T(0);

  std::vector<T> data = Utility::GlobalMPISession::gatherData( 0, local_data );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK_EQUAL( data.size(), Utility::GlobalMPISession::size() );

    for( int i = 0; i < Utility::GlobalMPISession::size(); ++i )
    {
      if( i%2 == 0 )
        BOOST_CHECK_EQUAL( data[i], T(1) );
      else
        BOOST_CHECK_EQUAL( data[i], T(0) );
    }
  }
  else
  {
    BOOST_CHECK( data.empty() );
  }

  if( Utility::GlobalMPISession::size() > 1 )
  {
    data = Utility::GlobalMPISession::gatherData( 1, local_data );

    if( Utility::GlobalMPISession::rank() == 1 )
    {
      BOOST_CHECK_EQUAL( data.size(), Utility::GlobalMPISession::size() );

      for( int i = 0; i < Utility::GlobalMPISession::size(); ++i )
      {
        if( i%2 == 0 )
          BOOST_CHECK_EQUAL( data[i], T(1) );
        else
          BOOST_CHECK_EQUAL( data[i], T(0) );
      }
    }
    else
    {
      BOOST_CHECK( data.empty() );
    }
  }
}

//---------------------------------------------------------------------------//
// end tstGlobalMPISession.cpp
//---------------------------------------------------------------------------//
