//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Model.cpp
//! \author Alex Robinson
//! \brief  The geometry model base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Geometry_Model.hpp"

namespace Geometry{

// The invalid cell handle
auto Model::invalidCellHandle() -> InternalCellHandle
{
  return Navigator::invalidCellHandle();
}

// The invalid surface handle
auto Model::invalidSurfaceHandle() -> InternalSurfaceHandle
{
  return Navigator::invalidSurfaceHandle();
}

// The invalid material handle
auto Model::invalidMaterialHandle() -> InternalMaterialHandle
{
  return std::numeric_limits<InternalMaterialHandle>::max();
}

// The invalid estimator handle
auto Model::invalidEstimatorHandle() -> InternalEstimatorHandle
{
  return std::numeric_limits<InternalEstimatorHandle>::max();
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_Model.cpp
//---------------------------------------------------------------------------//
