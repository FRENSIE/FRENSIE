//---------------------------------------------------------------------------//
//!
//! \file   tstInverseMeCMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse me*c momentum unit unit tests
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
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_MeCMomentumUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

BOOST_UNITS_STATIC_CONSTANT(si_momentum,boost::units::si::momentum);
BOOST_UNITS_STATIC_CONSTANT(cgs_momentum,boost::units::cgs::momentum);

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse me*c momentum unit can be initialized
BOOST_AUTO_TEST_CASE( initialize )
{
  boost::units::quantity<Utility::Units::InverseMeCMomentum> inverse_momentum( 1.0*inverse_mec_momentum );

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0*inverse_mec_momentum;

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse me*c momentum unit can be initialized from me*c
BOOST_AUTO_TEST_CASE( initialize_from_mec_momentum )
{
  boost::units::quantity<Utility::Units::InverseMeCMomentum> inverse_momentum( 1.0/mec_momentum );

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0/mec_momentum;

  BOOST_CHECK_EQUAL( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse me*c momentum unit can be initialized from cgs, si
BOOST_AUTO_TEST_CASE( initialize_from_cgs_si )
{
  boost::units::quantity<Utility::Units::InverseMeCMomentum> inverse_momentum_si( 1.0/si_momentum );

  boost::units::quantity<Utility::Units::InverseMeCMomentum> inverse_momentum_cgs( 1.0/cgs_momentum );

  BOOST_CHECK_CLOSE_FRACTION( inverse_momentum_si.value(),
                              2.7309244865637114e-22,
                              1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( inverse_momentum_cgs.value(),
                              2.7309244865637114e-17,
                              1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseMeCMomentumUnit.cpp
//---------------------------------------------------------------------------//
