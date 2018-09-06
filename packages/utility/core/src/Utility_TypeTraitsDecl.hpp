//---------------------------------------------------------------------------//
//!
//! \file   Utility_TypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  General type traits class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TYPE_TRAITS_DECL_HPP
#define UTILITY_TYPE_TRAITS_DECL_HPP

// Std Lib Includes
#include <type_traits>

/*! \defgroup type_traits Type Traits
 * \ingroup traits
 */

namespace Utility{

/*! Get the typed null pointer associated with a type
 * \ingroup type_traits
 */
template<typename T>
struct NullPointer : public std::integral_constant<T*,(T*)NULL>
{ 
  //! The pointer type
  typedef T* PointerType;
};

/*! Helper function to get a typed null pointer
 * \ingroup type_traits
 */
template<typename T>
constexpr typename NullPointer<T>::PointerType nullPointer();

/*! Check if the type is a pointer-to-const type
 * \ingroup type_traits
 */
template<typename T>
struct IsPointerToConst : public std::false_type
{ /* ... */ };

/*! Check if the type has a hash function defined
 *
 * If you create a new specialization of std::hash, specialize this class
 * with your type and inherit from std::true_type.
 * \ingroup type_traits
 */
template<typename T, typename Enabled = void>
struct IsHashable : public std::false_type
{ /* ... */ };

/*! Check if the type is a tuple (std::tuple or std::pair)
 * \ingroup type_traits
 */
template<typename T, typename Enabled = void>
struct IsTuple : public std::false_type
{ /* ... */ };

/*! Check if the type is a pair (std::pair only)
 * \ingroup type_traits
 */
template<typename T, typename Enabled = void>
struct IsPair : public std::false_type
{ /* ... */ };

/*! Check if the type is a sequence container that uses contiguous memory
 * \ingroup type_traits
 */
template<typename T, typename Enabled = void>
struct IsSequenceContainerWithContiguousMemory : public std::false_type
{ /* ... */ };
  
} // end Utility namespace

#endif // end UTILITY_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
