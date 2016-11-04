//---------------------------------------------------------------------------//
//!
//! \file   tstInverseMeCMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse me*c momentum unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseMeCMomentumUnit.hpp"
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
// Check that the inverse me*c momentum unit can be initialized
TEUCHOS_UNIT_TEST( InverseMeCMomentumUnit, initialize )
{
  quantity<InverseMeCMomentum> inverse_momentum( 1.0*inverse_mec_momentum );

  TEST_EQUALITY_CONST( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0*inverse_mec_momentum;

  TEST_EQUALITY_CONST( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse me*c momentum unit can be initialized from me*c
TEUCHOS_UNIT_TEST( InverseMeCMomentumUnit, initialize_from_mec_momentum )
{
  quantity<InverseMeCMomentum> inverse_momentum( 1.0/mec_momentum );

  TEST_EQUALITY_CONST( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0/mec_momentum;

  TEST_EQUALITY_CONST( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse me*c momentum unit can be initialized from cgs, si
TEUCHOS_UNIT_TEST( InverseMeCMomentumUnit, initialize_from_cgs_si )
{
  quantity<InverseMeCMomentum> inverse_momentum_si( 1.0/si_momentum );

  quantity<InverseMeCMomentum> inverse_momentum_cgs( 1.0/cgs_momentum );

  TEST_FLOATING_EQUALITY( inverse_momentum_si.value(),
			  2.7309244865637114e-22,
			  1e-15 );
  TEST_FLOATING_EQUALITY( inverse_momentum_cgs.value(),
			  2.7309244865637114e-17,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseMeCMomentumUnit.cpp
//---------------------------------------------------------------------------//
