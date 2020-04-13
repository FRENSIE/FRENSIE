//---------------------------------------------------------------------------//
//!
//! \file   tstInverseCentimeterUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse centimeter unit
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse centimeter unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::InverseCentimeter> inverse_cm( 1.0*inverse_centimeter );

  BOOST_CHECK_EQUAL( inverse_cm.value(), 1.0 );

  inverse_cm = 2.0*inverse_centimeter;

  BOOST_CHECK_EQUAL( inverse_cm.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse centimeter unit can be initialize from cgs, si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::InverseCentimeter> inverse_cm_cgs( 1.0/cgs::centimeter );

  boost::units::quantity<Utility::Units::InverseCentimeter> inverse_cm_si( 1.0/si::meter );

  BOOST_CHECK_EQUAL( inverse_cm_cgs.value(), 1.0 );
  BOOST_CHECK_EQUAL( inverse_cm_si.value(), 0.01 );
}

//---------------------------------------------------------------------------//
// end tstInverseCentimeterUnit.cpp
//---------------------------------------------------------------------------//
