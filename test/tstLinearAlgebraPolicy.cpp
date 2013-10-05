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
// Check that the angle between two vectors can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   computeCosineAngleBetweenVectors,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  typename ThreeSpace::Vector vector_a = 
    ThreeSpace::createVector( 10.0, 9.0, 8.0 );

  typename ThreeSpace::Vector vector_b = 
    ThreeSpace::createVector( 7.0, 6.0, 5.0 );

  ScalarType cos_angle = LAP::computeCosineAngleBetweenVectors( vector_a,
								vector_b );

  ScalarType ref_cos_angle = 82.0/385.0*ST::squareroot( 22.0 );

  TEST_FLOATING_EQUALITY( cos_angle, ref_cos_angle, ST::prec() );
  
  cos_angle = LAP::computeCosineAngleBetweenVectors(ThreeSpace::xaxisVector(),
						    ThreeSpace::yaxisVector());

  TEST_FLOATING_EQUALITY( cos_angle, ST::zero(), ST::prec() );

  cos_angle = LAP::computeCosineAngleBetweenVectors(ThreeSpace::xaxisVector(),
						    ThreeSpace::zaxisVector());

  TEST_FLOATING_EQUALITY( cos_angle, ST::zero(), ST::prec() );

  cos_angle = LAP::computeCosineAngleBetweenVectors(ThreeSpace::yaxisVector(),
						    ThreeSpace::zaxisVector());

  TEST_FLOATING_EQUALITY( cos_angle, ST::zero(), ST::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, 
			 computeCosineAngleBetweenVectors );

//---------------------------------------------------------------------------//
// Check that the cross product of two vectors can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   computeCrossProduct,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  typename ThreeSpace::Vector vector_a = 
    ThreeSpace::createVector( ST::one(), ST::zero(), ST::zero() );
  
  typename ThreeSpace::Vector vector_b = 
    ThreeSpace::createVector( ST::one(), ST::one(), ST::one() );

  typename ThreeSpace::Vector cross_product =
    LAP::computeCrossProduct( vector_a, vector_b );

  typename ThreeSpace::Vector ref_cross_product = 
    ThreeSpace::createVector( ST::zero(), -ST::one(), ST::one() );
  
  Teuchos::ArrayView<ScalarType> cross_product_view( cross_product.values(), 
						     3 );
  Teuchos::ArrayView<ScalarType> ref_cross_product_view( 
						    ref_cross_product.values(),
						    3);
  
  TEST_COMPARE_FLOATING_ARRAYS( cross_product_view,
				ref_cross_product_view,
				ST::prec() );

  cross_product = LAP::computeCrossProduct( ThreeSpace::xaxisVector(),
					    ThreeSpace::yaxisVector() );
  ref_cross_product = ThreeSpace::zaxisVector();

  TEST_COMPARE_FLOATING_ARRAYS( cross_product_view,
				ref_cross_product_view,
				ST::prec() );

  cross_product = LAP::computeCrossProduct( ThreeSpace::yaxisVector(),
					    ThreeSpace::zaxisVector() );
  ref_cross_product = ThreeSpace::xaxisVector();

  TEST_COMPARE_FLOATING_ARRAYS( cross_product_view,
				ref_cross_product_view,
				ST::prec() );

  cross_product = LAP::computeCrossProduct( ThreeSpace::xaxisVector(),
					    ThreeSpace::zaxisVector() );
  ref_cross_product = ThreeSpace::yaxisVector( FACEMC::NEGATIVE_DIRECTION );

  TEST_COMPARE_FLOATING_ARRAYS( cross_product_view,
				ref_cross_product_view,
				ST::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, computeCrossProduct );

