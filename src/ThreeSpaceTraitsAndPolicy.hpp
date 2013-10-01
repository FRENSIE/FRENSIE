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
#include <Teuchos_SerialDenseHelpers.hpp>

// FACEMC Includes
#include "ThreeSpaceTraitsAndPolicyDecl.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// The x-axis
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
ThreeSpaceTraitsAndPolicy<ScalarType>::xaxisVector( 
					        AxisVectorDirection direction )
{
  Vector xaxis( 3 );
  if( direction == POSITIVE_DIRECTION )
    xaxis[0] = ST::one();
  else
    xaxis[0] = -ST::one();

  return xaxis;
}

// The y-axis
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
ThreeSpaceTraitsAndPolicy<ScalarType>::yaxisVector( 
					        AxisVectorDirection direction )
{
  Vector yaxis( 3 );
  if( direction == POSITIVE_DIRECTION )
    yaxis[1] = ST::one();
  else
    yaxis[1] = -ST::one();

  return yaxis;
}

// The z-axis
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
ThreeSpaceTraitsAndPolicy<ScalarType>::zaxisVector( 
					        AxisVectorDirection direction )
{
  Vector zaxis( 3 );
  if( direction == POSITIVE_DIRECTION )
    zaxis[2] = ST::one();
  else
    zaxis[2] = -ST::one();  

  return zaxis;
}

// The zero matrix
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix
ThreeSpaceTraitsAndPolicy<ScalarType>::zeroMatrix()
{
  Matrix matrix( 3, 3 );
  return matrix;
}

// The identity matrix
template<typename ScalarType>
inline typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix
ThreeSpaceTraitsAndPolicy<ScalarType>::identityMatrix()
{
  Matrix matrix( 3, 3 );
  
  matrix( 0, 0 ) = ST::one();
  matrix( 1, 1 ) = ST::one();
  matrix( 2, 2 ) = ST::one();

  return matrix;
}

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

// Create a three space matrix
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix 
ThreeSpaceTraitsAndPolicy<ScalarType>::createSquareMatrixFromColumns( 
							const Vector column_1,
							const Vector column_2,
							const Vector column_3 )
{
  // Make sure the vectors are three space vectors
  testPrecondition( column_1.length() == 3 );
  testPrecondition( column_2.length() == 3 );
  testPrecondition( column_3.length() == 3 );

  Matrix matrix( 3, 3 );
  Teuchos::setCol( column_1, 0, matrix );
  Teuchos::setCol( column_2, 1, matrix );
  Teuchos::setCol( column_3, 2, matrix );

  return matrix;
}

// Create a three space matrix
template<typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Matrix 
ThreeSpaceTraitsAndPolicy<ScalarType>::createSquareMatrixFromRows( 
							const Vector row_1,
							const Vector row_2,
							const Vector row_3 )
{
  // Make sure the vectors are three space vectors
  testPrecondition( row_1.length() == 3 );
  testPrecondition( row_2.length() == 3 );
  testPrecondition( row_3.length() == 3 );

  Matrix matrix( 3, 3 );
  matrix( 0, 0 ) = row_1[0];
  matrix( 0, 1 ) = row_1[1];
  matrix( 0, 2 ) = row_1[2];
  matrix( 1, 0 ) = row_2[0];
  matrix( 1, 1 ) = row_2[1];
  matrix( 1, 2 ) = row_2[2];
  matrix( 2, 0 ) = row_3[0];
  matrix( 2, 1 ) = row_3[1];
  matrix( 2, 2 ) = row_3[2];

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

