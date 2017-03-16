//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCModel.cpp
//! \author Alex Robinson
//! \brief  DagMC model class unit tests
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
#include "Geometry_DagMCModel.hpp"
#include "Geometry_DagMCModelPropertiesFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::DagMCModelProperties> model_properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that DagMC can be initialized
TEUCHOS_UNIT_TEST( DagMCModel, initialize )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  TEST_ASSERT( !model->isInitialized() );
  TEST_NOTHROW( model->initialize( *model_properties ) );

  TEST_ASSERT( model->isInitialized() );
}

//---------------------------------------------------------------------------//
// Check that the model properties can be retrieved
TEUCHOS_UNIT_TEST( DagMCModel, getModelProperties )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  const Geometry::DagMCModelProperties& cached_properties =
    model->getModelProperties();

  TEST_ASSERT( cached_properties.getModelFileName().find( "test_geom.sat" ) <
               cached_properties.getModelFileName().size() );
                       
}

//---------------------------------------------------------------------------//
// Check if the model has cell estimator data
TEUCHOS_UNIT_TEST( DagMCModel, hasCellEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  TEST_ASSERT( model->hasCellEstimatorData() );
}

//---------------------------------------------------------------------------//
// Check if the model has surface estimator data
TEUCHOS_UNIT_TEST( DagMCModel, hasSurfaceEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  TEST_ASSERT( model->hasSurfaceEstimatorData() );
}

//---------------------------------------------------------------------------//
// Check that the material ids can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getMaterialIds )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  Geometry::Model::MaterialIdSet material_ids;

  TEST_NOTHROW( model->getMaterialIds( material_ids ) );

  TEST_EQUALITY_CONST( material_ids.size(), 8 );
  TEST_ASSERT( material_ids.count( 1 ) );
  TEST_ASSERT( material_ids.count( 2 ) );
  TEST_ASSERT( material_ids.count( 3 ) );
  TEST_ASSERT( material_ids.count( 4 ) );
  TEST_ASSERT( material_ids.count( 7 ) );
  TEST_ASSERT( material_ids.count( 8 ) );
  TEST_ASSERT( material_ids.count( 9 ) );
  TEST_ASSERT( material_ids.count( 10 ) );
}

