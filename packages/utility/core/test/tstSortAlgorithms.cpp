//---------------------------------------------------------------------------//
//!
//! \file   tstSortAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Sort function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
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
void fillSortedArray( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  if( array.size() > 0 )
  {
    for( size_t i = 0; i < array.size(); ++i )
      Utility::get<member>( array[i] ) = static_cast<tupleMemberType>( i );
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a sorted array can be checked
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Sort, isSortedAscending, TupleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, TupleMemberIndex );
  FETCH_TEMPLATE_PARAM( 1, TupleType );
  
  std::vector<TupleType> data( 10 );
  fillSortedArray<TupleMemberIndex::value>( data );

  FRENSIE_CHECK( Utility::Sort::isSortedAscending<TupleMemberIndex::value>(
                                                  data.begin(), data.end() ) );

  // Unsort the array
  Utility::get<TupleMemberIndex::value>( data[0] ) = 10;

  FRENSIE_CHECK( !Utility::Sort::isSortedAscending<TupleMemberIndex::value>(
                                                  data.begin(), data.end() ) );

}

//---------------------------------------------------------------------------//
// end tstSortAlgorithms.cpp
//---------------------------------------------------------------------------//
