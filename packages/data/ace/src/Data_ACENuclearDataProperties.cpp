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

// FRENSIE Includes
#include "Data_ACENuclearDataProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
ACENuclearDataProperties::ACENuclearDataProperties()
{ /* ... */ }

// Default constructor
ACENuclearDataProperties::ACENuclearDataProperties(
                                      const double atomic_weight_ratio,
                                      const double evaluation_temp_in_mev,
                                      const boost::filesystem::path& file_path,
                                      const size_t file_start_line,
                                      const ACETableName& file_table_name )
  : d_atomic_weight_ratio( atomic_weight_ratio ),
    d_evaluation_temp( evaluation_temp_in_mev ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_table_name( file_table_name )
{
  // Make sure that the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio >= 0.0 );
  // Make sure that the evaulation temp is valid
  testPrecondition( evaluation_temp_in_mev >= 0.0 );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();

  TEST_FOR_EXCEPTION( d_file_table_name.typeKey() != 'c',
                      std::runtime_error,
                      "The nuclear data table type is not supported!" );
}

// Copy constructor
ACENuclearDataProperties::ACENuclearDataProperties(
                                        const ACENuclearDataProperties& other )
  : d_atomic_weight_ratio( other.d_atomic_weight_ratio ),
    d_evaluation_temp( other.d_evaluation_temp ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_table_name( other.d_file_table_name )
{ 
  // Convert to the preferred path format
  d_file_path.make_preferred();
}

// Get the atom that the file specifies data for
AtomType ACENuclearDataProperties::atom() const
{
  return d_file_table_name.zaid().atom();
}

// Get the atomic mass number that the file specifies data for
unsigned ACENuclearDataProperties::atomicMassNumber() const
{
  return d_file_table_name.zaid().atomicMassNumber();
}

// Get the isomer number that the file specifies data for
unsigned ACENuclearDataProperties::isomerNumber() const
{
  return d_file_table_name.zaid().isomerNumber();
}

// Get the atomic weight ratio of the nuclide that the file specifies data for
double ACENuclearDataProperties::atomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

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
  return d_file_table_name.version();
}

// Get the nuclear data file table name
std::string ACENuclearDataProperties::tableName() const
{
  return d_file_table_name.toRaw();
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
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path = d_file_path.string();
  
  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

// Load the properties from an archive
template<typename Archive>
void ACENuclearDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( NuclearDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_evaluation_temp );

  std::string raw_path;
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();
  
  ar & BOOST_SERIALIZATION_NVP( d_file_start_line );
  ar & BOOST_SERIALIZATION_NVP( d_file_table_name );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACENuclearDataProperties );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACENuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACENuclearDataProperties.cpp
//---------------------------------------------------------------------------//
