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
// Testing Info.
//---------------------------------------------------------------------------//
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a vector can be normalized
TEUCHOS_UNIT_TEST( LinearAlgebraPolicy, normalizeVector )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<double> ThreeSpace;
  ThreeSpace::Vector vector = ThreeSpace::createVector( 1.0, 1.0, 1.0 );
  FACEMC::LinearAlgebraPolicy<double>::normalizeVector( vector );
  Teuchos::ArrayView<double> vector_view( vector.values(), 3 );

  double divisor = Teuchos::ScalarTraits<double>::squareroot( 3.0 );

  Teuchos::Tuple<double,3> ref_norm_vector = 
    Teuchos::tuple( 1.0/divisor, 1.0/divisor, 1.0/divisor );

  TEST_COMPARE_ARRAYS( vector_view, ref_norm_vector );
}

//---------------------------------------------------------------------------//
// Check that the correct rotation matrix can be calculated from two unit
// vectors
TEUCHOS_UNIT_TEST( LinearAlgebraPolicy, createRotationMatrixFromUnitVectors )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<double> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<double> LAP;

  // x-axis to z-axis rotation
  ThreeSpace::Vector initial_direction = ThreeSpace::createVector( 1.0, 
								   0.0, 
								   0.0 );
  ThreeSpace::Vector final_direction = ThreeSpace::createVector( 0.0, 
								 0.0, 
								 1.0 );

  ThreeSpace::Matrix ref_rotation_matrix = 
    ThreeSpace::createSquareMatrix( 0.0, 0.0, -1.0,
				    0.0, 1.0,  0.0,
				    1.0, 0.0,  0.0 );

  // This view will allow the reference rotation_matrix to be tested. Every
  // time the reference object is changed the view will see the change.
  Teuchos::ArrayView<double> ref_rotation_matrix_view( 
						  ref_rotation_matrix.values(),
						  9 );

  ThreeSpace::Matrix rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
					      final_direction );
    
  // This view will allow the calculated rotation_matrix to be tested. Every
  // time the rotation_matrix object is changed the view will see the change.
  Teuchos::ArrayView<double> rotation_matrix_view( rotation_matrix.values(),
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

//---------------------------------------------------------------------------//
// Check that the inverse of a matrix can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebraPolicy, computeMatrixInverse )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<double> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<double> LAP;
  
  ThreeSpace::Matrix matrix = ThreeSpace::createSquareMatrix( 1.0, 2.0, 3.0,
							      2.0, 1.0, 4.0,
							      3.0, 4.0, 1.0 );

  ThreeSpace::Matrix inverse_matrix = LAP::computeMatrixInverse( matrix );
  
  ThreeSpace::Matrix inverse_inverse_matrix = 
    LAP::computeMatrixInverse( inverse_matrix );
  
  Teuchos::ArrayView<double> matrix_view( matrix.values(), 9 );
  Teuchos::ArrayView<double> inverse_inverse_matrix_view( inverse_inverse_matrix.values(), 9 );

  TEST_COMPARE_FLOATING_ARRAYS( matrix_view, 
				inverse_inverse_matrix_view, 
				TOL );
}

//---------------------------------------------------------------------------//
// Check that the eigenvalues of a symmetric matrix can be found.
TEUCHOS_UNIT_TEST( LinearAlgebraPolicy, computeEigenvalues )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<double> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<double> LAP;
  
  // Positive-definite matrix
  ThreeSpace::Matrix coefficient_matrix = 
    ThreeSpace::createSymmetricMatrix( 3.0, 0.0, 0.0,
				            2.0, 0.0,
				                 1.0 );

  ThreeSpace::Vector ref_eigenvalues = 
    ThreeSpace::createVector( 1.0, 2.0, 3.0 );
  
  ThreeSpace::Vector eigenvalues = 
    LAP::computeEigenvalues( coefficient_matrix );

  Teuchos::ArrayView<double> ref_eigenvalues_view( ref_eigenvalues.values(), 3 );
  Teuchos::ArrayView<double> eigenvalues_view( eigenvalues.values(), 3 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				TOL );

  // Negative-definite matrix
  coefficient_matrix = ThreeSpace::createSymmetricMatrix( -3.0, 0.0, 0.0,
							       -2.0, 0.0,
							            -1.0 ); 

  ref_eigenvalues = ThreeSpace::createVector( -3.0, -2.0, -1.0 );
  
  eigenvalues = LAP::computeEigenvalues( coefficient_matrix );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				TOL );  
}

//---------------------------------------------------------------------------//
// Check that the eigenvalues and eigenvectors of a symmetric matrix can be 
// found.
TEUCHOS_UNIT_TEST( LinearAlgebraPolicy, computeEigenvaluesAndEigenvectors )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<double> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<double> LAP;
  
  // Positive-definite matrix
  ThreeSpace::Matrix coefficient_matrix = 
    ThreeSpace::createSymmetricMatrix( 3.0, 0.0, 0.0,
				            2.0, 0.0,
				                 1.0 );

  ThreeSpace::Matrix eigenvectors;
  
  ThreeSpace::Vector eigenvalues = 
    LAP::computeEigenvaluesAndEigenvectors( coefficient_matrix,
					    eigenvectors );

  ThreeSpace::Vector ref_eigenvalues = 
    ThreeSpace::createVector( 1.0, 2.0, 3.0 );

  ThreeSpace::Matrix ref_eigenvectors = 
    ThreeSpace::createSquareMatrix( 0.0, 0.0, 1.0,
				    0.0, 1.0, 0.0,
				    1.0, 0.0, 0.0 );

  Teuchos::ArrayView<double> ref_eigenvalues_view( ref_eigenvalues.values(), 3 );
  Teuchos::ArrayView<double> ref_eigenvectors_view( ref_eigenvectors.values(), 9 );
  Teuchos::ArrayView<double> eigenvalues_view( eigenvalues.values(), 3 );
  Teuchos::ArrayView<double> eigenvectors_view( eigenvectors.values(), 9 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				TOL );
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors_view,
				ref_eigenvectors_view,
				TOL );

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
				TOL );  
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors_view,
				ref_eigenvectors_view,
				TOL );
}

//---------------------------------------------------------------------------//
// end tstLinearAlgebraPolicy.cpp
//---------------------------------------------------------------------------//

