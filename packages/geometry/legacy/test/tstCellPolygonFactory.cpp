//---------------------------------------------------------------------------//
//!
//! \file   tstCellPolygonFactory.cpp
//! \author Alex Robinson
//! \brief  CellPolygonFactory unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_CellPolygonFactory.hpp"
#include "Geometry_Cell.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, short, short, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, long, long, double )

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename Cell>
class TestCellPolygonFactory : public Geometry::CellPolygonFactory<Cell>
{
public:
  TestCellPolygonFactory( const Teuchos::RCP<Cell> &cell_ptr )
    : Geometry::CellPolygonFactory<Cell>( cell_ptr )
  { /* ... */ }

  virtual ~TestCellPolygonFactory()
  { /* ... */ }

  using Geometry::CellPolygonFactory<Cell>::initializePolygonCorners;
  using Geometry::CellPolygonFactory<Cell>::cornerTripletNeedsReversing;
  using Geometry::CellPolygonFactory<Cell>::allPointsOnSamePlane;
  using Geometry::CellPolygonFactory<Cell>::getPlaneOfPolygonId;
  using Geometry::CellPolygonFactory<Cell>::getLexicographicallyLargestPoint;
  using Geometry::CellPolygonFactory<Cell>::getNextPolygonCorner;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Create the testing cell
template<typename Cell>
void createTestingCell( Teuchos::RCP<Cell> &cell_ptr )
{
  typedef typename Cell::surfaceOrdinalType ordinalType;
  typedef typename Cell::scalarType scalarType;
  typedef Geometry::Surface<ordinalType,scalarType> Surface;

  // Create the cell definition
  std::string cell_definition( "(-1n4n-7n10n-11n13n(2u-3u8u-9))u(-1n4n-5n6n-12n13)" );

  // Create the surface map
  std::map<ordinalType,Teuchos::RCP<Surface> > surface_map;

  // Create the cell surfaces:
  // Surface 1: x = 2
  Teuchos::RCP<Surface> surface_ptr( new Surface( 1,
						  1, 0, 0,
						  -2 ) );
  surface_map[1] = surface_ptr;

  // Surface 2: x = 1
  surface_ptr.reset( new Surface( 2,
				  1, 0, 0,
				  -1 ) );
  surface_map[2] = surface_ptr;

  // Surface 3: x = -1
  surface_ptr.reset( new Surface( 3,
				  1, 0, 0,
				  1 ) );
  surface_map[3] = surface_ptr;

  // Surface 4: x = -2
  surface_ptr.reset( new Surface( 4,
				  1, 0, 0,
				  2 ) );
  surface_map[4] = surface_ptr;

  // Surface 5: y = 7
  surface_ptr.reset( new Surface( 5,
				  0, 1, 0,
				  -7 ) );
  surface_map[5] = surface_ptr;

  // Surface 6: y = 3
  surface_ptr.reset( new Surface( 6,
				  0, 1, 0,
				  -3 ) );
  surface_map[6] = surface_ptr;

  // Surface 7: y = 2
  surface_ptr.reset( new Surface( 7,
				  0, 1, 0,
				  -2 ) );
  surface_map[7] = surface_ptr;

  // Surface 8: y = 1
  surface_ptr.reset( new Surface( 8,
				  0, 1, 0,
				  -1 ) );
  surface_map[8] = surface_ptr;

  // Surface 9: y = -1
  surface_ptr.reset( new Surface( 9,
				  0, 1, 0,
				  1 ) );
  surface_map[9] = surface_ptr;

  // Surface 10: y = -2
  surface_ptr.reset( new Surface( 10,
				  0, 1, 0,
				  2 ) );
  surface_map[10] = surface_ptr;

  // Surface 11: z = 2
  surface_ptr.reset( new Surface( 11,
				  0, 0, 1,
				  -2 ) );
  surface_map[11] = surface_ptr;

  // Surface 12: z = 0
  surface_ptr.reset( new Surface( 12,
				  0, 0, 1,
				  0 ) );
  surface_map[12] = surface_ptr;

  // Surface 13: z = -2
  surface_ptr.reset( new Surface( 13,
				  0, 0, 1,
				  2 ) );
  surface_map[13] = surface_ptr;

  // Create the cell
  cell_ptr.reset( new Cell( 0, cell_definition, surface_map ) );
}

// Create the polygon corners on surface 1
template<typename IntersectionPoint>
void createSurface1PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (2,-2,-2)
  IntersectionPoint corner_1( 2.0, -2.0, -2.0,
			      1, 10, 13 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2,7,-2)
  IntersectionPoint corner_2( 2.0, 7.0, -2.0,
			      1, 5, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2,3,0)
  IntersectionPoint corner_3( 2.0, 3.0, 0.0,
			      1, 6, 12 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (2,3,-2)
  IntersectionPoint corner_4( 2.0, 3.0, -2.0,
			      1, 6, 13 );
  polygon_corners.push_back( corner_4 );

  // Fifth point at (2,2,-2)
  IntersectionPoint corner_5( 2.0, 2.0, -2.0,
			      1, 7, 13 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (2,-2,2)
  IntersectionPoint corner_6( 2.0, -2.0, 2.0,
			      1, 10, 11 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (2,2,2)
  IntersectionPoint corner_7( 2.0, 2.0, 2.0,
			      1, 7, 11 );
  polygon_corners.push_back( corner_7 );

  // Eighth point at (2,7,0)
  IntersectionPoint corner_8( 2.0, 7.0, 0.0,
			      1, 5, 12 );
  polygon_corners.push_back( corner_8 );
}

// Create the polygon corners on surface 2
template<typename IntersectionPoint>
void createSurface2PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1,1,2)
  IntersectionPoint corner_1( 1.0, 1.0, 2.0,
			      2, 8, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (1,1,-2)
  IntersectionPoint corner_2( 1.0, 1.0, -2.0,
			      2, 8, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1,-1,-2)
  IntersectionPoint corner_3( 1.0, -1.0, -2.0,
			      2, 9, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1,-1,2)
  IntersectionPoint corner_4( 1.0, -1.0, 2.0,
			      2, 9, 11 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 3
template<typename IntersectionPoint>
void createSurface3PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-1,1,2)
  IntersectionPoint corner_1( -1.0, 1.0, 2.0,
			      3, 8, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1,-1,2)
  IntersectionPoint corner_2( -1.0, -1.0, 2.0,
			      3, 9, 11 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1,-1,-2)
  IntersectionPoint corner_3( -1.0, -1.0, -2.0,
			      3, 9, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-1,1,-2)
  IntersectionPoint corner_4( -1.0, 1.0, -2.0,
			      3, 8, 13 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 4
template<typename IntersectionPoint>
void createSurface4PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,2,2)
  IntersectionPoint corner_1( -2.0, 2.0, 2.0,
			      4, 7, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-2,-2,2)
  IntersectionPoint corner_2( -2.0, -2.0, 2.0,
			      4, 10, 11 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-2,-2,-2)
  IntersectionPoint corner_3( -2.0, -2.0, -2.0,
			      4, 10, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-2,2,-2)
  IntersectionPoint corner_4( -2.0, 2.0, -2.0,
			      4, 7, 13 );
  polygon_corners.push_back( corner_4 );

  // Fifth point at (-2,3,0)
  IntersectionPoint corner_5( -2.0, 3.0, 0.0,
			      4, 6, 12 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (-2,3,-2)
  IntersectionPoint corner_6( -2.0, 3.0, -2.0,
			      4, 6, 13 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (-2,7,-2)
  IntersectionPoint corner_7( -2.0, 7.0, -2.0,
			      4, 5, 13 );
  polygon_corners.push_back( corner_7 );

  // Eighth point at (-2,7,0)
  IntersectionPoint corner_8( -2.0, 7.0, 0.0,
			      4, 5, 12 );
  polygon_corners.push_back( corner_8 );
}

// Create the polygon corners on surface 5
template<typename IntersectionPoint>
void createSurface5PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,7,0)
  IntersectionPoint corner_1( -2.0, 7.0, 0.0,
			      4, 5, 12 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2,7,0)
  IntersectionPoint corner_2( 2.0, 7.0, 0.0,
			      1, 5, 12 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2,7,-2)
  IntersectionPoint corner_3( 2.0, 7.0, -2.0,
			      1, 5, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-2,7,-2)
  IntersectionPoint corner_4( -2.0, 7.0, -2.0,
			      4, 5, 13 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 6
template<typename IntersectionPoint>
void createSurface6PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (2,3,0)
  IntersectionPoint corner_1( 2.0, 3.0, 0.0,
			      1, 6, 12 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2,3,-2)
  IntersectionPoint corner_2( 2.0, 3.0, -2.0,
			      1, 6, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-2,3,-2)
  IntersectionPoint corner_3( -2.0, 3.0, -2.0,
			      4, 6, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-2,3,0)
  IntersectionPoint corner_4( -2.0, 3.0, 0.0,
			      4, 6, 12 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 7
template<typename IntersectionPoint>
void createSurface7PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,2,2)
  IntersectionPoint corner_1( -2.0, 2.0, 2.0,
			      4, 7, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2,2,-2)
  IntersectionPoint corner_2( 2.0, 2.0, -2.0,
			      1, 7, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2,2,2)
  IntersectionPoint corner_3( 2.0, 2.0, 2.0,
			      1, 7, 11 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-2,2,-2)
  IntersectionPoint corner_4( -2.0, 2.0, -2.0,
			      4, 7, 13 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 8
template<typename IntersectionPoint>
void createSurface8PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1,1,2)
  IntersectionPoint corner_1( 1.0, 1.0, 2.0,
			      2, 8, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1,1,2)
  IntersectionPoint corner_2( -1.0, 1.0, 2.0,
			      3, 8, 11 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1,1,-2)
  IntersectionPoint corner_3( 1.0, 1.0, -2.0,
			      2, 8, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-1,1,-2)
  IntersectionPoint corner_4( -1.0, 1.0, -2.0,
			      3, 8, 13 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 9
template<typename IntersectionPoint>
void createSurface9PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1,-1,-2)
  IntersectionPoint corner_1( 1.0, -1.0, -2.0,
			      2, 9, 13 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1,-1,-2)
  IntersectionPoint corner_2( -1.0, -1.0, -2.0,
			      3, 9, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1,-1,2)
  IntersectionPoint corner_3( 1.0, -1.0, 2.0,
			      2, 9, 11 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-1,-1,2)
  IntersectionPoint corner_4( -1.0, -1.0, 2.0,
			      3, 9, 11 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 10
template<typename IntersectionPoint>
void createSurface10PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,-2,2)
  IntersectionPoint corner_1( -2.0, -2.0, 2.0,
			      4, 10, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-2,-2,-2)
  IntersectionPoint corner_2( -2.0, -2.0, -2.0,
			      4, 10, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2,-2,2)
  IntersectionPoint corner_3( 2.0, -2.0, 2.0,
			      1, 10, 11 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (2,-2,-2)
  IntersectionPoint corner_4( 2.0, -2.0, -2.0,
			      1, 10, 13 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 11
template<typename IntersectionPoint>
void createSurface11PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,-2,2)
  IntersectionPoint corner_1( -2.0, -2.0, 2.0,
			      4, 10, 11 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1,-1,2)
  IntersectionPoint corner_2( -1.0, -1.0, 2.0,
			      3, 9, 11 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1,1,2)
  IntersectionPoint corner_3( 1.0, 1.0, 2.0,
			      2, 8, 11 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (2,2,2)
  IntersectionPoint corner_4( 2.0, 2.0, 2.0,
			      1, 7, 11 );
  polygon_corners.push_back( corner_4 );

  // Fifth point at (2,-2,2)
  IntersectionPoint corner_5( 2.0, -2.0, 2.0,
			      1, 10, 11 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (1,-1,2)
  IntersectionPoint corner_6( 1.0, -1.0, 2.0,
			      2, 9, 11 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (-1,1,2)
  IntersectionPoint corner_7( -1.0, 1.0, 2.0,
			      3, 8, 11 );
  polygon_corners.push_back( corner_7 );

  // Eighth point at (-2,2,2)
  IntersectionPoint corner_8( -2.0, 2.0, 2.0,
			      4, 7, 11 );
  polygon_corners.push_back( corner_8 );
}

// Create the polygon corners on surface 12
template<typename IntersectionPoint>
void createSurface12PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,7,0)
  IntersectionPoint corner_1( -2.0, 7.0, 0.0,
			      4, 5, 12 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-2,3,0)
  IntersectionPoint corner_2( -2.0, 3.0, 0.0,
			      4, 6, 12 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2,3,0)
  IntersectionPoint corner_3( 2.0, 3.0, 0.0,
			      1, 6, 12 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (2,7,0)
  IntersectionPoint corner_4( 2.0, 7.0, 0.0,
			      1, 5, 12 );
  polygon_corners.push_back( corner_4 );
}

// Create the polygon corners on surface 13
template<typename IntersectionPoint>
void createSurface13PolygonCorners(
				std::list<IntersectionPoint> &polygon_corners )
{
  polygon_corners.clear();

  // First point at (-2,7,-2)
  IntersectionPoint corner_1( -2.0, 7.0, -2.0,
			      4, 5, 13 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-2,3,-2)
  IntersectionPoint corner_2( -2.0, 3.0, -2.0,
			      4, 6, 13 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-2,2,-2)
  IntersectionPoint corner_3( -2.0, 2.0, -2.0,
			      4, 7, 13 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-1,1,-2)
  IntersectionPoint corner_4( -1.0, 1.0, -2.0,
			      3, 8, 13 );
  polygon_corners.push_back( corner_4 );

  // Fifth point at (1,-1,-2)
  IntersectionPoint corner_5( 1.0, -1.0, -2.0,
			      2, 9, 13 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (2,-2,-2)
  IntersectionPoint corner_6( 2.0, -2.0, -2.0,
			      1, 10, 13 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (-2,-2,-2)
  IntersectionPoint corner_7( -2.0, -2.0, -2.0,
			      4, 10, 13 );
  polygon_corners.push_back( corner_7 );

  // Eighth point at (-1,-1,-2)
  IntersectionPoint corner_8( -1.0, -1.0, -2.0,
			      3, 9, 13 );
  polygon_corners.push_back( corner_8 );

  // Ninth point at (1,1,-2)
  IntersectionPoint corner_9( 1.0, 1.0, -2.0,
			      2, 8, 13 );
  polygon_corners.push_back( corner_9 );

  // Tenth point at (2,2,-2)
  IntersectionPoint corner_10( 2.0, 2.0, -2.0,
			       1, 7, 13 );
  polygon_corners.push_back( corner_10 );

  // Eleventh point at (2,3,-2)
  IntersectionPoint corner_11( 2.0, 3.0, -2.0,
			       1, 6, 13 );
  polygon_corners.push_back( corner_11 );

  // Twelfth point at (2,7,-2)
  IntersectionPoint corner_12( 2.0, 7.0, -2.0,
			       1, 5, 13 );
  polygon_corners.push_back( corner_12 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that all points in the list can be tested as being on the same plane
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   allPointsOnSamePlane,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef TestCellPolygonFactory<Cell> CellPolygonFactory;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  std::list<IntersectionPoint> polygon_1_corners;
  std::list<IntersectionPoint> polygon_7_corners;
  std::list<IntersectionPoint> polygon_11_corners;
  std::list<IntersectionPoint> polygon_13_corners;

  // Create the lists of polygon corners
  createSurface1PolygonCorners( polygon_1_corners );
  createSurface7PolygonCorners( polygon_7_corners );
  createSurface11PolygonCorners( polygon_11_corners );
  createSurface13PolygonCorners( polygon_13_corners );

  // Create an invalid polygon list
  std::list<IntersectionPoint> invalid_polygon_corners;
  invalid_polygon_corners.push_back( IntersectionPoint( 1.0, 1.0, 1.0,
							1, 2, 3 ) );
  invalid_polygon_corners.push_back( IntersectionPoint( 2.0, 2.0, 2.0,
							4, 5, 6 ) );
  invalid_polygon_corners.push_back( IntersectionPoint( 3.0, 3.0, 3.0,
							7, 8, 9 ) );

  TEST_ASSERT( CellPolygonFactory::allPointsOnSamePlane( polygon_1_corners ) );
  TEST_ASSERT( CellPolygonFactory::allPointsOnSamePlane( polygon_7_corners ) );
  TEST_ASSERT( CellPolygonFactory::allPointsOnSamePlane( polygon_11_corners) );
  TEST_ASSERT( CellPolygonFactory::allPointsOnSamePlane( polygon_13_corners) );
  TEST_ASSERT( !CellPolygonFactory::allPointsOnSamePlane(
						   invalid_polygon_corners ) );
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory, allPointsOnSamePlane );

//---------------------------------------------------------------------------//
// Check that the id of the plane of the polygon can be found
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   getPlaneOfPolygonId,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef TestCellPolygonFactory<Cell> CellPolygonFactory;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  std::list<IntersectionPoint> polygon_1_corners;
  std::list<IntersectionPoint> polygon_2_corners;
  std::list<IntersectionPoint> polygon_3_corners;
  std::list<IntersectionPoint> polygon_4_corners;
  std::list<IntersectionPoint> polygon_5_corners;
  std::list<IntersectionPoint> polygon_6_corners;
  std::list<IntersectionPoint> polygon_7_corners;
  std::list<IntersectionPoint> polygon_8_corners;
  std::list<IntersectionPoint> polygon_9_corners;
  std::list<IntersectionPoint> polygon_10_corners;
  std::list<IntersectionPoint> polygon_11_corners;
  std::list<IntersectionPoint> polygon_12_corners;
  std::list<IntersectionPoint> polygon_13_corners;

  // Create the lists of polygon corners
  createSurface1PolygonCorners( polygon_1_corners );
  createSurface2PolygonCorners( polygon_2_corners );
  createSurface3PolygonCorners( polygon_3_corners );
  createSurface4PolygonCorners( polygon_4_corners );
  createSurface5PolygonCorners( polygon_5_corners );
  createSurface6PolygonCorners( polygon_6_corners );
  createSurface7PolygonCorners( polygon_7_corners );
  createSurface8PolygonCorners( polygon_8_corners );
  createSurface9PolygonCorners( polygon_9_corners );
  createSurface10PolygonCorners( polygon_10_corners );
  createSurface11PolygonCorners( polygon_11_corners );
  createSurface12PolygonCorners( polygon_12_corners );
  createSurface13PolygonCorners( polygon_13_corners );

  OrdinalType plane_of_polygon_1_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_1_corners );
  OrdinalType plane_of_polygon_2_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_2_corners );
  OrdinalType plane_of_polygon_3_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_3_corners );
  OrdinalType plane_of_polygon_4_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_4_corners );
  OrdinalType plane_of_polygon_5_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_5_corners );
  OrdinalType plane_of_polygon_6_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_6_corners );
  OrdinalType plane_of_polygon_7_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_7_corners );
  OrdinalType plane_of_polygon_8_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_8_corners );
  OrdinalType plane_of_polygon_9_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_9_corners );
  OrdinalType plane_of_polygon_10_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_10_corners );
  OrdinalType plane_of_polygon_11_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_11_corners );
  OrdinalType plane_of_polygon_12_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_12_corners );
  OrdinalType plane_of_polygon_13_id =
    CellPolygonFactory::getPlaneOfPolygonId( polygon_13_corners );

  OrdinalType ref_plane_of_polygon_1_id = 1;
  OrdinalType ref_plane_of_polygon_2_id = 2;
  OrdinalType ref_plane_of_polygon_3_id = 3;
  OrdinalType ref_plane_of_polygon_4_id = 4;
  OrdinalType ref_plane_of_polygon_5_id = 5;
  OrdinalType ref_plane_of_polygon_6_id = 6;
  OrdinalType ref_plane_of_polygon_7_id = 7;
  OrdinalType ref_plane_of_polygon_8_id = 8;
  OrdinalType ref_plane_of_polygon_9_id = 9;
  OrdinalType ref_plane_of_polygon_10_id = 10;
  OrdinalType ref_plane_of_polygon_11_id = 11;
  OrdinalType ref_plane_of_polygon_12_id = 12;
  OrdinalType ref_plane_of_polygon_13_id = 13;

  TEST_EQUALITY( plane_of_polygon_1_id, ref_plane_of_polygon_1_id );
  TEST_EQUALITY( plane_of_polygon_2_id, ref_plane_of_polygon_2_id );
  TEST_EQUALITY( plane_of_polygon_3_id, ref_plane_of_polygon_3_id );
  TEST_EQUALITY( plane_of_polygon_4_id, ref_plane_of_polygon_4_id );
  TEST_EQUALITY( plane_of_polygon_5_id, ref_plane_of_polygon_5_id );
  TEST_EQUALITY( plane_of_polygon_6_id, ref_plane_of_polygon_6_id );
  TEST_EQUALITY( plane_of_polygon_7_id, ref_plane_of_polygon_7_id );
  TEST_EQUALITY( plane_of_polygon_8_id, ref_plane_of_polygon_8_id );
  TEST_EQUALITY( plane_of_polygon_9_id, ref_plane_of_polygon_9_id );
  TEST_EQUALITY( plane_of_polygon_10_id, ref_plane_of_polygon_10_id );
  TEST_EQUALITY( plane_of_polygon_11_id, ref_plane_of_polygon_11_id );
  TEST_EQUALITY( plane_of_polygon_12_id, ref_plane_of_polygon_12_id );
  TEST_EQUALITY( plane_of_polygon_13_id, ref_plane_of_polygon_13_id );
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory, getPlaneOfPolygonId );

