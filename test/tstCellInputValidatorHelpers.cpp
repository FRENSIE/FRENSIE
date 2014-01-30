//---------------------------------------------------------------------------//
//!
//! \file   tstCellInputValidatorHelpers.cpp
//! \author Alex Robinson
//! \brief  Cell input validator helper function unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "CellInputValidatorHelpers.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell name can be validated
TEUCHOS_UNIT_TEST( CellInputValidatorHelpers, validateCellName )
{
  std::string good_cell_name = "cell_1";
  std::string bad_cell_name = "cell 1";

  TEST_NOTHROW( FACEMC::validateCellName( good_cell_name ) );
  
  TEST_THROW( FACEMC::validateCellName( bad_cell_name ),
	      std::invalid_argument );  
}

//---------------------------------------------------------------------------//
// Check that the cell material can be validated
TEUCHOS_UNIT_TEST( CellInputValidatorHelpers, validateCellMaterial )
{
  std::string good_material_name = "material_1";
  std::string bad_material_name = "material 1";

  TEST_NOTHROW( FACEMC::validateCellMaterial( good_material_name, "cell-1" ) );
  
  TEST_THROW( FACEMC::validateCellMaterial( bad_material_name, "cell_1" ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the cell density can be validated
TEUCHOS_UNIT_TEST( CellInputValidatorHelpers, validateCellDensity )
{
  double good_density = 1.0;
  double bad_density = -1.0;

  TEST_NOTHROW( FACEMC::validateCellDensity( good_density, "cell=1" ) );
  
  TEST_THROW( FACEMC::validateCellDensity( bad_density, "cell*1" ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the cell special attribute can be validated
TEUCHOS_UNIT_TEST( CellInputValidatorHelpers, validateCellSpecialAttribute )
{
  std::string valid_attribute_1 = "forced collision";
  std::string valid_attribute_2 = "graveyard";
  std::string invalid_attribute = "reflecting";

  TEST_NOTHROW( FACEMC::validateCellSpecialAttribute( valid_attribute_1,
						      "cell-1" ) );
  TEST_NOTHROW( FACEMC::validateCellSpecialAttribute( valid_attribute_2,
						      "cell_1" ) );

  TEST_THROW( FACEMC::validateCellSpecialAttribute( invalid_attribute,
						    "cell_1" ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// Check that the cell definition can be validated
TEUCHOS_UNIT_TEST( CellInputValidatorHelpers, validateCellDefinition )
{
  std::set<std::string> surface_names;
  surface_names.insert( "surface_1" );
  surface_names.insert( "surface_2" );
  surface_names.insert( "surface_3" );
  surface_names.insert( "surface_4" );
  surface_names.insert( "surface_5" );
  surface_names.insert( "surface_6" );
  surface_names.insert( "surface_7" );
  
  std::string valid_cell_definition_1 = "(surface_1 n -surface_2 n surface_3 n -surface_4 n surface_5 n -surface_6) u -surface_7";

  std::string valid_cell_definition_2 = "surface_1 n -surface_5";

  std::string invalid_cell_definition = "-surface_8";

  TEST_NOTHROW( FACEMC::validateCellDefinition( valid_cell_definition_1,
						"cell_1",
						surface_names ) );

  FACEMC::validateCellDefinition( valid_cell_definition_2,
				  "cell_2",
				  surface_names );

  TEST_THROW( FACEMC::validateCellDefinition( invalid_cell_definition,
					      "cell_3",
					      surface_names ),
	      std::invalid_argument );
}

//---------------------------------------------------------------------------//
// end tstCellInputValidatorHelpers.cpp
//---------------------------------------------------------------------------//
