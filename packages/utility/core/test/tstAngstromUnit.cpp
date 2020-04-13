//---------------------------------------------------------------------------//
//!
//! \file   tstAngstromUnit.cpp
//! \author Alex Robinson
//! \brief  The Angstrom unit unit tests
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
#include "Utility_AngstromUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the angstrom unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::Angstrom> angstrom_length( 1.0*angstrom );

  BOOST_CHECK_EQUAL( angstrom_length.value(), 1.0 );

  angstrom_length = 2.0*angstrom;

  BOOST_CHECK_EQUAL( angstrom_length.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the angstrom unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::Angstrom> angstrom_length_cgs( 1.0*cgs::centimeter );

  boost::units::quantity<Utility::Units::Angstrom> angstrom_length_si( 1.0*si::meter );

  BOOST_CHECK_EQUAL( angstrom_length_cgs.value(), 1e8 );
  BOOST_CHECK_EQUAL( angstrom_length_si.value(), 1e10 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the angstrom unit
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::length> centimeter_length( 1.0*angstrom );

  boost::units::quantity<si::length> meter_length( 1.0*angstrom );

  BOOST_CHECK_EQUAL( centimeter_length.value(), 1e-8 );
  BOOST_CHECK_EQUAL( meter_length.value(), 1e-10 );
}


//---------------------------------------------------------------------------//
// end tstAngstromUnit.cpp
//---------------------------------------------------------------------------//
