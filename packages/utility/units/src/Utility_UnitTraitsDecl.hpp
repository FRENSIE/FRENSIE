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
#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/operators.hpp>
#include <boost/units/io.hpp>
#include <boost/units/dimensionless_unit.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

/*! \defgroup unit_traits Unit Traits
 * \ingroup traits
 */

namespace Utility{

/*! The default unit traits implementation
 *
 * The default traits implementation assumes that a boost::units::unit object
 * is the template parameter. Specializations should be made for other types.
 * \ingroup unit_traits
 */
template<typename Unit>
struct UnitTraits
{
  //! The dimension of the unit
  typedef typename Unit::dimension_type Dimension;

  //! The unit system that the unit belongs to
  typedef typename Unit::system_type System;

  //! The inverse unit type
  typedef typename boost::units::power_typeof_helper<Unit,boost::units::static_rational<-1> >::type InverseUnit;

  //! The unit raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetUnitToPowerType
  {
    typedef typename boost::units::power_typeof_helper<Unit,boost::units::static_rational<N,D> >::type type;
  };

  //! The unit multiplied by another unit type
  template<typename OtherUnit>
  struct GetMultipliedUnitType
  {
    typedef typename boost::mpl::if_<boost::is_same<OtherUnit,void>,Unit,typename boost::units::multiply_typeof_helper<Unit,OtherUnit>::type>::type type;
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

} // end Utility namespace

#endif // end UTILITY_UNIT_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTraitsDecl.hpp
//---------------------------------------------------------------------------//
