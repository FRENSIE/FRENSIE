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

// FRENSIE Includes
#include "Geometry_LinearAlgebraAlgorithms.hpp"
#include "Geometry_VectorHelpers.hpp"
#include "Geometry_MatrixHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

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
  Geometry::Vector<ScalarType> vector_a( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> vector_b( 1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> cross_product =
    Geometry::LinearAlgebra::computeCrossProduct( vector_a, vector_b );

  Geometry::Vector<ScalarType> ref_cross_product( 0.0, -1.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // cross product of x-axis and y-axis
  cross_product = Geometry::LinearAlgebra::computeCrossProduct(
				     Geometry::createXAxisVector<ScalarType>(),
				     Geometry::createYAxisVector<ScalarType>() );

  ref_cross_product = Geometry::createZAxisVector<ScalarType>();

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // cross product of y-axis and z-axis
  cross_product = Geometry::LinearAlgebra::computeCrossProduct(
				     Geometry::createYAxisVector<ScalarType>(),
				     Geometry::createZAxisVector<ScalarType>() );
  ref_cross_product = Geometry::createXAxisVector<ScalarType>();

  TEST_COMPARE_FLOATING_ARRAYS( cross_product,
				ref_cross_product,
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // cross product of x-axis and z-axis
  cross_product = Geometry::LinearAlgebra::computeCrossProduct(
				     Geometry::createXAxisVector<ScalarType>(),
				     Geometry::createZAxisVector<ScalarType>() );
  ref_cross_product =
    Geometry::createYAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );

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
  Geometry::Matrix<ScalarType> matrix( 1.0, 2.0, 3.0,
				          1.0, 4.0,
				               1.0 );
  Geometry::Matrix<ScalarType> inverse_matrix =
    Geometry::LinearAlgebra::computeMatrixInverse( matrix );

  Geometry::Matrix<ScalarType> identity_matrix;
  identity_matrix.multiply( 1.0, matrix, false, inverse_matrix, false, 0.0 );

  Geometry::Matrix<ScalarType> ref_identity_matrix;
  ref_identity_matrix.identity();

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
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
  Geometry::Matrix<ScalarType> A( 5.0, 4.0, 3.0,
				2.0, 0.0, 1.0,
				8.0, 3.0, 1.0 );
  Geometry::Vector<ScalarType> b( 12.0, 3.0, 12.0 );

  Geometry::Vector<ScalarType> x = Geometry::LinearAlgebra::solveSystem( A, b );

  Geometry::Vector<ScalarType> ref_x( 1.0, 1.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( x(),
				ref_x(),
				2*Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, solveSystem );

//---------------------------------------------------------------------------//
// Check that eigenvalues of a 3x3 symmetric matrix can be computed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebra,
				   computeEigenvalues,
				   ScalarType )
{
  // Positive-definite matrix
  Geometry::Matrix<ScalarType> coefficient_matrix( 3.0,
						 0.0, 2.0,
						 0.0, 0.0, 1.0 );

  Geometry::Vector<ScalarType> eigenvalues =
    Geometry::LinearAlgebra::computeEigenvalues( coefficient_matrix );

  Geometry::Vector<ScalarType> ref_eigenvalues( 1.0, 2.0, 3.0 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues(),
				ref_eigenvalues(),
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // Negative-definite matrix
  coefficient_matrix = Geometry::createMatrix<ScalarType>( -3.0,
							  0.0, -2.0,
							  0.0, 0.0, -1.0 );
  eigenvalues = Geometry::LinearAlgebra::computeEigenvalues( coefficient_matrix);

  ref_eigenvalues = Geometry::createVector<ScalarType>( -3.0, -2.0, -1.0 );

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
  Geometry::Matrix<ScalarType> coef_matrix( 3.0,
					  0.0, 2.0,
					  0.0, 0.0, 1.0 );
  Geometry::Matrix<ScalarType> eigenvectors;

  Geometry::Vector<ScalarType> eigenvalues =
    Geometry::LinearAlgebra::computeEigenvaluesAndEigenvectors( coef_matrix,
							      eigenvectors );

  Geometry::Matrix<ScalarType> ref_eigenvectors( 0.0, 0.0, 1.0,
					       0.0, 1.0, 0.0,
					       1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_eigenvalues( 1.0, 2.0, 3.0 );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues(),
				ref_eigenvalues(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors(),
				ref_eigenvectors(),
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // Negative-definite matrix
  coef_matrix = Geometry::createMatrix<ScalarType>( -3.0,
						   0.0, -2.0,
						   0.0, 0.0, -1.0 );
  eigenvalues =
    Geometry::LinearAlgebra::computeEigenvaluesAndEigenvectors( coef_matrix,
							     eigenvectors );

  ref_eigenvectors.identity();
  ref_eigenvalues = Geometry::createVector<ScalarType>( -3.0, -2.0, -1.0 );

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
  Geometry::Vector<ScalarType> eigenvalues( 1.0, 1.0, 2.0 );
  Geometry::Matrix<ScalarType> eigenvectors;
  eigenvectors.identity();

  Geometry::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      Utility::X_AXIS );

  Geometry::Matrix<ScalarType> ref_eigenvectors;
  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // z-axis alignment to y-axis alignment
  eigenvalues = Geometry::createVector<ScalarType>( 1.0, 1.0, 2.0 );
  eigenvectors.identity();

  Geometry::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      Utility::Y_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 1, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // y-axis alignment to x-axis alignment
  eigenvalues = Geometry::createVector<ScalarType>( 1.0, 2.0, 1.0 );
  eigenvectors.identity();

  Geometry::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      Utility::X_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 1 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // y-axis alignment to z-axis alignment
  eigenvalues = Geometry::createVector<ScalarType>( 1.0, 2.0, 1.0 );
  eigenvectors.identity();

  Geometry::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      Utility::Z_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 1, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // x-axis alignment to y-axis alignment
  eigenvalues = Geometry::createVector<ScalarType>( 2.0, 1.0, 1.0 );
  eigenvectors.identity();

  Geometry::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      Utility::Y_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 1 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );

  // x-axis alignment to z-axis alignment
  eigenvalues = Geometry::createVector<ScalarType>( 2.0, 1.0, 1.0 );
  eigenvectors.identity();

  Geometry::LinearAlgebra::realignEigenvectors( eigenvalues,
					      eigenvectors,
					      Utility::Z_AXIS );

  ref_eigenvectors.identity();
  ref_eigenvectors.swapColumns( 0, 2 );

  TEST_EQUALITY( eigenvectors, ref_eigenvectors );
}

UNIT_TEST_INSTANTIATION( LinearAlgebra, realignEigenvectors );

//---------------------------------------------------------------------------//
// end tstLinearAlgebraAlgorithms.cpp
//---------------------------------------------------------------------------//

