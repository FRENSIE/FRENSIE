//---------------------------------------------------------------------------//
//!
//! \file   tstLinearAlgebraPolicy.cpp
//! \author Alex Robinson
//! \brief  Linear Algebra policy unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "LinearAlgebraPolicy.hpp"
#include "ThreeSpaceTraitsAndPolicy.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a vector can be normalized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy, 
				   normalizeVector,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  
  typename ThreeSpace::Vector vector = 
    ThreeSpace::createVector( 1.0, 1.0, 1.0 );
  
  FACEMC::LinearAlgebraPolicy<ScalarType>::normalizeVector( vector );
  
  Teuchos::ArrayView<ScalarType> vector_view( vector.values(), 3 );

  ScalarType divisor = ST::squareroot( 3.0 );

  Teuchos::Tuple<ScalarType,3> ref_norm_vector = 
    Teuchos::tuple( ST::one()/divisor, ST::one()/divisor, ST::one()/divisor );

  TEST_COMPARE_ARRAYS( vector_view, ref_norm_vector );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, normalizeVector );

//---------------------------------------------------------------------------//
// Check that the correct rotation matrix can be calculated from two unit
// vectors
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy, 
				   createRotationMatrixFromUnitVectors,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;

  // x-axis to z-axis rotation
  typename ThreeSpace::Vector initial_direction = 
    ThreeSpace::createVector( 1.0, 0.0, 0.0 );
  typename ThreeSpace::Vector final_direction = 
    ThreeSpace::createVector( 0.0, 0.0, 1.0 );

  typename ThreeSpace::Matrix ref_rotation_matrix = 
    ThreeSpace::createSquareMatrix( 0.0, 0.0, -1.0,
				    0.0, 1.0,  0.0,
				    1.0, 0.0,  0.0 );

  // This view will allow the reference rotation_matrix to be tested. Every
  // time the reference object is changed the view will see the change.
  Teuchos::ArrayView<ScalarType> ref_rotation_matrix_view( 
						  ref_rotation_matrix.values(),
						  9 );

  typename ThreeSpace::Matrix rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
					      final_direction );
    
  // This view will allow the calculated rotation_matrix to be tested. Every
  // time the rotation_matrix object is changed the view will see the change.
  Teuchos::ArrayView<ScalarType> rotation_matrix_view( rotation_matrix.values(),
						   9 );
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // x-axis to neg-z-axis rotation
  final_direction = ThreeSpace::createVector( 0.0, 0.0, -1.0 );
  
  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 0.0, -1.0,
							0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // x-axis to y-axis rotation
  final_direction = ThreeSpace::createVector( 0.0, 1.0, 0.0 );

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, -1.0, 0.0,
							1.0,  0.0, 0.0,
							0.0,  0.0, 1.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // x-axis to neg-y-axis rotation
  final_direction = ThreeSpace::createVector( 0.0, -1.0, 0.0 );

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0,
							0.0, 0.0, 1.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // z-axis to x-axis rotation
  initial_direction = ThreeSpace::createVector( 0.0, 0.0, 1.0 );
  final_direction = ThreeSpace::createVector( 1.0, 0.0, 0.0 );

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 0.0, 1.0,
							0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // neg-z-axis to x-axis rotation
  initial_direction = ThreeSpace::createVector( 0.0, 0.0, -1.0 );
  final_direction = ThreeSpace::createVector( 1.0, 0.0, 0.0 );

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 0.0, -1.0,
							0.0, 1.0,  0.0,
							-1.0, 0.0,  0.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // y-axis to x-axis rotation
  initial_direction = ThreeSpace::createVector( 0.0, 1.0, 0.0 );
  final_direction = ThreeSpace::createVector( 1.0, 0.0, 0.0 );

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0,
							0.0, 0.0, 1.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, createRotationMatrixFromUnitVectors);

