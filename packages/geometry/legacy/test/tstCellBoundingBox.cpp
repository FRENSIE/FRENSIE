//---------------------------------------------------------------------------//
//!
//! \file   tstCellBoundingBox.cpp
//! \author Alex Robinson
//! \brief  Cell bounding box unit tests
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
#include "Geometry_Cell.hpp"
#include "Geometry_Surface.hpp"
#include "Geometry_CellBoundingBox.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, double )

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Create the testing cell (unit sphere)
template<typename Cell>
void createTestingCell( Teuchos::RCP<Cell> &cell_ptr )
{
  typedef typename Cell::surfaceOrdinalType ordinalType;
  typedef typename Cell::scalarType scalarType;
  typedef Geometry::Surface<ordinalType,scalarType> Surface;

  // Create the cell definition
  std::string cell_definition( "-1" );

  // Create the surface map
  std::map<ordinalType,Teuchos::RCP<Surface> > surface_map;

  // Create the spherical surface
  Teuchos::RCP<Surface> surface_ptr( new Surface( 1,
						  1, 1, 1,
						  0, 0, 0,
						  -1 ) );

  surface_map[1] = surface_ptr;

  // Create the cell
  cell_ptr.reset( new Cell( 0, cell_definition, surface_map ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a cell's volume can be numerically integrated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( CellBoundingBox,
				   calculateCellVolume,
				   CellOrdinalType,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Cell<CellOrdinalType,OrdinalType,ScalarType> Cell;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  // Create a unit sphere
  Teuchos::RCP<Cell> unit_sphere;
  createTestingCell( unit_sphere );

  // Create a bounding box for the unit sphere
  Geometry::CellBoundingBox<Cell>
    unit_sphere_bounding_box( unit_sphere, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::initialize();

  // Calculate the cell volume
  unit_sphere_bounding_box.calculateCellVolume();

  // Reference cell volume
  ScalarType ref_unit_sphere_vol = 4.0/3.0*Utility::PhysicalConstants::pi;

  TEST_FLOATING_EQUALITY( unit_sphere->getVolume(),
			  ref_unit_sphere_vol,
			  static_cast<ScalarType>( 1e-3 ) );
}

UNIT_TEST_INSTANTIATION( CellBoundingBox, calculateCellVolume );

//---------------------------------------------------------------------------//
// end tstCellBoundingBox.cpp
//---------------------------------------------------------------------------//

