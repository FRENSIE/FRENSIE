//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTraits.hpp
//! \author Alex Robinson
//! \brief  Unit traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TRAITS_HPP
#define UTILITY_UNIT_TRAITS_HPP

// Std Lib Includes
#include <type_traits>

// Boost Includes
#include <boost/units/make_system.hpp>
#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/io.hpp>
#include <boost/units/dimensionless_unit.hpp>
#include <boost/units/is_dimensionless.hpp>

// FRENSIE Includes
#include "Utility_UnitTraitsDecl.hpp"

namespace Utility{

/*! The partial specialization of UnitTraits for boost::units::unit
 * \ingroup unit_traits
 */
template<typename Dim, typename Sys>
struct UnitTraits<boost::units::unit<Dim,Sys> >
{
  //! The unit type
  typedef boost::units::unit<Dim,Sys> Unit;

  //! The dimension of the unit
  typedef Dim Dimension;

  //! The unit system that the unit belongs to
  typedef Sys System;

  //! The inverse unit type
  typedef typename boost::units::power_typeof_helper<Unit,boost::units::static_rational<-1> >::type InverseUnit;

  //! The unit raised to rational power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetUnitToPowerType
  {
    typedef typename std::conditional<N!=0,typename boost::units::power_typeof_helper<Unit,boost::units::static_rational<N,D> >::type,void>::type type;
  };

  //! The unit multiplied by another unit type
  template<typename OtherUnit>
  struct GetMultipliedUnitType
  {
    typedef typename std::conditional<std::is_same<OtherUnit,void>::value,Unit,typename boost::units::multiply_typeof_helper<Unit,OtherUnit>::type>::type type;
  };

  //! The wrapped quantity type associated with the unit and value type T
  template<typename T>
  struct GetQuantityType
  { typedef boost::units::quantity<Unit,T> type; };

  //! The name string
  static inline std::string name()
  { return boost::units::name_string( Unit() ); }

  //! The symbol string
  static inline std::string symbol()
  { return boost::units::symbol_string( Unit() ); }
};

/*! The specialization of UnitTraits for void (no units)
 *
 * Note that void (no units) is different from dimensionless, which has a
 * distinct boost::units::unit class.
 * \ingroup unit_traits
 */
template<>
struct UnitTraits<void>
{
  // The dimensionless unit
  //typedef boost::units::dimensionless_unit<boost::units::make_system<>::type>::type UnitType;
  typedef void Unit;
  typedef void Dimension;
  typedef void System;
  typedef void InverseUnit;
  
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetUnitToPowerType
  {
    typedef void type;
  };

  template<typename OtherUnit>
  struct GetMultipliedUnitType
  {
    typedef OtherUnit type;
  };

  template<typename T>
  struct GetQuantityType
  { typedef T type; };

  static inline std::string name()
  { return "void"; }

  static inline std::string symbol()
  { return "0"; }
};

} // end Utility namespace

#endif // end UTILITY_UNIT_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTraits.hpp
//---------------------------------------------------------------------------//
