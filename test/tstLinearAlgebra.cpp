//---------------------------------------------------------------------------//
// \file   tstLinearAlgebra.cpp
// \author Alex Robinson
// \brief  Linear Algebra function unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>

// FACEMC Includes
#include "LinearAlgebraAlgorithms.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the product of a scalar and a vector can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, scalar_vector_multiply )
{
  double scalar = 2.0;
  
  Teuchos::Tuple<double,3> vector( Teuchos::tuple( 1.0, 1.0, 1.0) );

  Teuchos::Tuple<double,3> ref_vector( Teuchos::tuple( 2.0, 2.0, 2.0 ) );

  // Premultiply
  Teuchos::Tuple<double,3> premultiply_vector = 2.0*vector;

  // Postmultiply
  Teuchos::Tuple<double,3> postmultiply_vector = vector*2.0;

  // Reassignment
  vector *= 2.0;

  TEST_COMPARE_ARRAYS( premultiply_vector, ref_vector );
  TEST_COMPARE_ARRAYS( postmultiply_vector, ref_vector );
  TEST_COMPARE_ARRAYS( vector, ref_vector );
}

//---------------------------------------------------------------------------//
// Check that the product of a scalar and a matrix can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, scalar_matrix_multiply )
{
  double scalar = 2.0;

  Teuchos::Tuple<double,9> matrix = Teuchos::tuple( 1.0, 1.0, 1.0,
						    1.0, 1.0, 1.0,
						    1.0, 1.0, 1.0 );
  Teuchos::Tuple<double,9> ref_matrix = Teuchos::tuple( 2.0, 2.0, 2.0,
							2.0, 2.0, 2.0,
							2.0, 2.0, 2.0 );
  // Premultiply
  Teuchos::Tuple<double,9> premultiply_matrix = 2.0*matrix;
  
  // Postmultiply
  Teuchos::Tuple<double,9> postmultiply_matrix = matrix*2.0;

  // Reassignment
  matrix *= 2.0;

  TEST_COMPARE_ARRAYS( premultiply_matrix, ref_matrix );
  TEST_COMPARE_ARRAYS( postmultiply_matrix, ref_matrix );
  TEST_COMPARE_ARRAYS( matrix, ref_matrix );
}

//---------------------------------------------------------------------------//
// Check that the dot product of two vectors can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, dot_product )
{
  Teuchos::Tuple<double,3> row_vector = Teuchos::tuple( 1.0, 1.0, 1.0 );
  Teuchos::Tuple<double,3> column_vector = Teuchos::tuple( 2.0, 2.0, 2.0 );

  double ref_product = 6.0;

  // Dot product
  double product = row_vector*column_vector;

  TEST_EQUALITY( product, ref_product );
}

//---------------------------------------------------------------------------//
// Check that the product of a row vector and a matrix can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, row_vector_matrix_product )
{
  Teuchos::Tuple<double,3> row_vector = Teuchos::tuple( 1.0, 1.0, 1.0 );
  Teuchos::Tuple<double,9> matrix = Teuchos::tuple( 2.0, 2.0, 2.0,
						    2.0, 2.0, 2.0,
						    2.0, 2.0, 2.0 );
  
  Teuchos::Tuple<double,3> ref_row_vector = Teuchos::tuple( 6.0, 6.0, 6.0 );

  // Product
  Teuchos::Tuple<double,3> product_row_vector = row_vector*matrix;

  TEST_COMPARE_ARRAYS( product_row_vector, ref_row_vector );
}

//---------------------------------------------------------------------------//
// Check that the product of a matrix and a column vector can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, matrix_column_vector_product )
{
  Teuchos::Tuple<double,9> matrix = Teuchos::tuple( 2.0, 2.0, 2.0,
						    2.0, 2.0, 2.0,
						    2.0, 2.0, 2.0 );
  Teuchos::Tuple<double,3> column_vector = Teuchos::tuple( 1.0, 1.0, 1.0 );
  
  Teuchos::Tuple<double,3> ref_column_vector = Teuchos::tuple( 6.0, 6.0, 6.0 );

  // Product
  Teuchos::Tuple<double,3> product_column_vector = matrix*column_vector;
  
  TEST_COMPARE_ARRAYS( product_column_vector, ref_column_vector );
}

