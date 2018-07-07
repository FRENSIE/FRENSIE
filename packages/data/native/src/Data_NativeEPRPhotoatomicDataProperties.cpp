//---------------------------------------------------------------------------//
//!
//! \file   Data_NativeEPRPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The Native EPR photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
NativeEPRPhotoatomicDataProperties::NativeEPRPhotoatomicDataProperties()
{ /* ... */ }

// Constructor
NativeEPRPhotoatomicDataProperties::NativeEPRPhotoatomicDataProperties(
                                      const AtomicWeight atomic_weight,
                                      const boost::filesystem::path& file_path,
                                      const unsigned file_version,
                                      const AtomType atom )
  : d_atomic_weight( atomic_weight ),
    d_file_path( file_path ),
    d_file_version( file_version ),
    d_atom( atom )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0*Utility::Units::amu );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Copy constructor
NativeEPRPhotoatomicDataProperties::NativeEPRPhotoatomicDataProperties(
                                  const NativeEPRPhotoatomicDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_version( other.d_file_version ),
    d_atom( other.d_atom )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType NativeEPRPhotoatomicDataProperties::atom() const
{
  return d_atom;
}

// Get the photoatomic data file type
auto NativeEPRPhotoatomicDataProperties::fileType() const -> FileType
{
  return PhotoatomicDataProperties::Native_EPR_FILE;
}

// Get the atomic weight of the nuclide that the file specifies data for
auto NativeEPRPhotoatomicDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}

// Get the photoatomic data file path (relative to the data directory)
boost::filesystem::path NativeEPRPhotoatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the photoatomic data file start line
size_t NativeEPRPhotoatomicDataProperties::fileStartLine() const
{
  return 0;
}

// Get the photoatomic data file version
unsigned NativeEPRPhotoatomicDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the photoatomic table name
std::string NativeEPRPhotoatomicDataProperties::tableName() const
{
  return "";
}

// Clone the properties
NativeEPRPhotoatomicDataProperties* NativeEPRPhotoatomicDataProperties::clone() const
{
  return new NativeEPRPhotoatomicDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( NativeEPRPhotoatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( NativeEPRPhotoatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_NativeEPRPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
