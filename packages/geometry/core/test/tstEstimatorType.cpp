//---------------------------------------------------------------------------//
//!
//! \file   tstEstimatorType.cpp
//! \author Alex Robinson
//! \brief  Estimator type unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Geometry_EstimatorType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the  estimator type is a surface estimator
FRENSIE_UNIT_TEST( EstimatorType, isSurfaceEstimator )
{
  FRENSIE_CHECK( Geometry::isSurfaceEstimator(
                                       Geometry::SURFACE_CURRENT_ESTIMATOR ) );
  FRENSIE_CHECK( Geometry::isSurfaceEstimator(
                                          Geometry::SURFACE_FLUX_ESTIMATOR ) );
  FRENSIE_CHECK( !Geometry::isSurfaceEstimator(
                                     Geometry::CELL_PULSE_HEIGHT_ESTIMATOR ) );
  FRENSIE_CHECK( !Geometry::isSurfaceEstimator(
                                Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR ) );
  FRENSIE_CHECK( !Geometry::isSurfaceEstimator(
                                   Geometry::CELL_COLLISION_FLUX_ESTIMATOR ) );
}

//---------------------------------------------------------------------------//
// Check if the  estimator type is a cell estimator
FRENSIE_UNIT_TEST( EstimatorType, isCellEstimator )
{
  FRENSIE_CHECK( !Geometry::isCellEstimator(
                                       Geometry::SURFACE_CURRENT_ESTIMATOR ) );
  FRENSIE_CHECK( !Geometry::isCellEstimator(
                                          Geometry::SURFACE_FLUX_ESTIMATOR ) );
  FRENSIE_CHECK( Geometry::isCellEstimator(
                                     Geometry::CELL_PULSE_HEIGHT_ESTIMATOR ) );
  FRENSIE_CHECK( Geometry::isCellEstimator(
                                Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR ) );
  FRENSIE_CHECK( Geometry::isCellEstimator(
                                   Geometry::CELL_COLLISION_FLUX_ESTIMATOR ) );
}

//---------------------------------------------------------------------------//
// end tstEstimatorType.cpp
//---------------------------------------------------------------------------//
