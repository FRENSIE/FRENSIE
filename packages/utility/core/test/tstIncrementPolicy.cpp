//---------------------------------------------------------------------------//
//!
//! \file   tstIncrementPolicy.hpp
//! \author Alex Robinson
//! \brief  Increment policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ActiveCounter.hpp"
#include "Utility_IncrementPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )   \
  typedef unsigned long long uint64;            \
  typedef unsigned long uint32;                 \
  typedef Utility::ActiveCounter<uint64> counter;                       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint32 )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint64 )            \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )            \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, counter )

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
template<typename T>
void initializeCounter( T& counter )
{
  counter = 0;
}

void initializeCounter( Utility::ActiveCounter<unsigned long long>& counter )
{ /* ... */ }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a counter increment can be ignored
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IgnoreIncrementPolicy, increment, T )
{
  T counter;

  initializeCounter( counter );
  
  Utility::IgnoreIncrementPolicy::increment( counter );

  unsigned long long raw_counter = counter;

  TEST_EQUALITY_CONST( raw_counter, 0ull );
}

UNIT_TEST_INSTANTIATION( IgnoreIncrementPolicy, increment );

//---------------------------------------------------------------------------//
// Check that a counter can be incremented
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( IncrementPolicy, increment, T )
{
  T counter;

  initializeCounter( counter );
  
  Utility::IncrementPolicy::increment( counter );

  unsigned long long raw_counter = counter;

  TEST_EQUALITY_CONST( raw_counter, 1ull );
}

UNIT_TEST_INSTANTIATION( IncrementPolicy, increment );

//---------------------------------------------------------------------------//
// end tstIncrementPolicy.cpp
//---------------------------------------------------------------------------//
