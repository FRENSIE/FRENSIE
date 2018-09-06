//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ENDL photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Data_ENDLPhotoatomicDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
ENDLPhotoatomicDataProperties::ENDLPhotoatomicDataProperties()
{ /* ... */ }

// Constructor
ENDLPhotoatomicDataProperties::ENDLPhotoatomicDataProperties(
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
ENDLPhotoatomicDataProperties::ENDLPhotoatomicDataProperties(
                                  const ENDLPhotoatomicDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_version( other.d_file_version ),
    d_atom( other.d_atom )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType ENDLPhotoatomicDataProperties::atom() const
{
  return d_atom;
}

// Get the photoatomic data file type
auto ENDLPhotoatomicDataProperties::fileType() const -> FileType
{
  return PhotoatomicDataProperties::Native_ENDL_FILE;
}

// Get the atomic weight of the nuclide that the file specifies data for
auto ENDLPhotoatomicDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}


// Get the photoatomic data file path (relative to the data directory)
boost::filesystem::path ENDLPhotoatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the photoatomic data file start line
size_t ENDLPhotoatomicDataProperties::fileStartLine() const
{
  return 0;
}

// Get the photoatomic data file version
unsigned ENDLPhotoatomicDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the photoatomic table name
std::string ENDLPhotoatomicDataProperties::tableName() const
{
  return "";
}

// Clone the properties
ENDLPhotoatomicDataProperties* ENDLPhotoatomicDataProperties::clone() const
{
  return new ENDLPhotoatomicDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ENDLPhotoatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ENDLPhotoatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ENDLPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
