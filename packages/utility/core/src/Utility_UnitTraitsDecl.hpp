//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Unit traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TRAITS_DECL_HPP
#define UTILITY_UNIT_TRAITS_DECL_HPP

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

  //! The unit raised to power N/D type
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

  //! The wrapped quantity type associated with the unit and value type T
  template<typename U>
  struct GetQuantityType
  { typedef U type; };

  //! The name string
  static inline std::string name()
  { return UndefinedUnitTraits<T>::notDefined(); }

  //! The symbol string
  static inline std::string symbol()
  { return UndefinedUnitTraits<T>::notDefined(); }
};

} // end Utility namespace

#endif // end UTILITY_UNIT_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTraitsDecl.hpp
//---------------------------------------------------------------------------//
