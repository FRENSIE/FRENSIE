//---------------------------------------------------------------------------//
//!
//! \file   tstSphericalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Spherical spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that spherical spatial coordinates can be converted to Cartesian
// spatial coordinates
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  // Z-axis
  std::array<double,3> cartesian_position = {0.0, 0.0, 2.0};

  std::array<double,3> spherical_position;
  
  std::array<double,3> ref_spherical_position = {2.0, 0.0, 1.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.data(),
                                              spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );

  // Neg. z-axis
  cartesian_position = {0.0, 0.0, -2.0};
  ref_spherical_position = {2.0, 0.0, -1.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.data(),
                                              spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );

  // Y-axis
  cartesian_position = {0.0, 2.0, 0.0};
  ref_spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.data(),
                                              spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );

  // Neg. y-axis
  cartesian_position = {0.0, -2.0, 0.0};
  ref_spherical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.data(),
                                              spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );

  // X-axis
  cartesian_position = {2.0, 0.0, 0.0};
  ref_spherical_position = {2.0, 0.0, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.data(),
                                              spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );

  // Neg. x-axis
  cartesian_position = {-2.0, 0.0, 0.0};
  ref_spherical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              cartesian_position.data(),
                                              spherical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );

  // Off axis
  cartesian_position = {1.0, 1.0, 1.0};
  ref_spherical_position =
    {sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                       cartesian_position[0],
                                                       cartesian_position[1],
                                                       cartesian_position[2],
                                                       spherical_position[0],
                                                       spherical_position[1],
                                                       spherical_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_position, ref_spherical_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that spherical spatial coordinates can be converted to Cartesian
// spatial coordinates
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateConversionPolicy,
                   convertToCartesianPosition )
{
  // Z-axis
  std::array<double,3> spherical_position = {2.0, 0.0, 1.0};

  std::array<double,3> cartesian_position;
  
  std::array<double,3> ref_cartesian_position = {0.0, 0.0, 2.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.data(),
                                              cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Neg. Z-axis
  spherical_position = {2.0, 0.0, -1.0};
  ref_cartesian_position = {0.0, 0.0, -2.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.data(),
                                              cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Y-axis
  spherical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_cartesian_position = {0.0, 2.0, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.data(),
                                              cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Neg. y-axis
  spherical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_cartesian_position = {0.0, -2.0, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.data(),
                                              cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // X-axis
  spherical_position = {2.0, 0.0, 0.0};
  ref_cartesian_position = {2.0, 0.0, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.data(),
                                              cartesian_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Y-axis
  spherical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};
  ref_cartesian_position = {-2.0, 0.0, 0.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              spherical_position.data(),
                                              cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Off axis
  spherical_position =
    {sqrt(3.0), Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};
  ref_cartesian_position = {1.0, 1.0, 1.0};

  Utility::SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                       spherical_position[0],
                                                       spherical_position[1],
                                                       spherical_position[2],
                                                       cartesian_position[0],
                                                       cartesian_position[1],
                                                       cartesian_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstSphericalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
