//---------------------------------------------------------------------------//
//!
//! \file   tstInverseCentimeterUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse centimeter unit
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse centimeter unit can be initialized
TEUCHOS_UNIT_TEST( InverseCentimeterUnit, initialize )
{
  quantity<InverseCentimeter> inverse_cm( 1.0*inverse_centimeter );

  TEST_EQUALITY_CONST( inverse_cm.value(), 1.0 );

  inverse_cm = 2.0*inverse_centimeter;

  TEST_EQUALITY_CONST( inverse_cm.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse centimeter unit can be initialize from cgs, si units
TEUCHOS_UNIT_TEST( InverseCentimeterUnit, initialize_from_cgs_si )
{
  quantity<InverseCentimeter> inverse_cm_cgs( 1.0/cgs::centimeter );

  quantity<InverseCentimeter> inverse_cm_si( 1.0/si::meter );

  TEST_EQUALITY_CONST( inverse_cm_cgs.value(), 1.0 );
  TEST_EQUALITY_CONST( inverse_cm_si.value(), 0.01 );
}

//---------------------------------------------------------------------------//
// end tstInverseCentimeterUnit.cpp
//---------------------------------------------------------------------------//
