//---------------------------------------------------------------------------//
//!
//! \file   tstSurface.cpp
//! \author Alex Robinson
//! \brief  Surface class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Surface.hpp"
#include "ThreeSpaceHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a surface can determine if a point is on it
TEUCHOS_UNIT_TEST( Surface, isOn )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<short,double> sphere( 0,
						 1, 1, 1,
						 20, 20, 20,
						 10*10+10*10+10*10 - 10*10 );

  typedef FACEMC::Surface<short,double>::Vector Point;

  Point point_1 = FACEMC::createThreeSpaceVector( 0.0, -10.0, -10.0 );
  Point point_2 = FACEMC::createThreeSpaceVector( -10.0, -10.0, -10.0 ); 

  TEST_ASSERT( sphere.isOn( point_1 ) );
  TEST_ASSERT( !sphere.isOn( point_2 ) );
}

//---------------------------------------------------------------------------//
// Check that a surface returns if it is planar or not
TEUCHOS_UNIT_TEST( Surface, isPlanar )
{
  // Generic surface
  FACEMC::Surface<short,double> surface( 0, 
					 1, 2, 3,
					 4, 5, 6,
					 7, 8, 9,
					 10 );
  
  TEST_ASSERT( !surface.isPlanar() );

  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<short,double> sphere( 0,
					1, 1, 1,
					20, 20, 20,
					10*10+10*10+10*10 - 10*10 );

  TEST_ASSERT( !sphere.isPlanar() );

  // Planar surface
  FACEMC::Surface<short,double> plane( 0,
				       1, 2, 3,
				       4 );

  TEST_ASSERT( plane.isPlanar() );
}

//---------------------------------------------------------------------------//
// Check that a surface can return the correct sense of a point
TEUCHOS_UNIT_TEST( Surface, getSense )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<short,double> sphere( 0,
					1, 1, 1,
					20, 20, 20,
					10*10+10*10+10*10 - 10*10 );

  typedef FACEMC::Surface<short,double>::Vector Point;

  Point point_1 = FACEMC::createThreeSpaceVector( 0.0, -10.0, -10.0 );
  Point point_2 = FACEMC::createThreeSpaceVector( -10.0, -10.0, -10.0 ); 
  Point point_3 = FACEMC::createThreeSpaceVector( 10.0, 10.0, 10.0 ); 

  FACEMC::SurfaceSense sense_1 = sphere.getSenseOfPoint( point_1 );
  FACEMC::SurfaceSense sense_2 = sphere.getSenseOfPoint( point_2 );
  FACEMC::SurfaceSense sense_3 = sphere.getSenseOfPoint( point_3 );

  TEST_EQUALITY_CONST( sense_1, FACEMC::ON_SURFACE );
  TEST_EQUALITY_CONST( sense_2, FACEMC::NEG_SURFACE_SENSE );
  TEST_EQUALITY_CONST( sense_3, FACEMC::POS_SURFACE_SENSE );
}

