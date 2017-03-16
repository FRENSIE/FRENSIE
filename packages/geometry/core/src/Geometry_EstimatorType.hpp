//---------------------------------------------------------------------------//
//!
//! \file   Geometry_EstimatorType.hpp
//! \author Alex Robinson
//! \brief  Estimator type enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ESTIMATOR_TYPE_HPP
#define GEOMETRY_ESTIMATOR_TYPE_HPP

namespace Geometry{

//! The  estimator type enum
enum EstimatorType{
  SURFACE_CURRENT_ESTIMATOR = 0,
  SURFACE_FLUX_ESTIMATOR,
  CELL_PULSE_HEIGHT_ESTIMATOR,
  CELL_TRACK_LENGTH_FLUX_ESTIMATOR,
  CELL_COLLISION_FLUX_ESTIMATOR
};

//! Check if the estimator type is a surface estimator
bool isSurfaceEstimator( const EstimatorType type );

//! Check if the estimator type is a cell estimator
bool isCellEstimator( const EstimatorType type );
  
} // end Geometry namespace

#endif // end GEOMETRY_ESTIMATOR_TYPE_HPP

//---------------------------------------------------------------------------//
// end Geometry_EstimatorType.hpp
//---------------------------------------------------------------------------//
