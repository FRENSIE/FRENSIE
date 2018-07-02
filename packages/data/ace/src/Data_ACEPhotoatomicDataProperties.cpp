//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
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

// Save the properties to an archive
template<typename Archive>
void ACEPhotoatomicDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PhotoatomicDataProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );
  
  std::string raw_path = d_file_path.string();
  
  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

// Load the properties from an archive
template<typename Archive>
void ACEPhotoatomicDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PhotoatomicDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );
  
  std::string raw_path;  
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();
  
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACEPhotoatomicDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACEPhotoatomicDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACEPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
