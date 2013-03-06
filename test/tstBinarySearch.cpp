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
#include "TestingHelperFunctions.hpp"

//---------------------------------------------------------------------------//
// Helper Functions
//---------------------------------------------------------------------------//
template<typename T, template<typename> class Array>
void fillArrayFirstTupleMembers( Array<T> &array )
{
  unsigned int size = array.size();
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
      array[i].first = static_cast<typename T::firstType>(i);
  }
}

template<typename T, template<typename> class Array>
void fillArraySecondTupleMembers( Array<T> &array )
{
  unsigned int size = array.size();
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
      array[i].second = static_cast<typename T::secondType>(i);
  }
}

template<typename T, template<typename> class Array>
void fillArrayThirdTupleMembers( Array<T> &array )
{
  unsigned int size = array.size();
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
      array[i].third = static_cast<typename T::thirdType>(i);
  }
}

template<typename T, template<typename> class Array>
void fillArrayFourthTupleMembers( Array<T> &array )
{
  unsigned int size = array.size();
  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
      array[i].fourth = static_cast<typename T::fourthType>(i);
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

  fillArrayFirstTupleMembers( data );

  Teuchos::Array<FACEMC::Trip<double,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on first bin
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.0 );
  
  // Value in first bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.0 );
  
  // Value on second bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 2.0 );
  
  // Value in third bin
  value = 2.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 2.0 );
  
  // Value on fourth bin
  value = 3.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 6.0 );
  
  // Value on eighth bin
  value = 7.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 7.0 );
  
  // Value in eighth bin
  value = 7.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 9.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchContinuousData function can search the second
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchContinuous, search_array_second_tuple_members )
{
  Teuchos::Array<FACEMC::Trip<double,double,double> > data( 10 );

  fillArraySecondTupleMembers( data );

  Teuchos::Array<FACEMC::Trip<double,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on first bin
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.0 );
  
  // Value on second bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 2.0 );
  
  // Value in third bin
  value = 2.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 2.0 );
  
  // Value on fourth bin
  value = 3.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 6.0 );
  
  // Value on eighth bin
  value = 7.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 7.0 );
  
  // Value in eighth bin
  value = 7.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 9.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchContinuousData function can search the third
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchContinuous, search_array_third_tuple_members )
{
  Teuchos::Array<FACEMC::Trip<double,double,double> > data( 10 );

  fillArrayThirdTupleMembers( data );

  Teuchos::Array<FACEMC::Trip<double,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on first bin
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.0 );
  
  // Value on second bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 2.0 );
  
  // Value in third bin
  value = 2.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 2.0 );
  
  // Value on fourth bin
  value = 3.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 6.0 );
  
  // Value on eighth bin
  value = 7.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 7.0 );
  
  // Value in eighth bin
  value = 7.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 9.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search the fourth
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchContinuous, search_array_fourth_tuple_members )
{
  Teuchos::Array<FACEMC::Quad<double,double,double,double> > data( 10 );

  fillArrayFourthTupleMembers( data );
  
  Teuchos::Array<FACEMC::Quad<double,double,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on first bin
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.0 );

  // Value in first bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.0 );
  
  // Value on second bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 1.0 );

  // Value in second bin
  value = 1.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 1.0 );

  // Value on third bin
  value = 2.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 2.0 );
  
  // Value in third bin
  value = 2.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 2.0 );
  
  // Value on fourth bin
  value = 3.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 3.0 );

  // Value in fourth bin
  value = 3.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 3.0 );

  // Value on fifth bin
  value = 4.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 4.0 );

  // Value in fifth bin
  value = 4.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 4.0 );

  // Value on sixth bin
  value = 5.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 5.0 );

  // Value in sixth bin
  value = 5.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 5.0 );

  // Value on seventh bin
  value = 6.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 6.0 );

  // Value in seventh bin
  value = 6.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 6.0 );
  
  // Value on eighth bin
  value = 7.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 7.0 );
  
  // Value in eighth bin
  value = 7.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 7.0 );

  // Value on ninth bin
  value = 8.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 8.0 );

  // Value in ninth bin
  value = 8.5;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 8.0 );

  // Value on boundary
  value = 9.0;
  lower_bound = FACEMC::Search::binarySearchContinuousData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 9.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search the first
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchDiscrete, search_array_first_tuple_members )
{
  Teuchos::Array<FACEMC::Trip<double,double,double> > data( 11 );

  fillArrayFirstTupleMembers( data );
  data.erase( data.begin() );
  for( unsigned int i = 0; i < data.size(); ++i )
    data[i].first /= data.back().first;

  Teuchos::Array<FACEMC::Trip<double,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on boundry
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.1 );

  // Value in first bin
  value = 0.05;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.1 );
  
  // Value on first bin
  value = 0.1;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.1 );

  // Value in second bin
  value = 0.15;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.2 );

  // Value on second bin
  value = 0.2;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.2 );

  // Value in third bin
  value = 0.25;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.3 );

  // Value on third bin
  value = 0.3;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.3 );

  // Value in fourth bin
  value = 0.35;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.4 );

  // Value on fourth bin
  value = 0.4;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.4 );

  // Value in fifth bin
  value = 0.45;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.5 );

  // Value on fifth bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.5 );

  // Value in sixth bin
  value = 0.55;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.6 );

  // Value on sixth bin
  value = 0.6;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.6 );

  // Value in seventh bin
  value = 0.65;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.7 );

  // Value on seventh bin
  value = 0.70;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.7 );

  // Value in eighth bin
  value = 0.75;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.8 );

  // Value on eighth bin
  value = 0.80;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.8 );

  // Value in ninth bin
  value = 0.85;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.9 );

  // Value on ninth bin
  value = 0.90;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 0.9 );

  // Value in tenth bin
  value = 0.95;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 1.0 );

  // Value on tenth bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FIRST>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).first, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search the second
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchDiscrete, search_array_second_tuple_members )
{
  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data( 11 );

  fillArraySecondTupleMembers( data );
  data.erase( data.begin() );
  for( unsigned int i = 0; i < data.size(); ++i )
    data[i].second /= data.back().second;

  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on boundry
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.1 );

  // Value in first bin
  value = 0.05;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.1 );
  
  // Value on first bin
  value = 0.1;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.1 );

  // Value in second bin
  value = 0.15;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.2 );

  // Value on second bin
  value = 0.2;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.2 );

  // Value in third bin
  value = 0.25;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.3 );

  // Value on third bin
  value = 0.3;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.3 );

  // Value in fourth bin
  value = 0.35;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.4 );

  // Value on fourth bin
  value = 0.4;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.4 );

  // Value in fifth bin
  value = 0.45;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.5 );

  // Value on fifth bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.5 );

  // Value in sixth bin
  value = 0.55;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.6 );

  // Value on sixth bin
  value = 0.6;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.6 );

  // Value in seventh bin
  value = 0.65;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.7 );

  // Value on seventh bin
  value = 0.70;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.7 );

  // Value in eighth bin
  value = 0.75;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.8 );

  // Value on eighth bin
  value = 0.80;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.8 );

  // Value in ninth bin
  value = 0.85;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.9 );

  // Value on ninth bin
  value = 0.90;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 0.9 );

  // Value in tenth bin
  value = 0.95;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 1.0 );

  // Value on tenth bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::SECOND>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search the third
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchDiscrete, search_array_third_tuple_members )
{
  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data( 11 );

  fillArrayThirdTupleMembers( data );
  data.erase( data.begin() );
  for( unsigned int i = 0; i < data.size(); ++i )
    data[i].third /= data.back().third;

  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> >::iterator 
    start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on boundry
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.1 );

  // Value in first bin
  value = 0.05;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.1 );
  
  // Value on first bin
  value = 0.1;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.1 );

  // Value in second bin
  value = 0.15;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.2 );

  // Value on second bin
  value = 0.2;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.2 );

  // Value in third bin
  value = 0.25;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.3 );

  // Value on third bin
  value = 0.3;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.3 );

  // Value in fourth bin
  value = 0.35;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.4 );

  // Value on fourth bin
  value = 0.4;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.4 );

  // Value in fifth bin
  value = 0.45;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.5 );

  // Value on fifth bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.5 );

  // Value in sixth bin
  value = 0.55;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.6 );

  // Value on sixth bin
  value = 0.6;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.6 );

  // Value in seventh bin
  value = 0.65;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.7 );

  // Value on seventh bin
  value = 0.70;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.7 );

  // Value in eighth bin
  value = 0.75;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.8 );

  // Value on eighth bin
  value = 0.80;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.8 );

  // Value in ninth bin
  value = 0.85;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.9 );

  // Value on ninth bin
  value = 0.90;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 0.9 );

  // Value in tenth bin
  value = 0.95;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 1.0 );

  // Value on tenth bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::THIRD>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).third, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the binarySearchDiscreteData function can search the fourth
