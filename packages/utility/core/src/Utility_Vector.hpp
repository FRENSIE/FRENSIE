//---------------------------------------------------------------------------//
//!
//! \file   Utility_Vector.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::vector
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_VECTOR_HPP
#define UTILITY_VECTOR_HPP

// Std Lib Includes
#include <iostream>
#include <vector>

// Boost Includes
#include <boost/serialization/vector.hpp>

// FRENSIE Includes
#include "Utility_ArrayView.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_DesignByContract.hpp"

/*! \defgroup vector Vector
 *
 * Additional helper functions and classes for use with the std::vector have
 * been defined that do not appear in the standard library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::vector
 * \ingroup vector
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::vector<T> > : public Details::ToStringTraitsIteratorHelper<std::vector<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::vector iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup vector
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator>::value ||
          std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value ||
          std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value ||
          std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of FromStringTraits for std::vector
 * \ingroup vector
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::vector<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::vector<T> >
{ /* ... */ };

/*! Partial specialization of Utility::TypeNameTraits for std::vector types
 * \ingroup vector
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<std::vector<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("std::vector<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of ComparisonTraits for std::vector
 * \ingroup vector
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::vector<T> > : public Details::ComparisonTraitsSequenceContainerHelper<std::vector<T> >
{ /* ... */ };

namespace Details{

/*! Partial specialization of the zero helper for std::vector
 * \ingroup vector
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<std::vector<T> > : public STLCompliantContainerZeroHelper<std::vector<T> >
{ /* ... */ };
  
} // end Details namespace
  
} // end Utility namespace

namespace std{

/*! Create a view of a vector
 * \ingroup vector
 * \ingroup view
 */
template<typename T>
inline Utility::ArrayView<T> operator|( std::vector<T>& vector,
                                        const Utility::Slice& slice )
{
  // Make sure that the slice offset is valid
  testPrecondition( slice.offset() < vector.size() );
  // Make sure that the slice is valid
  testPrecondition( slice.offset() + slice.extent() <= vector.size() );
  
  return Utility::ArrayView<T>( vector.data() + slice.offset(),
                                slice.extent() );
}

/*! Create a const view of a vector
 * \ingroup vector
 * \ingroup view
 */
template<typename T>
inline Utility::ArrayView<const T> operator|( const std::vector<T>& vector,
                                              const Utility::Slice& slice )
{
  // Make sure that the slice offset is valid
  testPrecondition( slice.offset() < vector.size() );
  // Make sure that the slice is valid
  testPrecondition( slice.offset() + slice.extent() <= vector.size() );
  
  return Utility::ArrayView<const T>( vector.data() + slice.offset(),
                                      slice.extent() );
}

/*! Place a std::vector in a stream
 * \ingroup vector
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::vector<T>& vector )
{
  Utility::toStream( os, vector );

  return os;
}

/*! Extract a std::vector from a stream
 * \ingroup vector
 */
template<typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::vector<T>& vector )
{
  Utility::fromStream( is, vector );

  return is;
}

/*! Append an element to a std::vector
 *
 * This operator gives a std::vector ostream-like capabilities.
 * \ingroup vector
 */
template<typename T, typename U>
inline std::vector<T>& operator<<( std::vector<T>& vector, const U& value )
{
  vector.push_back( value );
  return vector;
}

/*! Append an element that has been converted to a string to a std::vector
 *
 * This operator first converts the string to a value of type T and then
 * appends it to the vector.
 * \ingroup vector
 */
template<typename T>
inline std::vector<T>& operator<<( std::vector<T>& vector,
                                   const std::string& value_string )
{
  vector.push_back( Utility::fromString<T>( value_string ) );
  return vector;
}

/*! Append an element that has been converted to a string to a std::vector
 *
 * This operator first converts the string to a value of type T and then
 * appends it to the vector.
 * \ingroup vector
 */
template<typename T>
inline std::vector<T>& operator<<( std::vector<T>& vector,
                                   const char* value_string )
{
  vector.push_back( Utility::fromString<T>( value_string ) );
  return vector;
}

/*! Extract an element from a std::vector
 *
 * This operator gives a std::vector istream-like capabilities. Unlike
 * an istream, the last element is taken from the vector first (FILO).
 * \ingroup vector
 */
template<typename T, typename U>
inline std::vector<T>& operator>>( std::vector<T>& vector, U& value )
{
  // Make sure that there are elements to extract
  testPrecondition( vector.size() > 0 );
  
  value = vector.back();
  vector.pop_back();

  return vector;
}

/*! Extract an element from a std::vector in its string form
 *
 * This operator extracts the last element from a vector and converts it
 * to a string.
 * \ingroup vector
 */
template<typename T>
inline std::vector<T>& operator>>( std::vector<T>& vector,
                                   std::string& value_string )
{
  // Make sure that there are elements to extract
  testPrecondition( vector.size() > 0 );
  
  value_string = Utility::toString( vector.back() );
  vector.pop_back();

  return vector;
}
  
} // end std namespace

#endif // end UTILITY_VECTOR_HPP

//---------------------------------------------------------------------------//
// end Utility_Vector.hpp
//---------------------------------------------------------------------------//
