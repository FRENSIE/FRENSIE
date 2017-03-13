//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModelProperties.hpp
//! \author Alex Robinson
//! \brief  Root model properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_MODEL_PROPERTIES_HPP
#define GEOMETRY_ROOT_MODEL_PROPERTIES_HPP

// Std Lib Includes
#include <string>

namespace Geometry{

//! The Root model properties
class RootModelProperties
{

public:

  //! Constructor
  RootModelProperties( const std::string& filename );

  //! Destructor
  ~RootModelProperties()
  { /* ... */ }

  //! Get the model file name
  const std::string& getModelFileName() const;

  //! Get the material property name
  const std::string& getMaterialPropertyName() const;

  //! Set the material property name
  void setMaterialPropertyName( const std::string& material_property_name );

  //! Get the void material property name
  const std::string& getVoidMaterialName() const;

  //! Set the void material property name
  void setVoidMaterialName( const std::string& void_material_name );

  //! Get the terminal material property name
  const std::string& getTerminalMaterialName() const;

  //! Set the terminal material property name
  void setTerminalMaterialName( const std::string& terminal_material_name );

private:

  // The model file name
  std::string d_file_name;

  // The material property name
  std::string d_material_property_name;

  // The void material name
  std::string d_void_material_name;

  // The terminal material name
  std::string d_terminal_material_name;
};
  
} // end Geometry namespace

#endif // end GEOMETRY_ROOT_MODEL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootModelProperties.hpp
//---------------------------------------------------------------------------//
