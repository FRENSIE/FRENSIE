//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root singleton wrapper class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_Root.hpp"
#include "Utility_ContractException.hpp"

// Get the geometry manager instance
TGeoManager* getManager()
{
  return d_manager; 
}

// Get the terminal material
TGeoMaterial* getTerminalMaterial()
{
  return d_terminal_material;
}

// Initialize the root geometry manager
void initialize( const std::string& filename )
{
  d_manager = TGeoManager::Import( filename.c_str() );
  
  d_terminal_material = new TGeoMaterial("Terminal",0,0,0);
}

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
