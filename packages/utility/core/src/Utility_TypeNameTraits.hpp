//---------------------------------------------------------------------------//
//!
//! \file   Utility_TypeNameTraits.hpp
//! \author Alex Robinson
//! \brief  Type name traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TYPE_NAME_TRAITS_HPP
#define UTILITY_TYPE_NAME_TRAITS_HPP

// FRENSIE Includes
#include "Utility_TypeNameTraitsDecl.hpp"

namespace Utility{

// Return the type name
template<typename T>
inline std::string typeName()
{
  Utility::TypeNameTraits<T>::name();
}

// Return the type name
template<typename T>
inline std::string typeName( const T& obj )
{
  Utility::TypeNameTraits<T>::name( obj );
}
  
} // end Utility namespace

#endif // end UTILITY_TYPE_NAME_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeNameTraits.hpp
//---------------------------------------------------------------------------//
