//---------------------------------------------------------------------------//
//!
//! \file   tstEstimatorType.cpp
//! \author Alex Robinson
//! \brief  Estimator type unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_EstimatorType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the  estimator type is a surface estimator
TEUCHOS_UNIT_TEST( EstimatorType, isSurfaceEstimator )
{
  TEST_ASSERT( Geometry::isSurfaceEstimator(
                                       Geometry::SURFACE_CURRENT_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isSurfaceEstimator(
                                          Geometry::SURFACE_FLUX_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isSurfaceEstimator(
                                     Geometry::CELL_PULSE_HEIGHT_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isSurfaceEstimator(
                                Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isSurfaceEstimator(
                                   Geometry::CELL_COLLISION_FLUX_ESTIMATOR ) );
}

//---------------------------------------------------------------------------//
// Check if the  estimator type is a cell estimator
TEUCHOS_UNIT_TEST( EstimatorType, isCellEstimator )
{
  TEST_ASSERT( !Geometry::isCellEstimator(
                                       Geometry::SURFACE_CURRENT_ESTIMATOR ) );
  TEST_ASSERT( !Geometry::isCellEstimator(
                                          Geometry::SURFACE_FLUX_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isCellEstimator(
                                     Geometry::CELL_PULSE_HEIGHT_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isCellEstimator(
                                Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR ) );
  TEST_ASSERT( Geometry::isCellEstimator(
                                   Geometry::CELL_COLLISION_FLUX_ESTIMATOR ) );
}

//---------------------------------------------------------------------------//
// end tstEstimatorType.cpp
//---------------------------------------------------------------------------//
