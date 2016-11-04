//---------------------------------------------------------------------------//
//!
//! \file   tstAngstromUnit.cpp
//! \author Alex Robinson
//! \brief  The Angstrom unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_AngstromUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the angstrom unit can be initialized
TEUCHOS_UNIT_TEST( AngstromUnit, initialize )
{
  quantity<Angstrom> angstrom_length( 1.0*angstrom );

  TEST_EQUALITY_CONST( angstrom_length.value(), 1.0 );

  angstrom_length = 2.0*angstrom;

  TEST_EQUALITY_CONST( angstrom_length.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the angstrom unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( AngstromUnit, initialize_from_cgs_si )
{
  quantity<Angstrom> angstrom_length_cgs( 1.0*cgs::centimeter );

  quantity<Angstrom> angstrom_length_si( 1.0*si::meter );

  TEST_EQUALITY_CONST( angstrom_length_cgs.value(), 1e8 );
  TEST_EQUALITY_CONST( angstrom_length_si.value(), 1e10 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the angstrom unit
TEUCHOS_UNIT_TEST( AngstromUnit, initialize_cgs_si )
{
  quantity<cgs::length> centimeter_length( 1.0*angstrom );

  quantity<si::length> meter_length( 1.0*angstrom );

  TEST_EQUALITY_CONST( centimeter_length.value(), 1e-8 );
  TEST_EQUALITY_CONST( meter_length.value(), 1e-10 );
}


//---------------------------------------------------------------------------//
// end tstAngstromUnit.cpp
//---------------------------------------------------------------------------//
