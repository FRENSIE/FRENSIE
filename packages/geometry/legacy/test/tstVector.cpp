//---------------------------------------------------------------------------//
//!
//! \file   tstVector.hpp
//! \author Alex Robinson
//! \brief  Vector (column) unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_Vector.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that two vectors can be compared equal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   equality,
				   ScalarType )
{
  Geometry::Vector<ScalarType> x;
  Geometry::Vector<ScalarType> y;

  TEST_ASSERT( x == y );
}

UNIT_TEST_INSTANTIATION( Vector, equality );

//---------------------------------------------------------------------------//
// Check that two vectors can be compared unequal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   inequality,
				   ScalarType )
{
  Geometry::Vector<ScalarType> x( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> y( 0.0, 1.0, 0.0 );

  TEST_ASSERT( x != y );
}

UNIT_TEST_INSTANTIATION( Vector, inequality );

//---------------------------------------------------------------------------//
// Check that a vector can be assigned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   assignment,
				   ScalarType )
{
  Geometry::Vector<ScalarType> x( 1.0, -2.0, 3.0 );
  Geometry::Vector<ScalarType> y = x;

  TEST_EQUALITY( x, y );
}

UNIT_TEST_INSTANTIATION( Vector, assignment );

//---------------------------------------------------------------------------//
// Check that a vector can be constructed from a Trip struct
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   tuple_constructor,
				   ScalarType )
{
  Utility::Trip<ScalarType,ScalarType,ScalarType> data( 1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> data_vector( data );

  Geometry::Vector<ScalarType> ref_vector( 1.0, 1.0, 1.0 );

  TEST_EQUALITY( data_vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( Vector, tuple_constructor );

//---------------------------------------------------------------------------//
// Check that elements of the vector can be accessed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   element_access,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, 2.0, 3.0 );

  TEST_EQUALITY( vector[0], 1.0 );
  TEST_EQUALITY( vector[1], 2.0 );
  TEST_EQUALITY( vector[2], 3.0 );

  const Geometry::Vector<ScalarType> const_vector( 1.0, 2.0, 3.0 );

  TEST_EQUALITY( const_vector[0], 1.0 );
  TEST_EQUALITY( const_vector[1], 2.0 );
  TEST_EQUALITY( const_vector[2], 3.0 );
}

UNIT_TEST_INSTANTIATION( Vector, element_access );

//---------------------------------------------------------------------------//
// Check that a pointer to the head of the vector is returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   getRawPtr,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector;

  TEST_EQUALITY( vector.getRawPtr(), &vector[0] );

  const Geometry::Vector<ScalarType> const_vector;

  TEST_EQUALITY( const_vector.getRawPtr(), &const_vector[0] )
}

UNIT_TEST_INSTANTIATION( Vector, getRawPtr );

//---------------------------------------------------------------------------//
// Check that a view of the vector can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   view,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector;

  Teuchos::ArrayView<const ScalarType> view_1 = vector.view();
  Teuchos::ArrayView<const ScalarType> view_2 = vector();

  TEST_COMPARE_ARRAYS( view_1, view_2 );
  TEST_EQUALITY( view_1.size(), 3 );
  TEST_EQUALITY( view_2.size(), 3 );
}

UNIT_TEST_INSTANTIATION( Vector, view );

//---------------------------------------------------------------------------//
// Check that a vector can be added to another vector
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   compound_addition,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, 0.0, 0.0 );

  Geometry::Vector<ScalarType> second_vector( 1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> ref_vector( 2.0, 1.0, 1.0 );

  vector += second_vector;

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( Vector, compound_addition );

//---------------------------------------------------------------------------//
// Check that a vector can subtracted from another vector
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   compound_subtraction,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, 0.0, 0.0 );

  Geometry::Vector<ScalarType> second_vector( 1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> ref_vector( 0.0, -1.0, -1.0 );

  vector -= second_vector;

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( Vector, compound_subtraction );

//---------------------------------------------------------------------------//
// Check that a vector can be multiplied by a scalar
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   compound_scalar_multiplication,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, 1.0, 1.0 );

  ScalarType scalar = 5.0;

  Geometry::Vector<ScalarType> ref_vector( 5.0, 5.0, 5.0 );

  vector *= scalar;

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( Vector, compound_scalar_multiplication );

//---------------------------------------------------------------------------//
// Check that a vector can be multiplied by a matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   compound_matrix_multiplication,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, 1.0, 1.0 );

  Geometry::Matrix<ScalarType> matrix( 1.0, 1.0, 1.0,
				     1.0, 1.0, 1.0,
				     1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> ref_vector( 3.0, 3.0, 3.0 );

  vector *= matrix;

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( Vector, compound_matrix_multiplication );

//---------------------------------------------------------------------------//
// Check that alpha*A*x + beta*this can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   multiply,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector;

  Geometry::Vector<ScalarType> x( 1.0, 1.0, 1.0 );
  Geometry::Matrix<ScalarType> A( 1.0, 1.0, 1.0,
				1.0, 1.0, 1.0,
				1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> ref_vector( 3.0, 3.0, 3.0 );

  vector.multiply( 1.0, A, false, x, 0.0 );

  TEST_EQUALITY( vector, ref_vector );

  vector.multiply( 1.0, A, true, x, 1.0 );

  ref_vector *= 2;

  TEST_EQUALITY( vector, ref_vector );

  vector.multiply( 2.0, A, true, x, 0.0 );

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( Vector, multiply );

//---------------------------------------------------------------------------//
// Check that a vector can be normalized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   normalize,
				   ScalarType )
{
  Geometry::Vector<ScalarType> norm_vector( 1.0, 1.0, 1.0 );
  norm_vector.normalize();

  ScalarType c = 1.0/sqrt(3.0);
  Geometry::Vector<ScalarType> ref_norm_vector( c, c, c );

  TEST_EQUALITY( norm_vector, ref_norm_vector );
}

UNIT_TEST_INSTANTIATION( Vector, normalize );

//---------------------------------------------------------------------------//
// Check that the dot product of two vectors can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   dot,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector_a( 1.0, 2.0, 3.0 );
  Geometry::Vector<ScalarType> vector_b( 4.0, 5.0, 6.0 );

  ScalarType dot_product = vector_a.dot( vector_b );
  ScalarType ref_dot_product = 32.0;

  TEST_EQUALITY( dot_product, ref_dot_product );
}

