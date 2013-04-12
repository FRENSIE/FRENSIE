//---------------------------------------------------------------------------//
// \file   tstCell.cpp
// \author Alex Robinson
// \brief  Cell class unit test
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Cell.hpp"
#include "Surface.hpp"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define CELL_DEFINITION_1 "-1 n 2 n -3 n 4 n -5 n 6 "
#define SIMPLIFIED_CELL_DEFINITION_1 "-1   2   -3   4   -5   6"
#define CELL_DEFINITION_2 "-1 n 2 n 3 n (4 u -5) n -6 n 7"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

class TestCell : public FACEMC::Cell
{
public:
  TestCell()
    : FACEMC::Cell()
  { /* ... */ }

  TestCell( std::string &cell_definition )
    : FACEMC::Cell( cell_definition )
  { /* ... */ }

  virtual ~TestCell()
  { /* ... */ }
  
  // Allow public access to the Cell protected member functions
  using FACEMC::Cell::simplifyCellDefinitionString;
  using FACEMC::Cell::assignSurfaces;
  using FACEMC::Cell::calculateVolumeAndSurfaceAreas;
  using FACEMC::Cell::calculatePolyhedralCellVolumeAndSurfaceAreas;
  using FACEMC::Cell::calculatePolygonIntersectionPoints;
  using FACEMC::Cell::testIntersectionPoint;
  using FACEMC::Cell::createPolygon;
  using FACEMC::Cell::initializePolygon;
  using FACEMC::Cell::calculatePolygonArea;
  using FACEMC::Cell::calculatePolygonVolumeContribution;
  using FACEMC::Cell::calculateRotationallySymmetricCellVolumeAndSurfaceAreas;
  using FACEMC::Cell::calculateVolumeAndSurfaceAreasUsingMonteCarlo;
  using FACEMC::Cell::calculateBoundingBox;
  using FACEMC::Cell::getSurfaceArray;
};

//---------------------------------------------------------------------------//
// Test.
//---------------------------------------------------------------------------//
// Check that the cell can simplify its definition string
TEUCHOS_UNIT_TEST( Cell, simplifyCellDefinitionString )
{
  TestCell cell;

  std::string cell_definition( CELL_DEFINITION_1 );

  cell.simplifyCellDefinitionString( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					SIMPLIFIED_CELL_DEFINITION_1 ) == 0 );
}

//---------------------------------------------------------------------------//
// Check that the cell can assign surfaces to the cell
TEUCHOS_UNIT_TEST( Cell, assignSurfaces )
{
  TestCell cell;

  std::string cell_definition( CELL_DEFINITION_1 );

  std::map<unsigned,Teuchos::RCP<FACEMC::Surface> > global_surface_map;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );
  global_surface_map[1] = surface;

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  global_surface_map[2] = surface;

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  global_surface_map[3] = surface;

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  global_surface_map[4] = surface;

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -1 ) );
  global_surface_map[5] = surface;

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      1 ) );
  global_surface_map[6] = surface;				 

  cell.simplifyCellDefinitionString( cell_definition );
  cell.assignSurfaces( cell_definition,
		      global_surface_map );

  Teuchos::Array<FACEMC::Pair<Teuchos::RCP<FACEMC::Surface>,FACEMC::Surface::Sense> > 
    cell_surfaces = cell.getSurfaceArray();

  TEST_EQUALITY_CONST( cell_surfaces.size(), 6 );
  TEST_EQUALITY_CONST( cell_surfaces[0].first->getId(), 1 );
  TEST_EQUALITY_CONST( cell_surfaces[0].second, -1 );
  TEST_EQUALITY_CONST( cell_surfaces[1].first->getId(), 2 );
  TEST_EQUALITY_CONST( cell_surfaces[1].second, 1 );
  TEST_EQUALITY_CONST( cell_surfaces[2].first->getId(), 3 );
  TEST_EQUALITY_CONST( cell_surfaces[2].second, -1 );
  TEST_EQUALITY_CONST( cell_surfaces[3].first->getId(), 4 );
  TEST_EQUALITY_CONST( cell_surfaces[3].second, 1 );
  TEST_EQUALITY_CONST( cell_surfaces[4].first->getId(), 5 );
  TEST_EQUALITY_CONST( cell_surfaces[4].second, -1 );
  TEST_EQUALITY_CONST( cell_surfaces[5].first->getId(), 6 );
  TEST_EQUALITY_CONST( cell_surfaces[5].second, 1 );
}

