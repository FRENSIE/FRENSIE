//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root singleton wrapper class
//!
//---------------------------------------------------------------------------//

// Root Includes
#include <TError.h>

// FRENSIE Includes
#include "Geometry_Root.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize static member data
TGeoManager* Root::s_manager = NULL;
std::string Root::s_terminal_material_name;

// Initialize the root geometry manager
void Root::initialize( const std::string& filename )
{
  s_manager = TGeoManager::Import( filename.c_str() );
  
  // Tell ROOT to suppress all non-fatal messages
  gErrorIgnoreLevel = kFatal;
  
  s_terminal_material_name = "graveyard";
}

} // end Geoemtry namespace

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
