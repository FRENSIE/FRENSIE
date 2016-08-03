//---------------------------------------------------------------------------//
//!
//! \file   tstCellInputValidator.cpp
//! \author Alex Robinson
//! \brief  Cell input validator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "Geometry_CellInputValidator.hpp"
#include "Geometry_SurfaceInputValidator.hpp"

//---------------------------------------------------------------------------//
// Test XML File Name
//---------------------------------------------------------------------------//
std::string test_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an individual cell can be validated
TEUCHOS_UNIT_TEST( CellInputValidator, validateCell )
{
  std::set<std::string> surface_names;
  surface_names.insert( "surface_1" );
  surface_names.insert( "surface_2" );
  surface_names.insert( "surface_3" );
  surface_names.insert( "surface_4" );
  surface_names.insert( "surface_5" );

  Teuchos::ParameterList valid_cell( "test_cell" );
  valid_cell.set( "definition", "surface_1 n -surface_2 n surface_3 u (-surface_4 n surface_5)" );
  valid_cell.set( "material", "mat_1" );
  valid_cell.set<double>( "density", 1.0 );
  valid_cell.set( "special attribute", "forced collision" );

  TEST_NOTHROW( Geometry::CellInputValidator::validateCell( valid_cell,
							  valid_cell.name(),
							  surface_names ) );
  Teuchos::ParameterList invalid_cell_1( "test__cell" );
  invalid_cell_1.set( "definition", "surface_1 n -surface_5" );
  invalid_cell_1.set( "material", "mat_1" );

  TEST_THROW( Geometry::CellInputValidator::validateCell( invalid_cell_1,
							invalid_cell_1.name(),
							surface_names ),
	      std::invalid_argument );

  Teuchos::ParameterList invalid_cell_2( "test___cell" );

  TEST_THROW( Geometry::CellInputValidator::validateCell( invalid_cell_2,
							invalid_cell_2.name(),
							surface_names ),
	      std::invalid_argument );

  Teuchos::ParameterList copy_cell( "test_cell" );

  TEST_THROW( Geometry::CellInputValidator::validateCell( copy_cell,
							copy_cell.name(),
							surface_names ),
	      std::invalid_argument );

  Geometry::CellInputValidator::clearCellNames();
  Geometry::CellInputValidator::clearMaterialNames();
}

//---------------------------------------------------------------------------//
// Check that all cells can be validated
TEUCHOS_UNIT_TEST( CellInputValidator, validateAllCells )
{
  // Read in the geometry parameter list from the xml file
  Teuchos::ParameterList geometry( "geometry" );

  Teuchos::updateParametersFromXmlFile( test_xml_file_name,
					Teuchos::inoutArg( geometry ) );

  // Validate the surfaces
  Geometry::SurfaceInputValidator::validateAllSurfaces(
					geometry.sublist( "surfaces", true ) );

  // Get the surface names
  std::set<std::string> surface_names =
    Geometry::SurfaceInputValidator::getSurfaceNames();

  // Validate the cells
  TEST_NOTHROW( Geometry::CellInputValidator::validateAllCells(
					     geometry.sublist( "cells", true ),
					     surface_names ) );
}

//---------------------------------------------------------------------------//
// Check that cell names can be recovered
TEUCHOS_UNIT_TEST( CellInputValidator, getCellNames )
{
  std::set<std::string> cell_names =
    Geometry::CellInputValidator::getCellNames();

  TEST_EQUALITY_CONST( cell_names.size(), 4 );
  TEST_ASSERT( cell_names.count( "left_cube" ) );
  TEST_ASSERT( cell_names.count( "right_cube" ) );
  TEST_ASSERT( cell_names.count( "surrounding_cuboid" ) );
  TEST_ASSERT( cell_names.count( "graveyard" ) );
  TEST_ASSERT( !cell_names.count( "no_such_cell" ) );
}

//---------------------------------------------------------------------------//
// Check that cell material names can be recovered
TEUCHOS_UNIT_TEST( CellInputValidator, getMaterialNames )
{
  std::set<std::string> material_names =
    Geometry::CellInputValidator::getMaterialNames();

  TEST_EQUALITY_CONST( material_names.size(), 1 );
  TEST_ASSERT( material_names.count( "water" ) );
  TEST_ASSERT( !material_names.count( "no_such_material" ) );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xml_file",
		 &test_xml_file_name,
		 "Test xml file name with geometry defined" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstCellInputValidator.cpp
//---------------------------------------------------------------------------//
