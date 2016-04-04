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
const ModuleTraits::InternalSourceHandle
ModuleTraits::invalid_internal_source_handle = 
  std::numeric_limits<ModuleTraits::InternalSourceHandle>::max();
  
const ModuleTraits::InternalEventObserverHandle
ModuleTraits::invalid_internal_event_observer_handle =
  std::numeric_limits<ModuleTraits::InternalEventObserverHandle>::max();

const ModuleTraits::InternalMaterialHandle
ModuleTraits::invalid_internal_material_handle = 
  std::numeric_limits<ModuleTraits::InternalMaterialHandle>::max();

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ModuleTraits.cpp
//---------------------------------------------------------------------------//
