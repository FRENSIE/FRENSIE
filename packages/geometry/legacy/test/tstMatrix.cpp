//---------------------------------------------------------------------------//
//!
//! \file   tstMatrix.hpp
//! \author Alex Robinson
//! \brief  Matrix (3x3) unit tests.
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
#include "Geometry_Matrix.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that two matrices can be compared equal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   equality,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> A;
  Geometry::Matrix<ScalarType> B;

  TEST_ASSERT( A == B );
}

UNIT_TEST_INSTANTIATION( Matrix, equality );

//---------------------------------------------------------------------------//
// Check that two matrices can be compared unequal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   inequality,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> A;
  Geometry::Matrix<ScalarType> B( 1.0,
				2.0, 4.0,
				3.0, 5.0, 6.0 );

  TEST_ASSERT( A != B );
}

UNIT_TEST_INSTANTIATION( Matrix, inequality );

//---------------------------------------------------------------------------//
// Check that a matrix can be set as a zero matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   zero,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix( 1.0, 1.0, 1.0,
				     1.0, 1.0, 1.0,
				     1.0, 1.0, 1.0 );

  matrix.zero();

  Geometry::Matrix<ScalarType> ref_zero_matrix( 0.0, 0.0, 0.0,
					      0.0, 0.0, 0.0,
					      0.0, 0.0, 0.0 );

  TEST_EQUALITY( matrix, ref_zero_matrix );
}

UNIT_TEST_INSTANTIATION( Matrix, zero );

//---------------------------------------------------------------------------//
// Check that a matrix can be set as an identity matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   identity,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;

  matrix.identity();

  Geometry::Matrix<ScalarType> ref_identity_matrix( 1.0, 0.0, 0.0,
						  0.0, 1.0, 0.0,
						  0.0, 0.0, 1.0 );

  TEST_EQUALITY( matrix, ref_identity_matrix );
}

UNIT_TEST_INSTANTIATION( Matrix, identity );

//---------------------------------------------------------------------------//
// Check that the elements of a matrix can be accessed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   element_access,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix( 1.0, 2.0, 3.0,
				     4.0, 5.0, 6.0,
				     7.0, 8.0, 9.0 );

  TEST_EQUALITY( matrix( 0, 0 ), 1.0 );
  TEST_EQUALITY( matrix( 0, 1 ), 2.0 );
  TEST_EQUALITY( matrix( 0, 2 ), 3.0 );
  TEST_EQUALITY( matrix( 1, 0 ), 4.0 );
  TEST_EQUALITY( matrix( 1, 1 ), 5.0 );
  TEST_EQUALITY( matrix( 1, 2 ), 6.0 );
  TEST_EQUALITY( matrix( 2, 0 ), 7.0 );
  TEST_EQUALITY( matrix( 2, 1 ), 8.0 );
  TEST_EQUALITY( matrix( 2, 2 ), 9.0 );

  const Geometry::Matrix<ScalarType> const_matrix( 1.0, 2.0, 3.0,
						 4.0, 5.0, 6.0,
						 7.0, 8.0, 9.0 );

  TEST_EQUALITY( const_matrix( 0, 0 ), 1.0 );
  TEST_EQUALITY( const_matrix( 0, 1 ), 2.0 );
  TEST_EQUALITY( const_matrix( 0, 2 ), 3.0 );
  TEST_EQUALITY( const_matrix( 1, 0 ), 4.0 );
  TEST_EQUALITY( const_matrix( 1, 1 ), 5.0 );
  TEST_EQUALITY( const_matrix( 1, 2 ), 6.0 );
  TEST_EQUALITY( const_matrix( 2, 0 ), 7.0 );
  TEST_EQUALITY( const_matrix( 2, 1 ), 8.0 );
  TEST_EQUALITY( const_matrix( 2, 2 ), 9.0 );
}

UNIT_TEST_INSTANTIATION( Matrix, element_access );

//---------------------------------------------------------------------------//
// Check that a column of the matrix can be accessed
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   column_access,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  Teuchos::ArrayView<const ScalarType> col_1_view( matrix[0], 3 );
  Teuchos::ArrayView<const ScalarType> col_2_view( matrix[1], 3 );
  Teuchos::ArrayView<const ScalarType> col_3_view( matrix[2], 3 );

  typedef Teuchos::ScalarTraits<ScalarType> ST;
  Teuchos::Tuple<ScalarType,3> ref_col_1 = Teuchos::tuple( ST::one(),
							   ST::zero(),
							   ST::zero() );
  Teuchos::Tuple<ScalarType,3> ref_col_2 = Teuchos::tuple( ST::zero(),
							   ST::one(),
							   ST::zero() );
  Teuchos::Tuple<ScalarType,3> ref_col_3 = Teuchos::tuple( ST::zero(),
							   ST::zero(),
							   ST::one() );

  TEST_COMPARE_ARRAYS( col_1_view, ref_col_1 );
  TEST_COMPARE_ARRAYS( col_2_view, ref_col_2 );
  TEST_COMPARE_ARRAYS( col_3_view, ref_col_3 );
}

