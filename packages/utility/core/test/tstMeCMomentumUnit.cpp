//---------------------------------------------------------------------------//
//!
//! \file   tstMeCMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The me*c momentum unit unit tests
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
#include "Utility_MeCMomentumUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

BOOST_UNITS_STATIC_CONSTANT(si_momentum,boost::units::si::momentum);
BOOST_UNITS_STATIC_CONSTANT(cgs_momentum,boost::units::cgs::momentum);

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the me*c momentum unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::MeCMomentum> momentum( 1.0*mec_momentum );

  BOOST_CHECK_EQUAL( momentum.value(), 1.0 );

  momentum = 2.0*mec_momentum;

  BOOST_CHECK_EQUAL( momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the me*c momentum unit can be initialized from cgs and si units
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::MeCMomentum> mec_momentum_si( 1.0*si_momentum );

  boost::units::quantity<Utility::Units::MeCMomentum> mec_momentum_cgs( 1.0*cgs_momentum );

  BOOST_CHECK_CLOSE_FRACTION( mec_momentum_si.value(),
                              3.6617636442166426e+21,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( mec_momentum_cgs.value(),
                              3.6617636442166426e+16,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the me*c unit
BOOST_AUTO_TEST_CASE( initialize_cgs_si )
{
  boost::units::quantity<cgs::momentum> cgs_momentum_q( 1.0*mec_momentum );

  boost::units::quantity<si::momentum> si_momentum_q( 1.0*mec_momentum );

  BOOST_CHECK_CLOSE_FRACTION( cgs_momentum_q.value(),
                              2.7309244865637114e-17,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( si_momentum_q.value(),
                              2.7309244865637114e-22,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// end tstMeCMomentumUnit.cpp
//---------------------------------------------------------------------------//
