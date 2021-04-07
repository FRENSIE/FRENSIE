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

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Geometry_Surface.hpp"
#include "Geometry_Vector.hpp"
#include "Geometry_VectorHelpers.hpp"
#include "Geometry_Matrix.hpp"
#include "Geometry_MatrixHelpers.hpp"

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
// Tests.
//---------------------------------------------------------------------------//
// Check that a surface can determine if a point is on it
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface,
				   isOn,
				   OrdinalType,
				   ScalarType )
{
  // Spherical surface centered at (-10,-10,-10) with radius 10
  Geometry::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  // Planar Surfaces
  Geometry::Surface<OrdinalType,ScalarType> plane_a( 1,
						   0.0, -1.0, 2.0,
						   0.0 );
  Geometry::Surface<OrdinalType,ScalarType> plane_b( 2,
						   0.0, 1.0, 2.0,
						   0.0 );

  Geometry::Vector<ScalarType> point_1( 0.0, -10.0, -10.0 );
  Geometry::Vector<ScalarType> point_2( -10.0, -10.0, -10.0 );
  Geometry::Vector<ScalarType> point_3( 0.0, 0.0, 0.0 );

  TEST_ASSERT( sphere.isOn( point_1 ) );
  TEST_ASSERT( !sphere.isOn( point_2 ) );
  TEST_ASSERT( plane_a.isOn( point_3 ) );
  TEST_ASSERT( plane_b.isOn( point_3 ) );
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
  Geometry::Surface<OrdinalType,ScalarType> surface( 0,
						   1, 2, 3,
						   4, 5, 6,
						   7, 8, 9,
						   10 );

  TEST_ASSERT( !surface.isPlanar() );

  // Spherical surface centered at (-10,-10,-10) with radius 10
  Geometry::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  TEST_ASSERT( !sphere.isPlanar() );

  // Planar surface
  Geometry::Surface<OrdinalType,ScalarType> plane( 0,
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
  Geometry::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  Geometry::Vector<ScalarType> point_1( 0.0, -10.0, -10.0 );
  Geometry::Vector<ScalarType> point_2( -10.0, -10.0, -10.0 );
  Geometry::Vector<ScalarType> point_3( 10.0, 10.0, 10.0 );

  Geometry::SurfaceSense sense_1 = sphere.getSenseOfPoint( point_1 );
  Geometry::SurfaceSense sense_2 = sphere.getSenseOfPoint( point_2 );
  Geometry::SurfaceSense sense_3 = sphere.getSenseOfPoint( point_3 );

  TEST_EQUALITY_CONST( sense_1, Geometry::ON_SURFACE );
  TEST_EQUALITY_CONST( sense_2, Geometry::NEG_SURFACE_SENSE );
  TEST_EQUALITY_CONST( sense_3, Geometry::POS_SURFACE_SENSE );
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
  Geometry::Surface<OrdinalType,ScalarType> sphere( 0,
						  1, 1, 1,
						  20, 20, 20,
						  10*10+10*10+10*10 - 10*10 );

  Geometry::Vector<ScalarType> point_1( 0.0, -10.0, -10.0 );
  Geometry::Vector<ScalarType> point_2( -10.0, 0.0, -10.0 );
  Geometry::Vector<ScalarType> point_3( -10.0, -10.0, 0.0 );
  Geometry::Vector<ScalarType> point_4( -20.0, -10.0, -10.0 );
  Geometry::Vector<ScalarType> point_5( -10.0, -20.0, -10.0 );
  Geometry::Vector<ScalarType> point_6( -10.0, -10.0, -20.0 );

  Geometry::Vector<ScalarType> normal_1 = sphere.getUnitNormalAtPoint( point_1 );
  Geometry::Vector<ScalarType> normal_2 = sphere.getUnitNormalAtPoint( point_2 );
  Geometry::Vector<ScalarType> normal_3 = sphere.getUnitNormalAtPoint( point_3 );
  Geometry::Vector<ScalarType> normal_4 = sphere.getUnitNormalAtPoint( point_4 );
  Geometry::Vector<ScalarType> normal_5 = sphere.getUnitNormalAtPoint( point_5 );
  Geometry::Vector<ScalarType> normal_6 = sphere.getUnitNormalAtPoint( point_6 );

  Geometry::Vector<ScalarType> ref_normal_1( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_normal_2( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> ref_normal_3( 0.0, 0.0, 1.0 );
  Geometry::Vector<ScalarType> ref_normal_4( -1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_normal_5( 0.0, -1.0, 0.0 );
  Geometry::Vector<ScalarType> ref_normal_6( 0.0, 0.0, -1.0 );

  Geometry::Vector<ScalarType> reverse_normal_1 =
    sphere.getUnitNormalAtPoint( point_1, Geometry::NEG_SURFACE_SENSE );
  Geometry::Vector<ScalarType> reverse_normal_2 =
    sphere.getUnitNormalAtPoint( point_2, Geometry::NEG_SURFACE_SENSE );
  Geometry::Vector<ScalarType> reverse_normal_3 =
    sphere.getUnitNormalAtPoint( point_3, Geometry::NEG_SURFACE_SENSE );
  Geometry::Vector<ScalarType> reverse_normal_4 =
    sphere.getUnitNormalAtPoint( point_4, Geometry::NEG_SURFACE_SENSE );
  Geometry::Vector<ScalarType> reverse_normal_5 =
    sphere.getUnitNormalAtPoint( point_5, Geometry::NEG_SURFACE_SENSE );
  Geometry::Vector<ScalarType> reverse_normal_6 =
    sphere.getUnitNormalAtPoint( point_6, Geometry::NEG_SURFACE_SENSE );

  Geometry::Vector<ScalarType> ref_reverse_normal_1( -1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_reverse_normal_2( 0.0, -1.0, 0.0 );
  Geometry::Vector<ScalarType> ref_reverse_normal_3( 0.0, 0.0, -1.0 );
  Geometry::Vector<ScalarType> ref_reverse_normal_4( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_reverse_normal_5( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> ref_reverse_normal_6( 0.0, 0.0, 1.0 );

  TEST_EQUALITY( normal_1, ref_normal_1 );
  TEST_EQUALITY( normal_2, ref_normal_2 );
  TEST_EQUALITY( normal_3, ref_normal_3 );
  TEST_EQUALITY( normal_4, ref_normal_4 );
  TEST_EQUALITY( normal_5, ref_normal_5 );
  TEST_EQUALITY( normal_6, ref_normal_6 );
  TEST_EQUALITY( reverse_normal_1, ref_reverse_normal_1 );
  TEST_EQUALITY( reverse_normal_2, ref_reverse_normal_2 );
  TEST_EQUALITY( reverse_normal_3, ref_reverse_normal_3 );
  TEST_EQUALITY( reverse_normal_4, ref_reverse_normal_4 );
  TEST_EQUALITY( reverse_normal_5, ref_reverse_normal_5 );
  TEST_EQUALITY( reverse_normal_6, ref_reverse_normal_6 );
}

UNIT_TEST_INSTANTIATION( Surface, getUnitNormal );

//---------------------------------------------------------------------------//
// Check that the distance to a surface from a point along a direction can be
// calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface,
				   getDistance,
				   OrdinalType,
				   ScalarType )
{
  Geometry::Surface<OrdinalType,ScalarType> xy_plane( 0,
						    0, 0, 1,
						    0 );
  Geometry::Surface<OrdinalType,ScalarType> unit_sphere( 1,
						       1, 1, 1,
						       0, 0, 0,
						       -1 );
  Geometry::Surface<OrdinalType,ScalarType> general_surface( 2,
							   1, 1, 1,
							   1, 1, 1,
							   1, 1, 1,
							   0 );

  // Testing points
  Geometry::Vector<ScalarType> point1( 0, 0, 0 );
  Geometry::Vector<ScalarType> point2( 1, 0, 0 );
  Geometry::Vector<ScalarType> point3( 0, 1, 0 );
  Geometry::Vector<ScalarType> point4( 0, 0, 1 );
  Geometry::Vector<ScalarType> point5( -1, 0, 0 );
  Geometry::Vector<ScalarType> point6( 0, -1, 0 );
  Geometry::Vector<ScalarType> point7( 0, 0, -1 );
  Geometry::Vector<ScalarType> point8( -1, -1, -1 );
  point8.normalize();
  Geometry::Vector<ScalarType> point9( -1, -1, -1 );
  point9.normalize();
  point9 *= 2;

  // Testing directions
  Geometry::Vector<ScalarType> direction1( 1, 0, 0 );
  Geometry::Vector<ScalarType> direction2( 0, 1, 0 );
  Geometry::Vector<ScalarType> direction3( 0, 0, 1 );
  Geometry::Vector<ScalarType> direction4( -1, 0, 0 );
  Geometry::Vector<ScalarType> direction5( 0, -1, 0 );
  Geometry::Vector<ScalarType> direction6( 0, 0, -1 );
  Geometry::Vector<ScalarType> direction7( 1, 1, 1 );
  direction7.normalize();

  // The distance to the surface
  ScalarType distance;

  // Test the xy plane
  distance = xy_plane.getDistance( point2, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point2, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point2, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point3, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point3, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point3, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point4, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point4, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point4, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point4, direction6 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = xy_plane.getDistance( point7, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point7, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point7, direction3 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = xy_plane.getDistance( point7, direction6 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = xy_plane.getDistance( point8, direction7 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  // Test the unit sphere
  distance = unit_sphere.getDistance( point1, direction1 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = unit_sphere.getDistance( point1, direction4 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = unit_sphere.getDistance( point1, direction2 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = unit_sphere.getDistance( point1, direction5 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = unit_sphere.getDistance( point1, direction3 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = unit_sphere.getDistance( point1, direction6 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 1.0 ) );

  distance = unit_sphere.getDistance( point2, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point2, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point2, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point2, direction4 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 2.0 ) );

  distance = unit_sphere.getDistance( point2, direction5 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point2, direction6 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point3, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point3, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point3, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point3, direction4 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point3, direction5 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 2.0 ) );

  distance = unit_sphere.getDistance( point3, direction6 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point4, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point4, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point4, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point4, direction4 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point4, direction5 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point4, direction6 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 2.0 ) );

  distance = unit_sphere.getDistance( point5, direction1 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 2.0 ) );

  distance = unit_sphere.getDistance( point5, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point5, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point5, direction4 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point5, direction5 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point5, direction6 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point6, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point6, direction2 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 2.0 ) );

  distance = unit_sphere.getDistance( point6, direction3 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point6, direction4 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point6, direction5 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point6, direction6 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point7, direction1 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point7, direction2 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point7, direction3 );
  TEST_EQUALITY_CONST( distance,
		       static_cast<ScalarType>( 2.0 ) );

  distance = unit_sphere.getDistance( point7, direction4 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point7, direction5 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point7, direction6 );
  TEST_EQUALITY_CONST( distance,
		       std::numeric_limits<ScalarType>::infinity() );

  distance = unit_sphere.getDistance( point8, direction7 );
  TEST_FLOATING_EQUALITY( distance,
			  static_cast<ScalarType>( 2.0 ),
			  Teuchos::ScalarTraits<ScalarType>::eps() );

  distance = unit_sphere.getDistance( point9, direction7 );
  TEST_FLOATING_EQUALITY( distance,
			  static_cast<ScalarType>( 1.0 ),
			  Teuchos::ScalarTraits<ScalarType>::eps() );

  // Test the general surface
  distance = general_surface.getDistance( point8, direction7 );
  ScalarType ref_distance =
    1.0 - Teuchos::ScalarTraits<ScalarType>::squareroot(3.0)/2.0;
  TEST_FLOATING_EQUALITY( distance,
			  ref_distance,
			  10*Teuchos::ScalarTraits<ScalarType>::eps() );
}

UNIT_TEST_INSTANTIATION( Surface, getDistance );

//---------------------------------------------------------------------------//
// Check that a surface can be created by transforming another surface with
// a translation vector.
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface,
				   constructor_with_translation_vector,
				   OrdinalType,
				   ScalarType )
{
  Geometry::Surface<OrdinalType,ScalarType> xy_plane( 0,
						    0, 0, 1,
						    0 );
  Geometry::Surface<OrdinalType,ScalarType> unit_sphere( 1,
						       1, 1, 1,
						       0, 0, 0,
						       -1 );


  Geometry::Vector<ScalarType> xaxis_translation_vector( 1.0, 0.0, 0.0 );

  Geometry::Vector<ScalarType> yaxis_translation_vector( 0.0, 1.0, 0.0 );

  Geometry::Vector<ScalarType> zaxis_translation_vector( 0.0, 0.0, 1.0 );

  Geometry::Matrix<ScalarType> zero_matrix;

  Geometry::Matrix<ScalarType> identity_matrix;
  identity_matrix.identity();

  // Create a plane at z=1 from the xy_plane
  Geometry::Surface<OrdinalType,ScalarType> z_plane( 2,
						   xy_plane,
						   zaxis_translation_vector );

  Geometry::Matrix<ScalarType> quad_form_matrix =
    z_plane.getQuadraticFormMatrix();
  Geometry::Vector<ScalarType> linear_term_vector =
    z_plane.getLinearTermVector();

  Geometry::Vector<ScalarType> ref_linear_term_vector( 0.0, 0.0, 1.0 );
  Geometry::Matrix<ScalarType> ref_quad_form_matrix;
  ScalarType ref_constant_term = 1.0;

  TEST_EQUALITY( quad_form_matrix, ref_quad_form_matrix );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector(),
				ref_linear_term_vector(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_FLOATING_EQUALITY( z_plane.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );

  // Create a unit sphere centered at (-1, 0, 0) from the unit sphere at origin
  Geometry::Surface<OrdinalType,ScalarType> unit_sphere_xaxis(
						    3,
						    unit_sphere,
						    xaxis_translation_vector );

  quad_form_matrix = unit_sphere_xaxis.getQuadraticFormMatrix();
  linear_term_vector = unit_sphere_xaxis.getLinearTermVector();

  ref_linear_term_vector =  Geometry::createVector<ScalarType>( 2.0, 0.0, 0.0 );
  ref_quad_form_matrix.identity();
  ref_constant_term = 0.0;

  TEST_EQUALITY( quad_form_matrix, ref_quad_form_matrix );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector(),
				ref_linear_term_vector(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_FLOATING_EQUALITY( unit_sphere_xaxis.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );

  // Create a unit sphere centered at (0, -1, 0) from the unit sphere at origin
  Geometry::Surface<OrdinalType,ScalarType> unit_sphere_yaxis(
						    3,
						    unit_sphere,
						    yaxis_translation_vector );

  quad_form_matrix = unit_sphere_yaxis.getQuadraticFormMatrix();
  linear_term_vector = unit_sphere_yaxis.getLinearTermVector();

  ref_linear_term_vector = Geometry::createVector<ScalarType>( 0.0, 2.0, 0.0 );
  ref_quad_form_matrix.identity();
  ref_constant_term = 0.0;

  TEST_EQUALITY( quad_form_matrix, ref_quad_form_matrix );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector(),
				ref_linear_term_vector(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_FLOATING_EQUALITY( unit_sphere_yaxis.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );

  // Create a unit sphere centered at (0, 0, -1) from the unit sphere at origin
  Geometry::Surface<OrdinalType,ScalarType> unit_sphere_zaxis(
						    3,
						    unit_sphere,
						    zaxis_translation_vector );

  quad_form_matrix = unit_sphere_zaxis.getQuadraticFormMatrix();
  linear_term_vector = unit_sphere_zaxis.getLinearTermVector();

  ref_linear_term_vector = Geometry::createVector<ScalarType>( 0.0, 0.0, 2.0 );
  ref_quad_form_matrix.identity();
  ref_constant_term = 0.0;

  TEST_EQUALITY( quad_form_matrix, ref_quad_form_matrix );
  TEST_COMPARE_FLOATING_ARRAYS( linear_term_vector(),
				ref_linear_term_vector(),
				Teuchos::ScalarTraits<ScalarType>::prec() );
  TEST_FLOATING_EQUALITY( unit_sphere_zaxis.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );
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
  Geometry::Surface<OrdinalType,ScalarType> plane( 0,
						 5, 4, 3,
						 0 );
  // Unit skew cylinder with axis direction (1/2,1/2,sqrt(2)/2)
  Geometry::Surface<OrdinalType,ScalarType> skew_cylinder( 1,
							 0.5, 1.0, 0.5,
							 0.0, 0.0, 1.0,
							 0.0, 0.0, 0.0,
							 -1.0 );

  // create the xy-plane by rotating the general plane
  Geometry::Vector<ScalarType> desired_direction( 0.0, 0.0, 1.0 );
  Geometry::Vector<ScalarType> current_direction =
    plane.getUnitNormalAtPoint( 0.0, 0.0, 0.0 );
  Geometry::Matrix<ScalarType> rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( desired_direction,
						 current_direction );

  Geometry::Surface<OrdinalType,ScalarType> xy_plane( 2,
						    plane,
						    rotation_matrix );

  Geometry::Matrix<ScalarType> quad_form_matrix =
    xy_plane.getQuadraticFormMatrix();
  Geometry::Vector<ScalarType> linear_term_vector =
    xy_plane.getLinearTermVector();

  Geometry::Matrix<ScalarType> ref_quad_form_matrix;
  Geometry::Vector<ScalarType> ref_linear_term_vector( 0.0, 0.0, 1.0 );
  ScalarType ref_constant_term = 0.0;

  TEST_EQUALITY( quad_form_matrix, ref_quad_form_matrix );
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
				    linear_term_vector(),
				    ref_linear_term_vector(),
				    Teuchos::ScalarTraits<ScalarType>::prec());
  TEST_FLOATING_EQUALITY( xy_plane.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );

  // create a cylinder parallel to z-axis centered at (0.0,0.0)
  Geometry::Vector<ScalarType> eigenvalues =
  Geometry::LinearAlgebra::computeEigenvaluesAndEigenvectors(
					skew_cylinder.getQuadraticFormMatrix(),
  					rotation_matrix );
  if( !eigenvalues.hasUniqueElements() )
    Geometry::LinearAlgebra::realignEigenvectors( eigenvalues, rotation_matrix );

  Geometry::Surface<OrdinalType,ScalarType> z_cylinder( 3,
						      skew_cylinder,
						      rotation_matrix );

  quad_form_matrix = z_cylinder.getQuadraticFormMatrix();
  linear_term_vector = z_cylinder.getLinearTermVector();

  ref_quad_form_matrix = Geometry::createMatrix<ScalarType>( 1.0,
							   0.0, 1.0,
							   0.0, 0.0, 0.0 );

  ref_linear_term_vector = Geometry::createVector<ScalarType>( 0.0, 0.0, 0.0 );
  ref_constant_term = -1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
				    quad_form_matrix(),
				    ref_quad_form_matrix(),
				    Teuchos::ScalarTraits<ScalarType>::prec());
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
				    linear_term_vector(),
				    ref_linear_term_vector(),
				    Teuchos::ScalarTraits<ScalarType>::prec());
  TEST_FLOATING_EQUALITY( z_cylinder.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( Surface, constructor_with_rotation_matrix );

//---------------------------------------------------------------------------//
// Check that a surface can be transformed with a rotation matrix and
// a translation vector
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Surface,
				   constructor_general_transformation,
				   OrdinalType,
				   ScalarType )
{
  // General plane.
  Geometry::Surface<OrdinalType,ScalarType> plane( 0,
						 5, 4, 3,
						 -2 );

  // create the xy-plane by transforming the general plane
  Geometry::Vector<ScalarType> desired_direction( 0.0, 0.0, 1.0 );
  Geometry::Vector<ScalarType> current_direction =
    plane.getUnitNormalAtPoint( 0.0, 0.5, 0.0 );
  Geometry::Matrix<ScalarType> rotation_matrix =
    Geometry::createRotationMatrixFromUnitVectors( desired_direction,
						 current_direction );
  Geometry::Vector<ScalarType> translation_vector =
    Geometry::createZeroingVector( current_direction,
				 plane.getConstantTerm() );

  Geometry::Surface<OrdinalType,ScalarType> xy_plane( 2,
						    plane,
						    rotation_matrix,
						    translation_vector );

  Geometry::Matrix<ScalarType> quad_form_matrix =
    xy_plane.getQuadraticFormMatrix();
  Geometry::Vector<ScalarType> linear_term_vector =
    xy_plane.getLinearTermVector();

  Geometry::Matrix<ScalarType> ref_quad_form_matrix;
  Geometry::Vector<ScalarType> ref_linear_term_vector( 0.0, 0.0, 1.0 );
  ScalarType ref_constant_term = 0.0;

  TEST_EQUALITY( quad_form_matrix, ref_quad_form_matrix );
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
				    linear_term_vector(),
				    ref_linear_term_vector(),
				    Teuchos::ScalarTraits<ScalarType>::prec());
  TEST_FLOATING_EQUALITY( xy_plane.getConstantTerm(),
			  ref_constant_term,
			  Teuchos::ScalarTraits<ScalarType>::prec() );

  // Unit skew cylinder with axis dir (1/2,1/2,sqrt(2)/2) off origin
  Geometry::Surface<OrdinalType,ScalarType> skew_cylinder(
					      1,
					      0.5, 1.0, 0.5,
					      0.0, 0.0, 1.0,
					      -2+sqrt(2.0), -4.0, -2+sqrt(2.0),
					      6-2*sqrt(2.0) );

  // create a cylinder parallel to z-axis centered at (1.0,1.0)
  Geometry::Vector<ScalarType> eigenvalues =
  Geometry::LinearAlgebra::computeEigenvaluesAndEigenvectors(
  					skew_cylinder.getQuadraticFormMatrix(),
  					rotation_matrix );
  if( !eigenvalues.hasUniqueElements() )
    Geometry::LinearAlgebra::realignEigenvectors( eigenvalues, rotation_matrix );

  translation_vector = Geometry::createVector<ScalarType>( 1, 1, 1 );

  Geometry::Surface<OrdinalType,ScalarType> z_cylinder( 3,
  						      skew_cylinder,
  						      rotation_matrix,
						      translation_vector );

  quad_form_matrix = z_cylinder.getQuadraticFormMatrix();
  linear_term_vector = z_cylinder.getLinearTermVector();

  ref_quad_form_matrix = Geometry::createMatrix<ScalarType>( 1.0,
  							   0.0, 1.0,
  							   0.0, 0.0, 0.0 );

  ref_linear_term_vector = Geometry::createVector<ScalarType>( 2.0, 2.0, 0.0 );
  ref_constant_term = 1.0;

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
  				    quad_form_matrix(),
  				    ref_quad_form_matrix(),
  				    Teuchos::ScalarTraits<ScalarType>::prec());
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS(
  				    linear_term_vector(),
  				    ref_linear_term_vector(),
  				    Teuchos::ScalarTraits<ScalarType>::prec());
  TEST_FLOATING_EQUALITY( z_cylinder.getConstantTerm(),
  			  ref_constant_term,
  			  Teuchos::ScalarTraits<ScalarType>::prec() );
}

UNIT_TEST_INSTANTIATION( Surface, constructor_general_transformation );

//---------------------------------------------------------------------------//
// end tstSurface.cpp
//---------------------------------------------------------------------------//
