//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCModel.cpp
//! \author Alex Robinson
//! \brief  DagMC model class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// FRENSIE Includes
#include "Geometry_DagMCModel.hpp"
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
std::unique_ptr<const Geometry::DagMCModelProperties> model_properties;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a DagMC model can be constructed
FRENSIE_UNIT_TEST( DagMCModel, constructor )
{
  std::shared_ptr<Geometry::DagMCModel>
    model_a, model_b;

  FRENSIE_CHECK_NO_THROW( model_a.reset( new Geometry::DagMCModel( *model_properties ) ) );
  FRENSIE_CHECK_NO_THROW( model_b.reset( new Geometry::DagMCModel( *model_properties ) ) );
}

//---------------------------------------------------------------------------//
// Check that the model properties can be retrieved
FRENSIE_UNIT_TEST( DagMCModel, getModelProperties )
{
  std::shared_ptr<Geometry::DagMCModel>
    model( new Geometry::DagMCModel( *model_properties ) );

  const Geometry::DagMCModelProperties& cached_properties =
    model->getModelProperties();

  FRENSIE_CHECK( cached_properties.getModelFileName().find( "test_geom.h5m" ) <
                 cached_properties.getModelFileName().size() );
}

//---------------------------------------------------------------------------//
// Check if the model has cell estimator data
FRENSIE_UNIT_TEST( DagMCModel, hasCellEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( model->hasCellEstimatorData() );
}

//---------------------------------------------------------------------------//
// Check if the model has surface estimator data
FRENSIE_UNIT_TEST( DagMCModel, hasSurfaceEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( model->hasSurfaceEstimatorData() );
}

//---------------------------------------------------------------------------//
// Check that the material ids can be returned
FRENSIE_UNIT_TEST( DagMCModel, getMaterialIds )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::Model::MaterialIdSet material_ids;

  FRENSIE_CHECK_NO_THROW( model->getMaterialIds( material_ids ) );

  FRENSIE_CHECK_EQUAL( material_ids.size(), 8 );
  FRENSIE_CHECK( material_ids.count( 1 ) );
  FRENSIE_CHECK( material_ids.count( 2 ) );
  FRENSIE_CHECK( material_ids.count( 3 ) );
  FRENSIE_CHECK( material_ids.count( 4 ) );
  FRENSIE_CHECK( material_ids.count( 7 ) );
  FRENSIE_CHECK( material_ids.count( 8 ) );
  FRENSIE_CHECK( material_ids.count( 9 ) );
  FRENSIE_CHECK( material_ids.count( 10 ) );
}