//---------------------------------------------------------------------------//
// Check that the problem cells can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getCells )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  Geometry::Model::CellIdSet cells;

  // Get all cells
  model->getCells( cells, true, true );

  // 55 + implicit compliment cell
  TEST_EQUALITY_CONST( cells.size(), 56 );

  TEST_ASSERT( cells.count( 1 ) );
  TEST_ASSERT( cells.count( 3 ) );
  TEST_ASSERT( cells.count( 5 ) );
  TEST_ASSERT( cells.count( 7 ) );
  TEST_ASSERT( cells.count( 9 ) );
  TEST_ASSERT( cells.count( 13 ) );
  TEST_ASSERT( cells.count( 19 ) );
  TEST_ASSERT( cells.count( 26 ) );
  TEST_ASSERT( cells.count( 27 ) );
  TEST_ASSERT( cells.count( 28 ) );
  TEST_ASSERT( cells.count( 29 ) );
  TEST_ASSERT( cells.count( 30 ) );
  TEST_ASSERT( cells.count( 31 ) );
  TEST_ASSERT( cells.count( 32 ) );
  TEST_ASSERT( cells.count( 33 ) );
  TEST_ASSERT( cells.count( 34 ) );
  TEST_ASSERT( cells.count( 35 ) );
  TEST_ASSERT( cells.count( 36 ) );
  TEST_ASSERT( cells.count( 37 ) );
  TEST_ASSERT( cells.count( 41 ) );
  TEST_ASSERT( cells.count( 48 ) );
  TEST_ASSERT( cells.count( 49 ) );
  TEST_ASSERT( cells.count( 50 ) );
  TEST_ASSERT( cells.count( 51 ) );
  TEST_ASSERT( cells.count( 52 ) );
  TEST_ASSERT( cells.count( 53 ) );
  TEST_ASSERT( cells.count( 54 ) );
  TEST_ASSERT( cells.count( 55 ) );
  TEST_ASSERT( cells.count( 56 ) );
  TEST_ASSERT( cells.count( 57 ) );
  TEST_ASSERT( cells.count( 58 ) );
  TEST_ASSERT( cells.count( 59 ) );
  TEST_ASSERT( cells.count( 63 ) );
  TEST_ASSERT( cells.count( 70 ) );
  TEST_ASSERT( cells.count( 71 ) );
  TEST_ASSERT( cells.count( 72 ) );
  TEST_ASSERT( cells.count( 73 ) );
  TEST_ASSERT( cells.count( 74 ) );
  TEST_ASSERT( cells.count( 75 ) );
  TEST_ASSERT( cells.count( 76 ) );
  TEST_ASSERT( cells.count( 77 ) );
  TEST_ASSERT( cells.count( 78 ) );
  TEST_ASSERT( cells.count( 79 ) );
  TEST_ASSERT( cells.count( 80 ) );
  TEST_ASSERT( cells.count( 81 ) );
  TEST_ASSERT( cells.count( 82 ) );
  TEST_ASSERT( cells.count( 83 ) );
  TEST_ASSERT( cells.count( 88 ) );
  TEST_ASSERT( cells.count( 136 ) );
  TEST_ASSERT( cells.count( 152 ) );
  TEST_ASSERT( cells.count( 154 ) );
  TEST_ASSERT( cells.count( 166 ) );
  TEST_ASSERT( cells.count( 168 ) );
  TEST_ASSERT( cells.count( 184 ) );
  TEST_ASSERT( cells.count( 188 ) );
  TEST_ASSERT( cells.count( 189 ) );

  cells.clear();
  
  // Get all cells except the termination cell
  model->getCells( cells, true, false );

  TEST_EQUALITY_CONST( cells.size(), 55 );
  TEST_ASSERT( !cells.count( 188 ) );

  cells.clear();
  
  // Get all cells exept the void cells
  model->getCells( cells, false, true );

  TEST_EQUALITY_CONST( cells.size(), 55 );
  TEST_ASSERT( !cells.count( 189 ) );

  cells.clear();

  // Get cells with a material only
  model->getCells( cells, false, false );

  TEST_EQUALITY_CONST( cells.size(), 54 );
  TEST_ASSERT( !cells.count( 188 ) );
  TEST_ASSERT( !cells.count( 189 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell material ids can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getCellMaterialIds )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  Geometry::Model::CellIdMatIdMap cell_id_mat_id_map;

  TEST_NOTHROW( model->getCellMaterialIds( cell_id_mat_id_map ) );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 9 )->second, 1 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 88 )->second, 1 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 136 )->second, 2 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 19 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 41 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 63 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 82 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 152 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 166 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 184 )->second, 3 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 3 )->second, 4 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 7 )->second, 4 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 13 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 83 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 154 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 168 )->second, 7 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 1 )->second, 8 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 26 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 27 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 28 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 29 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 30 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 31 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 32 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 33 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 34 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 35 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 36 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 37 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 48 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 49 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 50 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 51 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 52 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 53 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 54 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 55 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 56 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 57 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 58 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 59 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 70 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 71 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 72 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 73 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 74 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 75 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 76 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 77 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 78 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 79 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 80 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 81 )->second, 9 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 5 )->second, 10 );
}

//---------------------------------------------------------------------------//
// Check that the cell densities can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getCellDensities )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  Geometry::Model::CellIdDensityMap cell_id_density_map;

  TEST_NOTHROW( model->getCellDensities( cell_id_density_map ) );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 9 )->second, -8.027 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 88 )->second, -8.027 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 136 )->second, -7.75 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 19 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 41 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 63 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 82 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 152 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 166 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 184 )->second, -0.001633 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 3 )->second, -0.99823 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 7 )->second, -0.99823 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 13 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 83 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 154 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 168 )->second, -5.65 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 1 )->second, -1.8583 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 26 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 27 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 28 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 29 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 30 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 31 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 32 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 33 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 34 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 35 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 36 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 37 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 48 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 49 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 50 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 51 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 52 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 53 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 54 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 55 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 56 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 57 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 58 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 59 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 70 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 71 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 72 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 73 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 74 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 75 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 76 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 77 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 78 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 79 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 80 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 81 )->second, -7.83 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 5 )->second, -13.31 );
}

