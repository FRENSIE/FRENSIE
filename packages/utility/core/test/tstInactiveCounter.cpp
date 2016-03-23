//---------------------------------------------------------------------------//
//!
//! \file   tstInactiveCounter.cpp
//! \author Alex Robinson
//! \brief  Inactive counter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InactiveCounter.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )   \
  typedef unsigned long long uint64;            \
  typedef unsigned long uint32;                 \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint32 )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint64 )            \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the counter can be incremented
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, increment, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter( new Utility::InactiveCounter<T> );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );

  counter->increment();

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, increment );

//---------------------------------------------------------------------------//
// Check that the counter can be pre-incremented
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, preincrement, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter( new Utility::InactiveCounter<T> );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );

  ++(*counter);

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, preincrement );

//---------------------------------------------------------------------------//
// Check that a value can be added to the counter
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, addToCount_raw, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter( new Utility::InactiveCounter<T> );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );

  counter->addToCount( static_cast<T>( 2 ) );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, addToCount_raw );

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, assignment_raw, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter( new Utility::InactiveCounter<T> );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );

  (*counter) += static_cast<T>( 2 );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, assignment_raw );

//---------------------------------------------------------------------------//
// Check that two counters can be added
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, addToCount, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter_a( new Utility::InactiveCounter<T> );
  
  std::shared_ptr<Utility::Counter<T> > 
    counter_b( new Utility::InactiveCounter<T> );
  
  ++(*counter_a);
  
  *counter_b += static_cast<T>( 2 );

  counter_a->addToCount( *counter_b );

  TEST_EQUALITY_CONST( counter_a->getCount(), static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, addToCount );

//---------------------------------------------------------------------------//
// Check that two counters can be added
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, assignment, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter_a( new Utility::InactiveCounter<T> );
  
  std::shared_ptr<Utility::Counter<T> > 
    counter_b( new Utility::InactiveCounter<T> );
  
  ++(*counter_a);
  
  *counter_b += static_cast<T>( 2 );

  *counter_a += *counter_b;

  TEST_EQUALITY_CONST( counter_a->getCount(), static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, assignment );

//---------------------------------------------------------------------------//
// Check that the implicit conversion operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( InactiveCounter, implicit_conversion, T )
{
  std::shared_ptr<Utility::Counter<T> > 
    counter( new Utility::InactiveCounter<T> );

  TEST_EQUALITY_CONST( counter->getCount(), static_cast<T>( 0 ) );

  T raw_counter = *counter;

  TEST_EQUALITY_CONST( raw_counter, static_cast<T>( 0 ) );
}

UNIT_TEST_INSTANTIATION( InactiveCounter, implicit_conversion );

//---------------------------------------------------------------------------//
// end tstInactiveCounter.cpp
//---------------------------------------------------------------------------//
