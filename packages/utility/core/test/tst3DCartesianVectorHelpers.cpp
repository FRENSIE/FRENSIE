//---------------------------------------------------------------------------//
//!
//! \file   tst3DCartesianVectorHelpers.cpp
//! \author Alex Robinson
//! \brief  3D Cartesian vector helper function unit tests
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
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the magnitude of a vector can be calculated
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, vectorMagnitude )
{
  double vector[3] = {1.0, 1.0, 1.0};

  double vector_magnitude = Utility::vectorMagnitude( vector );

  TEST_EQUALITY( vector_magnitude, sqrt(3.0) );

  vector_magnitude = Utility::vectorMagnitude( 1.0, 0.0, 0.0 );

  TEST_EQUALITY_CONST( vector_magnitude, 1.0 );

  vector_magnitude = Utility::vectorMagnitude( 0.0, -1.0, 0.0 );

  TEST_EQUALITY_CONST( vector_magnitude, 1.0 );

  vector_magnitude = Utility::vectorMagnitude( 0.0, 0.0, 1.0 );

  TEST_EQUALITY_CONST( vector_magnitude, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a vector is normalized
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, isUnitVector )
{
  double vector[3] = {1.0, 1.0, 1.0};

  TEST_ASSERT( !Utility::isUnitVector( vector ) );

  vector[0] /= sqrt(3.0);
  vector[1] /= sqrt(3.0);
  vector[2] /= sqrt(3.0);

  TEST_ASSERT( Utility::isUnitVector( vector ) );
  TEST_ASSERT( Utility::isUnitVector( 1.0, 0.0, 0.0 ) );
  TEST_ASSERT( Utility::isUnitVector( 0.0, 1.0, 0.0 ) );
  TEST_ASSERT( Utility::isUnitVector( 0.0, 0.0, -1.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be normalized
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, normalizeVector )
{
  double vector[3] = {1.0, 1.0, 1.0};

  Utility::normalizeVector( vector );

  TEST_EQUALITY( vector[0], 1.0/sqrt(3.0) );
  TEST_EQUALITY( vector[1], 1.0/sqrt(3.0) );
  TEST_EQUALITY( vector[2], 1.0/sqrt(3.0) );
  TEST_ASSERT( Utility::isUnitVector( vector ) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be normalized and that its magnitude can be returned
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, normalizeVectorAndReturnMagnitude )
{
  double vector[3] = {1.0, 1.0, 1.0};

  double magnitude = Utility::normalizeVectorAndReturnMagnitude( vector );

  TEST_EQUALITY( magnitude, sqrt(3.0) );
  TEST_ASSERT( Utility::isUnitVector( vector ) );

  vector[0] = 1.0;
  vector[1] = 0.0;
  vector[2] = 1.0;
  
  magnitude = Utility::normalizeVectorAndReturnMagnitude(
                                             vector[0], vector[1], vector[2] );

  TEST_EQUALITY( magnitude, sqrt(2.0) );
  TEST_ASSERT( Utility::isUnitVector( vector ) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be cleared of rounding errors
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, clearVectorOfRoundingErrors )
{
  Teuchos::Tuple<double,3> vector = Teuchos::tuple( 1.0, 1.0, 1.0 );
  Teuchos::Tuple<double,3> ref_vector = vector;
  
  Utility::clearVectorOfRoundingErrors( vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( -1.0, -1.0, -1.0 );
  ref_vector = vector;

  Utility::clearVectorOfRoundingErrors( vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( 1e-15, 1.0, 1.0 );
  ref_vector = Teuchos::tuple( 0.0, 1.0, 1.0 );

  Utility::clearVectorOfRoundingErrors( vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( -1e-15, 1.0, 1.0 );
  ref_vector = Teuchos::tuple( 0.0, 1.0, 1.0 );

  Utility::clearVectorOfRoundingErrors( vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( 1e-14, 1e-14, 2.0 );
  ref_vector = Teuchos::tuple( 0.0, 0.0, 2.0 );

  Utility::clearVectorOfRoundingErrors( vector.getRawPtr(), 1e-14 );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( 1e-14, -1e-14, 2.0 );
  ref_vector = Teuchos::tuple( 0.0, 0.0, 2.0 );

  Utility::clearVectorOfRoundingErrors( vector.getRawPtr(), 1e-14 );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( -1e-15, -2.0, 1e-15 );
  ref_vector = Teuchos::tuple( 0.0, -2.0, 0.0 );

  Utility::clearVectorOfRoundingErrors( vector[0], vector[1], vector[2] );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );

  vector = Teuchos::tuple( 1e-14, -2.0, -1e-14 );
  ref_vector = Teuchos::tuple( 0.0, -2.0, 0.0 );

  Utility::clearVectorOfRoundingErrors(
                                      vector[0], vector[1], vector[2], 1e-14 );

  TEST_COMPARE_ARRAYS( vector(), ref_vector() );
}

//---------------------------------------------------------------------------//
// Check that a unit vector can be cleared of rounding errors
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, clearUnitVectorOfRoundingErrors )
{
  Teuchos::Tuple<double,3> unit_vector =
    Teuchos::tuple( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  Teuchos::Tuple<double,3> ref_unit_vector = unit_vector;
  
  Utility::clearUnitVectorOfRoundingErrors( unit_vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector=
    Teuchos::tuple( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );
  ref_unit_vector = unit_vector;

  Utility::clearUnitVectorOfRoundingErrors( unit_vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector = Teuchos::tuple( 1e-16, sqrt(2.0)/2, sqrt(2.0)/2 );
  ref_unit_vector = Teuchos::tuple( 0.0, sqrt(2.0)/2, sqrt(2.0)/2 );

  Utility::clearUnitVectorOfRoundingErrors( unit_vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector = Teuchos::tuple( -1e-16, sqrt(2.0)/2, sqrt(2.0)/2 );
  ref_unit_vector = Teuchos::tuple( 0.0, sqrt(2.0)/2, sqrt(2.0)/2 );

  Utility::clearUnitVectorOfRoundingErrors( unit_vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector = Teuchos::tuple( 1e-16, 2e-16, 1.0 );
  ref_unit_vector = Teuchos::tuple( 0.0, 0.0, 1.0 );

  Utility::clearUnitVectorOfRoundingErrors( unit_vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector = Teuchos::tuple( 1e-16, -2e-16, 1.0 );
  ref_unit_vector = Teuchos::tuple( 0.0, 0.0, 1.0 );

  Utility::clearUnitVectorOfRoundingErrors( unit_vector.getRawPtr() );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector = Teuchos::tuple( 1e-15, -1.0, 1e-15 );
  ref_unit_vector = Teuchos::tuple( 0.0, -1.0, 0.0 );

  Utility::clearUnitVectorOfRoundingErrors( unit_vector[0],
                                            unit_vector[1],
                                            unit_vector[2],
                                            1e-14 );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );

  unit_vector = Teuchos::tuple( 1e-15, -1.0, -1e-15 );
  ref_unit_vector = Teuchos::tuple( 0.0, -1.0, 0.0 );

  Utility::clearUnitVectorOfRoundingErrors( unit_vector[0],
                                            unit_vector[1],
                                            unit_vector[2],
                                            1e-14 );

  TEST_COMPARE_ARRAYS( unit_vector(), ref_unit_vector() );
}

//---------------------------------------------------------------------------//
// Check that the cosine between two unit vectors can be calculated
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   calculateCosineOfAngleBetweenUnitVectors )
{
  double unit_vector_a[3] = {1.0, 1.0, 1.0};
  Utility::normalizeVector( unit_vector_a );
  
  double unit_vector_b[3] = {-1.0, -1.0, -1.0};
  Utility::normalizeVector( unit_vector_b );

  double angle_cosine = Utility::calculateCosineOfAngleBetweenUnitVectors(
                                                unit_vector_a, unit_vector_b );

  TEST_EQUALITY_CONST( angle_cosine, -1.0 );

  unit_vector_b[0] *= -1.0;
  unit_vector_b[1] *= -1.0;
  unit_vector_b[2] *= -1.0;

  angle_cosine = Utility::calculateCosineOfAngleBetweenUnitVectors(
                                                unit_vector_a, unit_vector_b );

  TEST_EQUALITY_CONST( angle_cosine, 1.0 );

  unit_vector_b[0] = 0.0;
  unit_vector_b[1] = -1.0;
  unit_vector_b[2] = 1.0;
  Utility::normalizeVector( unit_vector_b );

  angle_cosine = Utility::calculateCosineOfAngleBetweenUnitVectors(
                                                unit_vector_a, unit_vector_b );

  TEST_EQUALITY_CONST( angle_cosine, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the cosine between two vectors can be calculated
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   calculateCosineOfAngleBetweenVectors )
{
  double vector_a[3] = {1.0, 1.0, 1.0};
  double vector_b[3] = {-1.0, -1.0, -1.0};

  double angle_cosine =
    Utility::calculateCosineOfAngleBetweenVectors( vector_a, vector_b );

  TEST_EQUALITY_CONST( angle_cosine, -1.0 );

  vector_b[0] = 1.0;
  vector_b[1] = 1.0;
  vector_b[2] = 1.0;

  angle_cosine =
    Utility::calculateCosineOfAngleBetweenVectors( vector_a, vector_b );

  TEST_EQUALITY_CONST( angle_cosine, 1.0 );

  vector_b[0] = 0.0;
  vector_b[1] = -1.0;
  vector_b[2] = 1.0;

  angle_cosine =
    Utility::calculateCosineOfAngleBetweenVectors( vector_a, vector_b );

  TEST_EQUALITY_CONST( angle_cosine, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit vector can be reflected about a unit normal
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, reflectUnitVector )
{
  // X-axis reflection
  double unit_vector[3] = {1.0, 0.0, 0.0};

  double unit_normal[3] = {1.0, 0.0, 0.0};

  double reflected_unit_vector[3];

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], -1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_normal[0] = -1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], -1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_vector[0] = -1.0;
  unit_vector[1] = 0.0;
  unit_vector[2] = 0.0;

  unit_normal[0] = 1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_normal[0] = -1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  // Y-axis reflection
  unit_vector[0] = 0.0;
  unit_vector[1] = 1.0;
  unit_vector[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], -1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = -1.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], -1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_vector[0] = 0.0;
  unit_vector[1] = -1.0;
  unit_vector[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = -1.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 1.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  // Z-axis reflection
  unit_vector[0] = 0.0;
  unit_vector[1] = 0.0;
  unit_vector[2] = 1.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 1.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], -1.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], -1.0 );

  unit_vector[0] = 0.0;
  unit_vector[1] = 0.0;
  unit_vector[2] = -1.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 1.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 1.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_EQUALITY_CONST( reflected_unit_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 1.0 );

  // Off-axis reflection
  unit_vector[0] = 1/sqrt(2.0);
  unit_vector[1] = 1/sqrt(2.0);
  unit_vector[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_FLOATING_EQUALITY( reflected_unit_vector[0], 1/sqrt(2.0), 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_unit_vector[1], -1/sqrt(2.0), 1e-12 );
  TEST_EQUALITY_CONST( reflected_unit_vector[2], 0.0 );

  unit_vector[0] = 1/sqrt(3.0);
  unit_vector[1] = 1/sqrt(3.0);
  unit_vector[2] = 1/sqrt(3.0);

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_FLOATING_EQUALITY( reflected_unit_vector[0], 1/sqrt(3.0), 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_unit_vector[1], 1/sqrt(3.0), 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_unit_vector[2], -1/sqrt(3.0), 1e-12 );

  unit_vector[0] = 0.0;
  unit_vector[1] = 0.0;
  unit_vector[2] = 1.0;

  unit_normal[0] = -1/sqrt(3.0);
  unit_normal[1] = -1/sqrt(3.0);
  unit_normal[2] = -1/sqrt(3.0);

  Utility::reflectUnitVector( unit_vector, unit_normal, reflected_unit_vector );

  TEST_FLOATING_EQUALITY( reflected_unit_vector[0], -2.0/3, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_unit_vector[1], -2.0/3, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_unit_vector[2], 1.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a vector can be reflected about a unit normal
TEUCHOS_UNIT_TEST( CartesianVectorHelpers, reflectVector )
{
  // X-axis reflection
  double vector[3] = {2.0, 0.0, 0.0};

  double unit_normal[3] = {1.0, 0.0, 0.0};

  double reflected_vector[3];

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], -2.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  unit_normal[0] = -1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], -2.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  vector[0] = -2.0;
  vector[1] = 0.0;
  vector[2] = 0.0;

  unit_normal[0] = 1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 2.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  unit_normal[0] = -1.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 2.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  // Y-axis reflection
  vector[0] = 0.0;
  vector[1] = 2.0;
  vector[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], -2.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = -1.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], -2.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  vector[0] = 0.0;
  vector[1] = -2.0;
  vector[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 2.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = -1.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 2.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  // Z-axis reflection
  vector[0] = 0.0;
  vector[1] = 0.0;
  vector[2] = 2.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 1.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], -2.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], -2.0 );

  vector[0] = 0.0;
  vector[1] = 0.0;
  vector[2] = -2.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = 1.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 2.0 );

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_EQUALITY_CONST( reflected_vector[0], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[1], 0.0 );
  TEST_EQUALITY_CONST( reflected_vector[2], 2.0 );

  // Off-axis reflection
  vector[0] = 1.0;
  vector[1] = 1.0;
  vector[2] = 0.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 1.0;
  unit_normal[2] = 0.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_FLOATING_EQUALITY( reflected_vector[0], 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_vector[1], -1.0, 1e-12 );
  TEST_EQUALITY_CONST( reflected_vector[2], 0.0 );

  vector[0] = 1.0;
  vector[1] = 1.0;
  vector[2] = 1.0;

  unit_normal[0] = 0.0;
  unit_normal[1] = 0.0;
  unit_normal[2] = -1.0;

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_FLOATING_EQUALITY( reflected_vector[0], 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_vector[1], 1.0, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_vector[2], -1.0, 1e-12 );

  vector[0] = 0.0;
  vector[1] = 0.0;
  vector[2] = 2.0;

  unit_normal[0] = -1/sqrt(3.0);
  unit_normal[1] = -1/sqrt(3.0);
  unit_normal[2] = -1/sqrt(3.0);

  Utility::reflectVector( vector, unit_normal, reflected_vector );

  TEST_FLOATING_EQUALITY( reflected_vector[0], -4.0/3, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_vector[1], -4.0/3, 1e-12 );
  TEST_FLOATING_EQUALITY( reflected_vector[2], 2.0/3.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a local vector can be converted to a global vector
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   convertLocalVectorToGlobalVector_same_origin )
{
  // Global x-axis aligned local z-axis
  Teuchos::Array<double> local_z_axis_wrt_gcs( 3 );
  local_z_axis_wrt_gcs[0] = 1.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Local z-axis ==> global x-axis
  Teuchos::Array<double> local_vector( 3 );
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = 2.0;

  Teuchos::Array<double> global_vector( 3 );

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  Teuchos::Array<double> ref_global_vector( 3 );
  ref_global_vector[0] = 2.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis ==> global neg. x-axis
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = -2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -2.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis ==> global y-axis
  local_vector[0] = 0.0;
  local_vector[1] = 2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 2.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis ==> global neg. y-axis
  local_vector[0] = 0.0;
  local_vector[1] = -2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = -2.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis ==> global neg. z-axis
  local_vector[0] = 2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
  
  // Local neg. x-axis ==> global z-axis
  local_vector[0] = -2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Global y-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 1.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Local z-axis ==> global y-axis
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = 2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 2.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis ==> global neg. y-axis
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = -2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = -2.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis ==> global neg. x-axis
  local_vector[0] = 0.0;
  local_vector[1] = 2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -2.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis ==> global x-axis
  local_vector[0] = 0.0;
  local_vector[1] = -2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 2.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis ==> global neg. z-axis
  local_vector[0] = 2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
  
  // Local neg. x-axis ==> global z-axis
  local_vector[0] = -2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Global z-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 1.0;

  // Local z-axis ==> global z-axis
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = 2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis ==> global neg. z-axis
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = -2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis ==> global y-axis
  local_vector[0] = 0.0;
  local_vector[1] = 2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = 2.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis ==> global neg. y-axis
  local_vector[0] = 0.0;
  local_vector[1] = -2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 0.0;
  ref_global_vector[1] = -2.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis ==> global x-axis
  local_vector[0] = 2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 2.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
  
  // Local neg. x-axis ==> global neg. x-axis
  local_vector[0] = -2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -2.0;
  ref_global_vector[1] = 0.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Off global axis local z-axis
  local_z_axis_wrt_gcs[0] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[1] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[2] = 1.0/sqrt(3.0);

  // Local z-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, 0.0, 2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = 2.0/sqrt(3.0);
  ref_global_vector[1] = 2.0/sqrt(3.0);
  ref_global_vector[2] = 2.0/sqrt(3.0);

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, 0.0, -2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = -2.0/sqrt(3.0);
  ref_global_vector[1] = -2.0/sqrt(3.0);
  ref_global_vector[2] = -2.0/sqrt(3.0);

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, 2.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = -sqrt(2.0);
  ref_global_vector[1] = sqrt(2.0);
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, -2.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );
  
  ref_global_vector[0] = sqrt(2.0);
  ref_global_vector[1] = -sqrt(2.0);
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis
  Utility::convertLocalVectorToGlobalVector( 2.0, 0.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = 2.0/sqrt(6.0);
  ref_global_vector[1] = 2.0/sqrt(6.0);
  ref_global_vector[2] = -sqrt(8.0/3.0);

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. x-axis
  Utility::convertLocalVectorToGlobalVector( -2.0, 0.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = -2.0/sqrt(6.0);
  ref_global_vector[1] = -2.0/sqrt(6.0);
  ref_global_vector[2] = sqrt(8.0/3.0);

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a local vector can be converted to a global vector
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   convertLocalVectorToGlobalVector_diff_origin )
{
  // Global x-axis aligned local z-axis
  Teuchos::Array<double> local_z_axis_wrt_gcs( 3 );
  local_z_axis_wrt_gcs[0] = 1.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Origin of local coordinate system w.r.t. global coordinate system
  Teuchos::Array<double> local_origin_wrt_gcs( 3 );
  local_origin_wrt_gcs[0] = -1.0;
  local_origin_wrt_gcs[1] = 1.0;
  local_origin_wrt_gcs[2] = 2.0;

  // Local z-axis ==> global x-axis
  Teuchos::Array<double> local_vector( 3 );
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = 2.0;

  Teuchos::Array<double> global_vector( 3 );

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  Teuchos::Array<double> ref_global_vector( 3 );
  ref_global_vector[0] = 1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis ==> global neg. x-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = -2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -3.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis ==> global y-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 3.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis ==> global neg. y-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = -2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = -1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis ==> global neg. z-axis (before translation)
  local_vector[0] = 2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
  
  // Local neg. x-axis ==> global z-axis (before translation)
  local_vector[0] = -2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 4.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Global y-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 1.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Local z-axis ==> global y-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = 2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 3.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis ==> global neg. y-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = -2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = -1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis ==> global neg. x-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -3.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis ==> global x-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = -2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis ==> global neg. z-axis (before translation)
  local_vector[0] = 2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
  
  // Local neg. x-axis ==> global z-axis (before translation)
  local_vector[0] = -2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 4.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Global z-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 1.0;

  // Local z-axis ==> global z-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = 2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 4.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis ==> global neg. z-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 0.0;
  local_vector[2] = -2.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis ==> global y-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = 2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = 3.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis ==> global neg. y-axis (before translation)
  local_vector[0] = 0.0;
  local_vector[1] = -2.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -1.0;
  ref_global_vector[1] = -1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis ==> global x-axis (before translation)
  local_vector[0] = 2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = 1.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );
  
  // Local neg. x-axis ==> global neg. x-axis (before translation)
  local_vector[0] = -2.0;
  local_vector[1] = 0.0;
  local_vector[2] = 0.0;

  Utility::convertLocalVectorToGlobalVector( local_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector.getRawPtr() );

  ref_global_vector[0] = -3.0;
  ref_global_vector[1] = 1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Off global axis local z-axis 
  local_z_axis_wrt_gcs[0] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[1] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[2] = 1.0/sqrt(3.0);

  // Local z-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, 0.0, 2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = 2.0/sqrt(3.0)-1.0;
  ref_global_vector[1] = 2.0/sqrt(3.0)+1.0;
  ref_global_vector[2] = 2.0/sqrt(3.0)+2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. z-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, 0.0, -2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = -2.0/sqrt(3.0)-1.0;
  ref_global_vector[1] = -2.0/sqrt(3.0)+1.0;
  ref_global_vector[2] = -2.0/sqrt(3.0)+2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local y-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, 2.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = -sqrt(2.0)-1.0;
  ref_global_vector[1] = sqrt(2.0)+1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local neg. y-axis
  Utility::convertLocalVectorToGlobalVector( 0.0, -2.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = sqrt(2.0)-1.0;
  ref_global_vector[1] = -sqrt(2.0)+1.0;
  ref_global_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-15 );

  // Local x-axis
  Utility::convertLocalVectorToGlobalVector( 2.0, 0.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = 2.0/sqrt(6.0)-1.0;
  ref_global_vector[1] = 2.0/sqrt(6.0)+1.0;
  ref_global_vector[2] = -sqrt(8.0/3.0)+2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-14 );

  // Local neg. x-axis
  Utility::convertLocalVectorToGlobalVector( -2.0, 0.0, 0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             global_vector[0],
                                             global_vector[1],
                                             global_vector[2] );

  ref_global_vector[0] = -2.0/sqrt(6.0)-1.0;
  ref_global_vector[1] = -2.0/sqrt(6.0)+1.0;
  ref_global_vector[2] = sqrt(8.0/3.0)+2.0;

  TEST_COMPARE_FLOATING_ARRAYS( global_vector, ref_global_vector, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that a global vector can be converted to a local vector
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   convertGlobalVectorToLocalVector_same_origin )
{
  // Global x-axis aligned local z-axis
  Teuchos::Array<double> local_z_axis_wrt_gcs( 3 );
  local_z_axis_wrt_gcs[0] = 1.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Global x-axis ==> local z-axis
  Teuchos::Array<double> global_vector( 3 );
  global_vector[0] = 2.0;
  global_vector[1] = 0.0;
  global_vector[2] = 0.0;

  Teuchos::Array<double> local_vector( 3 );

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  Teuchos::Array<double> ref_local_vector( 3 );
  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. x-axis ==> local neg. z-axis
  global_vector[0] = -2.0;
  global_vector[1] = 0.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis ==> local y-axis
  global_vector[0] = 0.0;
  global_vector[1] = 2.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. y-axis ==> local neg. y-axis
  global_vector[0] = 0.0;
  global_vector[1] = -2.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis ==> local neg. x-axis
  global_vector[0] = 0.0;
  global_vector[1] = 0.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. z-axis ==> local x-axis
  global_vector[0] = 0.0;
  global_vector[1] = 0.0;
  global_vector[2] = -2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 1.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Global x-axis ==> local neg. y-axis
  global_vector[0] = 2.0;
  global_vector[1] = 0.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. x-axis ==> local y-axis
  global_vector[0] = -2.0;
  global_vector[1] = 0.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis ==> local z-axis
  global_vector[0] = 0.0;
  global_vector[1] = 2.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );  

  // Global neg. y-axis ==> local neg. z-axis
  global_vector[0] = 0.0;
  global_vector[1] = -2.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis ==> local neg. x-axis
  global_vector[0] = 0.0;
  global_vector[1] = 0.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. z-axis ==> local x-axis
  global_vector[0] = 0.0;
  global_vector[1] = 0.0;
  global_vector[2] = -2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 1.0;

  // Global x-axis ==> local x-axis
  global_vector[0] = 2.0;
  global_vector[1] = 0.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. x-axis ==> local neg. x-axis
  global_vector[0] = -2.0;
  global_vector[1] = 0.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis ==> local y-axis
  global_vector[0] = 0.0;
  global_vector[1] = 2.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. y-axis ==> local neg. y-axis
  global_vector[0] = 0.0;
  global_vector[1] = -2.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis ==> local z-axis
  global_vector[0] = 0.0;
  global_vector[1] = 0.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. z-axis ==> local neg. z-axis
  global_vector[0] = 0.0;
  global_vector[1] = 0.0;
  global_vector[2] = -2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Off global axis local z-axis
  local_z_axis_wrt_gcs[0] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[1] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[2] = 1.0/sqrt(3.0);

  // Local x-axis
  Utility::convertGlobalVectorToLocalVector( 2.0/sqrt(6.0),
                                             2.0/sqrt(6.0),
                                             -sqrt(8.0/3.0),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local neg. x-axis
  Utility::convertGlobalVectorToLocalVector( -2.0/sqrt(6.0),
                                             -2.0/sqrt(6.0),
                                             sqrt(8.0/3.0),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local y-axis
  Utility::convertGlobalVectorToLocalVector( -sqrt(2.0),
                                             sqrt(2.0),
                                             0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local neg. y-axis
  Utility::convertGlobalVectorToLocalVector( sqrt(2.0),
                                             -sqrt(2.0),
                                             0.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );
  
  // Local z-axis
  Utility::convertGlobalVectorToLocalVector( 2.0/sqrt(3.0),
                                             2.0/sqrt(3.0),
                                             2.0/sqrt(3.0),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local neg. z-axis
  Utility::convertGlobalVectorToLocalVector( -2.0/sqrt(3.0),
                                             -2.0/sqrt(3.0),
                                             -2.0/sqrt(3.0),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a global vector can be converted to a local vector
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   convertGlobalVectorToLocalVector_diff_origin )
{
  // Global x-axis aligned local z-axis
  Teuchos::Array<double> local_z_axis_wrt_gcs( 3 );
  local_z_axis_wrt_gcs[0] = 1.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Origin of local coordinate system w.r.t. global coordinate system
  Teuchos::Array<double> local_origin_wrt_gcs( 3 );
  local_origin_wrt_gcs[0] = -1.0;
  local_origin_wrt_gcs[1] = 1.0;
  local_origin_wrt_gcs[2] = 2.0;

  // Global x-axis (after translation) ==> local z-axis
  Teuchos::Array<double> global_vector( 3 );
  global_vector[0] = 1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 2.0;

  Teuchos::Array<double> local_vector( 3 );

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  Teuchos::Array<double> ref_local_vector( 3 );
  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. x-axis (after translation) ==> local neg. z-axis
  global_vector[0] = -3.0;
  global_vector[1] = 1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis (after translation) ==> local y-axis
  global_vector[0] = -1.0;
  global_vector[1] = 3.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. y-axis (after translation) ==> local neg. y-axis
  global_vector[0] = -1.0;
  global_vector[1] = -1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis (after translation) ==> local neg. x-axis
  global_vector[0] = -1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 4.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg z-axis (after translation) ==> local x-axis
  global_vector[0] = -1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 1.0;
  local_z_axis_wrt_gcs[2] = 0.0;

  // Global x-axis (after translation) ==> local neg. y-axis
  global_vector[0] = 1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );
  
  // Global neg. x-axis (after translation) ==> local y-axis
  global_vector[0] = -3.0;
  global_vector[1] = 1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis (after translation) ==> local z-axis
  global_vector[0] = -1.0;
  global_vector[1] = 3.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. y-axis (after translation) ==> local neg. z-axis
  global_vector[0] = -1.0;
  global_vector[1] = -1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis (after translation) ==> local neg. x-axis
  global_vector[0] = -1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 4.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. z-axis (after translation) ==> local x-axis
  global_vector[0] = -1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis aligned local z-axis
  local_z_axis_wrt_gcs[0] = 0.0;
  local_z_axis_wrt_gcs[1] = 0.0;
  local_z_axis_wrt_gcs[2] = 1.0;

  // Global x-axis (after translation) ==> local x-axis
  global_vector[0] = 1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. x-axis (after translation) ==> local neg. x-axis
  global_vector[0] = -3.0;
  global_vector[1] = 1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global y-axis (after translation) ==> local y-axis
  global_vector[0] = -1.0;
  global_vector[1] = 3.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. y-axis (after translation) ==> local neg. y-axis
  global_vector[0] = -1.0;
  global_vector[1] = -1.0;
  global_vector[2] = 2.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global z-axis (after translation) ==> local z-axis
  global_vector[0] = -1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 4.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Global neg. z-axis (after translation) ==> local neg. z-axis
  global_vector[0] = -1.0;
  global_vector[1] = 1.0;
  global_vector[2] = 0.0;

  Utility::convertGlobalVectorToLocalVector( global_vector.getRawPtr(),
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector.getRawPtr() );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Off global axis local z-axis
  local_z_axis_wrt_gcs[0] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[1] = 1.0/sqrt(3.0);
  local_z_axis_wrt_gcs[2] = 1.0/sqrt(3.0);

  // Local z-axis
  Utility::convertGlobalVectorToLocalVector( 2.0/sqrt(3.0)-1.0,
                                             2.0/sqrt(3.0)+1.0,
                                             2.0/sqrt(3.0)+2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local neg. z-axis
  Utility::convertGlobalVectorToLocalVector( -2.0/sqrt(3.0)-1.0,
                                             -2.0/sqrt(3.0)+1.0,
                                             -2.0/sqrt(3.0)+2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = -2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local y-axis
  Utility::convertGlobalVectorToLocalVector( -sqrt(2.0)-1.0,
                                             sqrt(2.0)+1.0,
                                             2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = 2.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local neg. y-axis
  Utility::convertGlobalVectorToLocalVector( sqrt(2.0)-1.0,
                                             -sqrt(2.0)+1.0,
                                             2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 0.0;
  ref_local_vector[1] = -2.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local x-axis
  Utility::convertGlobalVectorToLocalVector( 2.0/sqrt(6.0)-1.0,
                                             2.0/sqrt(6.0)+1.0,
                                             -sqrt(8.0/3.0)+2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = 2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );

  // Local neg. x-axis
  Utility::convertGlobalVectorToLocalVector( -2.0/sqrt(6.0)-1.0,
                                             -2.0/sqrt(6.0)+1.0,
                                             sqrt(8.0/3.0)+2.0,
                                             local_z_axis_wrt_gcs.getRawPtr(),
                                             local_origin_wrt_gcs.getRawPtr(),
                                             local_vector[0],
                                             local_vector[1],
                                             local_vector[2] );

  ref_local_vector[0] = -2.0;
  ref_local_vector[1] = 0.0;
  ref_local_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( local_vector, ref_local_vector, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a unit vector can be rotated through a polar and azimuthal angle
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   rotateUnitVectorThroughPolarAndAzimuthalAngle )
{
  // Rotate x-axis to neg. x-axis
  Teuchos::Array<double> unit_vector( 3 );
  unit_vector[0] = 1.0;
  unit_vector[1] = 0.0;
  unit_vector[2] = 0.0;

  Teuchos::Array<double> rotated_unit_vector( 3 );

  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     -1.0,
                                             0.0,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  Teuchos::Array<double> ref_rotated_unit_vector( 3 );
  ref_rotated_unit_vector[0] = -1.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
				ref_rotated_unit_vector,
				1e-15 );

  // Rotate x-axis to y-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi/2,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );
  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 1.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate x-axis to neg. y-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    unit_vector.getRawPtr(),
					    rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = -1.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate x-axis to z-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate x-axis to neg. z-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             0.0,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = -1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate y-axis to neg. y-axis
  unit_vector[0] = 0.0;
  unit_vector[1] = 1.0;
  unit_vector[2] = 0.0;

  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     -1.0,
                                             0.0,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = -1.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate y-axis to x-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    unit_vector.getRawPtr(),
					    rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 1.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate the y-axis to neg. x-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi/2,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = -1.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate the y-axis to z-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate the y-axis to neg. z-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             0.0,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = -1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate the z-axis to neg. z-axis
  unit_vector[0] = 0.0;
  unit_vector[1] = 0.0;
  unit_vector[2] = 1.0;

  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     -1.0,
                                             0.0,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = -1.0;
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate the z-axis to x-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             0.0,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 1.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 0.0;
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );

  // Rotate the z-axis to neg. x-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi,
                                             unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = -1.0;
  ref_rotated_unit_vector[1] = 0.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );
  
  // Rotate the z-axis to y-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					     0.0,
					     Utility::PhysicalConstants::pi/2,
					     unit_vector.getRawPtr(),
					     rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = 1.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );
  // Rotate the z-axis to neg. y-axis
  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
					    0.0,
                                            3*Utility::PhysicalConstants::pi/2,
                                            unit_vector.getRawPtr(),
                                            rotated_unit_vector.getRawPtr() );

  ref_rotated_unit_vector[0] = 0.0;
  ref_rotated_unit_vector[1] = -1.0;
  ref_rotated_unit_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_unit_vector,
					ref_rotated_unit_vector,
					1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a vector can be rotated through a polar and azimuthal angle
TEUCHOS_UNIT_TEST( CartesianVectorHelpers,
                   rotateVectorThroughPolarAndAzimuthalAngle )
{
  // Rotate x-axis to neg. x-axis
  Teuchos::Array<double> vector( 3 );
  vector[0] = 2.0;
  vector[1] = 0.0;
  vector[2] = 0.0;

  Teuchos::Array<double> rotated_vector( 3 );

  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     -1.0,
                                             0.0,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  Teuchos::Array<double> ref_rotated_vector( 3 );
  ref_rotated_vector[0] = -2.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
				ref_rotated_vector,
				1e-15 );

  // Rotate x-axis to y-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi/2,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );
  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 2.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate x-axis to neg. y-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    vector.getRawPtr(),
					    rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = -2.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate x-axis to z-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate x-axis to neg. z-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             0.0,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = -2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate y-axis to neg. y-axis
  vector[0] = 0.0;
  vector[1] = 2.0;
  vector[2] = 0.0;

  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     -1.0,
                                             0.0,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = -2.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate y-axis to x-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					    0.0,
					    3*Utility::PhysicalConstants::pi/2,
					    vector.getRawPtr(),
					    rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 2.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the y-axis to neg. x-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi/2,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = -2.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the y-axis to z-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             Utility::PhysicalConstants::pi,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the y-axis to neg. z-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     0.0,
                                             0.0,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = -2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the z-axis to neg. z-axis
  vector[0] = 0.0;
  vector[1] = 0.0;
  vector[2] = 2.0;

  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					     -1.0,
                                             0.0,
                                             vector.getRawPtr(),
					     rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = -2.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the z-axis to x-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					          0.0,
                                                  0.0,
                                                  vector.getRawPtr(),
					          rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 2.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the z-axis to neg. x-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					        0.0,
					        Utility::PhysicalConstants::pi,
                                                vector.getRawPtr(),
                                                rotated_vector.getRawPtr() );
  
  ref_rotated_vector[0] = -2.0;
  ref_rotated_vector[1] = 0.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the z-axis to y-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					      0.0,
					      Utility::PhysicalConstants::pi/2,
                                              vector.getRawPtr(),
                                              rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = 2.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );

  // Rotate the z-axis to neg. y-axis
  Utility::rotateVectorThroughPolarAndAzimuthalAngle(
					    0.0,
                                            3*Utility::PhysicalConstants::pi/2,
                                            vector.getRawPtr(),
                                            rotated_vector.getRawPtr() );

  ref_rotated_vector[0] = 0.0;
  ref_rotated_vector[1] = -2.0;
  ref_rotated_vector[2] = 0.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( rotated_vector,
					ref_rotated_vector,
					1e-15 );
}

//---------------------------------------------------------------------------//
// end tst3DCartesianVectorHelpers.cpp
//---------------------------------------------------------------------------//
