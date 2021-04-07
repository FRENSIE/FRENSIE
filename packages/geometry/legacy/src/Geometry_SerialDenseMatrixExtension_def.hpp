//---------------------------------------------------------------------------//
//!
//! \file   SerialDenseMatrixExtension_def.hpp
//! \author Alex Robinson
//! \brief  Matrix base class def. that extends the Teuchos serial dense matrix
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_SERIAL_DENSE_MATRIX_EXTENSION_DEF_HPP
#define GEOMETRY_SERIAL_DENSE_MATRIX_EXTENSION_DEF_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseHelpers.hpp>
#include <Teuchos_LAPACK.hpp>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Constructor
template<typename ScalarType>
SerialDenseMatrixExtension<ScalarType>::SerialDenseMatrixExtension()
  : Teuchos::SerialDenseMatrix<int,ScalarType>()
{ /* ... */ }

// Shaping Constructor
template<typename ScalarType>
SerialDenseMatrixExtension<ScalarType>::SerialDenseMatrixExtension( int order )
  : Teuchos::SerialDenseMatrix<int,ScalarType>( order, order )
{ /* ... */ }

// Set the matrix as a zero matrix
template<typename ScalarType>
void SerialDenseMatrixExtension<ScalarType>::zero()
{
  for( int i = 0; i < this->numCols(); ++i )
    for( int j = 0; j < this->numCols(); ++j )
      this->operator()( i, j ) = ST::zero();
}

// Set the matrix as an identity matrix
template<typename ScalarType>
void SerialDenseMatrixExtension<ScalarType>::identity()
{
  for( int i = 0; i < this->numCols(); ++i )
  {
    for( int j = 0; j < this->numCols(); ++j )
    {
      if( i == j )
	this->operator()( i, j ) = ST::one();
      else
	this->operator()( i, j ) = ST::zero();
    }
  }
}

// Return a raw pointer to beginning of the data array (non-const)
template<typename ScalarType>
ScalarType* SerialDenseMatrixExtension<ScalarType>::getRawPtr()
{
  return this->values();
}

// Return a raw pointer to beginning of the data array (const)
template<typename ScalarType>
const ScalarType* SerialDenseMatrixExtension<ScalarType>::getRawPtr() const
{
  return this->values();
}

// Return a const view of the data array
template<typename ScalarType>
Teuchos::ArrayView<const ScalarType>
SerialDenseMatrixExtension<ScalarType>::view() const
{
  return Teuchos::ArrayView<const ScalarType>(
					     this->values(),
					     this->numRows()*this->numCols() );
}

// Return a const view of the data array
template<typename ScalarType>
Teuchos::ArrayView<const ScalarType>
SerialDenseMatrixExtension<ScalarType>::operator()() const
{
  return view();
}

// Multiply alpha*A*B and add them to beta*<em>this</em>
template<typename ScalarType>
void SerialDenseMatrixExtension<ScalarType>::multiply(
			       const ScalarType alpha,
			       const SerialDenseMatrixExtension<ScalarType> &A,
			       const bool transpose_A,
			       const SerialDenseMatrixExtension<ScalarType> &B,
			       const bool transpose_B,
			       const ScalarType beta )
{
  Teuchos::SerialDenseMatrix<int,ScalarType> A_copy(
				         Teuchos::View,
				         const_cast<ScalarType*>( A.values() ),
					 A.numCols(),
					 A.numCols(),
					 A.numCols() );
  Teuchos::SerialDenseMatrix<int,ScalarType> B_copy(
					 Teuchos::View,
				         const_cast<ScalarType*>( B.values() ),
					 B.numCols(),
					 B.numCols(),
					 B.numCols() );

  remember( int multiply_success = )
    Teuchos::SerialDenseMatrix<int,ScalarType>::multiply(
			      transpose_A ? Teuchos::TRANS : Teuchos::NO_TRANS,
			      transpose_B ? Teuchos::TRANS : Teuchos::NO_TRANS,
			      alpha,
			      A_copy,
			      B_copy,
			      beta );

  // Make sure that the multiplication was successful
  testPostcondition( multiply_success == 0 );
}

// Swap columns of this matrix
template<typename ScalarType>
void SerialDenseMatrixExtension<ScalarType>::swapColumns(
					     const ordinalType column_a_index,
					     const ordinalType column_b_index )
{
  Teuchos::SerialDenseVector<typename SerialDenseMatrixExtension<ScalarType>::ordinalType,ScalarType>
  column_a = Teuchos::getCol( Teuchos::Copy, *this, column_a_index );

  Teuchos::SerialDenseVector<typename SerialDenseMatrixExtension<ScalarType>::ordinalType,ScalarType>
  column_b = Teuchos::getCol( Teuchos::Copy, *this, column_b_index );

  bool swap_a_success = Teuchos::setCol( column_a, column_b_index, *this );
  bool swap_b_success = Teuchos::setCol( column_b, column_a_index, *this );

  // Make sure that all set operations were successful
  testPostcondition( swap_a_success && swap_b_success );
}

