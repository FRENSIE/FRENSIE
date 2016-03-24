//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionModuleInterface_Native.cpp
//! \author Alex Robinson
//! \brief  Collision module interface specialization for the native handler
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CollisionModuleInterface_Native.hpp"

namespace MonteCarlo{

// Initialize static member data
const CollisionModuleInterface<CollisionHandler>::ExternalMaterialHandle 
CollisionModuleInterface<CollisionHandler>::invalid_external_material_handle = 
  ModuleTraits::invalid_internal_material_handle;

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionModuleInterface_Native.cpp
//---------------------------------------------------------------------------//