//---------------------------------------------------------------------------//
// Check that the problem cells can be returned
FRENSIE_UNIT_TEST( DagMCModel, getCells )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::Model::CellIdSet cells;

  // Get all cells
  model->getCells( cells, true, true );

  // 55 + implicit compliment cell
  FRENSIE_CHECK_EQUAL( cells.size(), 56 );

  FRENSIE_CHECK( cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 3 ) );
  FRENSIE_CHECK( cells.count( 5 ) );
  FRENSIE_CHECK( cells.count( 7 ) );
  FRENSIE_CHECK( cells.count( 9 ) );
  FRENSIE_CHECK( cells.count( 13 ) );
  FRENSIE_CHECK( cells.count( 19 ) );
  FRENSIE_CHECK( cells.count( 26 ) );
  FRENSIE_CHECK( cells.count( 27 ) );
  FRENSIE_CHECK( cells.count( 28 ) );
  FRENSIE_CHECK( cells.count( 29 ) );
  FRENSIE_CHECK( cells.count( 30 ) );
  FRENSIE_CHECK( cells.count( 31 ) );
  FRENSIE_CHECK( cells.count( 32 ) );
  FRENSIE_CHECK( cells.count( 33 ) );
  FRENSIE_CHECK( cells.count( 34 ) );
  FRENSIE_CHECK( cells.count( 35 ) );
  FRENSIE_CHECK( cells.count( 36 ) );
  FRENSIE_CHECK( cells.count( 37 ) );
  FRENSIE_CHECK( cells.count( 41 ) );
  FRENSIE_CHECK( cells.count( 48 ) );
  FRENSIE_CHECK( cells.count( 49 ) );
  FRENSIE_CHECK( cells.count( 50 ) );
  FRENSIE_CHECK( cells.count( 51 ) );
  FRENSIE_CHECK( cells.count( 52 ) );
  FRENSIE_CHECK( cells.count( 53 ) );
  FRENSIE_CHECK( cells.count( 54 ) );
  FRENSIE_CHECK( cells.count( 55 ) );
  FRENSIE_CHECK( cells.count( 56 ) );
  FRENSIE_CHECK( cells.count( 57 ) );
  FRENSIE_CHECK( cells.count( 58 ) );
  FRENSIE_CHECK( cells.count( 59 ) );
  FRENSIE_CHECK( cells.count( 63 ) );
  FRENSIE_CHECK( cells.count( 70 ) );
  FRENSIE_CHECK( cells.count( 71 ) );
  FRENSIE_CHECK( cells.count( 72 ) );
  FRENSIE_CHECK( cells.count( 73 ) );
  FRENSIE_CHECK( cells.count( 74 ) );
  FRENSIE_CHECK( cells.count( 75 ) );
  FRENSIE_CHECK( cells.count( 76 ) );
  FRENSIE_CHECK( cells.count( 77 ) );
  FRENSIE_CHECK( cells.count( 78 ) );
  FRENSIE_CHECK( cells.count( 79 ) );
  FRENSIE_CHECK( cells.count( 80 ) );
  FRENSIE_CHECK( cells.count( 81 ) );
  FRENSIE_CHECK( cells.count( 82 ) );
  FRENSIE_CHECK( cells.count( 83 ) );
  FRENSIE_CHECK( cells.count( 88 ) );
  FRENSIE_CHECK( cells.count( 136 ) );
  FRENSIE_CHECK( cells.count( 152 ) );
  FRENSIE_CHECK( cells.count( 154 ) );
  FRENSIE_CHECK( cells.count( 166 ) );
  FRENSIE_CHECK( cells.count( 168 ) );
  FRENSIE_CHECK( cells.count( 184 ) );
  FRENSIE_CHECK( cells.count( 188 ) );
  FRENSIE_CHECK( cells.count( 189 ) );

  cells.clear();

  // Get all cells except the termination cell
  model->getCells( cells, true, false );

  FRENSIE_CHECK_EQUAL( cells.size(), 55 );
  FRENSIE_CHECK( !cells.count( 188 ) );

  cells.clear();

  // Get all cells except the void cells
  model->getCells( cells, false, true );

  FRENSIE_CHECK_EQUAL( cells.size(), 55 );
  FRENSIE_CHECK( !cells.count( 189 ) );

  cells.clear();

  // Get cells with a material only
  model->getCells( cells, false, false );

  FRENSIE_CHECK_EQUAL( cells.size(), 54 );
  FRENSIE_CHECK( !cells.count( 188 ) );
  FRENSIE_CHECK( !cells.count( 189 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell material ids can be returned
FRENSIE_UNIT_TEST( DagMCModel, getCellMaterialIds )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::Model::CellIdMatIdMap cell_id_mat_id_map;

  FRENSIE_CHECK_NO_THROW( model->getCellMaterialIds( cell_id_mat_id_map ) );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.size(), 54 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 9 )->second, 1 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 88 )->second, 1 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 136 )->second, 2 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 19 )->second, 3 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 41 )->second, 3 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 63 )->second, 3 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 82 )->second, 3 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 152 )->second, 3 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 166 )->second, 3 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 184 )->second, 3 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 3 )->second, 4 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 7 )->second, 4 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 13 )->second, 7 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 83 )->second, 7 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 154 )->second, 7 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 168 )->second, 7 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 1 )->second, 8 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 26 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 27 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 28 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 29 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 30 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 31 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 32 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 33 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 34 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 35 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 36 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 37 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 48 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 49 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 50 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 51 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 52 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 53 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 54 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 55 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 56 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 57 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 58 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 59 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 70 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 71 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 72 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 73 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 74 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 75 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 76 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 77 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 78 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 79 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 80 )->second, 9 );
  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 81 )->second, 9 );

  FRENSIE_CHECK_EQUAL( cell_id_mat_id_map.find( 5 )->second, 10 );
}

