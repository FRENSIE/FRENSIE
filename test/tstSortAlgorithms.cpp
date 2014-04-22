//---------------------------------------------------------------------------//
//!
//! \file   tstSortAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Sort function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FACEMC Includes
#include "SortAlgorithms.hpp"
#include "Tuple.hpp"
#include "TupleMemberTraits.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()			\
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
  
#define UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( type, name, array )	\
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    trip_d_u_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    trip_d_u_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    trip_d_u_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    quad_d_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_d_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_d_u_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_d_u_d_u, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )		\
  FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT( type, name, double, array ) \
  FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT( type, name, unsigned, array )


//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<FACEMC::TupleMember member, 
	 typename T, 
	 template<typename> class Array>
void fillSortedArray( Array<T> &array )
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

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a sorted array can be checked
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( Sort,
					     isSortedAscending,
					     type,
					     array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillSortedArray<FACEMC::FIRST>( raw_data );

  array<type> data;
  FACEMC::copyArrayView( data, raw_data() );

  TEST_ASSERT( FACEMC::Sort::isSortedAscending( data.begin(), 
						data.end() ) );

  // Unsort the array
  data[0] = 10.0;

  TEST_ASSERT( !FACEMC::Sort::isSortedAscending( data.begin(), 
						 data.end() ) );

}

UNIT_TEST_INSTANTIATION_ARRAY( Sort,
			       isSortedAscending,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( Sort,
			       isSortedAscending,
			       ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( Sort,
			       isSortedAscending,
			       ArrayView );

//---------------------------------------------------------------------------//
// Check that a sorted array can be checked
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( Sort,
						       isSortedAscending_tuple,
						       member,
						       type,
						       array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillSortedArray<member>( raw_data );

  array<type> data;
  FACEMC::copyArrayView( data, raw_data() );

  TEST_ASSERT( FACEMC::Sort::isSortedAscending<member>( data.begin(), 
							data.end() ) );

  // Unsort the array
  FACEMC::set<member>( data[0], 10.0 );

  TEST_ASSERT( !FACEMC::Sort::isSortedAscending<member>( data.begin(), 
							 data.end() ) );

}

UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Sort,
				     isSortedAscending_tuple,
				     Array );
UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Sort,
				     isSortedAscending_tuple,
				     ArrayRCP );
UNIT_TEST_INSTANTIATION_TUPLE_ARRAY( Sort,
				     isSortedAscending_tuple,
				     ArrayView );

//---------------------------------------------------------------------------//
// end tstSortAlgorithms.cpp
//---------------------------------------------------------------------------//
