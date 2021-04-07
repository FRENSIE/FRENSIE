//---------------------------------------------------------------------------//
//!
//! \file   tstStandardTimer.cpp
//! \author Alex Robinson
//! \brief  Standard timer unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <chrono>
#include <thread>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

// FRENSIE Includes
#include "Utility_StandardTimer.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<std::chrono::system_clock,std::chrono::steady_clock> ClockTypes;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a timer can be constructed
BOOST_AUTO_TEST_CASE_TEMPLATE( constructor, Clock, ClockTypes )
{
  Utility::StandardTimer<Clock> timer;

  BOOST_CHECK( timer.isStopped() );
  BOOST_CHECK_EQUAL( timer.elapsed().count(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a timer can be started, stopped and resumed
BOOST_AUTO_TEST_CASE_TEMPLATE( start_stop_resume, Clock, ClockTypes )
{
  std::unique_ptr<Utility::Timer> timer( new Utility::StandardTimer<Clock> );

  // Start the timer
  timer->start();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  BOOST_CHECK( timer->elapsed().count() >= 0.05 );

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  // Stop the timer
  timer->stop();

  double elapsed_time = timer->elapsed().count();

  BOOST_CHECK( elapsed_time >= 0.1 );

  // Once the timer has stopped the elapsed time should not change
  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  BOOST_CHECK_EQUAL( timer->elapsed().count(), elapsed_time );

  // Resume the timer
  timer->resume();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  timer->stop();

  BOOST_CHECK( timer->elapsed().count() >= 0.15 );

  // Restart the timer
  timer->start();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  timer->stop();

  BOOST_CHECK( timer->elapsed().count() >= 0.05 &&
               timer->elapsed().count() < 0.15 );
}

//---------------------------------------------------------------------------//
// Check that a default timer can be constructed
BOOST_AUTO_TEST_CASE( default_timer )
{
  std::shared_ptr<Utility::Timer> timer = Utility::createDefaultTimer();

  // Start the timer
  timer->start();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  BOOST_CHECK( timer->elapsed().count() >= 0.05 );

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  // Stop the timer
  timer->stop();

  double elapsed_time = timer->elapsed().count();

  BOOST_CHECK( elapsed_time >= 0.1 );

  // Once the timer has stopped the elapsed time should not change
  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  BOOST_CHECK_EQUAL( timer->elapsed().count(), elapsed_time );

  // Resume the timer
  timer->resume();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  timer->stop();

  BOOST_CHECK( timer->elapsed().count() >= 0.15 );

  // Restart the timer
  timer->start();

  std::this_thread::sleep_for( std::chrono::milliseconds(50) );

  timer->stop();

  BOOST_CHECK( timer->elapsed().count() >= 0.05 &&
               timer->elapsed().count() < 0.15 );
}

//---------------------------------------------------------------------------//
// end tstStandardTimer.cpp
//---------------------------------------------------------------------------//
