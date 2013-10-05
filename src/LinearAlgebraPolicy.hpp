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
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_LAPACK.hpp>
#include <Teuchos_SerialDenseHelpers.hpp>

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

// Compute the cosine of the angle between two vectors
template<typename ScalarType>
inline ScalarType
LinearAlgebraPolicy<ScalarType>::computeCosineAngleBetweenVectors(
							      const Vector &a,
							      const Vector &b )
{
  // The vectors must be three space vectors
  testPrecondition( a.length() == 3 );
  testPrecondition( b.length() == 3 );
  // The vectors must be valid
  testPrecondition( a.normFrobenius() > ST::zero() );
  testPrecondition( b.normFrobenius() > ST::zero() );

  return a.dot( b )/(a.normFrobenius()*b.normFrobenius());
}

// Compute the cross product of two vectors
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
LinearAlgebraPolicy<ScalarType>::computeCrossProduct( const Vector &a,
						      const Vector &b )
{
  // The vectors must be three space vectors
  testPrecondition( a.length() == 3 );
  testPrecondition( a.length() == 3 );
  // The vectors must be valid
  testPrecondition( a.normFrobenius() > ST::zero() );
  testPrecondition( b.normFrobenius() > ST::zero() );

  ScalarType x = a[1]*b[2]-a[2]*b[1];
  ScalarType y = a[2]*b[0]-a[0]*b[2];
  ScalarType z = a[0]*b[1]-a[1]*b[0];
  
  return ThreeSpace::createVector( x, y, z );
}

// Test if a vector is parallel to another vector
template<typename ScalarType>
bool LinearAlgebraPolicy<ScalarType>::isParallel( const Vector &a,
						  const Vector &b )
{
  // The vectors must be three space vectors
  testPrecondition( a.length() == 3 );
  testPrecondition( b.length() == 3 );

  ScalarType cos_angle = 
    LinearAlgebraPolicy<ScalarType>::computeCosineAngleBetweenVectors( a, b );

  if( ST::magnitude( cos_angle - ST::one() ) < ST::prec() )
    return true;
  else
    return false;
}

// Test if a vector is antiparallel to another vector
template<typename ScalarType>
bool LinearAlgebraPolicy<ScalarType>::isAntiparallel( const Vector &a,
						      const Vector &b )
{
  // The vectors must be three space vectors
  testPrecondition( a.length() == 3 );
  testPrecondition( b.length() == 3 );

  ScalarType cos_angle = 
    LinearAlgebraPolicy<ScalarType>::computeCosineAngleBetweenVectors( a, b );

  if( ST::magnitude( cos_angle + ST::one() ) < ST::prec() )
    return true;
  else
    return false;
}

// Test if a matrix is symmetric
template<typename ScalarType>
bool LinearAlgebraPolicy<ScalarType>::isSymmetric( const Matrix &matrix )
{
  // Make sure that the matrix is 3x3
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );

  return ( ( matrix( 0, 1 ) == matrix( 1, 0 ) ) &&
	   ( matrix( 0, 2 ) == matrix( 2, 0 ) ) &&
	   ( matrix( 1, 2 ) == matrix( 2, 1 ) ) );
}

// Test if a matrix is orthonormal
template<typename ScalarType>
bool LinearAlgebraPolicy<ScalarType>::isOrthonormal( const Matrix &matrix )
{
  // Make sure that the matrix is 3x3
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );

  Matrix matrix_copy = matrix;

  typename ThreeSpace::ordinalType col_index = 
    Teuchos::OrdinalTraits<typename ThreeSpace::ordinalType>::zero();

  Vector column_1 = Teuchos::getCol( Teuchos::View, matrix_copy, col_index );
  Vector column_2 = Teuchos::getCol( Teuchos::View, matrix_copy, ++col_index );
  Vector column_3 = Teuchos::getCol( Teuchos::View, matrix_copy, ++col_index );

  ScalarType column_1_magnitude = column_1.normFrobenius();
  ScalarType column_2_magnitude = column_2.normFrobenius();
  ScalarType column_3_magnitude = column_3.normFrobenius();

  // Allow for floating point error
  typename ST::magnitudeType tol = ST::prec();

  bool normal_columns = 
    ( ( ST::magnitude( column_1_magnitude - ST::one() ) < tol ) &&
      ( ST::magnitude( column_2_magnitude - ST::one() ) < tol ) &&
      ( ST::magnitude( column_3_magnitude - ST::one() ) < tol ) );

  bool orthogonal_columns =
    ( ( ST::magnitude( column_1.dot( column_2 ) ) < tol ) &&
      ( ST::magnitude( column_1.dot( column_3 ) ) < tol ) &&
      ( ST::magnitude( column_2.dot( column_3 ) ) < tol ) );
  
  return normal_columns && orthogonal_columns;
}

