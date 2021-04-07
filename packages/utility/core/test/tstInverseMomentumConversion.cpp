//---------------------------------------------------------------------------//
//!
//! \file   tstInverseMomentumConversion.cpp
//! \author Alex Robinson
//! \brief  The inverse momentum conversion unit tests
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
#include "Utility_InverseMomentumUnits.hpp"
#include "Utility_RawPhysicalConstants.hpp"

using namespace Utility::Units;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the inverse momentum units can be converted
BOOST_AUTO_TEST_CASE( convert )
{
  boost::units::quantity<Utility::Units::InverseAtomicMomentum>
    inverse_atomic_momentum_q( 1.0*inverse_mec_momentum );

  boost::units::quantity<Utility::Units::InverseMeCMomentum>
    inverse_mec_momentum_q( 1.0*inverse_atomic_momentum );

  BOOST_CHECK_CLOSE_FRACTION(
			inverse_atomic_momentum_q.value(),
			Utility::RawPhysicalConstants::fine_structure_constant,
			1e-15 );
  BOOST_CHECK_CLOSE_FRACTION(
		inverse_mec_momentum_q.value(),
		Utility::RawPhysicalConstants::inverse_fine_structure_constant,
		1e-15 );
}

//---------------------------------------------------------------------------//
// end tstInverseMomentumConversion.cpp
//---------------------------------------------------------------------------//
