//---------------------------------------------------------------------------//
//!
//! \file   tstVectorHelpers.cpp
//! \author Alex Robinson
//! \brief  Vector helper function unit tests.
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

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createVector,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  Geometry::Vector<ScalarType> vector = Geometry::createVector( ST::one(),
							    ST::one()*2,
							    ST::one()*3 );

  Geometry::Vector<ScalarType> ref_vector( 1.0, 2.0, 3.0 );

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createVector );

//---------------------------------------------------------------------------//
// Check that a vector can be created from a Trip struct
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createVector_tuple,
				   ScalarType )
{
  Utility::Trip<ScalarType,ScalarType,ScalarType> data( 1.0, 1.0, 1.0 );

  Geometry::Vector<ScalarType> data_vector = Geometry::createVector( data );

  Geometry::Vector<ScalarType> ref_vector( 1.0, 1.0, 1.0 );

  TEST_EQUALITY( data_vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createVector_tuple );

//---------------------------------------------------------------------------//
// Check that a x-axis vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createXAxisVector,
				   ScalarType )
{
  Geometry::Vector<ScalarType> pos_x_axis =
    Geometry::createXAxisVector<ScalarType>();
  Geometry::Vector<ScalarType> neg_x_axis =
    Geometry::createXAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );

  Geometry::Vector<ScalarType> ref_pos_x_axis( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_neg_x_axis( -1.0, 0.0, 0.0 );

  TEST_EQUALITY( pos_x_axis, ref_pos_x_axis );
  TEST_EQUALITY( neg_x_axis, ref_neg_x_axis );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createXAxisVector );

//---------------------------------------------------------------------------//
// Check that a y-axis vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createYAxisVector,
				   ScalarType )
{
  Geometry::Vector<ScalarType> pos_y_axis =
    Geometry::createYAxisVector<ScalarType>();
  Geometry::Vector<ScalarType> neg_y_axis =
    Geometry::createYAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );

  Geometry::Vector<ScalarType> ref_pos_y_axis( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> ref_neg_y_axis( 0.0, -1.0, 0.0 );

  TEST_EQUALITY( pos_y_axis, ref_pos_y_axis );
  TEST_EQUALITY( neg_y_axis, ref_neg_y_axis );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createYAxisVector );

//---------------------------------------------------------------------------//
// Check that a z-axis vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createZAxisVector,
				   ScalarType )
{
  Geometry::Vector<ScalarType> pos_z_axis =
    Geometry::createZAxisVector<ScalarType>();
  Geometry::Vector<ScalarType> neg_z_axis =
    Geometry::createZAxisVector<ScalarType>( Utility::NEGATIVE_DIRECTION );

  Geometry::Vector<ScalarType> ref_pos_z_axis( 0.0, 0.0, 1.0 );
  Geometry::Vector<ScalarType> ref_neg_z_axis( 0.0, 0.0, -1.0 );

  TEST_EQUALITY( pos_z_axis, ref_pos_z_axis );
  TEST_EQUALITY( neg_z_axis, ref_neg_z_axis );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createZAxisVector );

//---------------------------------------------------------------------------//
// Check that a zeroing vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createZeroingVector,
				   ScalarType )
{
  Geometry::Vector<ScalarType> vector( 3.0, 2.0, 1.0 );
  ScalarType constant_term = 4.0;

  Geometry::Vector<ScalarType> zeroing_vector =
    Geometry::createZeroingVector( vector, constant_term );

  Geometry::Vector<ScalarType> ref_zeroing_vector( -4.0/3, 0.0, 0.0 );

  TEST_EQUALITY( zeroing_vector, ref_zeroing_vector );

  vector = Geometry::createVector<ScalarType>( 0.0, 2.0, 1.0 );
  zeroing_vector = Geometry::createZeroingVector( vector, constant_term );
  ref_zeroing_vector = Geometry::createVector<ScalarType>( 0.0, -2.0, 0.0 );

  TEST_EQUALITY( zeroing_vector, ref_zeroing_vector );

  vector = Geometry::createVector<ScalarType>( 0.0, 0.0, 1.0 );
  zeroing_vector = Geometry::createZeroingVector( vector, constant_term );
  ref_zeroing_vector = Geometry::createVector<ScalarType>( 0.0, 0.0, -4.0 );

  TEST_EQUALITY( zeroing_vector, ref_zeroing_vector );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createZeroingVector );

//---------------------------------------------------------------------------//
// end tstVectorHelpers.cpp
//---------------------------------------------------------------------------//

