//---------------------------------------------------------------------------//
//!
//! \file   tstElectronVoltUnit.cpp
//! \author Alex Robinson
//! \brief  Electron volt unit unit test
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTraits.hpp"

using namespace Utility::Units;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the electron volt unit can be initialized
TEUCHOS_UNIT_TEST( ElectronVolt, initialize )
{
  boost::units::quantity<ElectronVolt> ev_energy( 1*eV );
 
  boost::units::quantity<boost::units::si::energy> si_energy( 1*eV );

  TEST_EQUALITY_CONST( ev_energy.value(), 1.0 );
  TEST_EQUALITY_CONST( si_energy.value(), 1.602176565e-19 );

  ev_energy = 
    boost::units::quantity<ElectronVolt>( 1*boost::units::si::joule ); 
						   
  si_energy = 1*boost::units::si::joule;

  TEST_FLOATING_EQUALITY( ev_energy.value(), 1.0/1.602176565e-19, 1e-15 );
  TEST_EQUALITY_CONST( si_energy.value(), 1.0 );

  ev_energy = boost::units::quantity<ElectronVolt>( 1*keV );

  TEST_EQUALITY_CONST( ev_energy.value(), 1000.0 );

  ev_energy = boost::units::quantity<ElectronVolt>( 1*MeV );

  TEST_EQUALITY_CONST( ev_energy.value(), 1e6 );
  
  typedef Utility::UnitTraits<ElectronVolt>::InverseUnit InverseElectronVolt;
  boost::units::quantity<InverseElectronVolt> inverse_ev_energy( 1.0/eV );
  
  std::cout << inverse_ev_energy << " " << 1.0/eV << std::endl;
}

//---------------------------------------------------------------------------//
// Check that the kilo-electron volt unit can be initialized
TEUCHOS_UNIT_TEST( KiloElectronVolt, initialize )
{
  boost::units::quantity<KiloElectronVolt> kev_energy( 1*keV );

  boost::units::quantity<boost::units::si::energy> si_energy( 1*keV );

  TEST_EQUALITY_CONST( kev_energy.value(), 1.0 );
  TEST_EQUALITY_CONST( si_energy.value(), 1.602176565e-16 );

  kev_energy = 
    boost::units::quantity<KiloElectronVolt>( 1*boost::units::si::joule );

  TEST_FLOATING_EQUALITY( kev_energy.value(), 1.0/1.602176565e-16, 1e-15 );
  
  kev_energy = boost::units::quantity<KiloElectronVolt>( 1*eV );

  TEST_EQUALITY_CONST( kev_energy.value(), 1e-3 );

  kev_energy = boost::units::quantity<KiloElectronVolt>( 1*MeV );

  TEST_EQUALITY_CONST( kev_energy.value(), 1e3 );    
}

//---------------------------------------------------------------------------//
// Check that the mega-electron volt unit can be initialized
TEUCHOS_UNIT_TEST( MegaElectronVolt, initialize )
{
  boost::units::quantity<MegaElectronVolt> mev_energy( 1*MeV );

  boost::units::quantity<boost::units::si::energy> si_energy( 1*MeV );

  TEST_EQUALITY_CONST( mev_energy.value(), 1.0 );
  TEST_EQUALITY_CONST( si_energy.value(), 1.602176565e-13 );

  mev_energy = 
    boost::units::quantity<MegaElectronVolt>( 1*boost::units::si::joule );

  TEST_FLOATING_EQUALITY( mev_energy.value(), 1.0/1.602176565e-13, 1e-15 );

  mev_energy = boost::units::quantity<MegaElectronVolt>( 1*eV );

  TEST_EQUALITY_CONST( mev_energy.value(), 1e-6 );

  mev_energy = boost::units::quantity<MegaElectronVolt>( 1*keV );

  TEST_EQUALITY_CONST( mev_energy.value(), 1e-3 );
}

//---------------------------------------------------------------------------//
// end tstElectronVoltUnit.cpp
//---------------------------------------------------------------------------//
