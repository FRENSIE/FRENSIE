//---------------------------------------------------------------------------//
//!
//! \file   tstLinearAlgebraAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Linear algebra algorithm unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "LinearAlgebraAlgorithms.hpp"
#include "VectorHelpers.hpp"
#include "MatrixHelpers.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cross product of two vectors can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra,
				   computeCrossProduct,
				   ScalarType )
{
  // cross product of general vectors
  FACEMC::Vector<ScalarType> vector_a( 1.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> vector_b( 1.0, 1.0, 1.0 );

  FACEMC::Vector<ScalarType> cross_product = 
    FACEMC::LinearAlgebra::computeCrossProduct( vector_a, vector_b );

  FACEMC::Vector<ScalarType> ref_cross_product( 0.0, -1.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // cross product of x-axis and y-axis
  cross_product = FACEMC::LinearAlgebra::computeCrossProduct( 
				     FACEMC::createXAxisVector<ScalarType>(),
				     FACEMC::createYAxisVector<ScalarType>() );

  ref_cross_product = FACEMC::createZAxisVector<ScalarType>();

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // cross product of y-axis and z-axis
  cross_product = FACEMC::LinearAlgebra::computeCrossProduct( 
				     FACEMC::createYAxisVector<ScalarType>(),
				     FACEMC::createZAxisVector<ScalarType>() );
  ref_cross_product = FACEMC::createXAxisVector<ScalarType>();

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // cross product of x-axis and z-axis
  cross_product = FACEMC::LinearAlgebra::computeCrossProduct( 
				     FACEMC::createXAxisVector<ScalarType>(),
				     FACEMC::createZAxisVector<ScalarType>() );
  ref_cross_product = 
    FACEMC::createYAxisVector<ScalarType>( FACEMC::NEGATIVE_DIRECTION );

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, computeCrossProduct );

//---------------------------------------------------------------------------//
// Check that the inverse of a matrix can be computed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra, 
				   computeMatrixInverse,
				   ScalarType )
{
  FACEMC::Matrix<ScalarType> matrix( 1.0, 2.0, 3.0,
				          1.0, 4.0,
				               1.0 );
  FACEMC::Matrix<ScalarType> inverse_matrix =
    FACEMC::LinearAlgebra::computeMatrixInverse( matrix );

  FACEMC::Matrix<ScalarType> identity_matrix;
  identity_matrix.multiply( 1.0, matrix, false, inverse_matrix, false, 0.0 );

  FACEMC::Matrix<ScalarType> ref_identity_matrix;
  ref_identity_matrix.identity();

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( 
				   identity_matrix(),
				   ref_identity_matrix(),
				   Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, computeMatrixInverse );

//---------------------------------------------------------------------------//
// Check that a 3x3 system of equations can be solved
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra, 
				   solveSystem,
				   ScalarType )
{
  FACEMC::Matrix<ScalarType> A( 5.0, 4.0, 3.0,
				2.0, 0.0, 1.0,
				8.0, 3.0, 1.0 );
  FACEMC::Vector<ScalarType> b( 12.0, 3.0, 12.0 );

  FACEMC::Vector<ScalarType> x = FACEMC::LinearAlgebra::solveSystem( A, b );

  FACEMC::Vector<ScalarType> ref_x( 1.0, 1.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( x(), 
				ref_x(), 
				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, solveSystem );

//---------------------------------------------------------------------------//
// Check that eigenvalues of a 3x3 symmetric matrix can be computed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra,
				   computeEigenvalues,
				   ScalarType )
{
  // Positive-definite matrix
  FACEMC::Matrix<ScalarType> coefficient_matrix( 3.0, 
						 0.0, 2.0,
						 0.0, 0.0, 1.0 );

  FACEMC::Vector<ScalarType> eigenvalues = 
    FACEMC::LinearAlgebra::computeEigenvalues( coefficient_matrix );

  FACEMC::Vector<ScalarType> ref_eigenvalues( 1.0, 2.0, 3.0 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues(),
				ref_eigenvalues(),
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // Negative-definite matrix
  coefficient_matrix = FACEMC::createMatrix<ScalarType>( -3.0, 
							  0.0, -2.0, 
							  0.0, 0.0, -1.0 );
  eigenvalues = FACEMC::LinearAlgebra::computeEigenvalues( coefficient_matrix);
  
  ref_eigenvalues = FACEMC::createVector<ScalarType>( -3.0, -2.0, -1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues(),
				ref_eigenvalues(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, computeEigenvalues );

//---------------------------------------------------------------------------//
// Check that the eigenvectors of a 3x3 symmetric matrix can be computed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra, 
				   computeEigenvaluesAndEigenvectors,
				   ScalarType )
{
  // Positive-definite matrix
  FACEMC::Matrix<ScalarType> coef_matrix( 3.0, 
					  0.0, 2.0,
					  0.0, 0.0, 1.0 );
  FACEMC::Matrix<ScalarType> eigenvectors;

  FACEMC::Vector<ScalarType> eigenvalues = 
    FACEMC::LinearAlgebra::computeEigenvaluesAndEigenvectors( coef_matrix,
							      eigenvectors );

  FACEMC::Matrix<ScalarType> ref_eigenvectors( 0.0, 0.0, 1.0,
					       0.0, 1.0, 0.0,
					       1.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> ref_eigenvalues( 1.0, 2.0, 3.0 );
  
  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues(),
				ref_eigenvalues(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors(),
				ref_eigenvectors(),
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // Negative-definite matrix
  coef_matrix = FACEMC::createMatrix<ScalarType>( -3.0, 
						   0.0, -2.0,
						   0.0, 0.0, -1.0 );
  eigenvalues = 
    FACEMC::LinearAlgebra::computeEigenvaluesAndEigenvectors( coef_matrix,
							     eigenvectors );

  ref_eigenvectors.identity();
  ref_eigenvalues = FACEMC::createVector<ScalarType>( -3.0, -2.0, -1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues(),
				ref_eigenvalues(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors(),
				ref_eigenvectors(),
				Teuchos::ScalarTraits<ScalarType>::prec() );  
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, computeEigenvaluesAndEigenvectors );

//---------------------------------------------------------------------------//
// Check that eigenvectors can be aligned with the desired axis
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra, 
				   realignEigenvectors,
				   ScalarType )
{
  // z-axis alignment to x-axis alignment
  FACEMC::Vector<ScalarType> eigenvalues( 1.0, 1.0, 2.0 );
  FACEMC::Matrix<ScalarType> eigenvectors;
  eigenvectors.identity();

  FACEMC::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      FACEMC::X_AXIS );

  FACEMC::Matrix<ScalarType> ref_eigenvectors;
  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // z-axis alignment to y-axis alignment
  eigenvalues = FACEMC::createVector<ScalarType>( 1.0, 1.0, 2.0 );
  eigenvectors.identity();
  
  FACEMC::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      FACEMC::Y_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 1, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // y-axis alignment to x-axis alignment
  eigenvalues = FACEMC::createVector<ScalarType>( 1.0, 2.0, 1.0 );
  eigenvectors.identity();

  FACEMC::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      FACEMC::X_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 1 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // y-axis alignment to z-axis alignment
  eigenvalues = FACEMC::createVector<ScalarType>( 1.0, 2.0, 1.0 );
  eigenvectors.identity();

  FACEMC::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      FACEMC::Z_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 1, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // x-axis alignment to y-axis alignment
  eigenvalues = FACEMC::createVector<ScalarType>( 2.0, 1.0, 1.0 );
  eigenvectors.identity();

  FACEMC::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      FACEMC::Y_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 1 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );
  
  // x-axis alignment to z-axis alignment
  eigenvalues = FACEMC::createVector<ScalarType>( 2.0, 1.0, 1.0 );
  eigenvectors.identity();

  FACEMC::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      FACEMC::Z_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, realignEigenvectors );

//---------------------------------------------------------------------------//
// end tstLinearAlgebraAlgorithms.cpp
//---------------------------------------------------------------------------//

