//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModel_def.hpp
//! \author Alex Robinson
//! \brief  Root model class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_MODEL_DEF_HPP
#define GEOMETRY_ROOT_MODEL_DEF_HPP

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
template<template<typename,typename,typename...> class MapType>
void RootModel::getCellMaterialNames(
                         MapType<ModuleTraits::InternalCellHandle,std::string>&
                         cell_id_mat_name_map ) const
{
  // Make sure that root is initialized
  testPrecondition( this->isInitialized() );

  // Get a list of the cells
  TObjArray* cells = d_manager->GetListOfVolumes();
  size_t number_of_cells = cells->GetEntries();

  TIterator* cell_it  = cells->MakeIterator();

  for( size_t i = 0; i < number_of_cells; ++i )
  {
    // Get the cell
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( cell_it->Next() );

    // Get the cell material
    TGeoMaterial* mat = cell->GetMaterial();

    // Add the material name to the map
    cell_id_mat_name_map[cell->GetUniqueID()] = mat->GetName();
  }
}

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootModel_def.hpp
//---------------------------------------------------------------------------//
