//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Vector_def.hpp
//! \author Alex Robinson
//! \brief  Vector class (in three space) definition.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_VECTOR_DEF_HPP
#define GEOMETRY_VECTOR_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Default constructor
template<typename ScalarType>
Vector<ScalarType>::Vector()
  : PrintableObject( "ThreeSpaceVector" ),
    ThreeSpaceObject( THREE_SPACE_VECTOR ),
    d_data( 3 )
{ /* ... */ }

// General constructor
template<typename ScalarType>
Vector<ScalarType>::Vector( const ScalarType x,
			    const ScalarType y,
			    const ScalarType z )
  : Utility::PrintableObject( "ThreeSpaceVector" ),
    ThreeSpaceObject( THREE_SPACE_VECTOR ),
    d_data( 3 )
{
  d_data[0] = x;
  d_data[1] = y;
  d_data[2] = z;
}

// Tuple constructor
template<typename ScalarType>
Vector<ScalarType>::Vector(
		 const Utility::Trip<ScalarType,ScalarType,ScalarType> &tuple )
  : Utility::PrintableObject( "ThreeSpaceVector" ),
    ThreeSpaceObject( THREE_SPACE_VECTOR ),
    d_data( 3 )
{
  d_data[0] = tuple.first;
  d_data[1] = tuple.second;
  d_data[2] = tuple.third;
}

// Copy constructor
template<typename ScalarType>
Vector<ScalarType>::Vector( const Vector<ScalarType> &source_vector )
  : Utility::PrintableObject( "ThreeSpaceVector" ),
    ThreeSpaceObject( THREE_SPACE_VECTOR ),
    d_data( source_vector.d_data )
{ /* ... */ }

// Copies values from one vector to another
template<typename ScalarType>
Vector<ScalarType>& Vector<ScalarType>::operator=(
			              const Vector<ScalarType> &source_vector )
{
  // Test if the source matrix is the same as the target
  if( this != &source_vector )
    d_data = source_vector.d_data;

  return *this;
}

// Element access method (non-const)
template<typename ScalarType>
ScalarType& Vector<ScalarType>::operator[]( const ordinalType index )
{
  // Make sure that the index is valid
  testPrecondition( index >= 0 && index < 3 );

  return d_data[index];
}

// Element access method (const)
template<typename ScalarType>
const ScalarType& Vector<ScalarType>::operator[](
					        const ordinalType index ) const
{
  // Make sure that the index is valid
  testPrecondition( index >= 0 && index < 3 );

  return d_data[index];
}

// Return a raw pointer to the beginning of the data array (non-const)
template<typename ScalarType>
ScalarType* Vector<ScalarType>::getRawPtr()
{
  return d_data.values();
}

// Return a raw pointer to the beginning of the data array (const)
template<typename ScalarType>
const ScalarType* Vector<ScalarType>::getRawPtr() const
{
  return d_data.values();
}

// Return a const view of the data array
template<typename ScalarType>
Teuchos::ArrayView<const ScalarType>
Vector<ScalarType>::view() const
{
  return Teuchos::ArrayView<const ScalarType>( d_data.values(), 3 );
}

// Return a const view of the data array
template<typename ScalarType>
Teuchos::ArrayView<const ScalarType>
Vector<ScalarType>::operator()() const
{
  return view();
}

// Add another vector to this vector
template<typename ScalarType>
Vector<ScalarType>& Vector<ScalarType>::operator+=(
			              const Vector<ScalarType> &source_vector )
{
  d_data += source_vector.d_data;

  return *this;
}

// Subtract another vector from this vector
template<typename ScalarType>
Vector<ScalarType>& Vector<ScalarType>::operator-=(
		                      const Vector<ScalarType> &source_vector )
{
  d_data -= source_vector.d_data;

  return *this;
}

// Scale this vector by alpha
template<typename ScalarType>
Vector<ScalarType>& Vector<ScalarType>::operator*=( const scalarType alpha )
{
  d_data *= alpha;

  return *this;
}

// Multiply this vector by a matrix (x => Ax)
/*! \details The source_matrix should be const qualified but the
 * Teuchos::SerialDenseMatrix constructors do not allow for const Pointers
 * to be passed. The source matrix will not be modified despite its
 * qualification.
 */
template<typename ScalarType>
Vector<ScalarType>& Vector<ScalarType>::operator*=(
				      const Matrix<ScalarType> &source_matrix )
{
  // Remove the const from source_matrix so that it is compatible with
  // Teuchos::SerialDenseMatrix interface
  Matrix<ScalarType>& nonconst_source_matrix =
    const_cast<Matrix<ScalarType>& >( source_matrix );

  remember( const Matrix<ScalarType> copy_source_matrix( source_matrix ) );

  Teuchos::SerialDenseMatrix<ordinalType,ScalarType>
    matrix_data( Teuchos::View, nonconst_source_matrix.getRawPtr(), 3, 3, 3 );

  Teuchos::SerialDenseVector<ordinalType,ScalarType>
    vector_data( Teuchos::Copy, d_data.values(), 3 );

  remember( int multiply_success = )
    d_data.multiply( Teuchos::NO_TRANS,
		     Teuchos::NO_TRANS,
		     ST::one(),
		     matrix_data,
		     vector_data,
		     ST::zero() );

  // Make sure that the multiplication was successful
  testPostcondition( multiply_success == 0 );
  // Make sure that the source matrix was not modified
  testPostcondition( source_matrix == copy_source_matrix );

  return *this;
}

