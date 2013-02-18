//---------------------------------------------------------------------------//
// \file   tstContractException.cpp
// \author Alex Robinson
// \brief  Contract Exception class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "FACEMC_config.hpp"
#include "ContractException.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a FACEMC::ContractException looks different than a 
// std::runtime_error as it inherits from std::logic_error.
TEUCHOS_UNIT_TEST( ContractException, differentiation_test )
{
  try
  {
    throw FACEMC::ContractException( "FACEMC logic error" );
  }
  catch( const std::runtime_error& exception )
  {
    TEST_ASSERT( 0 );
  }
  catch( ... )
  {
    TEST_ASSERT( 1 );
  }
}

//---------------------------------------------------------------------------//
// Check that a FACEMC::ContractException can be caught and the appropriate
// error message is written
TEUCHOS_UNIT_TEST( ContractException, message_test )
{
  std::string message;

  try
  {
    throw FACEMC::ContractException( "contract broken" );
  }
  catch( const FACEMC::ContractException& exception )
  {
    mesage = std::string( exception.what() );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }

  const std::string true_message( "contract broken" );
  TEST_ASSERT( 0 == message.compare( true_message ) );
}

//---------------------------------------------------------------------------//
// Check that we can throw a FACEMC::ContractException with 
// TEUCHOS_TEST_FOR_EXCEPTION
TEUCHOS_UNIT_TEST( ContractException, teuchos_throw_test )
{
  try
  {
    TEUCHOS_TEST_FOR_EXCEPTION( true,
				FACEMC::ContractException,
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
// Test the precondition check for DBC
TEUCHOS_UNIT_TEST( ContractException, precondition_test )
{

  try
  {
    testPrecondition( 0 );
    throw std::runtime_error( "this shouldn't be thrown" );
  }
  catch( const FACEMC::ContractException& exception )
  {
#if HAVE_FACEMC_DBC
    std::string message( exception.what() );
    std::string partial_message( "Precondition exception" );
    std::string::size_type idx = message.find( partial_message );
    if( idx == std::string::npos )
    {
      TEST_ASSERT( 0 );
    }
#else
    TEST_ASSERT( 0 );
#endif
  }
  catch( ... )
  {
#if HAVE_FACEMC_DBC
    TEST_ASSERT( 0 );
#endif
  }
}

//---------------------------------------------------------------------------//
// Test the postcondition check for DBC.
TEUCHOS_UNIT_TEST( ContractException, postcondition_test )
{

  try
  {
    testPostcondition( 0 );
    throw std::runtime_error( "this shouldn't be thrown" );
  }
  catch( const FACEMC::ContractException& exception )
  {
#if HAVE_FACEMC_DBC
    std::string message( exception.what() );
    std::string partial_message( "Postcondition exception" );
    std::string::size_type idx = message.find( partial_message );
    if( idx == std::string::npos )
    {
      TEST_ASSERT( 0 );
    }
#else
    TEST_ASSERT( 0 );
#endif
  }
  catch( ... )
  {
#if HAVE_FACEMC_DBC
    TEST_ASSERT( 0 );
#endif
  }
}

//---------------------------------------------------------------------------//
// Test the invariant check for DBC.
TEUCHOS_UNIT_TEST( ContractException, invariant_test )
{

  try
  {
    testInvariant( 0 );
    throw std::runtime_error( "this shouldn't be thrown" );
  }
  catch( const FACEMC::ContractException& exception )
  {
#if HAVE_FACEMC_DBC
    std::string message( exception.what() );
    std::string partial_message( "Invariant exception" );
    std::string::size_type idx = message.find( partial_message );
    if( idx == std::string::npos )
    {
      TEST_ASSERT( 0 );
    }
#else
    TEST_ASSERT( 0 );
#endif
  }
  catch( ... )
  {
#if HAVE_FACEMC_DBC
    TEST_ASSERT( 0 );
#endif
  }
}

//---------------------------------------------------------------------------//
// Test that we can remember a value and check it with DBC
TEUCHOS_UNIT_TEST( ContractException, remember_test )
{
  remember( int test_value_1 = 0 );
  remember( int test_value_2 = 1 );

  try
  {
    testInvariant( test_value_1 );
  }
  catch( const FACEMC::ContractException& exception )
  {
#if HAVE_FACEMC_DBC
    TEST_ASSERT( 1 );
#else
    TEST_ASSERT( 0 );
#endif
  }
  catch( ... )
  {
#if HAVE_FACEMC_DBC
    TEST_ASSERT( 0 );
#endif
  }

  try
  {
    testInvariant( test_value_2 );
    TEST_ASSERT( 1 );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }
}
