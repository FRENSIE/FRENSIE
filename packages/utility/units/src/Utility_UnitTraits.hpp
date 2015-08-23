//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTraits.hpp
//! \author Alex Robinson
//! \brief  Unit traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TRAITS_HPP
#define UTILITY_UNIT_TRAITS_HPP

// Boost Includes
#include <boost/units/make_system.hpp>

// FRENSIE Includes
#include "Utility_UnitTraitsDecl.hpp"

namespace Utility{

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
