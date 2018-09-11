//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModelProperties.cpp
//! \author Alex Robinson
//! \brief  Root model properties class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/serialization/string.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Geometry_RootModelProperties.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Initialize static member data
boost::filesystem::path RootModelProperties::s_default_path( "" );

// Default constructor
RootModelProperties::RootModelProperties()
  : RootModelProperties( "dummy" )
{ /* ... */ }

// Constructor
RootModelProperties::RootModelProperties( const boost::filesystem::path& filename )
  : d_file_name( filename.filename().string() ),
    d_file_path( filename.parent_path().make_preferred() ),
    d_material_property_name( "material" ),
    d_void_material_name( "void" ),
    d_terminal_material_name( "graveyard" )
{
  // Make sure that the file name is valid
  testPrecondition( filename.size() > 0 );
}

// Set the default file path
/*! \details This method should be called before loading the properties from
 * an archive.
 */
void RootModelProperties::setDefaultFilePath(
                                     const boost::filesystem::path& file_path )
{
  s_default_path = file_path;
  s_default_path.make_preferred();
}

// Get the default file path
std::string RootModelProperties::getDefaultFilePath()
{
  return s_default_path.string();
}

// Get the model file name
const std::string& RootModelProperties::getModelFileName() const
{
  return d_file_name;
}

// Get the model file path
std::string RootModelProperties::getModelFilePath() const
{
  return d_file_path.string();
}

// Get the model file name with path
std::string RootModelProperties::getModelFileNameWithPath() const
{
  return (d_file_path / d_file_name).string();
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

EXPLICIT_CLASS_SAVE_LOAD_INST( RootModelProperties );

} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( RootModelProperties, Geometry );

//---------------------------------------------------------------------------//
// end Geometry_RootModelProperties.cpp
//---------------------------------------------------------------------------//