//---------------------------------------------------------------------------//
// Check that a surface can return the correct unit normal at a point
TEUCHOS_UNIT_TEST( Surface, getUnitNormal )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<short,double> sphere( 0,
					1, 1, 1,
					20, 20, 20,
					10*10+10*10+10*10 - 10*10 );

  typedef FACEMC::Surface<short,double>::Vector Point;
  typedef FACEMC::Surface<short,double>::Vector Vector;

  Point point_1 = FACEMC::createThreeSpaceVector( 0.0, -10.0, -10.0 ); 
  Point point_2 = FACEMC::createThreeSpaceVector( -10.0, 0.0, -10.0 );
  Point point_3 = FACEMC::createThreeSpaceVector( -10.0, -10.0, 0.0 );
  Point point_4 = FACEMC::createThreeSpaceVector( -20.0, -10.0, -10.0 );
  Point point_5 = FACEMC::createThreeSpaceVector( -10.0, -20.0, -10.0 );
  Point point_6 = FACEMC::createThreeSpaceVector( -10.0, -10.0, -20.0 );

  Point normal_1 = sphere.getUnitNormalAtPoint( point_1 );
  Point normal_2 = sphere.getUnitNormalAtPoint( point_2 );
  Point normal_3 = sphere.getUnitNormalAtPoint( point_3 );
  Point normal_4 = sphere.getUnitNormalAtPoint( point_4 );
  Point normal_5 = sphere.getUnitNormalAtPoint( point_5 );
  Point normal_6 = sphere.getUnitNormalAtPoint( point_6 );

  Teuchos::ArrayView<double> normal_1_view( normal_1.values(), 3 );
  Teuchos::ArrayView<double> normal_2_view( normal_2.values(), 3 );
  Teuchos::ArrayView<double> normal_3_view( normal_3.values(), 3 );
  Teuchos::ArrayView<double> normal_4_view( normal_4.values(), 3 );
  Teuchos::ArrayView<double> normal_5_view( normal_5.values(), 3 );
  Teuchos::ArrayView<double> normal_6_view( normal_6.values(), 3 );

  Teuchos::Tuple<double,3> ref_normal_1 = Teuchos::tuple( 1.0, 0.0, 0.0 );
  Teuchos::Tuple<double,3> ref_normal_2 = Teuchos::tuple( 0.0, 1.0, 0.0 );
  Teuchos::Tuple<double,3> ref_normal_3 = Teuchos::tuple( 0.0, 0.0, 1.0 );
  Teuchos::Tuple<double,3> ref_normal_4 = Teuchos::tuple( -1.0, 0.0, 0.0 );
  Teuchos::Tuple<double,3> ref_normal_5 = Teuchos::tuple( 0.0, -1.0, 0.0 );
  Teuchos::Tuple<double,3> ref_normal_6 = Teuchos::tuple( 0.0, 0.0, -1.0 );

  
  TEST_COMPARE_ARRAYS( normal_1_view, ref_normal_1 );
  TEST_COMPARE_ARRAYS( normal_2_view, ref_normal_2 );
  TEST_COMPARE_ARRAYS( normal_3_view, ref_normal_3 );
  TEST_COMPARE_ARRAYS( normal_4_view, ref_normal_4 );
  TEST_COMPARE_ARRAYS( normal_5_view, ref_normal_5 );
  TEST_COMPARE_ARRAYS( normal_6_view, ref_normal_6 );
}

//---------------------------------------------------------------------------//
// Check that a surface can be transformed with a rotation matrix and 
// a translation vector
// TEUCHOS_UNIT_TEST( Surface, transformSurface )
// {
//   // Spherical surface centered at (-10,-10,-10) with radius 10
//   Teuchos::RCP<FACEMC::Surface> surface_ptr( 
// 			     new FACEMC::Surface( 0,
// 						  1, 1, 1,
// 						  20, 20, 20,
// 						  10*10+10*10+10*10 - 10*10 ) 
// 					  );
  
//   // Direction vector of sphere local z-axis (in global coordinate system)
//   FACEMC::Surface::Vector initial_direction =
//     Teuchos::tuple( -sqrt(3.0)/3, -sqrt(3.0)/3, -sqrt(3.0)/3 );

//   // Direction vector of sphere local z-axis after transform
//   FACEMC::Surface::Vector final_direction = 
//     Teuchos::tuple( 0.0, 0.0, 1.0 );

//   // Rotation matrix
//   FACEMC::Surface::Matrix rotation_matrix =
//     FACEMC::LinearAlgebra::generateRotationMatrixFromUnitVectors(
// 				              initial_direction,
// 				              final_direction );

//   // Translation vector (vector from origin to sphere center)
//   FACEMC::Surface::Vector translation_vector = 
//     Teuchos::tuple( -10.0, -10.0, -10.0 );

//   surface_ptr->transformSurface( rotation_matrix,
// 				 translation_vector );

//   FACEMC::Surface::Matrix ref_quadratic_form_matrix = 
//     Teuchos::tuple( 1.0, 0.0, 0.0,
// 		    0.0, 1.0, 0.0,
// 		    0.0, 0.0, 1.0 );
//   FACEMC::Surface::Vector ref_linear_term_vector = 
//     Teuchos::tuple( 0.0, 0.0, 0.0 );
//   double ref_constant_term = -10*10;

