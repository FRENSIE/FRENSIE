//---------------------------------------------------------------------------//
//!
//! \file   Utility_SearchAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Template definitions for search functions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SEARCH_ALGORITHMS_DEF_HPP
#define UTILITY_SEARCH_ALGORITHMS_DEF_HPP

// Std Lib Includes
#include <iostream>
#include <iterator>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace Utility{

//! The namespace where searching algorithms are located.
namespace Search{

// Binary search on a container of and return the lower bound iterator
/*! \details This function allows one to search a container of data and find
 * the lower bin boundary where the value of interest falls in. The
 * container is accessed with iterators and an iterator to the element
 * representing the lower bin boundary is returned.
 * \tparam member The tuple (either Utility::Pair, Utility::Trip or
 * Utility::Quad)
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
template<size_t member,
	 typename Iterator>
inline Iterator binaryLowerBound(
    Iterator start,
    Iterator end,
    const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value )
{
  // The iterators must be random access iterators (support +/- ops)
  //testStaticPrecondition((boost::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::random_access_iterator_tag>::value));
  remember( Iterator true_end = end );
  remember( --true_end );
  // The iterators must be from a valid container (size > 0)
  testPrecondition( (start != end) );

  // The value used for the search must be within the limits of the sorted data
  testPrecondition( (value >= Utility::get<member>( *start )) );
  testPrecondition( (value <= Utility::get<member>( *(true_end) )) );

  // Remember the end iterator for the Postcondition check
  remember( Iterator invalid = end );

  Iterator mid_point;

  typename std::iterator_traits<Iterator>::difference_type distance =
    std::distance( start, end );

  while( distance > 1 )
  {
    mid_point = start;
    std::advance( mid_point, distance/2 );

    if( value >= Utility::get<member>( *mid_point ) )
      start = mid_point;
    else
      end = mid_point;

    distance = std::distance( start, end );
  }

  // Check that a valid bin was found
  testPostcondition( start != invalid );

  return start;
}

// Binary search on a container of and return the lower bound iterator
/*! \details This function is meant for conducting a binary search on an
 * array of non tuple members. An array of tuple members can still be searched,
 * however the tuple member on which the search will be conducted will always
 * be Utility::FIRST.
 */
template<typename Iterator>
inline Iterator binaryLowerBound( Iterator start,
				  Iterator end,
				  const typename std::iterator_traits<Iterator>::value_type value )
{
  return binaryLowerBound<0>( start, end, value );
}

// Binary search on a container and return the lower bound container index
/*! \details This function allows one to search a container of data
 * and find the index of the lower bin boundary where the value of interest
 * falls. The container is accessed with iterators and an index to the
 * element representing the lower bin boundary is returned.
 * \tparam member The tuple (either Utility::Pair, Utility::Trip or
 * Utility::Quad)
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
template<size_t member, typename Iterator>
inline typename std::iterator_traits<Iterator>::difference_type
binaryLowerBoundIndex( Iterator start,
		       Iterator end,
		       const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value )
{
  // Make sure the container size can fit in an unsigned integer
  Iterator start_copy = start;

  Iterator lower_bound = binaryLowerBound<member>( start, end, value );

  return std::distance( start_copy, lower_bound );
}

// Binary search on a container and return the lower bound container index
/*! \details This function is meant for conducting a binary search on an
 * array of non tuple members. An array of tuple members can still be searched,
 * however the tuple member on which the search will be conducted will always
 * be Utility::FIRST.
 */
template<typename Iterator>
inline typename std::iterator_traits<Iterator>::difference_type
binaryLowerBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value )
{
  return binaryLowerBoundIndex<0>( start, end, value );
}

