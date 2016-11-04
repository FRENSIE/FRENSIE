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

// FRENSIE Includes
#include "Geometry_CellFactory.hpp"
#include "Geometry_Cell.hpp"
#include "Geometry_Surface.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define MAP_TYPEDEFS( space, map )					\
  typedef space::map<short,Teuchos::RCP<Geometry::Surface<short,float> > >	map##_s_f; \
  typedef space::map<short,Teuchos::RCP<Geometry::Surface<short,double> > > map##_s_d; \
  typedef space::map<int,Teuchos::RCP<Geometry::Surface<int,float> > > map##_i_f; \
  typedef space::map<int,Teuchos::RCP<Geometry::Surface<int,double> > > map##_i_d; \
  typedef space::map<long,Teuchos::RCP<Geometry::Surface<long,float> > > map##_l_f; \
  typedef space::map<long,Teuchos::RCP<Geometry::Surface<long,double> > > map##_l_d; \

#define UNIT_TEST_INSTANTIATION_STD_MAP( type, name )		\
  MAP_TYPEDEFS( std, map )						\
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, short, double, map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, double, map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, double, map_l_d ) \

#define UNIT_TEST_INSTANTIATION_BOOST_UMAP( type, name )		\
  MAP_TYPEDEFS( boost, unordered_map )					\
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, short, double, unordered_map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, double, unordered_map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, double, unordered_map_l_d ) \

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Create a cube centered on the origin and a sphere centered on the origin
template<typename SurfaceMap>
void createSurfaces( SurfaceMap &cell_surfaces )
{
  typedef typename SurfaceMap::mapped_type::element_type::ordinalType
    OrdinalType;
  typedef typename SurfaceMap::mapped_type::element_type::scalarType
    ScalarType;
  typedef Geometry::Surface<OrdinalType,ScalarType> Surface;

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
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;
  typedef Geometry::CellFactory<Cell,SurfaceMap> CellFactory;

  // Load the surfaces that define the cells
  std::string cube_cell_definition = "-1n2n-3n4n-5n6";
  std::string sphere_cell_definition = "-7";

  SurfaceMap surface_map;
  createSurfaces( surface_map );

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

UNIT_TEST_INSTANTIATION_STD_MAP( CellFactory, create );
UNIT_TEST_INSTANTIATION_BOOST_UMAP( CellFactory, create );

//---------------------------------------------------------------------------//
// end tstCellFactory.cpp
//---------------------------------------------------------------------------//
