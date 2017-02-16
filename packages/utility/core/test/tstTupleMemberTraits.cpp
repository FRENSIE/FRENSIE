//---------------------------------------------------------------------------//
//!
//! \file   tstTupleMemberTraits.cpp
//! \author Alex Robinson
//! \brief  Tuple member traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <cstdint>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TupleMemberTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs
//---------------------------------------------------------------------------//
#define UNIT_TEST_PAIR_TYPEDEFS( first_type, first_type_name, second_type, second_type_name ) \
  typedef Utility::Pair<first_type,second_type> utility_pair_##first_type_name##_##second_type_name; \
  typedef std::pair<first_type,second_type> std_pair_##first_type_name##_##second_type_name; \
  typedef std::tuple<first_type,second_type> std_tuple_##first_type_name##_##second_type_name

#define UNIT_TEST_TRIP_TYPEDEFS( first_type, first_type_name, second_type, second_type_name, third_type, third_type_name ) \
  typedef Utility::Trip<first_type,second_type,third_type> utility_trip_##first_type_name##_##second_type_name##_##third_type_name; \
  typedef std::tuple<first_type,second_type,third_type> std_tuple_##first_type_name##_##second_type_name##_##third_type_name

#define UNIT_TEST_QUAD_TYPEDEFS( first_type, first_type_name, second_type, second_type_name, third_type, third_type_name, fourth_type, fourth_type_name ) \
  typedef Utility::Quad<first_type,second_type,third_type,fourth_type> utility_quad_##first_type_name##_##second_type_name##_##third_type_name##_fourth_type_name; \
  typedef std::tuple<first_type,second_type,third_type,fourth_type> std_tuple_##first_type_name##_##second_type_name##_##third_type_name##_fourth_type_name

UNIT_TEST_PAIR_TYPEDEFS( float, float, float, float );
UNIT_TEST_PAIR_TYPEDEFS( double, double, double, double );
UNIT_TEST_PAIR_TYPEDEFS( char, char, char, char );
UNIT_TEST_PAIR_TYPEDEFS( int, int, int, int );
UNIT_TEST_PAIR_TYPEDEFS( unsigned, uint, unsigned, uint );
UNIT_TEST_PAIR_TYPEDEFS( long, lint, long, lint );
UNIT_TEST_PAIR_TYPEDEFS( unsigned long, ulint, unsigned long, ulint );
UNIT_TEST_PAIR_TYPEDEFS( long long, llint, long long, llint );
UNIT_TEST_PAIR_TYPEDEFS( unsigned long long, ullint, unsigned long long, ullint );
UNIT_TEST_PAIR_TYPEDEFS( double, double, int, int );
UNIT_TEST_PAIR_TYPEDEFS( int, int, double, double );

UNIT_TEST_TRIP_TYPEDEFS( double, double, double, double, double, double );
UNIT_TEST_TRIP_TYPEDEFS( int, int, int, int, int, int );
UNIT_TEST_TRIP_TYPEDEFS( long long, llint, long long, llint, long long, llint );
UNIT_TEST_TRIP_TYPEDEFS( double, double, int, int, long long, long_long );
UNIT_TEST_TRIP_TYPEDEFS( long long, llint, double, double, int, int );
UNIT_TEST_TRIP_TYPEDEFS( int, int, long long, llint, double, double );

UNIT_TEST_QUAD_TYPEDEFS( double, double, double, double, double, double, double, double );
UNIT_TEST_QUAD_TYPEDEFS( int, int, int, int, int, int, int, int );
UNIT_TEST_QUAD_TYPEDEFS( long long, llint, long long, llint, long long, llint, long long, llint );
UNIT_TEST_QUAD_TYPEDEFS( double, double, int, int, long long, llint, double, double );
UNIT_TEST_QUAD_TYPEDEFS( double, double, double, double, int, int, long long, llint );
UNIT_TEST_QUAD_TYPEDEFS( long long, llint, double, double, double, double, int, int );
UNIT_TEST_QUAD_TYPEDEFS( int, int, long long, llint, double, double, double, double );

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_PAIR_INSTANTIATION( type, name )      \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_float_float ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_double_double ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_char_char ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_int_int ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_uint_uint ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_lint_lint ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_ulint_ulint ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_llint_llint ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_double_int ); \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_int_double ); \

#define UNIT_TEST_INSTANTIATION( type, name )   \
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, utility_pair_double_double )
  //UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type, name, FIRST, std_tuple_double_double )
  
  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the value of the desired tuple member can be set and retrieved
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL( TupleMemberTraits,
                                                  get_set,
                                                  Member,
                                                  TupleType )
{
  TupleType tuple;

  typedef Utility::TupleMemberTraits<TupleType,Member> TMT;

  TMT::set( tuple, 1 );

  typename TMT::tupleMemberType& tuple_member_value = TMT::get( tuple );
    
  TEST_EQUALITY_CONST( tuple_member_value, 1 );

  // Check that a reference has been returned
  tuple_member_value = 2;

  TEST_EQUALITY_CONST( TMT::get( tuple ), 2 );

  // Check that a const tuple can be used
  const TupleType const_tuple = tuple;

  const typename TMT::tupleMemberType& const_tuple_member_value =
    TMT::get( const_tuple );

  TEST_EQUALITY_CONST( const_tuple_member_value, 2 );
}

UNIT_TEST_INSTANTIATION( TupleMemberTraits, get_set );

//---------------------------------------------------------------------------//
// Check that the standalone get/set methods can be used
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL( TupleMemberTraits,
                                                  standalone_get_set,
                                                  Member,
                                                  TupleType )
{
  TupleType tuple;

  Utility::set<Member>( tuple, 1 );

  typename Utility::TupleMemberTraits<TupleType,Member>::tupleMemberType&
    tuple_member_value = Utility::get<Member>( tuple );

  TEST_EQUALITY_CONST( tuple_member_value, 1 );

  // Check that a reference has been returned
  tuple_member_value = 2;

  TEST_EQUALITY_CONST( tuple_member_value, 2 );

  // Check that a const tuple can be used
  const TupleType const_tuple = tuple;

  const typename Utility::TupleMemberTraits<TupleType,Member>::tupleMemberType&
    const_tuple_member_value = Utility::get<Member>( const_tuple );

  TEST_EQUALITY_CONST( const_tuple_member_value, 2 );
}

UNIT_TEST_INSTANTIATION( TupleMemberTraits, standalone_get_set );

//---------------------------------------------------------------------------//
// end tstTupleMemberTraits.cpp
//---------------------------------------------------------------------------//
