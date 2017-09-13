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

namespace Details{

/*! The type name parameter pack helper class
 * \ingroup type_name_traits
 */
template<typename... Types>
struct TypeNameParameterPackHelper;

/*! \brief Partial specialization of the TypeNameParameterPackHelper class for
 * a single template parameter
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameParameterPackHelper<T>
{
  //! Append the type name to the end of the string
  static void appendName( std::string& parameter_pack_name )
  { parameter_pack_name += Utility::TypeNameTraits<T>::name(); }
};

/*! \brief Partial specialization of the TypeNameParameterPackHelper class for
 * peeling off the first parameter
 * \ingroup type_name_traits
 */
template<typename T, typename... Types>
struct TypeNameParameterPackHelper<T,Types...>
{
  //! Append all type names to the end of the string
  static void appendName( std::string& parameter_pack_name )
  {
    parameter_pack_name += Utility::TypeNameTraits<T>::name();
    parameter_pack_name += ",";

    TypeNameParameterPackHelper<Types...>::appendName( parameter_pack_name );
  }
};
  
  
} // end Details namespace

// Return the type name
template<typename T>
inline std::string typeName()
{
  return Utility::TypeNameTraits<T>::name();
}

// Return the type name
template<typename... Types>
inline typename std::enable_if<(sizeof...(Types)>1),std::string>::type
typeName()
{
  std::string parameter_pack_name;
  
  Details::TypeNameParameterPackHelper<Types...>::appendName( parameter_pack_name );

  return parameter_pack_name;
}

// Return the type name
template<typename T>
inline std::string typeName( const T& obj )
{
  return Utility::TypeNameTraits<T>::name( obj );
}

// Return the type names
template<typename... Types>
inline typename std::enable_if<(sizeof...(Types)>1),std::string>::type
typeName( const Types&... )
{
  return Utility::typeName<Types...>();
}
  
} // end Utility namespace

#endif // end UTILITY_TYPE_NAME_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeNameTraits.hpp
//---------------------------------------------------------------------------//