//---------------------------------------------------------------------------//
// Check that the product of two matrices can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, matrix_matrix_product )
{
  Teuchos::Tuple<double,9> left_matrix = Teuchos::tuple( 1.0, 1.0, 1.0,
							 1.0, 1.0, 1.0,
							 1.0, 1.0, 1.0 );
  Teuchos::Tuple<double,9> right_matrix = Teuchos::tuple( 2.0, 2.0, 2.0,
							  2.0, 2.0, 2.0,
							  2.0, 2.0, 2.0 );
  
  Teuchos::Tuple<double,9> ref_matrix = Teuchos::tuple( 6.0, 6.0, 6.0,
							6.0, 6.0, 6.0,
							6.0, 6.0, 6.0 );
  
  // Product
  Teuchos::Tuple<double,9> product_matrix = left_matrix*right_matrix;
  
  TEST_COMPARE_ARRAYS( product_matrix, ref_matrix );
}

//---------------------------------------------------------------------------//
// Check that the magnitude of a vector can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, vectorMagnitude )
{
  Teuchos::Tuple<double,3> vector = Teuchos::tuple( 1.0, 1.0, 1.0 );

  double ref_magnitude = sqrt(3);

  double magnitude = FACEMC::LinearAlgebra::vectorMagnitude( vector );

  TEST_EQUALITY( magnitude, ref_magnitude );
}

//---------------------------------------------------------------------------//
// Check that a vector can be normalized
TEUCHOS_UNIT_TEST( LinearAlgebra, normalizeVector )
{
  Teuchos::Tuple<double,3> vector = Teuchos::tuple( 1.0, 1.0, 1.0 );

  Teuchos::Tuple<double,3> ref_norm_vector = 
    Teuchos::tuple( 1.0, 1.0, 1.0 )*(1/sqrt(3));

  FACEMC::LinearAlgebra::normalizeVector( vector );

  TEST_COMPARE_ARRAYS( vector, ref_norm_vector );
}

//---------------------------------------------------------------------------//
// Check that the determinant of a matrix can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, matrixDeterminant )
{
  Teuchos::Tuple<double,9> matrix = Teuchos::tuple( 1.0, 1.0, 1.0,
						    1.0, 1.0, 1.0,
						    1.0, 1.0, 1.0 );

  double ref_determinant = 0.0;

  double determinant = FACEMC::LinearAlgebra::matrixDeterminant( matrix );

  TEST_EQUALITY( determinant, ref_determinant );
}

//---------------------------------------------------------------------------//
// Check that the transpose of a matrix can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, matrixTranspose )
{
  Teuchos::Tuple<double,9> matrix = Teuchos::tuple( 1.0, 2.0, 3.0,
						    4.0, 5.0, 6.0,
						    7.0, 8.0, 9.0 );

  Teuchos::Tuple<double,9> ref_transpose_matrix = 
    Teuchos::tuple( 1.0, 4.0, 7.0,
		    2.0, 5.0, 8.0,
		    3.0, 6.0, 9.0 );

  Teuchos::Tuple<double,9> transpose_matrix = 
    FACEMC::LinearAlgebra::matrixTranspose( matrix );

  TEST_COMPARE_ARRAYS( transpose_matrix, ref_transpose_matrix );
}

//---------------------------------------------------------------------------//
// Check that the inverse of a matrix can be calculated
TEUCHOS_UNIT_TEST( LinearAlgebra, matrixInverse )
{
  Teuchos::Tuple<double,9> matrix = Teuchos::tuple( 1.0, 2.0, 3.0,
						    2.0, 1.0, 4.0,
						    3.0, 4.0, 1.0 );

  Teuchos::Tuple<double,9> inverse_matrix = 
    FACEMC::LinearAlgebra::matrixInverse( matrix );
  
  Teuchos::Tuple<double,9> inverse_inverse_matrix = 
    FACEMC::LinearAlgebra::matrixInverse( inverse_matrix );
  
  TEST_COMPARE_FLOATING_ARRAYS( matrix, inverse_inverse_matrix, TOL );
}

//---------------------------------------------------------------------------//
// Check that a linear system can be solved
TEUCHOS_UNIT_TEST( LinearAlgebra, solveSystem )
{
  Teuchos::Tuple<double,9> coefficient_matrix = Teuchos::tuple( 1.0, 2.0, 3.0,
								2.0, 1.0, 4.0,
								3.0, 4.0, 1.0 );
  Teuchos::Tuple<double,3> constant_vector = Teuchos::tuple( 6.0, 7.0, 8.0 );

  Teuchos::Tuple<double,3> ref_solution_vector = 
    Teuchos::tuple( 1.0, 1.0, 1.0 );

  Teuchos::Tuple<double,3> solution_vector = 
    FACEMC::LinearAlgebra::solveSystem( coefficient_matrix, constant_vector );

  TEST_COMPARE_FLOATING_ARRAYS( solution_vector, ref_solution_vector, TOL );
}
//---------------------------------------------------------------------------//
// end tstLinearAlgebra.cpp
//---------------------------------------------------------------------------//

