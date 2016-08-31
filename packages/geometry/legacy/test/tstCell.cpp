//---------------------------------------------------------------------------//
//!
//! \file   tstCell.cpp
//! \author Alex Robinson
//! \brief  Cell class unit tests
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
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename CellOrdinalType,
	 typename SurfaceOrdinalType,
	 typename ScalarType>
class TestCell : public Geometry::Cell<CellOrdinalType,
				     SurfaceOrdinalType,
				     ScalarType>
{
public:
  TestCell() : Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>()
  { /* ... */ }

  virtual ~TestCell()
  { /* ... */ }

  using Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::simplifyCellDefinitionString;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Create a cube centered on the origin
template<typename SurfaceMap>
void createConvexPolyhedronSurfaces( SurfaceMap &cell_surfaces,
				     std::string &cell_definition )
{
  typedef typename SurfaceMap::mapped_type::element_type::ordinalType
    OrdinalType;
  typedef typename SurfaceMap::mapped_type::element_type::scalarType
    ScalarType;
  typedef Geometry::Surface<OrdinalType,ScalarType> Surface;

  // Clear the map
  cell_surfaces.clear();

  // Create the cell definition
  cell_definition = "-1n2n-3n4n-5n6";

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
}

// Create a unit sphere centered at the origin
template<typename SurfaceMap>
void createUnitSphereSurfaces( SurfaceMap &cell_surfaces,
			       std::string &cell_definition )
{
  typedef typename SurfaceMap::mapped_type::element_type::ordinalType
    OrdinalType;
  typedef typename SurfaceMap::mapped_type::element_type::scalarType
    ScalarType;
  typedef Geometry::Surface<OrdinalType,ScalarType> Surface;

  // Clear the map
  cell_surfaces.clear();

  // Create the cell definition
  cell_definition = "-1";

  // Surface 1: x = 2
  Teuchos::RCP<Surface> surface_ptr( new Surface( 1,
						  1, 1, 1,
						  0, 0, 0,
						  -1 ) );
  cell_surfaces[1] = surface_ptr;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell can simplify its definition string
TEUCHOS_UNIT_TEST( Cell, simplifyCellDefinitionString )
{
  std::string cell_def( "1n2n3 n 4n5 n 6 n 7" );

  TestCell<int,int,double>::simplifyCellDefinitionString( cell_def );

  std::string ref_simplified_cell_def( "1 2 3   4 5   6   7" );

  TEST_ASSERT( cell_def.compare( 0,
				 std::string::npos,
				 ref_simplified_cell_def ) == 0 );
}

//---------------------------------------------------------------------------//
// Check that the cell can assign surfaces to the cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   constructor,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;
  SurfaceMap surface_map;
  std::string cell_definition;

  // Load the surfaces that define a cube
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Test that the surfaces have been found and stored
  typename Cell::SurfaceSensePairsIterator surface_sense_pair,
    end_surface_sense_pair;
  surface_sense_pair = polyhedron.beginSurfaceSensePairs();
  end_surface_sense_pair = polyhedron.endSurfaceSensePairs();

  TEST_ASSERT( surface_sense_pair != end_surface_sense_pair );
  TEST_EQUALITY_CONST(std::distance(surface_sense_pair,end_surface_sense_pair),
		      6 );
}

UNIT_TEST_INSTANTIATION_STD_MAP( Cell, constructor );
UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, constructor );

