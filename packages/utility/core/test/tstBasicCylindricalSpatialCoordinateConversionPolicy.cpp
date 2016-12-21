//---------------------------------------------------------------------------//
//!
//! \file   tstBasicCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic cylindrical coordinate conversion policy unit tests
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
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local cylindrical spatial coordinates can be converted to
// global Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( BasicCylindricalSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  // Z-axis
  Teuchos::Tuple<double,3> local_cylindrical_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> global_cartesian_position;

  Teuchos::Tuple<double,3> ref_global_cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Neg. z-axis
  local_cylindrical_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_global_cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Y-axis
  local_cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Neg. y-axis
  local_cylindrical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // X-axis
  local_cylindrical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Neg. x-axis
  local_cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( -2.0, 0.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_cylindrical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Off axis
  local_cylindrical_position =
    Teuchos::tuple( sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0 );
  ref_global_cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );

  policy->convertToCartesianSpatialCoordinates( local_cylindrical_position[0],
                                                local_cylindrical_position[1],
                                                local_cylindrical_position[2],
                                                global_cartesian_position[0],
                                                global_cartesian_position[1],
                                                global_cartesian_position[2] );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local cylindrical spatial coordinates
TEUCHOS_UNIT_TEST( BasicCylindricalSpatialCoordinateConversionPolicy,
                   convertFromCartesianCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
              new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  // Z-axis
  Teuchos::Tuple<double,3> global_cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );
  
  Teuchos::Tuple<double,3> local_cylindrical_position;

  Teuchos::Tuple<double,3> ref_local_cylindrical_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.getRawPtr(),
                                      local_cylindrical_position.getRawPtr() );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );

  // Neg. z-axis
  global_cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_local_cylindrical_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.getRawPtr(),
                                      local_cylindrical_position.getRawPtr() );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );

  // Y-axis
  global_cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );
  ref_local_cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.getRawPtr(),
                                      local_cylindrical_position.getRawPtr() );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );

  // Neg. y-axis
  global_cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );
  ref_local_cylindrical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.getRawPtr(),
                                      local_cylindrical_position.getRawPtr() );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );

  // X-axis
  global_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_local_cylindrical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.getRawPtr(),
                                      local_cylindrical_position.getRawPtr() );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );

  // Neg. x-axis
  global_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_local_cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                      global_cartesian_position.getRawPtr(),
                                      local_cylindrical_position.getRawPtr() );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );

  // Off axis
  global_cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );
  ref_local_cylindrical_position =
    Teuchos::tuple( sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                               global_cartesian_position[0],
                                               global_cartesian_position[1],
                                               global_cartesian_position[2],
                                               local_cylindrical_position[0],
                                               local_cylindrical_position[1],
                                               local_cylindrical_position[2] );
                                       

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_cylindrical_position(),
                                        ref_local_cylindrical_position(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// end tstBasicCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
