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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long )

#define UNIT_TEST_TEMPLATE_2_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, float, float );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, unsigned, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, long );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, int );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double )

#define UNIT_TEST_TEMPLATE_3_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, float, float, float ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, double, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, int );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, unsigned, unsigned, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, long, long, long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, int, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, unsigned, double, int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, unsigned, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, unsigned, int )

#define UNIT_TEST_TEMPLATE_4_INSTANT( type, name )    \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, float, float, float ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, double, double, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, int, int );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, unsigned, unsigned, unsigned, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, long, long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, double, int, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, unsigned, float, double, int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, unsigned, float, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, int, unsigned, float ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, int, double, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, int, float, unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, unsigned, double, int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, unsigned, float, int )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Basic, TupleSize, T )
{
  TEST_EQUALITY_CONST( Utility::TupleSize<T>::value, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Basic, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST( Tuple_0, TupleSize )
{
  TEST_EQUALITY_CONST( Utility::TupleSize<std::tuple<> >::value, 0 );
  TEST_EQUALITY_CONST( Utility::TupleSize<std::tuple<> >::value, 0 );

  TEST_EQUALITY_CONST( std::tuple_size<std::tuple<> >::value, 0 );
  TEST_EQUALITY_CONST( std::tuple_size<std::tuple<> >::value, 0 );
}

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, TupleSize, T )
{
  TEST_EQUALITY_CONST( Utility::TupleSize<std::tuple<T> >::value, 1 );
  TEST_EQUALITY_CONST( Utility::TupleSize<std::tuple<T> >::value, 1 );

  TEST_EQUALITY_CONST( std::tuple_size<std::tuple<T> >::value, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Tuple_1, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, TupleSize, T1, T2 )
{
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );

  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
}

UNIT_TEST_TEMPLATE_2_INSTANT( Tuple_2, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, TupleSize, T1, T2, T3 )
{
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );

  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2,T3> >::value), 3 );
  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2,T3> >::value), 3 );
}

UNIT_TEST_TEMPLATE_3_INSTANT( Tuple_3, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Tuple_4, TupleSize, T1, T2, T3, T4 )
{
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  
  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2,T3,T4> >::value), 4 );
  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2,T3,T4> >::value ), 4 );
}

UNIT_TEST_TEMPLATE_4_INSTANT( Tuple_4, TupleSize );

