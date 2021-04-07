//---------------------------------------------------------------------------//
//!
//! \file   tstSearchAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Search function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Typedefs
//---------------------------------------------------------------------------//
typedef std::tuple<std::tuple<std::integral_constant<size_t,0>,unsigned>,
                   std::tuple<std::integral_constant<size_t,0>,double>,
                   std::tuple<std::integral_constant<size_t,0>,std::pair<double,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::tuple<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::tuple<double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,0>,std::tuple<double,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::tuple<double,unsigned,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,1>,std::pair<double,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<double,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<double,unsigned,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,2>,std::tuple<double,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::tuple<double,unsigned,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,3>,std::tuple<double,unsigned,double,unsigned> > > TupleMemberTypes;

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<size_t member,
	 typename T,
	 template<typename,typename...> class Array>
void fillArrayTupleMembersContinuousData( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  if( array.size() > 0 )
  {
    for( size_t i = 0; i < array.size(); ++i )
    {
      Utility::get<member>( array[i] ) = static_cast<tupleMemberType>( i*2 );
    }
  }
}

template<size_t member,
	 typename T,
	 template<typename,typename...> class Array>
void fillArrayTupleMembersDiscreteData( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  if( array.size() > 0 )
  {
    for( size_t i = 0; i < array.size(); ++i )
    {
      Utility::get<member>( array[i] ) =
        static_cast<tupleMemberType>( (i+1)*2 );
    }
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the binaryLowerBound function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE( Search,
                            binaryLowerBound_basic,
                            float, double, int, unsigned )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::vector<T> data( 10 );
  fillArrayTupleMembersContinuousData<0>( data );

  typename std::vector<T>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  T value, bin_value;

  // Value on first bin
  value = T(0);
  lower_bound = Utility::Search::binaryLowerBound( start, end, value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(0) );

  // Value in first bin
  value = T(1);
  lower_bound = Utility::Search::binaryLowerBound( start, end, value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(0) );

  // Value on second bin
  value = T(2);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value in second bin
  value = T(3);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value on third bin
  value = T(4);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value in third bin
  value = T(5);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value on fourth bin
  value = T(6);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value in fourth bin
  value = T(7);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value on fifth bin
  value = T(8);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value in fifth bin
  value = T(9);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value on sixth bin
  value = T(10);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value in sixth bin
  value = T(11);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value on seventh bin
  value = T(12);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value in seventh bin
  value = T(13);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value on eighth bin
  value = T(14);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value in eighth bin
  value = T(15);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value on ninth bin
  value = T(16);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value in ninth bin
  value = T(17);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value on boundary
  value = T(18);
  lower_bound = Utility::Search::binaryLowerBound( start,
						   end,
						   value );
  bin_value = *lower_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(18) );
}

//---------------------------------------------------------------------------//
// Check that the binaryLowerBound function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Search, binaryLowerBound, TupleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, TupleMemberIndex );
  FETCH_TEMPLATE_PARAM( 1, TupleType );
  typedef typename Utility::TupleElement<TupleMemberIndex::value,TupleType>::type T;
  
  std::vector<TupleType> data( 10 );
  fillArrayTupleMembersContinuousData<TupleMemberIndex::value>( data );

  typename std::vector<TupleType>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  T value, bin_value;

  // Value on first bin
  value = T(0);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(0) );

  // Value in first bin
  value = T(1);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(0) );

  // Value on second bin
  value = T(2);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value in second bin
  value = T(3);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value on third bin
  value = T(4);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value in third bin
  value = T(5);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value on fourth bin
  value = T(6);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value in fourth bin
  value = T(7);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value on fifth bin
  value = T(8);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value in fifth bin
  value = T(9);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value on sixth bin
  value = T(10);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value in sixth bin
  value = T(11);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value on seventh bin
  value = T(12);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value in seventh bin
  value = T(13);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value on eighth bin
  value = T(14);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value in eighth bin
  value = T(15);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value on ninth bin
  value = T(16);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value in ninth bin
  value = T(17);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value on boundary
  value = T(18);
  lower_bound = Utility::Search::binaryLowerBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *lower_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(18) );
}

//---------------------------------------------------------------------------//
// Check that the binaryLowerBoundIndex function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE( Search, binaryLowerBoundIndex_basic,
                            float, double, int, unsigned )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::vector<T> data( 10 );
  fillArrayTupleMembersContinuousData<0>( data );

  typename std::vector<T>::iterator start, end;
  start = data.begin();
  end = data.end();

  T value;
  typename std::iterator_traits<decltype(start)>::difference_type lower_bin_index;

  // first bin index
  value = T(0);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 0 );

  // Value in first bin
  value = T(1);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 0 );

  // Value on second bin
  value = T(2);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 1 );

  // Value in second bin
  value = T(3);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 1 );

  // Value on third bin
  value = T(4);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 2 );

  // Value in third bin
  value = T(5);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 2 );

  // Value on fourth bin
  value = T(6);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 3 );

  // Value in fourth bin
  value = T(7);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 3 );

  // Value on fifth bin
  value = T(8);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 4 );

  // Value in fifth bin
  value = T(9);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 4 );

  // Value on sixth bin
  value = T(10);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 5 );

  // Value in sixth bin
  value = T(11);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 5 );

  // Value on seventh bin
  value = T(12);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 6 );

  // Value in seventh bin
  value = T(13);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 6 );

  // Value on eighth bin
  value = T(14);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 7 );

  // Value in eighth bin
  value = T(15);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 7 );

  // Value on ninth bin
  value = T(16);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 8 );

  // Value in ninth bin
  value = T(17);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 8 );

  // Value on boundary
  value = T(18);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 9 );
}