// Return if this matrix is a zero matrix
template<typename ScalarType>
bool SerialDenseMatrixExtension<ScalarType>::isZeroMatrix() const
{
  bool test_value = true;

  for( int i = 0; i < this->numCols(); ++i )
  {
    for( int j = 0; j < this->numCols(); ++j )
    {
      test_value = test_value && (this->operator()( i, j ) == ST::zero() );
    }
  }

  return test_value;
}

// Return if this matrix is an identity matrix
template<typename ScalarType>
bool SerialDenseMatrixExtension<ScalarType>::isIdentityMatrix() const
{
  bool test_value = true;

  for( int i = 0; i < this->numCols(); ++i )
  {
    for( int j = 0; j < this->numCols(); ++j )
    {
      if( i == j )
	test_value = test_value && (this->operator()( i, j ) == ST::one());
      else
	test_value = test_value && (this->operator()( i, j ) == ST::zero());
    }
  }

  return test_value;
}

// Return if this matrix is symmetric
template<typename ScalarType>
bool SerialDenseMatrixExtension<ScalarType>::isSymmetric() const
{
  bool test_value = true;
  for( int i = 0; i < this->numCols()-1; ++i )
  {
    for( int j = i+1; j < this->numCols(); ++j )
    {
      test_value =
	test_value && (this->operator()( i, j ) == this->operator()( j, i ));
    }
  }

  return test_value;
}

// Return if this matrix is orthonormal
template<typename ScalarType>
bool SerialDenseMatrixExtension<ScalarType>::isOrthonormal() const
{
  typedef typename SerialDenseMatrixExtension<ScalarType>::ordinalType ordinalType;

  bool test_value = true;

  for( int i = 0; i < this->numCols()-1; ++i )
  {
    Teuchos::SerialDenseVector<ordinalType,ScalarType>
      column_a( Teuchos::View,
		const_cast<ScalarType*>( this->operator[](i) ),
		this->numCols() );

    for( int j = i+1; j < this->numCols(); ++j )
    {
      Teuchos::SerialDenseVector<ordinalType,ScalarType>
	column_b( Teuchos::View,
		  const_cast<ScalarType*>( this->operator[](j) ),
		  this->numCols() );

      ScalarType column_a_magnitude = column_a.normFrobenius();
      ScalarType column_b_magnitude = column_b.normFrobenius();

      bool normal_columns =
	( ST::magnitude( column_a_magnitude - ST::one() ) < ST::prec() &&
	  ST::magnitude( column_b_magnitude - ST::one() ) < ST::prec() );

      bool orthogonal_columns =
	( ST::magnitude( column_a.dot( column_b ) ) < ST::prec() );

      test_value = test_value && normal_columns && orthogonal_columns;
    }
  }

  return test_value;
}

// Returns if this matrix is nonsingular
template<typename ScalarType>
bool SerialDenseMatrixExtension<ScalarType>::isNonsingular() const
{
  // The matrix will be modified by the test (make a copy)
  Teuchos::SerialDenseMatrix<ordinalType,ScalarType>
    data_copy( Teuchos::Copy,
	       this->values(),
	       this->numCols(),
	       this->numCols(),
	       this->numCols() );

  // LAPACK wrapper
  Teuchos::LAPACK<ordinalType,ScalarType> lapack;

  // Pivot indices
  ordinalType ipiv[this->numCols()];

  // Computation info
  ordinalType success;

  // If the LU factorization can be completed the matrix is nonsingular
  lapack.GETRF( this->numCols(),
		this->numCols(),
		data_copy.values(),
		this->numCols(),
		ipiv,
		&success );

  if( success == 0 )
    return true;
  else
    return false;
}

// Print method that defines the behavior of the std::stream << operator
template<typename ScalarType>
void SerialDenseMatrixExtension<ScalarType>::print( std::ostream &os ) const
{
  Teuchos::SerialDenseMatrix<int,ScalarType>::print( os );
}

} // end Geometry namespace

#endif // end GEOMETRY_SERIAL_DENSE_MATRIX_EXTENSION_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_SerialDenseMatrixExtension_def.hpp
//---------------------------------------------------------------------------//
