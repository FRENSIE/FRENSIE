//---------------------------------------------------------------------------//
//!
//! \file   Utility_Map.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::map and
//!         std::unordered_map
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAP_HPP
#define UTILITY_MAP_HPP

// Std Lib Includes
#include <iostream>
#include <map>
#include <unordered_map>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

/*! \defgroup map Map
 *
 * Additional helper functions and classes for use with the set::map and
 * std::unordered_map have been defined that do not appear in the standard
 * library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::map
 * \ingroup map
 * \ingroup to_string_traits
 */
template<typename Key, typename T>
struct ToStringTraits<std::map<Key,T> > : public Details::ToStringTraitsIteratorHelper<std::map<Key,T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::unordered_map
 * \ingroup map
 * \ingroup to_string_traits
 */
template<typename Key, typename T>
struct ToStringTraits<std::unordered_map<Key,T> > : public Details::ToStringTraitsIteratorHelper<std::unordered_map<Key,T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::map
 * \ingroup map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::map<Key,T>, std::pair<Key,T>, std::map<Key,T>, std::pair<Key,T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_map
 * \ingroup map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::unordered_map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_map<Key,T>, std::pair<Key,T>, std::unordered_map<Key,T>, std::pair<Key,T> >
{ /* ... */ };
  
} // end Utility namespace

namespace std{

/*! Place a std::map in a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::map<Key,T>& map )
{
  Utility::toStream( os, map );

  return os;
}

/*! Extract a std::map from a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::map<Key,T>& map )
{
  Utility::fromStream( is, map );

  return is;
}
  
/*! Place a std::unordered_map in a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::unordered_map<Key,T>& map )
{
  Utility::toStream( os, map );

  return os;
}

/*! Extract a std::unordered_map from a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::unordered_map<Key,T>& map )
{
  Utility::fromStream( is, map );

  return is;
}
  
} // end std namespace

#endif // end UTILITY_MAP_HPP

//---------------------------------------------------------------------------//
// end Utility_Map.hpp
//---------------------------------------------------------------------------//
