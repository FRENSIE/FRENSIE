//---------------------------------------------------------------------------//
//!
//! \file   SearchAlgorithms.hpp
//! \author Alex Robinson
//! \brief  Functions declarations for searching algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

// Std Lib Includes
#include <iterator>

// FACEMC Includes
#include "TupleMemberTraits.hpp"

namespace FACEMC{

namespace Search{

//! Binary search on a container of and return the lower bound iterator
template<TupleMember member, typename Iterator>
Iterator binaryLowerBound( Iterator start,
			   Iterator end,
			   const typename Traits::TupleMemberTraits<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value );

//! Binary search on a container of and return the lower bound iterator
template<typename Iterator>
Iterator binaryLowerBound( Iterator start,
			   Iterator end,
			   const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the lower bound container index
template<TupleMember member, typename Iterator>
typename std::iterator_traits<Iterator>::difference_type  
binaryLowerBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the lower bound container index
template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type  
binaryLowerBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the upper bound iterator
template<TupleMember member, typename Iterator>
Iterator binaryUpperBound( Iterator start,
			   Iterator end,
			   const typename Traits::TupleMemberTraits<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value);

//! Binary search on a container and return the upper bound iterator
template<typename Iterator>
Iterator binaryUpperBound( Iterator start,
			   Iterator end,
			   const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the upper bound container index
template<TupleMember member, typename Iterator>
typename std::iterator_traits<Iterator>::difference_type  
binaryUpperBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the upper bound container index
template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type  
binaryUpperBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value );

} // end Search namespace

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "SearchAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SEARCH_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end SearchAlgorithms.hpp
//---------------------------------------------------------------------------//