//---------------------------------------------------------------------------//
// Check that the inverse of a matrix can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy, 
				   computeMatrixInverse,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  
  typename ThreeSpace::Matrix matrix = 
    ThreeSpace::createSquareMatrix( 1.0, 2.0, 3.0,
				    2.0, 1.0, 4.0,
				    3.0, 4.0, 1.0 );

  typename ThreeSpace::Matrix 
    inverse_matrix = LAP::computeMatrixInverse( matrix );
  
  typename ThreeSpace::Matrix inverse_inverse_matrix = 
    LAP::computeMatrixInverse( inverse_matrix );
  
  Teuchos::ArrayView<ScalarType> matrix_view( matrix.values(), 9 );
  Teuchos::ArrayView<ScalarType> inverse_inverse_matrix_view( 
					      inverse_inverse_matrix.values(), 
					      9 );

  TEST_COMPARE_FLOATING_ARRAYS( matrix_view, 
				inverse_inverse_matrix_view, 
				ST::eps()*10 );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, computeMatrixInverse );

//---------------------------------------------------------------------------//
// Check that the eigenvalues of a symmetric matrix can be found.
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy, 
				   computeEigenvalues,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  
  // Positive-definite matrix
  typename ThreeSpace::Matrix coefficient_matrix = 
    ThreeSpace::createSymmetricMatrix( 3.0, 0.0, 0.0,
				            2.0, 0.0,
				                 1.0 );

  typename ThreeSpace::Vector ref_eigenvalues = 
    ThreeSpace::createVector( 1.0, 2.0, 3.0 );
  
  typename ThreeSpace::Vector eigenvalues = 
    LAP::computeEigenvalues( coefficient_matrix );

  Teuchos::ArrayView<ScalarType> ref_eigenvalues_view( ref_eigenvalues.values(), 3 );
  Teuchos::ArrayView<ScalarType> eigenvalues_view( eigenvalues.values(), 3 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				ST::eps() );

  // Negative-definite matrix
  coefficient_matrix = ThreeSpace::createSymmetricMatrix( -3.0, 0.0, 0.0,
							       -2.0, 0.0,
							            -1.0 ); 

  ref_eigenvalues = ThreeSpace::createVector( -3.0, -2.0, -1.0 );
  
  eigenvalues = LAP::computeEigenvalues( coefficient_matrix );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				ST::eps() );  
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, computeEigenvalues );

//---------------------------------------------------------------------------//
// Check that the eigenvalues and eigenvectors of a symmetric matrix can be 
// found.
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy, 
				   computeEigenvaluesAndEigenvectors,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  
  // Positive-definite matrix
  typename ThreeSpace::Matrix coefficient_matrix = 
    ThreeSpace::createSymmetricMatrix( 3.0, 0.0, 0.0,
				            2.0, 0.0,
				                 1.0 );

  typename ThreeSpace::Matrix eigenvectors;
  
  typename ThreeSpace::Vector eigenvalues = 
    LAP::computeEigenvaluesAndEigenvectors( coefficient_matrix,
					    eigenvectors );

  typename ThreeSpace::Vector ref_eigenvalues = 
    ThreeSpace::createVector( 1.0, 2.0, 3.0 );

  typename ThreeSpace::Matrix ref_eigenvectors = 
    ThreeSpace::createSquareMatrix( 0.0, 0.0, 1.0,
				    0.0, 1.0, 0.0,
				    1.0, 0.0, 0.0 );

  Teuchos::ArrayView<ScalarType> ref_eigenvalues_view( ref_eigenvalues.values(), 3 );
  Teuchos::ArrayView<ScalarType> ref_eigenvectors_view( ref_eigenvectors.values(), 9 );
  Teuchos::ArrayView<ScalarType> eigenvalues_view( eigenvalues.values(), 3 );
  Teuchos::ArrayView<ScalarType> eigenvectors_view( eigenvectors.values(), 9 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				ST::eps() );
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors_view,
				ref_eigenvectors_view,
				ST::eps() );

  // Negative-definite matrix
  coefficient_matrix = ThreeSpace::createSymmetricMatrix( -3.0, 0.0, 0.0,
							       -2.0, 0.0,
							            -1.0 ); 

  eigenvalues = LAP::computeEigenvaluesAndEigenvectors( coefficient_matrix,
							eigenvectors );

  ref_eigenvalues = ThreeSpace::createVector( -3.0, -2.0, -1.0 );
  
  ref_eigenvectors = ThreeSpace::createSquareMatrix( 1.0, 0.0, 0.0,
						     0.0, 1.0, 0.0,
						     0.0, 0.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				ST::eps() );  
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors_view,
				ref_eigenvectors_view,
				ST::eps() );
}

//---------------------------------------------------------------------------//
// end tstLinearAlgebraPolicy.cpp
//---------------------------------------------------------------------------//

