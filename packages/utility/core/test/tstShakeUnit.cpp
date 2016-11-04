//---------------------------------------------------------------------------//
//!
//! \file   tstShakeUnit.cpp
//! \author Alex Robinson
//! \brief  The shake unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/time.hpp>
#include <boost/units/systems/si/time.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ShakeUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the shake unit can be initialized
TEUCHOS_UNIT_TEST( ShakeUnit, initialize )
{
  quantity<Shake> time( 1.0*shake );

  TEST_EQUALITY_CONST( time.value(), 1.0 );

  time = 2.0*shake;

  TEST_EQUALITY_CONST( time.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the shake unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( ShakeUnit, initialize_from_cgs_si )
{
  quantity<Shake> shake_time_cgs( 1.0*cgs::second );

  quantity<Shake> shake_time_si( 1.0*si::second );

  TEST_EQUALITY_CONST( shake_time_cgs.value(), 1e8 );
  TEST_EQUALITY_CONST( shake_time_cgs.value(), 1e8 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the shake unit
TEUCHOS_UNIT_TEST( ShakeUnit, initialize_cgs_si )
{
  quantity<cgs::time> cgs_time( 1.0*shake );

  quantity<si::time> si_time( 1.0*shake );

  TEST_EQUALITY_CONST( cgs_time.value(), 1e-8 );
  TEST_EQUALITY_CONST( si_time.value(), 1e-8 );
}

//---------------------------------------------------------------------------//
// end tstShakeUnit.cpp
//---------------------------------------------------------------------------//