//---------------------------------------------------------------------------//
// Check that the cell estimator data can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getCellEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  Geometry::Model::CellEstimatorIdDataMap cell_estimator_id_data_map;

  TEST_NOTHROW( model->getCellEstimatorData( cell_estimator_id_data_map ) );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.size(), 5 );
  TEST_ASSERT( cell_estimator_id_data_map.count( 0 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 1 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 2 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 3 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 4 ) );

  TEST_EQUALITY_CONST( Utility::get<0>(cell_estimator_id_data_map.find(0)->second ),
                       Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(cell_estimator_id_data_map.find(0)->second),
                       Geometry::NEUTRON );
  TEST_EQUALITY_CONST( Utility::get<2>(cell_estimator_id_data_map.find(0)->second).size(),
                       55 );

  TEST_EQUALITY_CONST( Utility::get<0>(cell_estimator_id_data_map.find(1)->second),
                       Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(cell_estimator_id_data_map.find(1)->second),
                       Geometry::PHOTON );
  TEST_EQUALITY_CONST( Utility::get<2>(cell_estimator_id_data_map.find(1)->second).size(),
                       55 );

  TEST_EQUALITY_CONST( Utility::get<0>(cell_estimator_id_data_map.find(2)->second),
                       Geometry::CELL_COLLISION_FLUX_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(cell_estimator_id_data_map.find(2)->second),
                       Geometry::NEUTRON );
  TEST_EQUALITY_CONST( Utility::get<2>(cell_estimator_id_data_map.find(2)->second).size(),
                       36 );

  TEST_EQUALITY_CONST( Utility::get<0>(cell_estimator_id_data_map.find(3)->second),
                       Geometry::CELL_COLLISION_FLUX_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(cell_estimator_id_data_map.find(3)->second),
                       Geometry::PHOTON );
  TEST_EQUALITY_CONST( Utility::get<2>(cell_estimator_id_data_map.find(3)->second).size(),
                       36 );

  TEST_EQUALITY_CONST( Utility::get<0>(cell_estimator_id_data_map.find(4)->second),
                       Geometry::CELL_PULSE_HEIGHT_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(cell_estimator_id_data_map.find(4)->second),
                       Geometry::PHOTON );
  TEST_EQUALITY_CONST( Utility::get<2>(cell_estimator_id_data_map.find(4)->second).size(),
                       2 );
}

