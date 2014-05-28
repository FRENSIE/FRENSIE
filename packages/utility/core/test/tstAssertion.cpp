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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_Assertion.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Utility::Assertion looks different than a 
// std::runtime_error as it inherits from std::logic_error.
TEUCHOS_UNIT_TEST( Assertion, differentiation_test )
{
  try
  {
    throw Utility::Assertion( "Utility logic error" );
  }
  catch( const std::runtime_error& assertion )
  {
    TEST_ASSERT( 0 );
  }
  catch( ... )
  {
    TEST_ASSERT( 1 );
  }
}

//---------------------------------------------------------------------------//
// Check that a Utility::Assertion can be caught and the appropriate
// error message is written.
TEUCHOS_UNIT_TEST( Assertion, message_test )
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
    TEST_ASSERT( 0 );
  }

  const std::string true_message( "failed assertion" );
  TEST_ASSERT( 0 == message.compare( true_message ) );
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with TEUCHOS_TEST_FOR_EXCEPTION
TEUCHOS_UNIT_TEST( Assertion, teuchos_throw_test )
{
  try
  {
    TEUCHOS_TEST_FOR_EXCEPTION( true, 
				Utility::Assertion,
				"Utility assertion failed" << std::endl );
  }
  catch( const Utility::Assertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with the assert macro
TEUCHOS_UNIT_TEST( Assertion, assert_throw_test )
{
  try
  {
    ASSERT( false );
  }
  catch( const Utility::Assertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a Utility::CriticalAssertion looks different than a 
// std::logic_error as it inherits from std::runtime_error
TEUCHOS_UNIT_TEST( CriticalAssertion, differentiation_test )
{
  try
  {
    throw Utility::CriticalAssertion( "Utility runtime error" );
  }
  catch( const std::logic_error& assertion )
  {
    TEST_ASSERT( 0 );
  }
  catch( ... )
  {
    TEST_ASSERT( 1 );
  }
}

//---------------------------------------------------------------------------//
// Check that a Utility::CriticalAssertion can be caught and the appropriate
// error message is written.
TEUCHOS_UNIT_TEST( CriticalAssertion, message_test )
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
    TEST_ASSERT( 0 );
  }

  const std::string true_message( "failed assertion" );
  TEST_ASSERT( 0 == message.compare( true_message ) );
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with TEUCHOS_TEST_FOR_EXCEPTION
TEUCHOS_UNIT_TEST( CriticalAssertion, teuchos_throw_test )
{
  try
  {
    TEUCHOS_TEST_FOR_EXCEPTION( true, 
				Utility::CriticalAssertion,
				"Utility assertion failed" << std::endl );
  }
  catch( const Utility::CriticalAssertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::Assertion with the assert macro
TEUCHOS_UNIT_TEST( CriticalAssertion, assert_throw_test )
{
  try
  {
    ASSERT_ALWAYS( false );
  }
  catch( const Utility::CriticalAssertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// end tstAssertion.cpp
//---------------------------------------------------------------------------//
