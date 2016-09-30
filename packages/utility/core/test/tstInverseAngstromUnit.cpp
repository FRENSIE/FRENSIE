//---------------------------------------------------------------------------//
//!
//! \file   tstInverseAngstromUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse Angstrom unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_AngstromUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse angstrom unit can be initialized
TEUCHOS_UNIT_TEST( InverseAngstromUnit, initialize )
{
  quantity<InverseAngstrom> inverse_angstrom_quantity( 1.0*inverse_angstrom );

  TEST_EQUALITY_CONST( inverse_angstrom_quantity.value(), 1.0 );

  inverse_angstrom_quantity = 2.0*inverse_angstrom;

  TEST_EQUALITY_CONST( inverse_angstrom_quantity.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse angstrom unit can be initialized from the Angstrom
TEUCHOS_UNIT_TEST( InverseAngstromUnit, initialize_from_angstrom )
{
  quantity<InverseAngstrom> inverse_angstrom_quantity( 1.0/angstrom );

  TEST_EQUALITY_CONST( inverse_angstrom_quantity.value(), 1.0 );

  inverse_angstrom_quantity = 2.0/angstrom;

  TEST_EQUALITY_CONST( inverse_angstrom_quantity.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse angstrom unit can be initialized from cgs, si units
TEUCHOS_UNIT_TEST( InverseAngstromUnit, initialize_from_cgs_si )
{
  quantity<InverseAngstrom> inverse_angstrom_cgs( 1.0/cgs::centimeter );

  quantity<InverseAngstrom> inverse_angstrom_si( 1.0/si::meter );

  TEST_EQUALITY_CONST( inverse_angstrom_cgs.value(), 1e-8 );
  TEST_EQUALITY_CONST( inverse_angstrom_si.value(), 1e-10 );
}

//---------------------------------------------------------------------------//
// end tstInverseAngstromUnit.cpp
//---------------------------------------------------------------------------//
