//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicMassUnit.cpp
//! \author Alex Robinson
//! \brief  The atomic mass unit unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/mass.hpp>
#include <boost/units/systems/si/mass.hpp>

// FRENSIE Includes
#include "Utility_AtomicMassUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the atomic mass unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::AtomicMass> mass( 1.0*amu );

  BOOST_CHECK_EQUAL( mass.value(), 1.0 );

  mass = 2.0*amu;

  BOOST_CHECK_EQUAL( mass.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic mass unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::AtomicMass> mass_cgs( 1.0*cgs::gram );

  boost::units::quantity<Utility::Units::AtomicMass> mass_si( 1.0*si::kilogram );

  BOOST_CHECK_CLOSE_FRACTION( mass_cgs.value(),
                              6.0221408585491615e+23,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( mass_si.value(),
                              6.0221408585491615e+26,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the atomic mass u.
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::mass> cgs_mass( 1.0*amu );

  boost::units::quantity<si::mass> si_mass( 1.0*amu );

  BOOST_CHECK_CLOSE_FRACTION( cgs_mass.value(),
                              1.660539040e-24,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( si_mass.value(),
                              1.660539040e-27,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// end tstAtomicMassUnit.cpp
//---------------------------------------------------------------------------//
