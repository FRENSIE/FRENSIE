//---------------------------------------------------------------------------//
//!
//! \file   tstContractException.cpp
//! \author Alex Robinson
//! \brief  Contract Exception class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "FRENSIE_config.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
void dummyPreconditionPassTestFunction()
{
  testPrecondition( true );
}

void dummyPreconditionFailTestFunction()
{
  testPrecondition( false );
}

double dummyPostconditionPassTestFunction( const double )
{
  testPostcondition( true );

  return 1.0;
}

double dummyPostconditionFailTestFunction( const double )
{
  testPostcondition( false );

  return 1.0;
}

double dummyInvariantPassTestFunction( const double, const double )
{
  testInvariant( true );

  return 1.0;
}

double dummyInvariantFailTestFunction( const double, const double )
{
  testInvariant( false );

  return 1.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Utility::ContractException looks different than a
// std::runtime_error as it inherits from std::logic_error.
TEUCHOS_UNIT_TEST( ContractException, differentiation_test )
{
  try
  {
    throw Utility::ContractException( "Utility logic error" );
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
// Check that a Utility::ContractException can be caught and the appropriate
// error message is written
TEUCHOS_UNIT_TEST( ContractException, message_test )
{
  std::string message;

  try
  {
    throw Utility::ContractException( "contract broken" );
  }
  catch( const Utility::ContractException& exception )
  {
    message = std::string( exception.what() );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }

  const std::string true_message( "contract broken" );
  TEST_ASSERT( 0 == message.compare( true_message ) );
}

//---------------------------------------------------------------------------//
// Check that we can throw a Utility::ContractException with
// TEUCHOS_TEST_FOR_EXCEPTION
TEUCHOS_UNIT_TEST( ContractException, teuchos_throw_test )
{
  try
  {
    TEUCHOS_TEST_FOR_EXCEPTION( true,
				Utility::ContractException,
				"Utility assertion failed" << std::endl );
  }
  catch( const Utility::ContractException& assertion )
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
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
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
#if HAVE_FRENSIE_DBC
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
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
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
#if HAVE_FRENSIE_DBC
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
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
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
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 0 );
#endif
  }
}

//---------------------------------------------------------------------------//
// Test that nested conditions of a function can be tested
TEUCHOS_UNIT_TEST( ContractException, nested_function_conditions_test )
{
  double dummy;

  // Check that nothing happens when nested function conditions pass
  try{
    testNestedConditions( dummyPreconditionPassTestFunction() );
    testNestedConditions( dummy = dummyPostconditionPassTestFunction( 1.0 ) );
    testNestedConditions( dummy = dummyInvariantPassTestFunction( 1.0, 1.0 ) );
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }

  // Check that nested function conditions can be caught
  try{
    testNestedConditions( dummyPreconditionFailTestFunction() );
  }
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    std::string message( exception.what() );
    std::string partial_message( "Nested condition violated" );
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
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 0 );
#endif
  }

  try{
    testNestedConditions( dummy = dummyPostconditionFailTestFunction( 1.0 ) );
  }
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    std::string message( exception.what() );
    std::string partial_message( "Nested condition violated" );
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
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 0 );
#endif
  }

  try{
    testNestedConditions( dummy = dummyInvariantFailTestFunction( 1.0, 1.0 ) );
  }
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    std::string message( exception.what() );
    std::string partial_message( "Nested condition violated" );
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
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 0 );
#endif
  }
}

//---------------------------------------------------------------------------//
// Test that nested conditions of all functions in a block can be tested
TEUCHOS_UNIT_TEST( ContractException, nested_block_conditions_test )
{
  double dummy;

  // Check that nothing happens when nested function conditions pass
  try{
    testNestedConditionsBegin(1);

    dummyPreconditionPassTestFunction();
    dummy = dummyPostconditionPassTestFunction( 1.0 );
    dummy = dummyInvariantPassTestFunction( 1.0, 1.0 );

    testNestedConditionsEnd(1);
  }
  catch( ... )
  {
    TEST_ASSERT( 0 );
  }

  // Check that nested function conditions can be caught
  try{
    testNestedConditionsBegin(1);

    dummyPreconditionFailTestFunction();

    testNestedConditionsEnd(1);
  }
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    std::string message( exception.what() );
    std::string partial_message( "Nested condition violated" );
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
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 0 );
#endif
  }

  try{
    testNestedConditionsBegin(2);

    dummy = dummyPostconditionFailTestFunction( 1.0 );

    testNestedConditionsEnd(2);
  }
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    std::string message( exception.what() );
    std::string partial_message( "Nested condition violated" );
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
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 0 );
#endif
  }

  try{
    testNestedConditionsBegin(1);

    testNestedConditionsBegin(2);

    dummy = dummyInvariantFailTestFunction( 1.0, 1.0 );

    testNestedConditionsEnd(2);

    testNestedConditionsEnd(1);
  }
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    std::string message( exception.what() );
    std::string partial_message( "Nested condition violated" );
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
#if HAVE_FRENSIE_DBC
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
  catch( const Utility::ContractException& exception )
  {
#if HAVE_FRENSIE_DBC
    TEST_ASSERT( 1 );
#else
    TEST_ASSERT( 0 );
#endif
  }
  catch( ... )
  {
#if HAVE_FRENSIE_DBC
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

//---------------------------------------------------------------------------//
// end tstContractException.cpp
//---------------------------------------------------------------------------//