//---------------------------------------------------------------------------//
// Check that the lexicographically largest point can be found
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   getLexicographicallyLargestPoint,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef TestCellPolygonFactory<Cell> CellPolygonFactory;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  std::list<IntersectionPoint> polygon_1_corners;
  std::list<IntersectionPoint> polygon_2_corners;
  std::list<IntersectionPoint> polygon_3_corners;
  std::list<IntersectionPoint> polygon_4_corners;
  std::list<IntersectionPoint> polygon_5_corners;
  std::list<IntersectionPoint> polygon_6_corners;
  std::list<IntersectionPoint> polygon_7_corners;
  std::list<IntersectionPoint> polygon_8_corners;
  std::list<IntersectionPoint> polygon_9_corners;
  std::list<IntersectionPoint> polygon_10_corners;
  std::list<IntersectionPoint> polygon_11_corners;
  std::list<IntersectionPoint> polygon_12_corners;
  std::list<IntersectionPoint> polygon_13_corners;

  // Create the lists of polygon corners
  createSurface1PolygonCorners( polygon_1_corners );
  createSurface2PolygonCorners( polygon_2_corners );
  createSurface3PolygonCorners( polygon_3_corners );
  createSurface4PolygonCorners( polygon_4_corners );
  createSurface5PolygonCorners( polygon_5_corners );
  createSurface6PolygonCorners( polygon_6_corners );
  createSurface7PolygonCorners( polygon_7_corners );
  createSurface8PolygonCorners( polygon_8_corners );
  createSurface9PolygonCorners( polygon_9_corners );
  createSurface10PolygonCorners( polygon_10_corners );
  createSurface11PolygonCorners( polygon_11_corners );
  createSurface12PolygonCorners( polygon_12_corners );
  createSurface13PolygonCorners( polygon_13_corners );

  typename std::list<IntersectionPoint>::iterator largest_corner;

  // Get the lexicographically largest points for each list
  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_1_corners );
  Geometry::Vector<ScalarType> polygon_1_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_2_corners );
  Geometry::Vector<ScalarType> polygon_2_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_3_corners );
  Geometry::Vector<ScalarType> polygon_3_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_4_corners );
  Geometry::Vector<ScalarType> polygon_4_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_5_corners );
  Geometry::Vector<ScalarType> polygon_5_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_6_corners );
  Geometry::Vector<ScalarType> polygon_6_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_7_corners );
  Geometry::Vector<ScalarType> polygon_7_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_8_corners );
  Geometry::Vector<ScalarType> polygon_8_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_9_corners );
  Geometry::Vector<ScalarType> polygon_9_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_10_corners );
  Geometry::Vector<ScalarType> polygon_10_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_11_corners );
  Geometry::Vector<ScalarType> polygon_11_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_12_corners );
  Geometry::Vector<ScalarType> polygon_12_largest_corner =
    largest_corner->getRawPoint();

  largest_corner =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_13_corners );
  Geometry::Vector<ScalarType> polygon_13_largest_corner =
    largest_corner->getRawPoint();

  // Set the reference corners
  Geometry::Vector<ScalarType> ref_polygon_1_largest_corner( 2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_2_largest_corner( 1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_3_largest_corner( -1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_4_largest_corner( -2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_5_largest_corner( 2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_6_largest_corner( 2.0, 3.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_7_largest_corner( 2.0, 2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_8_largest_corner( 1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_9_largest_corner( 1.0, -1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_10_largest_corner( 2.0, -2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_11_largest_corner( 2.0, 2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_12_largest_corner( 2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_13_largest_corner( 2.0, 7.0, -2.0 );

  TEST_EQUALITY( polygon_1_largest_corner, ref_polygon_1_largest_corner );
  TEST_EQUALITY( polygon_2_largest_corner, ref_polygon_2_largest_corner );
  TEST_EQUALITY( polygon_3_largest_corner, ref_polygon_3_largest_corner );
  TEST_EQUALITY( polygon_4_largest_corner, ref_polygon_4_largest_corner );
  TEST_EQUALITY( polygon_5_largest_corner, ref_polygon_5_largest_corner );
  TEST_EQUALITY( polygon_6_largest_corner, ref_polygon_6_largest_corner );
  TEST_EQUALITY( polygon_7_largest_corner, ref_polygon_7_largest_corner );
  TEST_EQUALITY( polygon_8_largest_corner, ref_polygon_8_largest_corner );
  TEST_EQUALITY( polygon_9_largest_corner, ref_polygon_9_largest_corner );
  TEST_EQUALITY( polygon_10_largest_corner, ref_polygon_10_largest_corner );
  TEST_EQUALITY( polygon_11_largest_corner, ref_polygon_11_largest_corner );
  TEST_EQUALITY( polygon_12_largest_corner, ref_polygon_12_largest_corner );
  TEST_EQUALITY( polygon_13_largest_corner, ref_polygon_13_largest_corner );
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory,
			 getLexicographicallyLargestPoint );

//---------------------------------------------------------------------------//
// Check that the next corner of polygon can be found
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   getNextPolygonCorner,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef TestCellPolygonFactory<Cell> CellPolygonFactory;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  std::list<IntersectionPoint> polygon_13_corners;

  // Create the lists of polygon corners
  createSurface13PolygonCorners( polygon_13_corners );

  // Start with the lexicographically largest point
  typename std::list<IntersectionPoint>::iterator current_point =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_13_corners );

  // Find the next point on surface 5
  current_point = CellPolygonFactory::getNextPolygonCorner(5,
							   *current_point,
							   polygon_13_corners);
  IntersectionPoint ref_second_point( -2.0, 7.0, -2.0,
				      4, 5, 13 );

  TEST_EQUALITY( *current_point, ref_second_point );

  // Find the next point on surface 6
  current_point = CellPolygonFactory::getNextPolygonCorner(6,
							   *current_point,
							   polygon_13_corners);
  IntersectionPoint ref_third_point( -2.0, 3.0, -2.0,
				     4, 6, 13 );

  TEST_EQUALITY( *current_point, ref_third_point );

  // Find the next point on surface 1
  current_point = CellPolygonFactory::getNextPolygonCorner(1,
							   *current_point,
							   polygon_13_corners);
  IntersectionPoint ref_fourth_point( 2.0, 3.0, -2.0,
				      1, 6, 13 );

  TEST_EQUALITY( *current_point, ref_fourth_point )
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory, getNextPolygonCorner );

//---------------------------------------------------------------------------//
// Check that the ordering of the points can be tested as needing reversing
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   cornerTripletNeedsReversing,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef TestCellPolygonFactory<Cell> CellPolygonFactory;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  // Create the cell that all polygons lie on
  Teuchos::RCP<Cell> cell;
  createTestingCell( cell );

  // Create the cell polygon factory
  CellPolygonFactory factory( cell );

  // Create the lists of polygon corners
  std::list<IntersectionPoint> polygon_2_corners;
  std::list<IntersectionPoint> polygon_7_corners;
  std::list<IntersectionPoint> polygon_11_corners;

  createSurface2PolygonCorners( polygon_2_corners );
  createSurface7PolygonCorners( polygon_7_corners );
  createSurface11PolygonCorners( polygon_11_corners );

  // Find the lexicographically largest point and the two neighbor points
  // on surface 2
  typename std::list<IntersectionPoint>::iterator largest_point;
  typename std::list<IntersectionPoint>::iterator neighbor_point_a;
  typename std::list<IntersectionPoint>::iterator neighbor_point_b;

  largest_point =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_2_corners );
  neighbor_point_a =
    CellPolygonFactory::getNextPolygonCorner( 9,
					      *largest_point,
					      polygon_2_corners );
  neighbor_point_b =
    CellPolygonFactory::getNextPolygonCorner( 13,
					      *largest_point,
					      polygon_2_corners );

  TEST_ASSERT( factory.cornerTripletNeedsReversing( 2, 11, 8,
						    *neighbor_point_a,
						    *largest_point,
						    *neighbor_point_b ) );

  TEST_ASSERT( !factory.cornerTripletNeedsReversing( 2, 8, 11,
						     *neighbor_point_b,
						     *largest_point,
						     *neighbor_point_a ) );

  // Find the lexicographically largest point and the two neighbor points
  // on surface 7
  largest_point =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_7_corners );
  neighbor_point_a =
    CellPolygonFactory::getNextPolygonCorner( 11,
					      *largest_point,
					      polygon_7_corners );
  neighbor_point_b =
    CellPolygonFactory::getNextPolygonCorner( 1,
					      *largest_point,
					      polygon_7_corners );

  TEST_ASSERT( factory.cornerTripletNeedsReversing( 7, 11, 1,
						    *neighbor_point_a,
						    *largest_point,
						    *neighbor_point_b ) );

  TEST_ASSERT( !factory.cornerTripletNeedsReversing( 7, 1, 11,
						     *neighbor_point_b,
						     *largest_point,
						     *neighbor_point_a ) );
  // Find the lexicographically largest point and the two neighbor points
  // on surface 11
  largest_point =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_11_corners );
  neighbor_point_a =
    CellPolygonFactory::getNextPolygonCorner( 1,
  					      *largest_point,
  					      polygon_11_corners );
  neighbor_point_b =
    CellPolygonFactory::getNextPolygonCorner( 7,
  					      *largest_point,
  					      polygon_11_corners );

  TEST_ASSERT( factory.cornerTripletNeedsReversing( 11, 1, 7,
						    *neighbor_point_a,
						    *largest_point,
						    *neighbor_point_b ) );

  TEST_ASSERT( !factory.cornerTripletNeedsReversing( 11, 7, 1,
						     *neighbor_point_b,
						     *largest_point,
						     *neighbor_point_a ) );

  // Find the lexicographically largest point and the two neighbor points
  // of the subpolygon on surface 11
  // The largest point of the subpolygon is the third largest point
  largest_point = polygon_11_corners.erase( largest_point );
  largest_point =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_11_corners );
  largest_point = polygon_11_corners.erase( largest_point );
  largest_point =
    CellPolygonFactory::getLexicographicallyLargestPoint( polygon_11_corners );

  neighbor_point_a =
    CellPolygonFactory::getNextPolygonCorner( 2,
  					      *largest_point,
  					      polygon_11_corners );
  neighbor_point_b =
    CellPolygonFactory::getNextPolygonCorner( 8,
  					      *largest_point,
  					      polygon_11_corners );

  TEST_ASSERT( !factory.cornerTripletNeedsReversing( 11, 2, 8,
						     *neighbor_point_a,
						     *largest_point,
						     *neighbor_point_b ) );

  TEST_ASSERT( factory.cornerTripletNeedsReversing( 11, 8, 2,
						    *neighbor_point_b,
						    *largest_point,
						    *neighbor_point_a ) );
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory, cornerTripletNeedsReversing );

//---------------------------------------------------------------------------//
// Check that a polygon can be initialized
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   initializePolygonCorners,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef TestCellPolygonFactory<Cell> CellPolygonFactory;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  // Create the cell that all polygons lie on
  Teuchos::RCP<Cell> cell;
  createTestingCell( cell );

  // Create the cell polygon factory
  CellPolygonFactory factory( cell );

  // Create the lists of polygon corners
  std::list<IntersectionPoint> polygon_1_corners;
  std::list<IntersectionPoint> polygon_2_corners;
  std::list<IntersectionPoint> polygon_3_corners;
  std::list<IntersectionPoint> polygon_4_corners;
  std::list<IntersectionPoint> polygon_5_corners;
  std::list<IntersectionPoint> polygon_6_corners;
  std::list<IntersectionPoint> polygon_7_corners;
  std::list<IntersectionPoint> polygon_8_corners;
  std::list<IntersectionPoint> polygon_9_corners;
  std::list<IntersectionPoint> polygon_10_corners;
  std::list<IntersectionPoint> polygon_11_corners;
  std::list<IntersectionPoint> polygon_12_corners;
  std::list<IntersectionPoint> polygon_13_corners;

  createSurface1PolygonCorners( polygon_1_corners );
  createSurface2PolygonCorners( polygon_2_corners );
  createSurface3PolygonCorners( polygon_3_corners );
  createSurface4PolygonCorners( polygon_4_corners );
  createSurface5PolygonCorners( polygon_5_corners );
  createSurface6PolygonCorners( polygon_6_corners );
  createSurface7PolygonCorners( polygon_7_corners );
  createSurface8PolygonCorners( polygon_8_corners );
  createSurface9PolygonCorners( polygon_9_corners );
  createSurface10PolygonCorners( polygon_10_corners );
  createSurface11PolygonCorners( polygon_11_corners );
  createSurface12PolygonCorners( polygon_12_corners );
  createSurface13PolygonCorners( polygon_13_corners );

  typename std::list<IntersectionPoint>::const_iterator first_point,
    second_point, third_point;

  // Initialize polygon 1
  std::list<IntersectionPoint> ordered_polygon_1_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_1_corners,
						  polygon_1_corners,
						  1 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_1_first_point( 2.0, 3.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_1_second_point( 2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_1_third_point( 2.0, 7.0, -2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_1_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_1_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_1_third_point );

  // Initialize polygon 2
  std::list<IntersectionPoint> ordered_polygon_2_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_2_corners,
						  polygon_2_corners,
						  2 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_2_first_point( 1.0, 1.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_2_second_point( 1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_2_third_point( 1.0, -1.0, 2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_2_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_2_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_2_third_point );

  // Initialize polygon 3
  std::list<IntersectionPoint> ordered_polygon_3_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_3_corners,
						  polygon_3_corners,
						  3 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_3_first_point( -1.0, -1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_3_second_point( -1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_3_third_point( -1.0, 1.0, -2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_3_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_3_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_3_third_point );

  // Initialize polygon 4
  std::list<IntersectionPoint> ordered_polygon_4_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_4_corners,
						  polygon_4_corners,
						  4 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_4_first_point( -2.0, 7.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_4_second_point( -2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_4_third_point( -2.0, 3.0, 0.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_4_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_4_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_4_third_point );

  // Initialize polygon 5
  std::list<IntersectionPoint> ordered_polygon_5_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_5_corners,
						  polygon_5_corners,
						  5 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_5_first_point( 2.0, 7.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_5_second_point( 2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_5_third_point( -2.0, 7.0, 0.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_5_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_5_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_5_third_point );

  // Initialize polygon 6
  std::list<IntersectionPoint> ordered_polygon_6_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_6_corners,
						  polygon_6_corners,
						  6 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_6_first_point( -2.0, 3.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_6_second_point( 2.0, 3.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_6_third_point( 2.0, 3.0, -2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_6_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_6_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_6_third_point );

  // Initialize polygon 7
  std::list<IntersectionPoint> ordered_polygon_7_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_7_corners,
						  polygon_7_corners,
						  7 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_7_first_point( 2.0, 2.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_7_second_point( 2.0, 2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_7_third_point( -2.0, 2.0, 2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_7_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_7_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_7_third_point );

  // Initialize polygon 8
  std::list<IntersectionPoint> ordered_polygon_8_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_8_corners,
						  polygon_8_corners,
						  8 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_8_first_point( -1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_8_second_point( 1.0, 1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_8_third_point( 1.0, 1.0, -2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_8_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_8_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_8_third_point );

  // Initialize polygon 9
  std::list<IntersectionPoint> ordered_polygon_9_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_9_corners,
						  polygon_9_corners,
						  9 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_9_first_point( 1.0, -1.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_9_second_point( 1.0, -1.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_9_third_point( -1.0, -1.0, 2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_9_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_9_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_9_third_point );

  // Initialize polygon 10
  std::list<IntersectionPoint> ordered_polygon_10_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_10_corners,
						  polygon_10_corners,
						  10 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_10_first_point( -2.0, -2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_10_second_point( 2.0, -2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_10_third_point( 2.0, -2.0, -2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_10_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_10_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_10_third_point );

  // Initialize polygon 11
  std::list<IntersectionPoint> ordered_polygon_11_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_11_corners,
						  polygon_11_corners,
						  11 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_11_first_point( -2.0, 2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_11_second_point( 2.0, 2.0, 2.0 );
  Geometry::Vector<ScalarType> ref_polygon_11_third_point( 2.0, -2.0, 2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_11_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_11_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_11_third_point );

  // Initialize polygon 12
  std::list<IntersectionPoint> ordered_polygon_12_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_12_corners,
						  polygon_12_corners,
						  12 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_12_first_point( -2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_12_second_point( 2.0, 7.0, 0.0 );
  Geometry::Vector<ScalarType> ref_polygon_12_third_point( 2.0, 3.0, 0.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_12_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_12_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_12_third_point );

  // Initialize polygon 13
  std::list<IntersectionPoint> ordered_polygon_13_corners;

  first_point = factory.initializePolygonCorners( ordered_polygon_13_corners,
						  polygon_13_corners,
						  13 );
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;

  Geometry::Vector<ScalarType> ref_polygon_13_first_point( 2.0, 3.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_13_second_point( 2.0, 7.0, -2.0 );
  Geometry::Vector<ScalarType> ref_polygon_13_third_point( -2.0, 7.0, -2.0 );

  TEST_EQUALITY( first_point->getRawPoint(), ref_polygon_13_first_point );
  TEST_EQUALITY( second_point->getRawPoint(), ref_polygon_13_second_point );
  TEST_EQUALITY( third_point->getRawPoint(), ref_polygon_13_third_point );
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory, initializePolygonCorners );

//---------------------------------------------------------------------------//
// Check that the factory can create correct polygons.
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellPolygonFactory,
				   create,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;
  typedef typename Geometry::CellPolygonFactory<Cell>::PolygonPtr PolygonPtr;

  // Create the cell that all polygons lie on
  Teuchos::RCP<Cell> cell;
  createTestingCell( cell );

  // Create the cell polygon factory
  Geometry::CellPolygonFactory<Cell> factory( cell );

  // Create the lists of polygon corners
  std::list<IntersectionPoint> polygon_1_corners;
  std::list<IntersectionPoint> polygon_2_corners;
  std::list<IntersectionPoint> polygon_3_corners;
  std::list<IntersectionPoint> polygon_4_corners;
  std::list<IntersectionPoint> polygon_5_corners;
  std::list<IntersectionPoint> polygon_6_corners;
  std::list<IntersectionPoint> polygon_7_corners;
  std::list<IntersectionPoint> polygon_8_corners;
  std::list<IntersectionPoint> polygon_9_corners;
  std::list<IntersectionPoint> polygon_10_corners;
  std::list<IntersectionPoint> polygon_11_corners;
  std::list<IntersectionPoint> polygon_12_corners;
  std::list<IntersectionPoint> polygon_13_corners;

  createSurface1PolygonCorners( polygon_1_corners );
  createSurface2PolygonCorners( polygon_2_corners );
  createSurface3PolygonCorners( polygon_3_corners );
  createSurface4PolygonCorners( polygon_4_corners );
  createSurface5PolygonCorners( polygon_5_corners );
  createSurface6PolygonCorners( polygon_6_corners );
  createSurface7PolygonCorners( polygon_7_corners );
  createSurface8PolygonCorners( polygon_8_corners );
  createSurface9PolygonCorners( polygon_9_corners );
  createSurface10PolygonCorners( polygon_10_corners );
  createSurface11PolygonCorners( polygon_11_corners );
  createSurface12PolygonCorners( polygon_12_corners );
  createSurface13PolygonCorners( polygon_13_corners );

  // Create the polygon on each surface
  PolygonPtr polygon_1 = factory.create( polygon_1_corners );
  PolygonPtr polygon_2 = factory.create( polygon_2_corners );
  PolygonPtr polygon_3 = factory.create( polygon_3_corners );
  PolygonPtr polygon_4 = factory.create( polygon_4_corners );
  PolygonPtr polygon_5 = factory.create( polygon_5_corners );
  PolygonPtr polygon_6 = factory.create( polygon_6_corners );
  PolygonPtr polygon_7 = factory.create( polygon_7_corners );
  PolygonPtr polygon_8 = factory.create( polygon_8_corners );
  PolygonPtr polygon_9 = factory.create( polygon_9_corners );
  PolygonPtr polygon_10 = factory.create( polygon_10_corners );
  PolygonPtr polygon_11 = factory.create( polygon_11_corners );
  PolygonPtr polygon_12 = factory.create( polygon_12_corners );
  PolygonPtr polygon_13 = factory.create( polygon_13_corners );

  // Test that the polygons have been created correctly
  ScalarType ref_area_polygon_1 = 24.0;
  ScalarType ref_area_polygon_2 = 8.0;
  ScalarType ref_area_polygon_3 = 8.0;
  ScalarType ref_area_polygon_4 = 24.0;
  ScalarType ref_area_polygon_5 = 8.0;
  ScalarType ref_area_polygon_6 = 8.0;
  ScalarType ref_area_polygon_7 = 16.0;
  ScalarType ref_area_polygon_8 = 8.0;
  ScalarType ref_area_polygon_9 = 8.0;
  ScalarType ref_area_polygon_10 = 16.0;
  ScalarType ref_area_polygon_11 = 12.0;
  ScalarType ref_area_polygon_12 = 16.0;
  ScalarType ref_area_polygon_13 = 28.0;

  TEST_EQUALITY( polygon_1->getArea(), ref_area_polygon_1 );
  TEST_EQUALITY( polygon_2->getArea(), ref_area_polygon_2 );
  TEST_EQUALITY( polygon_3->getArea(), ref_area_polygon_3 );
  TEST_EQUALITY( polygon_4->getArea(), ref_area_polygon_4 );
  TEST_EQUALITY( polygon_5->getArea(), ref_area_polygon_5 );
  TEST_EQUALITY( polygon_6->getArea(), ref_area_polygon_6 );
  TEST_EQUALITY( polygon_7->getArea(), ref_area_polygon_7 );
  TEST_EQUALITY( polygon_8->getArea(), ref_area_polygon_8 );
  TEST_EQUALITY( polygon_9->getArea(), ref_area_polygon_9 );
  TEST_EQUALITY( polygon_10->getArea(), ref_area_polygon_10 );
  TEST_EQUALITY( polygon_11->getArea(), ref_area_polygon_11 );
  TEST_EQUALITY( polygon_12->getArea(), ref_area_polygon_12 );
  TEST_EQUALITY( polygon_13->getArea(), ref_area_polygon_13 );
}

UNIT_TEST_INSTANTIATION( CellPolygonFactory, create );

//---------------------------------------------------------------------------//
// end tstCellPolygonFactory.cpp
//---------------------------------------------------------------------------//
