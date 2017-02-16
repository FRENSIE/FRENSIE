//---------------------------------------------------------------------------//
//!
//! \file   tstTuple.cpp
//! \author Alex Robinson
//! \brief  Tuple unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_SINGLE_ELEM_TUPLE_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long )

#define UNIT_TEST_DOUBLE_ELEM_TUPLE_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, float, float );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, unsigned, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, long );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, int );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double )

#define UNIT_TEST_TRIPLE_ELEM_TUPLE_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, float, float, float ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, double, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, int );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, unsigned, unsigned, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, long, long, long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, int, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, unsigned, double, int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, unsigned, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, unsigned, int )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an empty tuple can be constructed
TEUCHOS_UNIT_TEST( Tuple_0, constructor )
{
  // We just ensure that this compiles
  Utility::Tuple<> empty_tuple;
}

//---------------------------------------------------------------------------//
// Check that a tuple with a single element can be constructed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, constructor, T )
{
  Utility::Tuple<T> tuple_1( 1 );
  
  TEST_EQUALITY_CONST( tuple_1.head, 1 );

  // Check that the single alias will also work
  Utility::Single<T> single( 1 );

  TEST_EQUALITY_CONST( single.head, 1 );
}

UNIT_TEST_SINGLE_ELEM_TUPLE_INSTANT( Tuple_1, constructor );

//---------------------------------------------------------------------------//
// Check that a tuple with two elements can be constructed
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, constructor, T1, T2 )
{
  Utility::Tuple<T1,T2> tuple_2( 2, 1 );
  
  TEST_EQUALITY_CONST( tuple_2.head, 2 );
  TEST_EQUALITY_CONST( dynamic_cast<Utility::Tuple<T2>&>( tuple_2 ).head, 1 );

  // Check that the pair alias will also work
  Utility::Pair<T1,T2> pair( 2, 1 );

  TEST_EQUALITY_CONST( pair.head, 2 );
  TEST_EQUALITY_CONST( dynamic_cast<Utility::Single<T2>&>( pair ).head, 1 );
}

UNIT_TEST_DOUBLE_ELEM_TUPLE_INSTANT( Tuple_2, constructor );

//---------------------------------------------------------------------------//
// Check that a tuple with three elements can be constructed
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, constructor, T1, T2, T3 )
{
  Utility::Tuple<T1,T2,T3> tuple_3( 3, 2, 1 );

  TEST_EQUALITY_CONST( tuple_3.head, 3 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::Tuple<T2,T3>&>( tuple_3 ).head), 2 );
  TEST_EQUALITY_CONST( dynamic_cast<Utility::Tuple<T3>&>( tuple_3 ).head, 1 );

  Utility::Trip<T1,T2,T3> trip( 3, 2, 1 );

  TEST_EQUALITY_CONST( trip.head, 3 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::Pair<T2,T3>&>( trip ).head), 2 );
  TEST_EQUALITY_CONST( dynamic_cast<Utility::Single<T3>&>( trip ).head, 1 );
}

UNIT_TEST_TRIPLE_ELEM_TUPLE_INSTANT( Tuple_3, constructor );

//---------------------------------------------------------------------------//
// Check that a tuple can be constructed
// TEUCHOS_UNIT_TEST( Tuple, constructor )
// {
//   Utility::Tuple<double> tuple_1( 1.0 );
//   TEST_EQUALITY_CONST( tuple_1.head, 1.0 );

//   Utility::Tuple<double,double> tuple_2( 1.0, 2.0 );
//   TEST_EQUALITY_CONST( tuple_2.head, 1.0 );
//   TEST_EQUALITY_CONST( dynamic_cast<Utility::Tuple<double>& >( tuple_2 ).head, 2.0 );

//   Utility::Tuple<double,double,double> tuple_3( 1.0, 2.0, 3.0 );
//   TEST_EQUALITY_CONST( tuple_3.head, 1.0 );
//   TEST_EQUALITY_CONST( (dynamic_cast<Utility::Tuple<double,double>& >( tuple_3 ).head), 2.0 );
//   TEST_EQUALITY_CONST( dynamic_cast<Utility::Tuple<double>& >( tuple_3 ).head, 3.0 );

//   Utility::Tuple<double,double,double,double> tuple_4( 1.0, 2.0, 3.0, 4.0 );
//   TEST_EQUALITY_CONST( tuple_4.head, 1.0 );
//   TEST_EQUALITY_CONST( (dynamic_cast<Utility::Tuple<double,double,double>& >( tuple_4 ).head), 2.0 );
//   TEST_EQUALITY_CONST( (dynamic_cast<Utility::Tuple<double,double>& >( tuple_4 ).head), 3.0 );
//   TEST_EQUALITY_CONST( dynamic_cast<Utility::Tuple<double>& >( tuple_4 ).head, 4.0 );
// }

//---------------------------------------------------------------------------//
// end tstTuple.cpp
//---------------------------------------------------------------------------//
