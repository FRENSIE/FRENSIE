//---------------------------------------------------------------------------//
//!
//! \file   tstInverseAngstromUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse Angstrom unit unit tests
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
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_AngstromUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse angstrom unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::InverseAngstrom> inverse_angstrom_quantity( 1.0*inverse_angstrom );

  BOOST_CHECK_EQUAL( inverse_angstrom_quantity.value(), 1.0 );

  inverse_angstrom_quantity = 2.0*inverse_angstrom;

  BOOST_CHECK_EQUAL( inverse_angstrom_quantity.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse angstrom unit can be initialized from the Angstrom
BOOST_AUTO_TEST_CASE( initialize_from_angstrom )
{
  boost::units::quantity<Utility::Units::InverseAngstrom> inverse_angstrom_quantity( 1.0/angstrom );

  BOOST_CHECK_EQUAL( inverse_angstrom_quantity.value(), 1.0 );

  inverse_angstrom_quantity = 2.0/angstrom;

  BOOST_CHECK_EQUAL( inverse_angstrom_quantity.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse angstrom unit can be initialized from cgs, si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::InverseAngstrom> inverse_angstrom_cgs( 1.0/cgs::centimeter );

  boost::units::quantity<Utility::Units::InverseAngstrom> inverse_angstrom_si( 1.0/si::meter );

  BOOST_CHECK_EQUAL( inverse_angstrom_cgs.value(), 1e-8 );
  BOOST_CHECK_EQUAL( inverse_angstrom_si.value(), 1e-10 );
}

//---------------------------------------------------------------------------//
// end tstInverseAngstromUnit.cpp
//---------------------------------------------------------------------------//
