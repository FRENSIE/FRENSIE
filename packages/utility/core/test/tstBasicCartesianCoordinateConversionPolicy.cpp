//---------------------------------------------------------------------------//
//!
//! \file   tstBasicCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic Cartesian coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the input spatial coordinates can be converted to Cartesian
// coordinates
TEUCHOS_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  Teuchos::Array<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  Teuchos::Array<double> output_position( 3 );

  policy->convertToCartesianSpatialCoordinates( input_position.getRawPtr(),
                                                output_position.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  policy->convertToCartesianSpatialCoordinates( input_position[0],
                                                input_position[1],
                                                input_position[2],
                                                output_position[0],
                                                output_position[1],
                                                output_position[2] );

  TEST_COMPARE_ARRAYS( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that the input Cartesian coordinates can be converted to the
// spatial coordinates
TEUCHOS_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  Teuchos::Array<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  Teuchos::Array<double> output_position( 3 );

  policy->convertFromCartesianSpatialCoordinates( input_position.getRawPtr(),
                                                  output_position.getRawPtr());

  TEST_COMPARE_ARRAYS( input_position, output_position );

  input_position[0] = 2.0;
  input_position[1] = -1.0;
  input_position[2] = 0.1;

  policy->convertToCartesianSpatialCoordinates( input_position[0],
                                                input_position[1],
                                                input_position[2],
                                                output_position[0],
                                                output_position[1],
                                                output_position[2] );

  TEST_COMPARE_ARRAYS( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that the input directional coordinates can be converted to Cartesian
// coordinates
TEUCHOS_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  Teuchos::Array<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  Teuchos::Array<double> output_direction( 3 );

  policy->convertToCartesianDirectionalCoordinates(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  policy->convertToCartesianDirectionalCoordinates(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// Check that the input Cartesian coordinates can be converted to the
// directional coordinates
TEUCHOS_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicCartesianCoordinateConversionPolicy );

  Teuchos::Array<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  Teuchos::Array<double> output_direction( 3 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  policy->convertFromCartesianDirectionalCoordinates(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// end tstBasicCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