template<typename ScalarType>
bool LinearAlgebraPolicy<ScalarType>::isNonsingular( const Matrix &matrix )
{
  // Make sure that the matrix is 3x3
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

  // Check if the LU factorization of this matrix can be completed (if
  // yes, the matrix is nonsingular).
  lapack.GETRF( rows, 
		cols, 
		matrix_copy.values(), 
		rows, 
		ipiv, 
		&success );

  if( success == 0 )
    return true;
  else
    return false;
}

// Swap columns of a matrix
template<typename ScalarType>
void LinearAlgebraPolicy<ScalarType>::swapColumns( Matrix &matrix,
						   ordinalType column_a_index,
						   ordinalType column_b_index )
{
  // Make sure the matrix is 3x3
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );
  
  // The ordinal type used for the LinearAlgebraPolicy is not guaranteed to be
  // equal to the ordinal type used by the Matrix class - cast for safety with
  // template function type deduction.
  Vector column_a = Teuchos::getCol( 
		 Teuchos::Copy,
		 matrix,
		 static_cast<typename Matrix::ordinalType>( column_a_index ) );
  Vector column_b = Teuchos::getCol(
		 Teuchos::Copy,
		 matrix,
		 static_cast<typename Matrix::ordinalType>( column_b_index ) );

  bool success = true;
  bool set_success = true;

  set_success = Teuchos::setCol( 
		   column_b,
		   static_cast<typename Matrix::ordinalType>( column_a_index ),
		   matrix );
  
  success = set_success;

  set_success = Teuchos::setCol(
		   column_a,
		   static_cast<typename Matrix::ordinalType>( column_b_index ),
		   matrix );
  
  success = success && set_success;

  // Make sure that all set operations were successful
  testPostcondition( success );				
}

// Create a vector that satisfies the relationship n*x0+const = 0 => return x0
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
LinearAlgebraPolicy<ScalarType>::createZeroingVector( 
					       const Vector &vector,
					       const ScalarType constant_term )
{
  // The vector must be a three space vector
  testPrecondition( vector.length() == 3 );
  // The vector must be valid
  testPrecondition( vector.normFrobenius() > ST::one()-ST::prec() );
  
  Vector zeroing_vector;
  ScalarType zeroing_term;

  if( ST::magnitude( vector[0] ) > ST::prec() )
  {
    zeroing_term = -constant_term/vector[0];
    
    zeroing_vector = ThreeSpace::createVector( zeroing_term,
						ST::zero(),
						ST::zero() );
  }
  else if( ST::magnitude( vector[1] ) > ST::prec() )
  {
    zeroing_term = -constant_term/vector[1];
    
    zeroing_vector = ThreeSpace::createVector( ST::zero(),
					       zeroing_term,
					       ST::zero() );
  }
  else
  {
    zeroing_term = -constant_term/vector[2];

    zeroing_vector = ThreeSpace::createVector( ST::zero(),
					       ST::zero(),
					       zeroing_term );
  }
  
  return zeroing_vector;
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

  Matrix rotation_matrix = ThreeSpace::createSquareMatrix( 
						   1.0, 0.0,       0.0,
						   0.0, cos_angle, -sin_angle,
						   0.0, sin_angle, cos_angle );

  // The rotation matrix must be orthonormal
  testPostcondition( LinearAlgebraPolicy<ScalarType>::isOrthonormal( 
							   rotation_matrix ) );

  return rotation_matrix;
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

  Matrix rotation_matrix =  ThreeSpace::createSquareMatrix(
						  cos_angle,  0.0, sin_angle,
						  0.0,        1.0, 0.0,
						  -sin_angle, 0.0, cos_angle );

  // The rotation matrix must be orthonormal
  testPostcondition( LinearAlgebraPolicy<ScalarType>::isOrthonormal( 
							   rotation_matrix ) );

  return rotation_matrix;
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

  Matrix rotation_matrix =  ThreeSpace::createSquareMatrix(
						  cos_angle, -sin_angle, 0.0,
						  sin_angle, cos_angle,  0.0,
						  0.0,       0.0,        1.0 );

  // The rotation matrix must be orthonormal
  testPostcondition( LinearAlgebraPolicy<ScalarType>::isOrthonormal( 
							   rotation_matrix ) );

  return rotation_matrix;
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
				   ST::one() ) < ST::prec() );
  // The final direction must be a unit vector
  testPrecondition( ST::magnitude( final_direction.normFrobenius() - 
				   ST::one() ) < ST::prec() );
  // Both directions must be three space vectors
  testPrecondition( initial_direction.length() == 3 );
  testPrecondition( initial_direction.length() == 3 );

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
  if( ST::magnitude( ST::magnitude( w_i ) - ST::one() ) > ST::prec() )
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
  if( ST::magnitude( ST::magnitude( w_f ) - ST::one() ) > ST::prec() )
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
  // The rotation matrix must be orthonormal
  testPostcondition( LinearAlgebraPolicy<ScalarType>::isOrthonormal( 
							   rotation_matrix ) );

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
  // The matrix must be nonsingular
  testPrecondition( LinearAlgebraPolicy<ScalarType>::isNonsingular( matrix ) );

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

