//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ModuleTraits.cpp
//! \author Alex Robinson
//! \brief  Module traits class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

// Initialize static member data
const ModuleTraits::InternalROIHandle
ModuleTraits::reserved_internal_roi_handle =
  std::numeric_limits<ModuleTraits::InternalROIHandle>::max();

const ModuleTraits::InternalEventObserverHandle
ModuleTraits::invalid_internal_event_observer_handle =
  Geometry::ModuleTraits::invalid_internal_estimator_handle;

const ModuleTraits::InternalMaterialHandle
ModuleTraits::invalid_internal_material_handle =
  Geometry::ModuleTraits::invalid_internal_material_handle;

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ModuleTraits.cpp
//---------------------------------------------------------------------------//
