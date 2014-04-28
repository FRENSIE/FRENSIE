//---------------------------------------------------------------------------//
//!
//! \file   ModuleTraits.cpp
//! \author Alex Robinson
//! \brief  Module traits class definition
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "ModuleTraits.hpp"

namespace FACEMC{

namespace Traits{

// Initialize static member data
const ModuleTraits::InternalCellHandle 
ModuleTraits::invalid_internal_cell_handle =
  std::numeric_limits<ModuleTraits::InternalCellHandle>::max();

const ModuleTraits::InternalSurfaceHandle
ModuleTraits::invalid_internal_surface_handle =
  std::numeric_limits<ModuleTraits::InternalSurfaceHandle>::max();

const ModuleTraits::InternalEstimatorHandle
ModuleTraits::invalid_internal_estimator_handle =
  std::numeric_limits<ModuleTraits::InternalEstimatorHandle>::max();

const ModuleTraits::InternalMaterialHandle
ModuleTraits::invalid_internal_material_handle = 
  std::numeric_limits<ModuleTraits::InternalMaterialHandle>::max();

} // end Traits namespace

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ModuleTraits.cpp
//---------------------------------------------------------------------------//
