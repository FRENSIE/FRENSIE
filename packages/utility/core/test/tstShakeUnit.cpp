//---------------------------------------------------------------------------//
//!
//! \file   tstShakeUnit.cpp
//! \author Alex Robinson
//! \brief  The shake unit unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/time.hpp>
#include <boost/units/systems/si/time.hpp>

// FRENSIE Includes
#include "Utility_ShakeUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the shake unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::Shake> time( 1.0*shake );

  BOOST_CHECK_EQUAL( time.value(), 1.0 );

  time = 2.0*shake;

  BOOST_CHECK_EQUAL( time.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the shake unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::Shake> shake_time_cgs( 1.0*cgs::second );

  boost::units::quantity<Utility::Units::Shake> shake_time_si( 1.0*si::second );

  BOOST_CHECK_EQUAL( shake_time_cgs.value(), 1e8 );
  BOOST_CHECK_EQUAL( shake_time_cgs.value(), 1e8 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the shake unit
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::time> cgs_time( 1.0*shake );

  boost::units::quantity<si::time> si_time( 1.0*shake );

  BOOST_CHECK_EQUAL( cgs_time.value(), 1e-8 );
  BOOST_CHECK_EQUAL( si_time.value(), 1e-8 );
}

//---------------------------------------------------------------------------//
// end tstShakeUnit.cpp
//---------------------------------------------------------------------------//

