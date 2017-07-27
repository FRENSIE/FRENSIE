//---------------------------------------------------------------------------//
//!
//! \file   tstAssertion.cpp
//! \author Alex Robinson
//! \brief  Assertion class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdexcept>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_Assertion.hpp"
#include "Utility_ExceptionTestMacros.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Assertion )

//---------------------------------------------------------------------------//
// Check that a Utility::Assertion looks different than a
// std::runtime_error as it inherits from std::logic_error.
BOOST_AUTO_TEST_CASE( differentiation_test )
{
  try
  {
    throw Utility::Assertion( "Utility logic error" );
  }
  catch( const std::runtime_error& assertion )
  {
    BOOST_CHECK( 0 );
  }
  catch( ... )
  {
    BOOST_CHECK( 1 );
  }
}

//---------------------------------------------------------------------------//
// Check that a Utility::Assertion can be caught and the appropriate
// error message is written.
BOOST_AUTO_TEST_CASE( message_test )
{
  std::string message;

  try
  {
    throw Utility::Assertion( "failed assertion" );
  }
  catch( const Utility::Assertion& assertion )
  {
    message = std::string( assertion.what() );
  }
  catch( ... )
  {
    BOOST_CHECK( 0 );
  }

  const std::string true_message( "failed assertion" );
  BOOST_CHECK( 0 == message.compare( true_message ) );
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with TEST_FOR_EXCEPTION
BOOST_AUTO_TEST_CASE( throw_test )
{
  try
  {
    TEST_FOR_EXCEPTION( true,
                        Utility::Assertion,
                        "Utility assertion failed" << std::endl );
  }
  catch( const Utility::Assertion& assertion )
  {
    BOOST_CHECK( 1 );
  }
  catch( ... )
  {
    BOOST_CHECK( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with the assert macro
BOOST_AUTO_TEST_CASE( assert_throw_test )
{
  try
  {
    ASSERT( false );
  }
  catch( const Utility::Assertion& assertion )
  {
    BOOST_CHECK( 1 );
  }
  catch( ... )
  {
    BOOST_CHECK( 0 );
  }
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE( CriticalAssertion )

//---------------------------------------------------------------------------//
// Check that a Utility::CriticalAssertion looks different than a
// std::logic_error as it inherits from std::runtime_error
BOOST_AUTO_TEST_CASE( differentiation_test )
{
  try
  {
    throw Utility::CriticalAssertion( "Utility runtime error" );
  }
  catch( const std::logic_error& assertion )
  {
    BOOST_CHECK( 0 );
  }
  catch( ... )
  {
    BOOST_CHECK( 1 );
  }
}

//---------------------------------------------------------------------------//
// Check that a Utility::CriticalAssertion can be caught and the appropriate
// error message is written.
BOOST_AUTO_TEST_CASE( message_test )
{
  std::string message;

  try
  {
    throw Utility::CriticalAssertion( "failed assertion" );
  }
  catch( const Utility::CriticalAssertion& assertion )
  {
    message = std::string( assertion.what() );
  }
  catch( ... )
  {
    BOOST_CHECK( 0 );
  }

  const std::string true_message( "failed assertion" );
  BOOST_CHECK( 0 == message.compare( true_message ) );
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with TEST_FOR_EXCEPTION
BOOST_AUTO_TEST_CASE( throw_test )
{
  try
  {
    TEST_FOR_EXCEPTION( true,
                        Utility::CriticalAssertion,
                        "Utility assertion failed" << std::endl );
  }
  catch( const Utility::CriticalAssertion& assertion )
  {
    BOOST_CHECK( 1 );
  }
  catch( ... )
  {
    BOOST_CHECK( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with the assert macro
BOOST_AUTO_TEST_CASE( assert_throw_test )
{
  try
  {
    ASSERT_ALWAYS( false );
  }
  catch( const Utility::CriticalAssertion& assertion )
  {
    BOOST_CHECK( 1 );
  }
  catch( ... )
  {
    BOOST_CHECK( 0 );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstAssertion.cpp
//---------------------------------------------------------------------------//
