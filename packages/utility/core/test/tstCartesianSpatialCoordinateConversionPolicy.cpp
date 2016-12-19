//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that input spatial coordinates can be converted to output
// spatial coordinates
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  Teuchos::Array<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  Teuchos::Array<double> output_position( 3 );

  Utility::CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                 input_position.getRawPtr(),
                                                 output_position.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  Utility::CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                          input_position[0],
                                                          input_position[1],
                                                          input_position[2],
                                                          output_position[0],
                                                          output_position[1],
                                                          output_position[2] );
  
  TEST_COMPARE_ARRAYS( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that input spatial coordinates can be converted to output
// spatial coordinates
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateConversionPolicy,
                   convertToCartesianPosition)
{
  Teuchos::Array<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  Teuchos::Array<double> output_position( 3 );

  Utility::CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                 input_position.getRawPtr(),
                                                 output_position.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  Utility::CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                          input_position[0],
                                                          input_position[1],
                                                          input_position[2],
                                                          output_position[0],
                                                          output_position[1],
                                                          output_position[2] );
  
  TEST_COMPARE_ARRAYS( input_position, output_position );
}

//---------------------------------------------------------------------------//
// end tstCartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