//---------------------------------------------------------------------------//
// Check that two vectors can be tested as parallel or antiparallel
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   isParallel_isAntiparallel,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  typename ThreeSpace::Vector vector_a = 
    ThreeSpace::createVector( 3.0, 2.0, 1.0 );

  typename ThreeSpace::Vector vector_b = 
    ThreeSpace::createVector( 6.0, 4.0, 2.0 );

  typename ThreeSpace::Vector vector_c = 
    ThreeSpace::createVector( -6.0, -4.0, -2.0 );

  TEST_ASSERT( LAP::isParallel( vector_a, vector_b ) );
  TEST_ASSERT( !LAP::isAntiparallel( vector_a, vector_b ) );
  TEST_ASSERT( !LAP::isParallel( vector_a, vector_c ) );
  TEST_ASSERT( LAP::isAntiparallel( vector_a, vector_c ) );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, isParallel_isAntiparallel );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as symmetric 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   isSymmetric,
				   ScalarType )
{ 
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;

  typename ThreeSpace::Matrix symmetric_matrix_1 = 
    ThreeSpace::createSymmetricMatrix( 1.0, 2.0, 3.0,
				            4.0, 5.0, 
				                 6.0 );
  typename ThreeSpace::Matrix symmetric_matrix_2 = 
    ThreeSpace::identityMatrix();

  typename ThreeSpace::Matrix nonsymmetric_matrix = 
    ThreeSpace::createSquareMatrix( 1.0, 2.0, 3.0,
				    4.0, 5.0, 6.0,
				    7.0, 8.0, 9.0 );

  TEST_ASSERT( LAP::isSymmetric( symmetric_matrix_1 ) );
  TEST_ASSERT( LAP::isSymmetric( symmetric_matrix_2 ) );
  TEST_ASSERT( !LAP::isSymmetric( nonsymmetric_matrix ) );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, isSymmetric );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as orthonormal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   isOrthonormal,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  
  typename ThreeSpace::Matrix orthonormal_matrix_1 = 
    ThreeSpace::identityMatrix();

  ScalarType a = ST::one()/2;
  ScalarType b = ST::one()/ST::squareroot( ST::one()*2 );

  typename ThreeSpace::Matrix orthonormal_matrix_2 = 
    ThreeSpace::createSquareMatrix( a, -b,          a,
				    a,  b,          a,
				   -b,  ST::zero(), b ); 

  typename ThreeSpace::Matrix nonorthogonal_matrix = 
    ThreeSpace::createSquareMatrix( a, a, a,
				    b, b, b,
				    a, a, a );

  typename ThreeSpace::Matrix nonnormal_matrix = orthonormal_matrix_2;
  nonnormal_matrix.scale( ST::one()*2 );

  typename ThreeSpace::Matrix nonorthonormal_matrix = 
    ThreeSpace::createSquareMatrix( a, a, a,
				    a, a, a,
				    a, a, a );

  TEST_ASSERT( LAP::isOrthonormal( orthonormal_matrix_1 ) );
  TEST_ASSERT( LAP::isOrthonormal( orthonormal_matrix_2 ) );
  TEST_ASSERT( !LAP::isOrthonormal( nonorthogonal_matrix ) );
  TEST_ASSERT( !LAP::isOrthonormal( nonnormal_matrix ) );
  TEST_ASSERT( !LAP::isOrthonormal( nonorthonormal_matrix ) );
}
    
UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, isOrthonormal );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as orthonormal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   isNonsingular,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  typename ThreeSpace::Matrix nonsingular_matrix = 
    ThreeSpace::identityMatrix();
  
  typename ThreeSpace::Matrix singular_matrix = 
    ThreeSpace::createSymmetricMatrix( 1.0, 0.0, 0.0,
				            1.0, 0.0,
				                 0.0 );

  TEST_ASSERT( LAP::isNonsingular( nonsingular_matrix ) );
  TEST_ASSERT( !LAP::isNonsingular( singular_matrix ) );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, isNonsingular );

//---------------------------------------------------------------------------//
// Check that the columns of a matrix can be swapped.
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   swapColumns,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  typename ThreeSpace::Matrix matrix = 
    ThreeSpace::identityMatrix();

  LAP::swapColumns( matrix, 0, 1 );
  LAP::swapColumns( matrix, 1, 2 );
  
  typename ThreeSpace::Matrix ref_matrix = 
    ThreeSpace::createSquareMatrix( 0.0, 0.0, 1.0,
				    1.0, 0.0, 0.0,
				    0.0, 1.0, 0.0 );

  Teuchos::ArrayView<ScalarType> matrix_view( matrix.values(), 9 );
  Teuchos::ArrayView<ScalarType> ref_matrix_view( ref_matrix.values(), 9 );

  TEST_COMPARE_ARRAYS( matrix_view, ref_matrix_view );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, swapColumns );

