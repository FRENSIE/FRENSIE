//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEPhotonuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE photonuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
ACEPhotonuclearDataProperties::ACEPhotonuclearDataProperties()
{ /* ... */ }

// Constructor
ACEPhotonuclearDataProperties::ACEPhotonuclearDataProperties(
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

  TEST_FOR_EXCEPTION( d_file_table_name.typeKey() != 'u',
                      std::runtime_error,
                      "The photonuclear data table type is not supported!" );
}

// Copy constructor
ACEPhotonuclearDataProperties::ACEPhotonuclearDataProperties(
                                   const ACEPhotonuclearDataProperties& other )
  : d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_table_name( other.d_file_table_name )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the ZAID that the file specifies data for
Data::ZAID ACEPhotonuclearDataProperties::zaid() const
{
  return d_file_table_name.zaid();
}

// Get the atomic weight of the nuclide that the file specifies data for
auto ACEPhotonuclearDataProperties::atomicWeight() const -> AtomicWeight
{
  return d_atomic_weight;
}

// Get the nuclear data file type
auto ACEPhotonuclearDataProperties::fileType() const -> FileType
{
  return PhotonuclearDataProperties::ACE_FILE;
}

// Get the nuclear data file path (relative to the data directory)
boost::filesystem::path ACEPhotonuclearDataProperties::filePath() const 
{
  return d_file_path;
}

// Get the nuclear data file start line
size_t ACEPhotonuclearDataProperties::fileStartLine() const 
{
  return d_file_start_line;
}

// Get the nuclear data file version
unsigned ACEPhotonuclearDataProperties::fileVersion() const 
{
  return d_file_table_name.version();
}

// Get the nuclear data file table name
std::string ACEPhotonuclearDataProperties::tableName() const 
{
  return d_file_table_name.toRaw();
}

// Clone the properties
ACEPhotonuclearDataProperties* ACEPhotonuclearDataProperties::clone() const 
{
  return new ACEPhotonuclearDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ACEPhotonuclearDataProperties );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACEPhotonuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACEPhotonuclearDataProperties.cpp
//---------------------------------------------------------------------------//
