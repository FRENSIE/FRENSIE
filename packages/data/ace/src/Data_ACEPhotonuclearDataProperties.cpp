//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEPhotonuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE photonuclear data properties class definition
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
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
ACEPhotonuclearDataProperties::ACEPhotonuclearDataProperties()
{ /* ... */ }

// Constructor
ACEPhotonuclearDataProperties::ACEPhotonuclearDataProperties(
                                      const double atomic_weight,
                                      const boost::filesystem::path& file_path,
                                      const size_t file_start_line,
                                      const std::string& file_table_name )
  : d_zaid(),
    d_atomic_weight( atomic_weight ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_version( 0 ),
    d_file_table_name( file_table_name )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );
  // Make sure that the table name is valid
  testPrecondition( !file_table_name.empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();

  // Extract the raw zaid and file version from the table name
  std::vector<std::string> table_name_components;

  boost::split( table_name_components,
                file_table_name,
                boost::is_any_of( "." ) );

  TEST_FOR_EXCEPTION( table_name_components.size() != 2,
                      std::runtime_error,
                      "The table name must have a format of \"zaid.##u\"!" );

  d_zaid = Data::ZAID( Utility::fromString<unsigned>( table_name_components.front() ) );

  TEST_FOR_EXCEPTION( table_name_components.back().find( "u" ) >
                      table_name_components.back().size(),
                      std::runtime_error,
                      "The table name does not correspond to a photonuclear "
                      "table!" );

  boost::algorithm::erase_all( table_name_components.back(), "u" );

  d_file_version = Utility::fromString<size_t>( table_name_components.back() );
}

// Copy constructor
ACEPhotonuclearDataProperties::ACEPhotonuclearDataProperties(
                                   const ACEPhotonuclearDataProperties& other )
  : d_zaid( other.d_zaid ),
    d_atomic_weight( other.d_atomic_weight ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_version( other.d_file_version ),
    d_file_table_name( other.d_file_table_name )
{
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType ACEPhotonuclearDataProperties::atom() const 
{
  return d_zaid.atom();
}

// Get the atomic mass number that the file specifies data for
unsigned ACEPhotonuclearDataProperties::atomicMassNumber() const 
{
  return d_zaid.atomicMassNumber();
}

// Get the isomer number that the file specifies data for
unsigned ACEPhotonuclearDataProperties::isomerNumber() const 
{
  return d_zaid.isomerNumber();
}

// Get the atomic weight of the nuclide that the file specifies data for
double ACEPhotonuclearDataProperties::atomicWeight() const 
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
size_t ACEPhotonuclearDataProperties::fileVersion() const 
{
  return d_file_version;
}

// Get the nuclear data file table name
std::string ACEPhotonuclearDataProperties::tableName() const 
{
  return d_file_table_name;
}

// Clone the properties
ACEPhotonuclearDataProperties* ACEPhotonuclearDataProperties::clone() const 
{
  return new ACEPhotonuclearDataProperties( *this );
}

// Save the properties to an archive
template<typename Archive>
void ACEPhotonuclearDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PhotonuclearDataProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );

  std::string raw_path = d_file_path.string();
  
  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

// Load the properties from an archive
template<typename Archive>
void ACEPhotonuclearDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PhotonuclearDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_zaid );
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );

  std::string raw_path;  
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();
  
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACEPhotonuclearDataProperties );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACEPhotonuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACEPhotonuclearDataProperties.cpp
//---------------------------------------------------------------------------//
