//---------------------------------------------------------------------------//
//!
//! \file   tstBarnUnit.cpp
//! \author Alex Robinson
//! \brief  The barn unit unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/area.hpp>
#include <boost/units/systems/si/area.hpp>

// FRENSIE Includes
#include "Utility_BarnUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the barn unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::Barn> barn_area( 1.0*barn );

  BOOST_CHECK_EQUAL( barn_area.value(), 1.0 );

  barn_area = 2.0*barn;

  BOOST_CHECK_EQUAL( barn_area.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the barn unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::Barn> barn_area_cgs( 1.0*cgs::square_centimeter );

  boost::units::quantity<Utility::Units::Barn> barn_area_si( 1.0*si::square_meter );

  BOOST_CHECK_EQUAL( barn_area_cgs.value(), 1e24 );
  BOOST_CHECK_EQUAL( barn_area_si.value(), 1e28 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the barn unit
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::area> cgs_area( 1.0*barn );

  boost::units::quantity<si::area> si_area( 1.0*barn );

  BOOST_CHECK_EQUAL( cgs_area.value(), 1e-24 );
  BOOST_CHECK_EQUAL( si_area.value(), 1e-28 );
}

//---------------------------------------------------------------------------//
// end tstBarnUnit.cpp
//---------------------------------------------------------------------------//
