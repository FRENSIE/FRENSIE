//---------------------------------------------------------------------------//
//!
//! \file   tstMeCMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The me*c momentum unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_MeCMomentumUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

BOOST_UNITS_STATIC_CONSTANT(si_momentum,boost::units::si::momentum);
BOOST_UNITS_STATIC_CONSTANT(cgs_momentum,boost::units::cgs::momentum);

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the me*c momentum unit can be initialized
TEUCHOS_UNIT_TEST( MeCMomentum, initialize )
{
  quantity<MeCMomentum> momentum( 1.0*mec_momentum );

  TEST_EQUALITY_CONST( momentum.value(), 1.0 );

  momentum = 2.0*mec_momentum;

  TEST_EQUALITY_CONST( momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the me*c momentum unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( MeCMomentum, initialize_from_cgs_si )
{
  quantity<MeCMomentum> mec_momentum_si( 1.0*si_momentum );

  quantity<MeCMomentum> mec_momentum_cgs( 1.0*cgs_momentum );

  TEST_FLOATING_EQUALITY( mec_momentum_si.value(),
			  3.6617636442166426e+21,
			  1e-15 );
  TEST_FLOATING_EQUALITY( mec_momentum_cgs.value(),
			  3.6617636442166426e+16,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the me*c unit
TEUCHOS_UNIT_TEST( MeCMomentum, initialize_cgs_si )
{
  quantity<cgs::momentum> cgs_momentum_q( 1.0*mec_momentum );

  quantity<si::momentum> si_momentum_q( 1.0*mec_momentum );

  TEST_FLOATING_EQUALITY( cgs_momentum_q.value(), 
			  2.7309244865637114e-17,
			  1e-15 );
  TEST_FLOATING_EQUALITY( si_momentum_q.value(),
			  2.7309244865637114e-22,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstMeCMomentumUnit.cpp
//---------------------------------------------------------------------------//
