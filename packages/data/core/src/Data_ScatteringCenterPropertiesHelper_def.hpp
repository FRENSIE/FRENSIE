//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesHelper_def.hpp
//! \author Alex Robinson
//! \brief  The atom properties class template function definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_HELPER_DEF_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_HELPER_DEF_HPP

// FRENSIE Includes
#include "Utility_StaticOutputFormatter.hpp"

namespace Data{

// Check if there is data available with the desired format
template<typename PropertiesMap>
inline bool ScatteringCenterPropertiesHelper::dataAvailable(
                             const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type )
{
  return properties.find( file_type ) != properties.end();
}

// Check if there is data available with the desired format and table version
template<typename PropertiesMap>
inline bool ScatteringCenterPropertiesHelper::dataAvailable(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( file_type );

  if( properties_it != properties.end() )
  {
    if( properties_it->second.find( table_version ) != properties_it->second.end() )
      return true;
    else
      return false;
  }
  else
    return false;
}

// Get the data file types
template<typename PropertiesMap>
inline std::set<typename PropertiesMap::key_type>
ScatteringCenterPropertiesHelper::getDataFileTypes(
                                              const PropertiesMap& properties )
{
  std::set<typename PropertiesMap::key_type> file_types;

  typename PropertiesMap::const_iterator properties_it = properties.begin();

  while( properties_it != properties.end() )
  {
    file_types.insert( properties_it->first );

    ++properties_it;
  }

  return file_types;
}

// Get the data file versions
template<typename PropertiesMap>
inline std::set<unsigned> ScatteringCenterPropertiesHelper::getDataFileVersions(
                             const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type )
{
  std::set<unsigned> file_versions;

  typename PropertiesMap::const_iterator properties_it =
    properties.find( file_type );

  if( properties_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      properties_it->second.begin();

    while( version_it != properties_it->second.end() )
    {
      file_versions.insert( version_it->first );

      ++version_it;
    }
  }

  return file_versions;
}

// Get the recommended data file version
template<typename PropertiesMap>
unsigned ScatteringCenterPropertiesHelper::getMaxDataFileVersion(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const std::string& type_name )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( file_type );

  if( properties_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      properties_it->second.begin();

    unsigned version = 0u;

    while( version_it != properties_it->second.end() )
    {
      if( version < version_it->first )
        version = version_it->first;
      
      ++version_it;
    }

    return version;
  }
  else
  {
    THROW_EXCEPTION( InvalidScatteringCenterPropertiesRequest,
                     type_name << " data properties with file type "
                     << file_type << " does not have a recommended version!" );
  }
}

// Get the properties
template<typename Properties, typename PropertiesMap>
inline const Properties& ScatteringCenterPropertiesHelper::getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const std::string& type_name )
{
  return *ScatteringCenterPropertiesHelper::getSharedProperties<Properties>(
                                                                 properties,
                                                                 file_type,
                                                                 table_version,
                                                                 type_name );
}

// Get the properties
template<typename Properties, typename PropertiesMap>
inline const std::shared_ptr<const Properties>&
ScatteringCenterPropertiesHelper::getSharedProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const std::string& type_name )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( file_type );

  if( properties_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      properties_it->second.find( table_version );

    if( version_it != properties_it->second.end() )
      return version_it->second;
    else
    {
      THROW_EXCEPTION( InvalidScatteringCenterPropertiesRequest,
                       type_name << " data properties with file type "
                       << file_type << " and version " << table_version <<
                       " do not exist!" );
    }
  }
  else
  {
    THROW_EXCEPTION( InvalidScatteringCenterPropertiesRequest,
                     type_name << " data properties with file type "
                     << file_type << " do not exist!" );
  }
}

// Set the properties
template<typename Properties, typename PropertiesMap>
inline void ScatteringCenterPropertiesHelper::setProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const AtomType expected_atom,
                       const std::string& warning_tag,
                       const std::string& type_name )
{
  if( new_properties.get() )
  {
    TEST_FOR_EXCEPTION( new_properties->atom() != expected_atom,
                        InvalidScatteringCenterPropertiesData,
                        type_name << " data properties do not correspond to "
                        "this atom (" << new_properties->atom() << " != "
                        << expected_atom << ")!" );
    
    ScatteringCenterPropertiesHelper::setPropertiesImpl( properties,
                                                         new_properties,
                                                         warning_tag,
                                                         type_name );
  }
}

// Set the properties
template<typename Properties, typename PropertiesMap>
inline void ScatteringCenterPropertiesHelper::setPropertiesImpl(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const std::string& warning_tag,
                       const std::string& type_name )
{
  if( ScatteringCenterPropertiesHelper::dataAvailable(
                                               properties,
                                               new_properties->fileType(),
                                               new_properties->fileVersion()) )
  {
    FRENSIE_LOG_TAGGED_WARNING( warning_tag,
                                type_name << " data properties with file "
                                "type " << new_properties->fileType() <<
                                " and version "
                                << new_properties->fileVersion() <<
                                " are already present! The old properties "
                                "will be overwritten." );
  }
  
  properties[new_properties->fileType()][new_properties->fileVersion()] =
    new_properties;
}

// print properties
template<typename PropertiesMap>
void ScatteringCenterPropertiesHelper::printProperties(
                                               const PropertiesMap& properties,
                                               const std::string& type_name,
                                               std::ostream& os )
{
  std::string indent( "  " );
  
  os << indent << Utility::Underlined(type_name) << ":\n";

  indent += "  ";

  typename PropertiesMap::const_iterator file_type_it = properties.begin();

  while( file_type_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      file_type_it->second.begin();

    while( version_it != file_type_it->second.end() )
    {
      os << indent << file_type_it->first << " version " << version_it->first
         << " (" << Utility::Italicized(version_it->second->tableName()) << "): "
         << version_it->second->filePath().string() << "\n";
      
      ++version_it;
    }
    
    ++file_type_it;
  }
}
  
} // end Data namespace

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_HELPER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesHelper_def.hpp
//---------------------------------------------------------------------------//
