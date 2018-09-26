//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringenterProperties.cpp
//! \author Alex Robinson
//! \brief  The scattering center properties database linker helper definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"

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

// Load the archived object (implementation)
void ScatteringCenterPropertiesDatabase::loadFromFileImpl( const boost::filesystem::path& archive_name_with_path )
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpis pointer must be NULL. Depending on the libraries that have been
  // loaded (e.g. utility_grid) the bpis might be initialized to a non-NULL
  // value
  const boost::archive::detail::basic_pointer_iserializer* vector_double_bpis =
    this->resetBpisPointer<std::vector<double> >( extension );

  const boost::archive::detail::basic_pointer_iserializer* zaid_bpis =
    this->resetBpisPointer<Data::ZAID>( extension );
  
  // Import the data in the archive
  BaseArchivableObjectType::loadFromFileImpl( archive_name_with_path );

  // The bpis pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBpisPointer<std::vector<double> >( extension, vector_double_bpis );
  this->restoreBpisPointer<Data::ZAID>( extension, zaid_bpis );
}

// Archive the object (implementation)
void ScatteringCenterPropertiesDatabase::saveToFileImpl( const boost::filesystem::path& archive_name_with_path,
                                                         const bool overwrite ) const
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpos pointer must be NULL. Depending on the libraries that have been
  // loaded (e.g. utility_grid) the bpos might be initialized to a non-NULL
  // value
  const boost::archive::detail::basic_pointer_oserializer* vector_double_bpos =
    this->resetBposPointer<std::vector<double> >( extension );

  const boost::archive::detail::basic_pointer_oserializer* zaid_bpos =
    this->resetBposPointer<Data::ZAID>( extension );
  
  // Import the data in the archive
  BaseArchivableObjectType::saveToFileImpl( archive_name_with_path, overwrite );

  // The bpos pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBposPointer<std::vector<double> >( extension, vector_double_bpos );
  this->restoreBposPointer<Data::ZAID>( extension, zaid_bpos );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesDatabase );

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
