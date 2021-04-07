//---------------------------------------------------------------------------//
//!
//! \file   Geometry_SerialDenseMatrixExtension.hpp
//! \author Alex Robinson
//! \brief  Matrix base class decl that extends the Teuchos serial dense matrix
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_SERIAL_DENSE_MATRIX_EXTENSION_HPP
#define GEOMETRY_SERIAL_DENSE_MATRIX_EXTENSION_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ScalarTraits.hpp>

namespace Geometry{

template<typename ScalarType>
class SerialDenseMatrixExtension :
    public Teuchos::SerialDenseMatrix<int,ScalarType>
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
  SerialDenseMatrixExtension();

  //! Shaping Constructor
  SerialDenseMatrixExtension( int order );

  //! Destructor
  virtual ~SerialDenseMatrixExtension()
  { /* ... */ }
  //@}

  //! Set the matrix as a zero matrix
  void zero();

  //! Set the matrix as an identity matrix
  void identity();
  //@}

  //@{
  //! Accessor methods.
  //! Return a raw pointer to beginning of the data array (non-const).
  ScalarType* getRawPtr();

  //! Return a raw pointer to beginning of the data array (const).
  const ScalarType* getRawPtr() const;

  //! Base methods
  using Teuchos::SerialDenseMatrix<int,ScalarType>::operator();
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
  //! Multiply alpha*A*B and add them to beta*<em>this</em>.
  void multiply( const ScalarType alpha,
		 const SerialDenseMatrixExtension<ScalarType> &A,
		 const bool transpose_A,
		 const SerialDenseMatrixExtension<ScalarType> &B,
		 const bool transpose_B,
		 const ScalarType beta );

  //! Swap columns of <em> this </em> matrix
  void swapColumns( const ordinalType column_a_index,
		    const ordinalType column_b_index );
  //@}

  //@{
  //! Attributes
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
  //! I/O methods
  //! Print method that defines the behavior of the std::stream << operator
  virtual void print( std::ostream &os ) const;
  //@}
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_SerialDenseMatrixExtension_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_SERIAL_DENSE_MATRIX_EXTENSION_HPP

//---------------------------------------------------------------------------//
// end Geometry_SerialDenseMatrixExtension.hpp
//---------------------------------------------------------------------------//
