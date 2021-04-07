//---------------------------------------------------------------------------//
//!
//! \file   Geometry_LinearAlgebraAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  A collection of linear algebra algorithm definitions.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_LINEAR_ALGEBRA_ALGORITHMS_DEF_HPP
#define GEOMETRY_LINEAR_ALGEBRA_ALGORITHMS_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_LAPACK.hpp>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Geometry{

namespace LinearAlgebra{

// Compute the cross product of two vectors
template<typename ScalarType>
Vector<ScalarType> computeCrossProduct( const Vector<ScalarType> &a,
					const Vector<ScalarType> &b )
{
  // The vectors must be valid
  testPrecondition( a.normTwo() > Teuchos::ScalarTraits<ScalarType>::zero() );
  testPrecondition( b.normTwo() > Teuchos::ScalarTraits<ScalarType>::zero() );

  ScalarType x = a[1]*b[2]-a[2]*b[1];
  ScalarType y = a[2]*b[0]-a[0]*b[2];
  ScalarType z = a[0]*b[1]-a[1]*b[0];

  return Vector<ScalarType>( x, y, z );
}

// Compute the inverse of a general 3x3 matrix.
template<typename ScalarType>
Matrix<ScalarType> computeMatrixInverse( const Matrix<ScalarType> &matrix )
{
  // The matrix must be nonsingular
  testPrecondition( matrix.isNonsingular() );

  // LAPACK wrapper
  Teuchos::LAPACK<typename Matrix<ScalarType>::ordinalType,
		  ScalarType> lapack;

  // The matrix dimensions
  typename Matrix<ScalarType>::ordinalType rows, cols;
  rows = matrix.numRows();
  cols = matrix.numCols();

  // The matrix will be modified during the calculation (make a copy)
  Matrix<ScalarType> matrix_copy( matrix );

  // Pivot indices
  typename Matrix<ScalarType>::ordinalType ipiv[3];

  // Computation info
  typename Matrix<ScalarType>::ordinalType success;

  // Compute the LU factorization of this matrix
  lapack.GETRF( rows,
		cols,
		matrix_copy.getRawPtr(),
		rows,
		ipiv,
		&success );

  // Work array
  ScalarType work[3];

  // Compute the inverse of this matrix and store in the input matrix
  lapack.GETRI( rows,
		matrix_copy.getRawPtr(),
		rows,
		ipiv,
		work,
		rows,
		&success );

  // The computation must be successful
  testPostcondition( success == 0 );

  return matrix_copy;
}

// Solve a system of equations (Ax = b)
template<typename ScalarType>
Vector<ScalarType> solveSystem( const Matrix<ScalarType> &A,
				const Vector<ScalarType> &b )
{
  // The matrix must be nonsingular
  testPrecondition( A.isNonsingular() );

  Matrix<ScalarType> A_inverse = computeMatrixInverse( A );
  Vector<ScalarType> b_copy( b );

  Vector<ScalarType> x;
  x.multiply( Teuchos::ScalarTraits<ScalarType>::one(),
	      A_inverse,
	      false,
	      b_copy,
	      Teuchos::ScalarTraits<ScalarType>::zero() );

  return x;
}

/* Compute the eigenvalues and eigenvectors of a symmetric 3x3 matrix
 *
 * A symmetric matrix must be given so that the eigenvalues will be real.
 */
template<typename ScalarType>
Vector<ScalarType> computeEigenvaluesAndEigenvectors(
	                            const Matrix<ScalarType> &matrix,
	                            Matrix<ScalarType> &eigenvectors,
	                            const EigenvectorComp eigenvector_comp )
{
  // The matrix must be symmetric
  testPrecondition( matrix.isSymmetric() );

  // LAPACK wrapper
  Teuchos::LAPACK<typename Matrix<ScalarType>::ordinalType,
		  ScalarType> lapack;

  // The matrix will be modified during the calculation (make a copy)
  Matrix<ScalarType> matrix_copy( matrix );

  // Assign the calculation type
  char jobz;
  if( eigenvector_comp == IGNORE_EIGENVECTORS )
    jobz = 'N'; // Eigenvectors will not be computed
  else
    jobz = 'V';

  // The upper triangle of the matrix is stored
  char uplo = 'U';

  // The order of the matrix
  typename Matrix<ScalarType>::ordinalType order = 3;

  // The Eigenvalues
  Vector<ScalarType> eigenvalues;

  // The length of the work array
  typename Matrix<ScalarType>::ordinalType lwork = 3*3-1;

  // The work array
  ScalarType work[lwork];

  // Computation info
  typename Matrix<ScalarType>::ordinalType success;

  // Compute the eigenvalues (and possible eigenvectors) of this matrix
  lapack.SYEV( jobz,
	       uplo,
	       order,
	       matrix_copy.getRawPtr(),
	       order,
	       eigenvalues.getRawPtr(),
	       work,
	       lwork,
	       &success );

  // The computation must be successful
  testPostcondition( success == 0 );

  if( eigenvector_comp == COMPUTE_EIGENVECTORS )
  {
    eigenvectors = matrix_copy;

    // The matrix of eigenvectors must be orthonormal
    testPostcondition( eigenvectors.isOrthonormal() );
  }

  return eigenvalues;
}

/* Compute the eigenvalues of a symmetric 3x3 matrix
 *
 * A symmetric matrix must be given so that the eigenvalues will be real.
 */
template<typename ScalarType>
Vector<ScalarType> computeEigenvalues( const Matrix<ScalarType> &matrix )
{
  // The matrix must be symmetric
  testPrecondition( matrix.isSymmetric() );

  // Dummy matrix (since eigenvectors will be ignored)
  Matrix<ScalarType> dummy_matrix;

  return computeEigenvaluesAndEigenvectors( matrix,
					    dummy_matrix,
					    IGNORE_EIGENVECTORS );
}

// Align eigenvectors with desired axis
template<typename ScalarType>
void realignEigenvectors( Vector<ScalarType> &eigenvalues,
			  Matrix<ScalarType> &eigenvectors,
			  const Utility::Axis alignment_axis )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  // Make sure the eigenvalues are valid
  testPrecondition( eigenvalues.normTwo() > ST::zero() );
  // Make sure that the eigenvalues are realignable
  testPrecondition( !eigenvalues.hasUniqueElements() );
  // Make sure the matrix of eigenvectors is orthonormal
  testPrecondition( eigenvectors.isOrthonormal() );
  // Make sure that a valid alignment axis is requested
  testPrecondition( alignment_axis != Utility::UNDEFINED_AXIS );

