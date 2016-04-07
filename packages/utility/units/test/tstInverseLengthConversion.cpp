//---------------------------------------------------------------------------//
//!
//! \file   tstInverseLengthConversion.cpp
//! \author Alex Robinson
//! \brief  The inverse length conversion unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse length units can be converted
TEUCHOS_UNIT_TEST( InverseLengthConversion, convert )
{
  quantity<InverseAngstrom> inverse_angstrom_q( 1.0*inverse_centimeter );

  quantity<InverseCentimeter> inverse_centimeter_q( 1.0*inverse_angstrom );

  TEST_EQUALITY_CONST( inverse_angstrom_q.value(), 1e-8 );
  TEST_EQUALITY_CONST( inverse_centimeter_q.value(), 1e8 );
}

//---------------------------------------------------------------------------//
// end tstInverseLengthConversion.cpp
//---------------------------------------------------------------------------//
