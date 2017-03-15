//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCEstimatorType.hpp
//! \author Alex Robinson
//! \brief  DagMC estimator type enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_ESTIMATOR_TYPE_HPP
#define GEOMETRY_DAGMC_ESTIMATOR_TYPE_HPP

namespace Geometry{

//! The DagMC estimator type enum
enum DagMCEstimatorType{
  DAGMC_SURFACE_CURRENT_ESTIMATOR = 0,
  DAGMC_SURFACE_FLUX_ESTIMATOR,
  DAGMC_CELL_PULSE_HEIGHT_ESTIMATOR,
  DAGMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR,
  DAGMC_CELL_COLLISION_FLUX_ESTIMATOR
};

//! Check if the estimator type is a surface estimator
bool isDagMCSurfaceEstimator( const DagMCEstimatorType type );

//! Check if the estimator type is a cell estimator
bool isDagMCCellEstimator( const DagMCEstimatorType type );
  
} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_ESTIMATOR_TYPE_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCEstimatorType.hpp
//---------------------------------------------------------------------------//
