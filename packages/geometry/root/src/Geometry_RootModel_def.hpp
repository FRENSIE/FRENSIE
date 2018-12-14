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
#include "Utility_JustInTimeInitializer.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Get the cell materials
template<template<typename,typename,typename...> class MapType>
void RootModel::getCellMaterialNames( MapType<EntityId,std::string>&
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

// Save the model to an archive
template<typename Archive>
void RootModel::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Model );

  // Save the model properties - all other data will be reinitialized
  ar & BOOST_SERIALIZATION_NVP( d_model_properties );
}

// Load the model from an archive
template<typename Archive>
void RootModel::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Model );

  // Load the model properties only - all other data must be reinitialized
  ar & BOOST_SERIALIZATION_NVP( d_model_properties );

  Utility::JustInTimeInitializer::getInstance().addObject( *this );
}

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootModel_def.hpp
//---------------------------------------------------------------------------//
