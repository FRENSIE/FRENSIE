//---------------------------------------------------------------------------//
//!
//! \file   Utility_StreamHelpers.hpp
//! \author Alex Robinson
//! \brief  Stream helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STREAM_HELPERS_HPP
#define UTILITY_STREAM_HELPERS_HPP

// Std Lib Includes
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

namespace std{
  
//! Place a std::vector in a stream
template<typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::vector<T>& vector )
{
  Utility::toStream( os, vector );

  return os;
}

//! Extract a std::vector from a stream
template<typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::vector<T>& vector )
{
  Utility::fromStream( is, vector );

  return is;
}

//! Place a std::list in a stream
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::list<T>& list )
{
  Utility::toStream( os, list );

  return os;
}

//! Extract a std::list from a stream
template<typename T>
inline std::istream& operator>>( std::istream& is, std::list<T>& list )
{
  Utility::fromStream( is, list );

  return is;
}

//! Place a std::forward_list in a stream
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::forward_list<T>& list )
{
  Utility::toStream( os, list );

  return os;
}

//! Extract a std::forward_list from a stream
template<typename T>
inline std::istream& operator>>( std::istream& is, std::forward_list<T>& list )
{
  Utility::fromStream( is, list );

  return is;
}

//! Place a std::deque in a stream
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::deque<T>& deque )
{
  Utility::toStream( os, deque );

  return os;
}

//! Extract a std::deque from a stream
template<typename T>
inline std::istream& operator>>( std::istream& is, std::deque<T>& deque )
{
  Utility::fromStream( is, deque );

  return is;
}

//! Place a std::set in a stream
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::set<T>& set )
{
  Utility::toStream( os, set );

  return os;
}

//! Extract a std::set from a stream
template<typename T>
inline std::istream& operator>>( std::istream& is, std::set<T>& set )
{
  Utility::fromStream( is, set );

  return is;
}

//! Place a std::unordered_set in a stream
template<typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::unordered_set<T>& set )
{
  Utility::toStream( os, set );

  return os;
}

//! Extract a std::unordered_set from a stream
template<typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::unordered_set<T>& set )
{
  Utility::fromStream( is, set );

  return is;
}

//! Place a std::map in a stream
template<typename Key, typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::map<Key,T>& map )
{
  Utility::toStream( os, map );

  return os;
}

//! Extract a std::map from a stream
template<typename Key, typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::map<Key,T>& map )
{
  Utility::fromStream( is, map );

  return is;
}
  
//! Place a std::unordered_map in a stream
template<typename Key, typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::unordered_map<Key,T>& map )
{
  Utility::toStream( os, map );

  return os;
}

//! Extract a std::unordered_map from a stream
template<typename Key, typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::unordered_map<Key,T>& map )
{
  Utility::fromStream( is, map );

  return is;
}
  
} // end std namespace

#endif // end UTILITY_STREAM_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_StreamHelpers.hpp
//---------------------------------------------------------------------------//
