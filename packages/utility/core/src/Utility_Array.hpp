//---------------------------------------------------------------------------//
//!
//! \file   Utility_Array.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::array
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_HPP
#define UTILITY_ARRAY_HPP

// Std Lib Includes
#include <array>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

/*! \defgroup array Array.
 *
 * Additional helper functions and classes for use with std::array have
 * been defined that do not appear in the standard library.
 */

namespace Utility{
  
/*! Partial specialization of ToStringTraits for std::array
 * \ingroup array
 * \ingroup to_string_traits
 */
template<typename T, size_t N>
struct ToStringTraits<std::array<T,N> > : public Details::ToStringTraitsIteratorHelper<std::array<T,N> >
{ /* ... */ };
  
} // end Utility namespace

namespace std{

/*! Place a std::array in a stream
 * \ingroup array
 */
template<typename T, size_t N>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::array<T,N>& array )
{
  Utility::toStream( os, array );

  return os;
}

} // end std namespace

#endif // end UTILITY_ARRAY_HPP

//---------------------------------------------------------------------------//
// end Utility_Array.hpp
//---------------------------------------------------------------------------//