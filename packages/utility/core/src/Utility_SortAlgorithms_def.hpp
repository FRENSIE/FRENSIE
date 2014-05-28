//---------------------------------------------------------------------------//
//!
//! \file   Utility_SortAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Sort algorithms definitions.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SORT_ALGORITHMS_DEF_HPP
#define UTILITY_SORT_ALGORITHMS_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

namespace Sort{

// Test if the specified member of an array of tuples is sorted in ascending o.
/*! \details This function is nominally the same as the function in algorithms
 * of the new C++ 2011 standard library. When the transition to the 2011
 * standard is made, this function should be removed. The time complexity is 
 * linear in the number of elements in the container.
 */
template<TupleMember member, typename Iterator>
bool isSortedAscending( Iterator start, Iterator end )
{
  // Make sure the container is not empty
  testPrecondition( start != end );
  
  Iterator element_a = start;
  Iterator element_b = element_a;
  ++element_b;

  bool is_sorted = true;

  while( element_b != end )
  {
    if( get<member>( *element_a ) > get<member>( *element_b ) )
    {
      is_sorted = false;
      break;
    }

    ++element_a;
    ++element_b;
  }
  
  return is_sorted;
}

// Test if an array is sorted in ascending order
template<typename Iterator>
inline bool isSortedAscending( Iterator start, Iterator end )
{
  return isSortedAscending<FIRST>( start, end );
}

} // end Sort namespace

} // end Utility namespace

#endif // end UTILITY_SORT_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// Utility_SortAlgorithms_def.hpp
//---------------------------------------------------------------------------//
