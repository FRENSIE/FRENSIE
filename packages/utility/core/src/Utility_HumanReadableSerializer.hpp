//---------------------------------------------------------------------------//
//!
//! \file   Utility_HumanReadableSerializer.hpp
//! \author Alex Robinson
//! \brief  The human-readable serializer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HUMAN_READABLE_SERIALIZER_HPP
#define UTILITY_HUMAN_READABLE_SERIALIZER_HPP

// Std Lib Includes
#include <iostream>
#include <string>
#include <type_traits>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

namespace Utility{

//! The human-readable serializer class
template<typename T, typename Enabled = void>
struct HumanReadableSerializer
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const T& obj )
  { Utility::UndefinedTraits<T>::notDefined(); }
  
  //! Serialize the object
  static inline std::string serialize( const T& obj )
  { Utility::UndefinedTraits<T>::notDefined(); return std::string(); }

  //! Deserialize the object
  static inline int deserialize( const std::string& obj_string )
  { Utility::UndefinedTraits<T>::notDefined(); return 0; }

  //! Deserialize the object
  static inline int deserialize( std::istream& is,
                                 const std::string& delims = std::string() )
  { Utility::UndefinedTraits<T>::notDefined(); return 0; }
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_HumanReadableSerializer_def.hpp"

//---------------------------------------------------------------------------//
  
#endif // end UTILITY_HUMAN_READABLE_SERIALIZER_HPP

//---------------------------------------------------------------------------//
// end Utility_HumanReadableSerializer.hpp
//---------------------------------------------------------------------------//
