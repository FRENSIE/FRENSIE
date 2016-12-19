//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianDirectionalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian directional coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that input directional coordinates can be converted to output
// directional coordinates
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateConversionPolicy,
                   convertFromCartesianDirection )
{
  Teuchos::Array<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  Teuchos::Array<double> output_direction( 3 );

  Utility::CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  Utility::CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
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
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateConversionPolicy,
                   convertToCartesianDirection )
{
  Teuchos::Array<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  Teuchos::Array<double> output_direction( 3 );

  Utility::CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                                input_direction.getRawPtr(),
                                                output_direction.getRawPtr() );

  TEST_COMPARE_ARRAYS( input_direction, output_direction );

  input_direction[0] = 1.0/sqrt(2.0);
  input_direction[1] = -1.0/sqrt(2.0);
  input_direction[2] = 0.0;

  Utility::CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                                         input_direction[0],
                                                         input_direction[1],
                                                         input_direction[2],
                                                         output_direction[0],
                                                         output_direction[1],
                                                         output_direction[2] );
  
  TEST_COMPARE_ARRAYS( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// end tstCartesianDirectionalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
