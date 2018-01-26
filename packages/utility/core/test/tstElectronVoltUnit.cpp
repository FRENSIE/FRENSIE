//---------------------------------------------------------------------------//
//!
//! \file   tstElectronVoltUnit.cpp
//! \author Alex Robinson
//! \brief  Electron volt unit unit test
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTraits.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the electron volt unit can be initialized
TEUCHOS_UNIT_TEST( ElectronVolt, initialize )
{
  quantity<ElectronVolt> ev_energy( 1*eV );

  TEST_EQUALITY_CONST( ev_energy.value(), 1.0 );

  ev_energy = 2.0*eV;

  TEST_EQUALITY_CONST( ev_energy.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that electron volt unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( ElectronVolt, initialize_from_cgs_si )
{
  quantity<ElectronVolt> ev_energy_cgs( 1.0*cgs::erg );

  quantity<ElectronVolt> ev_energy_si( 1.0*si::joule );

  TEST_FLOATING_EQUALITY( ev_energy_cgs.value(),
			  6.24150934326017944e+11,
			  1e-15 );
  TEST_FLOATING_EQUALITY( ev_energy_si.value(),
			  1.0/1.602176565e-19,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the electron volt unit can be initialized from keV and MeV
TEUCHOS_UNIT_TEST( ElectronVolt, initialize_from_kev_mev )
{
  quantity<ElectronVolt> ev_energy_kev( 1.0*keV );

  quantity<ElectronVolt> ev_energy_mev( 1.0*MeV );

  TEST_EQUALITY_CONST( ev_energy_kev.value(), 1000.0 );
  TEST_EQUALITY_CONST( ev_energy_mev.value(), 1e6 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the electron volt
TEUCHOS_UNIT_TEST( ElectronVolt, initialize_cgs_si )
{
  quantity<cgs::energy> cgs_energy( 1*eV );

  quantity<si::energy> si_energy( 1*eV );

  TEST_FLOATING_EQUALITY( cgs_energy.value(), 1.602176565e-12, 1e-15 );
  TEST_FLOATING_EQUALITY( si_energy.value(), 1.602176565e-19, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the keV unit can be initialized
TEUCHOS_UNIT_TEST( KiloElectronVolt, initialize )
{
  quantity<KiloElectronVolt> kev_energy( 1*keV );

  TEST_EQUALITY_CONST( kev_energy.value(), 1.0 );

  kev_energy = 2.0*keV;

  TEST_EQUALITY_CONST( kev_energy.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the keV unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( KiloElectronVolt, initialize_from_cgs_si )
{
  quantity<KiloElectronVolt> kev_energy_cgs( 1.0*cgs::erg );

  quantity<KiloElectronVolt> kev_energy_si( 1.0*si::joule );

  TEST_FLOATING_EQUALITY( kev_energy_cgs.value(),
			  6.24150934326017976e8,
			  1e-15 );
  TEST_FLOATING_EQUALITY( kev_energy_si.value(),
			  1.0/1.602176565e-16,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the keV unit can bin initialized from eV and MeV units
TEUCHOS_UNIT_TEST( KiloElectronVolt, initialize_from_ev_mev )
{
  quantity<KiloElectronVolt> kev_energy_ev( 1.0*eV );

  quantity<KiloElectronVolt> kev_energy_mev( 1.0*MeV );

  TEST_EQUALITY_CONST( kev_energy_ev.value(), 1e-3 );
  TEST_EQUALITY_CONST( kev_energy_mev.value(), 1e3 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the keV unit
TEUCHOS_UNIT_TEST( KiloElectronVolt, initialize_cgs_si )
{
  quantity<cgs::energy> cgs_energy( 1.0*keV );

  quantity<si::energy> si_energy( 1.0*keV );

  TEST_FLOATING_EQUALITY( cgs_energy.value(),1.602176565e-09, 1e-15 );
  TEST_FLOATING_EQUALITY( si_energy.value(), 1.602176565e-16, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the mega-electron volt unit can be initialized
TEUCHOS_UNIT_TEST( MegaElectronVolt, initialize )
{
  quantity<MegaElectronVolt> mev_energy( 1*MeV );

  TEST_EQUALITY_CONST( mev_energy.value(), 1.0 );

  mev_energy = 2.0*MeV;

  TEST_EQUALITY_CONST( mev_energy.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the MeV unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( MegaElectronVolt, initialize_from_cgs_si )
{
  quantity<MegaElectronVolt> mev_energy_cgs( 1.0*cgs::erg );

  quantity<MegaElectronVolt> mev_energy_si( 1.0*si::joule );

  TEST_FLOATING_EQUALITY( mev_energy_cgs.value(),
			  6.24150934326017974e5,
			  1e-15 );
  TEST_FLOATING_EQUALITY( mev_energy_si.value(),
			  1.0/1.602176565e-13,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the MeV unit can bin initialized from eV and keV units
TEUCHOS_UNIT_TEST( MegaElectronVolt, initialize_from_ev_kev )
{
  quantity<MegaElectronVolt> mev_energy_ev( 1.0*eV );

  quantity<MegaElectronVolt> mev_energy_kev( 1.0*keV );

  TEST_EQUALITY_CONST( mev_energy_ev.value(), 1e-6 );
  TEST_EQUALITY_CONST( mev_energy_kev.value(), 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the MeV unit
TEUCHOS_UNIT_TEST( MegaElectronVolt, initialize_cgs_si )
{
  quantity<cgs::energy> cgs_energy( 1.0*MeV );

  quantity<si::energy> si_energy( 1.0*MeV );

  TEST_FLOATING_EQUALITY( cgs_energy.value(), 1.602176565e-06, 1e-15 );
  TEST_FLOATING_EQUALITY( si_energy.value(), 1.602176565e-13, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstElectronVoltUnit.cpp
//---------------------------------------------------------------------------//