// tuple elements correctly
TEUCHOS_UNIT_TEST( BinarySearchDiscrete, search_array_fourth_tuple_members )
{
  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data( 11 );

  fillArrayFourthTupleMembers( data );
  data.erase( data.begin() );
  for( unsigned int i = 0; i < data.size(); ++i )
    data[i].fourth /= data.back().fourth;

  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> >::iterator start, end, lower_bound;
  start = data.begin();
  end = data.end();

  // Value on boundry
  double value = 0.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.1 );

  // Value in first bin
  value = 0.05;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.1 );
  
  // Value on first bin
  value = 0.1;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.1 );

  // Value in second bin
  value = 0.15;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.2 );

  // Value on second bin
  value = 0.2;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.2 );

  // Value in third bin
  value = 0.25;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.3 );

  // Value on third bin
  value = 0.3;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.3 );

  // Value in fourth bin
  value = 0.35;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.4 );

  // Value on fourth bin
  value = 0.4;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.4 );

  // Value in fifth bin
  value = 0.45;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.5 );

  // Value on fifth bin
  value = 0.5;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.5 );

  // Value in sixth bin
  value = 0.55;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.6 );

  // Value on sixth bin
  value = 0.6;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.6 );

  // Value in seventh bin
  value = 0.65;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.7 );

  // Value on seventh bin
  value = 0.70;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.7 );

  // Value in eighth bin
  value = 0.75;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.8 );

  // Value on eighth bin
  value = 0.80;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.8 );

  // Value in ninth bin
  value = 0.85;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.9 );

  // Value on ninth bin
  value = 0.90;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 0.9 );

  // Value in tenth bin
  value = 0.95;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 1.0 );

  // Value on tenth bin
  value = 1.0;
  lower_bound = FACEMC::Search::binarySearchDiscreteData<FACEMC::FOURTH>(
								       start,
								       end,
								       value );
  TEST_EQUALITY_CONST( (*lower_bound).fourth, 1.0 );
}

//---------------------------------------------------------------------------//
//end tstBinarySearch.cpp
//---------------------------------------------------------------------------//