//---------------------------------------------------------------------------//
// Check that the cell densities can be returned
FRENSIE_UNIT_TEST( DagMCModel, getCellDensities )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::Model::CellIdDensityMap cell_id_density_map;

  FRENSIE_CHECK_NO_THROW( model->getCellDensities( cell_id_density_map ) );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.size(), 54 );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 9 )->second,
                       -8.027/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 88 )->second,
                       -8.027/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 136 )->second,
                       -7.75/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 19 )->second,
                       -0.001633/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 41 )->second,
                       -0.001633/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 63 )->second,
                       -0.001633/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 82 )->second,
                       -0.001633/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 152 )->second,
                       -0.001633/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 166 )->second,
                       -0.001633/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 184 )->second,
                       -0.001633/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 3 )->second,
                       -0.99823/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 7 )->second,
                       -0.99823/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 13 )->second,
                       -5.65/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 83 )->second,
                       -5.65/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 154 )->second,
                       -5.65/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 168 )->second,
                       -5.65/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 1 )->second,
                       -1.8583/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 26 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 27 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 28 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 29 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 30 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 31 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 32 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 33 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 34 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 35 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 36 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 37 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 48 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 49 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 50 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 51 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 52 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 53 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 54 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 55 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 56 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 57 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 58 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 59 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 70 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 71 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 72 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 73 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 74 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 75 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 76 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 77 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 78 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 79 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 80 )->second,
                       -7.83/cgs::cubic_centimeter );
  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 81 )->second,
                       -7.83/cgs::cubic_centimeter );

  FRENSIE_CHECK_EQUAL( cell_id_density_map.find( 5 )->second,
                       -13.31/cgs::cubic_centimeter );
}

//---------------------------------------------------------------------------//
// Check that the cell estimator data can be returned
FRENSIE_UNIT_TEST( DagMCModel, getCellEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::Model::CellEstimatorIdDataMap cell_estimator_id_data_map;

  FRENSIE_CHECK_NO_THROW( model->getCellEstimatorData( cell_estimator_id_data_map ) );

  FRENSIE_CHECK_EQUAL( cell_estimator_id_data_map.size(), 5 );
  FRENSIE_CHECK( cell_estimator_id_data_map.count( 0 ) );
  FRENSIE_CHECK( cell_estimator_id_data_map.count( 1 ) );
  FRENSIE_CHECK( cell_estimator_id_data_map.count( 2 ) );
  FRENSIE_CHECK( cell_estimator_id_data_map.count( 3 ) );
  FRENSIE_CHECK( cell_estimator_id_data_map.count( 4 ) );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(cell_estimator_id_data_map.find(0)->second ),
                       Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(cell_estimator_id_data_map.find(0)->second),
                       Geometry::NEUTRON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(cell_estimator_id_data_map.find(0)->second).size(),
                       55 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(cell_estimator_id_data_map.find(1)->second),
                       Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(cell_estimator_id_data_map.find(1)->second),
                       Geometry::PHOTON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(cell_estimator_id_data_map.find(1)->second).size(),
                       55 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(cell_estimator_id_data_map.find(2)->second),
                       Geometry::CELL_COLLISION_FLUX_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(cell_estimator_id_data_map.find(2)->second),
                       Geometry::NEUTRON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(cell_estimator_id_data_map.find(2)->second).size(),
                       36 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(cell_estimator_id_data_map.find(3)->second),
                       Geometry::CELL_COLLISION_FLUX_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(cell_estimator_id_data_map.find(3)->second),
                       Geometry::PHOTON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(cell_estimator_id_data_map.find(3)->second).size(),
                       36 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(cell_estimator_id_data_map.find(4)->second),
                       Geometry::CELL_PULSE_HEIGHT_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(cell_estimator_id_data_map.find(4)->second),
                       Geometry::PHOTON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(cell_estimator_id_data_map.find(4)->second).size(),
                       2 );
}

