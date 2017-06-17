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

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup from_string_traits From String Traits
 * \ingroup traits
 */

namespace Utility{

/*! Traits class used to convert a string to a type
 * \ingroup from_string_traits
 */
template<typename T, typename Enabled = void>
struct FromStringTraits
{
  //! Convert the string to an object of type T
  static inline T fromString( const std::string& obj_rep )
  { Utility::UndefinedTraits<T>::notDefined(); return T(); }

  //! Extract the object from a stream
  static inline void fromStream( std::istream&,
                                 T&,
                                 const std::string& = std::string() )
  { Utility::UndefinedTraits<T>::notDefined(); return T(); }
};

/*! Convert the string to an object of type T
 *
 * This method can be overloaded for custom types of the 
 * Utility::FromStringTraits class can be specialized for the custom type.
 * \ingroup from_string_traits
 */
template<typename T>
void fromString( const std::string& obj_rep, T& obj );

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
 * occurance of the start deliminator.
 * \ingroup from_string_traits
 */
void initializeInputStream( std::istream& is, const char start_delim );

/*! Move the input stream to the start of the next element
 * 
 * The input stream will be moved from its current location to the next
 * occurance of the element deliminator or the end deliminator. If the
 * end deliminator is reached first true will be returned indicating that all
 * elements have been read from the stream. 
 * \ingroup from_string_traits
 */
bool moveInputStreamToNextElement( std::istream& is,
                                   const char elem_delim,
                                   const char end_delim );
  
} // end Utility namespace

#endif // end UTILITY_FROM_STRING_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_FromStringTraitsDecl.hpp
//---------------------------------------------------------------------------//
