//---------------------------------------------------------------------------//
//!
//! \file   tstCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial coordinate conversion policy unit tests
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
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that Cartesian spatial coordinates can be converted to cylindrical
// spatial coordinates
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  // Z-axis
  Teuchos::Tuple<double,3> cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> cylindrical_position;
  Teuchos::Tuple<double,3> ref_cylindrical_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Neg. z-axis
  cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_cylindrical_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Y-axis
  cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );
  ref_cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Neg. y-axis
  cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );
  ref_cylindrical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // X-axis
  cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_cylindrical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Neg. x-axis
  cartesian_position = Teuchos::tuple( -2.0, 0.0, 0.0 );
  ref_cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Off axis
  cartesian_position = Teuchos::tuple( 1.0, 1.0, 1.0 );
  ref_cylindrical_position =
    Teuchos::tuple( sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.getRawPtr(),
                                            cylindrical_position.getRawPtr() );

  TEST_COMPARE_FLOATING_ARRAYS( cylindrical_position, ref_cylindrical_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that cylindrical spatial coordinates can be converted to Cartesian
// spatial coordinates
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateConversionPolicy,
                   convertToCartesianPosition )
{
  // Z-axis
  Teuchos::Tuple<double,3> cylindrical_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Teuchos::Tuple<double,3> cartesian_position;
  Teuchos::Tuple<double,3> ref_cartesian_position =
    Teuchos::tuple( 0.0, 0.0, 2.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );
                                            

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // Neg. z-axis
  cylindrical_position = Teuchos::tuple( 0.0, 0.0, -2.0 );
  ref_cartesian_position = Teuchos::tuple( 0.0, 0.0, -2.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );
                                            

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // Y-axis
  cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi/2, 0.0 );
  ref_cartesian_position = Teuchos::tuple( 0.0, 2.0, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );
                                            

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // Neg. y-axis
  cylindrical_position =
    Teuchos::tuple( 2.0, 3*Utility::PhysicalConstants::pi/2, 0.0 );
  ref_cartesian_position = Teuchos::tuple( 0.0, -2.0, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );
                                            

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );

  // X-axis
  cylindrical_position = Teuchos::tuple( 2.0, 0.0, 0.0 );
  ref_cartesian_position = Teuchos::tuple( 2.0, 0.0, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );
                                            

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );


  // Neg. x-axis
  cylindrical_position =
    Teuchos::tuple( 2.0, Utility::PhysicalConstants::pi, 0.0 );
  ref_cartesian_position = Teuchos::tuple( -2.0, 0.0, 0.0 );

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.getRawPtr(),
                                              cartesian_position.getRawPtr() );
                                            

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( cartesian_position(), ref_cartesian_position(), 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
