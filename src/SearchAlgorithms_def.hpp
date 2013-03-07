//---------------------------------------------------------------------------//
// \file   SearchAlgorithms_def.hpp
// \author Alex Robinson
// \brief  Template definitions for search functions
//---------------------------------------------------------------------------//

#ifndef SEARCH_ALGORITHMS_DEF_HPP
#define SEARCH_ALGORITHMS_DEF_HPP

// Std Lib Includes
#include <iostream>
#include <iterator>

// FACEMC Includes
#include "ContractException.hpp"
#include "SearchAlgorithms.hpp"
#include "TupleGetSetMemberPolicy.hpp"

namespace FACEMC{

namespace Search{

//! Binary search on an array of continuous data
template<TupleMember member, typename Iterator>
Iterator binarySearchContinuousData( Iterator start,
				     Iterator end,
				     const typename TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value )
{
  // The iterators must be from a valid container (size > 0)
  testPrecondition( (start != end) );
  
  // The value used for the search must be within the limits of the data
  testPrecondition( (value >= TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::get( *start )) );
  testPrecondition( (value <= TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::get( *(end-1) )) );

  // Remember the end iterator for the Postcondition check
  remember( Iterator invalid = end );
  
  typename std::iterator_traits<Iterator>::difference_type distance = 
    std::distance( start, end );
  
  while( distance > 1 )
  {
    if( value >= TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::get( *(start+distance/2) ) )
      start += distance/2;
    else
      end = start+distance/2;
    
    distance = std::distance( start, end );
  }

  // Check that a valid bin was found
  testPostcondition( start != invalid );
  
  return start;
}

//! Binary search on an array of discrete data
template<TupleMember member, typename Iterator>
Iterator binarySearchDiscreteData( Iterator start,
				   Iterator end,
				   const typename TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value )
{
  // The iterators must be from a valid container (size > 0)
  testPrecondition( (start != end) );
  
  // The value used for the search must be within the limits of the data
  testPrecondition( (value >= 0) );
  testPrecondition( (value <= TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::get( *(end-1) )) );
  
  // Remember the end iterator for the Postcondition check
  remember( Iterator invalid = end );
  
  typename std::iterator_traits<Iterator>::difference_type distance = std::distance( start, end );
  
  while( distance > 1 )
  {
    if( value >= TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::get( *(start+distance/2) ) )
      start += distance/2;
    else
      end = start+distance/2;
    
    distance = std::distance( start, end );
  }
  
  // If the search can only be narrowed to two bins, check which bin 
  // the value falls in
  if( distance == 1 )
  {
    if( value > TupleGetSetMemberPolicy<typename std::iterator_traits<Iterator>::value_type,member>::get( *(start) ) )
      start = end;
  }
  
  // Check that a valid bin was found
  testPostcondition( start != invalid );
  
  return start;
}

} // end Search namespace

} // end FACEMC namespace

#endif // end SEARCH_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end SearchAlgorithms_def.hpp
//---------------------------------------------------------------------------//

