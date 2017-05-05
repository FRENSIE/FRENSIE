//---------------------------------------------------------------------------//
//!
//! \file   tstRootModel.cpp
//! \author Alex Robinson
//! \brief  Root model class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_RootModel.hpp"
#include "Geometry_RootModelPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::RootModelProperties> model_properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that Root can be initialized
TEUCHOS_UNIT_TEST( RootModel, initialize )
{
  std::shared_ptr<Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  TEST_ASSERT( !model->isInitialized() );
  TEST_NOTHROW( model->initialize( *model_properties ) );
  TEST_ASSERT( model->isInitialized() );
}

//---------------------------------------------------------------------------//
// Check that the model properties can be returned
TEUCHOS_UNIT_TEST( RootModel, getModelProperties )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  const Geometry::RootModelProperties& properties =
    model->getModelProperties();

  TEST_ASSERT( properties.getModelFileName().find( "basic_root_geometry.root" ) < properties.getModelFileName().size() );
  TEST_EQUALITY_CONST( properties.getMaterialPropertyName(), "mat" );
  TEST_EQUALITY_CONST( properties.getVoidMaterialName(), "void" );
  TEST_EQUALITY_CONST( properties.getTerminalMaterialName(), "graveyard" );
}

//---------------------------------------------------------------------------//
// Check if the model has cell estimator data
TEUCHOS_UNIT_TEST( RootModel, hasCellEstimatorData )
{
  TEST_ASSERT( !Geometry::RootModel::getInstance()->hasCellEstimatorData() );
}

//---------------------------------------------------------------------------//
// Get the material ids
TEUCHOS_UNIT_TEST( RootModel, getMaterialIds )
{
  Geometry::Model::MaterialIdSet material_ids;

  Geometry::RootModel::getInstance()->getMaterialIds( material_ids );

  TEST_EQUALITY_CONST( material_ids.size(), 1 );
  TEST_ASSERT( material_ids.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if the cells can be returned
TEUCHOS_UNIT_TEST( RootModel, getCells )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  Geometry::Model::CellIdSet cells;

  // Get all cells except the termination cells
  model->getCells( cells, true, false );

  TEST_EQUALITY_CONST( cells.size(), 2 );
  TEST_ASSERT( cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( !cells.count( 3 ) );

  cells.clear();

  // Get all cells except the void and termination cells
  model->getCells( cells, false, false );

  TEST_EQUALITY_CONST( cells.size(), 1 );
  TEST_ASSERT( !cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( !cells.count( 3 ) );

  cells.clear();

  // Get all cells except the void cells
  model->getCells( cells, false, true );

  TEST_EQUALITY_CONST( cells.size(), 2 );
  TEST_ASSERT( !cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( cells.count( 3 ) );

  cells.clear();

  // Get all cells
  model->getCells( cells, true, true );

  TEST_EQUALITY_CONST( cells.size(), 3 );
  TEST_ASSERT( cells.count( 1 ) );
  TEST_ASSERT( cells.count( 2 ) );
  TEST_ASSERT( cells.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Get the cell material names
TEUCHOS_UNIT_TEST( RootModel, getCellMaterialNames )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  std::map<Geometry::ModuleTraits::InternalCellHandle,std::string>
    cell_id_material_name_map;

  model->getCellMaterialNames( cell_id_material_name_map );

  TEST_EQUALITY_CONST( cell_id_material_name_map.size(), 3 );
  TEST_ASSERT( cell_id_material_name_map.count( 1 ) );
  TEST_ASSERT( cell_id_material_name_map.count( 2 ) );
  TEST_ASSERT( cell_id_material_name_map.count( 3 ) );
  TEST_EQUALITY_CONST( cell_id_material_name_map.find( 1 )->second, "void" );
  TEST_EQUALITY_CONST( cell_id_material_name_map.find( 2 )->second, "mat_1" );
  TEST_EQUALITY_CONST( cell_id_material_name_map.find( 3 )->second,
                       "graveyard" );
}

//---------------------------------------------------------------------------//
// Get the cell material ids
TEUCHOS_UNIT_TEST( RootModel, getCellMaterialIds )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  Geometry::Model::CellIdMatIdMap cell_id_mat_id_map;

  model->getCellMaterialIds( cell_id_mat_id_map );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.size(), 1 );
  TEST_ASSERT( cell_id_mat_id_map.count( 2 ) );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 2 )->second, 1 );
}

//---------------------------------------------------------------------------//
// Get the cell densities
TEUCHOS_UNIT_TEST( RootModel, getCellDensities )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  Geometry::Model::CellIdDensityMap cell_id_density_map;

  model->getCellDensities( cell_id_density_map );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 1 );
  TEST_ASSERT( cell_id_density_map.count( 2 ) );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 2 )->second, 1 );
}

//---------------------------------------------------------------------------//
// Get the cell estimator data (there shouldn't be any)
TEUCHOS_UNIT_TEST( RootModel, getCellEstimatorData )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  Geometry::Model::CellEstimatorIdDataMap cell_estimator_id_data_map;

  model->getCellEstimatorData( cell_estimator_id_data_map );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check if the cell exists
TEUCHOS_UNIT_TEST( RootModel, doesCellExist )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  TEST_ASSERT( model->doesCellExist( 1 ) );
  TEST_ASSERT( model->doesCellExist( 2 ) );
  TEST_ASSERT( model->doesCellExist( 3 ) );

  TEST_ASSERT( !model->doesCellExist( 4 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is a termination cell
TEUCHOS_UNIT_TEST( RootModel, isTerminationCell )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  TEST_ASSERT( !model->isTerminationCell( 1 ) );
  TEST_ASSERT( !model->isTerminationCell( 2 ) );
  TEST_ASSERT( model->isTerminationCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is a void cell
TEUCHOS_UNIT_TEST( RootModel, isVoidCell )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  TEST_ASSERT( model->isVoidCell( 1 ) );
  TEST_ASSERT( !model->isVoidCell( 2 ) );
  TEST_ASSERT( !model->isVoidCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Get if the cell volume
TEUCHOS_UNIT_TEST( RootModel, getCellVolume )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();
  
  TEST_FLOATING_EQUALITY( model->getCellVolume( 1 ),
                          934.550153050213,
                          1e-9 );

  TEST_FLOATING_EQUALITY( model->getCellVolume( 2 ),
                          65.4498469497874,
                          1e-9 );

  TEST_FLOATING_EQUALITY( model->getCellVolume( 3 ),
                          1744.0,
                          1e-9 );
}

//---------------------------------------------------------------------------//
// Check that a Root navigator can be created
TEUCHOS_UNIT_TEST( RootModel, createNavigatorAdvanced )
{
  std::shared_ptr<Geometry::RootNavigator> navigator(
               Geometry::RootModel::getInstance()->createNavigatorAdvanced() );

  TEST_ASSERT( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be created
TEUCHOS_UNIT_TEST( RootModel, createNavigator )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    Geometry::RootModel::getInstance()->createNavigator();

  TEST_ASSERT( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_xml_file",
                   &xml_file_name,
                   "Model properties xml file name" );

}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  Teuchos::RCP<const Teuchos::ParameterList> raw_model_properties =
    Teuchos::getParametersFromXmlFile( xml_file_name );

  model_properties = Geometry::RootModelPropertiesFactory::createProperties(
                                                       *raw_model_properties );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRoot.cpp
//---------------------------------------------------------------------------//
