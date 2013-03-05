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
#include "BinarySearch.hpp"
#include "Tuple.hpp"

//---------------------------------------------------------------------------//
// Helper Functions
//---------------------------------------------------------------------------//
template<typename T, template<typename> class Array>
void fillArray( Array<T> &array, FACEMC::TupleMember member )
{
  unsigned int size = array.size();
  if( size > 0 )
  {
    for(unsigned int i = 0; i < size; ++i )
    {
      if( member == FACEMC::FIRST )
	array[i].first = i;
      else if( member == FACEMC::SECOND )
	array[i].second = i;
      else if( member == FACEMC::THIRD )
	array[i].third = i;
      else 
	array[i].third = i;
    }
  }
}


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the binarySearchContinuousData function can search the first
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchContinuous, search_array_first_tuple_members )
{
  Teuchos::Array<FACEMC::Trip<double,double,double> > data( 10 );
  
  fillArray( data, FACEMC::FIRST );

  Teuchos::Array<FACEMC::Trip<double,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  double value = 0.5;

  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>( 
								       start,
								       end,
								       value );

  TEST_EQUALITY_CONST( (*lower_bound).first, 0.0 );

}

//---------------------------------------------------------------------------//
//end tstBinarySearch.cpp
//---------------------------------------------------------------------------//

