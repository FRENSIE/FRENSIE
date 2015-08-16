//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTraits.hpp
//! \author Alex Robinson
//! \brief  Unit traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TRAITS_HPP
#define UTILITY_UNIT_TRAITS_HPP

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
  typedef void Dimension;
  typedef void System;

  template<typename T>
  struct GetQuantityType
  { typedef double value; };
};

} // end Utility namespace

#endif // end UTILITY_UNIT_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTraits.hpp
//---------------------------------------------------------------------------//
