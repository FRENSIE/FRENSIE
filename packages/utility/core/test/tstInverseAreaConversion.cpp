//---------------------------------------------------------------------------//
//!
//! \file   tstInverseAreaConversion.cpp
//! \author Alex Robinson
//! \brief  The inverse area conversion unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_InverseSquareCentimeterUnit.hpp"

using namespace Utility::Units;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse area units can be converted
BOOST_AUTO_TEST_CASE( convert )
{
  boost::units::quantity<Utility::Units::InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0*inverse_square_centimeter );

  boost::units::quantity<Utility::Units::InverseSquareCentimeter>
    inverse_sqr_centimeter( 1.0*inverse_square_angstrom );

  BOOST_CHECK_CLOSE_FRACTION( inverse_sqr_angstrom.value(), 1e-16, 1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( inverse_sqr_centimeter.value(), 1e16, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseAreaConversion.cpp
//---------------------------------------------------------------------------//
