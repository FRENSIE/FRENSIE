//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringenterProperties.cpp
//! \author Alex Robinson
//! \brief  The scattering center properties database linker helper definition
//!
//---------------------------------------------------------------------------//

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
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"

namespace Data{

// Initialize static member data
const std::string ScatteringCenterPropertiesDatabase::s_archive_name( "database" );

// Default constructor
ScatteringCenterPropertiesDatabase::ScatteringCenterPropertiesDatabase()
{ /* ... */ }

// Load existing database constructor
ScatteringCenterPropertiesDatabase::ScatteringCenterPropertiesDatabase(
                       const boost::filesystem::path& database_name_with_path )
{
  this->loadFromFile( database_name_with_path );
}

// The database name used in an archive
const char* ScatteringCenterPropertiesDatabase::getArchiveName() const
{
  return s_archive_name.c_str();
}

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

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesDatabase );

//! Make sure that the other data libraries get pulled in
bool initializeDataLibraries()
{
  // Pull in the data_ace library
  {
    ACEPhotoatomicDataProperties obj( 1.0*Utility::Units::amu,
                                      boost::filesystem::current_path(),
                                      1,
                                      "1000.12p" );
  }

  // Pull in the data_endl library
  {
    ENDLPhotoatomicDataProperties obj( 1.0*Utility::Units::amu,
                                       boost::filesystem::current_path(),
                                       0,
                                       Data::H_ATOM );
  }

  // Pull in the data_native library
  {
    NativeEPRPhotoatomicDataProperties obj( 1.0*Utility::Units::amu,
                                            boost::filesystem::current_path(),
                                            0,
                                            Data::H_ATOM );
  }

  return true;
}

static bool __data_libraries_initialized__ = initializeDataLibraries();
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ScatteringCenterPropertiesDatabase, Data );

//---------------------------------------------------------------------------//
// end Data_ScatteringenterProperties.cpp
//---------------------------------------------------------------------------//