// Multiply alpha*A*x and add them to beta*<em>this</em>.
/*! \details The matrix A and vector x should be const qualified but the
 * Teuchos::SerialDenseMatrix constructors do not allow for const Pointers
 * to be passed. The matrix A and vector x will not be modified despite their
 * qualification.
 */
template<typename ScalarType>
void Vector<ScalarType>::multiply( const ScalarType alpha,
				   const Matrix<ScalarType> &A,
				   const bool transpose_A,
				   const Vector<ScalarType> &x,
				   const ScalarType beta )
{
  // Remove the const from source_matrix so that it is compatible with
  // Teuchos::SerialDenseMatrix interface
  Matrix<ScalarType>& nonconst_A = const_cast<Matrix<ScalarType>& >( A );
  Vector<ScalarType>& nonconst_x = const_cast<Vector<ScalarType>& >( x );

  remember( const Matrix<ScalarType> copy_A( A ) );
  remember( const Vector<ScalarType> copy_x( x ) );

  Teuchos::SerialDenseMatrix<ordinalType,ScalarType>
    A_data( Teuchos::View, nonconst_A.getRawPtr(), 3, 3, 3 );

  Teuchos::SerialDenseMatrix<ordinalType,ScalarType>
    x_data( Teuchos::View, nonconst_x.getRawPtr(), 3, 3, 1 );

  remember( int multiply_success = )
    d_data.multiply( transpose_A ? Teuchos::TRANS : Teuchos::NO_TRANS,
		     Teuchos::NO_TRANS,
		     alpha,
		     A_data,
		     x_data,
		     beta );

  // Make sure that the input matrix and vector were not modified
  testPostcondition( A == copy_A );
  testPostcondition( x == copy_x );
}

// Normalize this vector
template<typename ScalarType>
void Vector<ScalarType>::normalize()
{
  // The vector must be valid
  testPrecondition( !isZeroVector() );

  d_data.scale( 1.0/d_data.normFrobenius() );
}

// Compute the dot product of this vector and x
template<typename ScalarType>
ScalarType Vector<ScalarType>::dot( const Vector<ScalarType> &x ) const
{
  d_data.dot( x.d_data );
}

// Return the cosine of the angle between this vector and x
template<typename ScalarType>
ScalarType Vector<ScalarType>::angleCosine( const Vector<ScalarType> &x ) const
{
  // The vectors must be valid
  testPrecondition( !isZeroVector() );
  testPrecondition( !x.isZeroVector() );

  return dot( x )/(normTwo()*x.normTwo());
}

// Returns if this vector is parallel is x
template<typename ScalarType>
bool Vector<ScalarType>::isParallel( const Vector<ScalarType> &x ) const
{
  ScalarType cos_angle = angleCosine( x );

  if( ST::magnitude( cos_angle - ST::one() ) < ST::prec() )
    return true;
  else
    return false;
}

// Returns if this vector is antiparallel to x
template<typename ScalarType>
bool Vector<ScalarType>::isAntiparallel( const Vector<ScalarType> &x ) const
{
  ScalarType cos_angle = angleCosine( x );

  if( ST::magnitude( cos_angle + ST::one() ) < ST::prec() )
    return true;
  else
    return false;
}

// Equality of two vectors
template<typename ScalarType>
bool Vector<ScalarType>::operator==( const Vector<ScalarType> &operand ) const
{
  return d_data == operand.d_data;
}

// Inequality of two vectors
template<typename ScalarType>
bool Vector<ScalarType>::operator!=( const Vector<ScalarType> &operand) const
{
  return d_data != operand.d_data;
}

// Returns the length of the vector
template<typename ScalarType>
typename Vector<ScalarType>::ordinalType Vector<ScalarType>::length() const
{
  return d_data.length();
}

// Return the length of the vector
template<typename ScalarType>
typename Vector<ScalarType>::ordinalType Vector<ScalarType>::size() const
{
  return length();
}

// Returns if the vector is a zero vector
template<typename ScalarType>
bool Vector<ScalarType>::isZeroVector() const
{
  return normOne() == ST::zero();
}

// Returns if every element of the vector is unique
template<typename ScalarType>
bool Vector<ScalarType>::hasUniqueElements() const
{
  return ( d_data[0] != d_data[1] &&
	   d_data[0] != d_data[2] &&
	   d_data[1] != d_data[2] );
}

// Return the 1-norm of this vector
template<typename ScalarType>
ScalarType Vector<ScalarType>::normOne() const
{
  return d_data.normOne();
}

// Return the 2-norm of this vector
template<typename ScalarType>
ScalarType Vector<ScalarType>::normTwo() const
{
  return d_data.normFrobenius();
}

// Return the Infinity-norm of this vector
template<typename ScalarType>
ScalarType Vector<ScalarType>::normInf() const
{
  return d_data.normInf();
}

// Print method that defines the behavior of the std::stream << operator
template<typename ScalarType>
void Vector<ScalarType>::print( std::ostream &os ) const
{
  d_data.print( os );
}

} // end Geometry namespace

#endif // end GEOMETRY_THREE_SPACE_VECTOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_ThreeSpaceVector_def.hpp
//---------------------------------------------------------------------------//
