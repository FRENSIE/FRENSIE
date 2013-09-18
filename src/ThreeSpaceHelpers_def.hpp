//---------------------------------------------------------------------------//
//!
//! \file   ThreeSpaceHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Helper function definitions for operations in \f$ R^3 \f$.
//!
//---------------------------------------------------------------------------//

#ifndef THREE_SPACE_HELPERS_DEF_HPP
#define THREE_SPACE_HELPERS_DEF_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

namespace FACEMC{

// Create a vector in \f$ R^3 \f$.
template<typename ScalarType>
Teuchos::SerialDenseVector<char,ScalarType> 
createThreeSpaceVector( ScalarType x,
			ScalarType y,
			ScalarType z )
{
  Teuchos::SerialDenseVector<char,ScalarType> vector( 3 );
  
  vector[0] = x;
  vector[1] = y;
  vector[2] = z;

  return vector;
}

//! Create a 3x3 matrix (for use in \f$ R^3 \f$).
template<typename ScalarType>
Teuchos::SerialDenseMatrix<char,ScalarType> 
createThreeByThreeMatrix( ScalarType a00, ScalarType a01, ScalarType a02,
			  ScalarType a10, ScalarType a11, ScalarType a12,
			  ScalarType a20, ScalarType a21, ScalarType a22 )
{
  Teuchos::SerialDenseMatrix<char,ScalarType> matrix( 3, 3 );

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

} // end FACEMC namespace

#endif // end THREE_SPACE_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end ThreeSpaceHelpers.hpp
//---------------------------------------------------------------------------//
