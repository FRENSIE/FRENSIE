//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalCoordinateSystemTraits.cpp
//! \author Alex Robinson
//! \brief  Directional coordinate system traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// FRENSIE Includes
#include "Utility_DirectionalCoordinateSystemTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs.
//---------------------------------------------------------------------------//
typedef Utility::DirectionalCoordinateSystemTraits<Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM> CartesianDirectionalCoordinateSystemTraits;

typedef Utility::DirectionalCoordinateSystemTraits<Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM> SphericalDirectionalCoordinateSystemTraits;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the primary directional dimension of the Cartesian directional coordinate
// system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimension )
{
  FRENSIE_CHECK_EQUAL(
     CartesianDirectionalCoordinateSystemTraits::primaryDirectionalDimension(),
     Utility::U_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary directional dimension of the
// Cartesian directional coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::primaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary directional dimension of the
// Cartesian directional coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::primaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional dimension of the Cartesian Directional
// coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimension )
{
  FRENSIE_CHECK_EQUAL(
   CartesianDirectionalCoordinateSystemTraits::secondaryDirectionalDimension(),
   Utility::V_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary directional dimension of the
// Cartesian directional coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary directional dimension of the
// Cartesian directional coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional dimension of the Cartesian Directional
// coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimension )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::tertiaryDirectionalDimension(),
                       Utility::W_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary directional dimension of the
// Cartesian directional coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary directional dimension of the
// Cartesian directional coordinate system can be returned
FRENSIE_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( CartesianDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional dimension of the spherical directional
// coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimension )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::primaryDirectionalDimension(),
                       Utility::R_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary directional dimension of the
// spherical directional coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::primaryDirectionalDimensionLowerBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary directional dimension of the
// spherical directional coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::primaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional dimension of the spherical Directional
// coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimension )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::secondaryDirectionalDimension(),
                       Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary directional dimension of the
// spherical directional coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary directional dimension of the
// spherical directional coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionUpperBound(),
                       2*Utility::PhysicalConstants::pi );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional dimension of the spherical Directional
// coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimension )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::tertiaryDirectionalDimension(),
                       Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary directional dimension of the
// spherical directional coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionLowerBound )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary directional dimension of the
// spherical directional coordinate system can be returned
FRENSIE_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionUpperBound )
{
  FRENSIE_CHECK_EQUAL( SphericalDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// end tstDirectionalCoordinateSystemTraits.cpp
//---------------------------------------------------------------------------//
