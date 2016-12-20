//---------------------------------------------------------------------------//
//!
//! \file   tstRotationSphericalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Rotation spherical coordinate conversion policy unit tests
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
#include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local spherical spatial coordinates can be converted to
// global Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( RotationSphericalCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> local_spherical_position =
    Teuchos::tuple( 2.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> global_cartesian_position;
  Teuchos::Tuple<double,3> ref_global_cartesian_position =
    Teuchos::tuple( 2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0) );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Local neg. z-axis
  local_spherical_position = Teuchos::tuple( 2.0, 0.0, -1.0 );
  ref_global_cartesian_position =
    Teuchos::tuple( -2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0) );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Local y-axis
  local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( -sqrt(2.0), sqrt(2.0), 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Local neg. y-axis
  local_spherical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( sqrt(2.0), -sqrt(2.0), 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Local x-axis
  local_spherical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_global_cartesian_position =
    Teuchos::tuple( 2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0) );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Local neg. x-axis
  local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_global_cartesian_position =
    Teuchos::tuple( -2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0) );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local spherical spatial coordinates
TEUCHOS_UNIT_TEST( RotationSphericalCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> global_cartesian_position =
    Teuchos::tuple( 2.0/sqrt(3.0), 2.0/sqrt(3.0), 2.0/sqrt(3.0) );

  Teuchos::Tuple<double,3> local_spherical_position;
  Teuchos::Tuple<double,3> ref_local_spherical_position =
    Teuchos::tuple( 2.0, 0.0, 1.0 );
  
  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.getRawPtr(),
                                        local_spherical_position.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Local neg. z-axis
  global_cartesian_position =
    Teuchos::tuple( -2.0/sqrt(3.0), -2.0/sqrt(3.0), -2.0/sqrt(3.0) );
  ref_local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, -1.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.getRawPtr(),
                                        local_spherical_position.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Local y-axis
  global_cartesian_position = Teuchos::tuple( -sqrt(2.0), sqrt(2.0), 0.0 );
  ref_local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.getRawPtr(),
                                        local_spherical_position.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Local neg. y-axis
  global_cartesian_position = Teuchos::tuple( sqrt(2.0), -sqrt(2.0), 0.0 );
  ref_local_spherical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.getRawPtr(),
                                        local_spherical_position.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Local x-axis
  global_cartesian_position =
    Teuchos::tuple( 2.0/sqrt(6.0), 2.0/sqrt(6.0), -sqrt(8.0/3.0) );
  ref_local_spherical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.getRawPtr(),
                                        local_spherical_position.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Local neg. x-axis
  global_cartesian_position =
    Teuchos::tuple( -2.0/sqrt(6.0), -2.0/sqrt(6.0), sqrt(8.0/3.0) );
  ref_local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                        global_cartesian_position.getRawPtr(),
                                        local_spherical_position.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the local spherical directional coordinates can be converted
// to global Cartesian directional coordinates
TEUCHOS_UNIT_TEST( RotationSphericalCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> local_spherical_direction =
    Teuchos::tuple( 1.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> global_cartesian_direction;
  Teuchos::Tuple<double,3> ref_global_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Local neg. z-axis
  local_spherical_direction = Teuchos::tuple( 1.0, 0.0, -1.0 );
  ref_global_cartesian_direction =
    Teuchos::tuple( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Local y-axis
  local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_direction =
    Teuchos::tuple( -sqrt(2.0)/2, sqrt(2.0)/2, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Local neg. y-axis
  local_spherical_direction =
    Teuchos::tuple( 1.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_direction =
    Teuchos::tuple( sqrt(2.0)/2, -sqrt(2.0)/2, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Local x-axis
  local_spherical_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );
  ref_global_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Local neg. x-axis
  local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_global_cartesian_direction =
    Teuchos::tuple( -1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian directional coordinates can be converted
// to local spherical directional coordinates
TEUCHOS_UNIT_TEST( RotationSphericalCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                     new Utility::RotationSphericalCoordinateConversionPolicy(
                                 Teuchos::tuple(1.0, 1.0, 1.0).getRawPtr() ) );

  // Local z-axis
  Teuchos::Tuple<double,3> global_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );

  Teuchos::Tuple<double,3> local_spherical_direction;
  Teuchos::Tuple<double,3> ref_local_spherical_direction =
    Teuchos::tuple( 1.0, 0.0, 1.0 );
  
  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );
                                         
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Local neg. z-axis
  global_cartesian_direction =
    Teuchos::tuple( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi, -1.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );
                                         
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Local y-axis
  global_cartesian_direction =
    Teuchos::tuple( -sqrt(2.0)/2, sqrt(2.0)/2, 0.0 );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );
                                         
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Local neg. y-axis
  global_cartesian_direction =
    Teuchos::tuple( sqrt(2.0)/2, -sqrt(2.0)/2, 0.0 );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );
                                         
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Local x-axis
  global_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(6.0), 1.0/sqrt(6.0), -sqrt(2.0/3.0) );
  ref_local_spherical_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Local neg. x-axis
  global_cartesian_direction =
    Teuchos::tuple( -1.0/sqrt(6.0), -1.0/sqrt(6.0), sqrt(2.0/3.0) );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );
                                       
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// end tstRotationSphericalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
