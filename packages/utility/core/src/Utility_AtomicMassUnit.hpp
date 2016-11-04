//---------------------------------------------------------------------------//
//!
//! \file   Utility_AtomicMassUnit.hpp
//! \author Alex Robinson
//! \brief  The atomic mass unit
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ATOMIC_MASS_UNIT_HPP
#define UTILITY_ATOMIC_MASS_UNIT_HPP

// Boost Includes
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/conversion.hpp>

namespace Utility{

namespace Units{

//! The atomic mass base unit
struct AtomicMassBaseUnit : public boost::units::base_unit<AtomicMassBaseUnit,boost::units::mass_dimension,4>
{
  static const char* name() { return "atomic mass unit"; }
  static const char* symbol() { return "amu"; }
};

//! The atomic mass unit
typedef AtomicMassBaseUnit::unit_type AtomicMass;

BOOST_UNITS_STATIC_CONSTANT( amu, AtomicMass );

} // end Units namespace

} // end Utility namespace

// From codata 2014
BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::AtomicMassBaseUnit, boost::units::si::mass, double, 1.660539040e-27 );
BOOST_UNITS_DEFINE_CONVERSION_FACTOR( boost::units::si::mass, Utility::Units::AtomicMassBaseUnit, double, 1.0/1.660539040e-27 );

BOOST_UNITS_DEFAULT_CONVERSION( Utility::Units::AtomicMassBaseUnit, boost::units::si::mass );

#endif // end UTILITY_ATOMIC_MASS_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_AtomicMassUnit.hpp
//---------------------------------------------------------------------------//