//---------------------------------------------------------------------------//
// Check that the cell can test if an intersection point is real
TEUCHOS_UNIT_TEST( Cell, testIntersectionPoint )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> 
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -2 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      0 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  FACEMC::Quad<double,double,unsigned,unsigned> 
    intersection_point( -1.0, -1.0, 2, 4 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point ) );

  intersection_point( 1.0, -1.0, 1, 4 );
  
  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point ) );

  intersection_point( 1.0, 1.0, 1, 3 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point ) );
  
  intersection_point( -1.0, 1.0, 2, 3 );
  
  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point ) );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the intersection points with the z-axis
TEUCHOS_UNIT_TEST( Cell, calculatePolygonIntersectionPoints )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> 
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -2 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      0 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > intersection_points;

  cell.calculatePolygonIntersectionPoints( copy_cell_surfaces,
					   intersection_points );

  TEST_EQUALITY_CONST( intersection_points.size(), 4 );

  FACEMC::Quad<double,double,unsigned,unsigned> 
    ref_intersection_point( 1.0, 1.0, 1, 3 );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    point = intersection_points.begin();

  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ref_intersection_point( 1.0, -1.0, 1, 4 );
  ++point;

  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ref_intersection_point( -1.0, 1.0, 2, 3 );
  ++point;

  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ref_intersection_point( -1.0, -1.0, 2, 4 );
  ++point;
  
  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );
}

//---------------------------------------------------------------------------//
// Check that the cell can initialize a polygon from a list of intersection 
// points 
TEUCHOS_UNIT_TEST( Cell, initializePolygon )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> 
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -2 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      0 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > 
    intersection_points, polygon;    

  cell.calculatePolygonIntersectionPoints( copy_cell_surfaces,
					   intersection_points );

  unsigned current_surface_id;
  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    start_point = cell.initializePolygon( polygon,
					  intersection_points,
					  copy_cell_surfaces,
					  current_surface_id );

  TEST_EQUALITY_CONST( polygon.size(), 3 );
  TEST_EQUALITY_CONST( intersection_points.size(), 1 );
  TEST_EQUALITY_CONST( current_surface_id, 2 );
  
  FACEMC::Quad<double,double,unsigned,unsigned> 
    ref_corner_point( 1.0, -1.0, 1, 4 );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    point = polygon.begin();

  FACEMC_TEST_EQUALITY( *start_point, ref_corner_point );
  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ref_corner_point( 1.0, 1.0, 1, 3 );
  ++point;
  
  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ref_corner_point( -1.0, 1.0, 2, 3 );
  ++point;
  
  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ref_corner_point( -1.0, -1.0, 2, 4 );
  point = intersection_points.begin();

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );  
}

