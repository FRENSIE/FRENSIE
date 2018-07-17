//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEThermalNuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE thermal nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACETableName.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
ACEThermalNuclearDataProperties::ACEThermalNuclearDataProperties()
{ /* ... */ }

// Constructor
ACEThermalNuclearDataProperties::ACEThermalNuclearDataProperties(
                               const std::set<Data::ZAID>& zaids,
                               const Energy evaluation_temp,
                               const boost::filesystem::path& file_path,
                               const size_t file_start_line,
                               const std::string& file_table_name )
  : d_zaids( zaids ),
    d_evaluation_temp( evaluation_temp ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_table_name( file_table_name ),
    d_name(),
    d_file_version()
{
  // Make sure that there is at least one zaid specified
  testPrecondition( !zaids.empty() );
  // Make sure that the evaluation temp is valid
  testPrecondition( evaluation_temp >= 0.0*Utility::Units::MeV );
  // Make sure that the file path is valid
  testPrecondition( !file_path.string().empty() );

  // Convert to the preferred path format
  d_file_path.make_preferred();

  // Extract the table name components
  char table_type_key;

  ACETableName::splitTableNameIntoComponents( file_table_name,
                                              d_name,
                                              d_file_version,
                                              table_type_key );
  TEST_FOR_EXCEPTION( table_type_key != 't',
                      std::runtime_error,
                      "The thermal nuclear data table type is not supported!" );
}

// Copy constructor
ACEThermalNuclearDataProperties::ACEThermalNuclearDataProperties(
                                 const ACEThermalNuclearDataProperties& other )
  : d_zaids( other.d_zaids ),
    d_evaluation_temp( other.d_evaluation_temp ),
    d_file_path( other.d_file_path ),
    d_file_start_line( other.d_file_start_line ),
    d_file_table_name( other.d_file_table_name ),
    d_name( other.d_name ),
    d_file_version( other.d_file_version )
{ /* ... */ }

// Get the name of the properties
std::string ACEThermalNuclearDataProperties::name() const
{
  return d_name;
}

// Check if the file specifies data for the ZAID of interest
bool ACEThermalNuclearDataProperties::hasDataForZAID( const Data::ZAID& zaid ) const
{
  return d_zaids.find( zaid ) != d_zaids.end();
}

// Get the ZAIDS that the file specifies data for
std::set<Data::ZAID> ACEThermalNuclearDataProperties::zaids() const
{
  return d_zaids;
}

// Get the nuclear data evaluation temperature (MeV)
auto ACEThermalNuclearDataProperties::evaluationTemperatureInMeV() const -> Energy
{
  return d_evaluation_temp;
}

// Get the nuclear data file type
auto ACEThermalNuclearDataProperties::fileType() const -> FileType
{
  if( d_file_version < 20 || (d_file_version < 70 && d_file_version >= 60 ) )
    return STANDARD_ACE_FILE;
  else
    return MCNP6_ACE_FILE;
}

// Get the nuclear data file path (relative to the data directory)
boost::filesystem::path ACEThermalNuclearDataProperties::filePath() const
{
  return d_file_path;
}

// Get the nuclear data file start line
size_t ACEThermalNuclearDataProperties::fileStartLine() const
{
  return d_file_start_line;
}

// Get the nuclear data file major version
unsigned ACEThermalNuclearDataProperties::fileMajorVersion() const
{
  return this->fileVersion()/10;
}


// Get the nuclear data file version
unsigned ACEThermalNuclearDataProperties::fileVersion() const
{
  return d_file_version;
}

// Get the nuclear data file table name
std::string ACEThermalNuclearDataProperties::tableName() const
{
  return d_file_table_name;
}

// Clone the properties
ACEThermalNuclearDataProperties* ACEThermalNuclearDataProperties::clone() const
{
  return new ACEThermalNuclearDataProperties( *this );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ACEThermalNuclearDataProperties );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACEThermalNuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACEThermalNuclearDataProperties.cpp
//---------------------------------------------------------------------------//
