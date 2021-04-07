//---------------------------------------------------------------------------//
//!
//! \file   Utility_Deque.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::deque
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DEQUE_HPP
#define UTILITY_DEQUE_HPP

// Std Lib Includes
#include <iostream>
#include <deque>

// Boost Includes
#include <boost/serialization/deque.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_DesignByContract.hpp"

/*! \defgroup deque Deque
 *
 * Additional helper functions and classes for use with the std::deque have
 * been defined that do not appear in the standard library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::deque
 * \ingroup deque
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::deque<T> > : public Details::ToStringTraitsIteratorHelper<std::deque<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::deque
 * \ingroup deque
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::deque<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::deque<T> >
{ /* ... */ };

/*! Partial specialization of Utility::TypeNameTraits for std::deque types
 * \ingroup vector
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<std::deque<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("std::deque<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of ComparisonTraits for std::deque
 * \ingroup deque
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::deque<T> > : public Details::ComparisonTraitsSequenceContainerHelper<std::deque<T> >
{ /* ... */ };

namespace Details{

/*! Partial specialization of the zero helper for std::deque
 * \ingroup deque
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<std::deque<T> > : public STLCompliantContainerZeroHelper<std::deque<T> >
{ /* ... */ };
  
} // end Details namespace
  
} // end Utility namespace

namespace std{

/*! Place a std::deque in a stream
 * \ingroup deque
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::deque<T>& deque )
{
  Utility::toStream( os, deque );

  return os;
}

/*! Extract a std::deque from a stream
 * \ingroup deque
 */
template<typename T>
inline std::istream& operator>>( std::istream& is, std::deque<T>& deque )
{
  Utility::fromStream( is, deque );

  return is;
}

/*! Append an element to a std::deque
 *
 * This operator gives a std::deque ostream-like capabilities.
 * \ingroup deque
 */
template<typename T, typename U>
inline std::deque<T>& operator<<( std::deque<T>& deque, const U& value )
{
  deque.push_back( value );
  return deque;
}

/*! Append an element that has been converted to a string to a std::deque
 *
 * This operator first converts the string to a value of type T and then
 * appends it to the deque.
 * \ingroup deque
 */
template<typename T>
inline std::deque<T>& operator<<( std::deque<T>& deque,
                                  const std::string& value_string )
{
  deque.push_back( Utility::fromString<T>( value_string ) );
  return deque;
}

/*! Append an element that has been converted to a string to a std::deque
 *
 * This operator first converts the string to a value of type T and then
 * appends it to the deque.
 * \ingroup deque
 */
template<typename T>
inline std::deque<T>& operator<<( std::deque<T>& deque,
                                  const char* value_string )
{
  deque.push_back( Utility::fromString<T>( value_string ) );
  return deque;
}

/*! Extract an element from a std::deque
 *
 * This operator gives a std::deque istream-like capabilities. Unlike
 * an istream, the last element is taken from the deque first (FILO).
 * \ingroup deque
 */
template<typename T, typename U>
inline std::deque<T>& operator>>( std::deque<T>& deque, U& value )
{
  // Make sure that there are elements to extract
  testPrecondition( deque.size() > 0 );
  
  value = deque.back();
  deque.pop_back();

  return deque;
}

/*! Extract an element from a std::deque in its string form
 *
 * This operator extracts the last element from a deque and converts it
 * to a string.
 * \ingroup deque
 */
template<typename T>
inline std::deque<T>& operator>>( std::deque<T>& deque,
                                  std::string& value_string )
{
  // Make sure that there are elements to extract
  testPrecondition( deque.size() > 0 );
  
  value_string = Utility::toString( deque.back() );
  deque.pop_back();

  return deque;
}
  
} // end std namespace

#endif // end UTILITY_DEQUE_HPP

//---------------------------------------------------------------------------//
// end Utility_Deque.hpp
//---------------------------------------------------------------------------//
