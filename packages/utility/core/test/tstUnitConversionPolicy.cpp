//---------------------------------------------------------------------------//
//!
//! \file   tstUnitConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Unit conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitConversionPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that inverse Angstrom can be converted to and from native units
TEUCHOS_UNIT_TEST( InverseAngstromConversionPolicy, convert )
{
  double inverse_length = 1.0; // native inverse length (1/cm)

  Utility::InverseAngstromConversionPolicy::convertFromNativeUnits( 
							      inverse_length );

  TEST_EQUALITY_CONST( inverse_length, 1e-8 );

  Utility::InverseAngstromConversionPolicy::convertToNativeUnits( 
							      inverse_length );

  TEST_EQUALITY_CONST( inverse_length, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that inverse cm can be converted to and from native units
TEUCHOS_UNIT_TEST( InverseCentimeterConversionPolicy, convert )
{
  double inverse_length = 1.0; // native inverse length (1/cm)

  Utility::InverseCentimeterConversionPolicy::convertFromNativeUnits( 
							      inverse_length );

  TEST_EQUALITY_CONST( inverse_length, 1.0 );

  Utility::InverseCentimeterConversionPolicy::convertToNativeUnits( 
							      inverse_length );

  TEST_EQUALITY_CONST( inverse_length, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that inverse squared Angstroms can be converted to/from native units
TEUCHOS_UNIT_TEST( InverseSquareAngstromConversionPolicy, convert )
{
  double inverse_area = 1.0; // native inverse area (1/cm^2)

  Utility::InverseSquareAngstromConversionPolicy::convertFromNativeUnits(
								inverse_area );

  TEST_EQUALITY_CONST( inverse_area, 1e-16 );

  Utility::InverseSquareAngstromConversionPolicy::convertToNativeUnits(
								inverse_area );

  TEST_EQUALITY_CONST( inverse_area, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that inverse square cm can be converted to/from native units
TEUCHOS_UNIT_TEST( InverseSquareCentimeterConversionPolicy, convert )
{
  double inverse_area = 1.0; // native inverse area (1/cm^2)

  Utility::InverseSquareCentimeterConversionPolicy::convertFromNativeUnits(
								inverse_area );

  TEST_EQUALITY_CONST( inverse_area, 1.0 );

  Utility::InverseSquareCentimeterConversionPolicy::convertToNativeUnits(
								inverse_area );

  TEST_EQUALITY_CONST( inverse_area, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that atomic unitless momentum can be converted to/from native units
TEUCHOS_UNIT_TEST( AtomicDimensionlessMomentumConversionPolicy, convert )
{
  double unitless_momentum = 1.0; // native unitless momentum (p/(me*c))

  Utility::AtomicDimensionlessMomentumConversionPolicy::convertFromNativeUnits(
							   unitless_momentum );

  TEST_EQUALITY_CONST( unitless_momentum, 
		       Utility::PhysicalConstants::inverse_fine_structure_constant );

  Utility::AtomicDimensionlessMomentumConversionPolicy::convertToNativeUnits(
							   unitless_momentum );

  TEST_EQUALITY_CONST( unitless_momentum, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that native unitless momentum can be converted to/from native units
TEUCHOS_UNIT_TEST( MeCDimensionlessMomentumConversionPolicy, convert )
{
  double unitless_momentum = 1.0; // native unitless momentum (p/(me*c))

  Utility::MeCDimensionlessMomentumConversionPolicy::convertFromNativeUnits(
							   unitless_momentum );

  TEST_EQUALITY_CONST( unitless_momentum, 1.0 );

  Utility::MeCDimensionlessMomentumConversionPolicy::convertToNativeUnits(
							   unitless_momentum );

  TEST_EQUALITY_CONST( unitless_momentum, 1.0 );
}
	
//---------------------------------------------------------------------------//
// end tstUnitConversionPolicy.cpp
//---------------------------------------------------------------------------//
