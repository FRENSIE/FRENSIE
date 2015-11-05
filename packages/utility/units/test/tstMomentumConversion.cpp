//---------------------------------------------------------------------------//
//!
//! \file   tstMomentumConversion.cpp
//! \author Alex Robinson
//! \brief  The momentum conversion unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_MomentumUnits.hpp"

using namespace Utility::Units;
using boost::units::quantity;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the momentum units can be converted
TEUCHOS_UNIT_TEST( MomentumConversion, convert )
{
  quantity<AtomicMomentum> atomic_momentum_q( 1.0*mec_momentum );

  quantity<MeCMomentum> mec_momentum_q( 1.0*atomic_momentum );

  TEST_FLOATING_EQUALITY( 
		   atomic_momentum_q.value(), 
		   Utility::PhysicalConstants::inverse_fine_structure_constant,
		   1e-15 );
  TEST_FLOATING_EQUALITY( mec_momentum_q.value(),
			  Utility::PhysicalConstants::fine_structure_constant,
			  1e-15 );
}

//---------------------------------------------------------------------------//
// end tstMomentumConversion.cpp
//---------------------------------------------------------------------------//