// Solve a system of equations (Ax = b)
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
LinearAlgebraPolicy<ScalarType>::solveSystem( const Matrix &A,
					      const Vector &b )
{
  // The matrix must be a three space matrix
  testPrecondition( A.numRows() == 3 );
  testPrecondition( A.numCols() == 3 );
  // The matrix must be nonsingular
  testPrecondition( LinearAlgebraPolicy<ScalarType>::isNonsingular( A ) );
  // The vector must be a three space vector
  testPrecondition( b.length() == 3 );
  
  Matrix A_inverse = 
    LinearAlgebraPolicy<ScalarType>::computeMatrixInverse( A );

  Vector x( 3 );
  x.multiply( Teuchos::NO_TRANS,
	      Teuchos::NO_TRANS,
	      1.0,
	      A_inverse,
	      b,
	      0.0 );

  return x;  
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
  testPrecondition( LinearAlgebraPolicy<ScalarType>::isSymmetric( matrix ) );
  
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
  testPrecondition( LinearAlgebraPolicy<ScalarType>::isSymmetric( matrix ) );

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
  {
    eigenvectors = matrix_copy;
    // The matrix of eigenvectors must be orthonormal
    testPostcondition( LinearAlgebraPolicy<ScalarType>::isOrthonormal( 
							      eigenvectors ) );
  }
  
  return eigenvalues;
}

// Check if the eigenvectors can be realigned
/* \details The eigenvectors can be realigned if there are atleast two
 * identical, nonzero eigenvalues.
 */
template<typename ScalarType>
bool LinearAlgebraPolicy<ScalarType>::isRealignable( 
						    const Vector &eigenvalues )
{
  ScalarType eigenvalue_0 = eigenvalues[0];
  ScalarType eigenvalue_1 = eigenvalues[1];
  ScalarType eigenvalue_2 = eigenvalues[2];

  bool realignable = false;

  if( ST::magnitude( eigenvalue_0 - eigenvalue_1 ) < ST::prec() &&
      ST::magnitude( eigenvalue_0 ) > ST::zero() )
    realignable = true;
  else if( ST::magnitude( eigenvalue_0 - eigenvalue_2 ) < ST::prec() &&
	   ST::magnitude( eigenvalue_0 ) > ST::zero() )
    realignable = true;
  else if( ST::magnitude( eigenvalue_1 - eigenvalue_2 ) < ST::prec() &&
	   ST::magnitude( eigenvalue_1 ) > ST::zero() )
    realignable = true;
  
  return realignable;
}

// Align eigenvectors with desired axis
/* \details Assume that a three space vector holds an x value, a y value and
 * a z value (vector[0] => x, vector[1] => y, vector[2] => z). To realign
 * the eigenvectors the eigenvalues must be analyzed first. Realignment can
 * only occur if there are two identical eigenvalues. If this is the case,
 * the two identical eigenvalues, and the corresponding eigenvectors, will be
 * moved to the vector locations that don't represent the alignment axis. 
 */