//---------------------------------------------------------------------------//
// Check if cells exist
FRENSIE_UNIT_TEST( DagMCModel, doesCellExist )
{
  std::shared_ptr<Geometry::DagMCModel>
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( !model->doesCellExist( 0 ) );
  FRENSIE_CHECK( model->doesCellExist( 1 ) );
  FRENSIE_CHECK( !model->doesCellExist( 2 ) );
  FRENSIE_CHECK( model->doesCellExist( 3 ) );
  FRENSIE_CHECK( !model->doesCellExist( 4 ) );
  FRENSIE_CHECK( model->doesCellExist( 5 ) );
  FRENSIE_CHECK( !model->doesCellExist( 6 ) );
  FRENSIE_CHECK( model->doesCellExist( 7 ) );
  FRENSIE_CHECK( !model->doesCellExist( 8 ) );
  FRENSIE_CHECK( model->doesCellExist( 9 ) );
  FRENSIE_CHECK( model->doesCellExist( 13 ) );
  FRENSIE_CHECK( model->doesCellExist( 19 ) );
  FRENSIE_CHECK( model->doesCellExist( 26 ) );
  FRENSIE_CHECK( model->doesCellExist( 27 ) );
  FRENSIE_CHECK( model->doesCellExist( 28 ) );
  FRENSIE_CHECK( model->doesCellExist( 29 ) );
  FRENSIE_CHECK( model->doesCellExist( 30 ) );
  FRENSIE_CHECK( model->doesCellExist( 31 ) );
  FRENSIE_CHECK( model->doesCellExist( 32 ) );
  FRENSIE_CHECK( model->doesCellExist( 33 ) );
  FRENSIE_CHECK( model->doesCellExist( 34 ) );
  FRENSIE_CHECK( model->doesCellExist( 35 ) );
  FRENSIE_CHECK( model->doesCellExist( 36 ) );
  FRENSIE_CHECK( model->doesCellExist( 37 ) );
  FRENSIE_CHECK( model->doesCellExist( 41 ) );
  FRENSIE_CHECK( model->doesCellExist( 48 ) );
  FRENSIE_CHECK( model->doesCellExist( 49 ) );
  FRENSIE_CHECK( model->doesCellExist( 50 ) );
  FRENSIE_CHECK( model->doesCellExist( 51 ) );
  FRENSIE_CHECK( model->doesCellExist( 52 ) );
  FRENSIE_CHECK( model->doesCellExist( 53 ) );
  FRENSIE_CHECK( model->doesCellExist( 54 ) );
  FRENSIE_CHECK( model->doesCellExist( 55 ) );
  FRENSIE_CHECK( model->doesCellExist( 56 ) );
  FRENSIE_CHECK( model->doesCellExist( 57 ) );
  FRENSIE_CHECK( model->doesCellExist( 58 ) );
  FRENSIE_CHECK( model->doesCellExist( 59 ) );
  FRENSIE_CHECK( model->doesCellExist( 63 ) );
  FRENSIE_CHECK( model->doesCellExist( 70 ) );
  FRENSIE_CHECK( model->doesCellExist( 71 ) );
  FRENSIE_CHECK( model->doesCellExist( 72 ) );
  FRENSIE_CHECK( model->doesCellExist( 73 ) );
  FRENSIE_CHECK( model->doesCellExist( 74 ) );
  FRENSIE_CHECK( model->doesCellExist( 75 ) );
  FRENSIE_CHECK( model->doesCellExist( 76 ) );
  FRENSIE_CHECK( model->doesCellExist( 77 ) );
  FRENSIE_CHECK( model->doesCellExist( 78 ) );
  FRENSIE_CHECK( model->doesCellExist( 79 ) );
  FRENSIE_CHECK( model->doesCellExist( 80 ) );
  FRENSIE_CHECK( model->doesCellExist( 81 ) );
  FRENSIE_CHECK( model->doesCellExist( 82 ) );
  FRENSIE_CHECK( model->doesCellExist( 83 ) );
  FRENSIE_CHECK( model->doesCellExist( 88 ) );
  FRENSIE_CHECK( model->doesCellExist( 136 ) );
  FRENSIE_CHECK( model->doesCellExist( 152 ) );
  FRENSIE_CHECK( model->doesCellExist( 154 ) );
  FRENSIE_CHECK( model->doesCellExist( 166 ) );
  FRENSIE_CHECK( model->doesCellExist( 168 ) );
  FRENSIE_CHECK( model->doesCellExist( 184 ) );
  FRENSIE_CHECK( model->doesCellExist( 188 ) );

  // Implicit compliment cell
  FRENSIE_CHECK( model->doesCellExist( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if cells are termination cells
FRENSIE_UNIT_TEST( DagMCModel, isTerminationCell )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( !model->isTerminationCell( 1 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 3 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 5 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 7 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 9 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 13 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 19 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 26 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 27 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 28 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 29 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 30 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 31 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 32 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 33 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 34 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 35 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 36 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 37 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 41 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 48 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 49 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 50 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 51 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 52 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 53 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 54 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 55 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 56 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 57 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 58 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 59 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 63 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 70 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 71 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 72 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 73 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 74 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 75 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 76 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 77 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 78 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 79 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 80 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 81 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 82 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 83 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 88 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 136 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 152 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 154 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 166 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 168 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 184 ) );
  FRENSIE_CHECK( model->isTerminationCell( 188 ) );
  FRENSIE_CHECK( !model->isTerminationCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell is a void cell
FRENSIE_UNIT_TEST( DagMCModel, isVoidCell )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( !model->isVoidCell( 1 ) );
  FRENSIE_CHECK( !model->isVoidCell( 3 ) );
  FRENSIE_CHECK( !model->isVoidCell( 5 ) );
  FRENSIE_CHECK( !model->isVoidCell( 7 ) );
  FRENSIE_CHECK( !model->isVoidCell( 9 ) );
  FRENSIE_CHECK( !model->isVoidCell( 13 ) );
  FRENSIE_CHECK( !model->isVoidCell( 19 ) );
  FRENSIE_CHECK( !model->isVoidCell( 26 ) );
  FRENSIE_CHECK( !model->isVoidCell( 27 ) );
  FRENSIE_CHECK( !model->isVoidCell( 28 ) );
  FRENSIE_CHECK( !model->isVoidCell( 29 ) );
  FRENSIE_CHECK( !model->isVoidCell( 30 ) );
  FRENSIE_CHECK( !model->isVoidCell( 31 ) );
  FRENSIE_CHECK( !model->isVoidCell( 32 ) );
  FRENSIE_CHECK( !model->isVoidCell( 33 ) );
  FRENSIE_CHECK( !model->isVoidCell( 34 ) );
  FRENSIE_CHECK( !model->isVoidCell( 35 ) );
  FRENSIE_CHECK( !model->isVoidCell( 36 ) );
  FRENSIE_CHECK( !model->isVoidCell( 37 ) );
  FRENSIE_CHECK( !model->isVoidCell( 41 ) );
  FRENSIE_CHECK( !model->isVoidCell( 48 ) );
  FRENSIE_CHECK( !model->isVoidCell( 49 ) );
  FRENSIE_CHECK( !model->isVoidCell( 50 ) );
  FRENSIE_CHECK( !model->isVoidCell( 51 ) );
  FRENSIE_CHECK( !model->isVoidCell( 52 ) );
  FRENSIE_CHECK( !model->isVoidCell( 53 ) );
  FRENSIE_CHECK( !model->isVoidCell( 54 ) );
  FRENSIE_CHECK( !model->isVoidCell( 55 ) );
  FRENSIE_CHECK( !model->isVoidCell( 56 ) );
  FRENSIE_CHECK( !model->isVoidCell( 57 ) );
  FRENSIE_CHECK( !model->isVoidCell( 58 ) );
  FRENSIE_CHECK( !model->isVoidCell( 59 ) );
  FRENSIE_CHECK( !model->isVoidCell( 63 ) );
  FRENSIE_CHECK( !model->isVoidCell( 70 ) );
  FRENSIE_CHECK( !model->isVoidCell( 71 ) );
  FRENSIE_CHECK( !model->isVoidCell( 72 ) );
  FRENSIE_CHECK( !model->isVoidCell( 73 ) );
  FRENSIE_CHECK( !model->isVoidCell( 74 ) );
  FRENSIE_CHECK( !model->isVoidCell( 75 ) );
  FRENSIE_CHECK( !model->isVoidCell( 76 ) );
  FRENSIE_CHECK( !model->isVoidCell( 77 ) );
  FRENSIE_CHECK( !model->isVoidCell( 78 ) );
  FRENSIE_CHECK( !model->isVoidCell( 79 ) );
  FRENSIE_CHECK( !model->isVoidCell( 80 ) );
  FRENSIE_CHECK( !model->isVoidCell( 81 ) );
  FRENSIE_CHECK( !model->isVoidCell( 82 ) );
  FRENSIE_CHECK( !model->isVoidCell( 83 ) );
  FRENSIE_CHECK( !model->isVoidCell( 88 ) );
  FRENSIE_CHECK( !model->isVoidCell( 136 ) );
  FRENSIE_CHECK( !model->isVoidCell( 152 ) );
  FRENSIE_CHECK( !model->isVoidCell( 154 ) );
  FRENSIE_CHECK( !model->isVoidCell( 166 ) );
  FRENSIE_CHECK( !model->isVoidCell( 168 ) );
  FRENSIE_CHECK( !model->isVoidCell( 184 ) );
  FRENSIE_CHECK( model->isVoidCell( 188 ) );
  FRENSIE_CHECK( model->isVoidCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell volume can be returned
FRENSIE_UNIT_TEST( DagMCModel, getCellVolume )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  // Get the volume of cell 53
  Geometry::Model::Volume cell_volume = model->getCellVolume( 53 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cell_volume,
                                   98.322384*cgs::cubic_centimeter,
                                   1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the problem surfaces can be returned
FRENSIE_UNIT_TEST( DagMCModel, getSurfaces )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::AdvancedModel::SurfaceIdSet surfaces;

  model->getSurfaces( surfaces );

  FRENSIE_CHECK_EQUAL( surfaces.size(), 293 );
}

//---------------------------------------------------------------------------//
// Check that the surface estimator data can be returned
FRENSIE_UNIT_TEST( DagMCModel, getSurfaceEstimatorData )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  Geometry::AdvancedModel::SurfaceEstimatorIdDataMap
    surface_estimator_id_data_map;

  FRENSIE_CHECK_NO_THROW( model->getSurfaceEstimatorData(
                                             surface_estimator_id_data_map ) );

  FRENSIE_CHECK_EQUAL( surface_estimator_id_data_map.size(), 4 );
  FRENSIE_CHECK( surface_estimator_id_data_map.count( 5 ) );
  FRENSIE_CHECK( surface_estimator_id_data_map.count( 6 ) );
  FRENSIE_CHECK( surface_estimator_id_data_map.count( 7 ) );
  FRENSIE_CHECK( surface_estimator_id_data_map.count( 8 ) );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(surface_estimator_id_data_map.find(5)->second),
                       Geometry::SURFACE_FLUX_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(surface_estimator_id_data_map.find(5)->second),
                       Geometry::NEUTRON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(surface_estimator_id_data_map.find(5)->second).size(),
                       7 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(surface_estimator_id_data_map.find(6)->second),
                       Geometry::SURFACE_FLUX_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(surface_estimator_id_data_map.find(6)->second),
                       Geometry::PHOTON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(surface_estimator_id_data_map.find(6)->second).size(),
                       7 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(surface_estimator_id_data_map.find(7)->second),
                       Geometry::SURFACE_CURRENT_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(surface_estimator_id_data_map.find(7)->second),
                       Geometry::NEUTRON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(surface_estimator_id_data_map.find(7)->second).size(),
                       7 );

  FRENSIE_CHECK_EQUAL( Utility::get<0>(surface_estimator_id_data_map.find(8)->second),
                       Geometry::SURFACE_CURRENT_ESTIMATOR );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(surface_estimator_id_data_map.find(8)->second),
                       Geometry::PHOTON );
  FRENSIE_CHECK_EQUAL( Utility::get<2>(surface_estimator_id_data_map.find(8)->second).size(),
                       7 );
}

//---------------------------------------------------------------------------//
// Check if surfaces exist
FRENSIE_UNIT_TEST( DagMCModel, doesSurfaceExist )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( !model->doesSurfaceExist( 0 ) );
  FRENSIE_CHECK( model->doesSurfaceExist( 1 ) );
  FRENSIE_CHECK( !model->doesSurfaceExist( 2 ) );
  FRENSIE_CHECK( !model->doesSurfaceExist( 3 ) );
  FRENSIE_CHECK( !model->doesSurfaceExist( 4 ) );
  FRENSIE_CHECK( !model->doesSurfaceExist( 5 ) );
  FRENSIE_CHECK( !model->doesSurfaceExist( 6 ) );
  FRENSIE_CHECK( model->doesSurfaceExist( 7 ) );
  FRENSIE_CHECK( model->doesSurfaceExist( 8 ) );
  FRENSIE_CHECK( model->doesSurfaceExist( 9 ) );

  // There are more surfaces than this but too many to feasibly check
}

//---------------------------------------------------------------------------//
// Check that the surface area can be returned
FRENSIE_UNIT_TEST( DagMCModel, getSurfaceArea )
{
  std::shared_ptr<Geometry::DagMCModel>
    model( new Geometry::DagMCModel( *model_properties ) );

  // Get the surface area of surface 242
  Geometry::AdvancedModel::Area surface_area = model->getSurfaceArea( 242 );

  FRENSIE_CHECK_FLOATING_EQUALITY( surface_area,
                                   38.7096*cgs::square_centimeter,
                                   1e-6 );
}

//---------------------------------------------------------------------------//
// Check if a surface is a reflecting surface
FRENSIE_UNIT_TEST( DagMCModel, isReflectingSurface )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  FRENSIE_CHECK( model->isReflectingSurface( 408 ) );
  FRENSIE_CHECK( !model->isReflectingSurface( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that a DagMC navigator can be created
FRENSIE_UNIT_TEST( DagMCModel, createNavigatorAdvanced )
{
  std::shared_ptr<Geometry::DagMCModel> 
    model( new Geometry::DagMCModel( *model_properties ) );

  std::shared_ptr<Geometry::DagMCNavigator> navigator(
                                            model->createNavigatorAdvanced() );

  FRENSIE_CHECK( navigator.get() != NULL );

  navigator.reset( model->createNavigatorAdvanced( [](const Geometry::Navigator::Length distance){ std::cout << "advanced " << distance << std::endl; } ) );

  FRENSIE_CHECK( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be created
FRENSIE_UNIT_TEST( DagMCModel, createNavigator )
{
  std::shared_ptr<Geometry::DagMCModel>
    model( new Geometry::DagMCModel( *model_properties ) );

  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  FRENSIE_CHECK( navigator.get() != NULL );

  navigator = model->createNavigator( [](const Geometry::Navigator::Length distance){ std::cout << "advanced " << distance << std::endl; } );
}

//---------------------------------------------------------------------------//
// Check that a model can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DagMCModel, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_name( "test_dagmc_model" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_name, archive_ostream, oarchive );
    
    std::shared_ptr<Geometry::DagMCModel>
      model( new Geometry::DagMCModel( *model_properties ) );

    std::shared_ptr<const Geometry::AdvancedModel>
      advanced_base_model = model;

    std::shared_ptr<const Geometry::Model>
      base_model = model;
    
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( model ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( advanced_base_model ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( base_model ) );
  }

  Utility::JustInTimeInitializer::getInstance().activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<Geometry::DagMCModel> model;
  std::shared_ptr<const Geometry::AdvancedModel> advanced_base_model;
  std::shared_ptr<const Geometry::Model> base_model;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( model ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( advanced_base_model ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( base_model ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !model->isInitialized() );

  const Geometry::DagMCModelProperties& cached_properties =
    model->getModelProperties();

  FRENSIE_CHECK( cached_properties.getModelFileName().find( "test_geom.h5m" ) <
                 cached_properties.getModelFileName().size() );

  // Initialize the model
  FRENSIE_CHECK_EQUAL( Utility::JustInTimeInitializer::getInstance().getNumberOfObjects(), 1 );

  FRENSIE_REQUIRE_NO_THROW( Utility::JustInTimeInitializer::getInstance().initializeObjectsAndClear() );

  Geometry::Model::CellIdSet cells;
  base_model->getCells( cells, true, true );
  
  FRENSIE_CHECK_EQUAL( cells.size(), 56 );
  FRENSIE_CHECK( cells.count( 1 ) );
  FRENSIE_CHECK( cells.count( 3 ) );
  FRENSIE_CHECK( cells.count( 5 ) );
  FRENSIE_CHECK( cells.count( 7 ) );
  FRENSIE_CHECK( cells.count( 9 ) );
  FRENSIE_CHECK( cells.count( 13 ) );
  FRENSIE_CHECK( cells.count( 19 ) );
  FRENSIE_CHECK( cells.count( 26 ) );
  FRENSIE_CHECK( cells.count( 27 ) );
  FRENSIE_CHECK( cells.count( 28 ) );
  FRENSIE_CHECK( cells.count( 29 ) );
  FRENSIE_CHECK( cells.count( 30 ) );
  FRENSIE_CHECK( cells.count( 31 ) );
  FRENSIE_CHECK( cells.count( 32 ) );
  FRENSIE_CHECK( cells.count( 33 ) );
  FRENSIE_CHECK( cells.count( 34 ) );
  FRENSIE_CHECK( cells.count( 35 ) );
  FRENSIE_CHECK( cells.count( 36 ) );
  FRENSIE_CHECK( cells.count( 37 ) );
  FRENSIE_CHECK( cells.count( 41 ) );
  FRENSIE_CHECK( cells.count( 48 ) );
  FRENSIE_CHECK( cells.count( 49 ) );
  FRENSIE_CHECK( cells.count( 50 ) );
  FRENSIE_CHECK( cells.count( 51 ) );
  FRENSIE_CHECK( cells.count( 52 ) );
  FRENSIE_CHECK( cells.count( 53 ) );
  FRENSIE_CHECK( cells.count( 54 ) );
  FRENSIE_CHECK( cells.count( 55 ) );
  FRENSIE_CHECK( cells.count( 56 ) );
  FRENSIE_CHECK( cells.count( 57 ) );
  FRENSIE_CHECK( cells.count( 58 ) );
  FRENSIE_CHECK( cells.count( 59 ) );
  FRENSIE_CHECK( cells.count( 63 ) );
  FRENSIE_CHECK( cells.count( 70 ) );
  FRENSIE_CHECK( cells.count( 71 ) );
  FRENSIE_CHECK( cells.count( 72 ) );
  FRENSIE_CHECK( cells.count( 73 ) );
  FRENSIE_CHECK( cells.count( 74 ) );
  FRENSIE_CHECK( cells.count( 75 ) );
  FRENSIE_CHECK( cells.count( 76 ) );
  FRENSIE_CHECK( cells.count( 77 ) );
  FRENSIE_CHECK( cells.count( 78 ) );
  FRENSIE_CHECK( cells.count( 79 ) );
  FRENSIE_CHECK( cells.count( 80 ) );
  FRENSIE_CHECK( cells.count( 81 ) );
  FRENSIE_CHECK( cells.count( 82 ) );
  FRENSIE_CHECK( cells.count( 83 ) );
  FRENSIE_CHECK( cells.count( 88 ) );
  FRENSIE_CHECK( cells.count( 136 ) );
  FRENSIE_CHECK( cells.count( 152 ) );
  FRENSIE_CHECK( cells.count( 154 ) );
  FRENSIE_CHECK( cells.count( 166 ) );
  FRENSIE_CHECK( cells.count( 168 ) );
  FRENSIE_CHECK( cells.count( 184 ) );
  FRENSIE_CHECK( cells.count( 188 ) );
  FRENSIE_CHECK( cells.count( 189 ) );

  Geometry::AdvancedModel::SurfaceIdSet surfaces;

  advanced_base_model->getSurfaces( surfaces );

  FRENSIE_CHECK_EQUAL( surfaces.size(), 293 );

  FRENSIE_CHECK_EQUAL( model->getModelProperties().getTerminationCellPropertyName(), "graveyard" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getMaterialPropertyName(), "mat" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getDensityPropertyName(), "rho" );
  FRENSIE_CHECK_EQUAL( model->getModelProperties().getEstimatorPropertyName(), "tally" );

  // Check that a navigator can be created
  std::shared_ptr<Geometry::Navigator> navigator;

  FRENSIE_CHECK_NO_THROW( navigator = base_model->createNavigator() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );

  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );

  model_properties.reset( new Geometry::DagMCModelProperties( local_properties ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCModel.cpp
//---------------------------------------------------------------------------//