//---------------------------------------------------------------------------//
// Check that basic types can be treated like tuples
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Basic, get, T )
{
  T value( 1 );

  TEST_EQUALITY_CONST( Utility::get<0>( value ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( value ), 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Basic, get );

//---------------------------------------------------------------------------//
// Check that a 1-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, get, T )
{
  std::tuple<T> tuple_1( 1 );
  
  TEST_EQUALITY_CONST( std::get<0>( tuple_1 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_1 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_1 ), 1 );

  // Check that the std tuple will also work
  std::tuple<T> std_tuple_1( 1 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_1 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_1 ), 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Tuple_1, get );

//---------------------------------------------------------------------------//
// Check that a 2-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, get, T1, T2 )
{
  std::tuple<T1,T2> tuple_2( 2, 1 );
  
  TEST_EQUALITY_CONST( std::get<0>( tuple_2 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_2 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_2 ), 2 );

  TEST_EQUALITY_CONST( std::get<1>( tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_2 ), 1 );

  // Check that the pair alias will also work
  std::tuple<T1,T2> pair( 2, 1 );

  TEST_EQUALITY_CONST( std::get<0>( pair ), 2 );
  TEST_EQUALITY_CONST( Utility::get<0>( pair ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( pair ), 2 );

  TEST_EQUALITY_CONST( std::get<1>( pair ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( pair ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( pair ), 1 );

  // Check that the std tuple will also work
  std::tuple<T1,T2> std_tuple_2( 2, 1 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_2 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_2 ), 2 );

  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( std_tuple_2 ), 1 );
}

UNIT_TEST_TEMPLATE_2_INSTANT( Tuple_2, get );

//---------------------------------------------------------------------------//
// Check that a 3-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, get, T1, T2, T3 )
{
  std::tuple<T1,T2,T3> tuple_3( 3, 2, 1 );

  TEST_EQUALITY_CONST( std::get<0>( tuple_3 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_3 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_3 ), 3 );

  TEST_EQUALITY_CONST( std::get<1>( tuple_3 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_3 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_3 ), 2 );

  TEST_EQUALITY_CONST( std::get<2>( tuple_3 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<2>( tuple_3 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( tuple_3 ), 1 );

  // Check that the trip alias will also work
  std::tuple<T1,T2,T3> trip( 3, 2, 1 );

  TEST_EQUALITY_CONST( std::get<0>( trip ), 3 );
  TEST_EQUALITY_CONST( Utility::get<0>( trip ), 3 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( trip ), 3 );

  TEST_EQUALITY_CONST( std::get<1>( trip ), 2 );
  TEST_EQUALITY_CONST( Utility::get<1>( trip ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( trip ), 2 );

  TEST_EQUALITY_CONST( std::get<2>( trip ), 1 );
  TEST_EQUALITY_CONST( Utility::get<2>( trip ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( trip ), 1 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3> std_tuple_3( 3, 2, 1 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_3 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_3 ), 3 );

  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_3 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( std_tuple_3 ), 2 );

  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_3 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( std_tuple_3 ), 1 );
}

UNIT_TEST_TEMPLATE_3_INSTANT( Tuple_3, get );

//---------------------------------------------------------------------------//
// Check that a 4-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Tuple_4, get, T1, T2, T3, T4 )
{
  std::tuple<T1,T2,T3,T4> tuple_4( 4, 3, 2, 1 );

  TEST_EQUALITY_CONST( std::get<0>( tuple_4 ), 4 );
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_4 ), 4 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_4 ), 4 );

  TEST_EQUALITY_CONST( std::get<1>( tuple_4 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_4 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_4 ), 3 );

  TEST_EQUALITY_CONST( std::get<2>( tuple_4 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<2>( tuple_4 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( tuple_4 ), 2 );

  TEST_EQUALITY_CONST( std::get<3>( tuple_4 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<3>( tuple_4 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FOURTH>( tuple_4 ), 1 );

  // Check that the quad alias will also work
  std::tuple<T1,T2,T3,T4> quad( 4, 3, 2, 1 );

  TEST_EQUALITY_CONST( std::get<0>( quad ), 4 );
  TEST_EQUALITY_CONST( Utility::get<0>( quad ), 4 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( quad ), 4 );

  TEST_EQUALITY_CONST( std::get<1>( quad ), 3 );
  TEST_EQUALITY_CONST( Utility::get<1>( quad ), 3 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( quad ), 3 );

  TEST_EQUALITY_CONST( std::get<2>( quad ), 2 );
  TEST_EQUALITY_CONST( Utility::get<2>( quad ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( quad ), 2 );

  TEST_EQUALITY_CONST( std::get<3>( quad ), 1 );
  TEST_EQUALITY_CONST( Utility::get<3>( quad ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FOURTH>( quad ), 1 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3,T4> std_tuple_4( 4, 3, 2, 1 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_4 ), 4 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_4 ), 4 );

  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_4 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( std_tuple_4 ), 3 );

  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_4 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( std_tuple_4 ), 2 );

  TEST_EQUALITY_CONST( Utility::get<3>( std_tuple_4 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FOURTH>( std_tuple_4 ), 1 );
}

UNIT_TEST_TEMPLATE_4_INSTANT( Tuple_4, get );

//---------------------------------------------------------------------------//
// Check that basic types can be treated like tuples
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Basic, get_reference, T )
{
  T value( 1 );

  Utility::get<0>( value ) = 2;
  TEST_EQUALITY_CONST( Utility::get<0>( value ), 2 );

  Utility::get<Utility::FIRST>( value ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( value ), 3 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Basic, get_reference );

//---------------------------------------------------------------------------//
// Check that a 1-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, get_reference, T )
{
  std::tuple<T> tuple_1( 1 );

  std::get<0>( tuple_1 ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( tuple_1 ), 2 );

  Utility::get<0>( tuple_1 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_1 ), 3 );

  Utility::get<Utility::FIRST>( tuple_1 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_1 ), 4 );

  // Check that the std tuple will also work
  std::tuple<T> std_tuple_1( 1 );

  Utility::get<0>( std_tuple_1 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_1 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_1 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_1 ), 3 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Tuple_1, get_reference );

//---------------------------------------------------------------------------//
// Check that a 2-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, get_reference, T1, T2 )
{
  std::tuple<T1,T2> tuple_2( 1, 1 );

  std::get<0>( tuple_2 ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( tuple_2 ), 2 );

  Utility::get<0>( tuple_2 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_2 ), 3 );

  Utility::get<Utility::FIRST>( tuple_2 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_2 ), 4 );

  std::get<1>( tuple_2 ) = 2;
  TEST_EQUALITY_CONST( std::get<1>( tuple_2 ), 2 );

  Utility::get<1>( tuple_2 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_2 ), 3 );

  Utility::get<Utility::SECOND>( tuple_2 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_2 ), 4 );

  // Check that the pair alias will also work
  std::tuple<T1,T2> pair( 1, 1 );

  std::get<0>( pair ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( pair ), 2 );

  Utility::get<0>( pair ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( pair ), 3 );

  Utility::get<Utility::FIRST>( pair ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( pair ), 4 );

  std::get<1>( pair ) = 2;
  TEST_EQUALITY_CONST( std::get<1>( pair ), 2 );

  Utility::get<1>( pair ) = 3;
  TEST_EQUALITY_CONST( Utility::get<1>( pair ), 3 );

  Utility::get<Utility::SECOND>( pair ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( pair ), 4 );

  // Check that the std tuple will also work
  std::tuple<T1,T2> std_tuple_2( 1, 1 );

  Utility::get<0>( std_tuple_2 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_2 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_2 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_2 ), 3 );

  Utility::get<1>( std_tuple_2 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_2 ), 2 );

  Utility::get<Utility::SECOND>( std_tuple_2 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( std_tuple_2 ), 3 );
}

