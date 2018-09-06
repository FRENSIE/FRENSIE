//---------------------------------------------------------------------------//
//!
//! \file   tstRootModel.cpp
//! \author Alex Robinson
//! \brief  Root model class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// FRENSIE Includes
#include "Geometry_RootModel.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::RootModelProperties> model_properties;

bool cache_test_archive;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that Root can be initialized
FRENSIE_UNIT_TEST( RootModel, initialize )
{
  std::shared_ptr<Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  FRENSIE_CHECK( !model->isInitialized() );
  FRENSIE_CHECK_NO_THROW( model->initialize( *model_properties ) );
  FRENSIE_CHECK( model->isInitialized() );
}

//---------------------------------------------------------------------------//
// Check that the model properties can be returned
FRENSIE_UNIT_TEST( RootModel, getModelProperties )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  const Geometry::RootModelProperties& properties =
    model->getModelProperties();

  FRENSIE_CHECK( properties.getModelFileName().find( "basic_root_geometry.root" ) < properties.getModelFileName().size() );
  FRENSIE_CHECK_EQUAL( properties.getMaterialPropertyName(), "mat" );
  FRENSIE_CHECK_EQUAL( properties.getVoidMaterialName(), "void" );
  FRENSIE_CHECK_EQUAL( properties.getTerminalMaterialName(), "graveyard" );
}

//---------------------------------------------------------------------------//
// Check if the model has cell estimator data
FRENSIE_UNIT_TEST( RootModel, hasCellEstimatorData )
{
  FRENSIE_CHECK( !Geometry::RootModel::getInstance()->hasCellEstimatorData() );
}

//---------------------------------------------------------------------------//
// Get the material ids
FRENSIE_UNIT_TEST( RootModel, getMaterialIds )
{
  Geometry::Model::MaterialIdSet material_ids;

  Geometry::RootModel::getInstance()->getMaterialIds( material_ids );

  FRENSIE_CHECK_EQUAL( material_ids.size(), 1 );
  FRENSIE_CHECK( material_ids.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check if the cells can be returned
FRENSIE_UNIT_TEST( RootModel, getCells )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  Geometry::Model::CellIdSet cells;

  // Get all cells except the termination cells
  model->getCells( cells, true, false );

  FRENSIE_CHECK_EQUAL( cells.size(), 2 );
  FRENSIE_CHECK( cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 2 ) );
  FRENSIE_CHECK( !cells.count( 3 ) );

  cells.clear();

  // Get all cells except the void and termination cells
  model->getCells( cells, false, false );

  FRENSIE_CHECK_EQUAL( cells.size(), 1 );
  FRENSIE_CHECK( !cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 2 ) );
  FRENSIE_CHECK( !cells.count( 3 ) );

  cells.clear();

  // Get all cells except the void cells
  model->getCells( cells, false, true );

  FRENSIE_CHECK_EQUAL( cells.size(), 2 );
  FRENSIE_CHECK( !cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 2 ) );
  FRENSIE_CHECK( cells.count( 3 ) );

  cells.clear();

  // Get all cells
  model->getCells( cells, true, true );

  FRENSIE_CHECK_EQUAL( cells.size(), 3 );
  FRENSIE_CHECK( cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 2 ) );
  FRENSIE_CHECK( cells.count( 3 ) );
}

//---------------------------------------------------------------------------//
// Get the cell material names
FRENSIE_UNIT_TEST( RootModel, getCellMaterialNames )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  std::map<Geometry::Model::EntityId,std::string>
    cell_id_material_name_map;

  model->getCellMaterialNames( cell_id_material_name_map );

  FRENSIE_CHECK_EQUAL( cell_id_material_name_map.size(), 3 );
  FRENSIE_CHECK( cell_id_material_name_map.count( 1 ) );
  FRENSIE_CHECK( cell_id_material_name_map.count( 2 ) );
  FRENSIE_CHECK( cell_id_material_name_map.count( 3 ) );
  FRENSIE_CHECK_EQUAL( cell_id_material_name_map.find( 1 )->second, "void" );
  FRENSIE_CHECK_EQUAL( cell_id_material_name_map.find( 2 )->second, "mat_1" );
  FRENSIE_CHECK_EQUAL( cell_id_material_name_map.find( 3 )->second,
                       "graveyard" );
}

//---------------------------------------------------------------------------//
// Get the cell material ids
FRENSIE_UNIT_TEST( RootModel, getCellMaterialIds )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  Geometry::Model::CellIdMatIdMap cell_id_mat_id_map;

  model->getCellMaterialIds( cell_id_mat_id_map );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.size(), 1 );
  FRENSIE_CHECK( cell_id_mat_id_map.count( 2 ) );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 2 )->second, 1 );
}

