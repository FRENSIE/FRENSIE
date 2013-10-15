//---------------------------------------------------------------------------//
//!
//! \file   Matrix_def.hpp
//! \author Alex Robinson
//! \brief  Matrix class (in three space) definition.
//! 
//---------------------------------------------------------------------------//

#ifndef MATRIX_DEF_HPP
#define MATRIX_DEF_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseHelpers.hpp>
#include <Teuchos_LAPACK.hpp>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Default constructor
template<typename ScalarType>
Matrix<ScalarType>::Matrix()
  : PrintableObject( "ThreeSpaceMatrix" ),
    ThreeSpaceObject( THREE_SPACE_MATRIX ),
    d_data( 3, 3 )
{ /* ... */ }

// General constructor
template<typename ScalarType>
Matrix<ScalarType>::Matrix( 
	     const ScalarType a00, const ScalarType a01, const ScalarType a02,
	     const ScalarType a10, const ScalarType a11, const ScalarType a12,
	     const ScalarType a20, const ScalarType a21, const ScalarType a22 )
  : PrintableObject( "ThreeSpaceMatrix" ),
    ThreeSpaceObject( THREE_SPACE_MATRIX ),
    d_data( 3, 3 )
{
  d_data( 0, 0 ) = a00;
  d_data( 0, 1 ) = a01;
  d_data( 0, 2 ) = a02;
  d_data( 1, 0 ) = a10;
  d_data( 1, 1 ) = a11;
  d_data( 1, 2 ) = a12;
  d_data( 2, 0 ) = a20;
  d_data( 2, 1 ) = a21;
  d_data( 2, 2 ) = a22;
}

// Symmetric constructor
template<typename ScalarType>
Matrix<ScalarType>::Matrix(
	     const ScalarType a00, 
	     const ScalarType a10, const ScalarType a11,
	     const ScalarType a20, const ScalarType a21, const ScalarType a22 )
  : PrintableObject( "ThreeSpaceMatrix" ),
    ThreeSpaceObject( THREE_SPACE_MATRIX ),
    d_data( 3, 3 )
{
  d_data( 0, 0 ) = a00;
  d_data( 0, 1 ) = a10;
  d_data( 0, 2 ) = a20;
  d_data( 1, 0 ) = a10;
  d_data( 1, 1 ) = a11;
  d_data( 1, 2 ) = a21;
  d_data( 2, 0 ) = a20;
  d_data( 2, 1 ) = a21;
  d_data( 2, 2 ) = a22;
}

// Copy constructor
template<typename ScalarType>
Matrix<ScalarType>::Matrix( const Matrix<ScalarType> &source_matrix )
  : PrintableObject( "ThreeSpaceMatrix" ),
    ThreeSpaceObject( THREE_SPACE_MATRIX ),
    d_data( source_matrix.d_data )
{ /* ... */ }

// Copies values from one matrix to another
template<typename ScalarType>
Matrix<ScalarType>& Matrix<ScalarType>::operator=(
			              const Matrix<ScalarType> &source_matrix )
{
  // Test if the source matrix is the same as the target
  if( this != &source_matrix )
    d_data = source_matrix.d_data;

  return *this;
}

// Set the matrix as a zero matrix
template<typename ScalarType>
void Matrix<ScalarType>::zero()
{
  d_data( 0, 0 ) = ST::zero();
  d_data( 0, 1 ) = ST::zero();
  d_data( 0, 2 ) = ST::zero();
  d_data( 1, 0 ) = ST::zero();
  d_data( 1, 1 ) = ST::zero();
  d_data( 1, 2 ) = ST::zero();
  d_data( 2, 0 ) = ST::zero();
  d_data( 2, 1 ) = ST::zero();
  d_data( 2, 2 ) = ST::zero();
}

// Set the matrix as an identity matrix
template<typename ScalarType>
void Matrix<ScalarType>::identity()
{
  d_data( 0, 0 ) = ST::one();
  d_data( 0, 1 ) = ST::zero();
  d_data( 0, 2 ) = ST::zero();
  d_data( 1, 0 ) = ST::zero();
  d_data( 1, 1 ) = ST::one();
  d_data( 1, 2 ) = ST::zero();
  d_data( 2, 0 ) = ST::zero();
  d_data( 2, 1 ) = ST::zero();
  d_data( 2, 2 ) = ST::one();
}

// Element access method (non-const).
template<typename ScalarType>
ScalarType& Matrix<ScalarType>::operator()( const ordinalType rowIndex,
					    const ordinalType colIndex )
{
  // Make sure that the row and column indices are valid
  testPrecondition( rowIndex >= 0 && rowIndex < 3 );
  testPrecondition( colIndex >= 0 && colIndex < 3 );
  
  return d_data( rowIndex, colIndex );
}