UNIT_TEST_TEMPLATE_2_INSTANT( Tuple_2, get_reference );

//---------------------------------------------------------------------------//
// Check that a 3-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, get_reference, T1, T2, T3 )
{
  std::tuple<T1,T2,T3> tuple_3( 1, 1, 1 );

  std::get<0>( tuple_3 ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( tuple_3 ), 2 );

  Utility::get<0>( tuple_3 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_3 ), 3 );

  Utility::get<Utility::FIRST>( tuple_3 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_3 ), 4 );

  std::get<1>( tuple_3 ) = 2;
  TEST_EQUALITY_CONST( std::get<1>( tuple_3 ), 2 );

  Utility::get<1>( tuple_3 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_3 ), 3 );

  Utility::get<Utility::SECOND>( tuple_3 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_3 ), 4 );

  std::get<2>( tuple_3 ) = 2;
  TEST_EQUALITY_CONST( std::get<2>( tuple_3 ), 2 );

  Utility::get<2>( tuple_3 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<2>( tuple_3 ), 3 );

  Utility::get<Utility::THIRD>( tuple_3 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( tuple_3 ), 4 );

  // Check that the trip alias will also work
  std::tuple<T1,T2,T3> trip( 1, 1, 1 );
  
  std::get<0>( trip ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( trip ), 2 );

  Utility::get<0>( trip ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( trip ), 3 );

  Utility::get<Utility::FIRST>( trip ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( trip ), 4 );

  std::get<1>( trip ) = 2;
  TEST_EQUALITY_CONST( std::get<1>( trip ), 2 );

  Utility::get<1>( trip ) = 3;
  TEST_EQUALITY_CONST( Utility::get<1>( trip ), 3 );

  Utility::get<Utility::SECOND>( trip ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( trip ), 4 );

  std::get<2>( trip ) = 2;
  TEST_EQUALITY_CONST( std::get<2>( trip ), 2 );

  Utility::get<2>( trip ) = 3;
  TEST_EQUALITY_CONST( Utility::get<2>( trip ), 3 );

  Utility::get<Utility::THIRD>( trip ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( trip ), 4 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3> std_tuple_3( 1, 1, 1 );

  Utility::get<0>( std_tuple_3 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_3 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_3 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_3 ), 3 );

  Utility::get<1>( std_tuple_3 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_3 ), 2 );

  Utility::get<Utility::SECOND>( std_tuple_3 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( std_tuple_3 ), 3 );

  Utility::get<2>( std_tuple_3 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_3 ), 2 );

  Utility::get<Utility::THIRD>( std_tuple_3 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( std_tuple_3 ), 3 );
}

