//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_CartesianCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that input spatial coordinates can be converted to output
// spatial coordinates
TEUCHOS_UNIT_TEST( CartesianCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  Teuchos::Array<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  Teuchos::Array<double> output_position( 3 );

  Utility::CartesianCoordinateConversionPolicy::convertFromCartesianPosition(
                                                 input_position.getRawPtr(),
                                                 output_position.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  Utility::CartesianCoordinateConversionPolicy::convertFromCartesianPosition(
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
TEUCHOS_UNIT_TEST( CartesianCoordinateConversionPolicy,
                   convertToCartesianPosition)
{
  Teuchos::Array<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  Teuchos::Array<double> output_position( 3 );

  Utility::CartesianCoordinateConversionPolicy::convertToCartesianPosition(
                                                 input_position.getRawPtr(),
                                                 output_position.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  Utility::CartesianCoordinateConversionPolicy::convertToCartesianPosition(
                                                          input_position[0],
                                                          input_position[1],
                                                          input_position[2],
                                                          output_position[0],
                                                          output_position[1],
                                                          output_position[2] );
  
  TEST_COMPARE_ARRAYS( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that input directional coordinates can be converted to output
// directional coordinates
TEUCHOS_UNIT_TEST( CartesianCoordinateConversionPolicy,
                   convertFromCartesianDirection )
{
  Teuchos::Array<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  Teuchos::Array<double> output_direction( 3 );

  Utility::CartesianCoordinateConversionPolicy::convertFromCartesianDirection(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  Utility::CartesianCoordinateConversionPolicy::convertFromCartesianDirection(
                                                         input_direction[0],
                                                         input_direction[1],
                                                         input_direction[2],
                                                         output_direction[0],
                                                         output_direction[1],
                                                         output_direction[2] );
  
  TEST_COMPARE_ARRAYS( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// Check that input directional coordinates can be converted to output
// directional coordinates
TEUCHOS_UNIT_TEST( CartesianCoordinateConversionPolicy,
                   convertToCartesianDirection )
{
  Teuchos::Array<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  Teuchos::Array<double> output_direction( 3 );

  Utility::CartesianCoordinateConversionPolicy::convertToCartesianDirection(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  Utility::CartesianCoordinateConversionPolicy::convertToCartesianDirection(
                                                         input_direction[0],
                                                         input_direction[1],
                                                         input_direction[2],
                                                         output_direction[0],
                                                         output_direction[1],
                                                         output_direction[2] );
  
  TEST_COMPARE_ARRAYS( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// end tstCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
