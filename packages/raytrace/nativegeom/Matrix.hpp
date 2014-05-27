//---------------------------------------------------------------------------//
//!
//! \file   Matrix.hpp
//! \author Alex Robinson
//! \brief  Matrix class (in N<4 space) declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MATRIX_HPP
#define MATRIX_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "SerialDenseMatrixExtension.hpp"
#include "TwoSpaceObject.hpp"
#include "ThreeSpaceObject.hpp"
#include "FourSpaceObject.hpp"

namespace FACEMC{

/*! A 3x3 matrix
 *
 * Guaranteed to never be empty and always contain 9 elements organized as a
 * 3x3 matrix (column ordering).
 */
template<typename ScalarType, int N = 3>
class Matrix : public ThreeSpaceObject, public SerialDenseMatrixExtension<ScalarType>
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
  Matrix( const ScalarType a00,
  	  const ScalarType a10, const ScalarType a11,
  	  const ScalarType a20, const ScalarType a21, const ScalarType a22 );

  //! Copy constructor
  Matrix( const Matrix<ScalarType,N> &source_matrix );

  //! Destructor
  virtual ~Matrix()
  { /* ... */ }
  //@}

  //@{
  //! Set methods
  //! Copies values from one matrix to another.
  Matrix<ScalarType,N>& 
  operator=( const Matrix<ScalarType,N> &source_matrix );

  //@{
  //! I/O methods
  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;
  //@}  
};

/*! A 4x4 matrix
 *
 * Guaranteed to never be empty and always contain 16 elements organized as a
 * 4x4 matrix (column ordering).
 */
template<typename ScalarType>
class Matrix<ScalarType,4> : public FourSpaceObject, public SerialDenseMatrixExtension<ScalarType>
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
  Matrix( const ScalarType a00, 
	  const ScalarType a01, 
	  const ScalarType a02,
	  const ScalarType a03,
  	  const ScalarType a10, 
	  const ScalarType a11, 
	  const ScalarType a12,
	  const ScalarType a13,
  	  const ScalarType a20, 
	  const ScalarType a21, 
	  const ScalarType a22,
	  const ScalarType a23 );

  //! Symmetric constructor
  Matrix( const ScalarType a00,
  	  const ScalarType a10, const ScalarType a11,
  	  const ScalarType a20, const ScalarType a21, const ScalarType a22,
	  const ScalarType a30, const ScalarType a31, const ScalarType a32, const ScalarType a33 );

  //! Copy constructor
  Matrix( const Matrix<ScalarType,4> &source_matrix );

  //! Destructor
  virtual ~Matrix()
  { /* ... */ }
  //@}

  //@{
  //! Set methods
  //! Copies values from one matrix to another.
  Matrix<ScalarType,4>& 
  operator=( const Matrix<ScalarType,4> &source_matrix );

  //@{
  //! I/O methods
  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;
  //@}  
};

/*! A 4x4 matrix
 *
 * Guaranteed to never be empty and always contain 16 elements organized as a
 * 4x4 matrix (column ordering).
 */
template<typename ScalarType>
class Matrix<ScalarType,2> : public TwoSpaceObject, public SerialDenseMatrixExtension<ScalarType>
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
  Matrix( const ScalarType a00, const ScalarType a01, 
	  const ScalarType a10, const ScalarType a11 );
	  
  //! Symmetric constructor
  Matrix( const ScalarType a00,
  	  const ScalarType a10, const ScalarType a11 );
  	  
  //! Copy constructor
  Matrix( const Matrix<ScalarType,2> &source_matrix );

  //! Destructor
  virtual ~Matrix()
  { /* ... */ }
  //@}

  //@{
  //! Set methods
  //! Copies values from one matrix to another.
  Matrix<ScalarType,2>& 
  operator=( const Matrix<ScalarType,2> &source_matrix );

  //@{
  //! I/O methods
  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;
  //@}  
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
