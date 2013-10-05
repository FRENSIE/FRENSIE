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
#include "ThreeSpaceTraitsAndPolicy.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, double ) 

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a surface can determine if a point is on it
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface, 
				   isOn,
				   OrdinalType,
				   ScalarType )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef typename ThreeSpace::Vector Point;

  Point point_1 = ThreeSpace::createVector( 0.0, -10.0, -10.0 );
  Point point_2 = ThreeSpace::createVector( -10.0, -10.0, -10.0 ); 

  TEST_ASSERT( sphere.isOn( point_1 ) );
  TEST_ASSERT( !sphere.isOn( point_2 ) );
}

UNIT_TEST_INSTANTIATION( Surface, isOn );

//---------------------------------------------------------------------------//
// Check that a surface returns if it is planar or not
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface, 
				   isPlanar,
				   OrdinalType,
				   ScalarType )
{
  // Generic surface
  FACEMC::Surface<OrdinalType,ScalarType> surface( 0, 
						   1, 2, 3,
						   4, 5, 6,
						   7, 8, 9,
						   10 );
  
  TEST_ASSERT( !surface.isPlanar() );

  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  TEST_ASSERT( !sphere.isPlanar() );

  // Planar surface
  FACEMC::Surface<OrdinalType,ScalarType> plane( 0,
						 1, 2, 3,
						 4 );

  TEST_ASSERT( plane.isPlanar() );
}

UNIT_TEST_INSTANTIATION( Surface, isPlanar );

//---------------------------------------------------------------------------//
// Check that a surface can return the correct sense of a point
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface, 
				   getSense,
				   OrdinalType,
				   ScalarType )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );
  
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef typename ThreeSpace::Vector Point;

  Point point_1 = ThreeSpace::createVector( 0.0, -10.0, -10.0 );
  Point point_2 = ThreeSpace::createVector( -10.0, -10.0, -10.0 ); 
  Point point_3 = ThreeSpace::createVector( 10.0, 10.0, 10.0 ); 

  FACEMC::SurfaceSense sense_1 = sphere.getSenseOfPoint( point_1 );
  FACEMC::SurfaceSense sense_2 = sphere.getSenseOfPoint( point_2 );
  FACEMC::SurfaceSense sense_3 = sphere.getSenseOfPoint( point_3 );

  TEST_EQUALITY_CONST( sense_1, FACEMC::ON_SURFACE );
  TEST_EQUALITY_CONST( sense_2, FACEMC::NEG_SURFACE_SENSE );
  TEST_EQUALITY_CONST( sense_3, FACEMC::POS_SURFACE_SENSE );
}

UNIT_TEST_INSTANTIATION( Surface, getSense );

