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
TGeoManager* Root::getManager()
{
  return d_manager; 
}

// Initialize the root geometry manager
void Root::initialize( const std::string& filename)
{
  d_manager = TGeoManager::Import( filename.c_str() );
}

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