//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getQuadraticFormMatrix()(), 
// 				       ref_quadratic_form_matrix(),
// 				       TOL );
//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getLinearTermVector()(), 
// 				       ref_linear_term_vector(),
// 				       TOL );
//   TEST_FLOATING_EQUALITY( surface_ptr->getConstantTerm(), 
// 			  ref_constant_term,
// 			  TOL );

//   // Spherical surface centered at (-10,-10,-10) with radius 10
//   surface_ptr.reset( new FACEMC::Surface( 0,
// 					  1, 1, 1,
// 					  20, 20, 20,
// 					  10*10+10*10+10*10 - 10*10 ) 
// 		     );
  
//   // Direction vector of sphere local z-axis (in global coordinate system)
//   initial_direction =
//     Teuchos::tuple( -sqrt(3.0)/3, -sqrt(3.0)/3, -sqrt(3.0)/3 );

//   // Direction vector of sphere local z-axis after transform
//   final_direction = 
//     Teuchos::tuple( 0.0, 1.0, 0.0 );

//   // Rotation matrix
//   rotation_matrix =
//     FACEMC::LinearAlgebra::generateRotationMatrixFromUnitVectors(
// 				              initial_direction,
// 					      final_direction );

//   // Translation vector 
//   translation_vector = 
//     Teuchos::tuple( -10.0, -10.0, -10.0 );

//   surface_ptr->transformSurface( rotation_matrix,
// 				 translation_vector );

//   translation_vector = 
//     Teuchos::tuple( 10.0, -10.0, -10.0 );

//   surface_ptr->transformSurface( ref_quadratic_form_matrix,
// 				 translation_vector );

//   ref_quadratic_form_matrix = 
//     Teuchos::tuple( 1.0, 0.0, 0.0,
// 		    0.0, 1.0, 0.0,
// 		    0.0, 0.0, 1.0 );
//   ref_linear_term_vector = 
//     Teuchos::tuple( 20.0, -20.0, -20.0 );
  
//   ref_constant_term = 10*10+10*10+10*10 - 10*10;

//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getQuadraticFormMatrix()(), 
// 				       ref_quadratic_form_matrix(),
// 				       TOL );
//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getLinearTermVector()(), 
// 				       ref_linear_term_vector(),
// 				       TOL );
//   TEST_FLOATING_EQUALITY( surface_ptr->getConstantTerm(), 
// 			  ref_constant_term,
// 			  TOL );

//   // cylindrical surface centered at (x0=-10, y0=-10) with radius 10
//   surface_ptr.reset( 
// 		    new FACEMC::Surface( 0,
// 					 1, 1, 0,
// 					 20, 20, 0,
// 					 10*10+10*10 - 10*10 ) 
// 		     );
  
//   // Direction vector of cylinder local z-axis (in global coordinate system)
//   initial_direction =
//     Teuchos::tuple( 0.0, 0.0, 1.0 );

//   // Direction vector of cylinder local z-axis after transformation
//   final_direction =
//     Teuchos::tuple( 1.0, 0.0, 0.0 );

//   // Rotation matrix
//   rotation_matrix =
//     FACEMC::LinearAlgebra::generateRotationMatrixFromUnitVectors(
// 				              initial_direction,
// 				              final_direction );

//   // Translation vector (vector from origin to cylinder center)
//   translation_vector = 
//     Teuchos::tuple( -10.0, -10.0, 0.0 );

//   surface_ptr->transformSurface( rotation_matrix,
// 				 translation_vector );

//   ref_quadratic_form_matrix = 
//     Teuchos::tuple( 0.0, 0.0, 0.0,
// 		    0.0, 1.0, 0.0,
// 		    0.0, 0.0, 1.0 );
//   ref_linear_term_vector = 
//     Teuchos::tuple( 0.0, 0.0, 0.0 );
//   ref_constant_term = -10*10;

//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getQuadraticFormMatrix()(), 
// 				       ref_quadratic_form_matrix(),
// 				       TOL );
//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getLinearTermVector()(), 
// 				       ref_linear_term_vector(),
// 				       TOL );
//   TEST_FLOATING_EQUALITY( surface_ptr->getConstantTerm(), 
// 			  ref_constant_term,
// 			  TOL );

