//---------------------------------------------------------------------------//
//!
//! \file   tstCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that Cartesian spatial coordinates can be converted to cylindrical
// spatial coordinates
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateConversionPolicy,
                   convertFromCartesianPosition )
{
  // Z-axis
  std::array<double,3> cartesian_position = {0.0, 0.0, 2.0};

  std::array<double,3> cylindrical_position;
  std::array<double,3> ref_cylindrical_position = {0.0, 0.0, 2.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.data(),
                                            cylindrical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Neg. z-axis
  cartesian_position = {0.0, 0.0, -2.0};
  ref_cylindrical_position = {0.0, 0.0, -2.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.data(),
                                            cylindrical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Y-axis
  cartesian_position = {0.0, 2.0, 0.0};
  ref_cylindrical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.data(),
                                            cylindrical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Neg. y-axis
  cartesian_position = {0.0, -2.0, 0.0};
  ref_cylindrical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.data(),
                                            cylindrical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // X-axis
  cartesian_position = {2.0, 0.0, 0.0};
  ref_cylindrical_position = {2.0, 0.0, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.data(),
                                            cylindrical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Neg. x-axis
  cartesian_position = {-2.0, 0.0, 0.0};
  ref_cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            cartesian_position.data(),
                                            cylindrical_position.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );

  // Off axis
  cartesian_position = {1.0, 1.0, 1.0};
  ref_cylindrical_position =
    {sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                     cartesian_position[0],
                                                     cartesian_position[1],
                                                     cartesian_position[2],
                                                     cylindrical_position[0],
                                                     cylindrical_position[1],
                                                     cylindrical_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( cylindrical_position, ref_cylindrical_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that cylindrical spatial coordinates can be converted to Cartesian
// spatial coordinates
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateConversionPolicy,
                   convertToCartesianPosition )
{
  // Z-axis
  std::array<double,3> cylindrical_position = {0.0, 0.0, 2.0};

  std::array<double,3> cartesian_position;
  std::array<double,3> ref_cartesian_position = {0.0, 0.0, 2.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.data(),
                                              cartesian_position.data() );
                                            

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Neg. z-axis
  cylindrical_position = {0.0, 0.0, -2.0};
  ref_cartesian_position = {0.0, 0.0, -2.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.data(),
                                              cartesian_position.data() );
                                            

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Y-axis
  cylindrical_position = {2.0, Utility::PhysicalConstants::pi/2, 0.0};
  ref_cartesian_position = {0.0, 2.0, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.data(),
                                              cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Neg. y-axis
  cylindrical_position = {2.0, 3*Utility::PhysicalConstants::pi/2, 0.0};
  ref_cartesian_position = {0.0, -2.0, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.data(),
                                              cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // X-axis
  cylindrical_position = {2.0, 0.0, 0.0};
  ref_cartesian_position = {2.0, 0.0, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.data(),
                                              cartesian_position.data() );
                                            

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );


  // Neg. x-axis
  cylindrical_position = {2.0, Utility::PhysicalConstants::pi, 0.0};
  ref_cartesian_position = {-2.0, 0.0, 0.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              cylindrical_position.data(),
                                              cartesian_position.data() );
  Utility::clearVectorOfRoundingErrors( cartesian_position.data(), 1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );

  // Off axis
  cylindrical_position = {sqrt(2.0), Utility::PhysicalConstants::pi/4, 1.0};
  ref_cartesian_position = {1.0, 1.0, 1.0};

  Utility::CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                       cylindrical_position[0],
                                                       cylindrical_position[1],
                                                       cylindrical_position[2],
                                                       cartesian_position[0],
                                                       cartesian_position[1],
                                                       cartesian_position[2] );
                                            

  FRENSIE_CHECK_FLOATING_EQUALITY( cartesian_position, ref_cartesian_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
