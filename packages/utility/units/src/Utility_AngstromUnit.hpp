//---------------------------------------------------------------------------//
//!
//! \file   Utility_AngstromUnit.hpp
//! \author Alex Robinson
//! \brief  The Angstrom unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ANGSTROM_UNIT_HPP
#define UTILITY_ANGSTROM_UNIT_HPP

// Boost Includes
#include <boost/units/scaled_base_unit.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/io.hpp>

namespace Utility{

namespace Units{

//! The Angstrom base unit
typedef boost::units::scaled_base_unit<boost::units::cgs::centimeter_base_unit, boost::units::scale<10, boost::units::static_rational<-8> > > AngstromBaseUnit;

//! The Angstrom unit
typedef AngstromBaseUnit::unit_type Angstrom;

BOOST_UNITS_STATIC_CONSTANT( angstrom, Angstrom );

} // end Units namespace

} // end Utility namespace

namespace boost{

namespace units{

template<>
struct base_unit_info<Utility::Units::AngstromBaseUnit>
{
  static const char* name() { return "Angstrom"; }
  static const char* symbol() { return "A"; }
};

} // end units namespace

} // end boost namespace

#endif // end UTILITY_ANGSTROM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_AngstromUnit.hpp
//---------------------------------------------------------------------------//
