//---------------------------------------------------------------------------//
//!
//! \file   tstUnitlessMomentumUnit.cpp
//! \author Alex Robinson
//! \brief  The atomic momentum unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
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
// Check that the atomic momentum unit can be initialized
TEUCHOS_UNIT_TEST( AtomicMomentum, initialize )
{
  quantity<AtomicMomentum> momentum( 1.0*atomic_momentum );

  TEST_EQUALITY_CONST( momentum.value(), 1.0 );

  momentum = 2.0*atomic_momentum;

  TEST_EQUALITY_CONST( momentum.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic momentum unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( AtomicMomentum,  initialize_from_cgs_si )
{
  quantity<AtomicMomentum> atomic_momentum_si( 1.0*si_momentum );

  quantity<AtomicMomentum> atomic_momentum_cgs( 1.0*cgs_momentum );

  TEST_FLOATING_EQUALITY( atomic_momentum_si.value(), 
			  5.017934393580787e+23,
			  1e-15 );
  TEST_FLOATING_EQUALITY( atomic_momentum_cgs.value(),
			  5.017934393580787e+18,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the atomic unit
TEUCHOS_UNIT_TEST( AtomicMomentum, initialize_cgs_si )
{
  quantity<cgs::momentum> cgs_momentum_q( 1.0*atomic_momentum );
  
  quantity<si::momentum> si_momentum_q( 1.0*atomic_momentum );

  TEST_FLOATING_EQUALITY( cgs_momentum_q.value(),
			  1.992851882e-19,
			  1e-15 );
  TEST_FLOATING_EQUALITY( si_momentum_q.value(),
			  1.992851882e-24,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstUnitlessMomentumUnit.cpp
//---------------------------------------------------------------------------//
