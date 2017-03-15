//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCEstimatorType.cpp
//! \author Alex Robinson
//! \brief  DagMC estimator type unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_DagMCEstimatorType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the DagMC estimator type is a surface estimator
TEUCHOS_UNIT_TEST( DagMCEstimatorType, isDagMCSurfaceEstimator )
{
  TEST_ASSERT( Geometry::isDagMCSurfaceEstimator(
                                 Geometry::DAGMC_SURFACE_CURRENT_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isDagMCSurfaceEstimator(
                                    Geometry::DAGMC_SURFACE_FLUX_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isDagMCSurfaceEstimator(
                               Geometry::DAGMC_CELL_PULSE_HEIGHT_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isDagMCSurfaceEstimator(
                          Geometry::DAGMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isDagMCSurfaceEstimator(
                             Geometry::DAGMC_CELL_COLLISION_FLUX_ESTIMATOR ) );
}

//---------------------------------------------------------------------------//
// Check if the DagMC estimator type is a cell estimator
TEUCHOS_UNIT_TEST( DagMCEstimatorType, isDagMCCellEstimator )
{
  TEST_ASSERT( !Geometry::isDagMCCellEstimator(
                                 Geometry::DAGMC_SURFACE_CURRENT_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isDagMCCellEstimator(
                                    Geometry::DAGMC_SURFACE_FLUX_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isDagMCCellEstimator(
                               Geometry::DAGMC_CELL_PULSE_HEIGHT_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isDagMCCellEstimator(
                          Geometry::DAGMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isDagMCCellEstimator(
                             Geometry::DAGMC_CELL_COLLISION_FLUX_ESTIMATOR ) );
}

//---------------------------------------------------------------------------//
// end tstDagmCEstimatorType.cpp
//---------------------------------------------------------------------------//
