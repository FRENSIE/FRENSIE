//---------------------------------------------------------------------------//
//! 
//! \file   tstCellFactory.cpp
//! \author Alex Robinson
//! \brief  Cell factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <map>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "CellFactory.hpp"
#include "Cell.hpp"
#include "Surface.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Create a cube centered on the origin and a sphere centered on the origin
template<typename SurfaceMap>
void createCubSurface( SurfaceMap &cell_surfaces )
{
  typedef typename SurfaceMap::mapped_type::element_type::ordinalType 
    OrdinalType;
  typedef typename SurfaceMap::mapped_type::element_type::scalarType 
    ScalarType;
  typedef FACEMC::Surface<OrdinalType,ScalarType> Surface;

  // Clear the map
  cell_surfaces.clear();
  
  // Surface 1: x = 2
  Teuchos::RCP<Surface> surface_ptr( new Surface( 1,
						  1, 0, 0,
						  -2 ) );
  cell_surfaces[1] = surface_ptr;

  // Surface 2: x = -2
  surface_ptr.reset( new Surface( 2,
				  1, 0, 0,
				  2 ) );

  cell_surfaces[2] = surface_ptr;

  // Surface 3: y = 2
  surface_ptr.reset( new Surface( 3,
				  0, 1, 0,
				  -2 ) );
  cell_surfaces[3] = surface_ptr;

  // Surface 4: y = -2
  surface_ptr.reset( new Surface( 4,
				  0, 1, 0,
				  2 ) );
  cell_surfaces[4] = surface_ptr;

  // Surface 5: z = 2
  surface_ptr.reset( new Surface( 5,
				  0, 0, 1,
				  -2 ) );
  cell_surfaces[5] = surface_ptr;

  // Surface 6: z = -2
  surface_ptr.reset( new Surface( 6,
				  0, 0, 1,
				  2 ) );
  cell_surfaces[6] = surface_ptr;

  // Surface 7: x^2+y^2+z^2 = 1
  surface_ptr.reset( new Surface( 1,
				  1, 1, 1, 
				  0, 0, 0,
				  -1 ) );
  cell_surfaces[7] = surface_ptr;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell factory can create the desired cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( CellFactory, 
				   create,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef FACEMC::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;
  typedef FACEMC::CellFactory<Cell,SurfaceMap> CellFactory;

  // Load the surfaces that define the cells
  std::string cube_cell_definition = "-1n2n-3n4n-5n6";
  std::string sphere_cell_definition = "-7";

  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map );

  // Create the cell factory
  CellFactory factory( surface_map );

  // Create the cells
  typename CellFactory::CellPtr cube = factory.create( 0, 
						       cube_cell_definition, 
						       true );
  
  typename CellFactory::CellPtr sphere = factory.create(1, 
							sphere_cell_definition,
							true );

  TEST_EQUALITY_CONST( cube->getVolume(), 64.0 );
  TEST_EQUALITY_CONST( sphere->getVolume(), 1.0 );
}
//---------------------------------------------------------------------------//
// end tstCellFactory.cpp
//---------------------------------------------------------------------------//