// Element access method (const).
template<typename ScalarType>
const ScalarType& Matrix<ScalarType>::operator()(
					     const ordinalType rowIndex,
					     const ordinalType colIndex ) const
{
  // Make sure that the row and column indices are valid
  testPrecondition( rowIndex >= 0 && rowIndex < 3 );
  testPrecondition( colIndex >= 0 && colIndex < 3 );

  return d_data( rowIndex, colIndex );
}

// Column access method (non-const).
template<typename ScalarType>
ScalarType* Matrix<ScalarType>::operator[]( const ordinalType colIndex )
{
  // Make sure that the column index is valid
  testPrecondition( colIndex >= 0 && colIndex < 3 );

  return d_data[colIndex];
}

// Column access method (const).
template<typename ScalarType>
const ScalarType* Matrix<ScalarType>::operator[]( 
					     const ordinalType colIndex ) const
{
  // Make sure that the column index is valid
  testPrecondition( colIndex >= 0 && colIndex < 3 );
  
  return d_data[colIndex];
}

// Return a raw pointer to beginning of the data array (non-const)
template<typename ScalarType>
ScalarType* Matrix<ScalarType>::getRawPtr()
{
  return d_data.values();
}

// Return a raw pointer to beginning of the data array (const)
template<typename ScalarType>
const ScalarType* Matrix<ScalarType>::getRawPtr() const
{
  return d_data.values();
}

// Return a const view of the data array
template<typename ScalarType>
Teuchos::ArrayView<const ScalarType> Matrix<ScalarType>::view() const
{
  return Teuchos::ArrayView<const ScalarType>( d_data.values(), 9 );
}

// Return a const view of the data array
template<typename ScalarType>
Teuchos::ArrayView<const ScalarType> Matrix<ScalarType>::operator()() const
{
  return view();
}

// Add another matrix to this matrix
template<typename ScalarType>
Matrix<ScalarType>& Matrix<ScalarType>::operator+=(
				      const Matrix<ScalarType> &source_matrix )
{
  d_data += source_matrix.d_data;

  return *this;
}

// Subtract another matrix from this matrix
template<typename ScalarType>
Matrix<ScalarType>& Matrix<ScalarType>::operator-=(
				      const Matrix<ScalarType> &source_matrix )
{ 
  d_data -= source_matrix.d_data;

  return *this;
}

// Multiply this matrix by alpha
template<typename ScalarType>
Matrix<ScalarType>& Matrix<ScalarType>::operator*=( const ScalarType alpha )
{
  d_data *= alpha;

  return *this;
}

// Multiply alpha*A*B and add them to beta*<em>this</em>
template<typename ScalarType>
void Matrix<ScalarType>::multiply( const ScalarType alpha,
				   const Matrix<ScalarType> &A,
				   const bool transpose_A,
				   const Matrix<ScalarType> &B,
				   const bool transpose_B,
				   const ScalarType beta )
{
  remember( int multiply_success = )
    d_data.multiply( transpose_A ? Teuchos::TRANS : Teuchos::NO_TRANS,
		     transpose_B ? Teuchos::TRANS : Teuchos::NO_TRANS,
		     alpha,
		     A.d_data,
		     B.d_data,
		     beta );

  // Make sure that the multiplication was successful
  testPostcondition( multiply_success == 0 );
}

//! Swap columns of this matrix
template<typename ScalarType>
void Matrix<ScalarType>::swapColumns( const ordinalType column_a_index,
				      const ordinalType column_b_index )
{
  Teuchos::SerialDenseVector<typename Matrix<ScalarType>::ordinalType,
			     ScalarType> 
  column_a = Teuchos::getCol( Teuchos::Copy, d_data, column_a_index );

  Teuchos::SerialDenseVector<typename Matrix<ScalarType>::ordinalType,
			     ScalarType>
  column_b = Teuchos::getCol( Teuchos::Copy, d_data, column_b_index );

  bool swap_a_success = Teuchos::setCol( column_a, column_b_index, d_data );
  bool swap_b_success = Teuchos::setCol( column_b, column_a_index, d_data );

  // Make sure that all set operations were successful
  testPostcondition( swap_a_success && swap_b_success );
}

// Equality of two matrices
template<typename ScalarType>
bool Matrix<ScalarType>::operator==( const Matrix<ScalarType> &operand ) const
{
  return d_data == operand.d_data;
}

// Inequality of two matrices
template<typename ScalarType>
bool Matrix<ScalarType>::operator!=( const Matrix<ScalarType> &operand ) const
{
  return d_data != operand.d_data;
}

// Returns the row dimension of this matrix
template<typename ScalarType>
typename Matrix<ScalarType>::ordinalType Matrix<ScalarType>::numRows() const
{
  return d_data.numRows();
}

// Returns the column dimension of this matrix
template<typename ScalarType>
typename Matrix<ScalarType>::ordinalType Matrix<ScalarType>::numCols() const
{
  return d_data.numCols();
}

