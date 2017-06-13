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
#include "Utility_Tuple.hpp"
#include "Utility_HumanReadableSerializer.hpp"
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
  TEST_EQUALITY_CONST( Utility::TupleSize<Utility::Tuple<> >::value, 0 );
  TEST_EQUALITY_CONST( Utility::TupleSize<std::tuple<> >::value, 0 );

  TEST_EQUALITY_CONST( std::tuple_size<Utility::Tuple<> >::value, 0 );
  TEST_EQUALITY_CONST( std::tuple_size<std::tuple<> >::value, 0 );
}

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, TupleSize, T )
{
  TEST_EQUALITY_CONST( Utility::TupleSize<Utility::Tuple<T> >::value, 1 );
  TEST_EQUALITY_CONST( Utility::TupleSize<std::tuple<T> >::value, 1 );

  TEST_EQUALITY_CONST( std::tuple_size<Utility::Tuple<T> >::value, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Tuple_1, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, TupleSize, T1, T2 )
{
  TEST_EQUALITY_CONST( (Utility::TupleSize<Utility::Tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<Utility::Pair<T1,T2> >::value), 2 );

  TEST_EQUALITY_CONST( (std::tuple_size<Utility::Tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
  TEST_EQUALITY_CONST( (std::tuple_size<Utility::Pair<T1,T2> >::value), 2 );
}

UNIT_TEST_TEMPLATE_2_INSTANT( Tuple_2, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, TupleSize, T1, T2, T3 )
{
  TEST_EQUALITY_CONST( (Utility::TupleSize<Utility::Tuple<T1,T2,T3> >::value), 3 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<Utility::Trip<T1,T2,T3> >::value), 3 );

  TEST_EQUALITY_CONST( (std::tuple_size<Utility::Tuple<T1,T2,T3> >::value), 3 );
  TEST_EQUALITY_CONST( (std::tuple_size<Utility::Trip<T1,T2,T3> >::value), 3 );
}

UNIT_TEST_TEMPLATE_3_INSTANT( Tuple_3, TupleSize );

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Tuple_4, TupleSize, T1, T2, T3, T4 )
{
  TEST_EQUALITY_CONST( (Utility::TupleSize<Utility::Tuple<T1,T2,T3,T4> >::value), 4 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  TEST_EQUALITY_CONST( (Utility::TupleSize<Utility::Quad<T1,T2,T3,T4> >::value), 4 );
  
  TEST_EQUALITY_CONST( (std::tuple_size<Utility::Tuple<T1,T2,T3,T4> >::value), 4 );
  TEST_EQUALITY_CONST( (std::tuple_size<Utility::Quad<T1,T2,T3,T4> >::value ), 4 );
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
  Utility::Tuple<T> tuple_1( 1 );
  
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
  Utility::Tuple<T1,T2> tuple_2( 2, 1 );
  
  TEST_EQUALITY_CONST( std::get<0>( tuple_2 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<0>( tuple_2 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<Utility::FIRST>( tuple_2 ), 2 );

  TEST_EQUALITY_CONST( std::get<1>( tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<Utility::SECOND>( tuple_2 ), 1 );

  // Check that the pair alias will also work
  Utility::Pair<T1,T2> pair( 2, 1 );

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
  Utility::Tuple<T1,T2,T3> tuple_3( 3, 2, 1 );

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
  Utility::Trip<T1,T2,T3> trip( 3, 2, 1 );

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
  Utility::Tuple<T1,T2,T3,T4> tuple_4( 4, 3, 2, 1 );

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
  Utility::Quad<T1,T2,T3,T4> quad( 4, 3, 2, 1 );

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
  Utility::Tuple<T> tuple_1( 1 );

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
  Utility::Tuple<T1,T2> tuple_2( 1, 1 );

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
  Utility::Pair<T1,T2> pair( 1, 1 );

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
  Utility::Tuple<T1,T2,T3> tuple_3( 1, 1, 1 );

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
  Utility::Trip<T1,T2,T3> trip( 1, 1, 1 );
  
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
  Utility::Tuple<T1,T2,T3,T4> tuple_4( 1, 1, 1, 1 );

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
  Utility::Quad<T1,T2,T3,T4> quad( 1, 1, 1, 1 );

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
  Utility::Tuple<T> tuple_1( 1 );

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
  Utility::Tuple<T1,T2> tuple_2( 1, 1 );

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
  Utility::Tuple<T1,T2,T3> tuple_3( 1, 1, 1 );

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
  Utility::Tuple<T1,T2,T3,T4> tuple_4( 1, 1, 1, 1 );

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
// Check that a tuple can be constructed using the standalone method
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Tuple_1, makeTuple, T )
{
  Utility::Tuple<T> tuple_1 = Utility::makeTuple( T( 1 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_1 ), 1 );

  // Check that std tuple can also be used
  std::tuple<T> std_tuple_1 = Utility::makeTuple( T( 1 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_1 ), 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( Tuple_1, makeTuple );

//---------------------------------------------------------------------------//
// Check that a tuple can be contructed using the standalone method
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Tuple_2, makeTuple, T1, T2 )
{
  Utility::Tuple<T1,T2> tuple_2 = Utility::makeTuple( T1( 1 ), T2( 2 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_2 ), 2 );

  // Check that std tuple can also be used
  std::tuple<T1,T2> std_tuple_2 = Utility::makeTuple( T1( 1 ), T2( 2 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_2 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_2 ), 2 );
}

UNIT_TEST_TEMPLATE_2_INSTANT( Tuple_2, makeTuple );

//---------------------------------------------------------------------------//
// Check that a tuple can be constructed using the standalone method
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Tuple_3, makeTuple, T1, T2, T3 )
{
  Utility::Tuple<T1,T2,T3> tuple_3 = Utility::makeTuple( T1( 1 ), T2( 2 ), T3( 3 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_3 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_3 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<2>( tuple_3 ), 3 );

  // Check that std tuple can also be used
  std::tuple<T1,T2,T3> std_tuple_3 = Utility::makeTuple( T1( 1 ), T2( 2 ), T3( 3 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_3 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_3 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_3 ), 3 );
}

UNIT_TEST_TEMPLATE_3_INSTANT( Tuple_3, makeTuple );

//---------------------------------------------------------------------------//
// Check that a tuple can be constructed using the standalone method
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Tuple_4, makeTuple, T1, T2, T3, T4 )
{
  Utility::Tuple<T1,T2,T3,T4> tuple_4 =
    Utility::makeTuple( T1( 1 ), T2( 2 ), T3( 3 ), T4( 4 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( tuple_4 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( tuple_4 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<2>( tuple_4 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<3>( tuple_4 ), 4 );

  // Check that std tuple can also be used
  std::tuple<T1,T2,T3,T4> std_tuple_4 =
    Utility::makeTuple( T1( 1 ), T2( 2 ), T3( 3 ), T4( 4 ) );

  TEST_EQUALITY_CONST( Utility::get<0>( std_tuple_4 ), 1 );
  TEST_EQUALITY_CONST( Utility::get<1>( std_tuple_4 ), 2 );
  TEST_EQUALITY_CONST( Utility::get<2>( std_tuple_4 ), 3 );
  TEST_EQUALITY_CONST( Utility::get<3>( std_tuple_4 ), 4 );
}

UNIT_TEST_TEMPLATE_4_INSTANT( Tuple_4, makeTuple );

//---------------------------------------------------------------------------//
// end tstTuple.cpp
//---------------------------------------------------------------------------//