UNIT_TEST_INSTANTIATION( Matrix, column_access );

//---------------------------------------------------------------------------//
// Check that a raw pointer to the head of the matrix can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   getRawPtr,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  ScalarType* head_ptr = matrix.getRawPtr();

  TEST_EQUALITY( *head_ptr, 1.0 );

  const Geometry::Matrix<ScalarType> const_matrix;

  const ScalarType* const_head_ptr = const_matrix.getRawPtr();

  TEST_EQUALITY( *const_head_ptr, 0.0 );
}

UNIT_TEST_INSTANTIATION( Matrix, getRawPtr );

//---------------------------------------------------------------------------//
// Check that a view of the matrix can be made
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   view,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  Teuchos::ArrayView<const ScalarType> view_1 = matrix.view();
  Teuchos::ArrayView<const ScalarType> view_2 = matrix();

  TEST_COMPARE_ARRAYS( view_1, view_2 );
  TEST_EQUALITY( view_1.size(), 9 );
  TEST_EQUALITY( view_2.size(), 9 );
}

UNIT_TEST_INSTANTIATION( Matrix, view );

//---------------------------------------------------------------------------//
// Check that a matrix can be added to another matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   compound_addition,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  Geometry::Matrix<ScalarType> second_matrix( 1.0, 1.0, 1.0,
					    1.0, 1.0, 1.0,
					    1.0, 1.0, 1.0 );

  Geometry::Matrix<ScalarType> ref_matrix( 2.0, 1.0, 1.0,
					 1.0, 2.0, 1.0,
					 1.0, 1.0, 2.0 );

  matrix += second_matrix;

  TEST_EQUALITY( matrix, ref_matrix );
}

UNIT_TEST_INSTANTIATION( Matrix, compound_addition );

//---------------------------------------------------------------------------//
// Check that a matrix can be subtracted from another matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   compound_subtraction,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  Geometry::Matrix<ScalarType> second_matrix( 1.0, 1.0, 1.0,
					    1.0, 1.0, 1.0,
					    1.0, 1.0, 1.0 );

  Geometry::Matrix<ScalarType> ref_matrix( 0.0, -1.0, -1.0,
					 -1.0, 0.0, -1.0,
					 -1.0, -1.0, 0.0 );

  matrix -= second_matrix;

  TEST_EQUALITY( matrix, ref_matrix );
}

UNIT_TEST_INSTANTIATION( Matrix, compound_subtraction );

//---------------------------------------------------------------------------//
// Check that a matrix can be multiplied by a scalar
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   compound_scalar_multiplication,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  ScalarType alpha = 5.0;

  Geometry::Matrix<ScalarType> ref_matrix( 5.0, 0.0, 0.0,
					 0.0, 5.0, 0.0,
					 0.0, 0.0, 5.0 );

  matrix *= alpha;

  TEST_EQUALITY( matrix, ref_matrix );
}

UNIT_TEST_INSTANTIATION( Matrix, compound_scalar_multiplication );

//---------------------------------------------------------------------------//
// Check that alpha*A*B + beta*this can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   multiply,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> A( 1.0,
				1.0, 1.0,
				1.0, 1.0, 1.0 );

  Geometry::Matrix<ScalarType> B;
  B.identity();

  Geometry::Matrix<ScalarType> matrix;

  matrix.multiply( 1.0, A, false, B, false, 0.0 );

  Geometry::Matrix<ScalarType> ref_matrix( A );

  TEST_EQUALITY( matrix, ref_matrix );

  matrix.multiply( 1.0, A, true, B, true, 1.0 );

  ref_matrix*= 2;

  TEST_EQUALITY( matrix, ref_matrix );
}

UNIT_TEST_INSTANTIATION( Matrix, multiply );

//---------------------------------------------------------------------------//
// Check that columns of a matrix can be swapped
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   swapColumns,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;
  matrix.identity();

  Geometry::Matrix<ScalarType> ref_matrix_1( 0.0, 1.0, 0.0,
					   1.0, 0.0, 0.0,
					   0.0, 0.0, 1.0 );

  Geometry::Matrix<ScalarType> ref_matrix_2( 0.0, 0.0, 1.0,
					   0.0, 1.0, 0.0,
					   1.0, 0.0, 0.0 );

  Geometry::Matrix<ScalarType> ref_matrix_3( 1.0, 0.0, 0.0,
					   0.0, 0.0, 1.0,
					   0.0, 1.0, 0.0 );

  matrix.swapColumns( 0, 1 );

  TEST_EQUALITY( matrix, ref_matrix_1 );

  matrix.swapColumns( 0, 1 );
  matrix.swapColumns( 0, 2 );

  TEST_EQUALITY( matrix, ref_matrix_2 );

  matrix.swapColumns( 0, 2 );
  matrix.swapColumns( 1, 2 );

  TEST_EQUALITY( matrix, ref_matrix_3 );
}

UNIT_TEST_INSTANTIATION( Matrix, swapColumns );

