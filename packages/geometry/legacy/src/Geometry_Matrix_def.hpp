//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Matrix_def.hpp
//! \author Alex Robinson
//! \brief  Matrix class (in N<4 space) definition.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MATRIX_DEF_HPP
#define GEOMETRY_MATRIX_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Default constructor
template<typename ScalarType, int N>
Matrix<ScalarType,N>::Matrix()
  : ThreeSpaceObject( THREE_SPACE_MATRIX ),
    SerialDenseMatrixExtension<ScalarType>( N )
{
  testStaticPrecondition( N == 3 );
}

// General constructor
template<typename ScalarType, int N>
Matrix<ScalarType,N>::Matrix(
	     const ScalarType a00, const ScalarType a01, const ScalarType a02,
	     const ScalarType a10, const ScalarType a11, const ScalarType a12,
	     const ScalarType a20, const ScalarType a21, const ScalarType a22 )
  : ThreeSpaceObject( THREE_SPACE_MATRIX ),
    SerialDenseMatrixExtension<ScalarType>( N )
{
  testStaticPrecondition( N == 3 );

  this->operator()( 0, 0 ) = a00;
  this->operator()( 0, 1 ) = a01;
  this->operator()( 0, 2 ) = a02;
  this->operator()( 1, 0 ) = a10;
  this->operator()( 1, 1 ) = a11;
  this->operator()( 1, 2 ) = a12;
  this->operator()( 2, 0 ) = a20;
  this->operator()( 2, 1 ) = a21;
  this->operator()( 2, 2 ) = a22;
}

// Symmetric constructor
template<typename ScalarType, int N>
Matrix<ScalarType,N>::Matrix(
	     const ScalarType a00,
	     const ScalarType a10, const ScalarType a11,
	     const ScalarType a20, const ScalarType a21, const ScalarType a22 )
  : ThreeSpaceObject( THREE_SPACE_MATRIX ),
    SerialDenseMatrixExtension<ScalarType>( N )
{
  testStaticPrecondition( N == 3 );

  this->operator()( 0, 0 ) = a00;
  this->operator()( 0, 1 ) = a10;
  this->operator()( 0, 2 ) = a20;
  this->operator()( 1, 0 ) = a10;
  this->operator()( 1, 1 ) = a11;
  this->operator()( 1, 2 ) = a21;
  this->operator()( 2, 0 ) = a20;
  this->operator()( 2, 1 ) = a21;
  this->operator()( 2, 2 ) = a22;
}

// Copy constructor
template<typename ScalarType,int N>
Matrix<ScalarType,N>::Matrix( const Matrix<ScalarType,N> &source_matrix )
  : ThreeSpaceObject( THREE_SPACE_MATRIX ),
    SerialDenseMatrixExtension<ScalarType>( N )
{
  this->operator()( 0, 0 ) = source_matrix( 0, 0 );
  this->operator()( 0, 1 ) = source_matrix( 0, 1 );
  this->operator()( 0, 2 ) = source_matrix( 0, 2 );
  this->operator()( 1, 0 ) = source_matrix( 1, 0 );
  this->operator()( 1, 1 ) = source_matrix( 1, 1 );
  this->operator()( 1, 2 ) = source_matrix( 1, 2 );
  this->operator()( 2, 0 ) = source_matrix( 2, 0 );
  this->operator()( 2, 1 ) = source_matrix( 2, 1 );
  this->operator()( 2, 2 ) = source_matrix( 2, 2 );
}

// Copies values from one matrix to another
template<typename ScalarType, int N>
Matrix<ScalarType,N>& Matrix<ScalarType,N>::operator=(
			            const Matrix<ScalarType,N> &source_matrix )
{
  // Test if the source matrix is the same as the target
  if( this != &source_matrix )
  {
    this->operator()( 0, 0 ) = source_matrix( 0, 0 );
    this->operator()( 0, 1 ) = source_matrix( 0, 1 );
    this->operator()( 0, 2 ) = source_matrix( 0, 2 );
    this->operator()( 1, 0 ) = source_matrix( 1, 0 );
    this->operator()( 1, 1 ) = source_matrix( 1, 1 );
    this->operator()( 1, 2 ) = source_matrix( 1, 2 );
    this->operator()( 2, 0 ) = source_matrix( 2, 0 );
    this->operator()( 2, 1 ) = source_matrix( 2, 1 );
    this->operator()( 2, 2 ) = source_matrix( 2, 2 );
  }

  return *this;
}

// Print method that defines the behavior of the std::stream << operator
template<typename ScalarType, int N>
void Matrix<ScalarType,N>::print( std::ostream &os ) const
{
  SerialDenseMatrixExtension<ScalarType>::print( os );
}

} // end Geometry namespace

#endif // end GEOMETRY_MATRIX_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_Matrix_def.hpp
//---------------------------------------------------------------------------//