  ScalarType eigenvalue_0 = eigenvalues[0];
  ScalarType eigenvalue_1 = eigenvalues[1];
  ScalarType eigenvalue_2 = eigenvalues[2];
  ScalarType repeated_eigenvalue, distinct_eigenvalue;
  Utility::Axis current_alignment_axis;

  if( ST::magnitude( eigenvalue_0 - eigenvalue_1 ) < ST::prec() )
  {
    repeated_eigenvalue = eigenvalue_0;
    distinct_eigenvalue = eigenvalue_2;
    current_alignment_axis = Utility::Z_AXIS;
  }
  else if( ST::magnitude( eigenvalue_0 - eigenvalue_2 ) < ST::prec() )
  {
    repeated_eigenvalue = eigenvalue_0;
    distinct_eigenvalue = eigenvalue_1;
    current_alignment_axis = Utility::Y_AXIS;
  }
  else if( ST::magnitude( eigenvalue_1 - eigenvalue_2 ) < ST::prec() )
  {
    repeated_eigenvalue = eigenvalue_1;
    distinct_eigenvalue = eigenvalue_0;
    current_alignment_axis = Utility::X_AXIS;
  }
  else
    current_alignment_axis = Utility::UNDEFINED_AXIS;

  if( current_alignment_axis != alignment_axis )
  {
    if( current_alignment_axis == Utility::X_AXIS &&
	alignment_axis == Utility::Y_AXIS )
    {
      eigenvalues[0] = repeated_eigenvalue;
      eigenvalues[1] = distinct_eigenvalue;
      eigenvectors.swapColumns( 0, 1 );
    }
    else if( current_alignment_axis == Utility::X_AXIS &&
	     alignment_axis == Utility::Z_AXIS )
    {
      eigenvalues[0] = repeated_eigenvalue;
      eigenvalues[2] = distinct_eigenvalue;
      eigenvectors.swapColumns( 0, 2 );
    }
    else if( current_alignment_axis == Utility::Y_AXIS &&
	     alignment_axis == Utility::X_AXIS )
    {
      eigenvalues[1] = repeated_eigenvalue;
      eigenvalues[0] = distinct_eigenvalue;
      eigenvectors.swapColumns( 1, 0 );
    }
    else if( current_alignment_axis == Utility::Y_AXIS &&
	     alignment_axis == Utility::Z_AXIS )
    {
      eigenvalues[1] = repeated_eigenvalue;
      eigenvalues[2] = distinct_eigenvalue;
      eigenvectors.swapColumns( 1, 2 );
    }
    else if( current_alignment_axis == Utility::Z_AXIS &&
	     alignment_axis == Utility::X_AXIS )
    {
      eigenvalues[2] = repeated_eigenvalue;
      eigenvalues[0] = distinct_eigenvalue;
      eigenvectors.swapColumns( 2, 0 );
    }
    else if( current_alignment_axis == Utility::Z_AXIS &&
	     alignment_axis == Utility::Y_AXIS )
    {
      eigenvalues[2] = repeated_eigenvalue;
      eigenvalues[1] = distinct_eigenvalue;
      eigenvectors.swapColumns( 2, 1 );
    }
  }

  // Make sure that a valid alignment axis was found
  testPostcondition( current_alignment_axis != Utility::UNDEFINED_AXIS );
}

} // end LinearAlgebra namespace

} // end Geometry namespace

#endif // end GEOMETRY_LINEAR_ALGEBRA_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end GeometrY_LinearAlgebraAlgorithms_def.hpp
//---------------------------------------------------------------------------//