UNIT_TEST_INSTANTIATION( Vector, dot );

//---------------------------------------------------------------------------//
// Check that the angle cosine between two vectors can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   angleCosine,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector_a( 1.0, 1.0, 1.0 );
  Geometry::Vector<ScalarType> vector_b( 1.0, -1.0, 1.0 );

  ScalarType angle_cosine = vector_a.angleCosine( vector_b );
  ScalarType ref_angle_cosine = 1.0/3;

  TEST_FLOATING_EQUALITY( angle_cosine,
			  ref_angle_cosine,
			  Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( Vector, angleCosine );

//---------------------------------------------------------------------------//
// Check that two vectors can be tested as parallel or antiparallel
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   isParallel_isAntiparallel,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, 1.0, 1.0 );
  Geometry::Vector<ScalarType> general_vector( 1.0, 2.0, 3.0 );
  Geometry::Vector<ScalarType> parallel_vector( 2.0, 2.0, 2.0 );
  Geometry::Vector<ScalarType> antiparallel_vector( -3.0, -3.0, -3.0 );

  TEST_ASSERT( !vector.isParallel( general_vector ) );
  TEST_ASSERT( !vector.isAntiparallel( general_vector ) );
  TEST_ASSERT( vector.isParallel( parallel_vector ) );
  TEST_ASSERT( !vector.isAntiparallel( parallel_vector ) );
  TEST_ASSERT( !vector.isParallel( antiparallel_vector ) );
  TEST_ASSERT( vector.isAntiparallel( antiparallel_vector ) );
}

UNIT_TEST_INSTANTIATION( Vector, isParallel_isAntiparallel );

//---------------------------------------------------------------------------//
// Check that the correct length of a vector is returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   length,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector;

  TEST_EQUALITY( vector.length(), 3 );
}

UNIT_TEST_INSTANTIATION( Vector, length );

//---------------------------------------------------------------------------//
// Check that the correct length of a vector is returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   size,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector;

  TEST_EQUALITY( vector.size(), 3 );
}

UNIT_TEST_INSTANTIATION( Vector, size );

//---------------------------------------------------------------------------//
// Check that a vector can be tested as a zero vector
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   isZeroVector,
				   ScalarType )
{
  Geometry::Vector<ScalarType> zero_vector;
  Geometry::Vector<ScalarType> vector( 1.0, 0.0, 0.0 );

  TEST_ASSERT( zero_vector.isZeroVector() );
  TEST_ASSERT( !vector.isZeroVector() );
}

UNIT_TEST_INSTANTIATION( Vector, isZeroVector );

//---------------------------------------------------------------------------//
// Check that a vector can be tested as having unique elements
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   hasUniqueElements,
				   ScalarType )
{
  Geometry::Vector<ScalarType> zero_unique_element_vector( 1.0, 1.0, 1.0 );
  Geometry::Vector<ScalarType> one_unique_element_vector( 0.0, 1.0, 1.0 );
  Geometry::Vector<ScalarType> all_unique_element_vector( 0.0, 1.0, 2.0 );

  TEST_ASSERT( !zero_unique_element_vector.hasUniqueElements() );
  TEST_ASSERT( !one_unique_element_vector.hasUniqueElements() );
  TEST_ASSERT( all_unique_element_vector.hasUniqueElements() );
}

UNIT_TEST_INSTANTIATION( Vector, hasUniqueElements );

//---------------------------------------------------------------------------//
// Check that the 1-norm of the vector can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   normOne,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, -2.0, 3.0 );

  TEST_EQUALITY( vector.normOne(), 6.0 );
}

UNIT_TEST_INSTANTIATION( Vector, normOne );

//---------------------------------------------------------------------------//
// Check that the 2-norm of the vector can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   normTwo,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 1.0, -2.0, 3.0 );

  ScalarType two_norm = sqrt( 1.0+4.0+9.0 );

  TEST_FLOATING_EQUALITY( vector.normTwo(),
			  two_norm,
			  Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( Vector, normTwo );

//---------------------------------------------------------------------------//
// Check that the inf-norm of the vector can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Vector,
				   normInf,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( -1.0, -2.0, -3.0 );

  TEST_EQUALITY( vector.normInf(), 3.0 );
}

UNIT_TEST_INSTANTIATION( Vector, normInf );

//---------------------------------------------------------------------------//
// end tstVector.cpp
//---------------------------------------------------------------------------//
