//---------------------------------------------------------------------------//
//!
//! \file   Data_NativeEPRAdjointPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The Native EPR adjoint photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
NativeEPRAdjointPhotoatomicDataProperties::NativeEPRAdjointPhotoatomicDataProperties()
{ /* ... */ }

// Constructor
NativeEPRAdjointPhotoatomicDataProperties::NativeEPRAdjointPhotoatomicDataProperties(
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
NativeEPRAdjointPhotoatomicDataProperties::NativeEPRAdjointPhotoatomicDataProperties(
                       const NativeEPRAdjointPhotoatomicDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_version( other.d_file_version ),
    d_atom( other.d_atom )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType NativeEPRAdjointPhotoatomicDataProperties::atom() const
{
  return d_atom;
}

// Get the photoatomic data file type
auto NativeEPRAdjointPhotoatomicDataProperties::fileType() const -> FileType
{
  return AdjointPhotoatomicDataProperties::Native_EPR_FILE;
}

// Get the photoatomic data file type
auto NativeEPRAdjointPhotoatomicDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}

// Get the photoatomic data file path (relative to the data directory)
boost::filesystem::path NativeEPRAdjointPhotoatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the photoatomic data file start line
size_t NativeEPRAdjointPhotoatomicDataProperties::fileStartLine() const
{
  return 0;
}

// Get the photoatomic data file version
unsigned NativeEPRAdjointPhotoatomicDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the photoatomic table name
std::string NativeEPRAdjointPhotoatomicDataProperties::tableName() const
{
  return "";
}

// Clone the properties
NativeEPRAdjointPhotoatomicDataProperties* NativeEPRAdjointPhotoatomicDataProperties::clone() const
{
  return new NativeEPRAdjointPhotoatomicDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( NativeEPRAdjointPhotoatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( NativeEPRAdjointPhotoatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_NativeEPRAdjointPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
