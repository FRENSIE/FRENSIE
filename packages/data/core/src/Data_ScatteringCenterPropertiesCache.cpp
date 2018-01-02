//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesCache.cpp
//! \author Alex Robinson
//! \brief  The scattering center properties cache definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <fstream>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesCache.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_PolymorphicHDF5OArchive.hpp"
#include "Utility_PolymorphicHDF5IArchive.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Initialize static member data
const std::string ScatteringCenterPropertiesCache::s_archive_name( "cache" );

// Default constructor
ScatteringCenterPropertiesCache::ScatteringCenterPropertiesCache()
{ /* ... */ }

// Load existing cache constructor
ScatteringCenterPropertiesCache::ScatteringCenterPropertiesCache(
                          const boost::filesystem::path& cache_name_with_path )
{
  this->loadFromFile( cache_name_with_path );
}

// The cache name used in an archive
const char* ScatteringCenterPropertiesCache::getArchiveName() const
{
  return s_archive_name.c_str();
}

// Add scattering center properties to the cache
void ScatteringCenterPropertiesCache::addProperties(
                                 const ScatteringCenterProperties& properties )
{
  if( d_properties.find( properties.name() ) != d_properties.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterPropertiesCache",
                                "Properties with name \""
                                << properties.name() << "\" already exist! "
                                "The existing properties will be "
                                "overwritten." )
  }

  if( d_aliases.find( properties.name() ) != d_aliases.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterPropertiesCache",
                                "An alias with the name of the new properties "
                                "(" << properties.name() << ") already exists!"
                                " The alias will be removed." );
    
    d_aliases.erase( properties.name() );
  }
  
  d_properties[properties.name()].reset( properties.clone() );
}

// Remove scattering center properties from the cache
void ScatteringCenterPropertiesCache::removeProperties( const std::string& name )
{
  if( d_properties.find( name ) != d_properties.end() )
  {
    d_properties.erase( name );

    // Check if any aliases were made for these properties and remove them
    ScatteringCenterAliasNameMap::iterator alias_it = d_aliases.begin();

    while( alias_it != d_aliases.end() )
    {
      if( alias_it->second == name )
        alias_it = d_aliases.erase( alias_it );
      else
        ++alias_it;
    }
  }
}

// Check if properties with the name of interest exist
bool ScatteringCenterPropertiesCache::doPropertiesExist( const std::string& name_or_alias ) const
{
  if( d_properties.find( name_or_alias ) != d_properties.end() )
    return true;
  else
  {
    ScatteringCenterAliasNameMap::const_iterator alias_it =
      d_aliases.find( name_or_alias );
    
    if( alias_it != d_aliases.end() )
      return this->doPropertiesExist( alias_it->second );
    else
      return false;
  }
}

// Return the desired properties
const ScatteringCenterProperties&
ScatteringCenterPropertiesCache::getProperties(
                                       const std::string& name_or_alias ) const
{
  ScatteringCenterNamePropertiesMap::const_iterator properties_it = 
    d_properties.find( name_or_alias );
  
  if( properties_it != d_properties.end() )
    return *properties_it->second;
  else
  {
    ScatteringCenterAliasNameMap::const_iterator alias_it =
      d_aliases.find( name_or_alias );
    
    if( alias_it != d_aliases.end() )
      return this->getProperties( alias_it->second );
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "There are no scattering center properties associated "
                       "with \"" << name_or_alias << "\" in the cache!" );
    }
  }
}

// Return the number of stored properties
size_t ScatteringCenterPropertiesCache::getNumberOfProperties() const
{
  return d_properties.size();
}

// List the properties names
void ScatteringCenterPropertiesCache::listPropertiesNames(
                                                       std::ostream& os ) const
{
  os << "Scattering Centers: \n";
  
  ScatteringCenterNamePropertiesMap::const_iterator properties_it =
    d_properties.begin();

  while( properties_it != d_properties.end() )
  {
    os << "  " << properties_it->first << "\n";

    ++properties_it;
  }

  os.flush();
}

// Add a scattering center properties alias
void ScatteringCenterPropertiesCache::addPropertiesAlias(
                                           const std::string& alias,
                                           const std::string& properties_name )
{
  TEST_FOR_EXCEPTION( d_properties.find( alias ) != d_properties.end(),
                      std::runtime_error,
                      "Cannot add alias " << alias << " to the cache because "
                      "a scattering center with that name already exists!" );

  TEST_FOR_EXCEPTION( alias == properties_name,
                      std::runtime_error,
                      "The alias must be different from the properties "
                      "name!" );

  TEST_FOR_EXCEPTION( d_properties.find( properties_name ) == d_properties.end(),
                      std::runtime_error,
                      "Cannot add alias " << alias << " to the cache because "
                      "the scattering center name " << properties_name <<
                      " does not exist!" );

  d_aliases[alias] = properties_name;
}

// Remove a scattering center properties alias
void ScatteringCenterPropertiesCache::removePropertiesAlias( const std::string& alias )
{
  d_aliases.erase( alias );
}

// Check if an alias exists
bool ScatteringCenterPropertiesCache::doesAliasExist( const std::string& alias ) const
{
  return d_aliases.find( alias ) != d_aliases.end();
}

// Return the number of aliases
size_t ScatteringCenterPropertiesCache::getNumberOfAliases() const
{
  return d_aliases.size();
}

// List the aliases
void ScatteringCenterPropertiesCache::listAliases( std::ostream& os ) const
{
  os << "Scattering Center Aliases: \n";

  ScatteringCenterAliasNameMap::const_iterator alias_it =
    d_aliases.begin();

  while( alias_it != d_aliases.end() )
  {
    os << "  " << alias_it->first << " -> " << alias_it->second << "\n";

    ++alias_it;
  }

  os.flush();
}

// Clear the cache
void ScatteringCenterPropertiesCache::clear()
{
  d_properties.clear();
  d_aliases.clear();
}

// Save the model to an archive
template<typename Archive>
void ScatteringCenterPropertiesCache::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_properties );
  ar & BOOST_SERIALIZATION_NVP( d_aliases );
}

// Load the model from an archive
template<typename Archive>
void ScatteringCenterPropertiesCache::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_properties );
  ar & BOOST_SERIALIZATION_NVP( d_aliases );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesCache );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ScatteringCenterPropertiesCache, Data );

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesCache.cpp
//---------------------------------------------------------------------------//