UNIT_TEST_TEMPLATE_3_INSTANT( Tuple_3, get_reference );

//---------------------------------------------------------------------------//
// Check that a 4-element tuple's elements can be retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Tuple_4, get_reference, T1, T2, T3, T4 )
{
  std::tuple<T1,T2,T3,T4> tuple_4( 1, 1, 1, 1 );

  std::get<0>( tuple_4 ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( tuple_4 ), 2 );

  Utility::get<0>( tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_4 ), 3 );

  Utility::get<Utility::FIRST>( tuple_4 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_4 ), 4 );

  std::get<1>( tuple_4 ) = 2;
  TEST_EQUALITY_CONST( std::get<1>( tuple_4 ), 2 );

  Utility::get<1>( tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_4 ), 3 );

  Utility::get<Utility::SECOND>( tuple_4 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_4 ), 4 );

  std::get<2>( tuple_4 ) = 2;
  TEST_EQUALITY_CONST( std::get<2>( tuple_4 ), 2 );

  Utility::get<2>( tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<2>( tuple_4 ), 3 );

  Utility::get<Utility::THIRD>( tuple_4 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( tuple_4 ), 4 );

  std::get<3>( tuple_4 ) = 2;
  TEST_EQUALITY_CONST( std::get<3>( tuple_4 ), 2 );

  Utility::get<3>( tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<3>( tuple_4 ), 3 );

  Utility::get<Utility::FOURTH>( tuple_4 ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FOURTH>( tuple_4 ), 4 );

  // Check that the quad alias will also work
  std::tuple<T1,T2,T3,T4> quad( 1, 1, 1, 1 );

  std::get<0>( quad ) = 2;
  TEST_EQUALITY_CONST( std::get<0>( quad ), 2 );

  Utility::get<0>( quad ) = 3;
  TEST_EQUALITY_CONST( Utility::get<0>( quad ), 3 );

  Utility::get<Utility::FIRST>( quad ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( quad ), 4 );

  std::get<1>( quad ) = 2;
  TEST_EQUALITY_CONST( std::get<1>( quad ), 2 );

  Utility::get<1>( quad ) = 3;
  TEST_EQUALITY_CONST( Utility::get<1>( quad ), 3 );

  Utility::get<Utility::SECOND>( quad ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( quad ), 4 );

  std::get<2>( quad ) = 2;
  TEST_EQUALITY_CONST( std::get<2>( quad ), 2 );

  Utility::get<2>( quad ) = 3;
  TEST_EQUALITY_CONST( Utility::get<2>( quad ), 3 );

  Utility::get<Utility::THIRD>( quad ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( quad ), 4 );

  std::get<3>( quad ) = 2;
  TEST_EQUALITY_CONST( std::get<3>( quad ), 2 );

  Utility::get<3>( quad ) = 3;
  TEST_EQUALITY_CONST( Utility::get<3>( quad ), 3 );

  Utility::get<Utility::FOURTH>( quad ) = 4;
  TEST_EQUALITY_CONST( Utility::get<Utility::FOURTH>( quad ), 4 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3,T4> std_tuple_4( 1, 1, 1, 1 );

  Utility::get<0>( std_tuple_4 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_4 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( std_tuple_4 ), 3 );

  Utility::get<1>( std_tuple_4 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_4 ), 2 );

  Utility::get<Utility::SECOND>( std_tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( std_tuple_4 ), 3 );

  Utility::get<2>( std_tuple_4 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_4 ), 2 );

  Utility::get<Utility::THIRD>( std_tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::THIRD>( std_tuple_4 ), 3 );

  Utility::get<3>( std_tuple_4 ) = 2;
  TEST_EQUALITY_CONST( Utility::get<3>( std_tuple_4 ), 2 );

  Utility::get<Utility::FOURTH>( std_tuple_4 ) = 3;
  TEST_EQUALITY_CONST( Utility::get<Utility::FOURTH>( std_tuple_4 ), 3 );
}

