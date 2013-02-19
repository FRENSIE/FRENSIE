//---------------------------------------------------------------------------//
// \file   tstAssertion.cpp
// \author Alex Robinson
// \brief  Assertion class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "FACEMC_Assertion.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a FACEMC::Assertion looks different than a 
// std::runtime_error as it inherits from std::logic_error.
TEUCHOS_UNIT_TEST( Assertion, differentiation_test )
{
  try
  {
    throw FACEMC::Assertion( "FACEMC logic error" );
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
// Check that a FACEMC::Assertion can be caught and the appropriate
// error message is written.
TEUCHOS_UNIT_TEST( Assertion, message_test )
{
  std::string message;

  try
  {
    throw FACEMC::Assertion( "failed assertion" );
  }
  catch( const FACEMC::Assertion& assertion )
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
// Check that we can throw a FACEMC::Assertion with TEUCHOS_TEST_FOR_EXCEPTION
TEUCHOS_UNIT_TEST( Assertion, teuchos_throw_test )
{
  try
  {
    TEUCHOS_TEST_FOR_EXCEPTION( true, 
				FACEMC::Assertion,
				"FACEMC assertion failed" << std::endl );
  }
  catch( const FACEMC::Assertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that we can throw a FACEMC::Assertion with the assert macro
TEUCHOS_UNIT_TEST( Assertion, assert_throw_test )
{
  try
  {
    FACEMC_ASSERT( false );
  }
  catch( const FACEMC::Assertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a FACEMC::CriticalAssertion looks different than a 
// std::logic_error as it inherits from std::runtime_error
TEUCHOS_UNIT_TEST( CriticalAssertion, differentiation_test )
{
  try
  {
    throw FACEMC::CriticalAssertion( "FACEMC runtime error" );
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
// Check that a FACEMC::CriticalAssertion can be caught and the appropriate
// error message is written.
TEUCHOS_UNIT_TEST( CriticalAssertion, message_test )
{
  std::string message;

  try
  {
    throw FACEMC::CriticalAssertion( "failed assertion" );
  }
  catch( const FACEMC::CriticalAssertion& assertion )
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
// Check that we can throw a FACEMC::Assertion with TEUCHOS_TEST_FOR_EXCEPTION
TEUCHOS_UNIT_TEST( CriticalAssertion, teuchos_throw_test )
{
  try
  {
    TEUCHOS_TEST_FOR_EXCEPTION( true, 
				FACEMC::CriticalAssertion,
				"FACEMC assertion failed" << std::endl );
  }
  catch( const FACEMC::CriticalAssertion& assertion )
  {
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that we can throw a FACEMC::Assertion with the assert macro
TEUCHOS_UNIT_TEST( CriticalAssertion, assert_throw_test )
{
  try
  {
    FACEMC_ASSERT_ALWAYS( false );
  }
  catch( const FACEMC::CriticalAssertion& assertion )
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
