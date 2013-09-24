//---------------------------------------------------------------------------//
//!
//! \file   ThreeSpaceTraitsAndPolicy.hpp
//! \author Alex Robinson
//! \brief  Three space traits and policy declaration.
//!
//---------------------------------------------------------------------------//

#ifndef THREE_SPACE_TRAITS_AND_POLICY_HPP
#define THREE_SPACE_TRAITS_AND_POLICY_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FACEMC Includes
#include "ThreeSpaceTraitsAndPolicyDecl.hpp"

namespace FACEMC{

// Create a three space vector
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector 
ThreeSpaceTraitsAndPolicy<ScalarType>::createVector( const ScalarType x,
						     const ScalarType y,
						     const ScalarType z )
{
  Vector vector( 3 );
  
  vector[0] = x;
  vector[1] = y;
  vector[2] = z;

  return vector;
}

// Create a three space matrix
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix 
ThreeSpaceTraitsAndPolicy<ScalarType>::createSquareMatrix( 
	     const ScalarType a00, const ScalarType a01, const ScalarType a02,
	     const ScalarType a10, const ScalarType a11, const ScalarType a12,
	     const ScalarType a20, const ScalarType a21, const ScalarType a22 )
{
  Matrix matrix( 3, 3 );

  matrix( 0, 0 ) = a00;
  matrix( 0, 1 ) = a01;
  matrix( 0, 2 ) = a02;
  matrix( 1, 0 ) = a10;
  matrix( 1, 1 ) = a11;
  matrix( 1, 2 ) = a12;
  matrix( 2, 0 ) = a20;
  matrix( 2, 1 ) = a21;
  matrix( 2, 2 ) = a22;

  return matrix;
}

// Create a symmetric three space matrix
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix 
ThreeSpaceTraitsAndPolicy<ScalarType>::createSymmetricMatrix( 
	     const ScalarType a00, const ScalarType a01, const ScalarType a02,
				   const ScalarType a11, const ScalarType a12,
						         const ScalarType a22 )
{
  Matrix symmetric_matrix( 3, 3 );
  
  symmetric_matrix( 0, 0 ) = a00;
  symmetric_matrix( 0, 1 ) = a01;
  symmetric_matrix( 0, 2 ) = a02;
  symmetric_matrix( 1, 0 ) = a01;
  symmetric_matrix( 1, 1 ) = a11;
  symmetric_matrix( 1, 2 ) = a12;
  symmetric_matrix( 2, 0 ) = a02;
  symmetric_matrix( 2, 1 ) = a12;
  symmetric_matrix( 2, 2 ) = a22;
  
  return symmetric_matrix;
}

} // end FACEMC namespace

#endif // end THREE_SPACE_TRAITS_AND_POLICY_HPP

//---------------------------------------------------------------------------//
// end ThreeSpaceTraitsAndPolicy.hpp
//---------------------------------------------------------------------------//

