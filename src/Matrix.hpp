//---------------------------------------------------------------------------//
//!
//! \file   Matrix.hpp
//! \author Alex Robinson
//! \brief  Matrix class (in three space) declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MATRIX_HPP
#define MATRIX_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "PrintableObject.hpp"
#include "ThreeSpaceObject.hpp"

namespace FACEMC{

/*! A 3x3 matrix
 *
 * Guaranteed to never be empty and always contain 9 elements organized as a
 * 3x3 matrix (column ordering).
 */
template<typename ScalarType>
class Matrix : public PrintableObject, public ThreeSpaceObject
{

public:

  //!@{
  //! Typedefs
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //! Typedef for ordinal type
  typedef int ordinalType;
  //@}

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<ScalarType> ST;

public:

  //@{
  //! Constructor/Destructor methods.
  //! Default constructor
  Matrix();

  //! General constructor
  Matrix( const ScalarType a00, const ScalarType a01, const ScalarType a02,
	  const ScalarType a10, const ScalarType a11, const ScalarType a12,
	  const ScalarType a20, const ScalarType a21, const ScalarType a22 );

  //! Symmetric constructor
  Matrix( const ScalarType a00, const ScalarType a01, const ScalarType a02,
	                        const ScalarType a11, const ScalarType a12, 
	                                              const ScalarType a22 );

  //! Copy constructor
  Matrix( const Matrix<ScalarType> &source_matrix );

  //! Destructor
  virtual ~Matrix()
  { /* ... */ }
  //@}

  //@{
  //! Set methods
  //! Copies values from one matrix to another.
  Matrix<ScalarType>& 
  operator=( const Matrix<ScalarType> &source_matrix );

  //! Set the matrix as a zero matrix
  void zero();

  //! Set the matrix as an identity matrix
  void identity();
  //@}

  //@{
  //! Accessor methods.
  //! Element access method (non-const).
  ScalarType& operator()( const ordinalType rowIndex, 
			  const ordinalType colIndex );

  //! Element access method (const).
  const ScalarType& operator()( const ordinalType rowIndex,
				const ordinalType colIndex ) const;

  //! Column access method (non-const).
  ScalarType* operator[]( const ordinalType colIndex );

  //! Column access method (const).
  const ScalarType* operator[]( const ordinalType colIndex ) const;

  //! Return a raw pointer to beginning of the data array (non-const).
  ScalarType* getRawPtr();

  //! Return a raw pointer to beginning of the data array (const).
  const ScalarType* getRawPtr() const;
  //@}

  //@{
  //! Views and conversion methods
  //! Return a const view of the data array
  Teuchos::ArrayView<const ScalarType> view() const;

  //! Returns a const view of the data array
  Teuchos::ArrayView<const ScalarType> operator()() const;
  //@}

  //@{
  //! Mathematical methods
  //! Add another matrix to <em> this </em> matrix.
  Matrix<ScalarType>& operator+=( const Matrix<ScalarType> &source_matrix );

  //! Subtract another matrix from <em> this </em> matrix.
  Matrix<ScalarType>& operator-=( const Matrix<ScalarType> &source_matrix );

  //! Scale <em> this </em> matrix by alpha.
  Matrix<ScalarType>& operator*=( const ScalarType alpha );
  
  //! Multiply alpha*A*B and add them to beta*<em>this</em>.
  void multiply( const ScalarType alpha,
		 const Matrix<ScalarType> &A,
		 const bool transpose_A,
		 const Matrix<ScalarType> &B,
		 const bool transpose_B,
		 const ScalarType beta );

  //! Swap columns of <em> this </em> matrix
  void swapColumns( const ordinalType column_a_index,
		    const ordinalType column_b_index );
  //@}

  //@{ 
  //! Comparison methods
  //! Equality of two matrices.
  bool operator==( const Matrix<ScalarType> &operand ) const;

  //! Inequality of two matrices.
  bool operator!=( const Matrix<ScalarType> &operand ) const;
  //@}

  //@{
  //! Attribute methods
  //! Returns the row dimension of <em> this </em> matrix
  ordinalType numRows() const;
  
  //! Returns the column dimension of <em> this </em> matrix
  ordinalType numCols() const;

  //! Returns if <em> this </em> matrix is a zero matrix
  bool isZeroMatrix() const;

  //! Returns if <em> this </em> matrix is an identity matrix
  bool isIdentityMatrix() const;

  //! Returns if <em> this </em> matrix is symmetric
  bool isSymmetric() const;

  //! Returns if <em> this </em> matrix is orthonormal
  bool isOrthonormal() const;

  //! Returns if <em> this </em> matrix is nonsingular
  bool isNonsingular() const;
  //@}

  //@{
  //! Norm methods
  //! Returns the 1-norm of <em> this </em> matrix.
  ScalarType normOne() const;

  //! Returns the Infinity-norm of <em> this </em> matrix.
  ScalarType normInf() const;

  //! Returns the Frobenius-norm of <em> this </em> matrix.
  ScalarType normFrobenius() const;
  //@}

  //@{
  //! I/O methods
  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;
  //@}  
  
private:

  Teuchos::SerialDenseMatrix<int,ScalarType> d_data;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Matrix_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MATRIX_HPP

//---------------------------------------------------------------------------//
// end Matrix.hpp
//---------------------------------------------------------------------------//