//---------------------------------------------------------------------------//
// Check that a zeroing vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   createZeroingVector,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  typename ThreeSpace::Vector vector = 
    ThreeSpace::createVector( 3.0, 2.0, 1.0 );

  ScalarType constant_term = 4.0;

  typename ThreeSpace::Vector zeroing_vector = 
    LAP::createZeroingVector( vector, constant_term );

  typename ThreeSpace::Vector ref_zeroing_vector = 
    ThreeSpace::createVector( -ST::one()*4/3, ST::zero(), ST::zero() );
  
  Teuchos::ArrayView<ScalarType> zeroing_vector_view( zeroing_vector.values(),
						      3 );
  Teuchos::ArrayView<ScalarType> ref_zeroing_vector_view(
						   ref_zeroing_vector.values(),
						   3 );
    
  TEST_COMPARE_FLOATING_ARRAYS( zeroing_vector_view,
				ref_zeroing_vector_view,
				ST::prec() );

  vector = ThreeSpace::createVector( 0.0, 2.0, 1.0 );
  zeroing_vector = LAP::createZeroingVector( vector, constant_term );
  ref_zeroing_vector = ThreeSpace::createVector( 0.0, -2.0, 0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( zeroing_vector_view,
				ref_zeroing_vector_view,
				ST::prec() );

  vector = ThreeSpace::createVector( 0.0, 0.0, 1.0 );
  zeroing_vector = LAP::createZeroingVector( vector, constant_term );
  ref_zeroing_vector = ThreeSpace::createVector( 0.0, 0.0, -4.0 );

  TEST_COMPARE_FLOATING_ARRAYS( zeroing_vector_view,
				ref_zeroing_vector_view,
				ST::prec() );    
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, createZeroingVector );

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
    ThreeSpace::xaxisVector();
  typename ThreeSpace::Vector final_direction = 
    ThreeSpace::zaxisVector();

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
  final_direction = ThreeSpace::zaxisVector( FACEMC::NEGATIVE_DIRECTION );
  
  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 0.0, -1.0,
							0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // x-axis to y-axis rotation
  final_direction = ThreeSpace::yaxisVector();

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, -1.0, 0.0,
							1.0,  0.0, 0.0,
							0.0,  0.0, 1.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // x-axis to neg-y-axis rotation
  final_direction = ThreeSpace::yaxisVector( FACEMC::NEGATIVE_DIRECTION );

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0,
							0.0, 0.0, 1.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // z-axis to x-axis rotation
  initial_direction = ThreeSpace::zaxisVector();
  final_direction = ThreeSpace::xaxisVector();

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 0.0, 1.0,
							0.0, 1.0, 0.0,
							-1.0, 0.0, 0.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // neg-z-axis to x-axis rotation
  initial_direction = ThreeSpace::zaxisVector( FACEMC::NEGATIVE_DIRECTION );
  final_direction = ThreeSpace::xaxisVector();

  ref_rotation_matrix = ThreeSpace::createSquareMatrix( 0.0, 0.0, -1.0,
							0.0, 1.0,  0.0,
							-1.0, 0.0,  0.0 );
  rotation_matrix = 
    LAP::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );
  
  TEST_COMPARE_ARRAYS( rotation_matrix_view, ref_rotation_matrix_view );

  // y-axis to x-axis rotation
  initial_direction = ThreeSpace::yaxisVector();
  final_direction = ThreeSpace::xaxisVector();

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
    ThreeSpace::createSymmetricMatrix( 1.0, 2.0, 3.0,
				            1.0, 4.0,
				                 1.0 );

  typename ThreeSpace::Matrix 
    inverse_matrix = LAP::computeMatrixInverse( matrix );
  
  typename ThreeSpace::Matrix identity_matrix( 3, 3 );
  identity_matrix.multiply( Teuchos::NO_TRANS,
			    Teuchos::NO_TRANS,
			    1.0,
			    matrix,
			    inverse_matrix,
			    0.0 );

  typename ThreeSpace::Matrix ref_identity_matrix = 
    ThreeSpace::identityMatrix();
  
  Teuchos::ArrayView<ScalarType> identity_matrix_view( 
						      identity_matrix.values(),
						      9 );
  Teuchos::ArrayView<ScalarType> ref_identity_matrix_view( 
						  ref_identity_matrix.values(),
						  9 );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( identity_matrix_view, 
				       ref_identity_matrix_view, 
				       ST::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, computeMatrixInverse );

