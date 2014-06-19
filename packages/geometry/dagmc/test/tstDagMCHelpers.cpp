//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCHelpers.cpp
//! \author Alex Robinson
//! \brief  DagMC helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>

// FRENSIE Includes
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geometry_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a set of property names can be validated
TEUCHOS_UNIT_TEST( DagMCHelpers, validatePropertyNames )
{
  std::vector<std::string> available_property_names( 3 );
  std::vector<std::string> valid_property_names( 3 );
  std::string invalid_property_names;

  available_property_names[0] = "graveyard";
  available_property_names[1] = "material";
  available_property_names[2] = "badprop";
  
  valid_property_names[0] = "graveyard";
  valid_property_names[1] = "material";
  valid_property_names[2] = "density";

  Geometry::validatePropertyNames( available_property_names,
				   valid_property_names,
				   invalid_property_names );
  
  TEST_EQUALITY_CONST( invalid_property_names.compare( "badprop" ), 0 );
}

//---------------------------------------------------------------------------//
// Check that DagMC can be initialized
TEUCHOS_UNIT_TEST( DagMCHelpers, initializeDagMC )
{
  // Set up the valid property names
  std::vector<std::string> property_names( 4 );
  property_names[0] = "graveyard";
  property_names[1] = "mat";
  property_names[2] = "rho";
  property_names[3] = "tally";
  
  // Initialize DagMC
  Geometry::initializeDagMC( test_geometry_file_name,
  			     property_names,
  			     1e-3 );
}

//---------------------------------------------------------------------------//
// Check that all property values associated with a property can be returned
TEUCHOS_UNIT_TEST( DagMCHelpers, getPropertyValues )
{
  std::vector<std::string> values;

  Geometry::getPropertyValues( "mat", values );

  TEST_EQUALITY_CONST( values.size(), 8 );
  TEST_ASSERT(std::find( values.begin(), values.end(), "1" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "2" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "3" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "4" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "7" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "8" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "9" ) != values.end());
  TEST_ASSERT(std::find( values.begin(), values.end(), "10" ) != values.end());
}

//---------------------------------------------------------------------------//
// Check that the property values assigned to cells can be returned
TEUCHOS_UNIT_TEST( DagMCHelpers, getCellPropertyValues )
{
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> >
    cell_id_prop_value_map;
  
  Geometry::getCellPropertyValues( "mat", cell_id_prop_value_map );
  
  TEST_EQUALITY_CONST( cell_id_prop_value_map[26].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[26][0], "9" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[27].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[27][0], "9" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[80].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[80][0], "9" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[81].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[81][0], "9" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[9].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[9][0], "1" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[88].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[88][0], "1" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[136].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[136][0], "2" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[19].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[19][0], "3" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[184].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[184][0], "3" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[3].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[3][0], "4" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[7].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[7][0], "4" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[5].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[5][0], "10" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[1].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[1][0], "8" );

  TEST_EQUALITY_CONST( cell_id_prop_value_map[13].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[13][0], "7" );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[168].size(), 1 );
  TEST_EQUALITY_CONST( cell_id_prop_value_map[168][0], "7" );
}

