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
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
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
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Initialize static member data
const std::string ScatteringCenterPropertiesCache::s_archive_name;

// Default constructor
ScatteringCenterPropertiesCache::ScatteringCenterPropertiesCache()
{ /* ... */ }

// Load existing cache constructor
ScatteringCenterPropertiesCache::ScatteringCenterPropertiesCache(
                          const boost::filesystem::path& cache_name_with_path )
{
  // Create the input archive
  std::unique_ptr<boost::archive::polymorphic_iarchive> cache_iarchive;

  this->createIArchive( cache_name_with_path, cache_iarchive );

  // Load the cache from the archive
  (*cache_iarchive) >> boost::serialization::make_nvp( this->getArchiveName().c_str(), *this );
}

// The cache name used in an archive
const std::string& ScatteringCenterPropertiesCache::getArchiveName()
{
  return s_archive_name;
}

// Add scattering center properties to the cache
void ScatteringCenterPropertiesCache::addProperties(
                                 const ScatteringCenterProperties& properties )
{
  d_properties[properties.name()].reset( properties.clone() );
}

// Remove scattering center properties from the cache
void ScatteringCenterPropertiesCache::removeProperties( const std::string& name )
{
  d_properties.erase( name );
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

// Clear dangling aliases
void ScatteringCenterPropertiesCache::clearDanglingAliases()
{
  ScatteringCenterAliasNameMap::iterator alias_it = d_aliases.begin();

  while( alias_it != d_aliases.end() )
  {
    // Check for a dangling alias
    if( d_properties.find( alias_it->second ) == d_properties.end() )
      alias_it = d_aliases.erase( alias_it );
    
    else
      ++alias_it;
  }
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

// Create an output archive
void ScatteringCenterPropertiesCache::createOArchive(
              const boost::filesystem::path& archive_name_with_path,
              std::unique_ptr<boost::archive::polymorphic_oarchive>& oarchive )
{
  // Verify that the parent directory exists
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( archive_name_with_path.parent_path() ),
                      std::runtime_error,
                      "Cannot create the output archive "
                      << archive_name_with_path.string() <<
                      " because the parent directory does not exist!" );

  // Get the file extension
  std::string extension = archive_name_with_path.extension().string();

  // Create the oarchive
  if( extension == "xml" || extension == "txt" )
  {
    // Create the oarchive file stream
    std::ofstream oarchive_stream( archive_name_with_path.string() );

    if( extension == "xml" )
    {
      oarchive.reset( new boost::archive::polymorphic_xml_oarchive( oarchive_stream ) );
    }
    else
    {
      oarchive.reset( new boost::archive::polymorphic_text_oarchive( oarchive_stream ) );
    }
  }
  else if( extension == "bin" )
  {
    // Create the oarchive file stream
    std::ofstream oarchive_stream( archive_name_with_path.string(),
                                   std::ofstream::binary );

    oarchive.reset( new boost::archive::polymorphic_binary_oarchive( oarchive_stream ) );
  }
  else if( extension == "h5fa" )
  {
    std::ostringstream oarchive_name( archive_name_with_path.string() );

    oarchive.reset( new Utility::PolymorphicHDF5OArchive( oarchive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE ) );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot create the output archive "
                     << archive_name_with_path.string() <<
                     " because the extension type is not supported!" );
  }
}

// Create an input archive
void ScatteringCenterPropertiesCache::createIArchive(
              const boost::filesystem::path& archive_name_with_path,
              std::unique_ptr<boost::archive::polymorphic_iarchive>& iarchive )
{
  // Verify that the archive exists
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( archive_name_with_path ),
                      std::runtime_error,
                      "Cannot create the input archive "
                      << archive_name_with_path.string() <<
                      " because the file does not exist!" );

  // Get the file extension
  std::string extension = archive_name_with_path.extension().string();

  // Create the oarchive
  if( extension == "xml" || extension == "txt" )
  {
    // Create the iarchive file stream
    std::ifstream iarchive_stream( archive_name_with_path.string() );

    if( extension == "xml" )
    {
      iarchive.reset( new boost::archive::polymorphic_xml_iarchive( iarchive_stream ) );
    }
    else
    {
      iarchive.reset( new boost::archive::polymorphic_text_iarchive( iarchive_stream ) );
    }
  }
  else if( extension == "bin" )
  {
    // Create the iarchive file stream
    std::ifstream iarchive_stream( archive_name_with_path.string(),
                                   std::ofstream::binary );

    iarchive.reset( new boost::archive::polymorphic_binary_iarchive( iarchive_stream ) );
  }
  else if( extension == "h5fa" )
  {
    std::istringstream iarchive_name( archive_name_with_path.string() );

    iarchive.reset( new Utility::PolymorphicHDF5IArchive( iarchive_name ) );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Cannot create the input archive "
                     << archive_name_with_path.string() <<
                     " because the extension type is not supported!" );
  }
}

// Export the cache
void ScatteringCenterPropertiesCache::save(
                    const boost::filesystem::path& cache_name_with_path ) const
{
  // Create the output archive
  std::unique_ptr<boost::archive::polymorphic_oarchive> cache_oarchive;

  this->createOArchive( cache_name_with_path, cache_oarchive );

  // Save the cache to the arhive
  (*cache_oarchive) << boost::serialization::make_nvp( s_archive_name.c_str(), *this );
}

// Import the cache
void ScatteringCenterPropertiesCache::load(
                          const boost::filesystem::path& cache_name_with_path )
{
  // Create the input archive
  std::unique_ptr<boost::archive::polymorphic_iarchive> cache_iarchive;

  this->createIArchive( cache_name_with_path, cache_iarchive );

  // Load the cache from the archive
  (*cache_iarchive) >> boost::serialization::make_nvp( this->getArchiveName().c_str(), *this );
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

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesCache.cpp
//---------------------------------------------------------------------------//
