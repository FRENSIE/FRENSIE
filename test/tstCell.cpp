//---------------------------------------------------------------------------//
// \file   tstCell.cpp
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

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Cell.hpp"
#include "Surface.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
#include "TestCell.hpp"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define CELL_DEFINITION_1 "-1 n 2 n -3 n 4 n -5 n 6 "
#define SIMPLIFIED_CELL_DEFINITION_1 "-1   2   -3   4   -5   6"
#define CELL_DEFINITION_2 "-1 n 2 n 3 n (4 u -5) n -6 n 7"
#define SIMPLIFIED_CELL_DEFINITION_2 "-1   2   3    4   -5    -6   7"


//---------------------------------------------------------------------------//
// Tests.
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
  
  cell_definition = CELL_DEFINITION_2;

  cell.simplifyCellDefinitionString( cell_definition );
  
  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					SIMPLIFIED_CELL_DEFINITION_2 ) == 0 );
  
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
// end tstCell.cpp
//---------------------------------------------------------------------------//
