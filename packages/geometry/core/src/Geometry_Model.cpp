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
#include "FRENSIE_Archives.hpp"
#include "Geometry_Model.hpp"

namespace Geometry{

// The invalid cell id
auto Model::invalidCellId() -> EntityId
{
  return Navigator::invalidCellId();
}

// The invalid surface id
auto Model::invalidSurfaceId() -> EntityId
{
  return Navigator::invalidSurfaceId();
}

// The invalid material id
auto Model::invalidMaterialId() -> MaterialId
{
  return std::numeric_limits<MaterialId>::max();
}

// The invalid estimator id
auto Model::invalidEstimatorId() -> EstimatorId
{
  return std::numeric_limits<EstimatorId>::max();
}
  
} // end Geometry namespace

EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry::Model );

//---------------------------------------------------------------------------//
// end Geometry_Model.cpp
//---------------------------------------------------------------------------//
