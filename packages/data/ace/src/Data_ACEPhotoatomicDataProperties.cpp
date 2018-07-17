//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default destructor
ACEPhotoatomicDataProperties::ACEPhotoatomicDataProperties()
{ /* ... */ }

// Constructor
ACEPhotoatomicDataProperties::ACEPhotoatomicDataProperties(
                                      const AtomicWeight atomic_weight,
                                      const boost::filesystem::path& file_path,
                                      const size_t file_start_line,
                                      const ACETableName& file_table_name )
  : d_atomic_weight( atomic_weight ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_table_name( file_table_name )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0*Utility::Units::amu );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();

  TEST_FOR_EXCEPTION( d_file_table_name.typeKey() != 'p',
                      std::runtime_error,
                      "The photoatomic data table type is not supported!" );
}

// Copy constructor
ACEPhotoatomicDataProperties::ACEPhotoatomicDataProperties(
                                 const ACEPhotoatomicDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_table_name( other.d_file_table_name )
{ 
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType ACEPhotoatomicDataProperties::atom() const
{
  return d_file_table_name.zaid().atom();
}

// Get the photoatomic data file type
auto ACEPhotoatomicDataProperties::fileType() const -> FileType
{
  if( d_file_table_name.version() < 12 )
    return PhotoatomicDataProperties::ACE_FILE;
  else
    return PhotoatomicDataProperties::ACE_EPR_FILE;
}

// Get the atomic weight of the nuclide that the file specifies data for
auto ACEPhotoatomicDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}

// Get the photoatomic data file path (relative to the data directory)
boost::filesystem::path ACEPhotoatomicDataProperties::filePath() const
{
  return d_file_path;
}

// Get the photoatomic data file start line
size_t ACEPhotoatomicDataProperties::fileStartLine() const
{
  return d_file_start_line;
}

// Get the photoatomic data file version
unsigned ACEPhotoatomicDataProperties::fileVersion() const
{
  return d_file_table_name.version();
}

// Get the photoatomic table name
std::string ACEPhotoatomicDataProperties::tableName() const
{
  return d_file_table_name.toRaw();
}

// Clone the properties
ACEPhotoatomicDataProperties* ACEPhotoatomicDataProperties::clone() const
{
  return new ACEPhotoatomicDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ACEPhotoatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACEPhotoatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACEPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
