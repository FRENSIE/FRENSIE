//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root_def.hpp
//! \author Alex Robinson
//! \brief  Root singleton wrapper class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_DEF_HPP
#define GEOMETRY_ROOT_DEF_HPP

// Std Lib Includes
#include <unordered_map>
#include <string>
#include <sstream>

// Root Includes
#include <TGeoMaterial.h>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Geometry{

// Get the cell materials
/*! \details The key type must be a ModuleTraits::InternalCellHandle. The
 * mapped type must be a string. 
 */
template<typename Map>
void Root::getCellMaterialNames( Map& cell_id_mat_name_map )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );

  // Get a list of the cells
  TObjArray* cells = s_manager->GetListOfVolumes();
  unsigned long long number_of_cells = cells->GetEntries();
  
  TIterator* cell_it  = cells->MakeIterator();

  for( unsigned long long i = 0ull; i < number_of_cells; ++i )
  {
    // Get the cell
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( cell_it->Next() );
    
    // Get the cell material
    TGeoMaterial* mat = cell->GetMaterial();

    // Add the material name to the map
    cell_id_mat_name_map[cell->GetUniqueID()] = mat->GetName();
  }
}

// Get the cell material ids
/*! \details The key type must be a ModuleTraits::InternalCellHandle. The
 * mapped type must be a string.
 */
template<typename Map>
void Root::getCellMaterialIds( Map& cell_id_mat_id_map )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );

  // Set the material property name plus underscore separator
  std::string material_property_suffix = 
    Root::getMaterialPropertyName() + "_";

  // Get the cell material names
  std::unordered_map<ModuleTraits::InternalCellHandle,std::string>
    cell_id_material_name;
  
  Root::getCellMaterialNames( cell_id_material_name );

  std::unordered_map<ModuleTraits::InternalCellHandle,std::string>::const_iterator
    cell_it = cell_id_material_name.begin();

  while( cell_it != cell_id_material_name.end() )
  {
    const std::string& material_name = cell_it->second;

    if( material_name != Root::getVoidMaterialName() &&
        material_name != Root::getTerminalMaterialName() )
    {
      TEST_FOR_EXCEPTION( material_name.find( material_property_suffix ) != 0,
                          InvalidRootGeometry,
                          "Error: ROOT cell " << cell_it->first << 
                          " used an invalid material name ("
                          << material_name << ")!" );
      
      TEST_FOR_EXCEPTION( material_name.find_first_not_of( "0123456789", material_property_suffix.size() )
                          < material_name.size(),
                          InvalidRootGeometry,
                          "Error: ROOT cell " << cell_it->first << 
                          "used an invalid material name ("
                          << material_name << ")!" );
      
      // Extract the material id from the name
      std::istringstream iss( material_name.substr( material_property_suffix.size() ) );

      unsigned long long mat_id;
      
      iss >> mat_id;
      
      cell_id_mat_id_map[cell_it->first] = mat_id;
    }

    ++cell_it;
  }
}

// Get the cell densities
/*! \details The key type must be a ModuleTraits::InternalCellHandle. The
 * mapped type must be a double. Note that void and terminal cells will
 * not be added to the map.
 */
template<typename Map>
void Root::getCellDensities( Map& cell_id_density_map )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );

  // Get a list of the cells
  TObjArray* cells = s_manager->GetListOfVolumes();
  unsigned long long number_of_cells = cells->GetEntries();
  
  TIterator* cell_it  = cells->MakeIterator();

  for( unsigned long long i = 0ull; i < number_of_cells; ++i )
  {
    // Get the cell
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( cell_it->Next() );
    
    // Get the cell material
    TGeoMaterial* mat = cell->GetMaterial();

    // Get the material name
    std::string mat_name = mat->GetName();

    // Add the density to the map
    if( mat_name != Root::getVoidMaterialName() &&
        mat_name != Root::getTerminalMaterialName() )
    {
      TEST_FOR_EXCEPTION( mat->GetDensity() == 0.0,
                          InvalidRootGeometry,
                          "Error: ROOT cell " << cell->GetUniqueID() <<
                          "has an invalid density ("
                          << mat->GetDensity() << ")!" );
      
      cell_id_density_map[cell->GetUniqueID()] = mat->GetDensity();
    }
  }
}

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_Root_def.hpp
//---------------------------------------------------------------------------//
