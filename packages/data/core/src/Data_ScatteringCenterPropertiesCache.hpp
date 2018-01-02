//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesCache.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties cache declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_CACHE_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_CACHE_HPP

// Std Lib Includes
#include <string>
#include <memory>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_ScatteringCenterProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ArchivableObject.hpp"
#include "Utility_Map.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The scattering center properties cache
class ScatteringCenterPropertiesCache : public Utility::ArchivableObject<ScatteringCenterPropertiesCache>
{

public:

  //! Default constructor
  ScatteringCenterPropertiesCache();

  //! Load existing cache constructor
  ScatteringCenterPropertiesCache(
                         const boost::filesystem::path& cache_name_with_path );

  //! Destructor
  ~ScatteringCenterPropertiesCache()
  { /* ... */ }

  // The cache name used in an archive
  virtual const char* getArchiveName() const override;

  //! Add scattering center properties to the cache
  void addProperties( const ScatteringCenterProperties& properties );

  //! Remove scattering center properties from the cache
  void removeProperties( const std::string& name );

  //! Check if properties with the name or alias of interest exist
  bool doPropertiesExist( const std::string& name_or_alias ) const;

  //! Return the desired properties
  const ScatteringCenterProperties& getProperties(
                                      const std::string& name_or_alias ) const;

  //! Return the number of stored properties
  size_t getNumberOfProperties() const;

  //! List the properties names
  void listPropertiesNames( std::ostream& os = std::cout ) const;

  //! Add a scattering center properties alias
  void addPropertiesAlias( const std::string& alias,
                           const std::string& properties_name );

  //! Remove a scattering center properties alias
  void removePropertiesAlias( const std::string& alias );

  //! Check if an alias exists
  bool doesAliasExist( const std::string& alias ) const;

  //! Return the number of aliases
  size_t getNumberOfAliases() const;

  //! List the aliases
  void listAliases( std::ostream& os = std::cout ) const;

  //! Clear the cache
  void clear();

private:

  // Create an input archive
  static void createIArchive(
             const boost::filesystem::path& archive_name_with_path,
             std::unique_ptr<std::istream>& iarchive_stream,
             std::unique_ptr<boost::archive::polymorphic_iarchive>& iarchive );

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The name used in archive name-value pairs
  static const std::string s_archive_name;

  // The scattering center properties
  typedef std::map<std::string,std::unique_ptr<const ScatteringCenterProperties> > ScatteringCenterNamePropertiesMap;
  
   ScatteringCenterNamePropertiesMap d_properties;

  // The scattering center properties aliases
  typedef std::map<std::string,std::string> ScatteringCenterAliasNameMap;

  ScatteringCenterAliasNameMap d_aliases;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterPropertiesCache, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ScatteringCenterPropertiesCache, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesCache );

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_CACHE_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesCache.hpp
//---------------------------------------------------------------------------//
