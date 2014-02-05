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

// FACEMC Includes
#include "SearchAlgorithms.hpp"
#include "Tuple.hpp"
#include "TupleMemberTraits.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()					\
  typedef FACEMC::Pair<double,double> pair_d_d;			\
  typedef FACEMC::Pair<unsigned,double> pair_u_d;			\
  typedef FACEMC::Pair<double,unsigned> pair_d_u;			\
  typedef FACEMC::Trip<double,double,double> trip_d_d_d;		\
  typedef FACEMC::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef FACEMC::Trip<unsigned,double,unsigned> trip_u_d_u;		\
  typedef FACEMC::Trip<double,double,unsigned> trip_d_d_u;		\
  typedef FACEMC::Trip<unsigned,unsigned,double> trip_u_u_d;		\
  typedef FACEMC::Trip<double,unsigned,double> trip_d_u_d;		\
  typedef FACEMC::Trip<double,unsigned,unsigned> trip_d_u_u;		\
  typedef FACEMC::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef FACEMC::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  typedef FACEMC::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;	\
  typedef FACEMC::Quad<unsigned,double,double,double> quad_u_d_d_d;	\
  typedef FACEMC::Quad<double,double,double,unsigned> quad_d_d_d_u;	\
  typedef FACEMC::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;	\
  typedef FACEMC::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;	\
  typedef FACEMC::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;	\
  typedef FACEMC::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef FACEMC::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  typedef FACEMC::Quad<double,unsigned,double,unsigned> quad_d_u_d_u;	\
  typedef FACEMC::Quad<double,double,unsigned,double> quad_d_d_u_d;	\
  typedef FACEMC::Quad<unsigned,double,unsigned,unsigned> quad_u_d_u_u; \
  typedef FACEMC::Quad<double,unsigned,double,double> quad_d_u_d_d; \
  typedef FACEMC::Quad<unsigned,unsigned,double,unsigned> quad_u_u_d_u; \
  
#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )		\
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    pair_d_u,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    pair_u_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    trip_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    trip_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    trip_d_u_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    trip_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    trip_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    trip_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    trip_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    trip_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    trip_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    trip_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    trip_u_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    quad_d_d_u_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    quad_d_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_d_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_d_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_u_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_d_d_u_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_u_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_u_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_u_d_u_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_d_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_d_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_u_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_d_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_u_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_u_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_u_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_d_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_d_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_u_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_d_u_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_u_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_u_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_u_u_u_d, \
							    array )	\

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<FACEMC::TupleMember member, 
	 typename T, 
	 template<typename> class Array>
void fillArrayTupleMembersContinuousData( Array<T> &array )
{
  typedef typename FACEMC::Traits::TupleMemberTraits<T,member>::tupleMemberType
    tupleMemberType;
  
  typename Array<T>::size_type size = FACEMC::getArraySize( array );
  
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      FACEMC::set<member>( array[i], static_cast<tupleMemberType>( i ) );
    }
  }
}

template<FACEMC::TupleMember member, 
	 typename T, 
	 template<typename> class Array>
void fillArrayTupleMembersDiscreteData( Array<T> &array )
{
  typedef typename FACEMC::Traits::TupleMemberTraits<T,member>::tupleMemberType
    tupleMemberType;
  
  typename Array<T>::size_type size = FACEMC::getArraySize( array );
      
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      FACEMC::set<member>( array[i], static_cast<tupleMemberType>( i+1 )/size);
    }
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the binarySearchContinuousData function can search tuple elements
// correctly.
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( 
						Search,
						binarySearchContinuousData,
						member,
						type,
						array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersContinuousData<member>( raw_data );
 
  array<type> data;
  FACEMC::copyArrayView( data, raw_data() );

  typename array<type>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  double value, bin_value;

  // Value on first bin
  value = 0.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value on second bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value in third bin
  value = 2.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value on fourth bin
  value = 3.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 6.0 );
  
  // Value on eighth bin
  value = 7.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 7.0 );
  
  // Value in eighth bin
  value = 7.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 9.0 );
}

UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchContinuousData, Array );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchContinuousData, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchContinuousData, ArrayView );

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search tuple elements
// correctly.
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( Search,
						       binarySearchDiscreteData,
						       member,
						       type,
						       array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersDiscreteData<member>( raw_data );

  array<type> data;
  FACEMC::copyArrayView( data, raw_data() );

  typename array<type>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  double value, bin_value;

  // Value on first bin
  value = 0.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value in first bin
  value = 0.05;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value on second bin
  value = 0.1;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value in second bin
  value = 0.15;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.2 );

  // Value on third bin
  value = 0.2;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.2 );

  // Value in third bin
  value = 0.25;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.3 );

  // Value on fourth bin
  value = 0.3;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.3 );

  // Value in fourth bin
  value = 0.35;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								    end,
								    value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.4 );

  // Value on fifth bin
  value = 0.4;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.4 );

  // Value in fifth bin
  value = 0.45;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.5 );

  // Value on sixth bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.5 );

  // Value in sixth bin
  value = 0.55;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.6 );

  // Value on seventh bin
  value = 0.6;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.6 );

  // Value in seventh bin
  value = 0.65;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.7 );
  
  // Value on eighth bin
  value = 0.7;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.7 );
  
  // Value in eighth bin
  value = 0.75;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.8 );

  // Value on ninth bin
  value = 0.8;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.8 );

  // Value in ninth bin
  value = 0.85;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.9 );

  // Value on boundary
  value = 0.9;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.9 );

  // Value in tenth bin
  value = 0.95;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on boundary
  value = 10.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = FACEMC::get<member>( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 9.0 );
}

UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchDiscreteData, Array );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchDiscreteData, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchDiscreteData, ArrayView );

//---------------------------------------------------------------------------//
//end tstSearchAlgorithms.cpp
//---------------------------------------------------------------------------//

