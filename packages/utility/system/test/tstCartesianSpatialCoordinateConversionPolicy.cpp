//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that input spatial coordinates can be converted to output
// spatial coordinates
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  std::vector<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  std::vector<double> output_position( 3 );

  Utility::CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                 input_position.data(),
                                                 output_position.data() );

  FRENSIE_CHECK_EQUAL( input_position, output_position );

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
  
  FRENSIE_CHECK_EQUAL( input_position, output_position );
}

//---------------------------------------------------------------------------//
// Check that input spatial coordinates can be converted to output
// spatial coordinates
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateConversionPolicy,
                   convertToCartesianPosition)
{
  std::vector<double> input_position( 3 );
  input_position[0] = 1.0;
  input_position[1] = 1.0;
  input_position[2] = 1.0;

  std::vector<double> output_position( 3 );

  Utility::CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                 input_position.data(),
                                                 output_position.data() );

  FRENSIE_CHECK_EQUAL( input_position, output_position );

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
  
  FRENSIE_CHECK_EQUAL( input_position, output_position );
}

//---------------------------------------------------------------------------//
// end tstCartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
