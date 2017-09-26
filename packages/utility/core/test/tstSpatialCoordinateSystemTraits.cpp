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

// FRENSIE Includes
#include "Utility_SpatialCoordinateSystemTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

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
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   primarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
             CartesianSpatialCoordinateSystemTraits::primarySpatialDimension(),
             Utility::X_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary spatial dimension of the
// Cartesian spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   primarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL(
   CartesianSpatialCoordinateSystemTraits::primarySpatialDimensionLowerBound(),
   -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary spatial dimension of the
// Cartesian spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   primarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL(
   CartesianSpatialCoordinateSystemTraits::primarySpatialDimensionUpperBound(),
   std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial dimension of the Cartesian Spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   secondarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
             CartesianSpatialCoordinateSystemTraits::secondarySpatialDimension(),
             Utility::Y_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary spatial dimension of the
// Cartesian spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CartesianSpatialCoordinateSystemTraits::secondarySpatialDimensionLowerBound(),
                       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary spatial dimension of the
// Cartesian spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CartesianSpatialCoordinateSystemTraits::secondarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial dimension of the Cartesian Spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   tertiarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL( CartesianSpatialCoordinateSystemTraits::tertiarySpatialDimension(),
                       Utility::Z_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary spatial dimension of the
// Cartesian spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CartesianSpatialCoordinateSystemTraits::tertiarySpatialDimensionLowerBound(),
                       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary spatial dimension of the
// Cartesian spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CartesianSpatialCoordinateSystemTraits::tertiarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial dimension of the cylindrical spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   primarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
           CylindricalSpatialCoordinateSystemTraits::primarySpatialDimension(),
           Utility::R_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary spatial dimension of the
// cylindrical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CylindricalSpatialCoordinateSystemTraits::primarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary spatial dimension of the
// cylindrical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CylindricalSpatialCoordinateSystemTraits::primarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial dimension of the cylindrical Spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   secondarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
         CylindricalSpatialCoordinateSystemTraits::secondarySpatialDimension(),
         Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary spatial dimension of the
// cylindrical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CylindricalSpatialCoordinateSystemTraits::secondarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary spatial dimension of the
// cylindrical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CylindricalSpatialCoordinateSystemTraits::secondarySpatialDimensionUpperBound(),
                       2*Utility::PhysicalConstants::pi );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial dimension of the cylindrical Spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
          CylindricalSpatialCoordinateSystemTraits::tertiarySpatialDimension(),
          Utility::Z_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary spatial dimension of the
// cylindrical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CylindricalSpatialCoordinateSystemTraits::tertiarySpatialDimensionLowerBound(),
                       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary spatial dimension of the
// cylindrical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( CylindricalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CylindricalSpatialCoordinateSystemTraits::tertiarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the primary spatial dimension of the spherical spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   primarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
             SphericalSpatialCoordinateSystemTraits::primarySpatialDimension(),
             Utility::R_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary spatial dimension of the
// spherical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( SphericalSpatialCoordinateSystemTraits::primarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary spatial dimension of the
// spherical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   primarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( SphericalSpatialCoordinateSystemTraits::primarySpatialDimensionUpperBound(),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the secondary spatial dimension of the spherical Spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   secondarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
           SphericalSpatialCoordinateSystemTraits::secondarySpatialDimension(),
           Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary spatial dimension of the
// spherical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( SphericalSpatialCoordinateSystemTraits::secondarySpatialDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary spatial dimension of the
// spherical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   secondarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( SphericalSpatialCoordinateSystemTraits::secondarySpatialDimensionUpperBound(),
                       2*Utility::PhysicalConstants::pi );
}

//---------------------------------------------------------------------------//
// Check that the tertiary spatial dimension of the spherical Spatial
// coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimension )
{
  FRENSIE_CHECK_EQUAL(
            SphericalSpatialCoordinateSystemTraits::tertiarySpatialDimension(),
            Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary spatial dimension of the
// spherical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( SphericalSpatialCoordinateSystemTraits::tertiarySpatialDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary spatial dimension of the
// spherical spatial coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalSpatialCoordinateSystemTraits,
                   tertiarySpatialDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( SphericalSpatialCoordinateSystemTraits::tertiarySpatialDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// end tstSpatialCoordinateSystemTraits.cpp
//---------------------------------------------------------------------------//
