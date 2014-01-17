//---------------------------------------------------------------------------//
//!
//! \file   DagMCHelpers.cpp
//! \author Alex Robinson
//! \brief  DagMC helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes


// MOAB Includes
#include <DagMC.hpp>

// FACEMC Includes
#include "DagMCHelpers.hpp"
#include "MOABException.hpp"
#include "ContractException.hpp"
#include "ExceptionTestMacros.hpp"

namespace FACEMC{

// Initialize DagMC
void initializeDagMC( const std::string& geometry_file_name, 
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
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Initialize the OBB Tree
  return_value = dagmc_instance->init_OBBTree();

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Detect the available properties in the geometry file
  std::vector<std::string> available_property_names;
  return_value = 
    dagmc_instance->detect_available_props( available_property_names );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Check that the properties names found are valid
  std::string invalid_property_names;
  validatePropertyNames( available_property_names,
			 property_names,
			 invalid_property_names );
  
  TEST_FOR_EXCEPTION( invalid_property_names.size() > 0,
		      FACEMC::MOABException,
		      "Invalid properties: " + invalid_property_names);

  // Parse the properties
  return_value = dagmc_instance->parse_properties( property_names );

  TEST_FOR_EXCEPTION( invalid_property_names.size() > 0,
		      FACEMC::MOABException,
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DagMCHelpers.cpp
//---------------------------------------------------------------------------//
