//---------------------------------------------------------------------------//
//!
//! \file   Utility_TypeNameTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  TypeNameTraits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TYPE_NAME_TRAITS_DECL_HPP
#define UTILITY_TYPE_NAME_TRAITS_DECL_HPP

// Std Lib Includes
#include <string>
#include <typeinfo>

/*! \defgroup type_name_traits Type Name Traits
 * \ingroup traits
 */

namespace Utility{

/*! Traits class used to get the name of a type
 * \ingroup type_name_traits
 */
template<typename T, typename Enabled = void>
struct TypeNameTraits
{
  //! Get the type name
  static inline std::string name()
  { return TypeNameTraits<T>::name( T() ); }

  //! Get the type name
  static inline std::string name( const T& obj )
  { return typeid(obj).name(); }
};

/*! Return the type name
 * \ingroup type_name_traits
 */
template<typename T>
std::string typeName();

/*! Return the type name
 * \ingroup type_name_traits
 */
template<typename T>
std::string typeName( const T& obj );
  
} // end Utility namespace

#endif // end UTILITY_TYPE_NAME_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeNameTraitsDecl.hpp
//---------------------------------------------------------------------------//
