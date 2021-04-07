//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianDirectionalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian directional coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that input directional coordinates can be converted to output
// directional coordinates
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateConversionPolicy,
                   convertFromCartesianDirection )
{
  std::vector<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  std::vector<double> output_direction( 3 );

  Utility::CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                input_direction.data(),
                                                output_direction.data() );

  FRENSIE_CHECK_EQUAL( input_direction, output_direction );

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
  
  FRENSIE_CHECK_EQUAL( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// Check that input directional coordinates can be converted to output
// directional coordinates
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateConversionPolicy,
                   convertToCartesianDirection )
{
  std::vector<double> input_direction( 3 );
  input_direction[0] = 1.0/sqrt(3.0);
  input_direction[1] = 1.0/sqrt(3.0);
  input_direction[2] = 1.0/sqrt(3.0);

  std::vector<double> output_direction( 3 );

  Utility::CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                                input_direction.data(),
                                                output_direction.data() );

  FRENSIE_CHECK_EQUAL( input_direction, output_direction );

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
  
  FRENSIE_CHECK_EQUAL( input_direction, output_direction );
}

//---------------------------------------------------------------------------//
// end tstCartesianDirectionalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
