//---------------------------------------------------------------------------//
//!
//! \file   tstIntersectionPoint.cpp
//! \author Alex Robinson
//! \brief  IntersectionPoint unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_IntersectionPoint.hpp"
#include "Geometry_Vector.hpp"
#include "Geometry_Cell.hpp"
#include "Geometry_Surface.hpp"

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
// Testing Functions.
//---------------------------------------------------------------------------//
// Create a concave polyhedron centered on the origin
// |\  /|  z
// | \/ |  |
// |_ _ |  .__ y
template<typename Cell>
void createConcavePolyhedronOnOrigin( Teuchos::RCP<Cell> &cell_ptr )
{
  typedef typename Cell::surfaceOrdinalType ordinalType;
  typedef typename Cell::scalarType scalarType;
  typedef Geometry::Surface<ordinalType,scalarType> Surface;

  // Create the cell definition
  std::string cell_definition( "-1n2n-3n4n(-5u-6)n7" );

  // Create the surface map
  std::map<ordinalType,Teuchos::RCP<Surface> > surface_map;

  // Create the cell surfaces:
  // Surface 1: x = 2
  Teuchos::RCP<Surface> surface_ptr( new Surface( 1,
						  1, 0, 0,
						  -2 ) );
  surface_map[1] = surface_ptr;

  // Surface 2: x = -2
  surface_ptr.reset( new Surface( 2,
				  1, 0, 0,
				  2 ) );
  surface_map[2] = surface_ptr;

  // Surface 3: y = 4
  surface_ptr.reset( new Surface( 3,
				  0, 1, 0,
				  -4 ) );
  surface_map[3] = surface_ptr;

  // Surface 4: y = -4
  surface_ptr.reset( new Surface( 4,
				  0, 1, 0,
				  4 ) );
  surface_map[4] = surface_ptr;

  // Surface 5: 2z-y = 0
  surface_ptr.reset( new Surface( 5,
				  0, -1, 2,
				  0 ) );
  surface_map[5] = surface_ptr;

  // Surface 6: 2z+y = 0
  surface_ptr.reset( new Surface( 6,
				  0, 1, 2,
				  0 ) );
  surface_map[6] = surface_ptr;

  // Surface 7: z = -1
  surface_ptr.reset( new Surface( 7,
				  0, 0, 1,
				  1 ) );
  surface_map[7] = surface_ptr;

  // Create the cell
  cell_ptr.reset( new Cell( 0, cell_definition, surface_map ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that two intersection points can be compared equal
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   equality,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a( 0.0, 0.0, 0.0,
							     0, 1, 2 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a_copy( point_a );

  TEST_ASSERT( point_a == point_a_copy );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, equality );

//---------------------------------------------------------------------------//
// Check that two intersection points can be compared as unequal
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   inequality,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a( 0.0, 0.0, 0.0,
							     0, 1, 2 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_b( 0.0, 0.0, 0.0,
							     3, 4, 5 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_c( 1.0, 1.0, 1.0,
							     4, 5, 6 );

  TEST_ASSERT( point_a != point_b );
  TEST_ASSERT( point_a != point_c );
  TEST_ASSERT( point_b != point_c );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, inequality );

//---------------------------------------------------------------------------//
// Check that an intersection point can be copied
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   copy_operator,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a( 0.0, 1.0, 2.0,
							     0, 1, 2 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_b( 3.0, 4.0, 5.0,
							     3, 4, 5 );

  TEST_ASSERT( point_a != point_b );

  point_a = point_b;

  TEST_ASSERT( point_a == point_b );
}

//---------------------------------------------------------------------------//
// Check that the coordinates of the intersection point can be accessed using
// the square bracket operator
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   coordinate_access_operator,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  Geometry::IntersectionPoint<OrdinalType,ScalarType> test_point( 0.0, 1.0, 0.0,
								1, 2, 3 );
  TEST_EQUALITY_CONST( test_point[0], ST::zero() );
  TEST_EQUALITY_CONST( test_point[1], ST::one() );
  TEST_EQUALITY_CONST( test_point[2], ST::zero() );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, coordinate_access_operator );

//---------------------------------------------------------------------------//
// Check that the coordinates of the intersection point can be accessed using
// the respective get method
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   getCoordinate,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  Geometry::IntersectionPoint<OrdinalType,ScalarType> test_point( 0.0, 1.0, 0.0,
								1, 2, 3 );

  TEST_EQUALITY_CONST( test_point.getXCoordinate(), ST::zero() );
  TEST_EQUALITY_CONST( test_point.getYCoordinate(), ST::one() );
  TEST_EQUALITY_CONST( test_point.getZCoordinate(), ST::zero() );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, getCoordinate );

//---------------------------------------------------------------------------//
// Check that the surface ids of the intersection point can be accessed using
// the respective get method
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   getSurfaceId,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  Geometry::IntersectionPoint<OrdinalType,ScalarType> test_point( 0.0, 1.0, 0.0,
								1, 2, 3 );

  OrdinalType ref_first_id = 1;
  OrdinalType ref_second_id = 2;
  OrdinalType ref_third_id = 3;

  TEST_EQUALITY( test_point.getFirstSurfaceId(), ref_first_id );
  TEST_EQUALITY( test_point.getSecondSurfaceId(), ref_second_id );
  TEST_EQUALITY( test_point.getThirdSurfaceId(), ref_third_id );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, getSurfaceId );

//---------------------------------------------------------------------------//
// Check that the point coordinates can be returned as a vector
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   getRawPoint,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> test_point( 0.0, 1.0, 2.0,
								1, 2, 3 );

  Geometry::Vector<ScalarType> test_point_coords( test_point.getRawPoint() );

  Geometry::Vector<ScalarType> ref_coords( 0.0, 1.0, 2.0 );

  TEST_EQUALITY( test_point_coords, ref_coords );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, getRawPoint );

