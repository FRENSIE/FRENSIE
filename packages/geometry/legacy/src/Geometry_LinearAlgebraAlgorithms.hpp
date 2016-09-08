//---------------------------------------------------------------------------//
//!
//! \file   Geometry_LinearAlgebraAlgorithms.hpp
//! \author Alex Robinson
//! \brief  A collection of linear algebra algrorithm declarations.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_LINEAR_ALGEBRA_ALGORITHMS_HPP
#define GEOMETRY_LINEAR_ALGEBRA_ALGORITHMS_HPP

// FRENSIE Includes
#include "Geometry_Vector.hpp"
#include "Geometry_VectorHelpers.hpp"
#include "Geometry_Matrix.hpp"

namespace Geometry{

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
void realignEigenvectors(
			Vector<ScalarType> &eigenvalues,
			Matrix<ScalarType> &eigenvectors,
			const Utility::Axis alignment_axis = Utility::Z_AXIS );

} // end LinearAlgebra namespace

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_LinearAlgebraAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_LINEAR_ALGEBRA_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end Geometry_LinearAlgebraAlgorithms.hpp
//---------------------------------------------------------------------------//
