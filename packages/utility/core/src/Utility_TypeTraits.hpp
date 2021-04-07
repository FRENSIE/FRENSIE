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
#include <array>
#include <initializer_list>
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
{ 
  //! The pointer type
  typedef T* const PointerType;
};

// Helper function to get a typed null pointer
template<typename T>
constexpr typename NullPointer<T>::PointerType nullPointer()
{ return NullPointer<T>::value; }

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
struct IsHashable<T,typename std::enable_if<std::is_pointer<T>::value>::type> : public std::true_type
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

/*! Specialization of IsHashable for const std::string
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::string> : public IsHashable<std::string>
{ /* ... */ };

/*! Specialization of IsHashable for std::u16string
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::u16string> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::u16string
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::u16string> : public IsHashable<std::u16string>
{ /* ... */ };

/*! Specialization of IsHashable for std::u32string
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::u32string> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::u32string
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::u32string> : public IsHashable<std::u32string>
{ /* ... */ };

/*! Specialization of IsHashable for std::wstring
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::wstring> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::wstring
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::wstring> : public IsHashable<std::wstring>
{ /* ... */ };

/*! Specialization of IsHashable for std::error_code
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::error_code> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::error_code
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::error_code> : public IsHashable<std::error_code>
{ /* ... */ };

/*! Partial specialization of IsHashable for std::bitset types
 * \ingroup type_traits
 */
template<size_t N>
struct IsHashable<std::bitset<N> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for const std::bitset types
 * \ingroup type_traits
 */
template<size_t N>
struct IsHashable<const std::bitset<N> > : public IsHashable<std::bitset<N> >
{ /* ... */ };

/*! Partial specialization of IsHashable for std::unique_ptr types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<std::unique_ptr<T> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for const std::unique_ptr types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<const std::unique_ptr<T> > : public IsHashable<std::unique_ptr<T> >
{ /* ... */ };

/*! Partial specialization of IsHashable for std::shared_ptr types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<std::shared_ptr<T> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of IsHashable for const std::shared_ptr types
 * \ingroup type_traits
 */
template<typename T>
struct IsHashable<const std::shared_ptr<T> > : public IsHashable<std::shared_ptr<T> >
{ /* ... */ };

/*! Specialization of IsHashable for std::type_index
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::type_index> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::type_index
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::type_index> : public IsHashable<std::type_index>
{ /* ... */ };

/*! Specialization of IsHashable for std::vector<bool> 
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::vector<bool> > : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::vector<bool> 
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::vector<bool> > : public IsHashable<std::vector<bool> >
{ /* ... */ };

/*! Specialization of IsHashable for std::thread::id
 * \ingroup type_traits
 */
template<>
struct IsHashable<std::thread::id> : public std::true_type
{ /* ... */ };

/*! Specialization of IsHashable for const std::thread::id
 * \ingroup type_traits
 */
template<>
struct IsHashable<const std::thread::id> : public IsHashable<std::thread::id>
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

/*! \brief Partial specialization of IsSequenceContainerWithContiguousMemory
 * for std::array
 * \ingroup type_traits
 */
template<typename T, size_t N>
struct IsSequenceContainerWithContiguousMemory<std::array<T,N> > : public std::true_type
{ /* ... */ };

/*! \brief Partial specialization of IsSequenceContainerWithContiguousMemory
 * for std::vector
 * \ingroup type_traits
 */
template<typename T>
struct IsSequenceContainerWithContiguousMemory<std::vector<T> > : public std::true_type
{ /* ... */ };

/*! \brief Partial specialization of IsSequenceContainerWithContiguousMemory
 * for std::initializer_list
 * \ingroup type_traits
 */
template<typename T>
struct IsSequenceContainerWithContiguousMemory<std::initializer_list<T> > : public std::true_type
{ /* ... */ };

/*! \brief Specialization of IsSequenceContainerWithContiguousMemory
 * for std::string
 * \ingroup type_traits
 */
template<>
struct IsSequenceContainerWithContiguousMemory<std::string> : public std::true_type
{ /* ... */ };

/*! \brief Partial specialization of IsSequenceContainerWithContiguousMemory
 * for const types
 * \ingroup type_traits
 */
template<typename T>
struct IsSequenceContainerWithContiguousMemory<const T> : public IsSequenceContainerWithContiguousMemory<T>
{ /* ... */ };

} // end Utility namespace

#endif // end UTILITY_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeTraits.hpp
//---------------------------------------------------------------------------//