//---------------------------------------------------------------------------//
// Check that the cell can create a polygon from a list of intersection 
// points 
TEUCHOS_UNIT_TEST( Cell, createPolygon )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> 
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -2 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      0 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > intersection_points;

  cell.calculatePolygonIntersectionPoints( copy_cell_surfaces,
					   intersection_points );

  cell.createPolygon( intersection_points,
		      copy_cell_surfaces );

  TEST_EQUALITY_CONST( intersection_points.size(), 5 );

  FACEMC::Quad<double,double,unsigned,unsigned> 
    ref_corner_point( 1.0, -1.0, 1, 4 );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    point = intersection_points.begin();

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ref_corner_point( 1.0, 1.0, 1, 3 );
  ++point;
  
  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ref_corner_point( -1.0, 1.0, 2, 3 );
  ++point;
  
  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ref_corner_point( -1.0, -1.0, 2, 4 );
  ++point;

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );  
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the area of the polygon created from
// intersection points
TEUCHOS_UNIT_TEST( Cell, calculatePolygonArea )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> 
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -2 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      0 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > intersection_points;

  cell.calculatePolygonIntersectionPoints( copy_cell_surfaces,
					   intersection_points );

  cell.createPolygon( intersection_points,
		      copy_cell_surfaces );

  std::list<double> polygon_areas;

  cell.calculatePolygonArea( 6,
			     intersection_points,
			     polygon_areas );

  TEST_EQUALITY_CONST( polygon_areas.front(), 4.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the volume contribution of the polygon 
// created from intersection points
TEUCHOS_UNIT_TEST( Cell, calculatePolygonVolumeContribution )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> 
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -2 ) );
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      0 ) );
  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > intersection_points;

  cell.calculatePolygonIntersectionPoints( copy_cell_surfaces,
					   intersection_points );

  cell.createPolygon( intersection_points,
		      copy_cell_surfaces );

  std::list<double> polygon_areas;

  cell.calculatePolygonArea( 6,
			     intersection_points,
			     polygon_areas );

  FACEMC::Surface reference_surface( 0,
				     0, 0, 0,
				     0, 0, 0,
				     0, 0, 1,
				     -1 );

  cell.calculatePolygonVolumeContribution( reference_surface,
					   intersection_points,
					   polygon_areas );

  TEST_EQUALITY_CONST( cell.getVolume(), 4.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the surface area of all surfaces bounding
// the cell and the cell volume assuming a polyhedral cell
TEUCHOS_UNIT_TEST( Cell, calculatePolyhedralCellVolumeAndSurfaceAreas )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  std::map<unsigned,Teuchos::RCP<FACEMC::Surface> > global_surface_map;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );
  global_surface_map[1] = surface;

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  global_surface_map[2] = surface;

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  global_surface_map[3] = surface;

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  global_surface_map[4] = surface;

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -1 ) );
  global_surface_map[5] = surface;

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      1 ) );
  global_surface_map[6] = surface;				 

  cell.simplifyCellDefinitionString( cell_definition );
  cell.assignSurfaces( cell_definition,
		       global_surface_map );
  cell.calculatePolyhedralCellVolumeAndSurfaceAreas();

  TEST_EQUALITY_CONST( cell.getVolume(), 8.0 );
  TEST_EQUALITY_CONST( cell.getSurfaceArea( 1 ), 4.0 );
  TEST_EQUALITY_CONST( cell.getSurfaceArea( 2 ), 4.0 );
  TEST_EQUALITY_CONST( cell.getSurfaceArea( 3 ), 4.0 );
  TEST_EQUALITY_CONST( cell.getSurfaceArea( 4 ), 4.0 );
  TEST_EQUALITY_CONST( cell.getSurfaceArea( 5 ), 4.0 );
  TEST_EQUALITY_CONST( cell.getSurfaceArea( 6 ), 4.0 );
}

//---------------------------------------------------------------------------//
// Check that a cell can be instantiated correctly
TEUCHOS_UNIT_TEST( Cell, constructor )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  std::map<unsigned,Teuchos::RCP<FACEMC::Surface> > global_surface_map;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      0, 0, 0,
							      0, 0, 0,
							      1, 0, 0,
							      -1 ) );
  global_surface_map[1] = surface;

  surface.reset( new FACEMC::Surface( 2,
				      0, 0, 0,
				      0, 0, 0,
				      1, 0, 0,
				      1 ) );
  global_surface_map[2] = surface;

  surface.reset( new FACEMC::Surface( 3,
				      0, 0, 0,
				      0, 0, 0,
				      0, 1, 0,
				      -1 ) );
  global_surface_map[3] = surface;

  surface.reset( new FACEMC::Surface( 4,
				      0, 0, 0,
				      0, 0, 0, 
				      0, 1, 0,
				      1 ) );
  global_surface_map[4] = surface;

  surface.reset( new FACEMC::Surface( 5,
				      0, 0, 0, 
				      0, 0, 0,
				      0, 0, 1,
				      -1 ) );
  global_surface_map[5] = surface;

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 0,
				      0, 0, 0,
				      0, 0, 1,
				      1 ) );
  global_surface_map[6] = surface;

  Teuchos::RCP<FACEMC::Cell> cell( new FACEMC::Cell( 1,
						     cell_definition,
						     global_surface_map,
						     true ) );

  TEST_EQUALITY_CONST( cell->getVolume(), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 1 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 2 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 3 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 4 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 5 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 6 ), 4.0 );
}

//---------------------------------------------------------------------------//
// end tstCell.cpp
//---------------------------------------------------------------------------//

