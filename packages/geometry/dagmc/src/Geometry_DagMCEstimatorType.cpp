//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCEstimatorType.cpp
//! \author Alex Robinson
//! \brief  DagMC estimator type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_DagMCEstimatorType.hpp"

namespace Geometry{

// Check if the estimator type is a surface estimator
bool isDagMCSurfaceEstimator( const DagMCEstimatorType type )
{
  return type == DAGMC_SURFACE_CURRENT_ESTIMATOR ||
    type == DAGMC_SURFACE_FLUX_ESTIMATOR;
}

// Check if the estimator type is a cell estimator
bool isDagMCCellEstimator( const DagMCEstimatorType type )
{
  return type == DAGMC_CELL_PULSE_HEIGHT_ESTIMATOR ||
    type == DAGMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR ||
    type == DAGMC_CELL_COLLISION_FLUX_ESTIMATOR;
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCEstimatorType.cpp
//---------------------------------------------------------------------------//