// Binary search on a container and return the upper bound iterator
/*! \details This function allows one to search a container of data and find
 * the upper bin boundary where the value of interest falls in. The
 * container is accessed with iterators and an iterator to the element
 * representing the upper bin boundary is returned. To get the correct upper
 * bound an extra test must be done to ensure that the correct bin has been
 * found.
 * \tparam member The tuple (either Utility::Pair, Utility::Trip or
 * Utility::Quad)
 * member where the data that is being searched on is stored.
 * \tparam Iterator An iterator type that gives access to the container of
 * interest.
 * \param[in] start An iterator pointing to the first element of the container
 * of interest.
 * \param[in] end An iterator pointing to the last element of the container of
 * interest.
 * \param[in] value The value whose location in the container must be found.
 * \return An iterator to the element of the container representing the upper
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
template<size_t member, typename Iterator>
inline Iterator binaryUpperBound( Iterator start,
				  Iterator end,
				  const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value )
{
  // The iterators must be random access iterators (support +/- ops)
  //testStaticPrecondition((boost::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::random_access_iterator_tag>::value));
  remember( Iterator true_end = end );
  remember( --true_end );
  // The iterators must be from a valid container (size > 0)
  testPrecondition( (start != end) );
  // The value used for the search must be within the limits of the data
  testPrecondition( (value <= Utility::get<member>( *(true_end) ) ) );

  // Remember the end iterator for the Postcondition check
  remember( Iterator invalid = end );

  Iterator mid_point;

  typename std::iterator_traits<Iterator>::difference_type distance =
    std::distance( start, end );

  while( distance > 1 )
  {
    mid_point = start;
    std::advance( mid_point, distance/2 );

    if( value >= Utility::get<member>( *mid_point ) )
      start = mid_point;
    else
      end = mid_point;

    distance = std::distance( start, end );
  }

  // If the search can only be narrowed to two bins, check which bin
  // the value falls in
  if( distance == 1 )
  {
    if( value > Utility::get<member>( *(start) ) )
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
 * be Utility::FIRST.
 */
template<typename Iterator>
inline Iterator binaryUpperBound( Iterator start,
				  Iterator end,
				  const typename std::iterator_traits<Iterator>::value_type value )
{
  return binaryUpperBound<0>( start, end, value );
}

// Binary search on a container and return the upper bound index
/*! \details This function allows one to search a container of data and find
 * the upper bin boundary where the value of interest falls in. The
 * container is accessed with iterators and an iterator to the element
 * representing the upper bin boundary is returned. To get the correct upper
 * bound an extra test must be done to ensure that the correct bin has been
 * found.
 * \tparam member The tuple (either Utility::Pair, Utility::Trip or
 * Utility::Quad)
 * member where the data that is being searched on is stored.
 * \tparam Iterator An iterator type that gives access to the container of
 * interest.
 * \param[in] start An iterator pointing to the first element of the container
 * of interest.
 * \param[in] end An iterator pointing to the last element of the container of
 * interest.
 * \param[in] value The value whose location in the container must be found.
 * \return An iterator to the element of the container representing the upper
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
template<size_t member, typename Iterator>
inline typename std::iterator_traits<Iterator>::difference_type
binaryUpperBoundIndex( Iterator start,
		       Iterator end,
		       const typename TupleElement<member,typename std::iterator_traits<Iterator>::value_type>::type value )
{
  // Make sure the container size can fit in an unsigned integer
  Iterator start_copy = start;

  Iterator upper_bound = binaryUpperBound<member>( start, end, value );

  return std::distance( start_copy, upper_bound );
}

// Binary search on a container and return the upper bound container index
/*! \details This function is meant for conducting a binary search on an
 * array of non tuple members. An array of tuple members can still be searched,
 * however the tuple member on which the search will be conducted will always
 * be Utility::FIRST.
 */
template<typename Iterator>
inline typename std::iterator_traits<Iterator>::difference_type
binaryUpperBoundIndex( Iterator start,
		       Iterator end,
		       const typename std::iterator_traits<Iterator>::value_type value )
{
  return binaryUpperBoundIndex<0>( start, end, value );
}

} // end Search namespace

} // end Utility namespace

#endif // end UTILITY_SEARCH_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SearchAlgorithms_def.hpp
//---------------------------------------------------------------------------//

