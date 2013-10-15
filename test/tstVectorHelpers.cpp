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

// FACEMC Includes
#include "Vector.hpp"
#include "VectorHelpers.hpp"

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
  FACEMC::Vector<ScalarType> vector = FACEMC::createVector( ST::one(), 
							    ST::one()*2, 
							    ST::one()*3 );

  FACEMC::Vector<ScalarType> ref_vector( 1.0, 2.0, 3.0 );

  TEST_EQUALITY( vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createVector );

//---------------------------------------------------------------------------//
// Check that a vector can be created from a Trip struct
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createVector_tuple,
				   ScalarType )
{
  FACEMC::Trip<ScalarType,ScalarType,ScalarType> data( 1.0, 1.0, 1.0 );

  FACEMC::Vector<ScalarType> data_vector = FACEMC::createVector( data );

  FACEMC::Vector<ScalarType> ref_vector( 1.0, 1.0, 1.0 );

  TEST_EQUALITY( data_vector, ref_vector );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createVector_tuple );

//---------------------------------------------------------------------------//
// Check that a x-axis vector can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( VectorHelpers,
				   createXAxisVector,
				   ScalarType )
{
  FACEMC::Vector<ScalarType> pos_x_axis = 
    FACEMC::createXAxisVector<ScalarType>();
  FACEMC::Vector<ScalarType> neg_x_axis = 
    FACEMC::createXAxisVector<ScalarType>( FACEMC::NEGATIVE_DIRECTION );

  FACEMC::Vector<ScalarType> ref_pos_x_axis( 1.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> ref_neg_x_axis( -1.0, 0.0, 0.0 );

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
  FACEMC::Vector<ScalarType> pos_y_axis = 
    FACEMC::createYAxisVector<ScalarType>();
  FACEMC::Vector<ScalarType> neg_y_axis = 
    FACEMC::createYAxisVector<ScalarType>( FACEMC::NEGATIVE_DIRECTION );

  FACEMC::Vector<ScalarType> ref_pos_y_axis( 0.0, 1.0, 0.0 );
  FACEMC::Vector<ScalarType> ref_neg_y_axis( 0.0, -1.0, 0.0 );

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
  FACEMC::Vector<ScalarType> pos_z_axis = 
    FACEMC::createZAxisVector<ScalarType>();
  FACEMC::Vector<ScalarType> neg_z_axis = 
    FACEMC::createZAxisVector<ScalarType>( FACEMC::NEGATIVE_DIRECTION );

  FACEMC::Vector<ScalarType> ref_pos_z_axis( 0.0, 0.0, 1.0 );
  FACEMC::Vector<ScalarType> ref_neg_z_axis( 0.0, 0.0, -1.0 );

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
  FACEMC::Vector<ScalarType> vector( 3.0, 2.0, 1.0 );
  ScalarType constant_term = 4.0;

  FACEMC::Vector<ScalarType> zeroing_vector = 
    FACEMC::createZeroingVector( vector, constant_term );

  FACEMC::Vector<ScalarType> ref_zeroing_vector( -4.0/3, 0.0, 0.0 );

  TEST_EQUALITY( zeroing_vector, ref_zeroing_vector );

  vector = FACEMC::createVector<ScalarType>( 0.0, 2.0, 1.0 );
  zeroing_vector = FACEMC::createZeroingVector( vector, constant_term );
  ref_zeroing_vector = FACEMC::createVector<ScalarType>( 0.0, -2.0, 0.0 );

  TEST_EQUALITY( zeroing_vector, ref_zeroing_vector );

  vector = FACEMC::createVector<ScalarType>( 0.0, 0.0, 1.0 );
  zeroing_vector = FACEMC::createZeroingVector( vector, constant_term );
  ref_zeroing_vector = FACEMC::createVector<ScalarType>( 0.0, 0.0, -4.0 );

  TEST_EQUALITY( zeroing_vector, ref_zeroing_vector );
}

UNIT_TEST_INSTANTIATION( VectorHelpers, createZeroingVector );

//---------------------------------------------------------------------------//
// end tstVectorHelpers.cpp
//---------------------------------------------------------------------------//

