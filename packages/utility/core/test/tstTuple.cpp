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
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float );    \
  // TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double );   \
  // TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );      \
  // TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long )

#define UNIT_TEST_TEMPLATE_2_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, float, float );   \
  // TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, double ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int );       \
  // TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, unsigned, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, long );       \
  // TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, int );      \
  // TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double )

#define UNIT_TEST_TEMPLATE_3_INSTANT( type, name )       \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, float, float, float ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, double, double ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, int );    \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, unsigned, unsigned, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, long, long, long ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, int, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, unsigned, double, int ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, unsigned, double ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, double, unsigned, int )

#define UNIT_TEST_TEMPLATE_4_INSTANT( type, name )    \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, float, float, float ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, double, double, double ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, int, int );   \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, unsigned, unsigned, unsigned, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, long, long ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, double, int, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, unsigned, float, double, int ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, unsigned, float, double ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, int, unsigned, float ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, int, double, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, int, float, unsigned ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, float, unsigned, double, int ); \
  // TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, double, unsigned, float, int )

//---------------------------------------------------------------------------//
// Tests.
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
// end tstTuple.cpp
//---------------------------------------------------------------------------//
