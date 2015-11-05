//---------------------------------------------------------------------------//
//!
//! \file   tstInverseMomentumConversion.cpp
//! \author Alex Robinson
//! \brief  The inverse momentum conversion unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InverseMomentumUnits.hpp"
#include "Utility_RawPhysicalConstants.hpp"

using namespace Utility::Units;
using boost::units::quantity;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse momentum units can be converted
TEUCHOS_UNIT_TEST( InverseMomentumConversion, convert )
{
  quantity<InverseAtomicMomentum> 
    inverse_atomic_momentum_q( 1.0*inverse_mec_momentum );

  quantity<InverseMeCMomentum>
    inverse_mec_momentum_q( 1.0*inverse_atomic_momentum );

  TEST_FLOATING_EQUALITY( 
			inverse_atomic_momentum_q.value(), 
			Utility::RawPhysicalConstants::fine_structure_constant,
			1e-15 );
  TEST_FLOATING_EQUALITY( 
		inverse_mec_momentum_q.value(),
		Utility::RawPhysicalConstants::inverse_fine_structure_constant,
		1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseMomentumConversion.cpp
//---------------------------------------------------------------------------//
