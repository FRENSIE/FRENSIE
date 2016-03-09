//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterface_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root Specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize the Root geometry module interface static member data
const ModuleInterface<Root>::ExternalSurfaceHandle
ModuleInterface<Root>::invalid_external_surface_handle = 0;

const ModuleInterface<Root>::ExternalCellHandle
ModuleInterface<Root>::invalid_external_cell_handle = 0;

// Do just in time initialization of interface members
void ModuleInterface<Root>::initialize()
{ 
  TEST_FOR_EXCEPTION( !Root::isInitialized(),
                      std::logic_error,
                      "Error: Root must be initialized before the geometry "
                      "module interface!" );
}		       				    

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.cpp
//---------------------------------------------------------------------------//