UNIT_TEST_TEMPLATE_4_INSTANT( Tuple_4, get_reference );

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Basic, set, T )
{
  T tuple( 1 );
  
  typename Utility::TupleElement<0,T>::type value( 2 );

  Utility::set<0>( tuple, value );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple ), 2 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Basic, set );

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, set, T )
{
  std::tuple<T> tuple_1( 1 );

  typename Utility::TupleElement<0,decltype(tuple_1)>::type value_0( 2 );

  Utility::set<0>( tuple_1, value_0 );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_1 ), 2 );

  // Check that std tuple will also work
  std::tuple<T> std_tuple_1( 1 );

  typename Utility::TupleElement<0,decltype(std_tuple_1)>::type std_value_0( 2 );

  Utility::set<0>( std_tuple_1, std_value_0 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Tuple_1, set );

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, set, T1, T2 )
{
  std::tuple<T1,T2> tuple_2( 1, 1 );

  typename Utility::TupleElement<0,decltype(tuple_2)>::type value_0( 2 );

  Utility::set<Utility::FIRST>( tuple_2, value_0 );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_2 ), value_0 );

  typename Utility::TupleElement<1,decltype(tuple_2)>::type value_1( 2 );

  Utility::set<Utility::SECOND>( tuple_2, value_1 );

  TEST_EQUALITY_CONST( Utility::get<1>( tuple_2 ), value_1 );

  // Check that std tuple will also work
  std::tuple<T1,T2> std_tuple_2( 1, 1 );

  typename Utility::TupleElement<0,decltype(std_tuple_2)>::type std_value_0( 2 );

  Utility::set<0>( std_tuple_2, std_value_0 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_2 ), std_value_0 );

  typename Utility::TupleElement<1,decltype(std_tuple_2)>::type std_value_1( 2 );

  Utility::set<1>( std_tuple_2, std_value_1 );

  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_2 ), std_value_1 );
}

UNIT_TEST_TEMPLATE_2_INSTANT( Tuple_2, set );

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, set, T1, T2, T3 )
{
  std::tuple<T1,T2,T3> tuple_3( 1, 1, 1 );

  typename Utility::TupleElement<0,decltype(tuple_3)>::type value_0( 2 );

  Utility::set<Utility::FIRST>( tuple_3, value_0 );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_3 ), value_0 );

  typename Utility::TupleElement<1,decltype(tuple_3)>::type value_1( 2 );

  Utility::set<Utility::SECOND>( tuple_3, value_1 );

  TEST_EQUALITY_CONST( Utility::get<1>( tuple_3 ), value_1 );

  typename Utility::TupleElement<2,decltype(tuple_3)>::type value_2( 2 );

  Utility::set<Utility::THIRD>( tuple_3, value_2 );

  TEST_EQUALITY_CONST( Utility::get<2>( tuple_3 ), value_2 );

  // Check that std tuple will also work
  std::tuple<T1,T2,T3> std_tuple_3( 1, 1, 1 );

  typename Utility::TupleElement<0,decltype(std_tuple_3)>::type std_value_0( 2 );

  Utility::set<0>( std_tuple_3, std_value_0 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_3 ), std_value_0 );

  typename Utility::TupleElement<1,decltype(std_tuple_3)>::type std_value_1( 2 );

  Utility::set<1>( std_tuple_3, std_value_1 );

  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_3 ), std_value_1 );

  typename Utility::TupleElement<2,decltype(std_tuple_3)>::type std_value_2( 2 );

  Utility::set<2>( std_tuple_3, std_value_2 );

  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_3 ), std_value_2 );
}

