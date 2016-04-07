//---------------------------------------------------------------------------//
// \file   tstDisjointConvexPolyhedralCell.cpp
// \author Alex Robinson
// \brief  Cell class unit tests
//---------------------------------------------------------------------------//


// Std Lib Includes
#include <iostream>
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "FRENSIE_UnitTestHarnessExtensions.hpp"
#include "Cell.hpp"
#include "Surface.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
#include "TestCell.hpp"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define CELL_DEFINITION_1 "(-1n2n-3n4n-7n8)u(-1n2n-5n6n-7n8)"
#define CELL_DEFINITION_2 "(-1n2n-6n7n-8n9)u(-2n3n-4n5n-8n9)"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell can be instantiated correctly
TEUCHOS_UNIT_TEST( Cell, constructor )
{
  std::string cell_definition( CELL_DEFINITION_1 );

  std::map<unsigned,Teuchos::RCP<FRENSIE::Surface> > global_surface_map;

  Teuchos::RCP<FRENSIE::Surface> surface( new FRENSIE::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  global_surface_map[1] = surface;
  
  surface.reset( new FRENSIE::Surface( 2,
				      1, 0, 0,
				      2 ) );

  global_surface_map[2] = surface;

  surface.reset( new FRENSIE::Surface( 3,
				      0, 1, 0,
				      -3 ) );

  global_surface_map[3] = surface;

  surface.reset( new FRENSIE::Surface( 4,
				      0, 1, 0,
				      -1 ) );

  global_surface_map[4] = surface;

  surface.reset( new FRENSIE::Surface( 5,
				      0, 1, 0,
				      1 ) );

  global_surface_map[5] = surface;

  surface.reset( new FRENSIE::Surface( 6,
				      0, 1, 0,
				      3 ) );

  global_surface_map[6] = surface;

  surface.reset( new FRENSIE::Surface( 7,
				      0, 0, 1,
				      -2 ) );

  global_surface_map[7] = surface;

  surface.reset( new FRENSIE::Surface( 8,
				      0, 0, 1,
				      2 ) );

  global_surface_map[8] = surface;

  Teuchos::RCP<FRENSIE::Cell> cell( new FRENSIE::Cell( 1,
						     cell_definition,
						     global_surface_map,
						     true ) );
  
  TEST_EQUALITY_CONST( cell->getVolume(), 64.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 1 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 2 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 3 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 4 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 5 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 6 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 7 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 8 ), 16.0 );

  cell_definition = CELL_DEFINITION_2;

  global_surface_map.clear();

  surface.reset( new FRENSIE::Surface( 1,
				      1, 0, 0,
				      -2 ) );

  global_surface_map[1] = surface;

  surface.reset( new FRENSIE::Surface( 2,
				      1, 0, 0,
				      0 ) );
  
  global_surface_map[2] = surface;

  surface.reset( new FRENSIE::Surface( 3,
				      1, 0, 0,
				      2 ) );
  
  global_surface_map[3] = surface;

  surface.reset( new FRENSIE::Surface( 4,
				      0, 1, 0,
				      -3 ) );

  global_surface_map[4] = surface;

  surface.reset( new FRENSIE::Surface( 5,
				      0, 1, 0,
				      -1 ) );

  global_surface_map[5] = surface;

  surface.reset( new FRENSIE::Surface( 6,
				      0, 1, 0,
				      1 ) );

  global_surface_map[6] = surface;
  
  surface.reset( new FRENSIE::Surface( 7,
				      0, 1, 0,
				      3 ) );

  global_surface_map[7] = surface;

  surface.reset( new FRENSIE::Surface( 8,
				      0, 0, 1,
				      -2 ) );
  
  global_surface_map[8] = surface;

  surface.reset( new FRENSIE::Surface( 9,
				      0, 0, 1,
				      2 ) );

  global_surface_map[9] = surface;

  cell.reset( new FRENSIE::Cell( 1,
				cell_definition,
				global_surface_map,
				true ) );

  TEST_EQUALITY_CONST( cell->getVolume(), 64.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 1 ), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 2 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 3 ), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 4 ), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 5 ), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 6 ), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 7 ), 8.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 8 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 9 ), 16.0 );
}

//---------------------------------------------------------------------------//
// end tstDisjointConvexPolyhedralCell.cpp
//---------------------------------------------------------------------------//
