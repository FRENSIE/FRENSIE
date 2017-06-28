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
#include <sstream>
#include <vector>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

/*! \defgroup vector Vector
 *
 * Additional helper functions and classes for use the std::vector have
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

/*! Partial specialization of FromStringTraits for std::vector
 * \ingroup vector
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::vector<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::vector<T> >
{ /* ... */ };
  
} // end Utility namespace

namespace std{

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
  
} // end std namespace

#endif // end UTILITY_VECTOR_HPP

//---------------------------------------------------------------------------//
// end Utility_Vector.hpp
//---------------------------------------------------------------------------//
