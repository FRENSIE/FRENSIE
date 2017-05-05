//---------------------------------------------------------------------------//
//!
//! \file   tstInfiniteMediumModel.cpp
//! \author Alex Robinson
//! \brief  Infinite medium model class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check if the model name can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getName )
{
  Geometry::InfiniteMediumModel model;

  TEST_EQUALITY_CONST( model.getName(), "Infinite Medium" );
}

//---------------------------------------------------------------------------//
// Check if the model has cell estimator data
TEUCHOS_UNIT_TEST( InfiniteMediumModel, hasCellEstimatorData )
{
  Geometry::InfiniteMediumModel model;

  TEST_ASSERT( !model.hasCellEstimatorData() );
}

//---------------------------------------------------------------------------//
// Check that the model material ids can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getMaterialIds )
{
  Geometry::InfiniteMediumModel model;

  Geometry::Model::MaterialIdSet material_ids;

  model.getMaterialIds( material_ids );

  TEST_ASSERT( material_ids.empty() );
}

//---------------------------------------------------------------------------//
// Check that the model cells can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getCells )
{
  Geometry::InfiniteMediumModel model( 1 );

  Geometry::Model::CellIdSet cells;

  // Get all cells except for the termination cells
  model.getCells( cells, true, false );

  TEST_EQUALITY_CONST( cells.size(), 1 );
  TEST_ASSERT( cells.count( 1 ) );

  cells.clear();

  // Get all cells except the void cells
  model.getCells( cells, false, true );

  TEST_ASSERT( cells.empty() );

  cells.clear();
  
  // Get all cells except the void and termination cells
  model.getCells( cells, false, false );

  TEST_ASSERT( cells.empty() );

  cells.clear();

  // Get all cells
  model.getCells( cells, true, true );

  TEST_EQUALITY_CONST( cells.size(), 1 );
  TEST_ASSERT( cells.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell material ids can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getCellMaterialIds )
{
  Geometry::InfiniteMediumModel model( 1 );

  Geometry::Model::CellIdMatIdMap cell_id_mat_id_map;

  model.getCellMaterialIds( cell_id_mat_id_map );

  TEST_ASSERT( cell_id_mat_id_map.empty() );
}

//---------------------------------------------------------------------------//
// Check that the cell densities can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getCellDensities )
{
  Geometry::InfiniteMediumModel model( 1 );

  Geometry::Model::CellIdDensityMap cell_id_density_map;

  model.getCellDensities( cell_id_density_map );

  TEST_ASSERT( cell_id_density_map.empty() );
}

//---------------------------------------------------------------------------//
// Check that the cell estimator data can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getCellEstimatorData )
{
  Geometry::InfiniteMediumModel model( 1 );

  Geometry::Model::CellEstimatorIdDataMap cell_estimator_id_data_map;

  model.getCellEstimatorData( cell_estimator_id_data_map );

  TEST_ASSERT( cell_estimator_id_data_map.empty() );
}

//---------------------------------------------------------------------------//
// Check if a cell exists
TEUCHOS_UNIT_TEST( InfiniteMediumModel, doesCellExist )
{
  Geometry::InfiniteMediumModel model( 2 );

  TEST_ASSERT( !model.doesCellExist( 1 ) );
  TEST_ASSERT( model.doesCellExist( 2 ) );
  TEST_ASSERT( !model.doesCellExist( 3 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell is a termination cell
TEUCHOS_UNIT_TEST( InfiniteMediumModel, isTerminationCell )
{
  Geometry::InfiniteMediumModel model( 2 );

  TEST_ASSERT( !model.isTerminationCell( 2 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell is a void cell
TEUCHOS_UNIT_TEST( InfiniteMediumModel, isVoidCell )
{
  Geometry::InfiniteMediumModel model( 3 );
  
  TEST_ASSERT( model.isVoidCell( 3 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell volume can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumModel, getCellVolume )
{
  Geometry::InfiniteMediumModel model( 1 );

  TEST_EQUALITY_CONST( model.getCellVolume( 1 ),
                       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be created
TEUCHOS_UNIT_TEST( InfiniteMediumModel, createNavigatorAdvanced )
{
  Geometry::InfiniteMediumModel model;
  
  std::shared_ptr<Geometry::InfiniteMediumNavigator> navigator(
                                             model.createNavigatorAdvanced() );

  TEST_ASSERT( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a navigator can be created
TEUCHOS_UNIT_TEST( InfiniteMediumModel, createNavigator )
{
  Geometry::InfiniteMediumModel model;
  
  std::shared_ptr<Geometry::Navigator> navigator = model.createNavigator();

  TEST_ASSERT( navigator.get() != NULL );
}

//---------------------------------------------------------------------------//
// end tstInfiniteMediumModel.cpp
//---------------------------------------------------------------------------//