//   // cylindrical surface centered at (x0=0, y0=-10) with radius 10
//   surface_ptr.reset( 
// 		    new FACEMC::Surface( 0,
// 					 1, 1, 0,
// 					 0, 20, 0,
// 					 10*10 - 10*10 ) 
// 		     );
  
//   // Direction vector of cylinder local z-axis (in global coordinate system)
//   initial_direction =
//     Teuchos::tuple( 0.0, 0.0, 1.0 );

//   // Direction vector of cylinder local z-axis after transformation
//   final_direction =
//     Teuchos::tuple( 1.0, 0.0, 0.0 );

//   // Rotation matrix
//   rotation_matrix =
//     FACEMC::LinearAlgebra::generateRotationMatrixFromUnitVectors(
// 				              initial_direction,
// 				              final_direction );

//   // Translation vector (vector from origin to cylinder center)
//   translation_vector = 
//     Teuchos::tuple( 0.0, -10.0, 0.0 );

//   surface_ptr->transformSurface( rotation_matrix,
// 				 translation_vector );

//   ref_quadratic_form_matrix = 
//     Teuchos::tuple( 0.0, 0.0, 0.0,
// 		    0.0, 1.0, 0.0,
// 		    0.0, 0.0, 1.0 );
//   ref_linear_term_vector = 
//     Teuchos::tuple( 0.0, 0.0, 0.0 );
//   ref_constant_term = -10*10;

//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getQuadraticFormMatrix()(), 
// 				       ref_quadratic_form_matrix(),
// 				       TOL );
//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getLinearTermVector()(), 
// 				       ref_linear_term_vector(),
// 				       TOL );
//   TEST_FLOATING_EQUALITY( surface_ptr->getConstantTerm(), 
// 			  ref_constant_term,
// 			  TOL );

//   // planar surface 
//   surface_ptr.reset( 
// 		    new FACEMC::Surface( 0,
// 					 6, 5, 4,
// 					 3 ) 
// 		     );
  
//   // Direction vector of plane local z-axis (in global coordinate system)
//   initial_direction =
//     Teuchos::tuple( 6.0/sqrt(6.0*6.0+5.0*5.0+4.0*4.0), 
// 		    5.0/sqrt(6.0*6.0+5.0*5.0+4.0*4.0), 
// 		    4.0/sqrt(6.0*6.0+5.0*5.0+4.0*4.0) );

//   // Direction vector of plane local z-axis after transformation
//   final_direction =
//     Teuchos::tuple( 0.0, 0.0, 1.0 );

//   // Rotation matrix
//   rotation_matrix =
//     FACEMC::LinearAlgebra::generateRotationMatrixFromUnitVectors(
// 					      initial_direction,
// 				              final_direction );
  
//   rotation_matrix = FACEMC::LinearAlgebra::matrixTranspose( rotation_matrix );
  
//   // Translation vector (vector from origin to plane)
//   translation_vector = 
//     Teuchos::tuple( 0.0, 0.0, surface_ptr->getConstantTerm()/-4.0 );

//   surface_ptr->transformSurface( rotation_matrix,
// 				 translation_vector );

//   ref_quadratic_form_matrix = 
//     Teuchos::tuple( 0.0, 0.0, 0.0,
// 		    0.0, 0.0, 0.0,
// 		    0.0, 0.0, 0.0 );
//   ref_linear_term_vector = 
//     Teuchos::tuple( 0.0, 0.0, sqrt(6.0*6.0+5.0*5.0+4.0*4.0) );
//   ref_constant_term = 0.0;

//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getQuadraticFormMatrix()(), 
// 				       ref_quadratic_form_matrix(),
// 				       TOL );
//   FACEMC_TEST_COMPARE_FLOATING_ARRAYS( surface_ptr->getLinearTermVector()(), 
// 				       ref_linear_term_vector(),
// 				       TOL );
//   TEST_FLOATING_EQUALITY( surface_ptr->getConstantTerm(), 
// 			  ref_constant_term,
// 			  TOL );

// }  
	   
//---------------------------------------------------------------------------//
// end tstSurface.cpp
//---------------------------------------------------------------------------//