//---------------------------------------------------------------------------//
// Check that a surface can return the correct unit normal at a point
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface, 
				   getUnitNormal,
				   OrdinalType,
				   ScalarType )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  FACEMC::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef typename ThreeSpace::Vector Point;
  typedef typename ThreeSpace::Vector Vector;

  Point point_1 = ThreeSpace::createVector( 0.0, -10.0, -10.0 ); 
  Point point_2 = ThreeSpace::createVector( -10.0, 0.0, -10.0 );
  Point point_3 = ThreeSpace::createVector( -10.0, -10.0, 0.0 );
  Point point_4 = ThreeSpace::createVector( -20.0, -10.0, -10.0 );
  Point point_5 = ThreeSpace::createVector( -10.0, -20.0, -10.0 );
  Point point_6 = ThreeSpace::createVector( -10.0, -10.0, -20.0 );

  Point normal_1 = sphere.getUnitNormalAtPoint( point_1 );
  Point normal_2 = sphere.getUnitNormalAtPoint( point_2 );
  Point normal_3 = sphere.getUnitNormalAtPoint( point_3 );
  Point normal_4 = sphere.getUnitNormalAtPoint( point_4 );
  Point normal_5 = sphere.getUnitNormalAtPoint( point_5 );
  Point normal_6 = sphere.getUnitNormalAtPoint( point_6 );

  Teuchos::ArrayView<ScalarType> normal_1_view( normal_1.values(), 3 );
  Teuchos::ArrayView<ScalarType> normal_2_view( normal_2.values(), 3 );
  Teuchos::ArrayView<ScalarType> normal_3_view( normal_3.values(), 3 );
  Teuchos::ArrayView<ScalarType> normal_4_view( normal_4.values(), 3 );
  Teuchos::ArrayView<ScalarType> normal_5_view( normal_5.values(), 3 );
  Teuchos::ArrayView<ScalarType> normal_6_view( normal_6.values(), 3 );

  Teuchos::Tuple<ScalarType,3> ref_normal_1 = 
    Teuchos::tuple( ST::one(), ST::zero(), ST::zero() );
  Teuchos::Tuple<ScalarType,3> ref_normal_2 = 
    Teuchos::tuple( ST::zero(), ST::one(), ST::zero() );
  Teuchos::Tuple<ScalarType,3> ref_normal_3 = 
    Teuchos::tuple( ST::zero(), ST::zero(), ST::one() );
  Teuchos::Tuple<ScalarType,3> ref_normal_4 = 
    Teuchos::tuple( -ST::one(), ST::zero(), ST::zero() );
  Teuchos::Tuple<ScalarType,3> ref_normal_5 = 
    Teuchos::tuple( ST::zero(), -ST::one(), ST::zero() );
  Teuchos::Tuple<ScalarType,3> ref_normal_6 = 
    Teuchos::tuple( ST::zero(), ST::zero(), -ST::one() );

  
  TEST_COMPARE_ARRAYS( normal_1_view, ref_normal_1 );
  TEST_COMPARE_ARRAYS( normal_2_view, ref_normal_2 );
  TEST_COMPARE_ARRAYS( normal_3_view, ref_normal_3 );
  TEST_COMPARE_ARRAYS( normal_4_view, ref_normal_4 );
  TEST_COMPARE_ARRAYS( normal_5_view, ref_normal_5 );
  TEST_COMPARE_ARRAYS( normal_6_view, ref_normal_6 );
}

UNIT_TEST_INSTANTIATION( Surface, getUnitNormal );

