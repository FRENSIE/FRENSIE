//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Vector.hpp
//! \author Alex Robinson
//! \brief  Vector class (in three space) declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_VECTOR_HPP
#define GEOMETRY_VECTOR_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_ThreeSpaceObject.hpp"
#include "Geometry_Matrix.hpp"
#include "Utility_PrintableObject.hpp"
#include "Utility_Tuple.hpp"

namespace Geometry{

/*! An array of three elements (always interpreted as a column vector)
 *
 * Guaranteed to never be empty and always contain 3 elements.
 */
template<typename ScalarType>
class Vector : public Utility::PrintableObject, public ThreeSpaceObject
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
  Vector();

  //! General constructor
  Vector( const ScalarType x,
	  const ScalarType y,
	  const ScalarType z );

  //! Tuple constructor
  explicit Vector(
		const Utility::Trip<ScalarType,ScalarType,ScalarType> &tuple );

  //! Copy constructor
  Vector( const Vector<ScalarType> &source_vector );

  //! Destructor
  virtual ~Vector()
  { /* ... */ }
  //@}

  //@{
  //! Set methods
  //! Copies values from one vector to another.
  Vector<ScalarType>&
  operator=( const Vector<ScalarType> &source_vector );
  //@}

  //@{
  //! Accessor methods.
  //! Element access method (non-const).
  ScalarType& operator[]( const ordinalType index );

  //! Element access method (const).
  const ScalarType& operator[]( const ordinalType index ) const;

  //! Return a raw pointer to the beginning of the data array (non-const).
  ScalarType* getRawPtr();

  //! Return a raw pointer to beginning of the data array (const).
  const ScalarType* getRawPtr() const;
  //@}

  //@{
  //! Views
  //! Return a const view of the data array
  Teuchos::ArrayView<const ScalarType> view() const;

  //! Return a const view of the data array
  Teuchos::ArrayView<const ScalarType> operator()() const;
  //@}

  //@{
  //! Mathematical methods
  //! Add another vector to <em> this </em> vector.
  Vector<ScalarType>& operator+=( const Vector<ScalarType> &source_vector );

  //! Subtract another vector from <em> this </em> vector.
  Vector<ScalarType>& operator-=( const Vector<ScalarType> &source_vector );

  //! Scale <em> this </em> vector by alpha.
  Vector<ScalarType>& operator*=( const scalarType alpha );

  //! Multiply <em> this </em> vector by a matrix (x => Ax ).
  Vector<ScalarType>& operator*=( const Matrix<ScalarType> &source_matrix );

  //! Multiply alpha*A*x and add them to beta*<em>this</em>.
  void multiply( const ScalarType alpha,
		 const Matrix<ScalarType> &A,
		 const bool transpose_A,
		 const Vector<ScalarType> &x,
		 const ScalarType beta );

  //! Normalize <em> this </em> vector
  void normalize();

  //! Compute the dot product of <em> this </em> vector and x
  ScalarType dot( const Vector<ScalarType> &x ) const;

  //! Returns the cosine of the angle between <em> this </em> vector and x
  ScalarType angleCosine( const Vector<ScalarType> &x ) const;

  //! Returns if <em> this </em> vector is parallel to x
  bool isParallel( const Vector<ScalarType> &x ) const;

  //! Returns if <em> this </em> vector is antiparallel to x
  bool isAntiparallel( const Vector<ScalarType> &x ) const;
  //@}

  //@{
  //! Comparison methods
  //! Equality of two vectors.
  bool operator==( const Vector<ScalarType> &operand ) const;

  //! Inequality of two vectors.
  bool operator!=( const Vector<ScalarType> &operand ) const;
  //@}

  //@{
  //! Attribute methods
  //! Returns the length of the vector
  ordinalType length() const;

  //! Returns the length of the vector
  ordinalType size() const;

  //! Returns if the vector is a zero vector
  bool isZeroVector() const;

  //! Returns if every element of the vector is unique
  bool hasUniqueElements() const;
  //@}

  //@{
  //! Norm methods
  //! Returns the 1-norm of <em> this </em> vector.
  ScalarType normOne() const;

  //! Returns the 2-norm of <em> this </em> vector.
  ScalarType normTwo() const;

  //! Retunrs the Infinity-norm of <em> this </em> vector.
  ScalarType normInf() const;
  //@}

  //@{
  //! I/O methods
  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;
  //@}

private:

  Teuchos::SerialDenseVector<ordinalType,ScalarType> d_data;
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_Vector_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_VECTOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_Vector.hpp
//---------------------------------------------------------------------------//
