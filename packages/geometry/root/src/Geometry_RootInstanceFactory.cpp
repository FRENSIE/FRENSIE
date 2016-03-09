//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootInstanceFactory.hpp
//! \author Eli Moll
//! \brief  Root instance factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <map>

// FRENSIE Includes
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_Root.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize the static member data
std::ostream* RootInstanceFactory::s_os_warn = NULL;

// Initialize Root
void RootInstanceFactory::initializeRoot( 
				       const Teuchos::ParameterList& geom_rep,
				       std::ostream& os_warn )
{
  // Set the warning output stream
  s_os_warn = &os_warn;

  // Validate the geometry representation
  RootInstanceFactory::validateGeometryRep( geom_rep );

  // Get the terminal material name (optional)
  if( geom_rep.isParameter( "Terminal Material Name" ) )
  {
    std::string terminal_material_name = 
      geom_rep.get<std::string>( "Terminal Material Name" );

    TEST_FOR_EXCEPTION( terminal_material_name.size() == 0,
                        std::runtime_error,
                        "Error: the terminal material name cannot be "
                        "an empty string!" );

    Root::setTerminalMaterialName( terminal_material_name );
  }

  // Get the void material name (optional)
  if( geom_rep.isParameter( "Void Material Name" ) )
  {
    std::string void_material_name =
      geom_rep.get<std::string>( "Void Material Name" );

    TEST_FOR_EXCEPTION( void_material_name.size() == 0,
                        std::runtime_error,
                        "Error: the void material name cannot be "
                        "an empty string!" );

    Root::setVoidMaterialName( void_material_name );
  }

  TEST_FOR_EXCEPTION( Root::getVoidMaterialName() ==
                      Root::getTerminalMaterialName(),
                      std::runtime_error,
                      "Error: the void material name and the terminal "
                      "material name must be different!" );

  // Get the material property name
  if( geom_rep.isParameter( "Material Property Name" ) )
  {
    std::string material_property_name =
      geom_rep.get<std::string>( "Material Property Name" );

    TEST_FOR_EXCEPTION( material_property_name.size() == 0,
                        std::runtime_error,
                        "Error: the material property name cannot be "
                        "an empty string!" );
                       
    Root::setMaterialPropertyName( material_property_name );
  }

  // Get the Root file name
  std::string root_file_name = geom_rep.get<std::string>( "Root File" );
  
  // Initialize the Root geometry handler
  Geometry::Root::initialize( root_file_name );

  // Print unused parameters
  geom_rep.unused( *s_os_warn );

}

// Validate a geometry representation
void RootInstanceFactory::validateGeometryRep( 
				       const Teuchos::ParameterList& geom_rep )
{
  testPrecondition( geom_rep.get<std::string>( "Handler" ) == "ROOT" );
  
  TEST_FOR_EXCEPTION( !geom_rep.isParameter( "Root File" ),
		      InvalidGeometryRepresentation,
		      "Error: The Root file needs to be specified!" );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_RootInstanceFactory.cpp
//---------------------------------------------------------------------------//
