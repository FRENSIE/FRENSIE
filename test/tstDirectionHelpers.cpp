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

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "DirectionHelpers.hpp"
#include "PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a direction is valid (lies on unit sphere)
TEUCHOS_UNIT_TEST( DirectionHelpers, validDirection )
{
  double direction[3] = {1.0, 1.0, 1.0};

  TEST_ASSERT( !FACEMC::validDirection( direction ) );

  direction[0] = 1.0/sqrt(3.0);
  direction[1] = 1.0/sqrt(3.0);
  direction[2] = 1.0/sqrt(3.0);

  TEST_ASSERT( FACEMC::validDirection( direction ) );
}

//---------------------------------------------------------------------------//
// Check that a direction can be normalized
TEUCHOS_UNIT_TEST( DirectionHelpers, normalizeDirection )
{
  double direction[3] = {1.0, 1.0, 1.0};

  FACEMC::normalizeDirection( direction );

  TEST_ASSERT( FACEMC::validDirection( direction ) );
}

//---------------------------------------------------------------------------//
// Check that the cosine of the angle between two vectors can be calculated
TEUCHOS_UNIT_TEST( DirectionHelpers, calculateCosineOfAngleBetweenVectors )
{
  double direction_a[3] = {1.0, 1.0, 1.0};
  FACEMC::normalizeDirection( direction_a );
  
  double direction_b[3] = {-1.0, -1.0, -1.0};
  FACEMC::normalizeDirection( direction_b );

  double angle_cosine = 
    FACEMC::calculateCosineOfAngleBetweenVectors( direction_a, direction_b );

  TEST_EQUALITY_CONST( angle_cosine, -1.0 );

  direction_b[0] *= -1.0;
  direction_b[1] *= -1.0;
  direction_b[2] *= -1.0;

  angle_cosine = 
    FACEMC::calculateCosineOfAngleBetweenVectors( direction_a, direction_b );

  TEST_EQUALITY_CONST( angle_cosine, 1.0 );

  direction_b[0] = 0.0;
  direction_b[1] = -1.0;
  direction_b[2] = 1.0;
  FACEMC::normalizeDirection( direction_b );

  angle_cosine = 
    FACEMC::calculateCosineOfAngleBetweenVectors( direction_a, direction_b );

  TEST_EQUALITY_CONST( angle_cosine, 0.0 );
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

  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle( 
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
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle( 
					       0.0,
					       FACEMC::PhysicalConstants::pi/2,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );
  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 1.0;
  ref_rotated_direction[2] = 0.0;
  
  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate x-axis to neg. y-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					     0.0,
					     3*FACEMC::PhysicalConstants::pi/2,
					     direction.getRawPtr(),
					     rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = -1.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate x-axis to z-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       FACEMC::PhysicalConstants::pi,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 1.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate x-axis to neg. z-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = -1.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );
  
  // Rotate y-axis to neg. y-axis
  direction[0] = 0.0;
  direction[1] = 1.0;
  direction[2] = 0.0;

  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       -1.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = -1.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate y-axis to x-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					     0.0,
					     3*FACEMC::PhysicalConstants::pi/2,
					     direction.getRawPtr(),
					     rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the y-axis to neg. x-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       FACEMC::PhysicalConstants::pi/2,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = -1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the y-axis to z-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       FACEMC::PhysicalConstants::pi,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 1.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the y-axis to neg. z-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = -1.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the z-axis to neg. z-axis
  direction[0] = 0.0;
  direction[1] = 0.0;
  direction[2] = 1.0;

  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       -1.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = -1.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the z-axis to x-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       FACEMC::PhysicalConstants::pi/2,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the z-axis to neg. x-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					     0.0,
					     3*FACEMC::PhysicalConstants::pi/2,
					     direction.getRawPtr(),
					     rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = -1.0;
  ref_rotated_direction[1] = 0.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the z-axis to y-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					     0.0,
					     FACEMC::PhysicalConstants::pi,
					     direction.getRawPtr(),
					     rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = 1.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );

  // Rotate the z-axis to neg. y-axis
  FACEMC::rotateDirectionThroughPolarAndAzimuthalAngle(
					       0.0,
					       0.0,
					       direction.getRawPtr(),
					       rotated_direction.getRawPtr() );

  ref_rotated_direction[0] = 0.0;
  ref_rotated_direction[1] = -1.0;
  ref_rotated_direction[2] = 0.0;

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( rotated_direction, 
				       ref_rotated_direction,
				       1e-15 );
}

//---------------------------------------------------------------------------//
// end tstDirectionHelpers.cpp
//---------------------------------------------------------------------------//
