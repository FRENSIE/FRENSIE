//---------------------------------------------------------------------------//
//!
//! \file   tstMatrixHelpers.cpp
//! \author Alex Robinson
//! \brief  Matrix helper functions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_Vector.hpp"
#include "Geometry_VectorHelpers.hpp"
#include "Geometry_Matrix.hpp"
#include "Geometry_MatrixHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a 3x3 matrix can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createMatrix,
				   ScalarType)
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  Geometry::Matrix<ScalarType> general_matrix =
    Geometry::createMatrix( ST::one(), ST::one(), ST::one(),
			  ST::one(), ST::one(), ST::one(),
			  ST::one(), ST::one(), ST::one() );

  Geometry::Matrix<ScalarType> ref_general_matrix( 1.0, 1.0, 1.0,
						 1.0, 1.0, 1.0,
						 1.0, 1.0, 1.0 );

  Geometry::Matrix<ScalarType> symmetric_matrix =
    Geometry::createMatrix<ScalarType>( 1.0,
				      2.0, 1.0,
				      3.0, 2.0, 1.0 );

  Geometry::Matrix<ScalarType> ref_symmetric_matrix( 1.0,
						   2.0, 1.0,
						   3.0, 2.0, 1.0 );

  TEST_EQUALITY( general_matrix, ref_general_matrix );
  TEST_EQUALITY( symmetric_matrix, ref_symmetric_matrix );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createMatrix );

//---------------------------------------------------------------------------//
// Check that a matrix can be created from rows
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createMatrixFromRows,
				   ScalarType)
{
  Geometry::Vector<ScalarType> row_1( 1.0, 2.0, 3.0 );
  Geometry::Vector<ScalarType> row_2( 4.0, 5.0, 6.0 );
  Geometry::Vector<ScalarType> row_3( 7.0, 8.0, 9.0 );

  Geometry::Matrix<ScalarType> matrix =
    Geometry::createMatrixFromRows( row_1, row_2, row_3 );

  Geometry::Matrix<ScalarType> ref_matrix( 1.0, 2.0, 3.0,
					 4.0, 5.0, 6.0,
					 7.0, 8.0, 9.0 );

  TEST_EQUALITY( matrix, ref_matrix );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createMatrixFromRows );

//---------------------------------------------------------------------------//
// Check that a matrix can be created from columns
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createMatrixFromColumns,
				   ScalarType )
{
  Geometry::Vector<ScalarType> col_1( 1.0, 2.0, 3.0 );
  Geometry::Vector<ScalarType> col_2( 4.0, 5.0, 6.0 );
  Geometry::Vector<ScalarType> col_3( 7.0, 8.0, 9.0 );

  Geometry::Matrix<ScalarType> matrix =
    Geometry::createMatrixFromColumns( col_1, col_2, col_3 );

  Geometry::Matrix<ScalarType> ref_matrix( 1.0, 4.0, 7.0,
					 2.0, 5.0, 8.0,
					 3.0, 6.0, 9.0 );

  TEST_EQUALITY( matrix, ref_matrix );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createMatrixFromColumns );

