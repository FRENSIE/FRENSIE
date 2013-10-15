//---------------------------------------------------------------------------//
//!
//! \file   LinearAlgebraAlgorithms.hpp
//! \author Alex Robinson
//! \brief  A collection of linear algebra algrorithm declarations.
//!
//---------------------------------------------------------------------------//

#ifndef LINEAR_ALBEGRA_ALGORITHMS_HPP
#define LINEAR_ALGEBRA_ALGORITHMS_HPP

// FACEMC Includes
#include "Vector.hpp"
#include "VectorHelpers.hpp"
#include "Matrix.hpp"

namespace FACEMC{

//! Enum for specifying whether eigenvectors should be calculated
enum EigenvectorComp{
  COMPUTE_EIGENVECTORS,
  IGNORE_EIGENVECTORS
};

namespace LinearAlgebra{

//! Compute the cross product of two vectors
template<typename ScalarType>
Vector<ScalarType> computeCrossProduct( const Vector<ScalarType> &a,
					const Vector<ScalarType> &b );

//! Compute the inverse of a general 3x3 matrix.
template<typename ScalarType>
Matrix<ScalarType> computeMatrixInverse( const Matrix<ScalarType> &matrix );

//! Solve a system of equations (Ax = b)
template<typename ScalarType>
Vector<ScalarType> solveSystem( const Matrix<ScalarType> &A,
				const Vector<ScalarType> &b );

/*! Compute the eigenvalues and eigenvectors of a symmetric 3x3 matrix
 * 
 * A symmetric matrix must be given so that the eigenvalues will be real.
 */
template<typename ScalarType>
Vector<ScalarType> computeEigenvaluesAndEigenvectors(
	       const Matrix<ScalarType> &matrix,
	       Matrix<ScalarType> &eigenvectors,
	       const EigenvectorComp eigenvector_comp = COMPUTE_EIGENVECTORS );

/*! Compute the eigenvalues of a symmetric 3x3 matrix
 *
 * A symmetric matrix must be given so that the eigenvalues will be real.
 */
template<typename ScalarType>
Vector<ScalarType> computeEigenvalues( const Matrix<ScalarType> &matrix );

//! Align eigenvectors with desired axis
template<typename ScalarType>
void realignEigenvectors( Vector<ScalarType> &eigenvalues,
			  Matrix<ScalarType> &eigenvectors,
			  const Axis alignment_axis = Z_AXIS );

} // end LinearAlgebra namespace

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "LinearAlgebraAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end LINEAR_ALGEBRA_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end LinearAlgebraAlgorithms.hpp
//---------------------------------------------------------------------------//
