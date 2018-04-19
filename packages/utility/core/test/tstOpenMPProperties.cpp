//---------------------------------------------------------------------------//
//!
//! \file   tstOpenMPProperties.cpp
//! \author Alex Robinson
//! \brief  OpenMP session unit tests
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <thread>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ToStringTraits.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if OpenMP is used
BOOST_AUTO_TEST_CASE( isOpenMPUsed )
{
#ifdef HAVE_FRENSIE_OPENMP
  BOOST_CHECK( Utility::OpenMPProperties::isOpenMPUsed() );
#else
  BOOST_CHECK( !Utility::OpenMPProperties::isOpenMPUsed() );
#endif
}

//---------------------------------------------------------------------------//
// Check that the number of threads that will be used in OMP blocks can be set
BOOST_AUTO_TEST_CASE( setNumberOfThreads )
{
  Utility::OpenMPProperties::setNumberOfThreads( 2 );

#ifdef HAVE_FRENSIE_OPENMP
  BOOST_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 2 );
#else
  BOOST_CHECK_EQUAL( Utility::OpenMPProperties::getRequestedNumberOfThreads(), 1 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that the number of threads in the current parallel scope can be
// returned
BOOST_AUTO_TEST_CASE( getNumberOfThreads )
{
  // Outside of parallel block, this should always return 1;
  BOOST_CHECK_EQUAL( Utility::OpenMPProperties::getNumberOfThreads(), 1 );
  
  #pragma omp parallel num_threads( 4 )
  {
    if( Utility::OpenMPProperties::getThreadId() == 0 )
    {
#ifdef HAVE_FRENSIE_OPENMP
      BOOST_CHECK_EQUAL( Utility::OpenMPProperties::getNumberOfThreads(), 4 );
#else
      BOOST_CHECK_EQUAL( Utility::OpenMPProperties::getNumberOfThreads(), 1 );
#endif
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a timer can be created that is safe for use with OpenMP
BOOST_AUTO_TEST_CASE( createTimer )
{
  std::shared_ptr<Utility::Timer> timer =
    Utility::OpenMPProperties::createTimer();

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
// end tstOpenMPProperties.cpp
//---------------------------------------------------------------------------//
