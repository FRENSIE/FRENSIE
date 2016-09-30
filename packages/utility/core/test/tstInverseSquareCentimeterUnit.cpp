//---------------------------------------------------------------------------//
//!
//! \file   tstInverseSquareCentimeterUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse square centimeter unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/area.hpp>
#include <boost/units/systems/si/area.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseSquareCentimeterUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse square centimeter unit can be initialized
TEUCHOS_UNIT_TEST( InverseSquareCentimeterUnit, initialize )
{
  quantity<InverseSquareCentimeter>
    inverse_sqr_centimeter( 1.0*inverse_square_centimeter );

  TEST_EQUALITY_CONST( inverse_sqr_centimeter.value(), 1.0 );

  inverse_sqr_centimeter = 2.0*inverse_square_centimeter;

  TEST_EQUALITY_CONST( inverse_sqr_centimeter.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. cm unit can be initialized from the inv. cm unit
TEUCHOS_UNIT_TEST( InverseSquareCentimeterUnit, initialize_from_inv_cm )
{
  quantity<InverseSquareCentimeter>
    inverse_sqr_centimeter( 1.0*inverse_centimeter*inverse_centimeter );

  TEST_EQUALITY_CONST( inverse_sqr_centimeter.value(), 1.0 );

  inverse_sqr_centimeter = 2.0*inverse_centimeter*inverse_centimeter;

  TEST_EQUALITY_CONST( inverse_sqr_centimeter.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. cm unit can be initialized from cgs, si units
TEUCHOS_UNIT_TEST( InverseSquareCentimeterUnit, initialize_from_cgs_si )
{
  quantity<InverseSquareCentimeter>
    inverse_sqr_centimeter_cgs( 1.0/cgs::square_centimeter );

  quantity<InverseSquareCentimeter>
    inverse_sqr_centimeter_si( 1.0/si::square_meter );

  TEST_EQUALITY_CONST( inverse_sqr_centimeter_cgs.value(), 1.0 );
  TEST_EQUALITY_CONST( inverse_sqr_centimeter_si.value(), 1e-4 );
}

//---------------------------------------------------------------------------//
// end tstInverseSquareCentimeterUnit.cpp
//---------------------------------------------------------------------------//
