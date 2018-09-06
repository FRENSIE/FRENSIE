//---------------------------------------------------------------------------//
//!
//! \file   Utility_SearchAlgorithms.hpp
//! \author Alex Robinson
//! \brief  Functions declarations for searching algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SEARCH_ALGORITHMS_HPP
#define UTILITY_SEARCH_ALGORITHMS_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_Tuple.hpp"

namespace Utility{

namespace Search{

//! Binary search on a container of and return the lower bound iterator
template<size_t member, typename Iterator>
Iterator binaryLowerBound( Iterator start,
			   Iterator end,
			   const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value );

//! Binary search on a container of and return the lower bound iterator
template<typename Iterator>
Iterator binaryLowerBound( Iterator start,
			   Iterator end,
			   const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the lower bound container index
template<size_t member, typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
binaryLowerBoundIndex( Iterator start,
		       Iterator end,
		       const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value );

//! Binary search on a container and return the lower bound container index
template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
binaryLowerBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the upper bound iterator
template<size_t member, typename Iterator>
Iterator binaryUpperBound( Iterator start,
			   Iterator end,
			   const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value );

//! Binary search on a container and return the upper bound iterator
template<typename Iterator>
Iterator binaryUpperBound( Iterator start,
			   Iterator end,
			   const typename std::iterator_traits<Iterator>::value_type value );

//! Binary search on a container and return the upper bound container index
template<size_t member, typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
binaryUpperBoundIndex( Iterator start,
		       Iterator end,
		       const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value );

//! Binary search on a container and return the upper bound container index
template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
binaryUpperBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value );

} // end Search namespace

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_SearchAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SEARCH_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end Utility_SearchAlgorithms.hpp
//---------------------------------------------------------------------------//

