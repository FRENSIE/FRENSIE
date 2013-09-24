//---------------------------------------------------------------------------//
//!
//! \file   LinearAlgebraPolicy.hpp
//! \author Alex Robinson
//! \brief  Linear algebra policy definition
//!
//---------------------------------------------------------------------------//

#ifndef LINEAR_ALGEBRA_POLICY_HPP
#define LINEAR_ALGEBRA_POLICY_HPP

// Std Lib Includes
#include <cmath>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_LAPACK.hpp>

// FACEMC Includes
#include "ThreeSpaceTraitsAndPolicy.hpp"
#include "LinearAlgebraPolicyDecl.hpp"
#include "ContractException.hpp"

namespace FACEMC{

 // Normalize a vector
template<typename ScalarType>
inline void LinearAlgebraPolicy<ScalarType>::normalizeVector( Vector &vector )
{
  // The vector must be a three space vector
  testPrecondition( vector.length() == 3 );
  
  vector.scale( 1.0/vector.normFrobenius() );
}

// Generate a rotation matrix for rotation about the x-axis
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix
LinearAlgebraPolicy<ScalarType>::createXAxisRotationMatrix( 
					      const ScalarType rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( ScalarType pi = acos( -1.0 ) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );

  ScalarType cos_angle = cos( rotation_angle );
  ScalarType sin_angle = sin( rotation_angle );

  return ThreeSpaceTraitsAndPolicy<ScalarType>::createSquareMatrix(
						   1.0, 0.0,       0.0,
						   0.0, cos_angle, -sin_angle,
						   0.0, sin_angle, cos_angle );
						  
}

// Generate a rotation matrix for rotation about the y-axis
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix
LinearAlgebraPolicy<ScalarType>::createYAxisRotationMatrix(
					      const ScalarType rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( ScalarType pi = acos( -1.0 ) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );

  ScalarType cos_angle = cos( rotation_angle );
  ScalarType sin_angle = sin( rotation_angle );

  return ThreeSpaceTraitsAndPolicy<ScalarType>::createSquareMatrix(
						  cos_angle,  0.0, sin_angle,
						  0.0,        1.0, 0.0,
						  -sin_angle, 0.0, cos_angle );
}

// Generate a rotation matrix for rotation about the z-axis
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix
LinearAlgebraPolicy<ScalarType>::createZAxisRotationMatrix(
					      const ScalarType rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( ScalarType pi = acos( -1.0 ) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );

  ScalarType cos_angle = cos( rotation_angle );
  ScalarType sin_angle = sin( rotation_angle );

  return ThreeSpaceTraitsAndPolicy<ScalarType>::createSquareMatrix(
						  cos_angle, -sin_angle, 0.0,
						  sin_angle, cos_angle,  0.0,
						  0.0,       0.0,        1.0 );
}

// Generate a rotation matrix that will rotate one unit vector to another.
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix
LinearAlgebraPolicy<ScalarType>::createRotationMatrixFromUnitVectors(
					       const Vector &initial_direction,
					       const Vector &final_direction )
{
  // The initial direction must be a unit vector
  testPrecondition( ST::magnitude( initial_direction.normFrobenius() - 
				   ST::one() ) < ST::eps() );
  // The final direction must be a unit vector
  testPrecondition( ST::magnitude( final_direction.normFrobenius() - 
				   ST::one() ) < ST::eps() );

  ScalarType u_i = initial_direction[0];
  ScalarType v_i = initial_direction[1];
  ScalarType w_i = initial_direction[2];
  ScalarType arg_i = ST::squareroot( ST::one() - w_i*w_i );
  
  ScalarType u_f = final_direction[0];
  ScalarType v_f = final_direction[1];
  ScalarType w_f = final_direction[2];
  ScalarType arg_f = ST::squareroot( ST::one() - w_f*w_f );

  Matrix initial_dir_to_zaxis_matrix;
  Matrix zaxis_to_final_dir_matrix;

  // Create a rotation matrix for rotating the initial direction to the z-axis
  if( ST::magnitude( ST::magnitude( w_i ) - ST::one() ) > ST::eps() )
  {
    initial_dir_to_zaxis_matrix = ThreeSpace::createSquareMatrix( 
					  u_i*w_i/arg_i, v_i*w_i/arg_i, -arg_i,
					  -v_i/arg_i,    u_i/arg_i, ST::zero(),
					  u_i,           v_i,           w_i );
  }
  // The initial direction is parallel to the z-axis
  else if( w_i > ST::zero() )
  {
    initial_dir_to_zaxis_matrix = ThreeSpace::createSquareMatrix( 
					   ST::one(), ST::zero(), ST::zero(),
					   ST::zero(), ST::one(), ST::zero(),
					   ST::zero(), ST::zero(), ST::one() );
  }
  // The initial direction is anti-parallel to the z-axis
  else
  {
    initial_dir_to_zaxis_matrix = ThreeSpace::createSquareMatrix(
					  ST::one(), ST::zero(), ST::zero(),
					  ST::zero(), ST::one(), ST::zero(),
					  ST::zero(), ST::zero(), -ST::one() );
  }

  // Create a rotation matrix for rotating the z-axis to the final direction
  if( ST::magnitude( ST::magnitude( w_f ) - ST::one() ) > ST::eps() )
  {
    zaxis_to_final_dir_matrix = ThreeSpace::createSquareMatrix(
					      u_f*w_f/arg_f, -v_f/arg_f, u_f,
					      v_f*w_f/arg_f, u_f/arg_f,  v_f,
					      -arg_f,        ST::zero(), w_f );
  }
  // The final direction is parallel to the z-axis
  else if( w_f > ST::zero() )
  {
    zaxis_to_final_dir_matrix = ThreeSpace::createSquareMatrix(
					   ST::one(), ST::zero(), ST::zero(),
					   ST::zero(), ST::one(), ST::zero(),
					   ST::zero(), ST::zero(), ST::one() );
  }
  // The final direction is anti-parallel to the z-axis
  else
  {
    zaxis_to_final_dir_matrix = ThreeSpace::createSquareMatrix(
					  ST::one(), ST::zero(), ST::zero(),
					  ST::zero(), ST::one(), ST::zero(),
					  ST::zero(), ST::zero(), -ST::one() );
  }

  // Successful multiplication returns 0
  remember( int multiply_success = 0 );  

  Matrix rotation_matrix( 3, 3 );

  remember( multiply_success = )
    rotation_matrix.multiply( Teuchos::NO_TRANS, 
			      Teuchos::NO_TRANS,
			      1.0,
			      zaxis_to_final_dir_matrix,
			      initial_dir_to_zaxis_matrix,
			      0.0 );

  // Check that the matrix multiplication was successful
  testPostcondition( multiply_success == 0 );

  return rotation_matrix;
}

// Compute the inverse of a general 3x3 matrix
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix 
LinearAlgebraPolicy<ScalarType>::computeMatrixInverse( const Matrix &matrix )
{
  // The matrix must be a three space matrix
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );

