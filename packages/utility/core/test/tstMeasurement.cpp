//---------------------------------------------------------------------------//
//!
//! \file   tstMeasurement.cpp
//! \author Alex Robinson
//! \brief  Measurement unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_Measurement.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a measurement can be constructed
TEUCHOS_UNIT_TEST( Measurement, constructor )
{
  // The default constructor
  Utility::Measurement<double> measurement;

  TEST_EQUALITY_CONST( measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.0 );

  // Default uncertainty constructor
  measurement = Utility::Measurement<double>( 1.0 );

  TEST_EQUALITY_CONST( measurement.getValue(), 1.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.0 );

  // Full constructor
  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  
  TEST_EQUALITY_CONST( measurement.getValue(), 1.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  // Copy constructor
  Utility::Measurement<double> measurement_2( measurement );

  TEST_EQUALITY_CONST( measurement_2.getValue(), 1.0 );
  TEST_EQUALITY_CONST( measurement_2.getUncertainty(), 0.1 );
}

//---------------------------------------------------------------------------//
// Check that the relative uncertainty can be calculated
TEUCHOS_UNIT_TEST( Measurement, getRelativeUncertainty )
{
  Utility::Measurement<double> measurement;

  TEST_EQUALITY_CONST( measurement.getRelativeUncertainty(), 0.0 );

  measurement = Utility::Measurement<double>( 1.0 );

  TEST_EQUALITY_CONST( measurement.getRelativeUncertainty(), 0.0 );

  measurement = Utility::Measurement<double>( 0.1, 0.01 );

  TEST_FLOATING_EQUALITY( measurement.getRelativeUncertainty(), 0.1, 1e-15 );

  measurement = Utility::Measurement<double>( 0.0, 0.01 );

  TEST_EQUALITY_CONST( measurement.getRelativeUncertainty(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the measurement can be calculated
TEUCHOS_UNIT_TEST( Measurement, getLowerBound )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  TEST_EQUALITY_CONST( measurement.getLowerBound(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the measurement can be calculated
TEUCHOS_UNIT_TEST( Measurement, getUpperBound )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );

  TEST_EQUALITY_CONST( measurement.getUpperBound(), 1.1 );
}

//---------------------------------------------------------------------------//
// Check that a measurement can be converted to double
TEUCHOS_UNIT_TEST( Measurement, implicit_conversion )
{
  double value = Utility::Measurement<double>( 2.0, 0.1 );

  TEST_EQUALITY_CONST( value, 2.0 );

  float reduced_precision_value = Utility::Measurement<float>( 2.0f, 0.1f );

  TEST_EQUALITY_CONST( reduced_precision_value, 2.0f );
}

//---------------------------------------------------------------------------//
// Check that a value can be added to a measurement
TEUCHOS_UNIT_TEST( Measurement, addition )
{
  Utility::Measurement<double> measurement( 1.0, 0.1 );
  
  // Addition of measurement and scalar
  Utility::Measurement<double> new_measurement = measurement + 1.0;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = measurement - 1.0;
  
  TEST_EQUALITY_CONST( new_measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // Addition of scalar and measurement
  new_measurement = 2.0 + measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), 3.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  new_measurement = -2.0 + measurement;

  TEST_EQUALITY_CONST( new_measurement.getValue(), -1.0 );
  TEST_EQUALITY_CONST( new_measurement.getUncertainty(), 0.1 );

  // In-place addition of measurement and scalar
  measurement += 1.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 2.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement += -1.0;

  TEST_EQUALITY_CONST( measurement.getValue(), 0.0 );
  TEST_EQUALITY_CONST( measurement.getUncertainty(), 0.1 );

  // In-place addition of measurement and another measurement
  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement += Utility::Measurement<double>( 2.0, 0.3 );

  TEST_EQUALITY_CONST( measurement.getValue(), 3.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(), 
			  sqrt( 0.1*0.1+0.3*0.3 ),
			  1e-15 );

  measurement = Utility::Measurement<double>( 1.0, 0.1 );
  measurement += Utility::Measurement<double>( -2.0, 0.3 );

  TEST_EQUALITY_CONST( measurement.getValue(), -1.0 );
  TEST_FLOATING_EQUALITY( measurement.getUncertainty(), 
			  sqrt( 0.1*0.1+0.3*0.3 ),
			  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a value can be subtracted from a measurement


//---------------------------------------------------------------------------//
// end tstMeasurement.cpp
//---------------------------------------------------------------------------//
