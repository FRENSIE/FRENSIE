//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabase.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties database linker helper decl.
//!
//---------------------------------------------------------------------------//

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

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterPropertiesDatabase, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ScatteringCenterPropertiesDatabase, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesDatabase );

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabase.hpp
//---------------------------------------------------------------------------//