UNIT_TEST_TEMPLATE_3_INSTANT( Tuple_3, set );

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Tuple_4, set, T1, T2, T3, T4 )
{
  std::tuple<T1,T2,T3,T4> tuple_4( 1, 1, 1, 1 );

  Utility::set<0>( tuple_4, 0 );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_4 ), 0 );

  Utility::set<1>( tuple_4, 1 );

  TEST_EQUALITY_CONST( Utility::get<1>( tuple_4 ), 1 );

  Utility::set<2>( tuple_4, 2 );

  TEST_EQUALITY_CONST( Utility::get<2>( tuple_4 ), 2 );

  Utility::set<3>( tuple_4, 3 );

  TEST_EQUALITY_CONST( Utility::get<3>( tuple_4 ), 3 );

  // Check that std tuple will also work
  std::tuple<T1,T2,T3,T4> std_tuple_4( 1, 1, 1, 1 );

  Utility::set<0>( std_tuple_4, 0 );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_4 ), 0 );

  Utility::set<1>( std_tuple_4, 1 );

  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_4 ), 1 );

  Utility::set<2>( std_tuple_4, 2 );

  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_4 ), 2 );

  Utility::set<3>( std_tuple_4, 3 );

  TEST_EQUALITY_CONST( Utility::get<3>( std_tuple_4 ), 3 );
}

UNIT_TEST_TEMPLATE_4_INSTANT( Tuple_4, set );

