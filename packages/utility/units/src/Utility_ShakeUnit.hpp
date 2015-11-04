//---------------------------------------------------------------------------//
//!
//! \file   Utility_ShakeUnit.hpp
//! \author Alex Robinson
//! \brief  The shake unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SHAKE_UNIT_HPP
#define UTILITY_SHAKE_UNIT_HPP

// Boost Includes
#include <boost/units/scaled_base_unit.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/io.hpp>

namespace Utility{

namespace Units{

//! The Shake base unit
typedef boost::units::scaled_base_unit<boost::units::si::second_base_unit, boost::units::scale<10,boost::units::static_rational<-8> > > ShakeBaseUnit;

//! The Shake unit
typedef ShakeBaseUnit::unit_type Shake;

BOOST_UNITS_STATIC_CONSTANT( shake, Shake );

} // end Units namespace

} // end Utility namespace

namespace boost{

namespace units{

template<>
struct base_unit_info<Utility::Units::ShakeBaseUnit>
{
  static const char* name() { return "Shake"; }
  static const char* symbol() { return "sh"; }
};

} // end units namespace

} // end boost namespace

#endif // end UTILITY_SHAKE_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_ShakeUnit.hpp
//---------------------------------------------------------------------------//
