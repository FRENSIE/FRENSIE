//---------------------------------------------------------------------------//
//!
//! \file   tstInverseAtomicMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse atomic momentum unit unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// FRENSIE Includes
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_AtomicMomentumUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

BOOST_UNITS_STATIC_CONSTANT(si_momentum,boost::units::si::momentum);
BOOST_UNITS_STATIC_CONSTANT(cgs_momentum,boost::units::cgs::momentum);

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse atomic momentum unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::InverseAtomicMomentum>
    inverse_momentum( 1.0*inverse_atomic_momentum );

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0*inverse_atomic_momentum;

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse atomic momentum unit can be initialized from a.mom.
BOOST_AUTO_TEST_CASE( initialize_from_atomic_momentum )
{
  boost::units::quantity<Utility::Units::InverseAtomicMomentum> inverse_momentum( 1.0/atomic_momentum );

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0/atomic_momentum;

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse atomic momentum unit can be initialized from cgs, si
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::InverseAtomicMomentum> inverse_momentum_si( 1.0/si_momentum );

  boost::units::quantity<Utility::Units::InverseAtomicMomentum> inverse_momentum_cgs( 1.0/cgs_momentum );

  BOOST_CHECK_CLOSE_FRACTION( inverse_momentum_si.value(),
                              1.992851882e-24,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( inverse_momentum_cgs.value(),
                              1.992851882e-19,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseAtomicMomentumUnit.cpp
//---------------------------------------------------------------------------//
