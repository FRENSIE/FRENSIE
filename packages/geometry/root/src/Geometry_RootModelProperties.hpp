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

// Boost Includes
#include <boost/filesystem.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Geometry{

//! The Root model properties
class RootModelProperties
{

public:

  //! Constructor
  RootModelProperties( const boost::filesystem::path& filename );

  //! Destructor
  ~RootModelProperties()
  { /* ... */ }

  //! Set the default file path
  static void setDefaultFilePath( const boost::filesystem::path& file_path );

  //! Get the default file path
  static std::string getDefaultFilePath();

  //! Get the model file name
  const std::string& getModelFileName() const;

  //! Get the model file path
  std::string getModelFilePath() const;

  //! Get the model file name with path
  std::string getModelFileNameWithPath() const;

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

  // Default constructor
  RootModelProperties();

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The default file path
  static boost::filesystem::path s_default_path;

  // The model file name
  std::string d_file_name;

  // The model file path
  boost::filesystem::path d_file_path;

  // The material property name
  std::string d_material_property_name;

  // The void material name
  std::string d_void_material_name;

  // The terminal material name
  std::string d_terminal_material_name;
};

// Save the model to an archive
template<typename Archive>
void RootModelProperties::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_file_name );

  std::string raw_file_path = d_file_path.string();

  ar & BOOST_SERIALIZATION_NVP( raw_file_path );
  
  ar & BOOST_SERIALIZATION_NVP( d_material_property_name );
  ar & BOOST_SERIALIZATION_NVP( d_void_material_name );
  ar & BOOST_SERIALIZATION_NVP( d_terminal_material_name );
}

// Load the model from an archive
template<typename Archive>
void RootModelProperties::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_file_name );

  std::string raw_file_path;

  ar & BOOST_SERIALIZATION_NVP( raw_file_path );

  d_file_path = raw_file_path;
  d_file_path.make_preferred();

  // If the path doesn't exist - try to use the default path
  if( !boost::filesystem::exists( d_file_path ) ||
      !boost::filesystem::exists( d_file_path / d_file_name ) )
    d_file_path = s_default_path;
  
  ar & BOOST_SERIALIZATION_NVP( d_material_property_name );
  ar & BOOST_SERIALIZATION_NVP( d_void_material_name );
  ar & BOOST_SERIALIZATION_NVP( d_terminal_material_name );
}

} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_VERSION( RootModelProperties, Geometry, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( RootModelProperties, Geometry );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry, RootModelProperties );

#endif // end GEOMETRY_ROOT_MODEL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootModelProperties.hpp
//---------------------------------------------------------------------------//
