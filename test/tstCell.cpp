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

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Cell.hpp"
#include "Surface.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define MAP_TYPEDEFS( space, map )					\
  typedef space::map<short,Teuchos::RCP<FACEMC::Surface<short,float> > >	map##_s_f; \
  typedef space::map<short,Teuchos::RCP<FACEMC::Surface<short,double> > > map##_s_d; \
  typedef space::map<int,Teuchos::RCP<FACEMC::Surface<int,float> > > map##_i_f; \
  typedef space::map<int,Teuchos::RCP<FACEMC::Surface<int,double> > > map##_i_d; \
  typedef space::map<long,Teuchos::RCP<FACEMC::Surface<long,float> > > map##_l_f; \
  typedef space::map<long,Teuchos::RCP<FACEMC::Surface<long,double> > > map##_l_d; \
  
#define UNIT_TEST_INSTANTIATION_STD_MAP( type, name )		\
  MAP_TYPEDEFS( std, map )						\
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, short, float, map_s_f) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, short, double, map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, int, float, map_i_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, int, double, map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, long, float, map_l_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, long, double, map_l_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, short, float, map_s_f) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, short, double, map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, float, map_i_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, double, map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, long, float, map_l_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, long, double, map_l_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, short, float, map_s_f) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, short, double, map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, int, float, map_i_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, int, double, map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, float, map_l_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, double, map_l_d ) \

#define UNIT_TEST_INSTANTIATION_BOOST_UMAP( type, name )		\
  MAP_TYPEDEFS( boost, unordered_map )					\
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, short, float, unordered_map_s_f) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, short, double, unordered_map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, int, float, unordered_map_i_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, int, double, unordered_map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, long, float, unordered_map_l_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, short, long, double, unordered_map_l_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, short, float, unordered_map_s_f) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, short, double, unordered_map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, float, unordered_map_i_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, int, double, unordered_map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, long, float, unordered_map_l_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, int, long, double, unordered_map_l_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, short, float, unordered_map_s_f) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, short, double, unordered_map_s_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, int, float, unordered_map_i_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, int, double, unordered_map_i_d ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, float, unordered_map_l_f ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( type, name, long, long, double, unordered_map_l_d ) \

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
class TestCell : public FACEMC::Cell<CellOrdinalType,
				     SurfaceOrdinalType,
				     ScalarType>
{
public:
  TestCell() : FACEMC::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>()
  { /* ... */ }
  
  virtual ~TestCell()
  { /* ... */ }

  using FACEMC::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::simplifyCellDefinitionString;
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
  typedef FACEMC::Surface<OrdinalType,ScalarType> Surface;
  
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
  typedef FACEMC::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;
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
// Check that a point can be tested as in a cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isIn,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef FACEMC::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;
  
  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Point in cell
  FACEMC::Vector<ScalarType> point_1( 0.0, 0.0, 0.0 );
  // Point outside of cell
  FACEMC::Vector<ScalarType> point_2( 10.0, 10.0, 10.0 );
  // Points on cell
  FACEMC::Vector<ScalarType> point_3( 2.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> point_4( -2.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> point_5( 0.0, 2.0, 0.0 );
  FACEMC::Vector<ScalarType> point_6( 0.0, -2.0, 0.0 );
  FACEMC::Vector<ScalarType> point_7( 0.0, 0.0, 2.0 );
  FACEMC::Vector<ScalarType> point_8( 0.0, 0.0, -2.0 );
  
  TEST_ASSERT( polyhedron.isIn( point_1 ) );
  TEST_ASSERT( !polyhedron.isIn( point_2 ) );
  TEST_ASSERT( !polyhedron.isIn( point_3 ) );
  TEST_ASSERT( !polyhedron.isIn( point_4 ) );
  TEST_ASSERT( !polyhedron.isIn( point_5 ) );
  TEST_ASSERT( !polyhedron.isIn( point_6 ) );
  TEST_ASSERT( !polyhedron.isIn( point_7 ) );
  TEST_ASSERT( !polyhedron.isIn( point_8 ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isIn );

//---------------------------------------------------------------------------//
// Check that a point can be tested as on a cell
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( Cell,
				   isOn,
				   CellOrdinalType,
				   SurfaceOrdinalType,
				   ScalarType,
				   SurfaceMap )
{
  typedef FACEMC::Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType> Cell;
  
  // Load the surfaces that define a cube
  std::string cell_definition;
  SurfaceMap surface_map;
  createConvexPolyhedronSurfaces( surface_map, cell_definition );

  // Create the cell
  Cell polyhedron( 0, cell_definition, surface_map );

  // Point in cell
  FACEMC::Vector<ScalarType> point_1( 0.0, 0.0, 0.0 );
  // Point outside of cell
  FACEMC::Vector<ScalarType> point_2( 10.0, 10.0, 10.0 );
  // Points on cell
  FACEMC::Vector<ScalarType> point_3( 2.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> point_4( -2.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> point_5( 0.0, 2.0, 0.0 );
  FACEMC::Vector<ScalarType> point_6( 0.0, -2.0, 0.0 );
  FACEMC::Vector<ScalarType> point_7( 0.0, 0.0, 2.0 );
  FACEMC::Vector<ScalarType> point_8( 0.0, 0.0, -2.0 );
  
  TEST_ASSERT( !polyhedron.isOn( point_1 ) );
  TEST_ASSERT( !polyhedron.isOn( point_2 ) );
  TEST_ASSERT( polyhedron.isOn( point_3 ) );
  TEST_ASSERT( polyhedron.isOn( point_4 ) );
  TEST_ASSERT( polyhedron.isOn( point_5 ) );
  TEST_ASSERT( polyhedron.isOn( point_6 ) );
  TEST_ASSERT( polyhedron.isOn( point_7 ) );
  TEST_ASSERT( polyhedron.isOn( point_8 ) );
}

UNIT_TEST_INSTANTIATION_BOOST_UMAP( Cell, isOn );

//---------------------------------------------------------------------------//
// end tstCell.cpp
//---------------------------------------------------------------------------//
