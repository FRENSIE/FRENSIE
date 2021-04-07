//---------------------------------------------------------------------------//
//!
//! \file   tstInverseLengthConversion.cpp
//! \author Alex Robinson
//! \brief  The inverse length conversion unit tests
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
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_InverseCentimeterUnit.hpp"

using namespace Utility::Units;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse length units can be converted
BOOST_AUTO_TEST_CASE( convert )
{
  boost::units::quantity<Utility::Units::InverseAngstrom> inverse_angstrom_q( 1.0*inverse_centimeter );

  boost::units::quantity<Utility::Units::InverseCentimeter> inverse_centimeter_q( 1.0*inverse_angstrom );

  BOOST_CHECK_EQUAL( inverse_angstrom_q.value(), 1e-8 );
  BOOST_CHECK_EQUAL( inverse_centimeter_q.value(), 1e8 );
}

//---------------------------------------------------------------------------//
// end tstInverseLengthConversion.cpp
//---------------------------------------------------------------------------//
