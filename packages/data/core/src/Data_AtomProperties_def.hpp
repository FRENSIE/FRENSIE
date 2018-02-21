//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomProperties_def.hpp
//! \author Alex Robinson
//! \brief  The atom properties class template function definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ATOM_PROPERTIES_DEF_HPP
#define DATA_ATOM_PROPERTIES_DEF_HPP

namespace Data{

// Check if there is data available with the desired format
template<typename PropertiesMap>
inline bool AtomProperties::dataAvailable(
                             const PropertiesMap& properties,
                             const typename PropertiesMap::key_type file_type )
{
  return properties.find( file_type ) != properties.end();
}

// Check if there is data available with the desired format and table version
template<typename PropertiesMap>
inline bool AtomProperties::dataAvailable(
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
AtomProperties::getDataFileTypes( const PropertiesMap& properties )
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
inline std::set<unsigned> AtomProperties::getDataFileVersions(
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
unsigned AtomProperties::getMaxDataFileVersion(
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
    THROW_EXCEPTION( std::runtime_error,
                     type_name << " data properties with file type "
                     << file_type << " does not have a recommended version!" );
  }
}

// Get the properties
template<typename Properties, typename PropertiesMap>
inline const Properties& AtomProperties::getProperties(
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
      return *version_it->second;
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       type_name << " data properties with file type "
                       << file_type << " and version " << table_version <<
                       " do not exist!" );
    }
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     type_name << " data properties with file type "
                     << file_type << " do not exist!" );
  }
}

// Set the properties
template<typename Properties, typename PropertiesMap>
inline void AtomProperties::setProperties(
                      PropertiesMap& properties,
                      const std::shared_ptr<const Properties>& new_properties,
                      const std::string& type_name )
{
  if( new_properties.get() )
  {
    if( AtomProperties::dataAvailable( properties,
                                       new_properties->fileType(),
                                       new_properties->fileVersion()) )
    {
      FRENSIE_LOG_TAGGED_WARNING( "AtomProperties",
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
}

// Clone properties
template<typename PropertiesMap>
void AtomProperties::cloneProperties( const PropertiesMap& original_properties,
                                      PropertiesMap& new_properties )
{
  new_properties.clear();

  typename PropertiesMap::const_iterator properties_it =
    original_properties.begin();

  while( properties_it != original_properties.end() )
  {
    typename PropertiesMap::mapped_type& new_properties_map = 
      new_properties[properties_it->first];
    
    typename PropertiesMap::mapped_type::const_iterator version_it =
      properties_it->second.begin();

    while( version_it != properties_it->second.end() )
    {
      new_properties_map[version_it->first] =
        typename PropertiesMap::mapped_type::mapped_type(
                                                 version_it->second->clone() );
      
      ++version_it;
    }

    ++properties_it;
  }
}

// print properties
template<typename PropertiesMap>
void AtomProperties::printProperties( const PropertiesMap& properties,
                                      const std::string& type_name,
                                      std::ostream& os )
{
  std::string indent( "  " );
  
  os << indent << type_name << ":\n";

  indent += "  ";

  typename PropertiesMap::const_iterator file_type_it = properties.begin();

  while( file_type_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      file_type_it->second.begin();

    while( version_it != file_type_it->second.end() )
    {
      os << indent << file_type_it->first << " version " << version_it->first
         << " (" << version_it->second->tableName() << "): "
         << version_it->second->filePath().string() << "\n";
      
      ++version_it;
    }
    
    ++file_type_it;
  }
}

// Save the properties to an archive
template<typename Archive>
void AtomProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}

// Load the properties from an archive
template<typename Archive>
void AtomProperties::load( Archive& ar, const unsigned version )
{
  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photoatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_electroatomic_data_properties );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electroatomic_data_properties );
}
  
} // end Data namespace

#endif // end DATA_ATOM_PROPERTIES_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_AtomProperties_def.hpp
//---------------------------------------------------------------------------//
