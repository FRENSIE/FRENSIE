//---------------------------------------------------------------------------//
//!
//! \file   tstInverseAreaConversion.cpp
//! \author Alex Robinson
//! \brief  The inverse area conversion unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_InverseSquareCentimeterUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse area units can be converted
TEUCHOS_UNIT_TEST( InverseAreaConversion, convert )
{
  quantity<InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0*inverse_square_centimeter );

  quantity<InverseSquareCentimeter>
    inverse_sqr_centimeter( 1.0*inverse_square_angstrom );

  TEST_FLOATING_EQUALITY( inverse_sqr_angstrom.value(), 1e-16, 1e-15 );
  TEST_FLOATING_EQUALITY( inverse_sqr_centimeter.value(), 1e16, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseAreaConversion.cpp
//---------------------------------------------------------------------------//