//---------------------------------------------------------------------------//
// Check that tuple types can be converted to a string
TEUCHOS_UNIT_TEST( Tuple, toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 0 ) ), "{0}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 0.0f ) ),
                       "{0.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 0.0 ) ),
                       "{0.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( "test" ) ),
                       "{test}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( true ) ),
                       "{true}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( false ) ),
                       "{false}" );
  
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( -1, 1.0 ) ),
                       "{-1, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 1.0f, -1000 ) ),
                       "{1.000000000e+00, -1000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 10l, true ) ),
                       "{10, true}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( true, false ) ),
                       "{true, false}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( std::string( "test" ), false ) ),
                       "{test, false}" );

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    TEST_EQUALITY_CONST( Utility::toString( std::tie( test_string, test_double ) ),
                         "{test string, 1.000000000000000000e+00}" );
                                            
  }

  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 100u, -1, false ) ),
                       "{100, -1, false}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 1.0, true, "test" ) ),
                       "{1.000000000000000000e+00, true, test}" );

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    TEST_EQUALITY_CONST( Utility::toString( std::tie( test_bool, test_ull, test_float ) ),
                         "{true, 256, -1.000000000e+00}" );
  }

  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) ) ),
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that tuple types can be placed in a stream
TEUCHOS_UNIT_TEST( Tuple, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::make_tuple( 0 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 0.0f ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 0.0 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( "test" ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{test}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( true ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{true}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( false ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{false}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( -1, 1.0 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 1.0f, -1000 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+00, -1000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 10l, true ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{10, true}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( true, false ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{true, false}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( std::string( "test" ), false ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{test, false}" );

  oss.str( "" );
  oss.clear();

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    Utility::toStream( oss, std::tie( test_string, test_double ) );
    
    TEST_EQUALITY_CONST( oss.str(),
                         "{test string, 1.000000000000000000e+00}" );

    oss.str( "" );
    oss.clear();                                            
  }

  Utility::toStream( oss, std::make_tuple( 100u, -1, false ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{100, -1, false}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 1.0, true, "test" ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+00, true, test}" );

  oss.str( "" );
  oss.clear();

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    Utility::toStream( oss, std::tie( test_bool, test_ull, test_float ) );

    TEST_EQUALITY_CONST( oss.str(), "{true, 256, -1.000000000e+00}" );

    oss.str( "" );
    oss.clear();
  }

  Utility::toStream( oss, std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) ) );
  
  TEST_EQUALITY_CONST( oss.str(), 
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that pair types can be converted to a string
TEUCHOS_UNIT_TEST( Tuple, pair_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( -1, 1.0 ) ),
                       "{-1, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( -1.0f, 1l ) ),
                       "{-1.000000000e+00, 1}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( "test", true ) ),
                       "{test, true}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( false, std::string( "test" ) ) ),
                       "{false, test}" );
}

//---------------------------------------------------------------------------//
// Check that pair types can be placed in a stream
TEUCHOS_UNIT_TEST( Tuple, pair_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::make_pair( -1, 1.0 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_pair( -1.0f, 1l ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1.000000000e+00, 1}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_pair( "test", true ) );
 
  TEST_EQUALITY_CONST( oss.str(), "{test, true}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_pair( false, std::string( "test" ) ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{false, test}" );
}

//---------------------------------------------------------------------------//
// Check that a pair can be placed in a stream
TEUCHOS_UNIT_TEST( Tuple, pair_ostream )
{
  std::ostringstream oss;
  oss << std::make_pair( -1, 1.0 );

  TEST_EQUALITY_CONST( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_pair( -1.0f, 1l );

  TEST_EQUALITY_CONST( oss.str(), "{-1.000000000e+00, 1}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_pair( "test", true );
  
  TEST_EQUALITY_CONST( oss.str(), "{test, true}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_pair( false, std::string( "test" ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{false, test}" );
}

//---------------------------------------------------------------------------//
// Check that a pair can be extracted from a stream
TEUCHOS_UNIT_TEST( Tuple, pair_istream )
{
  std::istringstream iss( "{-1, 1.000000000000000000e+00}" );

  {
    std::pair<int,double> test_pair;

    iss >> test_pair;

    TEST_EQUALITY_CONST( test_pair, std::make_pair( -1, 1.0 ) );
  }

  iss.str( "{-1.0, 1}" );
  iss.clear();

  {
    std::pair<float,long> test_pair;

    iss >> test_pair;
    
    TEST_EQUALITY_CONST( test_pair, std::make_pair( -1.0f, 1l ) );
  }

  iss.str( "{test, true}" );
  iss.clear();

  {
    std::pair<std::string,bool> test_pair;

    iss >> test_pair;

    TEST_EQUALITY_CONST( test_pair, std::make_pair( std::string( "test" ), true ) );
  }

  iss.str( "{0, test}" );
  iss.clear();

  {
    std::pair<bool,std::string> test_pair;

    iss >> test_pair;

    TEST_EQUALITY_CONST( test_pair, std::make_pair( false, std::string( "test" ) ) );
  }

  iss.str( "{-1000000, -1.0}" );
  iss.clear();
  
  {
    long test_long;
    double test_double;

    std::pair<long&, double&> pair_proxy =
      std::make_pair( std::ref( test_long ), std::ref( test_double ) );

    std::pair<long&, double&>& pair_proxy_reference = pair_proxy;

    Utility::fromStream( iss, pair_proxy_reference );

    TEST_EQUALITY_CONST( test_long, -1000000l );
    TEST_EQUALITY_CONST( test_double, -1.0 );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::pair<int,std::string> test_pair;

    Utility::fromStream( iss, test_pair, "," );

    TEST_EQUALITY_CONST( test_pair, std::make_pair( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_pair;

    TEST_EQUALITY_CONST( test_pair, std::make_pair( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that a tuple can be placed in a stream
TEUCHOS_UNIT_TEST( Tuple, ostream )
{
  std::ostringstream oss;

  oss << std::make_tuple( 0 );
  
  TEST_EQUALITY_CONST( oss.str(), "{0}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 0.0f );
  
  TEST_EQUALITY_CONST( oss.str(), "{0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 0.0 );
  
  TEST_EQUALITY_CONST( oss.str(), "{0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( "test" );
  
  TEST_EQUALITY_CONST( oss.str(), "{test}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( true );
  
  TEST_EQUALITY_CONST( oss.str(), "{true}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( false );
  
  TEST_EQUALITY_CONST( oss.str(), "{false}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( -1, 1.0 );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 1.0f, -1000 );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+00, -1000}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 10l, true );
  
  TEST_EQUALITY_CONST( oss.str(), "{10, true}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( true, false );
  
  TEST_EQUALITY_CONST( oss.str(), "{true, false}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( std::string( "test" ), false );
  
  TEST_EQUALITY_CONST( oss.str(), "{test, false}" );

  oss.str( "" );
  oss.clear();

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    oss << std::tie( test_string, test_double );
    
    TEST_EQUALITY_CONST( oss.str(),
                         "{test string, 1.000000000000000000e+00}" );

    oss.str( "" );
    oss.clear();                                            
  }

  oss << std::make_tuple( 100u, -1, false );
  
  TEST_EQUALITY_CONST( oss.str(), "{100, -1, false}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 1.0, true, "test" );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+00, true, test}" );

  oss.str( "" );
  oss.clear();

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    oss << std::tie( test_bool, test_ull, test_float );

    TEST_EQUALITY_CONST( oss.str(), "{true, 256, -1.000000000e+00}" );

    oss.str( "" );
    oss.clear();
  }

  oss << std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) );
  
  TEST_EQUALITY_CONST( oss.str(), 
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that a tuple can be extracted from a stream
TEUCHOS_UNIT_TEST( Tuple, istream )
{
  std::istringstream iss( "{0}" );

  {
    std::tuple<int> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 0 ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<float> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 0.0f ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<double> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 0.0 ) );
  }

  iss.str( "{test}" );
  iss.clear();

  {
    std::tuple<std::string> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( std::string( "test" ) ) );
  }

  iss.str( "{0}" );
  iss.clear();

  {
    std::tuple<bool> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( false ) );

    iss.str( "{false}" );
    iss.clear();

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( false ) );

    iss.str( "{1}" );
    iss.clear();

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true ) );

    iss.str( "{true}" );
    iss.clear();

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true ) );
  }

  iss.str( "{-1, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::tuple<int,double> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( -1, 1.0 ) );
  }

  iss.str( "{1.000000000e+00, -1000}" );
  iss.clear();

  {
    std::tuple<float,int> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 1.0f, -1000 ) );
  }

  iss.str( "{10, true}" );
  iss.clear();

  {
    std::tuple<long,bool> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 10l, true ) );
  }

  iss.str( "{1, false}" );
  iss.clear();

  {
    std::tuple<bool,bool> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true, false ) );
  }

  iss.str( "{test, 0}" );
  iss.clear();

  {
    std::tuple<std::string,bool> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( std::string( "test" ), false ) );
  }

  iss.str( "{test, -1.0}" );
  iss.clear();
  
  {
    std::string test_string;
    double test_double;

    auto tuple_proxy = std::tie( test_string, test_double );

    Utility::fromStream( iss, tuple_proxy );

    TEST_EQUALITY_CONST( test_string, "test" );
    TEST_EQUALITY_CONST( test_double, -1.0 );
  }

  iss.str( "{100, -1, false}" );
  iss.clear();

  {
    std::tuple<unsigned,int,bool> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 100u, -1, false ) );
  }

  iss.str( "{1.0, 1, test}" );
  iss.clear();

  {
    std::tuple<double,bool,std::string> test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 1.0, true, std::string( "test" ) ) );
  }

  iss.str( "{true, 100000, -1.0}" );
  iss.clear();

  {
    bool test_bool;
    unsigned long long test_ull;
    float test_float;

    auto tuple_proxy = std::tie( test_bool, test_ull, test_float );
    decltype(tuple_proxy)& tuple_proxy_reference = tuple_proxy;

    Utility::fromStream( iss, tuple_proxy_reference );

    TEST_EQUALITY_CONST( test_bool, true );
    TEST_EQUALITY_CONST( test_ull, 100000 );
    TEST_EQUALITY_CONST( test_float, -1.0f );
  }

  iss.str( "{true, -100, test, {-1.0, 1.0}}" );
  iss.clear();

  {
    std::tuple<bool,long long,std::string,std::tuple<float,double> > test_tuple;

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0 ) ) );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::tuple<int,std::string> test_tuple;

    Utility::fromStream( iss, test_tuple, "," );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_tuple;

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// end tstTuple.cpp
//---------------------------------------------------------------------------//
