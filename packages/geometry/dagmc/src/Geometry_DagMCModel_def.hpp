//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModel_def.hpp
//! \author Alex Robinson
//! \brief  DagMC model class template and inline definitions
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_MODEL_DEF_HPP
#define GEOMETRY_DAGMC_MODEL_DEF_HPP

// Std Lib Includes
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Get the property values associated with a property name
template<template<typename,typename...> class ArrayType>
void DagMCModel::getPropertyValues( const std::string& property,
                                    ArrayType<std::string>& values ) const
{
  // Make sure DagMC has been initialized
  testPrecondition( this->isInitialized() );

  std::vector<std::string> stored_values;

  this->getPropertyValues( property, stored_values );

  values.resize( stored_values.size() );

  for( unsigned i = 0; i < stored_values.size(); ++i )
    values[i] = stored_values[i];
}

// Get the property values associated with a property name and cell id
template<template<typename,typename...> class ArrayType,
         template<typename,typename,typename...> class MapType>
void DagMCModel::getCellPropertyValues(
             const std::string& property,
             MapType<ModuleTraits::InternalCellHandle,ArrayType<std::string> >&
             cell_id_prop_val_map ) const
{
  // Make sure DagMC has been initialized
  testPrecondition( this->isInitialized() );

  std::vector<moab::EntityHandle> cells_with_property;

  // Get all of the cells with the desired property
  try{
    this->getCellsWithProperty( cells_with_property, property );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to extract cells with property "
                           << property << "!" );

  // Get the property value for each cell
  for( unsigned i = 0u; i < cells_with_property.size(); ++i )
  {
    ModuleTraits::InternalCellHandle cell_id =
      d_cell_handler->getCellId( cells_with_property[i] );

    moab::ErrorCode return_value =
      d_dagmc->prop_values( cells_with_property[i],
                            property,
                            cell_id_prop_val_map[cell_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			InvalidDagMCGeometry,
			moab::ErrorCodeStr[return_value] );
  }
}

// Get the cell ids with a property value
template<template<typename,typename...> class ArrayType,
         template<typename,typename,typename...> class MapType>
void DagMCModel::getCellIdsWithPropertyValue(
             const std::string& property,
             MapType<std::string,ArrayType<ModuleTraits::InternalCellHandle> >&
             prop_val_cell_id_map ) const
{
  // Make sure DagMC has been initialized
  testPrecondition( this->isInitialized() );

  // Get all of the values for the desired property
  std::vector<std::string> property_values;

  moab::ErrorCode return_value =
    d_dagmc->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> cells;

  for( unsigned i = 0u; i < property_values.size(); ++i )
  {
    try{
      this->getCellsWithProperty( cells, property, &property_values[i] );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Unable to extract cells with property "
                             << property << " and value "
                             << property_values[i] << "!" );

    if( cells.size() > 0 )
    {
      std::vector<ModuleTraits::InternalCellHandle>& cell_ids =
	prop_val_cell_id_map[property_values[i]];

      cell_ids.resize( cells.size() );

      // Convert the entity handles to cell ids
      for( unsigned j = 0u; j < cells.size(); ++j )
	cell_ids[j] = d_cell_handler->getCellId( cells[j] );

      cells.clear();
    }
  }
}

// Get the property values associated with a property name and surface id
template<template<typename,typename...> class ArrayType,
         template<typename,typename,typename...> class MapType>
void DagMCModel::getSurfacePropertyValues(
          const std::string& property,
          MapType<ModuleTraits::InternalSurfaceHandle,ArrayType<std::string> >&
          surface_id_prop_val_map ) const
{
  // Make sure DagMC has been initialized
  testPrecondition( this->isInitialized() );

  std::vector<moab::EntityHandle> surfaces_with_property;

  // Get all of the surfaces with the desired property
  try{
    this->getSurfacesWithProperty( surfaces_with_property, property );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to extract surfaces with property "
                           << property << "!" );

  // Get the property value for each surface
  for( unsigned i = 0u; i < surfaces_with_property.size(); ++i )
  {
    ModuleTraits::InternalSurfaceHandle surface_id =
      d_surface_handler->getSurfaceId( surfaces_with_property[i] );

    moab::EntityHandle return_value =
      d_dagmc->prop_values( surfaces_with_property[i],
                            property,
                            surface_id_prop_val_map[surface_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			InvalidDagMCGeometry,
			moab::ErrorCodeStr[return_value] );
  }
}

// Get the surface ids with a property value
/* The key type must be a std::string. The mapped type must be
 * an array of ModuleTraits::InternalSurfaceHandle types. This method is
 * thread safe as long as enableThreadSupport has been called.
 */
template<template<typename,typename...> class ArrayType,
         template<typename,typename,typename...> class MapType>
void DagMCModel::getSurfaceIdsWithPropertyValue(
          const std::string& property,
          MapType<std::string,ArrayType<ModuleTraits::InternalSurfaceHandle> >&
          prop_val_surface_id_map ) const
{
  // Make sure DagMC has been initialized
  testPrecondition( this->isInitialized() );

  // Get all of the values for the desired property
  std::vector<std::string> property_values;

  moab::ErrorCode return_value =
    d_dagmc->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> surfaces;

  for( unsigned i = 0u; i < property_values.size(); ++i )
  {
    return_value = d_dagmc->entities_by_property( property,
                                                  surfaces,
                                                  2,
                                                  &property_values[i] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );

    if( surfaces.size() > 0 )
    {
      std::vector<ModuleTraits::InternalSurfaceHandle>& surface_ids =
	prop_val_surface_id_map[property_values[i]];

      surface_ids.resize( surfaces.size() );

      // Convert the entity handles to surface ids
      for( unsigned j = 0u; j < surfaces.size(); ++j )
	surface_ids[j] = d_surface_handler->getSurfaceId( surfaces[j] );

      surfaces.clear();
    }
  }
}

// Extract estimator property values
// An estimator property is assumed to have the form id.type.ptype
template<typename IntType>
void DagMCModel::extractEstimatorPropertyValues(
                                            const std::string& prop_value,
                                            IntType& estimator_id,
                                            EstimatorType& estimator_type,
                                            ParticleType& particle_type ) const
{
  size_t first_pos = prop_value.find_first_of( "." );
  size_t last_pos = prop_value.find_last_of( "." );

  // Make sure the estimator property format is valid
  TEST_FOR_EXCEPTION( first_pos > prop_value.size(),
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( last_pos > prop_value.size(),
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( first_pos == last_pos,
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );

  std::string id_string = prop_value.substr( 0, first_pos );

  std::istringstream iss( id_string );

  iss >> estimator_id;

  std::string estimator_name =
    prop_value.substr( first_pos+1, last_pos-first_pos-1 );

  // Make sure the estimator type is valid
  TEST_FOR_EXCEPTION(
                   !d_model_properties->isEstimatorNameValid( estimator_name ),
                   InvalidDagMCGeometry,
                   "estimator " << estimator_id <<
                   " has an invalid estimator type ("
                   << estimator_type << ") specified!" );

  estimator_type = d_model_properties->getEstimatorType( estimator_name );

  std::string particle_name =
    prop_value.substr( last_pos+1, prop_value.size()-last_pos-1);

  // Make sure the particle type is valid
  TEST_FOR_EXCEPTION(
                     !d_model_properties->isParticleNameValid( particle_name ),
                     InvalidDagMCGeometry,
                     "estimator " << estimator_id <<
                     " has an invalid particle type (" << particle_type <<
                     ") specified!" );

  particle_type = d_model_properties->getParticleType( particle_name );
}

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModel_def.hpp
//---------------------------------------------------------------------------//
