//---------------------------------------------------------------------------//
//!
//! \file   tstBasicSphericalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic spherical coordinate conversion policy unit tests
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
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local spatial coordinate system type can be returned
TEUCHOS_UNIT_TEST( BasicCartesianCoordinateConversionPolicy,
                   getLocalSpatialCoordinateSystemType )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_EQUALITY_CONST( policy->getLocalSpatialCoordinateSystemType(),
                       Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary spatial coordinate is valid
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isPrimarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_ASSERT( policy->isPrimarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  TEST_ASSERT( policy->isPrimarySpatialCoordinateValid(
                                   std::numeric_limits<double>::infinity() ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary spatial coordinate is valid
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isSecondarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_ASSERT( policy->isSecondarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  TEST_ASSERT( policy->isSecondarySpatialCoordinateValid(
                                          2*Utility::PhysicalConstants::pi ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary spatial coordinate is valid
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isTertiarySpatialCoordinateValid )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_ASSERT( policy->isTertiarySpatialCoordinateValid( -1.0 ) );
  
  TEST_ASSERT( policy->isTertiarySpatialCoordinateValid( 0.0 ) );
                                                       
  
  TEST_ASSERT( policy->isTertiarySpatialCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the local directional coordinate system type can be returned
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   getLocalDirectionalCoordinateSystemType )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_EQUALITY_CONST( policy->getLocalDirectionalCoordinateSystemType(),
                       Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM );
}

//---------------------------------------------------------------------------//
// Check if the primary directional coordinate is valid
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isPrimaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_ASSERT( !policy->isPrimaryDirectionalCoordinateValid( -0.99 ) );
  TEST_ASSERT( policy->isPrimaryDirectionalCoordinateValid( 1.0 ) );
  TEST_ASSERT( !policy->isPrimaryDirectionalCoordinateValid( 1.01 ) );
}

//---------------------------------------------------------------------------//
// Check if the secondary directional coordinate is valid
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isSecondaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_ASSERT( policy->isSecondaryDirectionalCoordinateValid( 0.0 ) );

  TEST_ASSERT( policy->isSecondaryDirectionalCoordinateValid(
                                          2*Utility::PhysicalConstants::pi ) );
}

//---------------------------------------------------------------------------//
// Check if the tertiary directional coordinate is valid
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   isTertiaryDirectionalCoordinateValid )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  TEST_ASSERT( policy->isTertiaryDirectionalCoordinateValid( -1.0 ) );

  TEST_ASSERT( policy->isTertiaryDirectionalCoordinateValid( 0.0 ) );
                                                       
  
  TEST_ASSERT( policy->isTertiaryDirectionalCoordinateValid( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the local spherical spatial coordinates can be converted to
// global Cartesian spatial coordinates
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  Teuchos::Tuple<double,3> local_spherical_position =
    Teuchos::tuple( 2.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> global_cartesian_position;
  
  Teuchos::Tuple<double,3> ref_global_cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Neg. z-axis
  local_spherical_position = Teuchos::tuple( 2.0, 0.0, -1.0 );
  ref_global_cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Y-axis
  local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Neg y-axis
  local_spherical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // X-axis
  local_spherical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Neg. x-axis
  local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_global_cartesian_position = Teuchos::tuple( -2.0, 0.0, 0.0 );

  policy->convertToCartesianSpatialCoordinates(
                                       local_spherical_position.getRawPtr(),
                                       global_cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );

  // Off axis
  local_spherical_position = Teuchos::tuple( sqrt(3.0),
                                             Utility::PhysicalConstants::pi/4,
                                             1.0/sqrt(3.0) );
  ref_global_cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );

  policy->convertToCartesianSpatialCoordinates( local_spherical_position[0],
                                                local_spherical_position[1],
                                                local_spherical_position[2],
                                                global_cartesian_position[0],
                                                global_cartesian_position[1],
                                                global_cartesian_position[2] );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_position(),
                                        ref_global_cartesian_position(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local spherical spatial coordinates
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  Teuchos::Tuple<double,3> global_cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> local_spherical_position;
  
  Teuchos::Tuple<double,3> ref_local_spherical_position =
    Teuchos::tuple( 2.0, 0.0, 1.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.getRawPtr(),
                                       local_spherical_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Neg. z-axis
  global_cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_local_spherical_position = Teuchos::tuple( 2.0, 0.0, -1.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.getRawPtr(),
                                       local_spherical_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Y-axis
  global_cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );
  ref_local_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.getRawPtr(),
                                       local_spherical_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Neg. y-axis
  global_cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );
  ref_local_spherical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.getRawPtr(),
                                       local_spherical_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // X-axis
  global_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_local_spherical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  policy->convertFromCartesianSpatialCoordinates(
                                       global_cartesian_position.getRawPtr(),
                                       local_spherical_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );

  // Off axis
  global_cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );
  ref_local_spherical_position =
    Teuchos::tuple( sqrt(3.0),
                    Utility::PhysicalConstants::pi/4,
                    1.0/sqrt(3.0) );

  policy->convertFromCartesianSpatialCoordinates(
                                                 global_cartesian_position[0],
                                                 global_cartesian_position[1],
                                                 global_cartesian_position[2],
                                                 local_spherical_position[0],
                                                 local_spherical_position[1],
                                                 local_spherical_position[2] );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_position(),
                                        ref_local_spherical_position(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the local spherical directional coordinates can be converted
// to global Cartesian directional coordinates
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertToCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  Teuchos::Tuple<double,3> local_spherical_direction =
    Teuchos::tuple( 1.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> global_cartesian_direction;
  
  Teuchos::Tuple<double,3> ref_global_cartesian_direction =
    Teuchos::tuple( 0.0, 0.0, 1.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Neg. z-axis
  local_spherical_direction = Teuchos::tuple( 1.0, 0.0, -1.0 );
  ref_global_cartesian_direction = Teuchos::tuple( 0.0, 0.0, -1.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Y-axis
  local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_direction = Teuchos::tuple( 0.0, 1.0, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Neg y-axis
  local_spherical_direction =
    Teuchos::tuple( 1.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_global_cartesian_direction = Teuchos::tuple( 0.0, -1.0, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // X-axis
  local_spherical_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );
  ref_global_cartesian_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Neg. x-axis
  local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_global_cartesian_direction = Teuchos::tuple( -1.0, 0.0, 0.0 );

  policy->convertToCartesianDirectionalCoordinates(
                                      local_spherical_direction.getRawPtr(),
                                      global_cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );

  // Off axis
  local_spherical_direction = Teuchos::tuple( 1.0/sqrt(3.0),
                                             Utility::PhysicalConstants::pi/4,
                                             1.0/sqrt(3.0) );
  ref_global_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );

  policy->convertToCartesianDirectionalCoordinates(
                                               local_spherical_direction[0],
                                               local_spherical_direction[1],
                                               local_spherical_direction[2],
                                               global_cartesian_direction[0],
                                               global_cartesian_direction[1],
                                               global_cartesian_direction[2] );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( global_cartesian_direction(),
                                        ref_global_cartesian_direction(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian directional coordinates can be converted
// to local spherical directional coordinates
TEUCHOS_UNIT_TEST( BasicSphericalCoordinateConversionPolicy,
                   convertFromCartesianDirectionalCoordinates )
{
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy> policy(
                       new Utility::BasicSphericalCoordinateConversionPolicy );

  // Z-axis
  Teuchos::Tuple<double,3> global_cartesian_direction =
    Teuchos::tuple( 0.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> local_spherical_direction;
  
  Teuchos::Tuple<double,3> ref_local_spherical_direction =
    Teuchos::tuple( 1.0, 0.0, 1.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Neg. z-axis
  global_cartesian_direction = Teuchos::tuple( 0.0, 0.0, -1.0 );
  ref_local_spherical_direction = Teuchos::tuple( 1.0, 0.0, -1.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Y-axis
  global_cartesian_direction = Teuchos::tuple( 0.0, 1.0, 0.0 );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Neg. y-axis
  global_cartesian_direction = Teuchos::tuple( 0.0, -1.0, 0.0 );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // X-axis
  global_cartesian_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );
  ref_local_spherical_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );

  policy->convertFromCartesianDirectionalCoordinates(
                                       global_cartesian_direction.getRawPtr(),
                                       local_spherical_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );

  // Off axis
  global_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  ref_local_spherical_direction =
    Teuchos::tuple( 1.0,
                    Utility::PhysicalConstants::pi/4,
                    1.0/sqrt(3.0) );

  policy->convertFromCartesianDirectionalCoordinates(
                                                global_cartesian_direction[0],
                                                global_cartesian_direction[1],
                                                global_cartesian_direction[2],
                                                local_spherical_direction[0],
                                                local_spherical_direction[1],
                                                local_spherical_direction[2] );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_spherical_direction(),
                                        ref_local_spherical_direction(),
                                        1e-15 );
}

//---------------------------------------------------------------------------//
// end tstBasicSphericalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