//---------------------------------------------------------------------------//
// Check that the dimensions of the matrix can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   numRows_numCols,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix;

  TEST_EQUALITY( matrix.numRows(), 3 );
  TEST_EQUALITY( matrix.numCols(), 3 );
}

UNIT_TEST_INSTANTIATION( Matrix, numRows_numCols );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as a zero matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   isZeroMatrix,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> zero_matrix;
  Geometry::Matrix<ScalarType> identity_matrix;
  identity_matrix.identity();

  TEST_ASSERT( zero_matrix.isZeroMatrix() );
  TEST_ASSERT( !identity_matrix.isZeroMatrix() );
}

UNIT_TEST_INSTANTIATION( Matrix, isZeroMatrix );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as an identity matrix
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   isIdentityMatrix,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> zero_matrix;
  Geometry::Matrix<ScalarType> identity_matrix;
  identity_matrix.identity();

  TEST_ASSERT( !zero_matrix.isIdentityMatrix() );
  TEST_ASSERT( identity_matrix.isIdentityMatrix() );
}

UNIT_TEST_INSTANTIATION( Matrix, isIdentityMatrix );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested for symmetry
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   isSymmetric,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> general_matrix( 1.0, 2.0, 3.0,
					     4.0, 5.0, 6.0,
					     7.0, 8.0, 9.0 );
  Geometry::Matrix<ScalarType> symmetric_matrix( 1.0,
					       2.0, 1.0,
					       3.0, 2.0, 1.0 );

  TEST_ASSERT( !general_matrix.isSymmetric() );
  TEST_ASSERT( symmetric_matrix.isSymmetric() );
}

UNIT_TEST_INSTANTIATION( Matrix, isSymmetric );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as orthonormal
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   isOrthonormal,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> general_matrix( 1.0, 2.0, 3.0,
					     4.0, 5.0, 6.0,
					     7.0, 8.0, 9.0 );
  Geometry::Matrix<ScalarType> orthogonal_matrix( 1.0, 0.0, -1.0,
						1.0, 0.0, 1.0,
						0.0, 1.0, 0.0 );
  Geometry::Matrix<ScalarType> normal_matrix( 1.0, 1.0, 1.0,
					    0.0, 0.0, 0.0,
					    0.0, 0.0, 0.0 );
  ScalarType c = 1.0/sqrt(2);
  Geometry::Matrix<ScalarType> orthonormal_matrix( c,   0.0, -c,
						 c,   0.0, c,
						 0.0, 1.0, 0.0 );

  TEST_ASSERT( !general_matrix.isOrthonormal() );
  TEST_ASSERT( !orthogonal_matrix.isOrthonormal() );
  TEST_ASSERT( !normal_matrix.isOrthonormal() );
  TEST_ASSERT( orthonormal_matrix.isOrthonormal() );
}

UNIT_TEST_INSTANTIATION( Matrix, isOrthonormal );

//---------------------------------------------------------------------------//
// Check that a matrix can be tested as nonsingular
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   isNonsingular,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> singular_matrix( 1.0, 0.0, 0.0,
					      0.0, 1.0, 0.0,
					      0.0, 0.0, 0.0 );
  Geometry::Matrix<ScalarType> nonsingular_matrix;
  nonsingular_matrix.identity();

  TEST_ASSERT( !singular_matrix.isNonsingular() );
  TEST_ASSERT( nonsingular_matrix.isNonsingular() );
}

UNIT_TEST_INSTANTIATION( Matrix, isNonsingular );

//---------------------------------------------------------------------------//
// Check that the 1-norm of the matrix can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   normOne,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix( -1.0, 2.0, -3.0,
				     4.0, -5.0, 6.0,
				     -7.0, 8.0, -9.0 );
  ScalarType ref_one_norm = 18;

  TEST_EQUALITY( matrix.normOne(), ref_one_norm );
}

UNIT_TEST_INSTANTIATION( Matrix, normOne );

//---------------------------------------------------------------------------//
// Check that the Infinity-norm of the matrix can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   normInf,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix( -1.0, 2.0, -3.0,
				     4.0, -5.0, 6.0,
				     -7.0, 8.0, -9.0 );

  TEST_EQUALITY( matrix.normInf(), 24.0 );
}

UNIT_TEST_INSTANTIATION( Matrix, normInf );

//---------------------------------------------------------------------------//
// Check that the Frobenius-norm of the matrix can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Matrix,
				   normFrobenius,
				   ScalarType )
{
  Geometry::Matrix<ScalarType> matrix( -1.0, 2.0, -3.0,
				     4.0, -5.0, 6.0,
				     -7.0, 8.0, -9.0 );

  ScalarType ref_frobenius_norm = sqrt(1+4+9+16+25+36+49+64+81);

  TEST_FLOATING_EQUALITY( matrix.normFrobenius(),
			  ref_frobenius_norm,
			  Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( Matrix, normFrobenius );

//---------------------------------------------------------------------------//
// end tstMatrix.cpp
//---------------------------------------------------------------------------//
