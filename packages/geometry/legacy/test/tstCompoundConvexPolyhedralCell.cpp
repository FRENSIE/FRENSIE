//---------------------------------------------------------------------------//
// \file   tstCompoundConvexPolyhedralCell.cpp
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
#define CELL_DEFINITION_1 "-1n2n-3n4n-5n6n(7u-8u9u-10u11u-12)"
#define CELL_DEFINITION_2 "-1n2n-3n4n-5n6n(-7u9u-10u11u-12)"

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
				      -2 ) );

  global_surface_map[3] = surface;

  surface.reset( new FRENSIE::Surface( 4, 
				      0, 1, 0,
				      2 ) );

  global_surface_map[4] = surface;

  surface.reset( new FRENSIE::Surface( 5,
				      0, 0, 1,
				      -2 ) );

  global_surface_map[5] = surface;
  
  surface.reset( new FRENSIE::Surface( 6,
				      0, 0, 1,
				      2 ) );

  global_surface_map[6] = surface;

  surface.reset( new FRENSIE::Surface( 7,
				      1, 0, 0,
				      -1 ) );

  global_surface_map[7] = surface;

  surface.reset( new FRENSIE::Surface( 8,
				      1, 0, 0,
				      1 ) );
  
  global_surface_map[8] = surface;

  surface.reset( new FRENSIE::Surface( 9,
				      0, 1, 0,
				      -1 ) );

  global_surface_map[9] = surface;

  surface.reset( new FRENSIE::Surface( 10,
				      0, 1, 0,
				      1 ) );

  global_surface_map[10] = surface;

  surface.reset( new FRENSIE::Surface( 11,
				      0, 0, 1,
				      -1 ) );
  
  global_surface_map[11] = surface;

  surface.reset( new FRENSIE::Surface( 12,
				      0, 0, 1,
				      1 ) );

  global_surface_map[12] = surface;

  Teuchos::RCP<FRENSIE::Cell> cell( new FRENSIE::Cell( 1,
						     cell_definition,
						     global_surface_map,
						     true ) );

  TEST_EQUALITY_CONST( cell->getVolume(), 56.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 1 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 2 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 3 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 4 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 5 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 6 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 7 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 8 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 9 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 10 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 11 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 12 ), 4.0 );

  cell_definition = CELL_DEFINITION_2;

  cell.reset( new FRENSIE::Cell( 2,
				cell_definition,
				global_surface_map,
				true ) );

  TEST_EQUALITY_CONST( cell->getVolume(), 60.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 1 ), 12.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 2 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 3 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 4 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 5 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 6 ), 16.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 7 ), 4.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 9 ), 2.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 10 ), 2.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 11 ), 2.0 );
  TEST_EQUALITY_CONST( cell->getSurfaceArea( 12 ), 2.0 );
}

//---------------------------------------------------------------------------//
// end tstCompoundConvexPolyhedralCell.cpp
//---------------------------------------------------------------------------//

