//---------------------------------------------------------------------------//
//!
//! \file   tstSearchAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Search function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()					\
  typedef Utility::Pair<double,double> pair_d_d;			\
  typedef Utility::Pair<unsigned,double> pair_u_d;			\
  typedef Utility::Pair<double,unsigned> pair_d_u;			\
  typedef Utility::Trip<double,double,double> trip_d_d_d;		\
  typedef Utility::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef Utility::Trip<unsigned,double,unsigned> trip_u_d_u;		\
  typedef Utility::Trip<double,double,unsigned> trip_d_d_u;		\
  typedef Utility::Trip<unsigned,unsigned,double> trip_u_u_d;		\
  typedef Utility::Trip<double,unsigned,double> trip_d_u_d;		\
  typedef Utility::Trip<double,unsigned,unsigned> trip_d_u_u;		\
  typedef Utility::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef Utility::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  typedef Utility::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;	\
  typedef Utility::Quad<unsigned,double,double,double> quad_u_d_d_d;	\
  typedef Utility::Quad<double,double,double,unsigned> quad_d_d_d_u;	\
  typedef Utility::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;	\
  typedef Utility::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;	\
  typedef Utility::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;	\
  typedef Utility::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef Utility::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  typedef Utility::Quad<double,unsigned,double,unsigned> quad_d_u_d_u;	\
  typedef Utility::Quad<double,double,unsigned,double> quad_d_d_u_d;	\
  typedef Utility::Quad<unsigned,double,unsigned,unsigned> quad_u_d_u_u; \
  typedef Utility::Quad<double,unsigned,double,double> quad_d_u_d_d; \
  typedef Utility::Quad<unsigned,unsigned,double,unsigned> quad_u_u_d_u; \

#define UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( type, name, array )	\
  TUPLE_TYPEDEFS()							\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     FIRST,	\
							     pair_d_d,	\
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     SECOND,	\
							     pair_d_d,	\
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     FIRST,	\
							     trip_d_d_d, \
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     SECOND,	\
							     trip_d_d_d, \
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     THIRD,	\
							     trip_d_d_d, \
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     FIRST,	\
							     quad_d_d_d_d, \
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     SECOND,	\
							     quad_d_d_d_d, \
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     THIRD,	\
							     quad_d_d_d_d, \
							     array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							     name,	\
							     FOURTH,	\
							     quad_d_d_d_d, \
							     array )	\

#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )		\
  UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT( type,		\
						   name,		\
						   double,		\
						   array )		\
  UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT( type,		\
						   name,		\
						   unsigned,		\
						   array )

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<Utility::TupleMember member,
	 typename T,
	 template<typename> class Array>
void fillArrayTupleMembersContinuousData( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  typename Array<T>::size_type size = Utility::getArraySize( array );

  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      Utility::set<member>( array[i], static_cast<tupleMemberType>( i ) );
    }
  }
}

template<Utility::TupleMember member,
	 typename T,
	 template<typename> class Array>
void fillArrayTupleMembersDiscreteData( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  typename Array<T>::size_type size = Utility::getArraySize( array );

  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      Utility::set<member>( array[i], static_cast<tupleMemberType>( i+1 )/size);
    }
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the binaryLowerBound function can search tuple elements
// correctly.
UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( Search,
					      binaryLowerBound,
					      type,
					      array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersContinuousData<Utility::FIRST>( raw_data );

  array<type> data;
  Utility::copyArrayView( data, raw_data() );

  typename array<type>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  double value, bin_value;

  // Value on first bin
  value = 0.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value on second bin
  value = 1.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value in third bin
  value = 2.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value on fourth bin
  value = 3.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 6.0 );

  // Value on eighth bin
  value = 7.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 7.0 );

  // Value in eighth bin
  value = 7.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 9.0 );
}

UNIT_TEST_INSTANTIATION_ARRAY( Search, binaryLowerBound, Array );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binaryLowerBound, ArrayRCP );

//---------------------------------------------------------------------------//
// Check that the binaryLowerBound function can search tuple elements
// correctly.
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL(
					      Search,
					      binaryLowerBound_tuple,
					      member,
					      type,
					      array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersContinuousData<member>( raw_data );

  array<type> data;
  Utility::copyArrayView( data, raw_data() );

  typename array<type>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  double value, bin_value;

  // Value on first bin
  value = 0.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value on second bin
  value = 1.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value in third bin
  value = 2.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value on fourth bin
  value = 3.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 6.0 );

  // Value on eighth bin
  value = 7.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 7.0 );

  // Value in eighth bin
  value = 7.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = Utility::Search::binaryLowerBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 9.0 );
}

UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Search,
				     binaryLowerBound_tuple,
				     Array );
UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Search,
				     binaryLowerBound_tuple,
				     ArrayRCP );