//---------------------------------------------------------------------------//
// Check that a surface can be created by transforming another surface with
// a translation vector.
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface,
				   constructor_with_translation_vector,
				   OrdinalType,
				   ScalarType )
{
  FACEMC::Surface<OrdinalType,ScalarType> xy_plane( 0,
						    0, 0, 1,
						    0 );
  FACEMC::Surface<OrdinalType,ScalarType> unit_sphere( 1,
						       1, 1, 1,
						       0, 0, 0,
						       -1 );

  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  
  typename ThreeSpace::Vector xaxis_translation_vector = 
    ThreeSpace::createVector( 1.0, 0.0, 0.0 );

  typename ThreeSpace::Vector yaxis_translation_vector = 
    ThreeSpace::createVector( 0.0, 1.0, 0.0 );
  
  typename ThreeSpace::Vector zaxis_translation_vector = 
    ThreeSpace::createVector( 0.0, 0.0, 1.0 );

  typename ThreeSpace::Matrix zero_matrix = 
    ThreeSpace::createSquareMatrix( 0.0, 0.0, 0.0,
				    0.0, 0.0, 0.0,
				    0.0, 0.0, 0.0 );

  typename ThreeSpace::Matrix identity_matrix = 
    ThreeSpace::createSquareMatrix( 1.0, 0.0, 0.0,
				    0.0, 1.0, 0.0,
				    0.0, 0.0, 1.0 );
  
  // Create a plane at z=1 from the xy_plane
  FACEMC::Surface<OrdinalType,ScalarType> z_plane( 2,
						   xy_plane,
						   zaxis_translation_vector );

  typename ThreeSpace::Matrix quad_form_matrix = 
    z_plane.getQuadraticFormMatrix();
  typename ThreeSpace::Vector linear_term_vector = 
    z_plane.getLinearTermVector();
  
  Teuchos::ArrayView<ScalarType> quad_form_matrix_view( 
						     quad_form_matrix.values(),
						     9 );
  Teuchos::ArrayView<ScalarType> linear_term_vector_view(
						   linear_term_vector.values(),
						   3 );

  typename ThreeSpace::Vector ref_linear_term_vector =
    ThreeSpace::createVector( 0.0, 0.0, 1.0 );
  typename ThreeSpace::Matrix ref_quad_form_matrix = zero_matrix;
  ScalarType ref_constant_term = 1.0;

  Teuchos::ArrayView<ScalarType> ref_quad_form_matrix_view(
						 ref_quad_form_matrix.values(),
						 9 );
  Teuchos::ArrayView<ScalarType> ref_linear_term_vector_view(
					       ref_linear_term_vector.values(),
					       3 );
  
  TEST_COMPARE_FLOATING_ARRAYS( quad_form_matrix_view,
				ref_quad_form_matrix_view,
				ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector_view,
				ref_linear_term_vector_view,
				ST::prec() );
  TEST_FLOATING_EQUALITY( z_plane.getConstantTerm(), 
			  ref_constant_term, 
			  ST::prec() );

  // Create a unit sphere centered at (-1, 0, 0) from the unit sphere at origin
  FACEMC::Surface<OrdinalType,ScalarType> unit_sphere_xaxis(
						    3,
						    unit_sphere,
						    xaxis_translation_vector );
  
  quad_form_matrix = unit_sphere_xaxis.getQuadraticFormMatrix();
  linear_term_vector = unit_sphere_xaxis.getLinearTermVector();

  ref_linear_term_vector = ThreeSpace::createVector( 2.0, 0.0, 0.0 );
  ref_quad_form_matrix = identity_matrix;
  ref_constant_term = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( quad_form_matrix_view,
				ref_quad_form_matrix_view,
				ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector_view,
				ref_linear_term_vector_view,
				ST::prec() );
  TEST_FLOATING_EQUALITY( unit_sphere_xaxis.getConstantTerm(), 
			  ref_constant_term, 
			  ST::prec() );

  // Create a unit sphere centered at (0, -1, 0) from the unit sphere at origin
  FACEMC::Surface<OrdinalType,ScalarType> unit_sphere_yaxis(
						    3,
						    unit_sphere,
						    yaxis_translation_vector );

  quad_form_matrix = unit_sphere_yaxis.getQuadraticFormMatrix();
  linear_term_vector = unit_sphere_yaxis.getLinearTermVector();

  ref_linear_term_vector = ThreeSpace::createVector( 0.0, 2.0, 0.0 );
  ref_quad_form_matrix = identity_matrix;
  ref_constant_term = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( quad_form_matrix_view,
				ref_quad_form_matrix_view,
				ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector_view,
				ref_linear_term_vector_view,
				ST::prec() );
  TEST_FLOATING_EQUALITY( unit_sphere_yaxis.getConstantTerm(), 
			  ref_constant_term, 
			  ST::prec() );

  // Create a unit sphere centered at (0, 0, -1) from the unit sphere at origin
  FACEMC::Surface<OrdinalType,ScalarType> unit_sphere_zaxis( 
						    3,
						    unit_sphere,
						    zaxis_translation_vector );
  
  quad_form_matrix = unit_sphere_zaxis.getQuadraticFormMatrix();
  linear_term_vector = unit_sphere_zaxis.getLinearTermVector();

  ref_linear_term_vector = ThreeSpace::createVector( 0.0, 0.0, 2.0 );
  ref_quad_form_matrix = identity_matrix;
  ref_constant_term = 0.0;

  TEST_COMPARE_FLOATING_ARRAYS( quad_form_matrix_view,
				ref_quad_form_matrix_view,
				ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector_view,
				ref_linear_term_vector_view,
				ST::prec() );
  TEST_FLOATING_EQUALITY( unit_sphere_zaxis.getConstantTerm(), 
			  ref_constant_term, 
			  ST::prec() );
}

UNIT_TEST_INSTANTIATION( Surface, constructor_with_translation_vector );
  