//---------------------------------------------------------------------------//
// Check that a x-axis rotation matrix can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createXAxisRotationMatrix,
				   ScalarType )
{
  Geometry::Vector<ScalarType> x_axis( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> y_axis( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> z_axis( 0.0, 0.0, 1.0 );

  ScalarType rotation_angle = Utility::PhysicalConstants::pi/4;

  Geometry::Matrix<ScalarType> rotation_matrix =
    Geometry::createXAxisRotationMatrix( rotation_angle );

  Geometry::Vector<ScalarType> x_prime_axis( x_axis );
  Geometry::Vector<ScalarType> y_prime_axis( 0.0, 1/sqrt(2.0), 1/sqrt(2.0) );
  Geometry::Vector<ScalarType> z_prime_axis( 0.0, -1/sqrt(2.0), 1/sqrt(2.0) );

  x_axis *= rotation_matrix;
  y_axis *= rotation_matrix;
  z_axis *= rotation_matrix;

  TEST_COMPARE_FLOATING_ARRAYS( x_axis(),
				x_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( y_axis(),
				y_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( z_axis(),
				z_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createXAxisRotationMatrix );

//---------------------------------------------------------------------------//
// Check that a y-axis rotation matrix can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createYAxisRotationMatrix,
				   ScalarType )
{
  Geometry::Vector<ScalarType> x_axis( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> y_axis( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> z_axis( 0.0, 0.0, 1.0 );

  ScalarType rotation_angle = Utility::PhysicalConstants::pi/4;

  Geometry::Matrix<ScalarType> rotation_matrix =
    Geometry::createYAxisRotationMatrix( rotation_angle );

  Geometry::Vector<ScalarType> x_prime_axis( 1/sqrt(2.0), 0.0, -1/sqrt(2.0) );
  Geometry::Vector<ScalarType> y_prime_axis( y_axis );
  Geometry::Vector<ScalarType> z_prime_axis( 1/sqrt(2.0), 0.0, 1/sqrt(2.0) );

  x_axis *= rotation_matrix;
  y_axis *= rotation_matrix;
  z_axis *= rotation_matrix;

  TEST_COMPARE_FLOATING_ARRAYS( x_axis(),
				x_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( y_axis(),
				y_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( z_axis(),
				z_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createYAxisRotationMatrix );

//---------------------------------------------------------------------------//
// Check that a z-axis rotation matrix can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createZAxisRotationMatrix,
				   ScalarType )
{
  Geometry::Vector<ScalarType> x_axis( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> y_axis( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> z_axis( 0.0, 0.0, 1.0 );

  ScalarType rotation_angle = Utility::PhysicalConstants::pi/4;

  Geometry::Matrix<ScalarType> rotation_matrix =
    Geometry::createZAxisRotationMatrix( rotation_angle );

  Geometry::Vector<ScalarType> x_prime_axis( 1/sqrt(2.0), 1/sqrt(2.0), 0.0 );
  Geometry::Vector<ScalarType> y_prime_axis( -1/sqrt(2.0), 1/sqrt(2.0), 0.0 );
  Geometry::Vector<ScalarType> z_prime_axis( z_axis );

  x_axis *= rotation_matrix;
  y_axis *= rotation_matrix;
  z_axis *= rotation_matrix;

  TEST_COMPARE_FLOATING_ARRAYS( x_axis(),
				x_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( y_axis(),
				y_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( z_axis(),
				z_prime_axis(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createZAxisRotationMatrix );

//---------------------------------------------------------------------------//
// Check that a rotation matrix can be created from two unit vectors
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MatrixHelpers,
				   createRotationMatrixFromUnitVectors,
				   ScalarType )
{
  // x-axis to z-axis rotation
  Geometry::Vector<ScalarType> initial_direction =
    Geometry::createXAxisVector<ScalarType>();
  Geometry::Vector<ScalarType> final_direction =
    Geometry::createZAxisVector<ScalarType>();

  Geometry::Matrix<ScalarType> rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
						 final_direction );

  Geometry::Matrix<ScalarType> ref_rotation_matrix( 0.0, 0.0, -1.0,
						  0.0, 1.0,  0.0,
						  1.0, 0.0,  0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
				ref_rotation_matrix(),
				Teuchos::ScalarTraits<ScalarType>::prec() );

  // x-axis to neg-z-axis rotation
  final_direction =
    Geometry::createZAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );

  rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
  						 final_direction );

  ref_rotation_matrix = Geometry::createMatrix<ScalarType>( 0.0, 0.0, -1.0,
  							  0.0, 1.0, 0.0,
  							  -1.0, 0.0, 0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
  				ref_rotation_matrix(),
  				Teuchos::ScalarTraits<ScalarType>::prec() );

  // x-axis to y-axis rotation
  final_direction = Geometry::createYAxisVector<ScalarType>();

  rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
  						 final_direction );

  ref_rotation_matrix = Geometry::createMatrix<ScalarType>( 0.0, -1.0, 0.0,
  							  1.0,  0.0, 0.0,
  							  0.0,  0.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
  				ref_rotation_matrix(),
  				Teuchos::ScalarTraits<ScalarType>::prec() );

  // x-axis to neg-y-axis rotation
  final_direction =
    Geometry::createYAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );

  rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
  						 final_direction );

  ref_rotation_matrix = Geometry::createMatrix<ScalarType>( 0.0, 1.0, 0.0,
  							  -1.0, 0.0, 0.0,
  							  0.0, 0.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
  				ref_rotation_matrix(),
  				Teuchos::ScalarTraits<ScalarType>::prec() );

  // z-axis to x-axis rotation
  initial_direction = Geometry::createZAxisVector<ScalarType>();
  final_direction = Geometry::createXAxisVector<ScalarType>();

  rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
  						 final_direction );

  ref_rotation_matrix = Geometry::createMatrix<ScalarType>( 0.0, 0.0, 1.0,
  							  0.0, 1.0, 0.0,
  							  -1.0, 0.0, 0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
  				ref_rotation_matrix(),
  				Teuchos::ScalarTraits<ScalarType>::prec() );

  // neg-z-axis to x-axis rotation
  initial_direction =
    Geometry::createZAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );
  final_direction = Geometry::createXAxisVector<ScalarType>();

  rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
  						 final_direction );

  ref_rotation_matrix = Geometry::createMatrix<ScalarType>( 0.0, 0.0, -1.0,
  							  0.0, 1.0,  0.0,
  							  -1.0, 0.0,  0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
  				ref_rotation_matrix(),
  				Teuchos::ScalarTraits<ScalarType>::prec() );

  // y-axis to x-axis rotation
  initial_direction = Geometry::createYAxisVector<ScalarType>();
  final_direction = Geometry::createXAxisVector<ScalarType>();

  rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( initial_direction,
  					      final_direction );

  ref_rotation_matrix = Geometry::createMatrix<ScalarType>( 0.0, 1.0, 0.0,
  							  -1.0, 0.0, 0.0,
  							  0.0, 0.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( rotation_matrix(),
  				ref_rotation_matrix(),
  				Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( MatrixHelpers, createRotationMatrixFromUnitVectors );

//---------------------------------------------------------------------------//
// end tstMatrixHelpers.cpp
//---------------------------------------------------------------------------//

