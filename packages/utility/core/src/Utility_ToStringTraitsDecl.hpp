//---------------------------------------------------------------------------//
//!
//! \file   Utility_ToStringTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  ToStringTraits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TO_STRING_TRAITS_DECL_HPP
#define UTILITY_TO_STRING_TRAITS_DECL_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup to_string_straits To String Traits
 * \ingroup traits
 */

namespace Utility{

/*! Traits class used to convert a type to a string
 * \ingroup to_string_traits
 */
template<typename T, typename Enabled = void>
struct ToStringTraits
{
  //! Convert an object of type T to a string
  static inline std::string toString( const T& obj )
  { Utility::UndefinedTraits<T>::notDefined(); return std::string(); }

  //! Place an object of type T in a stream
  static inline void toStream( std::ostream&, const T& )
  { Utility::UndefinedTraits<T>::notDefined(); }
};

/*! Convert the object to a string
 *
 * This method can be overloaded for custom types or the 
 * Utility::ToStringTraits class can be specialized for the custom type.
* \ingroup to_string_traits
 */
template<typename T>
std::string toString( const T& obj );

/*! Place the object in a stream
 *
 * Use this method when the behavior of stream operator << for type T is
 * insufficient for some reason (e.g. preserving floating point precision by
 * default). This method can be overloaded for custom types or the 
 * Utility::ToStringTraits class can be specialized for the custom type.
* \ingroup to_string_traits
 */
template<typename T>
void toStream( std::ostream& os, const T& obj );
  
} // end Utility namespace

#endif // end UTILITY_TO_STRING_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_ToStringTraitsDecl.hpp
//---------------------------------------------------------------------------//
