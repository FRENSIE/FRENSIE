//---------------------------------------------------------------------------//
//!
//! \file   Geometry_EstimatorType.cpp
//! \author Alex Robinson
//! \brief  Estimator type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_EstimatorType.hpp"

namespace Geometry{

// Check if the estimator type is a surface estimator
bool isSurfaceEstimator( const EstimatorType type )
{
  return type == SURFACE_CURRENT_ESTIMATOR ||
    type == SURFACE_FLUX_ESTIMATOR;
}

// Check if the estimator type is a cell estimator
bool isCellEstimator( const EstimatorType type )
{
  return type == CELL_PULSE_HEIGHT_ESTIMATOR ||
    type == CELL_TRACK_LENGTH_FLUX_ESTIMATOR ||
    type == CELL_COLLISION_FLUX_ESTIMATOR;
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_EstimatorType.cpp
//---------------------------------------------------------------------------//