//---------------------------------------------------------------------------//
// Get the cell densities
FRENSIE_UNIT_TEST( RootModel, getCellDensities )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  Geometry::Model::CellIdDensityMap cell_id_density_map;

  model->getCellDensities( cell_id_density_map );

  FRENSIE_REQUIRE_EQUAL( cell_id_density_map.size(), 1 );
  FRENSIE_REQUIRE( cell_id_density_map.count( 2 ) );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 2 )->second,
                       1e24/cgs::cubic_centimeter );
}

//---------------------------------------------------------------------------//
// Get the cell estimator data (there shouldn't be any)
FRENSIE_UNIT_TEST( RootModel, getCellEstimatorData )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  Geometry::Model::CellEstimatorIdDataMap cell_estimator_id_data_map;

  model->getCellEstimatorData( cell_estimator_id_data_map );

  FRENSIE_CHECK_EQUAL( cell_estimator_id_data_map.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check if the cell exists
FRENSIE_UNIT_TEST( RootModel, doesCellExist )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  FRENSIE_CHECK( model->doesCellExist( 1 ) );
  FRENSIE_CHECK( model->doesCellExist( 2 ) );
  FRENSIE_CHECK( model->doesCellExist( 3 ) );

  FRENSIE_CHECK( !model->doesCellExist( 4 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is a termination cell
FRENSIE_UNIT_TEST( RootModel, isTerminationCell )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  FRENSIE_CHECK( !model->isTerminationCell( 1 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 2 ) );
  FRENSIE_CHECK( model->isTerminationCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Check if a cell is a void cell
FRENSIE_UNIT_TEST( RootModel, isVoidCell )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  FRENSIE_CHECK( model->isVoidCell( 1 ) );
  FRENSIE_CHECK( !model->isVoidCell( 2 ) );
  FRENSIE_CHECK( !model->isVoidCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Get if the cell volume
FRENSIE_UNIT_TEST( RootModel, getCellVolume )
{
  std::shared_ptr<const Geometry::RootModel> model =
    Geometry::RootModel::getInstance();

  FRENSIE_CHECK_FLOATING_EQUALITY( model->getCellVolume( 1 ),
                                   934.550153050213*cgs::cubic_centimeter,
                                   1e-9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( model->getCellVolume( 2 ),
                                   65.4498469497874*cgs::cubic_centimeter,
                                   1e-9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( model->getCellVolume( 3 ),
                                   1744.0*cgs::cubic_centimeter,
                                   1e-9 );
}

//---------------------------------------------------------------------------//
// Check that a Root navigator can be created
FRENSIE_UNIT_TEST( RootModel, createNavigatorAdvanced )
{
  std::shared_ptr<Geometry::RootNavigator> navigator(
               Geometry::RootModel::getInstance()->createNavigatorAdvanced() );

  FRENSIE_CHECK( navigator.get() != NULL );

  navigator.reset( Geometry::RootModel::getInstance()->createNavigatorAdvanced( [](const Geometry::Navigator::Length distance){ std::cout << "advanced " << distance << std::endl; } ) );

  FRENSIE_CHECK( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be created
FRENSIE_UNIT_TEST( RootModel, createNavigator )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    Geometry::RootModel::getInstance()->createNavigator();

  FRENSIE_CHECK( navigator.get() != NULL );

  navigator =
    Geometry::RootModel::getInstance()->createNavigator( [](const Geometry::Navigator::Length distance){ std::cout << "advanced " << distance << std::endl; } );
  FRENSIE_CHECK( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( RootModel, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_name( "test_root_model" );
  std::ostringstream archive_ostream;

  std::unique_ptr<OArchive> oarchive;

  createOArchive( archive_name, archive_ostream, oarchive );

  auto model = Geometry::RootModel::getInstance();

  FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( "model", model ) );

  oarchive.reset();

  if( cache_test_archive && archive_name.find(".h5a") >= archive_name.size() )
  {
    std::unique_ptr<std::ofstream> ofstream;

    if( archive_name.find( ".bin" ) < archive_name.size() )
    {
      ofstream.reset( new std::ofstream( archive_name, std::ofstream::binary ) );
    }
    else
    {
      ofstream.reset( new std::ofstream( archive_name ) );
    }

    (*ofstream) << archive_ostream.str();
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "cache_test_archive",
                                        cache_test_archive, false,
                                        "Cache the test archive" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );
  local_properties.setMaterialPropertyName("mat");

  model_properties.reset( new Geometry::RootModelProperties( local_properties ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRoot.cpp
//---------------------------------------------------------------------------//
