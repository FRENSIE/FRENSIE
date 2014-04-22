//---------------------------------------------------------------------------//
//!
//! \file   SortAlgorithms
//! \author Alex Robinson
//! \brief  Sorting algorithm declarations.
//!
//---------------------------------------------------------------------------//

#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP

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

#include "SortAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SORT_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end SortAlgorithms.hpp
//---------------------------------------------------------------------------//
