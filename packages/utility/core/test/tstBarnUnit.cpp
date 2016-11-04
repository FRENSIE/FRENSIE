//---------------------------------------------------------------------------//
//!
//! \file   tstBarnUnit.cpp
//! \author Alex Robinson
//! \brief  The barn unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/area.hpp>
#include <boost/units/systems/si/area.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_BarnUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the barn unit can be initialized
TEUCHOS_UNIT_TEST( BarnUnit, initialize )
{
  quantity<Barn> barn_area( 1.0*barn );

  TEST_EQUALITY_CONST( barn_area.value(), 1.0 );

  barn_area = 2.0*barn;

  TEST_EQUALITY_CONST( barn_area.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the barn unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( BarnUnit, initialize_from_cgs_si )
{
  quantity<Barn> barn_area_cgs( 1.0*cgs::square_centimeter );

  quantity<Barn> barn_area_si( 1.0*si::square_meter );

  TEST_EQUALITY_CONST( barn_area_cgs.value(), 1e24 );
  TEST_EQUALITY_CONST( barn_area_si.value(), 1e28 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the barn unit
TEUCHOS_UNIT_TEST( BarnUnit, initialize_cgs_si )
{
  quantity<cgs::area> cgs_area( 1.0*barn );

  quantity<si::area> si_area( 1.0*barn );

  TEST_EQUALITY_CONST( cgs_area.value(), 1e-24 );
  TEST_EQUALITY_CONST( si_area.value(), 1e-28 );
}

//---------------------------------------------------------------------------//
// end tstBarnUnit.cpp
//---------------------------------------------------------------------------//
