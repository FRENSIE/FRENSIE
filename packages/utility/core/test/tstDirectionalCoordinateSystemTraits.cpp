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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DirectionalCoordinateSystemTraits.hpp"

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
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimension )
{
  TEST_EQUALITY_CONST(
     CartesianDirectionalCoordinateSystemTraits::primaryDirectionalDimension(),
     Utility::U_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary directional dimension of the
// Cartesian directional coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::primaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary directional dimension of the
// Cartesian directional coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::primaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional dimension of the Cartesian Directional
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimension )
{
  TEST_EQUALITY_CONST(
   CartesianDirectionalCoordinateSystemTraits::secondaryDirectionalDimension(),
   Utility::V_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary directional dimension of the
// Cartesian directional coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary directional dimension of the
// Cartesian directional coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional dimension of the Cartesian Directional
// coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimension )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::tertiaryDirectionalDimension(),
                       Utility::W_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary directional dimension of the
// Cartesian directional coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionLowerBound )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary directional dimension of the
// Cartesian directional coordinate system can be returned
TEUCHOS_UNIT_TEST( CartesianDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionUpperBound )
{
  TEST_EQUALITY_CONST( CartesianDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the primary directional dimension of the spherical directional
// coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimension )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::primaryDirectionalDimension(),
                       Utility::R_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the primary directional dimension of the
// spherical directional coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionLowerBound )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::primaryDirectionalDimensionLowerBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the primary directional dimension of the
// spherical directional coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   primaryDirectionalDimensionUpperBound )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::primaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the secondary directional dimension of the spherical Directional
// coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimension )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::secondaryDirectionalDimension(),
                       Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the secondary directional dimension of the
// spherical directional coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionLowerBound )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionLowerBound(),
                       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the secondary directional dimension of the
// spherical directional coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   secondaryDirectionalDimensionUpperBound )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::secondaryDirectionalDimensionUpperBound(),
                       2*Utility::PhysicalConstants::pi );
}

//---------------------------------------------------------------------------//
// Check that the tertiary directional dimension of the spherical Directional
// coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimension )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::tertiaryDirectionalDimension(),
                       Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the tertiary directional dimension of the
// spherical directional coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionLowerBound )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionLowerBound(),
                       -1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the tertiary directional dimension of the
// spherical directional coordinate system can be returned
TEUCHOS_UNIT_TEST( SphericalDirectionalCoordinateSystemTraits,
                   tertiaryDirectionalDimensionUpperBound )
{
  TEST_EQUALITY_CONST( SphericalDirectionalCoordinateSystemTraits::tertiaryDirectionalDimensionUpperBound(),
                       1.0 );
}

//---------------------------------------------------------------------------//
// end tstDirectionalCoordinateSystemTraits.cpp
//---------------------------------------------------------------------------//
