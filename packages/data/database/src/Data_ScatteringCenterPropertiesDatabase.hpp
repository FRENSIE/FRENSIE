//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabase.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties database linker helper decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_HPP

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabaseImpl.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Data_ENDLPhotoatomicDataProperties.hpp"
#include "Data_ENDLElectroatomicDataProperties.hpp"
#include "Utility_ArchivableObject.hpp"

namespace Data{

//! The scattering center properties database
class ScatteringCenterPropertiesDatabase : public ScatteringCenterPropertiesDatabaseImpl,
                                           public Utility::ArchivableObject<ScatteringCenterPropertiesDatabase>
{
  // The base archivable object type
  typedef Utility::ArchivableObject<ScatteringCenterPropertiesDatabase> BaseArchivableObjectType;

public:

  //! Default constructor
  ScatteringCenterPropertiesDatabase();

  //! Load existing database constructor
  ScatteringCenterPropertiesDatabase(
                      const boost::filesystem::path& database_name_with_path );

  //! Destructor
  ~ScatteringCenterPropertiesDatabase()
  { /* ... */ }

  //! The database name used in an archive
  virtual const char* getArchiveName() const override;

protected:

  //! Load the archived object (implementation)
  void loadFromFileImpl( const boost::filesystem::path& archive_name_with_path ) final override;

  //! Archive the object (implementation)
  void saveToFileImpl( const boost::filesystem::path& archive_name_with_path,
                       const bool overwrite ) const final override;

private:

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
};

// Save the model to an archive
template<typename Archive>
void ScatteringCenterPropertiesDatabase::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ScatteringCenterPropertiesDatabaseImpl );
}

// Load the model from an archive
template<typename Archive>
void ScatteringCenterPropertiesDatabase::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ScatteringCenterPropertiesDatabaseImpl );
}

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterPropertiesDatabase, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ScatteringCenterPropertiesDatabase, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ScatteringCenterPropertiesDatabase );

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabase.hpp
//---------------------------------------------------------------------------//
