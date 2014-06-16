//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCHelpers.cpp
//! \author Alex Robinson
//! \brief  DagMC helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <map>

// MOAB Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize DagMC
void initializeDagMC(
	   const std::string& geometry_file_name, 
	   const std::vector<std::string>& property_names,
	   const double facet_tol )
{
  // Make sure that the file name is valid
  testPrecondition( geometry_file_name.size() > 0 );
  testPrecondition( geometry_file_name.find(".sat")<geometry_file_name.size()||
		    geometry_file_name.find(".h5m")<geometry_file_name.size());
  // Make sure that at least one property name is specified
  testPrecondition( property_names.size() > 0 );
  // Make sure that the facet tolerance is valid
  testPrecondition( facet_tol >= 0 );

  // Get an instance of DagMC
  moab::DagMC* dagmc_instance = moab::DagMC::instance();

  // Load the geometry
  moab::ErrorCode return_value =
    dagmc_instance->load_file( geometry_file_name.c_str(), facet_tol );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Initialize the OBB Tree
  return_value = dagmc_instance->init_OBBTree();

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Detect the available properties in the geometry file
  std::vector<std::string> available_property_names;
  return_value = 
    dagmc_instance->detect_available_props( available_property_names );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Check that the properties names found are valid
  std::string invalid_property_names;
  validatePropertyNames( available_property_names,
  			 property_names,
  			 invalid_property_names );
  
  TEST_FOR_EXCEPTION( invalid_property_names.size() > 0,
		      Utility::MOABException,
		      "Invalid properties: " + invalid_property_names );

  // Parse the properties
  return_value = dagmc_instance->parse_properties( property_names );
						     
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Validate the properties that DagMC found in the geometry file
void validatePropertyNames(
		      const std::vector<std::string>& available_property_names,
		      const std::vector<std::string>& valid_property_names,
		      std::string& invalid_property_names )
{
  for( unsigned i = 0; i < available_property_names.size(); ++i )
  {
    bool valid_name = false;
    
    for( unsigned j = 0; j < valid_property_names.size(); ++j )
    {
      if( available_property_names[i].compare( valid_property_names[j] ) == 0 )
      {
	valid_name = true;
	break;
      }
    }
    
    if( !valid_name )
    {
      if( invalid_property_names.size() > 0 )
	invalid_property_names += ", ";
      
      invalid_property_names += available_property_names[i];
    }
  }
}

// Validate the synonyms map
void validateSynonymNames(const std::vector<std::string>& valid_property_names,
			  const std::map<std::string,std::string>& synonyms,
			  std::string& invalid_property_names )
{
  std::map<std::string,std::string>::const_iterator it = synonyms.begin();

  while( it != synonyms.end() )
  {
    bool valid_name = false;

    for( unsigned j = 0u; j < valid_property_names.size(); ++j )
    {
      if( it->second.compare( valid_property_names[j] ) == 0 )
      {
	valid_name = true;
	break;
      }
    }

    if( !valid_name )
    {
      if( invalid_property_names.size() > 0 )
	invalid_property_names += ", ";

      invalid_property_names += it->second;
    }

    ++it;
  }
}
		       
// Return all of the property values associated with a prop. name and cell id
void getCellPropertyValues( 
          const std::string& property,
          boost::unordered_map<ModuleTraits::InternalCellHandle,
			       std::vector<std::string> >&
	  cell_id_prop_val_map )
{
  // Clear the map
  cell_id_prop_val_map.clear();
  
  // Get an instance of DagMC
  moab::DagMC* dagmc_instance = moab::DagMC::instance();

  std::vector<moab::EntityHandle> entities_with_property;

  // Get all of the cells with the desired property
  moab::ErrorCode return_value =
    dagmc_instance->entities_by_property( property, entities_with_property, 3);
		       
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Get the property value for each cell
  for( unsigned i = 0u; i < entities_with_property.size(); ++i )
  {
    ModuleTraits::InternalSurfaceHandle cell_id = 
      dagmc_instance->get_entity_id( entities_with_property[i] );
    
    return_value = 
      dagmc_instance->prop_values( entities_with_property[i],
				   property,
				   cell_id_prop_val_map[cell_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );
  }
}

// Return all of the property values associated with a prop. name and surf. id
void getSurfacePropertyValues( 
      const std::string& property,
      boost::unordered_map<ModuleTraits::InternalSurfaceHandle,
			   std::vector<std::string> >&
      surface_id_prop_val_map )
{
  // Clear the map
  surface_id_prop_val_map.clear();
  
  // Get an instance of DagMC
  moab::DagMC* dagmc_instance = moab::DagMC::instance();

  std::vector<moab::EntityHandle> entities_with_property;

  // Get all of the surfaces with the desired property
  moab::ErrorCode return_value =
    dagmc_instance->entities_by_property( property, entities_with_property, 2);
		       
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Get the property value for each surface
  for( unsigned i = 0u; i < entities_with_property.size(); ++i )
  {
    ModuleTraits::InternalSurfaceHandle surface_id = 
      dagmc_instance->get_entity_id( entities_with_property[i] );
    
    return_value = 
      dagmc_instance->prop_values( entities_with_property[i],
				   property,
				   surface_id_prop_val_map[surface_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );
  }
}

// Return all of the cell ids with a property value
void getCellIdsWithPropertyValue(
	  const std::string& property,
          boost::unordered_map<std::string,
			       std::vector<ModuleTraits::InternalCellHandle> >&
	  prop_val_cell_id_map )
{
  // Clear the map
  prop_val_cell_id_map.clear();

  // Get an instance of DagMC
  moab::DagMC* dagmc_instance = moab::DagMC::instance();

  // Get all of the values for the desired property
  std::vector<std::string> property_values;
  
  moab::ErrorCode return_value =
    dagmc_instance->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> entities;
  
  for( unsigned i = 0u; i < property_values.size(); ++i )
  {
    return_value = dagmc_instance->entities_by_property( property,
							 entities,
							 3,
							 &property_values[i] );

    std::vector<ModuleTraits::InternalCellHandle>& cell_ids = 
      prop_val_cell_id_map[property_values[i]];
    
    cell_ids.resize( entities.size() );

    // Convert the entity handles to cell ids
    for( unsigned j = 0u; j < entities.size(); ++j )
      cell_ids[j] = dagmc_instance->get_entity_id( entities[j] );

    entities.clear();
  }
}

// Return all of the surface ids with a property value
void getSurfaceIdsWithPropertyValue(
      const std::string& property,
      boost::unordered_map<std::string,
			   std::vector<ModuleTraits::InternalSurfaceHandle> >&
      prop_val_surface_id_map )
{
  // Clear the map
  prop_val_surface_id_map.clear();

  // Get an instance of DagMC
  moab::DagMC* dagmc_instance = moab::DagMC::instance();

  // Get all of the values for the desired property
  std::vector<std::string> property_values;
  
  moab::ErrorCode return_value =
    dagmc_instance->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> entities;
  
  for( unsigned i = 0u; i < property_values.size(); ++i )
  {
    return_value = dagmc_instance->entities_by_property( property,
							 entities,
							 2,
							 &property_values[i] );

    std::vector<ModuleTraits::InternalSurfaceHandle>& surface_ids = 
      prop_val_surface_id_map[property_values[i]];
    
    surface_ids.resize( entities.size() );

    // Convert the entity handles to cell ids
    for( unsigned j = 0u; j < entities.size(); ++j )
      surface_ids[j] = dagmc_instance->get_entity_id( entities[j] );

    entities.clear();
  }
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCHelpers.cpp
//---------------------------------------------------------------------------//
