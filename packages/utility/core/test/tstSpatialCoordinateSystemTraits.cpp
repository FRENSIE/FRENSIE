//---------------------------------------------------------------------------//
//!
//! \file   tstSpatialCoordinateSystemTraits.cpp
//! \author Alex Robinson
//! \brief  Spatial coordinate system traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Include
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_SpatialCoordinateSystemTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs.
//---------------------------------------------------------------------------//
typedef Utility::SpatialCoordinateSystemTraits<Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM> CartesianSpatialCoordinateSystemTraits;

typedef Utility::SpatialCoordinateSystemTraits<Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM> CylindricalSpatialCoordinateSystemTraits;

typedef Utility::SpatialCoordinateSystemTraits<Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM> SphericalSpatialCoordinateSystemTraits;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the primary spatial dimension of the Cartesian spatial coordinate
// system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   primarySpatialDimension )
{
  TEST_EQUALITY_CONST(
             CartesianSpatialCoordinateSystemTraits::primarySpatialDimension(),
             Utility::X_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary spatial dimension of the
// Cartesian spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   primarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST(
   CartesianSpatialCoordinateSystemTraits::primarySpatialDimensionLowerBound(),
   -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary spatial dimension of the
// Cartesian spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   primarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST(
   CartesianSpatialCoordinateSystemTraits::primarySpatialDimensionUpperBound(),
   std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial dimension of the Cartesian Spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   secondarySpatialDimension )
{
  TEST_EQUALITY_CONST(
             CartesianSpatialCoordinateSystemTraits::secondarySpatialDimension(),
             Utility::Y_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary spatial dimension of the
// Cartesian spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CartesianSpatialCoordinateSystemTraits::secondarySpatialDimensionLowerBound(),
                       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary spatial dimension of the
// Cartesian spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CartesianSpatialCoordinateSystemTraits::secondarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial dimension of the Cartesian Spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   tertiarySpatialDimension )
{
  TEST_EQUALITY_CONST( CartesianSpatialCoordinateSystemTraits::tertiarySpatialDimension(),
                       Utility::Z_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary spatial dimension of the
// Cartesian spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CartesianSpatialCoordinateSystemTraits::tertiarySpatialDimensionLowerBound(),
                       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary spatial dimension of the
// Cartesian spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CartesianSpatialCoordinateSystemTraits::tertiarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial dimension of the cylindrical spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   primarySpatialDimension )
{
  TEST_EQUALITY_CONST(
           CylindricalSpatialCoordinateSystemTraits::primarySpatialDimension(),
           Utility::R_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary spatial dimension of the
// cylindrical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CylindricalSpatialCoordinateSystemTraits::primarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary spatial dimension of the
// cylindrical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CylindricalSpatialCoordinateSystemTraits::primarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial dimension of the cylindrical Spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   secondarySpatialDimension )
{
  TEST_EQUALITY_CONST(
         CylindricalSpatialCoordinateSystemTraits::secondarySpatialDimension(),
         Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary spatial dimension of the
// cylindrical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CylindricalSpatialCoordinateSystemTraits::secondarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary spatial dimension of the
// cylindrical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CylindricalSpatialCoordinateSystemTraits::secondarySpatialDimensionUpperBound(),
                       2*Utility::PhysicalConstants::pi );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial dimension of the cylindrical Spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimension )
{
  TEST_EQUALITY_CONST(
          CylindricalSpatialCoordinateSystemTraits::tertiarySpatialDimension(),
          Utility::Z_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary spatial dimension of the
// cylindrical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CylindricalSpatialCoordinateSystemTraits::tertiarySpatialDimensionLowerBound(),
                       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary spatial dimension of the
// cylindrical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CylindricalSpatialCoordinateSystemTraits::tertiarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial dimension of the spherical spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   primarySpatialDimension )
{
  TEST_EQUALITY_CONST(
             SphericalSpatialCoordinateSystemTraits::primarySpatialDimension(),
             Utility::R_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary spatial dimension of the
// spherical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( SphericalSpatialCoordinateSystemTraits::primarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary spatial dimension of the
// spherical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( SphericalSpatialCoordinateSystemTraits::primarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial dimension of the spherical Spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   secondarySpatialDimension )
{
  TEST_EQUALITY_CONST(
           SphericalSpatialCoordinateSystemTraits::secondarySpatialDimension(),
           Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary spatial dimension of the
// spherical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( SphericalSpatialCoordinateSystemTraits::secondarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary spatial dimension of the
// spherical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( SphericalSpatialCoordinateSystemTraits::secondarySpatialDimensionUpperBound(),
                       2*Utility::PhysicalConstants::pi );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial dimension of the spherical Spatial
// coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimension )
{
  TEST_EQUALITY_CONST(
            SphericalSpatialCoordinateSystemTraits::tertiarySpatialDimension(),
            Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary spatial dimension of the
// spherical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionLowerBound )
{
  TEST_EQUALITY_CONST( SphericalSpatialCoordinateSystemTraits::tertiarySpatialDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary spatial dimension of the
// spherical spatial coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionUpperBound )
{
  TEST_EQUALITY_CONST( SphericalSpatialCoordinateSystemTraits::tertiarySpatialDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// end tstSpatialCoordinateSystemTraits.cpp
//---------------------------------------------------------------------------//
