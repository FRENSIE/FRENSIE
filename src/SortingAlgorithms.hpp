//---------------------------------------------------------------------------//
//!
//! \file   SortingAlgorithms
//! \author Alex Robinson
//! \brief  Sorting algorithm declarations.
//!
//---------------------------------------------------------------------------//

#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

// Std Lib Includes
#include <iterator>

// FACEMC Includes
#include "TupleMemberTraits.hpp"

namespace FACEMC{

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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "SortingAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SORTING_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end SortingAlgorithms.hpp
//---------------------------------------------------------------------------//
