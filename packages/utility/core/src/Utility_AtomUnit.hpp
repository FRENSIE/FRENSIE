//---------------------------------------------------------------------------//
//!
//! \file   Utility_AtomUnit.hpp
//! \author Alex Robinson
//! \brief  The atom unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ATOM_UNIT_HPP
#define UTILITY_ATOM_UNIT_HPP

// Boost Includes
#include <boost/units/systems/si/amount.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/conversion.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_RawPhysicalConstants.hpp"

namespace Utility{

namespace Units{

//! The atom base unit
struct AtomBaseUnit : public boost::units::base_unit<AtomBaseUnit, boost::units::amount_dimension,2>
{
  static const char* name() { return "atom"; }
  static const char* symbol() { return "atom"; }
};

//! The atom unit
typedef AtomBaseUnit::unit_type Atom;

BOOST_UNITS_STATIC_CONSTANT( atom, Atom );

} // end Units namespace

} // end Utility namespace

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::AtomBaseUnit, boost::units::si::amount, double, 1.0/Utility::RawPhysicalConstants::avogadro_constant );
BOOST_UNITS_DEFINE_CONVERSION_FACTOR( boost::units::si::amount, Utility::Units::AtomBaseUnit, double, Utility::RawPhysicalConstants::avogadro_constant );

BOOST_UNITS_DEFAULT_CONVERSION( Utility::Units::AtomBaseUnit, boost::units::si::amount );

#endif // end UTILITY_ATOM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_AtomUnit.hpp
//---------------------------------------------------------------------------//

