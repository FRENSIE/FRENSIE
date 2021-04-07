//---------------------------------------------------------------------------//
//!
//! \file   tstInverseSquareCentimeterUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse square centimeter unit unit tests
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
#include "Utility_InverseSquareCentimeterUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse square centimeter unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::InverseSquareCentimeter>
    inverse_sqr_centimeter( 1.0*inverse_square_centimeter );

  BOOST_CHECK_EQUAL( inverse_sqr_centimeter.value(), 1.0 );

  inverse_sqr_centimeter = 2.0*inverse_square_centimeter;

  BOOST_CHECK_EQUAL( inverse_sqr_centimeter.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. cm unit can be initialized from the inv. cm unit
BOOST_AUTO_TEST_CASE( initialize_from_inv_cm )
{
  boost::units::quantity<Utility::Units::InverseSquareCentimeter>
    inverse_sqr_centimeter( 1.0*inverse_centimeter*inverse_centimeter );

  BOOST_CHECK_EQUAL( inverse_sqr_centimeter.value(), 1.0 );

  inverse_sqr_centimeter = 2.0*inverse_centimeter*inverse_centimeter;

  BOOST_CHECK_EQUAL( inverse_sqr_centimeter.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. cm unit can be initialized from cgs, si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::InverseSquareCentimeter>
    inverse_sqr_centimeter_cgs( 1.0/cgs::square_centimeter );

  boost::units::quantity<Utility::Units::InverseSquareCentimeter>
    inverse_sqr_centimeter_si( 1.0/si::square_meter );

  BOOST_CHECK_EQUAL( inverse_sqr_centimeter_cgs.value(), 1.0 );
  BOOST_CHECK_EQUAL( inverse_sqr_centimeter_si.value(), 1e-4 );
}

//---------------------------------------------------------------------------//
// end tstInverseSquareCentimeterUnit.cpp
//---------------------------------------------------------------------------//