// Return if this matrix is a zero matrix
template<typename ScalarType>
bool Matrix<ScalarType>::isZeroMatrix() const
{
  return normOne() == ST::zero();
}

// Return if this matrix is an identity matrix
template<typename ScalarType>
bool Matrix<ScalarType>::isIdentityMatrix() const
{
  return ( d_data( 0, 0 ) == ST::one() &&
	   d_data( 0, 1 ) == ST::zero() &&
	   d_data( 0, 2 ) == ST::zero() &&
	   d_data( 1, 0 ) == ST::zero() &&
	   d_data( 1, 1 ) == ST::one() &&
	   d_data( 1, 2 ) == ST::zero() &&
	   d_data( 2, 0 ) == ST::zero() &&
	   d_data( 2, 1 ) == ST::zero() &&
	   d_data( 2, 2 ) == ST::one() );
}

// Return if this matrix is symmetric
template<typename ScalarType>
bool Matrix<ScalarType>::isSymmetric() const
{
  return ( d_data( 0, 1 ) == d_data( 1, 0 ) &&
	   d_data( 0, 2 ) == d_data( 2, 0 ) &&
	   d_data( 1, 2 ) == d_data( 2, 1 ) );
}

// Return if this matrix is orthonormal
template<typename ScalarType>
bool Matrix<ScalarType>::isOrthonormal() const
{
  typedef typename Matrix<ScalarType>::ordinalType ordinalType;
  
  Teuchos::SerialDenseMatrix<ordinalType,ScalarType> 
    column_1_matrix( Teuchos::View, d_data, 3, 1, 0, 0 );
  Teuchos::SerialDenseVector<ordinalType,ScalarType>
    column_1( Teuchos::View, column_1_matrix.values(), 3 );

  Teuchos::SerialDenseMatrix<ordinalType,ScalarType>
    column_2_matrix( Teuchos::View, d_data, 3, 1, 0, 1 );
  Teuchos::SerialDenseVector<ordinalType,ScalarType>
    column_2( Teuchos::View, column_2_matrix.values(), 3 );
    
  Teuchos::SerialDenseMatrix<ordinalType,ScalarType>
    column_3_matrix( Teuchos::View, d_data, 3, 1, 0, 2 );
  Teuchos::SerialDenseVector<ordinalType,ScalarType>
    column_3( Teuchos::View, column_3_matrix.values(), 3 );

  ScalarType column_1_magnitude = column_1.normFrobenius();
  ScalarType column_2_magnitude = column_2.normFrobenius();
  ScalarType column_3_magnitude = column_3.normFrobenius();

  bool normal_columns = 
    ( ST::magnitude( column_1_magnitude - ST::one() ) < ST::prec() &&
      ST::magnitude( column_2_magnitude - ST::one() ) < ST::prec() &&
      ST::magnitude( column_3_magnitude - ST::one() ) < ST::prec() );

  bool orthogonal_columns = 
    ( ST::magnitude( column_1.dot( column_2 ) ) < ST::prec() &&
      ST::magnitude( column_1.dot( column_3 ) ) < ST::prec() &&
      ST::magnitude( column_2.dot( column_3 ) ) < ST::prec() );

  return normal_columns && orthogonal_columns;
}

// Returns if this matrix is nonsingular
template<typename ScalarType>
bool Matrix<ScalarType>::isNonsingular() const
{
  // The matrix will be modified by the test (make a copy)
  Teuchos::SerialDenseMatrix<ordinalType,ScalarType> data_copy( d_data );

  // LAPACK wrapper
  Teuchos::LAPACK<ordinalType,ScalarType> lapack;

  // Pivot indices
  ordinalType ipiv[3];

  // Computation info
  ordinalType success;

  // If the LU factorization can be completed the matrix is nonsingular
  lapack.GETRF( 3, 3, data_copy.values(), 3, ipiv, &success );

  if( success == 0 )
    return true;
  else
    return false;
}


// Return the 1-norm of this matrix
template<typename ScalarType>
ScalarType Matrix<ScalarType>::normOne() const
{
  return d_data.normOne();
}

// Return the Infinity-norm of this matrix
template<typename ScalarType>
ScalarType Matrix<ScalarType>::normInf() const
{
  return d_data.normInf();
}

// Return the Frobenius-norm of this matrix
template<typename ScalarType>
ScalarType Matrix<ScalarType>::normFrobenius() const
{
  return d_data.normFrobenius();
}

// Print method that defines the behavior of the std::stream << operator
template<typename ScalarType>
void Matrix<ScalarType>::print( std::ostream &os ) const
{
  d_data.print( os );
}

} // end FACEMC namespace

#endif // end MATRIX_DEF_HPP

//---------------------------------------------------------------------------//
// end Matrix_def.hpp
//---------------------------------------------------------------------------//