//---------------------------------------------------------------------------//
// Check that the binaryLowerBoundIndex function can search tuple elements
// correctly.
UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( Search,
					      binaryLowerBoundIndex,
					      type,
					      array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersContinuousData<Utility::FIRST>( raw_data );

  array<type> data;
  Utility::copyArrayView( data, raw_data() );

  typename array<type>::iterator start, end;
  start = data.begin();
  end = data.end();

  double value;
  unsigned lower_bin_index;

  // first bin index
  value = 0.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 0 );

  // Value in first bin
  value = 0.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 0 );

  // Value on second bin
  value = 1.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 1 );

  // Value in second bin
  value = 1.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 1 );

  // Value on third bin
  value = 2.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 2 );

  // Value in third bin
  value = 2.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 2 );

  // Value on fourth bin
  value = 3.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 3 );

  // Value in fourth bin
  value = 3.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 3 );

  // Value on fifth bin
  value = 4.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 4 );

  // Value in fifth bin
  value = 4.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 4 );

  // Value on sixth bin
  value = 5.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 5 );

  // Value in sixth bin
  value = 5.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 5 );

  // Value on seventh bin
  value = 6.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 6 );

  // Value in seventh bin
  value = 6.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 6 );

  // Value on eighth bin
  value = 7.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 7 );

  // Value in eighth bin
  value = 7.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 7 );

  // Value on ninth bin
  value = 8.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 8 );

  // Value in ninth bin
  value = 8.5;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 8 );

  // Value on boundary
  value = 9.0;
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( lower_bin_index, 9 );
}

UNIT_TEST_INSTANTIATION_ARRAY( Search, binaryLowerBoundIndex, Array );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binaryLowerBoundIndex, ArrayRCP );

//---------------------------------------------------------------------------//
// Check that the binaryUpperBound function can search an array of
// doubles correctly
TEUCHOS_UNIT_TEST( Search, binaryUpperBound_unsigned )
{
  Teuchos::Array<unsigned> data( 10 );

  // Use continuous data so that values are all integers
  fillArrayTupleMembersContinuousData<Utility::FIRST>( data );

  typename Teuchos::Array<unsigned>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  unsigned value, bin_value;

  // Value on first bin
  value = 0u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 0u );

  // Value on second bin
  value = 1u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 1u );

  // Value on third bin
  value = 3u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 3u );

  // Value on fourth bin
  value = 4u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 4u );

  // Value on fifth bin
  value = 5u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 5u );

  // Value on sixth bin
  value = 6u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 6u );

  // Value on seventh bin
  value = 7u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 7u );

  // Value in eighth bin
  value = 8u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 8u );

  // Value on nineth bin
  value = 9u;
  lower_bound = Utility::Search::binaryUpperBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  TEST_EQUALITY_CONST( bin_value, 9u );
}

//---------------------------------------------------------------------------//
// Check that the binaryUpperBound function can search tuple elements
// correctly.
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL(
					        Search,
						binaryUpperBound_tuple,
						member,
						type,
						array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersDiscreteData<member>( raw_data );

  array<type> data;
  Utility::copyArrayView( data, raw_data() );

  typename array<type>::iterator start, end, upper_bound;
  start = data.begin();
  end = data.end();

  double value, bin_value;

  // Value on first bin
  value = 0.0;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value in first bin
  value = 0.05;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value on second bin
  value = 0.1;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value in second bin
  value = 0.15;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.2 );

  // Value on third bin
  value = 0.2;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.2 );

  // Value in third bin
  value = 0.25;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.3 );

  // Value on fourth bin
  value = 0.3;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.3 );

  // Value in fourth bin
  value = 0.35;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.4 );

  // Value on fifth bin
  value = 0.4;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.4 );

  // Value in fifth bin
  value = 0.45;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.5 );

  // Value on sixth bin
  value = 0.5;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.5 );

  // Value in sixth bin
  value = 0.55;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.6 );

  // Value on seventh bin
  value = 0.6;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.6 );

  // Value in seventh bin
  value = 0.65;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.7 );

  // Value on eighth bin
  value = 0.7;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.7 );

  // Value in eighth bin
  value = 0.75;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.8 );

  // Value on ninth bin
  value = 0.8;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.8 );

  // Value in ninth bin
  value = 0.85;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.9 );

  // Value on boundary
  value = 0.9;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 0.9 );

  // Value in tenth bin
  value = 0.95;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on boundary
  value = 1.0;
  upper_bound = Utility::Search::binaryUpperBound<member>( start,
							   end,
							   value );
  bin_value = Utility::get<member>( *upper_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );
}

UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Search,
				     binaryUpperBound_tuple,
				     Array );
UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Search,
				     binaryUpperBound_tuple,
				     ArrayRCP );

//---------------------------------------------------------------------------//
// Check that the binaryUpperBoundIndex function can search an array of
// doubles correctly
TEUCHOS_UNIT_TEST( Search, binaryUpperBoundIndex_unsigned )
{
  Teuchos::Array<unsigned> data( 10 );

  // Use continuous data so that values are all integers
  fillArrayTupleMembersContinuousData<Utility::FIRST>( data );

  typename Teuchos::Array<unsigned>::iterator start, end;
  start = data.begin();
  end = data.end();

  unsigned value, upper_bin_index;

  // Value on first bin
  value = 0u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 0u );

  // Value on second bin
  value = 1u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 1u );

  // Value on third bin
  value = 3u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 3u );

  // Value on fourth bin
  value = 4u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 4u );

  // Value on fifth bin
  value = 5u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 5u );

  // Value on sixth bin
  value = 6u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 6u );

  // Value on seventh bin
  value = 7u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 7u );

  // Value in eighth bin
  value = 8u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 8u );

  // Value on nineth bin
  value = 9u;
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start,
							    end,
							    value );
  TEST_EQUALITY_CONST( upper_bin_index, 9u );
}

//---------------------------------------------------------------------------//
//end tstSearchAlgorithms.cpp
//---------------------------------------------------------------------------//