//---------------------------------------------------------------------------//
// Check that a system can be solved.
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   solveSystem,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  
  typename ThreeSpace::Matrix A =
    ThreeSpace::createSquareMatrix( 5.0, 4.0, 3.0,
				    2.0, 0.0, 1.0,
				    8.0, 3.0, 1.0 );
  typename ThreeSpace::Vector b = 
    ThreeSpace::createVector( 12.0, 3.0, 12.0 );

  typename ThreeSpace::Vector x = LAP::solveSystem( A, b );

  typename ThreeSpace::Vector ref_x = 
    ThreeSpace::createVector( 1.0, 1.0, 1.0 );

  Teuchos::ArrayView<ScalarType> x_view( x.values(), 3 );
  Teuchos::ArrayView<ScalarType> ref_x_view( ref_x.values(), 3 );

  TEST_COMPARE_FLOATING_ARRAYS( x_view,
				ref_x_view,
				ST::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, solveSystem );

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
				ST::prec() );

  // Negative-definite matrix
  coefficient_matrix = ThreeSpace::createSymmetricMatrix( -3.0, 0.0, 0.0,
							       -2.0, 0.0,
							            -1.0 ); 

  ref_eigenvalues = ThreeSpace::createVector( -3.0, -2.0, -1.0 );
  
  eigenvalues = LAP::computeEigenvalues( coefficient_matrix );

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				ST::prec() );  
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
				ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors_view,
				ref_eigenvectors_view,
				ST::prec() );

  // Negative-definite matrix
  coefficient_matrix = ThreeSpace::createSymmetricMatrix( -3.0, 0.0, 0.0,
							       -2.0, 0.0,
							            -1.0 ); 

  eigenvalues = LAP::computeEigenvaluesAndEigenvectors( coefficient_matrix,
							eigenvectors );

  ref_eigenvalues = ThreeSpace::createVector( -3.0, -2.0, -1.0 );
  
  ref_eigenvectors = ThreeSpace::identityMatrix();

  TEST_COMPARE_FLOATING_ARRAYS( eigenvalues_view, 
				ref_eigenvalues_view, 
				ST::prec() );  
  TEST_COMPARE_FLOATING_ARRAYS( eigenvectors_view,
				ref_eigenvectors_view,
				ST::prec() );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, 
			 computeEigenvaluesAndEigenvectors );

//---------------------------------------------------------------------------//
// Check if eigenvector realignment potential can be correctly determined
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy, 
				   isRealignable,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;

  typename ThreeSpace::Vector eigenvalues_1 = 
    ThreeSpace::createVector( 0.0, 0.0, 0.0 );

  typename ThreeSpace::Vector eigenvalues_2 = 
    ThreeSpace::createVector( 1.0, 0.0, 0.0 );

  typename ThreeSpace::Vector eigenvalues_3 = 
    ThreeSpace::createVector( 1.0, 2.0, 3.0 );

  typename ThreeSpace::Vector eigenvalues_4 = 
    ThreeSpace::createVector( 1.0, 1.0, 0.0 );

  typename ThreeSpace::Vector eigenvalues_5 = 
    ThreeSpace::createVector( 1.0, 0.0, 1.0 );
  
  typename ThreeSpace::Vector eigenvalues_6 = 
    ThreeSpace::createVector( 0.0, 1.0, 1.0 );
  
  typename ThreeSpace::Vector eigenvalues_7 = 
    ThreeSpace::createVector( 1.0, 1.0, 1.0 );

  TEST_ASSERT( !LAP::isRealignable( eigenvalues_1 ) );
  TEST_ASSERT( !LAP::isRealignable( eigenvalues_2 ) );
  TEST_ASSERT( !LAP::isRealignable( eigenvalues_3 ) );
  TEST_ASSERT( LAP::isRealignable( eigenvalues_4 ) );
  TEST_ASSERT( LAP::isRealignable( eigenvalues_5 ) );
  TEST_ASSERT( LAP::isRealignable( eigenvalues_6 ) );
  TEST_ASSERT( LAP::isRealignable( eigenvalues_7 ) );
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, isRealignable );

