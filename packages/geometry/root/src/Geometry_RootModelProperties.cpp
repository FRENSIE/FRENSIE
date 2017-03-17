//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModelProperties.cpp
//! \author Alex Robinson
//! \brief  Root model properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_RootModelProperties.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
RootModelProperties::RootModelProperties( const std::string& filename )
  : d_file_name( filename ),
    d_material_property_name( "mat" ),
    d_void_material_name( "void" ),
    d_terminal_material_name( "graveyard" )
{
  // Make sure that the file name is valid
  testPrecondition( filename.size() > 0 );
}

// Get the model file name
const std::string& RootModelProperties::getModelFileName() const
{
  return d_file_name;
}

// Get the material property name
const std::string& RootModelProperties::getMaterialPropertyName() const
{
  return d_material_property_name;
}

// Set the material property name
void RootModelProperties::setMaterialPropertyName(
                                    const std::string& material_property_name )
{
  // Make sure that the material property name is valid
  testPrecondition( material_property_name.size() > 0 );

  d_material_property_name = material_property_name;
}

// Get the void material property name
const std::string& RootModelProperties::getVoidMaterialName() const
{
  return d_void_material_name;
}

// Set the void material property name
void RootModelProperties::setVoidMaterialName(
                                        const std::string& void_material_name )
{
  // Make sure that the void material name is valid
  testPrecondition( void_material_name.size() > 0 );
  
  d_void_material_name = void_material_name;
}

// Get the terminal material property name
const std::string& RootModelProperties::getTerminalMaterialName() const
{
  return d_terminal_material_name;
}

// Set the terminal material property name
void RootModelProperties::setTerminalMaterialName(
                                    const std::string& terminal_material_name )
{
  // Make sure that the terminal material name is valid
  testPrecondition( terminal_material_name.size() > 0 );
  
  d_terminal_material_name = terminal_material_name;
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_RootModelProperties.cpp
//---------------------------------------------------------------------------//
