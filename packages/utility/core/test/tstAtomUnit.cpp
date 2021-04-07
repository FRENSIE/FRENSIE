//---------------------------------------------------------------------------//
//!
//! \file   tstAtomUnit.cpp
//! \author Alex Robinson
//! \brief  The atom unit unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/amount.hpp>

// FRENSIE Includes
#include "Utility_AtomUnit.hpp"
#include "Utility_PhysicalConstants.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the atom unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::Atom> amount( 1.0*atom );

  BOOST_CHECK_EQUAL( amount.value(), 1.0 );

  amount = 2.0*atom;

  BOOST_CHECK_EQUAL( amount.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the atom unit can be initialized from si units
BOOST_AUTO_TEST_CASE( initialize_from_si )
{
  boost::units::quantity<Utility::Units::Atom> amount( 1.0*si::mole );

  BOOST_CHECK_CLOSE_FRACTION( amount.value(),
                              Utility::PhysicalConstants::avogadro_constant,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the si units can be initialized from the atom unit
BOOST_AUTO_TEST_CASE( initialize_si )
{
  boost::units::quantity<si::amount> amount( 1.0*atom );

  BOOST_CHECK_CLOSE_FRACTION( amount.value(),
                              1.0/Utility::PhysicalConstants::avogadro_constant,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// end tstAtomUnit.cpp
//---------------------------------------------------------------------------//
