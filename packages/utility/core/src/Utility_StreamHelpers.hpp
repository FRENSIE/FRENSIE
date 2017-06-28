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
#include <map>
#include <unordered_map>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

namespace std{

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
