//---------------------------------------------------------------------------//
//!
//! \file   tstElectronVoltUnit.cpp
//! \author Alex Robinson
//! \brief  Electron volt unit unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_ElectronVoltUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// ElectronVolt Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( ElectronVolt )

//---------------------------------------------------------------------------//
// Check that the electron volt unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::ElectronVolt> ev_energy( 1.0*eV );

  BOOST_CHECK_EQUAL( ev_energy.value(), 1.0 );

  ev_energy = 2.0*eV;

  BOOST_CHECK_EQUAL( ev_energy.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that electron volt unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::ElectronVolt> ev_energy_cgs( 1.0*cgs::erg );

  boost::units::quantity<Utility::Units::ElectronVolt> ev_energy_si( 1.0*si::joule );

  BOOST_CHECK_CLOSE_FRACTION( ev_energy_cgs.value(),
                              6.24150934326017944e+11,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( ev_energy_si.value(),
                              1.0/1.602176565e-19,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the electron volt unit can be initialized from keV and MeV
BOOST_AUTO_TEST_CASE( initialize_from_kev_mev )
{
  boost::units::quantity<Utility::Units::ElectronVolt> ev_energy_kev( 1.0*keV );

  boost::units::quantity<Utility::Units::ElectronVolt> ev_energy_mev( 1.0*MeV );

  BOOST_CHECK_EQUAL( ev_energy_kev.value(), 1000.0 );
  BOOST_CHECK_EQUAL( ev_energy_mev.value(), 1e6 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the electron volt
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::energy> cgs_energy( 1*eV );

  boost::units::quantity<si::energy> si_energy( 1*eV );

  BOOST_CHECK_CLOSE_FRACTION( cgs_energy.value(), 1.602176565e-12, 1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( si_energy.value(), 1.602176565e-19, 1e-15 );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// KiloElectronVolt Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( KiloElectronVolt )

//---------------------------------------------------------------------------//
// Check that the keV unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::KiloElectronVolt> kev_energy( 1*keV );

  BOOST_CHECK_EQUAL( kev_energy.value(), 1.0 );

  kev_energy = 2.0*keV;

  BOOST_CHECK_EQUAL( kev_energy.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the keV unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::KiloElectronVolt> kev_energy_cgs( 1.0*cgs::erg );

  boost::units::quantity<Utility::Units::KiloElectronVolt> kev_energy_si( 1.0*si::joule );

  BOOST_CHECK_CLOSE_FRACTION( kev_energy_cgs.value(),
                              6.24150934326017976e8,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( kev_energy_si.value(),
                              1.0/1.602176565e-16,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the keV unit can bin intialized from eV and MeV units
BOOST_AUTO_TEST_CASE( initialize_from_ev_mev )
{
  boost::units::quantity<Utility::Units::KiloElectronVolt> kev_energy_ev( 1.0*eV );

  boost::units::quantity<Utility::Units::KiloElectronVolt> kev_energy_mev( 1.0*MeV );

  BOOST_CHECK_EQUAL( kev_energy_ev.value(), 1e-3 );
  BOOST_CHECK_EQUAL( kev_energy_mev.value(), 1e3 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the keV unit
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::energy> cgs_energy( 1.0*keV );

  boost::units::quantity<si::energy> si_energy( 1.0*keV );

  BOOST_CHECK_CLOSE_FRACTION( cgs_energy.value(),1.602176565e-09, 1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( si_energy.value(), 1.602176565e-16, 1e-15 );
}

BOOST_AUTO_TEST_SUITE_END()
 
//---------------------------------------------------------------------------//
// MegaElectronVolt Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( MegaElectronVolt )

//---------------------------------------------------------------------------//
// Check that the mega-electron volt unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::MegaElectronVolt> mev_energy( 1*MeV );

  BOOST_CHECK_EQUAL( mev_energy.value(), 1.0 );

  mev_energy = 2.0*MeV;

  BOOST_CHECK_EQUAL( mev_energy.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the MeV unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::MegaElectronVolt> mev_energy_cgs( 1.0*cgs::erg );

  boost::units::quantity<Utility::Units::MegaElectronVolt> mev_energy_si( 1.0*si::joule );

  BOOST_CHECK_CLOSE_FRACTION( mev_energy_cgs.value(),
                              6.24150934326017974e5,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( mev_energy_si.value(),
                              1.0/1.602176565e-13,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the MeV unit can bin intialized from eV and keV units
BOOST_AUTO_TEST_CASE( initialize_from_ev_kev )
{
  boost::units::quantity<Utility::Units::MegaElectronVolt> mev_energy_ev( 1.0*eV );

  boost::units::quantity<Utility::Units::MegaElectronVolt> mev_energy_kev( 1.0*keV );

  BOOST_CHECK_EQUAL( mev_energy_ev.value(), 1e-6 );
  BOOST_CHECK_EQUAL( mev_energy_kev.value(), 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the MeV unit
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::energy> cgs_energy( 1.0*MeV );

  boost::units::quantity<si::energy> si_energy( 1.0*MeV );

  BOOST_CHECK_CLOSE_FRACTION( cgs_energy.value(), 1.602176565e-06, 1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( si_energy.value(), 1.602176565e-13, 1e-15 );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstElectronVoltUnit.cpp
//---------------------------------------------------------------------------//
