//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Unit traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TRAITS_DECL_HPP
#define UTILITY_UNIT_TRAITS_DECL_HPP

// Std Lib Includes
#include <type_traits>

// Boost Includes
#include <boost/units/operators.hpp>

/*! \defgroup unit_traits Unit Traits
 * \ingroup traits
 */

namespace Utility{

/*! A struct designed to give a compile time error for unit traits
 * \ingroup unit_traits
 */
template<typename T>
struct UndefinedUnitTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*! The default unit traits implementation
 *
 * The default traits implementation assumes that a boost::units::unit object
 * is the template parameter. Specializations should be made for other types.
 * \ingroup unit_traits
 */
template<typename T>
struct UnitTraits
{
  //! The unit type
  typedef T Unit;

  //! The dimension of the unit
  typedef void Dimension;

  //! The unit system that the unit belongs to
  typedef void System;

  //! The inverse unit type
  typedef T InverseUnit;

  //! The unit raised to rational power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetUnitToPowerType
  {
    typedef T type;
  };

  //! The unit multiplied by another unit type
  template<typename OtherUnit>
  struct GetMultipliedUnitType
  {
    typedef OtherUnit type;
  };

  //! The wrapped quantity type associated with the unit and value type U
  template<typename U>
  struct GetQuantityType
  { typedef U type; };

  //! Check if the unit is dimensionless
  static inline bool isDimensionless()
  { return UndefinedUnitTraits<T>::notDefined(); }

  //! The name string
  static inline std::string name()
  { return UndefinedUnitTraits<T>::notDefined(); }

  //! The symbol string
  static inline std::string symbol()
  { return UndefinedUnitTraits<T>::notDefined(); }
};

} // end Utility namespace

/*! Macro for restricting distribution units to a certain dimension
 *
 * \details Certain classes only make sense when defined on a certain
 * dimension (e.g. energy). This macro will prevent improper use of a
 * class by preventing the class template instance from
 * compiling when the template parameter has the incorrect dimension. Void
 * will also be allowed (needed for creating unit-agnostic class instances). If
 * the compiler shows "__unit_has_invalid_dimension_if_visible__" then you
 * know that an attempt to use a unit with a restricted dimension was made,
 * which should help remedy the error faster (given that boost::units
 * template errors can be intimidating!). This macro can only be used
 * once - using it multiple times in the same header will prevent your
 * class from working with any dimension! It is safe to place it
 * anywhere in the class class declaration.
 * \ingroup unit_traits
 */
#define RESTRICT_UNIT_TO_BOOST_DIMENSION( Unit, Dim )\
typedef typename std::enable_if<std::is_same<typename Utility::UnitTraits<Unit>::Dimension,boost::units::Dim>::value || std::is_same<typename Utility::UnitTraits<Unit>::Dimension,void>::value>::type __unit_has_invalid_dimension_if_visible__

/*! Macro for excluding a unit from a certain dimension
 *
 * \details Certain class do not make sense when defined on a
 * certain dimension. This macro will prevent improper use of a class
 * by preventing the class template instance from compiling when
 * the template parameter has the incorrect dimension. If the compiler shows
 * "__unit_has_invalid_dimension_if_visible__" then you know that an attempt
 * to use a unit with a restricted dimension was made, which should help remedy
 * the error faster (given that boost::units template errors can be
 * intimidating!). This macro can be used as many times as desired in a
 * class header file, but only once per dimension. It is
 * safe to place it anywhere in the class declaration.
 * \ingroup unit_traits
 */
#define RESTRICT_UNIT_FROM_BOOST_DIMENSION( Unit, Dim )\
typedef typename std::enable_if<!std::is_same<typename Utility::UnitTraits<Unit>::Dimension,boost::units::Dim>::value>,Unit>::type __unit_has_invalid_ ## Dim ## _if_visible__

#endif // end UTILITY_UNIT_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTraitsDecl.hpp
//---------------------------------------------------------------------------//