  // LAPACK wrapper
  LapackWrapper lapack;
  
  // The matrix dimensions
  ordinalType rows = matrix.numRows();
  ordinalType cols = matrix.numCols();
  
  // The matrix will be modified during the calculation (make a copy)
  Matrix matrix_copy( matrix );

  // Pivot indices
  ordinalType ipiv[3];

  // Computation info
  ordinalType success;

  // Compute the LU factorization of this matrix
  lapack.GETRF( rows, 
		cols, 
		matrix_copy.values(), 
		rows, 
		ipiv, 
		&success );

  // Work array
  Vector work( 3 );

  // Compute the inverse of this matrix and store in the input matrix
  lapack.GETRI( rows, 
		matrix_copy.values(), 
		rows, 
		ipiv, 
		work.values(), 
		rows,
		&success );

  // The computation must be successful
  testPostcondition( success == 0 );

  return matrix_copy;
}

// Compute the eigenvalues of a symmetric 3x3 matrix
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
LinearAlgebraPolicy<ScalarType>::computeEigenvalues( const Matrix &matrix )
{
  // The matrix must be a three space matrix
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );
  // The matrix must be symmetric
  testPrecondition( matrix( 0, 1 ) == matrix( 1, 0 ) );
  testPrecondition( matrix( 0, 2 ) == matrix( 2, 0 ) );
  testPrecondition( matrix( 1, 2 ) == matrix( 2, 1 ) );
  
  // Dummy matrix (since eigenvectors will be ignored)
  Matrix dummy;

  return computeEigenvaluesAndEigenvectors( matrix,
					    dummy,
					    IGNORE_EIGENVECTORS );
}

// Compute the eigenvalues and eigenvectors of a symmetric 3x3 matrix.
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
LinearAlgebraPolicy<ScalarType>::computeEigenvaluesAndEigenvectors( 
				       const Matrix &matrix,
				       Matrix &eigenvectors,
				       const EigenvectorComp eigenvector_comp )
{
  // The matrix must be a three space matrix
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );
  // The matrix must be symmetric
  testPrecondition( matrix( 0, 1 ) == matrix( 1, 0 ) );
  testPrecondition( matrix( 0, 2 ) == matrix( 2, 0 ) );
  testPrecondition( matrix( 1, 2 ) == matrix( 2, 1 ) );

  // LAPACK wrapper
  LapackWrapper lapack;
  
  // The matrix will be modified during the calculation (make a copy)
  Matrix matrix_copy( matrix );

  char jobz;
  if( eigenvector_comp == IGNORE_EIGENVECTORS )
    jobz = 'N'; // Do not compute the Eigenvectors
  else if( eigenvector_comp == COMPUTE_EIGENVECTORS )
    jobz = 'V'; // Compute Eigenvectors

  // The upper triangle of the matrix is stored
  char uplo = 'U';

  // The order of the matrix
  ordinalType order = 3;

  // The Eigenvalues
  Vector eigenvalues( 3 );

  // The length of the work array
  ordinalType lwork = 3*3-1;

  // Work array
  Vector work( lwork );

  // Computation info
  ordinalType success;

  // Compute the eigenvalues of this matrix
  lapack.SYEV( jobz, 
	       uplo, 
	       order, 
	       matrix_copy.values(),
	       order,
	       eigenvalues.values(),
	       work.values(),
	       lwork,
	       &success );

  // The computation must be successful
  testPostcondition( success == 0 );

  if( eigenvector_comp == COMPUTE_EIGENVECTORS )
    eigenvectors = matrix_copy;
  
  return eigenvalues;
}

} // end FACEMC namespace

#endif // end LINEAR_ALGEBRA_POLICY_HPP

//---------------------------------------------------------------------------//
// end LinearAlgebraPolicy.hpp
//---------------------------------------------------------------------------//
