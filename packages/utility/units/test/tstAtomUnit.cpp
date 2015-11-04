//---------------------------------------------------------------------------//
//!
//! \file   tstAtomUnit.cpp
//! \author Alex Robinson
//! \brief  The atom unit unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/amount.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_AtomUnit.hpp"

using namespace Utility::Units;
using boost::units::quantity;
namespace si = boost::units::si;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the atom unit can be initialized
TEUCHOS_UNIT_TEST( AtomUnit, initialize )
{
  quantity<Atom> amount( 1.0*atom );

  TEST_EQUALITY_CONST( amount.value(), 1.0 );

  amount = 2.0*atom;

  TEST_EQUALITY_CONST( amount.value(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the atom unit can be initialized from si units
TEUCHOS_UNIT_TEST( AtomUnit, initialize_from_si )
{
  quantity<Atom> amount( 1.0*si::mole );

  TEST_FLOATING_EQUALITY( amount.value(), 6.022140857e23, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the si units can be initialized from the atom unit
TEUCHOS_UNIT_TEST( AtomUnit, initialize_si )
{
  quantity<si::amount> amount( 1.0*atom );

  TEST_FLOATING_EQUALITY( amount.value(), 1.0/6.022140857e23, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstAtomUnit.cpp
//---------------------------------------------------------------------------//
