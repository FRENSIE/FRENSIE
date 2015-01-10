//---------------------------------------------------------------------------//
//!
//! \file   Utility_SortAlgorithms.hpp
//! \author Alex Robinson
//! \brief  Sorting algorithm declarations.
//!
//---------------------------------------------------------------------------//
  
#ifndef UTILITY_SORT_ALGORITHMS_HPP
#define UTILITY_SORT_ALGORITHMS_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_TupleMemberTraits.hpp"

namespace Utility{

namespace Sort{

/*! Test if the specified member of an array of tuples is sorted in ascending 
 * order
 */
template<TupleMember member, typename Iterator>
bool isSortedAscending( Iterator start, Iterator end );

//! Test if an array is sorted in ascending order
template<typename Iterator>
bool isSortedAscending( Iterator start, Iterator end );	        

} // end Sort namespace

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_SortAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SORT_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end Utility_SortAlgorithms.hpp
//---------------------------------------------------------------------------//