//---------------------------------------------------------------------------//
// Check that the binaryLowerBoundIndex function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Search, binaryLowerBoundIndex, TupleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, TupleMemberIndex );
  FETCH_TEMPLATE_PARAM( 1, TupleType );
  typedef typename Utility::TupleElement<TupleMemberIndex::value,TupleType>::type T;
  
  std::vector<TupleType> data( 10 );
  fillArrayTupleMembersContinuousData<TupleMemberIndex::value>( data );

  typename std::vector<TupleType>::iterator start, end;
  start = data.begin();
  end = data.end();

  T value;
  typename std::iterator_traits<decltype(start)>::difference_type lower_bin_index;

  // first bin index
  value = T(0);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 0 );

  // Value in first bin
  value = T(1);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 0 );

  // Value on second bin
  value = T(2);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 1 );

  // Value in second bin
  value = T(3);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 1 );

  // Value on third bin
  value = T(4);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 2 );

  // Value in third bin
  value = T(5);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 2 );

  // Value on fourth bin
  value = T(6);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 3 );

  // Value in fourth bin
  value = T(7);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 3 );

  // Value on fifth bin
  value = T(8);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 4 );

  // Value in fifth bin
  value = T(9);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 4 );

  // Value on sixth bin
  value = T(10);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 5 );

  // Value in sixth bin
  value = T(11);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 5 );

  // Value on seventh bin
  value = T(12);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 6 );

  // Value in seventh bin
  value = T(13);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 6 );

  // Value on eighth bin
  value = T(14);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 7 );

  // Value in eighth bin
  value = T(15);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 7 );

  // Value on ninth bin
  value = T(16);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 8 );

  // Value in ninth bin
  value = T(17);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 8 );

  // Value on boundary
  value = T(18);
  lower_bin_index = Utility::Search::binaryLowerBoundIndex<TupleMemberIndex::value>( start,
							    end,
							    value );
  FRENSIE_CHECK_EQUAL( lower_bin_index, 9 );
}

//---------------------------------------------------------------------------//
// Check that the binaryUpperBound function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE( Search, binaryUpperBound_basic,
                            float, double, int, unsigned )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::vector<T> data( 10 );
  fillArrayTupleMembersDiscreteData<0>( data );

  typename std::vector<T>::iterator start, end, upper_bound;
  start = data.begin();
  end = data.end();

  T value, bin_value;

  // Value in first bin
  value = T(0);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value in first bin
  value = T(1);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value on second bin
  value = T(2);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value in second bin
  value = T(3);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value on third bin
  value = T(4);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value in third bin
  value = T(5);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value on fourth bin
  value = T(6);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value in fourth bin
  value = T(7);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value on fifth bin
  value = T(8);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value in fifth bin
  value = T(9);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value on sixth bin
  value = T(10);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value in sixth bin
  value = T(11);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value on seventh bin
  value = T(12);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value in seventh bin
  value = T(13);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value on eighth bin
  value = T(14);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value in eighth bin
  value = T(15);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value on ninth bin
  value = T(16);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value in ninth bin
  value = T(17);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(18) );

  // Value on boundary
  value = T(18);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(18) );

  // Value in tenth bin
  value = T(19);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(20) );

  // Value on boundary
  value = T(20);
  upper_bound = Utility::Search::binaryUpperBound( start, end, value );
  bin_value = *upper_bound;
  FRENSIE_CHECK_EQUAL( bin_value, T(20) );
}

