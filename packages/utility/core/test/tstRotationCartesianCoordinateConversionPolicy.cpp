//---------------------------------------------------------------------------//
//!
//! \file   tstRotationCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Rotation Cartesian coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local Cartesian spatial coordinates can be converted to
// global Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> local_position = Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> global_position;
  Teuchos::Tuple<double,3> ref_global_position =
    Teuchos::tuple( 2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0) );
  
  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-15 );

  // Local neg. z-axis
  local_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_global_position =
    Teuchos::tuple( -2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0) );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-15 );

  // Local y-axis
  local_position = Teuchos::tuple( 0.0, 2.0, 0.0 );
  ref_global_position = Teuchos::tuple( -sqrt(2.0), sqrt(2.0), 0.0 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-15 );

  // Local neg. y-axis
  local_position = Teuchos::tuple( 0.0, -2.0, 0.0 );
  ref_global_position = Teuchos::tuple( sqrt(2.0), -sqrt(2.0), 0.0 );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-15 );

  // Local x-axis
  local_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_global_position =
    Teuchos::tuple( 2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0) );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-15 );

  // Local neg. x-axis
  local_position = Teuchos::tuple( -2.0, 0.0, 0.0 );
  ref_global_position =
    Teuchos::tuple( -2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0) );

  policy->convertToCartesianSpatialCoordinates( local_position.getRawPtr(),
                                                global_position.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_position, ref_global_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // To local x-axis
  Teuchos::Tuple<double,3> global_position =
    Teuchos::tuple( 2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0) );

  Teuchos::Tuple<double,3> local_position;
  Teuchos::Tuple<double,3> ref_local_position =
    Teuchos::tuple( 2.0, 0.0, 0.0 );
  
  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-15 );

  // To local neg. x-axis
  global_position =
    Teuchos::tuple( -2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0) );
  ref_local_position = Teuchos::tuple( -2.0, 0.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-15 );

  // To local y-axis
  global_position = Teuchos::tuple( -sqrt(2.0), sqrt(2.0), 0.0 );
  ref_local_position = Teuchos::tuple( 0.0, 2.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-15 );

  // To local neg. y-axis
  global_position = Teuchos::tuple( sqrt(2.0), -sqrt(2.0), 0.0 );
  ref_local_position = Teuchos::tuple( 0.0, -2.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-15 );

  // To local z-axis
  global_position =
    Teuchos::tuple( 2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0) );
  ref_local_position = Teuchos::tuple( 0.0, 0.0, 2.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-15 );

  // To local neg. z-axis
  global_position =
    Teuchos::tuple( -2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0) );
  ref_local_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  policy->convertFromCartesianSpatialCoordinates( global_position.getRawPtr(),
                                                  local_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_position(), ref_local_position(), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the local Cartesian directional coordinates can be converted to
// global Cartesian directional coordinates
TEUCHOS_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> local_direction = Teuchos::tuple( 0.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> global_direction;
  Teuchos::Tuple<double,3> ref_global_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  
  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.getRawPtr(),
                                                global_direction.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_direction, ref_global_direction, 1e-15 );

  // Local neg. z-axis
  local_direction = Teuchos::tuple( 0.0, 0.0, -1.0 );
  ref_global_direction =
    Teuchos::tuple( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.getRawPtr(),
                                                global_direction.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_direction, ref_global_direction, 1e-15 );

  // Local y-axis
  local_direction = Teuchos::tuple( 0.0, 1.0, 0.0 );
  ref_global_direction = Teuchos::tuple( -sqrt(2.0)/2, sqrt(2.0)/2, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.getRawPtr(),
                                                global_direction.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_direction, ref_global_direction, 1e-15 );

  // Local neg. y-axis
  local_direction = Teuchos::tuple( 0.0, -1.0, 0.0 );
  ref_global_direction = Teuchos::tuple( sqrt(2.0)/2, -sqrt(2.0)/2, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.getRawPtr(),
                                                global_direction.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_direction, ref_global_direction, 1e-15 );

  // Local x-axis
  local_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );
  ref_global_direction =
    Teuchos::tuple( 1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.getRawPtr(),
                                                global_direction.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_direction, ref_global_direction, 1e-15 );

  // Local neg. x-axis
  local_direction = Teuchos::tuple( -1.0, 0.0, 0.0 );
  ref_global_direction =
    Teuchos::tuple( -1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                                local_direction.getRawPtr(),
                                                global_direction.getRawPtr() );
  
  TEST_COMPARE_FLOATING_ARRAYS( global_direction, ref_global_direction, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian directional coordinates can be converted to
// local Cartesian directional coordinates
TEUCHOS_UNIT_TEST( RotationCartesianCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
   new Utility::RotationCartesianCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // To local x-axis
  Teuchos::Tuple<double,3> global_direction =
    Teuchos::tuple( 1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0) );

  Teuchos::Tuple<double,3> local_direction;
  Teuchos::Tuple<double,3> ref_local_direction =
    Teuchos::tuple( 1.0, 0.0, 0.0 );
  
  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.getRawPtr(),
                                                 local_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_direction(), ref_local_direction(), 1e-15 );

  // To local neg. x-axis
  global_direction =
    Teuchos::tuple( -1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0) );
  ref_local_direction = Teuchos::tuple( -1.0, 0.0, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.getRawPtr(),
                                                 local_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_direction(), ref_local_direction(), 1e-15 );

  // To local y-axis
  global_direction = Teuchos::tuple( -sqrt(2.0)/2, sqrt(2.0)/2, 0.0 );
  ref_local_direction = Teuchos::tuple( 0.0, 1.0, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.getRawPtr(),
                                                 local_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_direction(), ref_local_direction(), 1e-15 );

  // To local neg. y-axis
  global_direction = Teuchos::tuple( sqrt(2.0)/2, -sqrt(2.0)/2, 0.0 );
  ref_local_direction = Teuchos::tuple( 0.0, -1.0, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.getRawPtr(),
                                                 local_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_direction(), ref_local_direction(), 1e-15 );

  // To local z-axis
  global_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  ref_local_direction = Teuchos::tuple( 0.0, 0.0, 1.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.getRawPtr(),
                                                 local_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_direction(), ref_local_direction(), 1e-15 );

  // To local neg. z-axis
  global_direction =
    Teuchos::tuple( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );
  ref_local_direction = Teuchos::tuple( 0.0, 0.0, -1.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                                 global_direction.getRawPtr(),
                                                 local_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_direction(), ref_local_direction(), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstRotationCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
