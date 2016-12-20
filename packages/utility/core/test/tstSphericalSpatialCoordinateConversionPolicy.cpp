//---------------------------------------------------------------------------//
//!
//! \file   tstSphericalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Spherical spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that spherical spatial coordinates can be converted to Cartesian
// spatial coordinates
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  // Z-axis
  Teuchos::Tuple<double,3> cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> spherical_position;
  
  Teuchos::Tuple<double,3> ref_spherical_position =
    Teuchos::tuple( 2.0, 0.0, 1.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.getRawPtr(),
                                              spherical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );

  // Neg. z-axis
  cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_spherical_position = Teuchos::tuple( 2.0, 0.0, -1.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.getRawPtr(),
                                              spherical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );

  // Y-axis
  cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );
  ref_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.getRawPtr(),
                                              spherical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );

  // Neg. y-axis
  cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );
  ref_spherical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.getRawPtr(),
                                              spherical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );

  // X-axis
  cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_spherical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.getRawPtr(),
                                              spherical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );

  // Neg. x-axis
  cartesian_position = Teuchos::tuple( -2.0, 0.0, 0.0 );
  ref_spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.getRawPtr(),
                                              spherical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );

  // Off axis
  cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );
  ref_spherical_position =
    Teuchos::tuple( sqrt(3.0),
                    Utility::PhysicalConstants::pi/4,
                    1.0/sqrt(3.0) );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                       cartesian_position[0],
                                                       cartesian_position[1],
                                                       cartesian_position[2],
                                                       spherical_position[0],
                                                       spherical_position[1],
                                                       spherical_position[2] );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_position, ref_spherical_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that spherical spatial coordinates can be converted to Cartesian
// spatial coordinates
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateConversionPolicy,
                   convertToCartesianPosition )
{
  // Z-axis
  Teuchos::Tuple<double,3> spherical_position =
    Teuchos::tuple( 2.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> cartesian_position;
  
  Teuchos::Tuple<double,3> ref_cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cartesian_position, ref_cartesian_position, 1e-15 );

  // Neg. Z-axis
  spherical_position = Teuchos::tuple( 2.0, 0.0, -1.0 );
  ref_cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cartesian_position, ref_cartesian_position, 1e-15 );

  // Y-axis
  spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // Neg. y-axis
  spherical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // X-axis
  spherical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // Y-axis
  spherical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_cartesian_position = Teuchos::tuple( -2.0, 0.0, 0.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // Off axis
  spherical_position =
    Teuchos::tuple( sqrt(3.0),
                    Utility::PhysicalConstants::pi/4,
                    1.0/sqrt(3.0) );
  ref_cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                       spherical_position[0],
                                                       spherical_position[1],
                                                       spherical_position[2],
                                                       cartesian_position[0],
                                                       cartesian_position[1],
                                                       cartesian_position[2] );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstSphericalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
