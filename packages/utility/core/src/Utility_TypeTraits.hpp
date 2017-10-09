//---------------------------------------------------------------------------//
//!
//! \file   Utility_TypeTraits.hpp
//! \author Alex Robinson
//! \brief  Type traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TYPE_TRAITS_HPP
#define UTILITY_TYPE_TRAITS_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <vector>
#include <bitset>
#include <thread>
#include <typeindex>
#include <system_error>
#include <tuple>
#include <utility>

// FRENSIE Includes
#include "Utility_TypeTraitsDecl.hpp"

namespace Utility{

/*! Partial specialization of NullPointer for const types
 * \ingroup type_traits
 */
template<typename T>
struct NullPointer<const T> : public std::integral_constant<T* const, (T* const)NULL>
{ /* ... */ };

/*! Partial specialization of NullPointer for const pointer-to-const types
 * \ingroup type_traits
 */
template<typename T>
struct NullPointer<const T* const> : public std::integral_constant<const T* const, (const T* const)NULL>
{ /* ... */ };

/*! Partial specialization of IsPointerToConst for pointer-to-const types
 * \ingroup type_traits
 */
template<typename T>
struct IsPointerToConst<const T*> : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsPointerToConst for const pointer-to-const types
 * \ingroup type_traits
 */
template<typename T>
struct IsPointerToConst<const T* const> : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for pointer types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<T*> : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for arithemtic types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<T,typename std::enable_if<std::is_arithmetic<T>::value>::type> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::string
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::string> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::u16string
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::u16string> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::u32string
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::u32string> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::wstring
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::wstring> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::error_code
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::error_code> : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for std::bitset types
 * \ingroup type_traits
 */
template<size_t N>
struct IsHashable<std::bitset<N> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for std::unique_ptr types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<std::unique_ptr<T> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for std::shared_ptr types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<std::shared_ptr<T> > : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::type_index
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::type_index> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::vector<bool> 
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::vector<bool> > : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for std::thread::id
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::thread::id> : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsTuple for std::tuple
 * \ingroup type_traits
 */
template<typename... Types>
struct IsTuple<std::tuple<Types...> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsTuple for std::pair
 * \ingroup type_traits
 */
template<typename T1, typename T2>
struct IsTuple<std::pair<T1,T2> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsTuple for const types
 * \ingroup type_traits
 */
template<typename T>
struct IsTuple<const T> : public IsTuple<T>
{ /* ... */ };

/*! Partial specialization of IsTuple for volatile types
 * \ingroup type_traits
 */
template<typename T>
struct IsTuple<volatile T> : public IsTuple<T>
{ /* ... */ };

/*! Partial specialization of IsTuple for const volatile types
 * \ingroup type_traits
 */
template<typename T>
struct IsTuple<const volatile T> : public IsTuple<T>
{ /* ... */ };

/*! Partial specialization of IsPair for std::pair
 * \ingroup type_traits
 */
template<typename T1, typename T2>
struct IsPair<std::pair<T1,T2> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsPair for const types
 * \ingroup type_traits
 */
template<typename T>
struct IsPair<const T> : public IsPair<T>
{ /* ... */ };

/*! Partial specialization of IsPair for volatile types
 * \ingroup type_traits
 */
template<typename T>
struct IsPair<volatile T> : public IsPair<T>
{ /* ... */ };

/*! Partial specialization of IsPair for const volatile types
 * \ingroup type_traits
 */
template<typename T>
struct IsPair<const volatile T> : public IsPair<T>
{ /* ... */ };  

} // end Utility namespace

#endif // end UTILITY_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeTraits.hpp
//---------------------------------------------------------------------------//