//---------------------------------------------------------------------------//
// Check that the binaryUpperBound function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Search, binaryUpperBound, TupleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, TupleMemberIndex );
  FETCH_TEMPLATE_PARAM( 1, TupleType );
  typedef typename Utility::TupleElement<TupleMemberIndex::value,TupleType>::type T;
  
  std::vector<TupleType> data( 10 );
  fillArrayTupleMembersDiscreteData<TupleMemberIndex::value>( data );

  typename std::vector<TupleType>::iterator start, end, upper_bound;
  start = data.begin();
  end = data.end();

  T value, bin_value;

  // Value in first bin
  value = T(0);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value in first bin
  value = T(1);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value on second bin
  value = T(2);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(2) );

  // Value in second bin
  value = T(3);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value on third bin
  value = T(4);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(4) );

  // Value in third bin
  value = T(5);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value on fourth bin
  value = T(6);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(6) );

  // Value in fourth bin
  value = T(7);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value on fifth bin
  value = T(8);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(8) );

  // Value in fifth bin
  value = T(9);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value on sixth bin
  value = T(10);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(10) );

  // Value in sixth bin
  value = T(11);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value on seventh bin
  value = T(12);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(12) );

  // Value in seventh bin
  value = T(13);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value on eighth bin
  value = T(14);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(14) );

  // Value in eighth bin
  value = T(15);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value on ninth bin
  value = T(16);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(16) );

  // Value in ninth bin
  value = T(17);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(18) );

  // Value on boundary
  value = T(18);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(18) );

  // Value in tenth bin
  value = T(19);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(20) );

  // Value on boundary
  value = T(20);
  upper_bound = Utility::Search::binaryUpperBound<TupleMemberIndex::value>( start,
							   end,
							   value );
  bin_value = Utility::get<TupleMemberIndex::value>( *upper_bound );
  FRENSIE_CHECK_EQUAL( bin_value, T(20) );
}

//---------------------------------------------------------------------------//
// Check that the binaryUpperBound function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE( Search, binaryUpperBoundIndex_basic,
                            float, double, int, unsigned )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::vector<T> data( 10 );
  fillArrayTupleMembersDiscreteData<0>( data );

  typename std::vector<T>::iterator start, end;
  start = data.begin();
  end = data.end();

  T value;
  typename std::iterator_traits<decltype(start)>::difference_type upper_bin_index;

  // Value in first bin
  value = T(0);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 0 );

  // Value in first bin
  value = T(1);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 0 );

  // Value on second bin
  value = T(2);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 0 );

  // Value in second bin
  value = T(3);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 1 );

  // Value on third bin
  value = T(4);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 1 );

  // Value in third bin
  value = T(5);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 2 );

  // Value on fourth bin
  value = T(6);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 2 );

  // Value in fourth bin
  value = T(7);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 3 );

  // Value on fifth bin
  value = T(8);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 3 );

  // Value in fifth bin
  value = T(9);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 4 );

  // Value on sixth bin
  value = T(10);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 4 );

  // Value in sixth bin
  value = T(11);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 5 );

  // Value on seventh bin
  value = T(12);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 5 );

  // Value in seventh bin
  value = T(13);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 6 );

  // Value on eighth bin
  value = T(14);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 6 );

  // Value in eighth bin
  value = T(15);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 7 );

  // Value on ninth bin
  value = T(16);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 7 );

  // Value in ninth bin
  value = T(17);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 8 );

  // Value on boundary
  value = T(18);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 8 );

  // Value in tenth bin
  value = T(19);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 9 );

  // Value on boundary
  value = T(20);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 9 );
}

//---------------------------------------------------------------------------//
// Check that the binaryUpperBound function can search tuple elements
// correctly.
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Search, binaryUpperBoundIndex, TupleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, TupleMemberIndex );
  FETCH_TEMPLATE_PARAM( 1, TupleType );
  typedef typename Utility::TupleElement<TupleMemberIndex::value,TupleType>::type T;
  
  std::vector<TupleType> data( 10 );
  fillArrayTupleMembersDiscreteData<TupleMemberIndex::value>( data );

  typename std::vector<TupleType>::iterator start, end;
  start = data.begin();
  end = data.end();

  T value;
  typename std::iterator_traits<decltype(start)>::difference_type upper_bin_index;

  // Value in first bin
  value = T(0);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 0 );

  // Value in first bin
  value = T(1);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 0 );

  // Value on second bin
  value = T(2);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 0 );

  // Value in second bin
  value = T(3);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 1 );

  // Value on third bin
  value = T(4);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 1 );

  // Value in third bin
  value = T(5);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 2 );

  // Value on fourth bin
  value = T(6);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 2 );

  // Value in fourth bin
  value = T(7);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 3 );

  // Value on fifth bin
  value = T(8);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 3 );

  // Value in fifth bin
  value = T(9);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 4 );

  // Value on sixth bin
  value = T(10);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 4 );

  // Value in sixth bin
  value = T(11);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 5 );

  // Value on seventh bin
  value = T(12);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 5 );

  // Value in seventh bin
  value = T(13);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 6 );

  // Value on eighth bin
  value = T(14);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 6 );

  // Value in eighth bin
  value = T(15);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 7 );

  // Value on ninth bin
  value = T(16);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 7 );

  // Value in ninth bin
  value = T(17);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 8 );

  // Value on boundary
  value = T(18);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 8 );

  // Value in tenth bin
  value = T(19);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 9 );

  // Value on boundary
  value = T(20);
  upper_bin_index = Utility::Search::binaryUpperBoundIndex<TupleMemberIndex::value>( start, end, value );
  FRENSIE_CHECK_EQUAL( upper_bin_index, 9 );
}

//---------------------------------------------------------------------------//
//end tstSearchAlgorithms.cpp
//---------------------------------------------------------------------------//

