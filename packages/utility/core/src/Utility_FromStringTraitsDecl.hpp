//---------------------------------------------------------------------------//
//!
//! \file   Utility_FromStringTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  FromStringTraits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FROM_STRING_TRAITS_DECL_HPP
#define UTILITY_FROM_STRING_TRAITS_DECL_HPP

// Std Lib Includes
#include <iostream>
#include <string>
#include <stdexcept>
#include <type_traits>

// FRENSIE Includes
#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup from_string_traits From String Traits
 * \ingroup traits
 */

namespace Utility{

/*! \brief Exception thrown by FromStringTraits methods when a conversion from
 * a string to the desired type fails
 * \ingroup from_string_traits
 */
class StringConversionException : public std::runtime_error
{
public:
  StringConversionException( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  ~StringConversionException() throw()
  { /* ... */ }
};

/*! Traits class used to convert a string to a type
 * \ingroup from_string_traits
 */
template<typename T, typename Enabled = void>
struct FromStringTraits
{
  //! The type that a string will be converted to (usually T)
  typedef typename Utility::UndefinedTraits<T>::DesiredTypeIsMissingSpecialization ReturnType;

  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  { Utility::UndefinedTraits<T>::notDefined(); return T(); }

  //! Extract the object from a stream
  static inline void fromStream( std::istream&,
                                 T&,
                                 const std::string& = std::string() )
  { Utility::UndefinedTraits<T>::notDefined(); }
};

/*! Convert the string to an object of type T
 *
 * This method can be overloaded for custom types of the
 * Utility::FromStringTraits class can be specialized for the custom type.
 * \ingroup from_string_traits
 */
template<typename T>
typename FromStringTraits<T>::ReturnType fromString( const std::string& obj_rep );

/*! Extract an object of type T from the stream
 *
 * Use this method when the behavior of stream operator >> for type T is
 * insufficient for some reason (e.g. extracting a boolean from "true" or
 * "false"). This method can be overloaded for custom types or the
 * Utility::FromStringTraits class can be specialized for the custom type.
 * \ingroup from_string_traits
 */
template<typename T>
void fromStream( std::istream& is,
                 T& obj,
                 const std::string& delims = std::string() );

/*! Initialize the input stream that will be used to extract an object
 *
 * The input stream will be moved from its current location to the first
 * occurrence of the start deliminator.
 * \ingroup from_string_traits
 */
void initializeInputStream( std::istream& is, const char start_delim );

/*! Move the input stream to the start of the next element
 *
 * The input stream will be moved from its current location to the next
 * occurrence of the element deliminator or the end deliminator. If the
 * end deliminator is reached first true will be returned indicating that all
 * elements have been read from the stream.
 * \ingroup from_string_traits
 */
bool moveInputStreamToNextElement( std::istream& is,
                                   const char elem_delim,
                                   const char end_delim );

/*! Check if the input stream contains any more elements to read.
 *
 * The input stream will be temporarily moved from its current location to
 * the next occurrence of a character not equal to the end deliminator. White
 * space can be optionally ignored. If another element is present, the
 * stream's original state will be restored.
 * \ingroup from_string_traits
 */
bool doesInputStreamContainAnotherElement( std::istream& is,
                                           const char end_delim,
                                           const bool ignore_whitespace = false );

/*! Expand pi keyword in string
 *
 * All occurrences of elements with the 'pi' keyword in the string will be
 * expanded to the actual value. A valid element with the 'pi' keyword must
 * have one of the following formats: 'n*pi/d', '-pi' or '-pi/d', where n and d
 * are integers and/or floating point values. The pi keyword is case
 * insensitive.
 */
void expandPiKeywords( std::string& obj_rep );

/*! Expand interval keywords in string
 *
 * All occurrences of elements with the 'i' or 'l' keyword in the string will be
 * expanded to actual element values. The 'i' and 'l' keywords are case
 * insensitive. An integer must appear before the keyword to indicate the
 * number of elements that will be created. Both keywords rely on the elements
 * directly before and after the element with the keyword to calculate the
 * intermediate elements. The 'i' keyword represents elements with equal linear
 * spacing while the l keyword represents elements with equal logarithmic
 * spacing.
 * \ingroup from_string_traits
 */
  template<typename T>
void expandIntervalKeywords( std::string& obj_rep );

/*! Expand repeated value keywords in string
 *
 * All occurrences of elements with the 'r' keyword in the string wil be
 * expanded to actual element values. The 'r' keywords are case
 * insensitive. An arithmetic value must appear before the keyword to
 * indicate that value that will be repeated. An integer value must appear
 * after the r keyword to indicate the number of times that the value
 * is repeated.
 * \ingroup from_string_traits
 */
template<typename T>
void expandRepeatKeywords( std::string& obj_rep );

} // end Utility namespace

#endif // end UTILITY_FROM_STRING_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_FromStringTraitsDecl.hpp
//---------------------------------------------------------------------------//
