//---------------------------------------------------------------------------//
//!
//! \file   tstInverseSquareAngstromUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse square Angstrom unit unit tests
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
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_AngstromUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse square angstrom unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0*inverse_square_angstrom );

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom.value(), 1.0 );

  inverse_sqr_angstrom = 2.0*inverse_square_angstrom;

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. angs. unit can be initialized from the inv. angs.
BOOST_AUTO_TEST_CASE( initialize_from_inv_angstrom )
{
  boost::units::quantity<Utility::Units::InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0*inverse_angstrom*inverse_angstrom );

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom.value(), 1.0 );

  inverse_sqr_angstrom = 2.0*inverse_angstrom*inverse_angstrom;

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. angs. unit can be initialized from the angs. unit
BOOST_AUTO_TEST_CASE( initialize_from_angstrom )
{
  boost::units::quantity<Utility::Units::InverseSquareAngstrom>
    inverse_sqr_angstrom( 1.0/(angstrom*angstrom) );

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom.value(), 1.0 );

  inverse_sqr_angstrom = 2.0/(angstrom*angstrom);

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inv. sqr. angs. unit can be initialized from cgs, si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::InverseSquareAngstrom>
    inverse_sqr_angstrom_cgs( 1.0/cgs::square_centimeter );

  boost::units::quantity<Utility::Units::InverseSquareAngstrom>
    inverse_sqr_angstrom_si( 1.0/si::square_meter );

  BOOST_CHECK_EQUAL( inverse_sqr_angstrom_cgs.value(), 1e-16 );
  BOOST_CHECK_EQUAL( inverse_sqr_angstrom_si.value(), 1e-20 );
}

//---------------------------------------------------------------------------//
// end tstInverseSquareAngstrom.cpp
//---------------------------------------------------------------------------//