//---------------------------------------------------------------------------//
// Check if cells exist
TEUCHOS_UNIT_TEST( DagMCModel, doesCellExist )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  TEST_ASSERT( !model->doesCellExist( 0 ) );
  TEST_ASSERT( model->doesCellExist( 1 ) );
  TEST_ASSERT( !model->doesCellExist( 2 ) );
  TEST_ASSERT( model->doesCellExist( 3 ) );
  TEST_ASSERT( !model->doesCellExist( 4 ) );
  TEST_ASSERT( model->doesCellExist( 5 ) );
  TEST_ASSERT( !model->doesCellExist( 6 ) );
  TEST_ASSERT( model->doesCellExist( 7 ) );
  TEST_ASSERT( !model->doesCellExist( 8 ) );
  TEST_ASSERT( model->doesCellExist( 9 ) );
  TEST_ASSERT( model->doesCellExist( 13 ) );
  TEST_ASSERT( model->doesCellExist( 19 ) );
  TEST_ASSERT( model->doesCellExist( 26 ) );
  TEST_ASSERT( model->doesCellExist( 27 ) );
  TEST_ASSERT( model->doesCellExist( 28 ) );
  TEST_ASSERT( model->doesCellExist( 29 ) );
  TEST_ASSERT( model->doesCellExist( 30 ) );
  TEST_ASSERT( model->doesCellExist( 31 ) );
  TEST_ASSERT( model->doesCellExist( 32 ) );
  TEST_ASSERT( model->doesCellExist( 33 ) );
  TEST_ASSERT( model->doesCellExist( 34 ) );
  TEST_ASSERT( model->doesCellExist( 35 ) );
  TEST_ASSERT( model->doesCellExist( 36 ) );
  TEST_ASSERT( model->doesCellExist( 37 ) );
  TEST_ASSERT( model->doesCellExist( 41 ) );
  TEST_ASSERT( model->doesCellExist( 48 ) );
  TEST_ASSERT( model->doesCellExist( 49 ) );
  TEST_ASSERT( model->doesCellExist( 50 ) );
  TEST_ASSERT( model->doesCellExist( 51 ) );
  TEST_ASSERT( model->doesCellExist( 52 ) );
  TEST_ASSERT( model->doesCellExist( 53 ) );
  TEST_ASSERT( model->doesCellExist( 54 ) );
  TEST_ASSERT( model->doesCellExist( 55 ) );
  TEST_ASSERT( model->doesCellExist( 56 ) );
  TEST_ASSERT( model->doesCellExist( 57 ) );
  TEST_ASSERT( model->doesCellExist( 58 ) );
  TEST_ASSERT( model->doesCellExist( 59 ) );
  TEST_ASSERT( model->doesCellExist( 63 ) );
  TEST_ASSERT( model->doesCellExist( 70 ) );
  TEST_ASSERT( model->doesCellExist( 71 ) );
  TEST_ASSERT( model->doesCellExist( 72 ) );
  TEST_ASSERT( model->doesCellExist( 73 ) );
  TEST_ASSERT( model->doesCellExist( 74 ) );
  TEST_ASSERT( model->doesCellExist( 75 ) );
  TEST_ASSERT( model->doesCellExist( 76 ) );
  TEST_ASSERT( model->doesCellExist( 77 ) );
  TEST_ASSERT( model->doesCellExist( 78 ) );
  TEST_ASSERT( model->doesCellExist( 79 ) );
  TEST_ASSERT( model->doesCellExist( 80 ) );
  TEST_ASSERT( model->doesCellExist( 81 ) );
  TEST_ASSERT( model->doesCellExist( 82 ) );
  TEST_ASSERT( model->doesCellExist( 83 ) );
  TEST_ASSERT( model->doesCellExist( 88 ) );
  TEST_ASSERT( model->doesCellExist( 136 ) );
  TEST_ASSERT( model->doesCellExist( 152 ) );
  TEST_ASSERT( model->doesCellExist( 154 ) );
  TEST_ASSERT( model->doesCellExist( 166 ) );
  TEST_ASSERT( model->doesCellExist( 168 ) );
  TEST_ASSERT( model->doesCellExist( 184 ) );
  TEST_ASSERT( model->doesCellExist( 188 ) );

  // Implicit compliment cell
  TEST_ASSERT( model->doesCellExist( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if cells are termination cells
TEUCHOS_UNIT_TEST( DagMCModel, isTerminationCell )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  TEST_ASSERT( !model->isTerminationCell( 1 ) );
  TEST_ASSERT( !model->isTerminationCell( 3 ) );
  TEST_ASSERT( !model->isTerminationCell( 5 ) );
  TEST_ASSERT( !model->isTerminationCell( 7 ) );
  TEST_ASSERT( !model->isTerminationCell( 9 ) );
  TEST_ASSERT( !model->isTerminationCell( 13 ) );
  TEST_ASSERT( !model->isTerminationCell( 19 ) );
  TEST_ASSERT( !model->isTerminationCell( 26 ) );
  TEST_ASSERT( !model->isTerminationCell( 27 ) );
  TEST_ASSERT( !model->isTerminationCell( 28 ) );
  TEST_ASSERT( !model->isTerminationCell( 29 ) );
  TEST_ASSERT( !model->isTerminationCell( 30 ) );
  TEST_ASSERT( !model->isTerminationCell( 31 ) );
  TEST_ASSERT( !model->isTerminationCell( 32 ) );
  TEST_ASSERT( !model->isTerminationCell( 33 ) );
  TEST_ASSERT( !model->isTerminationCell( 34 ) );
  TEST_ASSERT( !model->isTerminationCell( 35 ) );
  TEST_ASSERT( !model->isTerminationCell( 36 ) );
  TEST_ASSERT( !model->isTerminationCell( 37 ) );
  TEST_ASSERT( !model->isTerminationCell( 41 ) );
  TEST_ASSERT( !model->isTerminationCell( 48 ) );
  TEST_ASSERT( !model->isTerminationCell( 49 ) );
  TEST_ASSERT( !model->isTerminationCell( 50 ) );
  TEST_ASSERT( !model->isTerminationCell( 51 ) );
  TEST_ASSERT( !model->isTerminationCell( 52 ) );
  TEST_ASSERT( !model->isTerminationCell( 53 ) );
  TEST_ASSERT( !model->isTerminationCell( 54 ) );
  TEST_ASSERT( !model->isTerminationCell( 55 ) );
  TEST_ASSERT( !model->isTerminationCell( 56 ) );
  TEST_ASSERT( !model->isTerminationCell( 57 ) );
  TEST_ASSERT( !model->isTerminationCell( 58 ) );
  TEST_ASSERT( !model->isTerminationCell( 59 ) );
  TEST_ASSERT( !model->isTerminationCell( 63 ) );
  TEST_ASSERT( !model->isTerminationCell( 70 ) );
  TEST_ASSERT( !model->isTerminationCell( 71 ) );
  TEST_ASSERT( !model->isTerminationCell( 72 ) );
  TEST_ASSERT( !model->isTerminationCell( 73 ) );
  TEST_ASSERT( !model->isTerminationCell( 74 ) );
  TEST_ASSERT( !model->isTerminationCell( 75 ) );
  TEST_ASSERT( !model->isTerminationCell( 76 ) );
  TEST_ASSERT( !model->isTerminationCell( 77 ) );
  TEST_ASSERT( !model->isTerminationCell( 78 ) );
  TEST_ASSERT( !model->isTerminationCell( 79 ) );
  TEST_ASSERT( !model->isTerminationCell( 80 ) );
  TEST_ASSERT( !model->isTerminationCell( 81 ) );
  TEST_ASSERT( !model->isTerminationCell( 82 ) );
  TEST_ASSERT( !model->isTerminationCell( 83 ) );
  TEST_ASSERT( !model->isTerminationCell( 88 ) );
  TEST_ASSERT( !model->isTerminationCell( 136 ) );
  TEST_ASSERT( !model->isTerminationCell( 152 ) );
  TEST_ASSERT( !model->isTerminationCell( 154 ) );
  TEST_ASSERT( !model->isTerminationCell( 166 ) );
  TEST_ASSERT( !model->isTerminationCell( 168 ) );
  TEST_ASSERT( !model->isTerminationCell( 184 ) );
  TEST_ASSERT( model->isTerminationCell( 188 ) );
  TEST_ASSERT( !model->isTerminationCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell is a void cell
TEUCHOS_UNIT_TEST( DagMCModel, isVoidCell )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  TEST_ASSERT( !model->isVoidCell( 1 ) );
  TEST_ASSERT( !model->isVoidCell( 3 ) );
  TEST_ASSERT( !model->isVoidCell( 5 ) );
  TEST_ASSERT( !model->isVoidCell( 7 ) );
  TEST_ASSERT( !model->isVoidCell( 9 ) );
  TEST_ASSERT( !model->isVoidCell( 13 ) );
  TEST_ASSERT( !model->isVoidCell( 19 ) );
  TEST_ASSERT( !model->isVoidCell( 26 ) );
  TEST_ASSERT( !model->isVoidCell( 27 ) );
  TEST_ASSERT( !model->isVoidCell( 28 ) );
  TEST_ASSERT( !model->isVoidCell( 29 ) );
  TEST_ASSERT( !model->isVoidCell( 30 ) );
  TEST_ASSERT( !model->isVoidCell( 31 ) );
  TEST_ASSERT( !model->isVoidCell( 32 ) );
  TEST_ASSERT( !model->isVoidCell( 33 ) );
  TEST_ASSERT( !model->isVoidCell( 34 ) );
  TEST_ASSERT( !model->isVoidCell( 35 ) );
  TEST_ASSERT( !model->isVoidCell( 36 ) );
  TEST_ASSERT( !model->isVoidCell( 37 ) );
  TEST_ASSERT( !model->isVoidCell( 41 ) );
  TEST_ASSERT( !model->isVoidCell( 48 ) );
  TEST_ASSERT( !model->isVoidCell( 49 ) );
  TEST_ASSERT( !model->isVoidCell( 50 ) );
  TEST_ASSERT( !model->isVoidCell( 51 ) );
  TEST_ASSERT( !model->isVoidCell( 52 ) );
  TEST_ASSERT( !model->isVoidCell( 53 ) );
  TEST_ASSERT( !model->isVoidCell( 54 ) );
  TEST_ASSERT( !model->isVoidCell( 55 ) );
  TEST_ASSERT( !model->isVoidCell( 56 ) );
  TEST_ASSERT( !model->isVoidCell( 57 ) );
  TEST_ASSERT( !model->isVoidCell( 58 ) );
  TEST_ASSERT( !model->isVoidCell( 59 ) );
  TEST_ASSERT( !model->isVoidCell( 63 ) );
  TEST_ASSERT( !model->isVoidCell( 70 ) );
  TEST_ASSERT( !model->isVoidCell( 71 ) );
  TEST_ASSERT( !model->isVoidCell( 72 ) );
  TEST_ASSERT( !model->isVoidCell( 73 ) );
  TEST_ASSERT( !model->isVoidCell( 74 ) );
  TEST_ASSERT( !model->isVoidCell( 75 ) );
  TEST_ASSERT( !model->isVoidCell( 76 ) );
  TEST_ASSERT( !model->isVoidCell( 77 ) );
  TEST_ASSERT( !model->isVoidCell( 78 ) );
  TEST_ASSERT( !model->isVoidCell( 79 ) );
  TEST_ASSERT( !model->isVoidCell( 80 ) );
  TEST_ASSERT( !model->isVoidCell( 81 ) );
  TEST_ASSERT( !model->isVoidCell( 82 ) );
  TEST_ASSERT( !model->isVoidCell( 83 ) );
  TEST_ASSERT( !model->isVoidCell( 88 ) );
  TEST_ASSERT( !model->isVoidCell( 136 ) );
  TEST_ASSERT( !model->isVoidCell( 152 ) );
  TEST_ASSERT( !model->isVoidCell( 154 ) );
  TEST_ASSERT( !model->isVoidCell( 166 ) );
  TEST_ASSERT( !model->isVoidCell( 168 ) );
  TEST_ASSERT( !model->isVoidCell( 184 ) );
  TEST_ASSERT( model->isVoidCell( 188 ) );
  TEST_ASSERT( model->isVoidCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell volume can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getCellVolume )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  // Get the volume of cell 53
  double cell_volume = model->getCellVolume( 53 );

  TEST_FLOATING_EQUALITY( cell_volume, 98.322384, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the problem surfaces can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getSurfaces )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  Geometry::AdvancedModel::SurfaceIdSet surfaces;

  model->getSurfaces( surfaces );

  TEST_EQUALITY_CONST( surfaces.size(), 293 );
}

//---------------------------------------------------------------------------//
// Check that the surface estimator data can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getSurfaceEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  Geometry::AdvancedModel::SurfaceEstimatorIdDataMap
    surface_estimator_id_data_map;

  TEST_NOTHROW( model->getSurfaceEstimatorData(
                                             surface_estimator_id_data_map ) );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.size(), 4 );
  TEST_ASSERT( surface_estimator_id_data_map.count( 5 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 6 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 7 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 8 ) );

  TEST_EQUALITY_CONST( Utility::get<0>(surface_estimator_id_data_map.find(5)->second),
                       Geometry::SURFACE_FLUX_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(surface_estimator_id_data_map.find(5)->second),
                       Geometry::NEUTRON );
  TEST_EQUALITY_CONST( Utility::get<2>(surface_estimator_id_data_map.find(5)->second).size(),
                       7 );

  TEST_EQUALITY_CONST( Utility::get<0>(surface_estimator_id_data_map.find(6)->second),
                       Geometry::SURFACE_FLUX_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(surface_estimator_id_data_map.find(6)->second),
                       Geometry::PHOTON );
  TEST_EQUALITY_CONST( Utility::get<2>(surface_estimator_id_data_map.find(6)->second).size(),
                       7 );

  TEST_EQUALITY_CONST( Utility::get<0>(surface_estimator_id_data_map.find(7)->second),
                       Geometry::SURFACE_CURRENT_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(surface_estimator_id_data_map.find(7)->second),
                       Geometry::NEUTRON );
  TEST_EQUALITY_CONST( Utility::get<2>(surface_estimator_id_data_map.find(7)->second).size(),
                       7 );

  TEST_EQUALITY_CONST( Utility::get<0>(surface_estimator_id_data_map.find(8)->second),
                       Geometry::SURFACE_CURRENT_ESTIMATOR );
  TEST_EQUALITY_CONST( Utility::get<1>(surface_estimator_id_data_map.find(8)->second),
                       Geometry::PHOTON );
  TEST_EQUALITY_CONST( Utility::get<2>(surface_estimator_id_data_map.find(8)->second).size(),
                       7 );
}

