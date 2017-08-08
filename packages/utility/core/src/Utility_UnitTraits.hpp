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

// FRENSIE Includes
#include "Utility_UnitTraitsDecl.hpp"

namespace Utility{

/*! The partial specialization of UnitTraits for boost::units::unit
 * \ingroup unit_traits
 */
template<typename Dim, typename Sys>
struct UnitTraits<boost::units::unit<Dim,Sys> >
{
  typedef boost::units::unit<Dim,Sys> Unit;
  typedef Dim Dimension;
  typedef Sys System;

  typedef typename boost::units::power_typeof_helper<Unit,boost::units::static_rational<-1> >::type InverseUnit;

  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetUnitToPowerType
  {
    typedef typename boost::units::power_typeof_helper<Unit,boost::units::static_rational<N,D> >::type type;
  };

  template<typename OtherUnit>
  struct GetMultipliedUnitType
  {
    typedef typename std::conditional<std::is_same<OtherUnit,void>::value,Unit,typename boost::units::multiply_typeof_helper<Unit,OtherUnit>::type>::type type;
  };

  template<typename T>
  struct GetQuantityType
  { typedef boost::units::quantity<Unit,T> type; };

  static inline std::string name()
  { return boost::units::name_string( Unit() ); }

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
  //! The dimensionless unit
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
