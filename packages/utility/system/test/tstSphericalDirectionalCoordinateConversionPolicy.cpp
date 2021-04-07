//---------------------------------------------------------------------------//
//!
//! \file   tstSphericalDirectionalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Spherical directional coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the spherical directional coordinates can be converted to
// Cartesian directional coordinates
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateConversionPolicy,
                   convertFromCartesianDirection )
{
  // Z-axis
  std::array<double,3> cartesian_direction = {0.0, 0.0, 1.0};

  std::array<double,3> spherical_direction;
  
  std::array<double,3> ref_spherical_direction = {1.0, 0.0, 1.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.data(),
                                             spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );

  // Neg. z-axis
  cartesian_direction = {0.0, 0.0, -1.0};
  ref_spherical_direction = {1.0, 0.0, -1.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.data(),
                                             spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );

  // Y-axis
  cartesian_direction = {0.0, 1.0, 0.0};
  ref_spherical_direction = {1.0, Utility::PhysicalConstants::pi/2, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.data(),
                                             spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );

  // Neg. y-axis
  cartesian_direction = {0.0, -1.0, 0.0};
  ref_spherical_direction = {1.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.data(),
                                             spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );

  // X-axis
  cartesian_direction = {1.0, 0.0, 0.0};
  ref_spherical_direction = {1.0, 0.0, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.data(),
                                             spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );

  // Neg. x-axis
  cartesian_direction = {-1.0, 0.0, 0.0};
  ref_spherical_direction = {1.0, Utility::PhysicalConstants::pi, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                             cartesian_direction.data(),
                                             spherical_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );

  // Off axis
  cartesian_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};
  ref_spherical_direction =
    {1.0, Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                      cartesian_direction[0],
                                                      cartesian_direction[1],
                                                      cartesian_direction[2],
                                                      spherical_direction[0],
                                                      spherical_direction[1],
                                                      spherical_direction[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( spherical_direction, ref_spherical_direction, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the spherical directional coordinates can be converted to
// Cartesian directional coordinates
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateConversionPolicy,
                   convertToCartesianDirection )
{
  // Z-axis
  std::array<double,3> spherical_direction = {1.0, 0.0, 1.0};

  std::array<double,3> cartesian_direction;
  
  std::array<double,3> ref_cartesian_direction = {0.0, 0.0, 1.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Neg. Z-axis
  spherical_direction = {1.0, 0.0, -1.0};
  ref_cartesian_direction = {0.0, 0.0, -1.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Y-axis
  spherical_direction = {1.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_cartesian_direction = {0.0, 1.0, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_direction.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Neg. y-axis
  spherical_direction = {1.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_cartesian_direction = {0.0, -1.0, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_direction.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // X-axis
  spherical_direction = {1.0, 0.0, 0.0};
  ref_cartesian_direction = {1.0, 0.0, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Y-axis
  spherical_direction = {1.0, Utility::PhysicalConstants::pi, 0.0};
  ref_cartesian_direction = {-1.0, 0.0, 0.0};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_direction.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );

  // Off axis
  spherical_direction =
    {1.0, Utility::PhysicalConstants::pi/4, 1.0/sqrt(3.0)};
  ref_cartesian_direction = {1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0)};

  Utility::SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                             spherical_direction.data(),
                                             cartesian_direction.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_direction, ref_cartesian_direction, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstSphericalDirectionalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
