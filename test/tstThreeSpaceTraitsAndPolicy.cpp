//---------------------------------------------------------------------------//
//!
//! \file   tstThreeSpaceTraitsAndPolicy.cpp
//! \author Alex Robinson
//! \brief  Three space traits and policy unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ThreeSpaceTraitsAndPolicy.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a matrix can be created from individual columns
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ThreeSpaceTraitsAndPolicy,
				   createSquareMatrixFromColumns,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;

  typename ThreeSpace::Vector column_1 = 
    ThreeSpace::createVector( 0.0, 1.0, 2.0 );
  typename ThreeSpace::Vector column_2 = 
    ThreeSpace::createVector( 3.0, 4.0, 5.0 );
  typename ThreeSpace::Vector column_3 = 
    ThreeSpace::createVector( 6.0, 7.0, 8.0 );

  typename ThreeSpace::Matrix matrix = 
    ThreeSpace::createSquareMatrixFromColumns( column_1, column_2, column_3 );

  typename ThreeSpace::Matrix ref_matrix = 
    ThreeSpace::createSquareMatrix( 0.0, 3.0, 6.0,
				    1.0, 4.0, 7.0,
				    2.0, 5.0, 8.0 );

  Teuchos::ArrayView<ScalarType> matrix_view( matrix.values(), 9 );
  Teuchos::ArrayView<ScalarType> ref_matrix_view( ref_matrix.values(), 9 );

  TEST_COMPARE_ARRAYS( matrix_view, ref_matrix_view );
}

UNIT_TEST_INSTANTIATION( ThreeSpaceTraitsAndPolicy, 
			 createSquareMatrixFromColumns );

// Check that a matrix can be created from individual rows
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ThreeSpaceTraitsAndPolicy,
				   createSquareMatrixFromRows,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;

  typename ThreeSpace::Vector row_1 = 
    ThreeSpace::createVector( 0.0, 1.0, 2.0 );
  typename ThreeSpace::Vector row_2 = 
    ThreeSpace::createVector( 3.0, 4.0, 5.0 );
  typename ThreeSpace::Vector row_3 = 
    ThreeSpace::createVector( 6.0, 7.0, 8.0 );

  typename ThreeSpace::Matrix matrix = 
    ThreeSpace::createSquareMatrixFromRows( row_1, row_2, row_3 );

  typename ThreeSpace::Matrix ref_matrix = 
    ThreeSpace::createSquareMatrix( 0.0, 1.0, 2.0,
				    3.0, 4.0, 5.0,
				    6.0, 7.0, 8.0 );

  Teuchos::ArrayView<ScalarType> matrix_view( matrix.values(), 9 );
  Teuchos::ArrayView<ScalarType> ref_matrix_view( ref_matrix.values(), 9 );

  TEST_COMPARE_ARRAYS( matrix_view, ref_matrix_view );
}

UNIT_TEST_INSTANTIATION( ThreeSpaceTraitsAndPolicy, 
			 createSquareMatrixFromRows );


//---------------------------------------------------------------------------//
// end tstThreeSpaceTraitsAndPolicy.cpp
//---------------------------------------------------------------------------//

