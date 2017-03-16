//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModuleTraits.cpp
//! \author Alex Robinson
//! \brief  Geometry module traits class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Geometry_ModuleTraits.hpp"

namespace Geometry{

// Initialize static member data
const ModuleTraits::InternalCellHandle
ModuleTraits::invalid_internal_cell_handle = 0;

const ModuleTraits::InternalSurfaceHandle
ModuleTraits::invalid_internal_surface_handle = 0;

const ModuleTraits::InternalMaterialHandle
ModuleTraits::invalid_internal_material_handle =
  std::numeric_limits<ModuleTraits::InternalMaterialHandle>::max();

const ModuleTraits::InternalEstimatorHandle
ModuleTraits::invalid_internal_estimator_handle =
  std::numeric_limits<ModuleTraits::InternalEstimatorHandle>::max();

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModuleTraits.cpp
//---------------------------------------------------------------------------//