template<typename ScalarType>
void
LinearAlgebraPolicy<ScalarType>::realignEigenvectors( 
						    Vector &eigenvalues,
						    Matrix &eigenvectors,
						    const Axis alignment_axis )
{
  // Make sure the vector of eigenvalues is a three space vector
  testPrecondition( eigenvalues.length() == 3 );
  // Make sure the eigenvalues are valid
  testPrecondition( eigenvalues.normFrobenius() > 0.0 );
  // Make sure the eigenvectors are realignable
  testPrecondition( LinearAlgebraPolicy<ScalarType>::isRealignable( 
							       eigenvalues ) );
  // Make sure the matrix of eigenvectors is 3x3
  testPrecondition( eigenvectors.numRows() == 3 );
  testPrecondition( eigenvectors.numCols() == 3 );
  // Make sure the matrix of eigenvectors must be orthonormal
  testPrecondition( LinearAlgebraPolicy<ScalarType>::isOrthonormal( 
							      eigenvectors ) );
  // Make sure that a valid alignment axis is requested
  testPrecondition( alignment_axis != UNDEFINED_AXIS );

  ScalarType eigenvalue_0 = eigenvalues[0];
  ScalarType eigenvalue_1 = eigenvalues[1];
  ScalarType eigenvalue_2 = eigenvalues[2];
  ScalarType repeated_eigenvalue, distinct_eigenvalue;
  Axis current_alignment_axis;
  
  if( ST::magnitude( eigenvalue_0 - eigenvalue_1 ) < ST::prec() )
  {
    repeated_eigenvalue = eigenvalue_0;
    distinct_eigenvalue = eigenvalue_2;
    current_alignment_axis = Z_AXIS;
  }
  else if( ST::magnitude( eigenvalue_0 - eigenvalue_2 ) < ST::prec() )
  {
    repeated_eigenvalue = eigenvalue_0;
    distinct_eigenvalue = eigenvalue_1;
    current_alignment_axis = Y_AXIS;
  }
  else if( ST::magnitude( eigenvalue_1 - eigenvalue_2 ) < ST::prec() )
  {
    repeated_eigenvalue = eigenvalue_1;
    distinct_eigenvalue = eigenvalue_0;
    current_alignment_axis = X_AXIS;
  }
  else 
    current_alignment_axis = UNDEFINED_AXIS;

  if( current_alignment_axis != alignment_axis )
  {
    if( current_alignment_axis == X_AXIS && alignment_axis == Y_AXIS )
    {
      eigenvalues[0] = repeated_eigenvalue;
      eigenvalues[1] = distinct_eigenvalue;
      LinearAlgebraPolicy<ScalarType>::swapColumns( eigenvectors, 0, 1 );
    }
    else if( current_alignment_axis == X_AXIS && alignment_axis == Z_AXIS )
    {
      eigenvalues[0] = repeated_eigenvalue;
      eigenvalues[2] = distinct_eigenvalue;
      LinearAlgebraPolicy<ScalarType>::swapColumns( eigenvectors, 0, 2 );
    }
    else if( current_alignment_axis == Y_AXIS && alignment_axis == X_AXIS )
    {
      eigenvalues[1] = repeated_eigenvalue;
      eigenvalues[0] = distinct_eigenvalue;
      LinearAlgebraPolicy<ScalarType>::swapColumns( eigenvectors, 1, 0 );
    }
    else if( current_alignment_axis == Y_AXIS && alignment_axis == Z_AXIS )
    {
      eigenvalues[1] = repeated_eigenvalue;
      eigenvalues[2] = distinct_eigenvalue;
      LinearAlgebraPolicy<ScalarType>::swapColumns( eigenvectors, 1, 2 );
    }
    else if( current_alignment_axis == Z_AXIS && alignment_axis == X_AXIS )
    {
      eigenvalues[2] = repeated_eigenvalue;
      eigenvalues[0] = distinct_eigenvalue;
      LinearAlgebraPolicy<ScalarType>::swapColumns( eigenvectors, 2, 0 );
    }
    else if( current_alignment_axis == Z_AXIS && alignment_axis == Y_AXIS )
    {
      eigenvalues[2] = repeated_eigenvalue;
      eigenvalues[1] = distinct_eigenvalue;
      LinearAlgebraPolicy<ScalarType>::swapColumns( eigenvectors, 2, 1 );
    }
  }

  // Make sure that a valid alignment axis was found
  testPostcondition( current_alignment_axis != UNDEFINED_AXIS );
}

} // end FACEMC namespace

#endif // end LINEAR_ALGEBRA_POLICY_HPP

//---------------------------------------------------------------------------//
// end LinearAlgebraPolicy.hpp
//---------------------------------------------------------------------------//