//---------------------------------------------------------------------------//
// Check that the point can be set and tested as a star corner
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   set_test_star_corner,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType>
    normal_point( 0.0, 1.0, 2.0,
		  1, 2, 3 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> star_point( 0.0, 1.0, 2.0,
								1, 2, 3,
								true );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point( 0.0, 1.0, 2.0,
							   1, 2, 3 );
  point.setAsStarCorner();

  TEST_ASSERT( !normal_point.isStarCorner() );
  TEST_ASSERT( star_point.isStarCorner() );
  TEST_ASSERT( point.isStarCorner() );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, set_test_star_corner );

//---------------------------------------------------------------------------//
// Check that two intersection points can be tested as on the same plane
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   isOnSamePlane,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a( 0.0, 0.0, 0.0,
							     1, 2, 3 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_b( 1.0, 0.0, 0.0,
							     1, 4, 5 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_c( 0.0, 1.0, 0.0,
							     6, 2, 3 );

  TEST_ASSERT( point_a.isOnSamePlane( point_b ) );
  TEST_ASSERT( point_a.isOnSamePlane( point_c ) );
  TEST_ASSERT( !point_b.isOnSamePlane( point_c ) );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, isOnSamePlane );

//---------------------------------------------------------------------------//
// Check that two intersection points can be tested as on the same curve
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   isOnSameCurve,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a( 0.0, 0.0, 0.0,
							     1, 2, 3 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_b( 1.0, 0.0, 0.0,
							     1, 4, 5 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_c( 0.0, 1.0, 0.0,
							     6, 2, 3 );

  TEST_ASSERT( !point_a.isOnSameCurve( point_b ) );
  TEST_ASSERT( point_a.isOnSameCurve( point_c ) );
  TEST_ASSERT( !point_b.isOnSameCurve( point_c ) );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, isOnSameCurve );

//---------------------------------------------------------------------------//
// Check that the unshared surface id between two points on a curve can be
// found
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   getUnsharedSurfaceId,
				   OrdinalType,
				   ScalarType )
{
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_a( 0.0, 0.0, 0.0,
							     1, 2, 3 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_b( 1.0, 0.0, 0.0,
							     6, 2, 3 );

  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_c( 0.0, 1.0, 0.0,
							     6, 4, 3 );

  OrdinalType unshared_a_b_surface = point_a.getUnsharedSurfaceId( point_b );
  OrdinalType unshared_b_a_surface = point_b.getUnsharedSurfaceId( point_a );
  OrdinalType unshared_b_c_surface = point_b.getUnsharedSurfaceId( point_c );
  OrdinalType unshared_c_b_surface = point_c.getUnsharedSurfaceId( point_b );

  OrdinalType ref_unshared_a_b_surface = 1;
  OrdinalType ref_unshared_b_a_surface = 6;
  OrdinalType ref_unshared_b_c_surface = 2;
  OrdinalType ref_unshared_c_b_surface = 4;

  TEST_EQUALITY( unshared_a_b_surface, ref_unshared_a_b_surface );
  TEST_EQUALITY( unshared_b_a_surface, ref_unshared_b_a_surface );
  TEST_EQUALITY( unshared_b_c_surface, ref_unshared_b_c_surface );
  TEST_EQUALITY( unshared_c_b_surface, ref_unshared_c_b_surface );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, getUnsharedSurfaceId );

//---------------------------------------------------------------------------//
// Check that an intersection point can be test as real in relation to a cell
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPoint,
				   isRealIntersectionPoint,
				   OrdinalType,
				   ScalarType )
{
  // Create the test cell
  Teuchos::RCP<Geometry::Cell<unsigned,OrdinalType,ScalarType> > cell_ptr;
  createConcavePolyhedronOnOrigin( cell_ptr );

  // Create all corners of the cell
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_1( 2.0, 4.0, 2.0,
							     1, 3, 5 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_2( 2.0, 0.0, 0.0,
							     1, 5, 6 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_3( 2.0, -4.0, 2.0,
							     1, 4, 6 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_4( 2.0, -4.0, -1.0,
							     1, 4, 7 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_5( 2.0, 4.0, -1.0,
							     1, 3, 7 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_6( -2.0, 4.0, 2.0,
							     2, 3, 5 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_7( -2.0, 0.0, 0.0,
							     2, 5, 6 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_8( -2.0, -4.0, 2.0,
							     2, 4, 6 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_9( -2.0, -4.0, -1.0,
							     2, 4, 7 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_10( -2.0, 4.0, -1.0,
							      2, 3, 5 );

  // Create all of the fictitious corners not on the cell
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_11( 2.0, 4.0, -2.0,
							      1, 3, 6 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_12( -2.0, 4.0, -2.0,
							      2, 3, 6 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_13( 2.0, -4.0, -2.0,
							      1, 4, 5 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_14( -2.0, -4.0, -2.0,
							      2, 4, 5 );

  // Create all of the fictitious corners on the cell
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_15( 2.0, 2.0, -1.0,
							      1, 6, 7 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_16( -2.0, 2.0, -1.0,
							      2, 6, 7 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_17( 2.0, -2.0, -1.0,
							      1, 5, 7 );
  Geometry::IntersectionPoint<OrdinalType,ScalarType> point_18( -2.0, -2.0, -1.0,
							      2, 5, 7 );

  TEST_ASSERT( cell_ptr->isOn( point_1.getRawPoint() ) );
  TEST_ASSERT( point_1.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_2.getRawPoint() ) );
  TEST_ASSERT( point_2.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_3.getRawPoint() ) );
  TEST_ASSERT( point_3.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_4.getRawPoint() ) );
  TEST_ASSERT( point_4.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_5.getRawPoint() ) );
  TEST_ASSERT( point_5.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_6.getRawPoint() ) );
  TEST_ASSERT( point_6.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_7.getRawPoint() ) );
  TEST_ASSERT( point_7.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_8.getRawPoint() ) );
  TEST_ASSERT( point_8.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_9.getRawPoint() ) );
  TEST_ASSERT( point_9.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_10.getRawPoint() ) );
  TEST_ASSERT( point_10.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( !cell_ptr->isOn( point_11.getRawPoint() ) );
  TEST_ASSERT( !point_11.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( !cell_ptr->isOn( point_12.getRawPoint() ) );
  TEST_ASSERT( !point_12.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( !cell_ptr->isOn( point_13.getRawPoint() ) );
  TEST_ASSERT( !point_13.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( !cell_ptr->isOn( point_14.getRawPoint() ) );
  TEST_ASSERT( !point_14.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_15.getRawPoint() ) );
  TEST_ASSERT( !point_15.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_16.getRawPoint() ) );
  TEST_ASSERT( !point_16.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_17.getRawPoint() ) );
  TEST_ASSERT( !point_17.isRealIntersectionPoint( *cell_ptr ) );

  TEST_ASSERT( cell_ptr->isOn( point_18.getRawPoint() ) );
  TEST_ASSERT( !point_18.isRealIntersectionPoint( *cell_ptr ) );
}

UNIT_TEST_INSTANTIATION( IntersectionPoint, isRealIntersectionPoint );

//---------------------------------------------------------------------------//
// end tstIntersectionPoint.cpp
//---------------------------------------------------------------------------//