//---------------------------------------------------------------------------//
// Check that a surface can be created by transforming another surface with
// a translation vector.
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface,
				   constructor_with_rotation_matrix,
				   OrdinalType,
				   ScalarType )
{
  // General plane.
  FACEMC::Surface<OrdinalType,ScalarType> plane( 0,
						 5, 4, 3,
						 0 );
  // Unit skew cylinder with axis direction (1/2,1/2,sqrt(2)/2)
  FACEMC::Surface<OrdinalType,ScalarType> skew_cylinder( 1,
							 0.5, 1.0, 0.5,
							 0.0, 0.0, 1.0,
							 0.0, 0.0, 0.0,
							 -1.0 );

  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  
  // create the xy-plane by rotating the general plane
  typename ThreeSpace::Vector desired_direction = 
    ThreeSpace::createVector( 0.0, 0.0, 1.0 );
  typename ThreeSpace::Vector current_direction = 
    plane.getUnitNormalAtPoint( 0.0, 0.0, 0.0 );
  typename ThreeSpace::Matrix rotation_matrix =
    LAP::createRotationMatrixFromUnitVectors( desired_direction,
					      current_direction );

  FACEMC::Surface<OrdinalType,ScalarType> xy_plane( 2,
						    plane,
						    rotation_matrix );
  
  typename ThreeSpace::Matrix quad_form_matrix = 
    xy_plane.getQuadraticFormMatrix();
  typename ThreeSpace::Vector linear_term_vector = 
    xy_plane.getLinearTermVector();
  
  Teuchos::ArrayView<ScalarType> quad_form_matrix_view( 
						     quad_form_matrix.values(),
						     9 );
  Teuchos::ArrayView<ScalarType> linear_term_vector_view( 
						   linear_term_vector.values(),
						   3 );

  typename ThreeSpace::Matrix ref_quad_form_matrix = 
    ThreeSpace::createSymmetricMatrix( 0.0, 0.0, 0.0,
				            0.0, 0.0,
				                 0.0 );
  typename ThreeSpace::Vector ref_linear_term_vector = 
    ThreeSpace::createVector( 0.0,
			      0.0, 
			      1.0 );
  
  ScalarType ref_constant_term = 0.0;

  Teuchos::ArrayView<ScalarType> ref_quad_form_matrix_view(
						 ref_quad_form_matrix.values(),
						 9 );
  Teuchos::ArrayView<ScalarType> ref_linear_term_vector_view(
					       ref_linear_term_vector.values(),
					       3 );
  
  TEST_COMPARE_FLOATING_ARRAYS( quad_form_matrix_view,
				ref_quad_form_matrix_view,
				ST::prec() );
  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector_view,
				       ref_linear_term_vector_view,
				       ST::prec() );
  TEST_FLOATING_EQUALITY( xy_plane.getConstantTerm(), 
			  ref_constant_term, 
			  ST::prec() );

  // create a cylinder parallel to z-axis centered at (1.0,1.0)
  typename ThreeSpace::Vector eigenvalues;
  eigenvalues = LAP::computeEigenvaluesAndEigenvectors( 
  					skew_cylinder.getQuadraticFormMatrix(),
  					rotation_matrix );
  if( LAP::isRealignable( eigenvalues ) )
    LAP::realignEigenvectors( eigenvalues, rotation_matrix );

  FACEMC::Surface<OrdinalType,ScalarType> z_cylinder( 3,
						      skew_cylinder,
						      rotation_matrix );

  quad_form_matrix = z_cylinder.getQuadraticFormMatrix();
  linear_term_vector = z_cylinder.getLinearTermVector();

  ref_quad_form_matrix = ThreeSpace::createSymmetricMatrix( 1.0, 0.0, 0.0,
							         1.0, 0.0,
							              0.0 );
  ref_linear_term_vector = ThreeSpace::createVector( 0.0, 0.0, 0.0 );
  ref_constant_term = -1.0;

  TEST_COMPARE_FLOATING_ARRAYS( quad_form_matrix_view,
				ref_quad_form_matrix_view,
				ST::prec() );
  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector_view,
				       ref_linear_term_vector_view,
				       ST::prec() );
  TEST_FLOATING_EQUALITY( z_cylinder.getConstantTerm(), 
			  ref_constant_term, 
			  ST::prec() );
}

UNIT_TEST_INSTANTIATION( Surface, constructor_with_rotation_matrix );
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
