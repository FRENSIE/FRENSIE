//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModelPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Root model properties factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Geometry_RootModelPropertiesFactory.hpp"
#include "Geometry_RootLoggingMacros.hpp"
#include "Utility_ParameterListHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Load the Root model properties
std::shared_ptr<const RootModelProperties>
RootModelPropertiesFactory::createProperties(
                                     const Teuchos::ParameterList& properties )
{
  // The handler property must be defined
  TEST_FOR_EXCEPTION( !properties.isParameter( "Handler" ),
                      std::runtime_error,
                      "Unable to determine the geometry handler type!" );

  // The handler type must be ROOT
  TEST_FOR_EXCEPTION( properties.get<std::string>( "Handler" ) != "ROOT",
                      std::runtime_error,
                      "Invalid geometry handler type ("
                      << properties.get<std::string>( "Handler" ) << ")!" );

  // The root file property must be present
  TEST_FOR_EXCEPTION( !properties.isParameter( "Root File" ),
                      std::runtime_error,
                      "The Root file needs to be specified!" );
  
  // Create the new Root model properties object
  std::shared_ptr<RootModelProperties>
    model_properties( new RootModelProperties(
                                properties.get<std::string>( "Root File" ) ) );

  // Get the material property name (optional)
  if( properties.isParameter( "Material Property Name" ) )
  {
    const std::string material_property_name =
      properties.get<std::string>( "Material Property Name" );

    TEST_FOR_EXCEPTION( material_property_name.size() == 0,
                        std::runtime_error,
                        "The material property name cannot be an empty "
                        "string!" );

    model_properties->setMaterialPropertyName( material_property_name );
  }

  // Get the void material name (optional)
  if( properties.isParameter( "Void Material Name" ) )
  {
    const std::string void_material_name =
      properties.get<std::string>( "Void Material Name" );

    TEST_FOR_EXCEPTION( void_material_name.size() == 0,
                        std::runtime_error,
                        "The void material name cannot be an empty string!" );

    model_properties->setVoidMaterialName( void_material_name );
  }

  // Get the terminal material name (optional)
  if( properties.isParameter( "Terminal Material Name" ) )
  {
    const std::string terminal_material_name =
      properties.get<std::string>( "Terminal Material Name" );

    TEST_FOR_EXCEPTION( terminal_material_name.size() == 0,
                        std::runtime_error,
                        "The terminal material name cannot be an empty "
                        "string!" );

    model_properties->setTerminalMaterialName( terminal_material_name );
  }

  // Log unused parameters
  std::vector<std::string> unused_parameters;

  Utility::getUnusedParameterWarningMessages( properties, unused_parameters );

  for( size_t i = 0; i < unused_parameters.size(); ++i )
  {
    FRENSIE_LOG_ROOT_WARNING( unused_parameters[i] );
  }

  FRENSIE_FLUSH_ALL_LOGS();

  return model_properties;
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_RootModelPropertiesFactory.cpp
//---------------------------------------------------------------------------//
