//---------------------------------------------------------------------------//
//!
//! \file   tstSphericalDirectionalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Spherical directional coordinate conversion policy unit tests
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
#include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the spherical directional coordinates can be converted to
// Cartesian directional coordinates
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateConversionPolicy,
                   convertFromCartesianDirection )
{
  // Z-axis
  Teuchos::Tuple<double,3> cartesian_direction =
    Teuchos::tuple( 0.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> spherical_direction;
  
  Teuchos::Tuple<double,3> ref_spherical_direction =
    Teuchos::tuple( 1.0, 0.0, 1.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.getRawPtr(),
                                             spherical_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );

  // Neg. z-axis
  cartesian_direction = Teuchos::tuple( 0.0, 0.0, -1.0 );
  ref_spherical_direction = Teuchos::tuple( 1.0, 0.0, -1.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.getRawPtr(),
                                             spherical_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );

  // Y-axis
  cartesian_direction = Teuchos::tuple( 0.0, 1.0, 0.0 );
  ref_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi/2, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.getRawPtr(),
                                             spherical_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );

  // Neg. y-axis
  cartesian_direction = Teuchos::tuple( 0.0, -1.0, 0.0 );
  ref_spherical_direction =
    Teuchos::tuple( 1.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.getRawPtr(),
                                             spherical_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );

  // X-axis
  cartesian_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );
  ref_spherical_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.getRawPtr(),
                                             spherical_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );

  // Neg. x-axis
  cartesian_direction = Teuchos::tuple( -1.0, 0.0, 0.0 );
  ref_spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.getRawPtr(),
                                             spherical_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );

  // Off axis
  cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  ref_spherical_direction =
    Teuchos::tuple( 1.0,
                    Utility::PhysicalConstants::pi/4,
                    1.0/sqrt(3.0) );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                      cartesian_direction[0],
                                                      cartesian_direction[1],
                                                      cartesian_direction[2],
                                                      spherical_direction[0],
                                                      spherical_direction[1],
                                                      spherical_direction[2] );

  TEST_COMPARE_FLOATING_ARRAYS( spherical_direction, ref_spherical_direction, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the spherical directional coordinates can be converted to
// Cartesian directional coordinates
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateConversionPolicy,
                   convertToCartesianDirection )
{
  // Z-axis
  Teuchos::Tuple<double,3> spherical_direction =
    Teuchos::tuple( 1.0, 0.0, 1.0 );

  Teuchos::Tuple<double,3> cartesian_direction;
  
  Teuchos::Tuple<double,3> ref_cartesian_direction =
    Teuchos::tuple( 0.0, 0.0, 1.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Neg. Z-axis
  spherical_direction = Teuchos::tuple( 1.0, 0.0, -1.0 );
  ref_cartesian_direction = Teuchos::tuple( 0.0, 0.0, -1.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Y-axis
  spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_cartesian_direction = Teuchos::tuple( 0.0, 1.0, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction(), ref_cartesian_direction(), 1e-15 );

  // Neg. y-axis
  spherical_direction =
    Teuchos::tuple( 1.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_cartesian_direction = Teuchos::tuple( 0.0, -1.0, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction(), ref_cartesian_direction(), 1e-15 );

  // X-axis
  spherical_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );
  ref_cartesian_direction = Teuchos::tuple( 1.0, 0.0, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction(), ref_cartesian_direction(), 1e-15 );

  // Y-axis
  spherical_direction =
    Teuchos::tuple( 1.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_cartesian_direction = Teuchos::tuple( -1.0, 0.0, 0.0 );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction(), ref_cartesian_direction(), 1e-15 );

  // Off axis
  spherical_direction =
    Teuchos::tuple( 1.0,
                    Utility::PhysicalConstants::pi/4,
                    1.0/sqrt(3.0) );
  ref_cartesian_direction =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.getRawPtr(),
                                             cartesian_direction.getRawPtr() );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_direction(), ref_cartesian_direction(), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstSphericalDirectionalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
