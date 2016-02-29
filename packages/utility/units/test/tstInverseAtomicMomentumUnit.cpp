//---------------------------------------------------------------------------//
//!
//! \file   tstInverseAtomicMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The inverse atomic momentum unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_AtomicMomentumUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

BOOST_UNITS_STATIC_CONSTANT(si_momentum,boost::units::si::momentum);
BOOST_UNITS_STATIC_CONSTANT(cgs_momentum,boost::units::cgs::momentum);

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse atomic momentum unit can be initialized
TEUCHOS_UNIT_TEST( InverseAtomicMomentumUnit, initialize )
{
  quantity<InverseAtomicMomentum> 
    inverse_momentum( 1.0*inverse_atomic_momentum );

  TEST_EQUALITY_CONST( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0*inverse_atomic_momentum;

  TEST_EQUALITY_CONST( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse atomic momentum unit can be initialized from a.mom.
TEUCHOS_UNIT_TEST( InverseAtomicMomentumUnit, initialize_from_atomic_momentum )
{
  quantity<InverseAtomicMomentum> inverse_momentum( 1.0/atomic_momentum );

  TEST_EQUALITY_CONST( inverse_momentum.value(), 1.0 );

  inverse_momentum = 2.0/atomic_momentum;

  TEST_EQUALITY_CONST( inverse_momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the inverse atomic momentum unit can be initialized from cgs, si
TEUCHOS_UNIT_TEST( InverseAtomicMomentumUnit, initialize_from_cgs_si )
{
  quantity<InverseAtomicMomentum> inverse_momentum_si( 1.0/si_momentum );

  quantity<InverseAtomicMomentum> inverse_momentum_cgs( 1.0/cgs_momentum );

  TEST_FLOATING_EQUALITY( inverse_momentum_si.value(),
			  1.992851882e-24,
			  1e-15 );
  TEST_FLOATING_EQUALITY( inverse_momentum_cgs.value(),
			  1.992851882e-19,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseAtomicMomentumUnit.cpp
//---------------------------------------------------------------------------//
