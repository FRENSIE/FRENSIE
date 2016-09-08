//---------------------------------------------------------------------------//
//!
//! \file   tstInverseSquareAngstromUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse square Angstrom unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/area.hpp>
#include <boost/units/systems/si/area.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_AngstromUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse square angstrom unit can be initialized
TEUCHOS_UNIT_TEST( InverseSquareAngstromUnit, initialize )
{
  quantity<InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0*inverse_square_angstrom );

  TEST_EQUALITY_CONST( inverse_sqr_angstrom.value(), 1.0 );

  inverse_sqr_angstrom = 2.0*inverse_square_angstrom;

  TEST_EQUALITY_CONST( inverse_sqr_angstrom.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. angs. unit can be initialized from the inv. angs.
TEUCHOS_UNIT_TEST( InverseSquareAngstromUnit, initialize_from_inv_angstrom )
{
  quantity<InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0*inverse_angstrom*inverse_angstrom );

  TEST_EQUALITY_CONST( inverse_sqr_angstrom.value(), 1.0 );

  inverse_sqr_angstrom = 2.0*inverse_angstrom*inverse_angstrom;

  TEST_EQUALITY_CONST( inverse_sqr_angstrom.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. angs. unit can be initialized from the angs. unit
TEUCHOS_UNIT_TEST( InverseSquareAngstromUnit, initialize_from_angstrom )
{
  quantity<InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0/(angstrom*angstrom) );

  TEST_EQUALITY_CONST( inverse_sqr_angstrom.value(), 1.0 );

  inverse_sqr_angstrom = 2.0/(angstrom*angstrom);

  TEST_EQUALITY_CONST( inverse_sqr_angstrom.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. angs. unit can be initialized from cgs, si units
TEUCHOS_UNIT_TEST( InverseSquareAngstromUnit, initialize_from_cgs_si )
{
  quantity<InverseSquareAngstrom>
    inverse_sqr_angstrom_cgs( 1.0/cgs::square_centimeter );

  quantity<InverseSquareAngstrom>
    inverse_sqr_angstrom_si( 1.0/si::square_meter );

  TEST_EQUALITY_CONST( inverse_sqr_angstrom_cgs.value(), 1e-16 );
  TEST_EQUALITY_CONST( inverse_sqr_angstrom_si.value(), 1e-20 );
}

//---------------------------------------------------------------------------//
// end tstInverseSquareAngstrom.cpp
//---------------------------------------------------------------------------//
