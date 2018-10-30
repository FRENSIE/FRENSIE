//---------------------------------------------------------------------------//
//!
//! \file   Utility_UndefinedTraits.hpp
//! \author Alex Robinson
//! \brief  A class that causes a compile time error in default trait/policy
//!         structs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNDEFINED_TRAITS_HPP
#define UTILITY_UNDEFINED_TRAITS_HPP

namespace Utility{

/*! \brief A struct designed to give a compile time error
 * \ingroup traits
 */
template<typename T>
struct UndefinedTraits
{
  //! This type should be used as the default value of typedefsw
  struct DesiredTypeIsMissingSpecialization{};

  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*! \brief A struct designed to give a compile time error
 * \ingroup traits
 */
template<template<typename,typename...> class Traits, typename T>
struct VerboseUndefinedTraits
{
  //! This type should be used as the default value of typedefsw
  struct DesiredTypeIsMissingSpecialization{};

  //! This function should not compile if there is any attempt to instantiate!
  static inline Traits<T> notDefined() { return T::This_type_is_missing_a_specialization(); }
};

} // end Utility namespace

#endif // end UTILITY_UNDEFINED_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_UndefinedTraits.hpp
//---------------------------------------------------------------------------//
