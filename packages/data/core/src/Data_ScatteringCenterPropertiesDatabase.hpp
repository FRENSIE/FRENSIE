//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabase.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties database declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_HPP

// Std Lib Includes
#include <string>
#include <memory>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_AtomProperties.hpp"
#include "Data_NuclideProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ArchivableObject.hpp"
#include "Utility_Map.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The scattering center properties database
class ScatteringCenterPropertiesDatabase : public Utility::ArchivableObject<ScatteringCenterPropertiesDatabase>
{

public:

  //! Default constructor
  ScatteringCenterPropertiesDatabase();

  //! Load existing database constructor
  ScatteringCenterPropertiesDatabase(
                         const boost::filesystem::path& database_name_with_path );

  //! Destructor
  ~ScatteringCenterPropertiesDatabase()
  { /* ... */ }

  // The database name used in an archive
  virtual const char* getArchiveName() const override;

  //! Check if the atom properties exist
  bool doPropertiesExist( const AtomType atom );
  
  //! Check if properties with zaid exist
  bool doPropertiesExist( const Data::ZAID zaid );

  //! Add atom properties to the database
  void addProperties( const AtomProperties& properties );

  //! Add nuclide properties to the database
  void addProperties( const NuclideProperties& properties );

  //! Return the desired properties
  const AtomProperties& getAtomProperties( const AtomType atom ) const;

  //! Return the desired properties
  AtomProperties& getAtomProperties( const AtomType atom );

  //! Return the desired properties
  const AtomProperties& getAtomProperties( const Data::ZAID zaid ) const;

  //! Return the desired properties
  AtomProperties& getAtomProperties( const Data::ZAID zaid );

  //! Return the desired properties
  const NuclideProperties& getNuclideProperties( const Data::ZAID zaid ) const;

  //! Return the desired properties
  NuclideProperties& getNuclideProperties( const Data::ZAID zaid );

  //! Return the number of stored properties
  size_t getNumberOfProperties() const;

  //! List the properties zaids
  void listPropertiesZaids( std::ostream& os = std::cout ) const;

  //! Log the properties zaids
  void logPropertiesZaids() const;

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
  typedef std::map<std::string,std::unique_ptr<ScatteringCenterProperties> > ScatteringCenterNamePropertiesMap;
  
   ScatteringCenterNamePropertiesMap d_properties;

  // The scattering center properties aliases
  typedef std::map<std::string,std::string> ScatteringCenterAliasNameMap;

  ScatteringCenterAliasNameMap d_aliases;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterPropertiesDatabase, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ScatteringCenterPropertiesDatabase, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesDatabase );

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabase.hpp
//---------------------------------------------------------------------------//
