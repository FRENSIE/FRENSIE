//---------------------------------------------------------------------------//
//!
//! \file   SearchAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Template definitions for search functions
//!
//---------------------------------------------------------------------------//

#ifndef SEARCH_ALGORITHMS_DEF_HPP
#define SEARCH_ALGORITHMS_DEF_HPP

// Std Lib Includes
#include <iostream>
#include <iterator>

// FACEMC Includes
#include "ContractException.hpp"
#include "SearchAlgorithms.hpp"
#include "TupleMemberTraits.hpp"

namespace FACEMC{

//! The namespace where searching algorithms are located.
namespace Search{

// Binary search on an array of continuous data
/*! \details This function allows one to search a container of continuous data
 * and find the lower bin boundary where the value of interest falls in. The
 * container is accessed with iterators and an iterator to the element 
 * representing the lower bin boundary is returned. 
 * \tparam member The tuple (either FACEMC::Pair, FACEMC::Trip or FACEMC::Quad)
 * member where the data that is being search on is stored. 
 * \tparam Iterator An iterator type that gives access to the container of
 * interest.
 * \param[in] start An iterator pointing to the first element of the container
 * of interest.
 * \param[in] end An iterator pointing to the last element of the container of
 * interest.
 * \param[in] value The value whose location in the container must be found.
 * \return An iterator to the element of the container representing the lower
 * bin boundary of the bin where the value of interest falls.
 * \pre 
 * <ul>
 *  <li> A valid set of iterators, which are any two iterators that are not
 *       equal (and from the same container), must be given to this function.
 *  <li> The value of interest must be greater than (or equal to) the start 
 *       value.
 *  <li> The value of interest must be less than (or equal to) the end value.
 * </ul>
 * \post The returned iterator must be valid (not equal to the initial end
 * iterator).
 */ 
template<TupleMember member, 
	 typename Iterator>
Iterator binarySearchContinuousData( Iterator start,
				     Iterator end,
				     const typename Traits::TupleMemberTraits<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value )
{
  // The iterators must be random access iterators (support +/- ops)
  testStaticPrecondition((boost::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::random_access_iterator_tag>::value));
  remember( Iterator true_end = end );
  remember( --true_end );
  // The iterators must be from a valid container (size > 0)
  testPrecondition( (start != end) );
  // The value used for the search must be within the limits of the sorted data
  testPrecondition( (value >= get<member>( *start )) );
  testPrecondition( (value <= get<member>( *(true_end) )) );

  // Remember the end iterator for the Postcondition check
  remember( Iterator invalid = end );
  
  typename std::iterator_traits<Iterator>::difference_type distance = 
    std::distance( start, end );
  
  while( distance > 1 )
  {
    if( value >= get<member>( *(start+distance/2) ) )
      start += distance/2;
    else
      end = start+distance/2;
    
    distance = std::distance( start, end );
  }

  // Check that a valid bin was found
  testPostcondition( start != invalid );
  
  return start;
}

// Binary search on a container of continuous data
/*! \details This function is meant for conducting a binary search on an 
 * array of non tuple members. An array of tuple members can still be searched,
 * however the tuple member on which the search will be conducted will always
 * be FACEMC::FIRST.
 */
template<typename Iterator>
inline Iterator binarySearchContinuousData( Iterator start,
					    Iterator end,
					    const typename std::iterator_traits<Iterator>::value_type value )
{
  return binarySearchContinuousData<FIRST>( start, end, value );
}

// Binary search on an array of discrete data
/*! \details This function allows one to search a container of discrete data
 * and find the lower bin boundary where the value of interest falls in. The
 * container is accessed with iterators and an iterator to the element 
 * representing the lower bin boundary is returned. When dealing with discrete
 * data an extra test must be done to ensure that the correct bin has been
 * found.
 * \tparam member The tuple (either FACEMC::Pair, FACEMC::Trip or FACEMC::Quad)
 * member where the data that is being searched on is stored.
 * \tparam Iterator An iterator type that gives access to the container of
 * interest.
 * \param[in] start An iterator pointing to the first element of the container
g * of interest.
 * \param[in] end An iterator pointing to the last element of the container of
 * interest.
 * \param[in] value The value whose location in the container must be found.
 * \return An iterator to the element of the container representing the lower
 * bin boundary of the bin where the value of interest falls.
 * \pre 
 * <ul> 
 *  <li> A valid set of iterators, which are any two iterators that are not
 *       equal (and from the same container), must be given to this function.
 *  <li> The value of interest must be less than the value in the last element
 *       of the container.
 * </ul>
 * \post The returned iterator must be valid (not equal to the initial end
 * iterator).
 */
template<TupleMember member, typename Iterator>
Iterator binarySearchDiscreteData( Iterator start,
				   Iterator end,
				   const typename Traits::TupleMemberTraits<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value )
{
  // The iterators must be random access iterators (support +/- ops)
  testStaticPrecondition((boost::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::random_access_iterator_tag>::value));
  remember( Iterator true_end = end );
  remember( --true_end );
  // The iterators must be from a valid container (size > 0)
  testPrecondition( (start != end) );
  // The value used for the search must be within the limits of the data
  //testPrecondition( (value >= 0.0) );
  testPrecondition( (value <= get<member>( *(true_end) ) ) );
  
  // Remember the end iterator for the Postcondition check
  remember( Iterator invalid = end );
  
  typename std::iterator_traits<Iterator>::difference_type distance = 
    std::distance( start, end );
  
  while( distance > 1 )
  {
    if( value >= get<member>( *(start+distance/2) ) )
      start += distance/2;
    else
      end = start+distance/2;
    
    distance = std::distance( start, end );
  }
  
  // If the search can only be narrowed to two bins, check which bin 
  // the value falls in
  if( distance == 1 )
  {
    if( value > get<member>( *(start) ) )
      start = end;
  }
  
  // Check that a valid bin was found
  testPostcondition( start != invalid );
  
  return start;
}

// Binary search on a container of discrete data
/*! \details This function is meant for conducting a binary search on an 
 * array of non tuple members. An array of tuple members can still be searched,
 * however the tuple member on which the search will be conducted will always
 * be FACEMC::FIRST.
 */
template<typename Iterator>
inline Iterator binarySearchDiscreteData( Iterator start,
					  Iterator end,
					  const typename std::iterator_traits<Iterator>::value_type value )
{
  return binarySearchDiscreteData<FIRST>( start, end, value );
}

} // end Search namespace

} // end FACEMC namespace

#endif // end SEARCH_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end SearchAlgorithms_def.hpp
//---------------------------------------------------------------------------//