//---------------------------------------------------------------------------//
// Check that a point can be tested as in a polyhedral cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isIn_polyhedron,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Point in cell
  Geometry::Vector<ScalarType> point_1( 0.0, 0.0, 0.0 );
  // Point outside of cell
  Geometry::Vector<ScalarType> point_2( 10.0, 10.0, 10.0 );
  // Points on cell
  Geometry::Vector<ScalarType> point_3( 2.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_4( -2.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_5( 0.0, 2.0, 0.0 );
  Geometry::Vector<ScalarType> point_6( 0.0, -2.0, 0.0 );
  Geometry::Vector<ScalarType> point_7( 0.0, 0.0, 2.0 );
  Geometry::Vector<ScalarType> point_8( 0.0, 0.0, -2.0 );

  TEST_ASSERT( polyhedron.isIn( point_1 ) );
  TEST_ASSERT( !polyhedron.isIn( point_2 ) );
  TEST_ASSERT( !polyhedron.isIn( point_3 ) );
  TEST_ASSERT( !polyhedron.isIn( point_4 ) );
  TEST_ASSERT( !polyhedron.isIn( point_5 ) );
  TEST_ASSERT( !polyhedron.isIn( point_6 ) );
  TEST_ASSERT( !polyhedron.isIn( point_7 ) );
  TEST_ASSERT( !polyhedron.isIn( point_8 ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isIn_polyhedron );

//---------------------------------------------------------------------------//
// Check that a point can be tested as in a spherical cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isIn_sphere,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createUnitSphereSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell sphere( 0, cell_definition, surface_map );

  // Point in cell
  Geometry::Vector<ScalarType> point_1( 0.0, 0.0, 0.0 );
  // Point outside of cell
  Geometry::Vector<ScalarType> point_2( 10.0, 10.0, 10.0 );
  // Points on cell
  Geometry::Vector<ScalarType> point_3( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_4( -1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_5( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> point_6( 0.0, -1.0, 0.0 );
  Geometry::Vector<ScalarType> point_7( 0.0, 0.0, 1.0 );
  Geometry::Vector<ScalarType> point_8( 0.0, 0.0, -1.0 );

  TEST_ASSERT( sphere.isIn( point_1 ) );
  TEST_ASSERT( !sphere.isIn( point_2 ) );
  TEST_ASSERT( !sphere.isIn( point_3 ) );
  TEST_ASSERT( !sphere.isIn( point_4 ) );
  TEST_ASSERT( !sphere.isIn( point_5 ) );
  TEST_ASSERT( !sphere.isIn( point_6 ) );
  TEST_ASSERT( !sphere.isIn( point_7 ) );
  TEST_ASSERT( !sphere.isIn( point_8 ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isIn_sphere );

//---------------------------------------------------------------------------//
// Check that a point can be tested as on a polyhedral cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isOn_polyhedron,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Point in cell
  Geometry::Vector<ScalarType> point_1( 0.0, 0.0, 0.0 );
  // Point outside of cell
  Geometry::Vector<ScalarType> point_2( 10.0, 10.0, 10.0 );
  // Points on cell
  Geometry::Vector<ScalarType> point_3( 2.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_4( -2.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_5( 0.0, 2.0, 0.0 );
  Geometry::Vector<ScalarType> point_6( 0.0, -2.0, 0.0 );
  Geometry::Vector<ScalarType> point_7( 0.0, 0.0, 2.0 );
  Geometry::Vector<ScalarType> point_8( 0.0, 0.0, -2.0 );

  TEST_ASSERT( !polyhedron.isOn( point_1 ) );
  TEST_ASSERT( !polyhedron.isOn( point_2 ) );
  TEST_ASSERT( polyhedron.isOn( point_3 ) );
  TEST_ASSERT( polyhedron.isOn( point_4 ) );
  TEST_ASSERT( polyhedron.isOn( point_5 ) );
  TEST_ASSERT( polyhedron.isOn( point_6 ) );
  TEST_ASSERT( polyhedron.isOn( point_7 ) );
  TEST_ASSERT( polyhedron.isOn( point_8 ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isOn_polyhedron );

//---------------------------------------------------------------------------//
// Check that a point can be tested as on a polyhedral cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isOn_sphere,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createUnitSphereSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell sphere( 0, cell_definition, surface_map );

  // Point in cell
  Geometry::Vector<ScalarType> point_1( 0.0, 0.0, 0.0 );
  // Point outside of cell
  Geometry::Vector<ScalarType> point_2( 10.0, 10.0, 10.0 );
  // Points on cell
  Geometry::Vector<ScalarType> point_3( 1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_4( -1.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> point_5( 0.0, 1.0, 0.0 );
  Geometry::Vector<ScalarType> point_6( 0.0, -1.0, 0.0 );
  Geometry::Vector<ScalarType> point_7( 0.0, 0.0, 1.0 );
  Geometry::Vector<ScalarType> point_8( 0.0, 0.0, -1.0 );

  TEST_ASSERT( !sphere.isOn( point_1 ) );
  TEST_ASSERT( !sphere.isOn( point_2 ) );
  TEST_ASSERT( sphere.isOn( point_3 ) );
  TEST_ASSERT( sphere.isOn( point_4 ) );
  TEST_ASSERT( sphere.isOn( point_5 ) );
  TEST_ASSERT( sphere.isOn( point_6 ) );
  TEST_ASSERT( sphere.isOn( point_7 ) );
  TEST_ASSERT( sphere.isOn( point_8 ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isOn_sphere );

//---------------------------------------------------------------------------//
// Check that the presence of a cell can be tested
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isCellPresent,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create a polyhedral cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Load th surfaces that define a sphere
  createUnitSphereSurfaces( surface_map, cell_definition );

  // Create the spherical cell
  Cell sphere( 0, cell_definition, surface_map );

  // Boolean sense test array for the polyhedron
  Teuchos::ArrayRCP<bool> polyhedron_sense_tests( 6 );

  // Boolean sense test array for the sphere
  Teuchos::ArrayRCP<bool> sphere_sense_tests( 1 );

  // Polyhedron present
  polyhedron_sense_tests[0] = true;
  polyhedron_sense_tests[1] = true;
  polyhedron_sense_tests[2] = true;
  polyhedron_sense_tests[3] = true;
  polyhedron_sense_tests[4] = true;
  polyhedron_sense_tests[5] = true;

  TEST_ASSERT( polyhedron.isCellPresent( polyhedron_sense_tests ) );

  // Polyhedron not present
  polyhedron_sense_tests[0] = false;

  TEST_ASSERT( !polyhedron.isCellPresent( polyhedron_sense_tests ) );

  // Sphere present
  sphere_sense_tests[0] = true;

  TEST_ASSERT( sphere.isCellPresent( sphere_sense_tests ) );

  // Sphere not present
  sphere_sense_tests[0] = false;

  TEST_ASSERT( !sphere.isCellPresent( sphere_sense_tests ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isCellPresent );

//---------------------------------------------------------------------------//
// Check that a cell can be tested as a polyhedron
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isPolyhedron,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the polyhedral cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Load the surfaces that define the sphere
  createUnitSphereSurfaces( surface_map, cell_definition );

  // Create the spherical cell
  Cell sphere( 1, cell_definition, surface_map );

  TEST_ASSERT( polyhedron.isPolyhedron() );
  TEST_ASSERT( !sphere.isPolyhedron() );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isPolyhedron );

//---------------------------------------------------------------------------//
// Check that the volume of a cell can be set and retrieved.
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   get_set_volume,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the polyhedral cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Set the polyhedral cell volume
  ScalarType volume = 123.45;
  polyhedron.setVolume( volume );

  TEST_EQUALITY( polyhedron.getVolume(), volume );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, get_set_volume );

//---------------------------------------------------------------------------//
// Check that the surface areas of a cell can be set and retrieved
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   get_set_surface_area,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the polyhedral cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Surface areas
  Teuchos::Array<ScalarType> surface_areas( 6 );
  surface_areas[0] = 123.45;
  surface_areas[1] = 234.56;
  surface_areas[2] = 345.67;
  surface_areas[3] = 456.78;
  surface_areas[4] = 567.89;
  surface_areas[5] = 678.90;

  // Set the polyhedral cell surface areas
  polyhedron.setSurfaceArea( 1, surface_areas[0] );
  polyhedron.setSurfaceArea( 2, surface_areas[1] );
  polyhedron.setSurfaceArea( 3, surface_areas[2] );
  polyhedron.setSurfaceArea( 4, surface_areas[3] );
  polyhedron.setSurfaceArea( 5, surface_areas[4] );
  polyhedron.setSurfaceArea( 6, surface_areas[5] );

  TEST_EQUALITY( polyhedron.getSurfaceArea( 1 ), surface_areas[0] );
  TEST_EQUALITY( polyhedron.getSurfaceArea( 2 ), surface_areas[1] );
  TEST_EQUALITY( polyhedron.getSurfaceArea( 3 ), surface_areas[2] );
  TEST_EQUALITY( polyhedron.getSurfaceArea( 4 ), surface_areas[3] );
  TEST_EQUALITY( polyhedron.getSurfaceArea( 5 ), surface_areas[4] );
  TEST_EQUALITY( polyhedron.getSurfaceArea( 6 ), surface_areas[5] );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, get_set_surface_area );

//---------------------------------------------------------------------------//
// Check that an iterator to the desired surface sense pair is returned
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   getSurfaceSensePair,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef Geometry::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;

  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the polyhedral cell
  Cell polyhedron( 0, cell_definition, surface_map );

  typename Cell::SurfaceSensePairsIterator desired_pair, end_pair;
  end_pair = polyhedron.endSurfaceSensePairs();

  // Get the first surface-sense pair
  desired_pair = polyhedron.getSurfaceSensePair( 1 );

  TEST_ASSERT( desired_pair != end_pair );
  TEST_EQUALITY_CONST( desired_pair->first->getId(), 1 );

  // Get the second surface-sense pair
  desired_pair = polyhedron.getSurfaceSensePair( 2 );

  TEST_ASSERT( desired_pair != end_pair );
  TEST_EQUALITY_CONST( desired_pair->first->getId(), 2 );

  // Get the third surface-sense pair
  desired_pair = polyhedron.getSurfaceSensePair( 3 );

  TEST_ASSERT( desired_pair != end_pair );
  TEST_EQUALITY_CONST( desired_pair->first->getId(), 3 );

  // Get the fourth surface-sense pair
  desired_pair = polyhedron.getSurfaceSensePair( 4 );

  TEST_ASSERT( desired_pair != end_pair );
  TEST_EQUALITY_CONST( desired_pair->first->getId(), 4 );

  // Get the fifth surface-sense pair
  desired_pair = polyhedron.getSurfaceSensePair( 5 );

  TEST_ASSERT( desired_pair != end_pair );
  TEST_EQUALITY_CONST( desired_pair->first->getId(), 5 );

  // Get the sixth surface-sense pair
  desired_pair = polyhedron.getSurfaceSensePair( 6 );

  TEST_ASSERT( desired_pair != end_pair );
  TEST_EQUALITY_CONST( desired_pair->first->getId(), 6 );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, getSurfaceSensePair );

//---------------------------------------------------------------------------//
// end tstCell.cpp
//---------------------------------------------------------------------------//
