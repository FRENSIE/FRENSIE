//---------------------------------------------------------------------------//
//!
//! \file   Data_ACENuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE nuclear data properties class definition
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
#include "Data_ACENuclearDataProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_FromStringTraits.hpp"

namespace Data{

// Default constructor
ACENuclearDataProperties::ACENuclearDataProperties()
{ /* ... */ }

// Default constructor
ACENuclearDataProperties::ACENuclearDataProperties(
                                      const double evaluation_temp_in_mev,
                                      const boost::filesystem::path& file_path,
                                      const size_t file_start_line,
                                      const std::string& file_table_name )
  : d_evaluation_temp( evaluation_temp_in_mev ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_version( 0 ),
    d_file_table_name( file_table_name )
{
  // Make sure that the evaulation temp is valid
  testPrecondition( evaluation_temp_in_mev > 0.0 );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );
  // Make sure that the table name is valid
  testPrecondition( !file_table_name.empty() );

  // Extract the file version from the table name
  std::vector<std::string> table_name_components;

  boost::split( table_name_components,
                file_table_name,
                boost::is_any_of( "." ) );

  TEST_FOR_EXCEPTION( table_name_components.size() != 2,
                      std::runtime_error,
                      "The table name must have a format of \"name.##c\"!" );

  TEST_FOR_EXCEPTION( table_name_components.back().find( "c" ) >
                      table_name_components.back().size(),
                      std::runtime_error,
                      "The table name does not correspond to a continuous "
                      "energy neutron table!" );

  boost::algorithm::erase_all( table_name_components.back(), "c" );

  d_file_version = Utility::fromString<size_t>( table_name_components.back() );
}

// Copy constructor
ACENuclearDataProperties::ACENuclearDataProperties(
                                        const ACENuclearDataProperties& other )
  : d_evaluation_temp( other.d_evaluation_temp ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_table_name( other.d_file_table_name ),
    d_file_version( other.d_file_version )
{ /* ... */ }

// Get the nuclear data evaluation temperature (MeV)
double ACENuclearDataProperties::evaluationTemperatureInMeV() const
{
  return d_evaluation_temp;
}

// Get the nuclear data file type
auto ACENuclearDataProperties::fileType() const -> FileType
{
  return NuclearDataProperties::ACE_FILE;
}

// Get the nuclear data file path (relative to the data directory)
boost::filesystem::path ACENuclearDataProperties::filePath() const
{
  return d_file_path;
}

// Get the nuclear data file start line
size_t ACENuclearDataProperties::fileStartLine() const
{
  return d_file_start_line;
}

//! Get the nuclear data file version
size_t ACENuclearDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the nuclear data file table name
std::string ACENuclearDataProperties::tableName() const
{
  return d_file_table_name;
}

// Clone the properties
ACENuclearDataProperties* ACENuclearDataProperties::clone() const
{
  return new ACENuclearDataProperties( *this );
}

// Save the properties to an archive
template<typename Archive>
void ACENuclearDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( NuclearDataProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path = d_file_path.string();
  
  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

// Load the properties from an archive
template<typename Archive>
void ACENuclearDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( NuclearDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path;
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();
  
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACENuclearDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACENuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACENuclearDataProperties.cpp
//---------------------------------------------------------------------------//
