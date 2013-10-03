//---------------------------------------------------------------------------//
//!
//! \file   LinearAlgebraPolicyDecl.hpp
//! \author Alex Robinson
//! \brief  Linear algebra policy declaration.
//---------------------------------------------------------------------------//

#ifndef LINEAR_ALGEBRA_POLICY_DECL_HPP
#define LINEAR_ALGEBRA_POLICY_DECL_HPP

// Trilinos Includes
#include "Teuchos_LAPACK.hpp"

// FACEMC Includes
#include "ThreeSpaceTraitsAndPolicy.hpp"

/*! \defgroup linear_algebra_policies Linear Algebra Policies
 * \ingroup policy
 *
 * Add description
 */

namespace FACEMC{

  //! Enum for specifying whether eigenvectors should be calculated
  enum EigenvectorComp{
    COMPUTE_EIGENVECTORS,
    IGNORE_EIGENVECTORS
  };

  //! Enum for specifying which axis to align eigenvectors with
  enum Axis{
    X_AXIS,
    Y_AXIS,
    Z_AXIS,
    UNDEFINED_AXIS
  };

  /*! \brief This struct provides some convenient linear algebra functions
   * that are required by FACEMC.
   * \ingroup linear_algebra_policies
   *
   * Specializations aren't required for this struct since the SerialDense
   * classes already give compile time errors if the ordinal tyep and scalar 
   * type do not have specializations.
   */
template<typename ScalarType>
struct LinearAlgebraPolicy
{

private:

  // Typedef for ThreeSpaceTraitsAndPolicy
  typedef ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;

  // Scalar type
  typedef ScalarType scalarType;

  // Ordinal type
  typedef int ordinalType;

  // The vector type that will be used by all algorithms.
  typedef typename ThreeSpace::Vector Vector;
  
  // The matrix type that will be used by all algorithms.
  typedef typename ThreeSpace::Matrix Matrix;

  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  
  // Typedef for LAPACK wrappers
  typedef Teuchos::LAPACK<ordinalType,ScalarType> LapackWrapper;

public:

  //! Normalize a vector.
  static inline void normalizeVector( Vector &vector );

  //! Compute the cosine of the angle between two vectors
  static ScalarType computeCosineAngleBetweenVectors( const Vector &a,
						      const Vector &b );

  //! Test if a vector is parallel to another vector
  static bool isParallel( const Vector &a,
			  const Vector &b );

  //! Test if a vector is antiparallel to another vector
  static bool isAntiparallel( const Vector &a,
			      const Vector &b );

  //! Test if a matrix is symmetric
  static bool isSymmetric( const Matrix &matrix );

  //! Test if a matrix is orthonormal
  static bool isOrthonormal( const Matrix &matrix );

  //! Test if a matrix is nonsingular
  static bool isNonsingular( const Matrix &matrix );

  //! Swap columns of a matrix
  static void swapColumns( Matrix &matrix, 
			   ordinalType column_a_index,
			   ordinalType column_b_index );

  //! Create a vector that satisfies the relationship n*x0+const = 0 => ret. x0
  static Vector createZeroingVector( const Vector &vector,
				     const ScalarType constant_term );

  //! Create a rotation matrix for rotation about the x-axis.
  static Matrix 
  createXAxisRotationMatrix( const ScalarType rotation_angle );

  //! Create a rotation matrix for rotation about the y-axis.
  static Matrix
  createYAxisRotationMatrix( const ScalarType rotation_angle );

  //! Create a rotation matrix for rotation about the z-axis.
  static Matrix
  createZAxisRotationMatrix( const ScalarType rotation_angle );

  //! Create a rotation matrix that will rotate one unit vector to another.
  /*! \details When rotating surfaces initial_direction = desired_direction
   * and final_direction = surface_normal.
   */
  static Matrix
  createRotationMatrixFromUnitVectors( const Vector &initial_direction,
				       const Vector &final_direction );

  //! Compute the inverse of a general 3x3 matrix.
  static Matrix computeMatrixInverse( const Matrix &matrix );

  //! Solve a system of equations (Ax = b)
  static Vector solveSystem( const Matrix &A,
			     const Vector &b);

  //! Compute the eigenvalues and eigenvectors of a symmetric 3x3 matrix.
  static Vector
  computeEigenvaluesAndEigenvectors( 
		const Matrix &matrix,
		Matrix &eigenvectors,
		const EigenvectorComp eigenvector_comp = COMPUTE_EIGENVECTORS);

  //! Compute the eigenvalues of a symmetric 3x3 matrix
  static Vector computeEigenvalues( const Matrix &matrix );

  //! Check if the eigenvectors can be realigned
  static bool isRealignable( const Vector &eigenvalues );

  //! Align eigenvectors with desired axis
  static void realignEigenvectors( Vector &eigenvalues,
				   Matrix &eigenvectors,
				   const Axis alignment_axis = Z_AXIS );
};

} // end FACEMC namespace

#endif // end LINEAR_ALGEBRA_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end LinearAlgebraPolicyDecl.hpp
//---------------------------------------------------------------------------//

					
