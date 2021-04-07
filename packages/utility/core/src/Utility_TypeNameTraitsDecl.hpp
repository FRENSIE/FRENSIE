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
  //! Check if the type has a specialization
  typedef std::false_type IsSpecialized;
  
  //! Get the type name
  static inline std::string name()
  { return typeid(typename std::remove_cv<T>::type()).name(); }
};

/*! Return the type name
 * \ingroup type_name_traits
 */
template<typename T>
std::string typeName();

/*! return the parameter pack type name
 * \ingroup type_name_traits
 */
template<typename... Types>
typename std::enable_if<(sizeof...(Types)>1),std::string>::type typeName();
 
} // end Utility namespace

/*! Helper macro for quickly defining the type name traits for a type
 * \ingroup type_name_traits
 */
#define TYPE_NAME_TRAITS_QUICK_DECL( Type )             \
  template<>                                            \
  struct TypeNameTraits<Type>                           \
  {                                                     \
    typedef std::true_type IsSpecialized;               \
                                                        \
    static inline std::string name()                    \
    { return #Type; }                                   \
  }

/*! Helper macro for quickly defining the type name traits for a type
 *
 * Use this macro when the type is not in the Utility namespace. This macro
 * must be called from the global namespace.
 * \ingroup type_name_traits
 */
#define TYPE_NAME_TRAITS_QUICK_DECL2( Type, Namespace ) \
  namespace Utility{                                    \
  template<>                                            \
  struct TypeNameTraits<Namespace::Type>                \
  {                                                     \
    typedef std::true_type IsSpecialized;                 \
                                                          \
    static inline std::string name()                      \
    { return #Type; }                                     \
  };                                                      \
  }


#endif // end UTILITY_TYPE_NAME_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeNameTraitsDecl.hpp
//---------------------------------------------------------------------------//
