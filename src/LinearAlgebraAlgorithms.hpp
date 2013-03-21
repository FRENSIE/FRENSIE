//---------------------------------------------------------------------------//
// \file   LinearAlgebraAlgorithms.hpp
// \author Alex Robinson
// \brief  Function declarations for linear algebra algorithms.
//---------------------------------------------------------------------------//

#ifndef LINEAR_ALGEBRA_ALGORITHMS_HPP
#define LINEAR_ALGEBRA_ALGORITHMS_HPP

// Trilinos Includes
#include <Teuchos_Tuple.hpp>

namespace FACEMC{

namespace LinearAlgebra{

//! Compute the magnitude of a vector
double vectorMagnitude( const Teuchos::Tuple<double,3> &vector );

//! Normalize a vector
void normalizeVector( Teuchos::Tuple<double,3> &vector );

//! Compute the determinant of a 3x3 matrix
double matrixDeterminant( const Teuchos::Tuple<double,9> &matrix );

//! Compute the transpose of a matrix
Teuchos::Tuple<double,9>
matrixTranspose( const Teuchos::Tuple<double,9> &matrix );

//! Compute the inverse of a 3x3 matrix
Teuchos::Tuple<double,9> 
matrixInverse( const Teuchos::Tuple<double,9> &matrix );

//! Solve a 3x3 linear system
Teuchos::Tuple<double,3> 
solveSystem( const Teuchos::Tuple<double,9> &matrix,
	     const Teuchos::Tuple<double,3> &solution );

//! Compute the eigenvalues of a 3x3 matrix
//Teuchos::Tuple<double,3>
//eigenvalues( const Teuchos::Tuple<double,9> &matrix );

//! Compute the eigenvectors of a 3x3 matrix
//Teuchos::Tuple<double,9>
//eigenvectors( const Teuchos::Tuple<double,9> &matrix );

} // end LinearAlgebra namespace 

} // end FACEMC namespace

//! Define the product of a scalar and a vector (premultiply)
Teuchos::Tuple<double,3> operator*( const double multiplier,
				    const Teuchos::Tuple<double,3> &vector );

//! Define the product of a scalar and a vector (postmultiply)
Teuchos::Tuple<double,3> operator*( const Teuchos::Tuple<double,3> &vector,
				    const double multiplier );

//! Define the product of a scalara and a vector (in place)
Teuchos::Tuple<double,3> operator*=( Teuchos::Tuple<double,3> &vector,
				     const double multiplier );

//! Define the product of a scalar and a matrix (premultiply)
Teuchos::Tuple<double,9> operator*( const double multiplier,
				    const Teuchos::Tuple<double,9> &matrix );

//! Define the product of a scalar and a matrix (postmultiply)
Teuchos::Tuple<double,9> operator*( const Teuchos::Tuple<double,9> &matrix,
				    const double multiplier );

//! Define the product of a scalar and a matrix (in place)
Teuchos::Tuple<double,9> operator*=( Teuchos::Tuple<double,9> &matrix,
				     const double multiplier );

//! Define the dot product of a 1x3 row vector and a 3x1 column vector
double operator*( const Teuchos::Tuple<double,3> &left_vector,
		  const Teuchos::Tuple<double,3> &right_vector );

//! Define the product of a 1x3 row vector and a 3x3 matrix
Teuchos::Tuple<double,3> operator*( const Teuchos::Tuple<double,3> &vector,
				    const Teuchos::Tuple<double,9> &matrix );

//! Define the product of a 3x3 matrix and a 3x1 column vector
Teuchos::Tuple<double,3> operator*( const Teuchos::Tuple<double,9> &matrix,
				    const Teuchos::Tuple<double,3> &vector );

//! Define the product of two 3x3 matrices
Teuchos::Tuple<double,9> operator*( const Teuchos::Tuple<double,9> &left_matrix,
				    const Teuchos::Tuple<double,9> &right_matrix );

#endif // end LINEAR_ALGEBRA_ALGORITHMS

//---------------------------------------------------------------------------//
// end LinearAlgebraAlgorithms.hpp
//---------------------------------------------------------------------------//

					