//---------------------------------------------------------------------------//
// Check that the property values assigned to surfaces can be returned
TEUCHOS_UNIT_TEST( DagMCHelpers, getSurfacePropertyValues )
{
  boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,
		       std::vector<std::string> >
    surface_id_prop_value_map;

  Geometry::getSurfacePropertyValues( "tally", surface_id_prop_value_map );
  
  TEST_EQUALITY_CONST( surface_id_prop_value_map[7].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[7][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[7][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[7][2], "7.surface.current.n");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[7][3], "8.surface.current.p");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[16].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[16][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[16][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[16][2],"7.surface.current.n");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[16][3],"8.surface.current.p");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[25].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[25][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[25][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[25][2],"7.surface.current.n");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[25][3],"8.surface.current.p");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[34].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[34][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[34][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[34][2],"7.surface.current.n");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[34][3],"8.surface.current.p");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[94].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[94][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[94][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[94][2],"7.surface.current.n");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[94][3],"8.surface.current.p");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[202].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[202][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[202][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST(surface_id_prop_value_map[202][2],"7.surface.current.n");
  TEST_EQUALITY_CONST(surface_id_prop_value_map[202][3],"8.surface.current.p");
  TEST_EQUALITY_CONST( surface_id_prop_value_map[310].size(), 4 );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[310][0], "5.surface.flux.n" );
  TEST_EQUALITY_CONST( surface_id_prop_value_map[310][1], "6.surface.flux.p" );
  TEST_EQUALITY_CONST(surface_id_prop_value_map[310][2],"7.surface.current.n");
  TEST_EQUALITY_CONST(surface_id_prop_value_map[310][3],"8.surface.current.p");
}

//---------------------------------------------------------------------------//
// Check that the cell ids with a property value can be returned
TEUCHOS_UNIT_TEST( DagMCHelpers, getCellIdsWithPropertyValue )
{
  boost::unordered_map<std::string,
		      std::vector<Geometry::ModuleTraits::InternalCellHandle> >
    prop_value_cell_id_map;

  Geometry::getCellIdsWithPropertyValue( "mat", prop_value_cell_id_map );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["9"].size(), 36 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["9"].front(), 26 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["9"].back(), 81 );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["1"].size(), 2 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["1"].front(), 9 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["1"].back(), 88 );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["2"].size(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["2"].front(), 136 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["2"].back(), 136 );
  
  TEST_EQUALITY_CONST( prop_value_cell_id_map["3"].size(), 7 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["3"].front(), 19 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["3"].back(), 184 );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].size(), 2 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].front(), 3 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].back(), 7 );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["10"].size(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["10"].front(), 5 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["10"].back(), 5 );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["8"].size(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["8"].front(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["8"].back(), 1 );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].size(), 2 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].front(), 3 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].back(), 7 );
  
  TEST_EQUALITY_CONST( prop_value_cell_id_map["7"].size(), 4 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["7"].front(), 13 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["7"].back(), 168 );
}

//---------------------------------------------------------------------------//
// Check that the surface ids with a property value can be returned
TEUCHOS_UNIT_TEST( DagMCHelpers, getSurfaceIdsWithPropertyValue )
{
  boost::unordered_map<std::string,
		   std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> >
    prop_value_surface_id_map;

  Geometry::getSurfaceIdsWithPropertyValue("tally", prop_value_surface_id_map);

  TEST_EQUALITY_CONST( prop_value_surface_id_map["5.surface.flux.n"].size(), 
		       7 );
  TEST_EQUALITY_CONST( prop_value_surface_id_map["5.surface.flux.n"].front(), 
		       7 );
  TEST_EQUALITY_CONST( prop_value_surface_id_map["5.surface.flux.n"].back(), 
		       310 );

  TEST_EQUALITY_CONST( prop_value_surface_id_map["6.surface.flux.p"].size(), 
		       7 );
  TEST_EQUALITY_CONST( prop_value_surface_id_map["6.surface.flux.p"].front(), 
		       7 );
  TEST_EQUALITY_CONST( prop_value_surface_id_map["6.surface.flux.p"].back(), 
		       310 );

  TEST_EQUALITY_CONST( prop_value_surface_id_map["7.surface.current.n"].size(),
		       7 );
  TEST_EQUALITY_CONST(prop_value_surface_id_map["7.surface.current.n"].front(),
		       7 );
  TEST_EQUALITY_CONST( prop_value_surface_id_map["7.surface.current.n"].back(),
		       310 );

  TEST_EQUALITY_CONST( prop_value_surface_id_map["8.surface.current.p"].size(),
		       7 );
  TEST_EQUALITY_CONST(prop_value_surface_id_map["8.surface.current.p"].front(),
		       7 );
  TEST_EQUALITY_CONST( prop_value_surface_id_map["8.surface.current.p"].back(),
		       310 );
}  

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_sat_file",
		 &test_geometry_file_name,
		 "Test sat file name" );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}
				  
//---------------------------------------------------------------------------//
// end tstDagMCHelpers.cpp
//---------------------------------------------------------------------------//