//---------------------------------------------------------------------------//
// Check if surfaces exist
TEUCHOS_UNIT_TEST( DagMCModel, doesSurfaceExist )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  TEST_ASSERT( !model->doesSurfaceExist( 0 ) );
  TEST_ASSERT( model->doesSurfaceExist( 1 ) );
  TEST_ASSERT( !model->doesSurfaceExist( 2 ) );
  TEST_ASSERT( !model->doesSurfaceExist( 3 ) );
  TEST_ASSERT( !model->doesSurfaceExist( 4 ) );
  TEST_ASSERT( !model->doesSurfaceExist( 5 ) );
  TEST_ASSERT( !model->doesSurfaceExist( 6 ) );
  TEST_ASSERT( model->doesSurfaceExist( 7 ) );
  TEST_ASSERT( model->doesSurfaceExist( 8 ) );
  TEST_ASSERT( model->doesSurfaceExist( 9 ) );

  // There are more surfaces than this but too many to feasibly check
}

//---------------------------------------------------------------------------//
// Check that the surface area can be returned
TEUCHOS_UNIT_TEST( DagMCModel, getSurfaceArea )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  // Get the surface area of surface 242
  double surface_area = model->getSurfaceArea( 242 );

  TEST_FLOATING_EQUALITY( surface_area, 38.7096, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check if a surface is a reflecting surface
TEUCHOS_UNIT_TEST( DagMCModel, isReflectingSurface )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();
  
  TEST_ASSERT( model->isReflectingSurface( 408 ) );
  TEST_ASSERT( !model->isReflectingSurface( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that a DagMC navigator can be created
TEUCHOS_UNIT_TEST( DagMCModel, createDagMCNavigator )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  std::shared_ptr<Geometry::DagMCNavigator> navigator =
    model->createDagMCNavigator();

  TEST_ASSERT( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be created
TEUCHOS_UNIT_TEST( DagMCModel, createNavigator )
{
  std::shared_ptr<Geometry::DagMCModel> model =
    Geometry::DagMCModel::getInstance();

  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

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

  model_properties = Geometry::DagMCModelPropertiesFactory::createProperties(
                                                       *raw_model_properties );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCModel.cpp
//---------------------------------------------------------------------------//