//---------------------------------------------------------------------------//
// Check that realignable eigenvectors are realigned correctly
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( LinearAlgebraPolicy,
				   realignEigenvectors,
				   ScalarType )
{ 
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;

  // z-axis alignment to x-axis alignment
  typename ThreeSpace::Vector eigenvalues = 
    ThreeSpace::createVector( 1.0, 1.0, 2.0 );
  typename ThreeSpace::Matrix eigenvectors =
    ThreeSpace::identityMatrix();

  LAP::realignEigenvectors( eigenvalues,
			    eigenvectors,
			    FACEMC::X_AXIS );

  typename ThreeSpace::Matrix ref_realigned_eigenvectors = 
    ThreeSpace::identityMatrix();
  LAP::swapColumns( ref_realigned_eigenvectors, 0, 2 );

  Teuchos::ArrayView<ScalarType> eigenvectors_view( eigenvectors.values(), 9 );
  Teuchos::ArrayView<ScalarType> ref_realigned_eigenvectors_view(
					   ref_realigned_eigenvectors.values(),
					   9 );

  TEST_COMPARE_ARRAYS( eigenvectors_view, ref_realigned_eigenvectors_view );

  // z-axis alignment to y-axis alignment
  eigenvalues = ThreeSpace::createVector( 1.0, 1.0, 2.0 );
  eigenvectors = ThreeSpace::identityMatrix();

  LAP::realignEigenvectors( eigenvalues,
			    eigenvectors,
			    FACEMC::Y_AXIS );

  ref_realigned_eigenvectors = ThreeSpace::identityMatrix();
  LAP::swapColumns( ref_realigned_eigenvectors, 1, 2 );
  
  TEST_COMPARE_ARRAYS( eigenvectors_view, ref_realigned_eigenvectors_view );

  // y-axis alignment to x-axis alignment
  eigenvalues = ThreeSpace::createVector( 1.0, 2.0, 1.0 );
  eigenvectors = ThreeSpace::identityMatrix();

  LAP::realignEigenvectors( eigenvalues,
  			    eigenvectors,
  			    FACEMC::X_AXIS );

  ref_realigned_eigenvectors = ThreeSpace::identityMatrix();
  LAP::swapColumns( ref_realigned_eigenvectors, 0, 1 );

  TEST_COMPARE_ARRAYS( eigenvectors_view, ref_realigned_eigenvectors_view );

  // y-axis alignment to z-axis alignment
  eigenvalues = ThreeSpace::createVector( 1.0, 2.0, 1.0 );
  eigenvectors = ThreeSpace::identityMatrix();

  LAP::realignEigenvectors( eigenvalues,
  			    eigenvectors,
  			    FACEMC::Z_AXIS );

  ref_realigned_eigenvectors = ThreeSpace::identityMatrix();
  LAP::swapColumns( ref_realigned_eigenvectors, 1, 2 );

  TEST_COMPARE_ARRAYS( eigenvectors_view, ref_realigned_eigenvectors_view );

  // x-axis alignment to y-axis alignment
  eigenvalues = ThreeSpace::createVector( 2.0, 1.0, 1.0 );
  eigenvectors = ThreeSpace::identityMatrix();

  LAP::realignEigenvectors( eigenvalues,
  			    eigenvectors,
  			    FACEMC::Y_AXIS );

  ref_realigned_eigenvectors = ThreeSpace::identityMatrix();
  LAP::swapColumns( ref_realigned_eigenvectors, 0, 1 );

  TEST_COMPARE_ARRAYS( eigenvectors_view, ref_realigned_eigenvectors_view );

  // x-axis alignment to z-axis alignment
  eigenvalues = ThreeSpace::createVector( 2.0, 1.0, 1.0 );
  eigenvectors = ThreeSpace::identityMatrix();

  LAP::realignEigenvectors( eigenvalues,
  			    eigenvectors,
  			    FACEMC::Z_AXIS );
  
  ref_realigned_eigenvectors = ThreeSpace::identityMatrix();
  LAP::swapColumns( ref_realigned_eigenvectors, 0, 2 );

  TEST_COMPARE_ARRAYS( eigenvectors_view, ref_realigned_eigenvectors_view );  
}

UNIT_TEST_INSTANTIATION( LinearAlgebraPolicy, realignEigenvectors );

//---------------------------------------------------------------------------//
// end tstLinearAlgebraPolicy.cpp
//---------------------------------------------------------------------------//

