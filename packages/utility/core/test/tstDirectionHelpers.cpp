//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionHelpers.cpp
//! \author Alex Robinson
//! \brief  Direction helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a direction is valid (lies on unit sphere)
TEUCHOS_UNIT_TEST( DirectionHelpers, validDirection )
{
  double direction[3] = {1.0, 1.0, 1.0};

  TEST_ASSERT( !Utility::validDirection( direction ) );

  direction[0] = 1.0/sqrt(3.0);
  direction[1] = 1.0/sqrt(3.0);
  direction[2] = 1.0/sqrt(3.0);

  TEST_ASSERT( Utility::validDirection( direction ) );
}

//---------------------------------------------------------------------------//
// Check that a direction can be normalized
TEUCHOS_UNIT_TEST( DirectionHelpers, normalizeDirection )
{
  double direction[3] = {1.0, 1.0, 1.0};

  Utility::normalizeDirection( direction );

  TEST_ASSERT( Utility::validDirection( direction ) );
}

//---------------------------------------------------------------------------//
// Check that the cosine of the angle between two vectors can be calculated
TEUCHOS_UNIT_TEST( DirectionHelpers, calculateCosineOfAngleBetweenVectors )
{
  double direction_a[3] = {1.0, 1.0, 1.0};
  Utility::normalizeDirection( direction_a );
  
  double direction_b[3] = {-1.0, -1.0, -1.0};
  Utility::normalizeDirection( direction_b );

  double angle_cosine = 
    Utility::calculateCosineOfAngleBetweenVectors( direction_a, direction_b );

  TEST_EQUALITY_CONST( angle_cosine, -1.0 );

  direction_b[0] *= -1.0;
  direction_b[1] *= -1.0;
  direction_b[2] *= -1.0;

  angle_cosine = 
    Utility::calculateCosineOfAngleBetweenVectors( direction_a, direction_b );

  TEST_EQUALITY_CONST( angle_cosine, 1.0 );

  direction_b[0] = 0.0;
  direction_b[1] = -1.0;
  direction_b[2] = 1.0;
  Utility::normalizeDirection( direction_b );

  angle_cosine = 
    Utility::calculateCosineOfAngleBetweenVectors( direction_a, direction_b );

  TEST_EQUALITY_CONST( angle_cosine, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a direction can be reflected about a unit normal
TEUCHOS_UNIT_TEST( DirectionHelpers, reflectDirection )
{
  // X-axis reflection
  double direction[3] = {1.0, 0.0, 0.0};

  double unit_normal[3] = {1.0, 0.0, 0.0};

  double reflected_direction[3];

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], -1.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  unit_normal[0] = -1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], -1.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  direction[0] = -1.0;
  direction[1] = 0.0;
  direction[2] = 0.0;

  unit_normal[0] = 1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 1.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  unit_normal[0] = -1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 1.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  // Y-axis reflection
  direction[0] = 0.0;
  direction[1] = 1.0;
  direction[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], -1.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = -1.0;
  unit_normal[2] = 0.0;
  
  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], -1.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  direction[0] = 0.0;
  direction[1] = -1.0;
  direction[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 1.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = -1.0;
  unit_normal[2] = 0.0;
  
  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 1.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  // Z-axis reflection
  direction[0] = 0.0;
  direction[1] = 0.0;
  direction[2] = 1.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 1.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], -1.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;
  
  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], -1.0 );

  direction[0] = 0.0;
  direction[1] = 0.0;
  direction[2] = -1.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 1.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 1.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;
  
  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_EQUALITY_CONST( reflected_direction[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_direction[2], 1.0 );

  // Off-axis reflection
  direction[0] = 1/sqrt(2.0);
  direction[1] = 1/sqrt(2.0);
  direction[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_FLOATING_EQUALITY( reflected_direction[0], 1/sqrt(2.0), 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_direction[1], -1/sqrt(2.0), 1e-12 );
  TEST_EQUALITY_CONST( reflected_direction[2], 0.0 );

  direction[0] = 1/sqrt(3.0);
  direction[1] = 1/sqrt(3.0);
  direction[2] = 1/sqrt(3.0);

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_FLOATING_EQUALITY( reflected_direction[0], 1/sqrt(3.0), 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_direction[1], 1/sqrt(3.0), 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_direction[2], -1/sqrt(3.0), 1e-12 );

  direction[0] = 0.0;
  direction[1] = 0.0;
  direction[2] = 1.0;

  unit_normal[0] = -1/sqrt(3.0);
  unit_normal[1] = -1/sqrt(3.0);
  unit_normal[2] = -1/sqrt(3.0);

  Utility::reflectDirection( direction, unit_normal, reflected_direction );

  TEST_FLOATING_EQUALITY( reflected_direction[0], -2.0/3, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_direction[1], -2.0/3, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_direction[2], 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a direction can be rotated through a polar and azimuthal angle
TEUCHOS_UNIT_TEST( DirectionHelpers, 
		   rotateDirectionThroughPolarAndAzimuthalAngle )
{
  // Rotate x-axis to neg. x-axis
  Teuchos::Array<double> direction( 3 );
  direction[0] = 1.0;
  direction[1] = 0.0;
  direction[2] = 0.0;

  Teuchos::Array<double> rotated_direction( 3 );

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
					       -1.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  Teuchos::Array<double> ref_rotated_direction( 3 );
  ref_rotated_direction[0] = -1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				ref_rotated_direction,
				1e-15 );

  // Rotate x-axis to y-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
					      0.0,
					      Utility::PhysicalConstants::pi/2,
					      direction.getRawPtr(),
					      rotated_direction.getRawPtr() );
  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 1.0;
  ref_rotated_direction[2] = 0.0;
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate x-axis to neg. y-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    direction.getRawPtr(),
					    rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = -1.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate x-axis to z-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       Utility::PhysicalConstants::pi,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate x-axis to neg. z-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = -1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );
  
  // Rotate y-axis to neg. y-axis
  direction[0] = 0.0;
  direction[1] = 1.0;
  direction[2] = 0.0;

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       -1.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = -1.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate y-axis to x-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    direction.getRawPtr(),
					    rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the y-axis to neg. x-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					      0.0,
					      Utility::PhysicalConstants::pi/2,
					      direction.getRawPtr(),
					      rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = -1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the y-axis to z-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       Utility::PhysicalConstants::pi,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the y-axis to neg. z-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = -1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the z-axis to neg. z-axis
  direction[0] = 0.0;
  direction[1] = 0.0;
  direction[2] = 1.0;

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       -1.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = -1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the z-axis to x-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					      0.0,
					      Utility::PhysicalConstants::pi/2,
					      direction.getRawPtr(),
					      rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the z-axis to neg. x-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    direction.getRawPtr(),
					    rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = -1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the z-axis to y-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					     0.0,
					     Utility::PhysicalConstants::pi,
					     direction.getRawPtr(),
					     rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 1.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );

  // Rotate the z-axis to neg. y-axis
  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = -1.0;
  ref_rotated_direction[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
					ref_rotated_direction,
					1e-15 );
}

//---------------------------------------------------------------------------//
// end tstDirectionHelpers.cpp
//---------------------------------------------------------------------------//
