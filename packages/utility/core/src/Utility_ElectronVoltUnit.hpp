//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElectronVoltUnit.hpp
//! \author Alex Robinson
//! \brief  The electron volt unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELECTRON_VOLT_UNIT_HPP
#define UTILITY_ELECTRON_VOLT_UNIT_HPP

// Boost Includes
#include <boost/units/systems/si/energy.hpp>
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/conversion.hpp>
#include <boost/units/make_scaled_unit.hpp>

namespace Utility{

namespace Units{

//! The electron volt base unit
struct ElectronVoltBaseUnit : public boost::units::base_unit<ElectronVoltBaseUnit,boost::units::energy_dimension,1>
{
  static const char* name() { return "electron volt"; }
  static const char* symbol() { return "eV"; }
};

//! The electron volt unit
typedef ElectronVoltBaseUnit::unit_type ElectronVolt;

//! The kilo-electron volt unit
typedef boost::units::make_scaled_unit<ElectronVolt, boost::units::scale<10,boost::units::static_rational<3> > >::type KiloElectronVolt;

//! The mega-electron volt unit
typedef boost::units::make_scaled_unit<ElectronVolt, boost::units::scale<10,boost::units::static_rational<6> > >::type MegaElectronVolt;

BOOST_UNITS_STATIC_CONSTANT( eV, ElectronVolt );
BOOST_UNITS_STATIC_CONSTANT( keV, KiloElectronVolt );
BOOST_UNITS_STATIC_CONSTANT( MeV, MegaElectronVolt );

} // end Units namespace

} // end Utility namespace

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::ElectronVoltBaseUnit, boost::units::si::energy, double, 1.602176565e-19 );
BOOST_UNITS_DEFINE_CONVERSION_FACTOR( boost::units::si::energy, Utility::Units::ElectronVoltBaseUnit, double, 1.0/1.602176565e-19 );

BOOST_UNITS_DEFAULT_CONVERSION( Utility::Units::ElectronVoltBaseUnit, boost::units::si::energy );

#endif // end UTILITY_ELECTRON_VOLT_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_ElectronVoltUnit.hpp
//---------------------------------------------------------------------------//
