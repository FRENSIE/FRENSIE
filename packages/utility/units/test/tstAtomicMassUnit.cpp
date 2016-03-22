//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicMassUnit.cpp
//! \author Alex Robinson
//! \brief  The atomic mass unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/mass.hpp>
#include <boost/units/systems/si/mass.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_AtomicMassUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the atomic mass unit can be initialized
TEUCHOS_UNIT_TEST( AtomicMassUnit, initialize )
{
  quantity<AtomicMass> mass( 1.0*amu );

  TEST_EQUALITY_CONST( mass.value(), 1.0 );

  mass = 2.0*amu;

  TEST_EQUALITY_CONST( mass.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic mass unit can be initialized from cgs and si units
TEUCHOS_UNIT_TEST( AtomicMassUnit, initialize_from_cgs_si )
{
  quantity<AtomicMass> mass_cgs( 1.0*cgs::gram );

  quantity<AtomicMass> mass_si( 1.0*si::kilogram );

  TEST_FLOATING_EQUALITY( mass_cgs.value(), 
			  6.0221408585491615e+23,
			  1e-15 );
  TEST_FLOATING_EQUALITY( mass_si.value(),
			  6.0221408585491615e+26,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cgs and si units can be initialized from the atomic mass u.
TEUCHOS_UNIT_TEST( AtomicMassUnit, initialize_cgs_si )
{
  quantity<cgs::mass> cgs_mass( 1.0*amu );

  quantity<si::mass> si_mass( 1.0*amu );

  TEST_FLOATING_EQUALITY( cgs_mass.value(), 
			  1.660539040e-24,
			  1e-15 );
  TEST_FLOATING_EQUALITY( si_mass.value(),
			  1.660539040e-27,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstAtomicMassUnit.cpp
//---------------------------------------------------------------------------//
