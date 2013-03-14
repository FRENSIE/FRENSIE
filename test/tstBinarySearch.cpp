//---------------------------------------------------------------------------//
// \file   tstBinarySearch.cpp
// \author Alex Robinson
// \brief  Binary Search function unit tests.
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
#include "TupleGetSetMemberPolicy.hpp"
#include "TestingHelperFunctions.hpp"
#include "ArrayTestingPolicy.hpp"
#include "TupleTestingTypedefs.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )	\
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, pair_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, pair_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, pair_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, pair_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, trip_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, trip_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, trip_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, trip_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, trip_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, trip_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, trip_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, trip_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, trip_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, trip_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, trip_uint_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_uint_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FIRST, quad_double_uint_uint_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_double_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_double_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_double_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_uint_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_double_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_uint_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_uint_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, SECOND, quad_uint_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_double_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_double_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_double_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_uint_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_double_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_uint_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_uint_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, THIRD, quad_uint_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_double_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_double_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_double_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_uint_double_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_double_uint_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_uint_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_uint_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, FOURTH, quad_uint_uint_uint_double, array ) \

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<FACEMC::TupleMember member, typename T, template<typename> class Array>
void fillArrayTupleMembersContinuousData( Array<T> &array )
{
  typedef FACEMC::TupleGetSetMemberPolicy<T,member> localTGSMP;
  typename Array<T>::size_type size = 
    FACEMC::ArrayTestingPolicy<T,Array>::size( array );
  
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      localTGSMP::set( array[i], 
		       static_cast<typename localTGSMP::tupleMemberType>( i ) );
    }
  }
}

template<FACEMC::TupleMember member, typename T, template<typename> class Array>
void fillArrayTupleMembersDiscreteData( Array<T> &array )
{
  typedef FACEMC::TupleGetSetMemberPolicy<T,member> localTGSMP;
  typename Array<T>::size_type size = 
    FACEMC::ArrayTestingPolicy<T,Array>::size( array );
  
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      localTGSMP::set( array[i], 
		       static_cast<double>( i+1 )/size );
    }
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the binarySearchContinuousData function can search tuple elements
// correctly.
FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_DECL( 
						Search,
						binarySearchContinuousData,
						member,
						type,
						array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersContinuousData<member>( raw_data );
 
  array<type> data =
  FACEMC::ArrayTestingPolicy<type,array>::createArrayFromView( raw_data() );

  typename array<type>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  typedef FACEMC::TupleGetSetMemberPolicy<type,member> localTGSMP;
  double value, bin_value;

  // Value on first bin
  value = 0.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.0 );

  // Value on second bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value in third bin
  value = 2.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 2.0 );

  // Value on fourth bin
  value = 3.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 6.0 );
  
  // Value on eighth bin
  value = 7.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 7.0 );
  
  // Value in eighth bin
  value = 7.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 9.0 );
}

UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchContinuousData, Array );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchContinuousData, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchContinuousData, ArrayView );

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search tuple elements
// correctly.
FACEMC_UNIT_TEST_TUPLE_MEMBER_TEUCHOS_ARRAY_TEMPLATE_1_DECL( 
						Search,
						binarySearchDiscreteData,
						member,
						type,
						array )
{
  Teuchos::Array<type> raw_data( 10 );
  fillArrayTupleMembersDiscreteData<member>( raw_data );

  array<type> data =
    FACEMC::ArrayTestingPolicy<type,array>::createArrayFromView( raw_data() );

  typename array<type>::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  typedef FACEMC::TupleGetSetMemberPolicy<type,member> localTGSMP;
  double value, bin_value;

  // Value on first bin
  value = 0.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value in first bin
  value = 0.05;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value on second bin
  value = 0.1;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.1 );

  // Value in second bin
  value = 0.15;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.2 );

  // Value on third bin
  value = 0.2;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.2 );

  // Value in third bin
  value = 0.25;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.3 );

  // Value on fourth bin
  value = 0.3;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.3 );

  // Value in fourth bin
  value = 0.35;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								    end,
								    value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.4 );

  // Value on fifth bin
  value = 0.4;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.4 );

  // Value in fifth bin
  value = 0.45;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.5 );

  // Value on sixth bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.5 );

  // Value in sixth bin
  value = 0.55;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.6 );

  // Value on seventh bin
  value = 0.6;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.6 );

  // Value in seventh bin
  value = 0.65;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.7 );
  
  // Value on eighth bin
  value = 0.7;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.7 );
  
  // Value in eighth bin
  value = 0.75;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.8 );

  // Value on ninth bin
  value = 0.8;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.8 );

  // Value in ninth bin
  value = 0.85;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.9 );

  // Value on boundary
  value = 0.9;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 0.9 );

  // Value on boundary
  value = 0.95;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );

  // Value on boundary
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<member>( start,
								  end,
								  value );
  bin_value = localTGSMP::get( *lower_bound );
  TEST_EQUALITY_CONST( bin_value, 1.0 );
}

UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchDiscreteData, Array );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchDiscreteData, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( Search, binarySearchDiscreteData, ArrayView );

//---------------------------------------------------------------------------//
//end tstBinarySearch.cpp
//---------------------------------------------------------------------------//

