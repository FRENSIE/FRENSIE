//---------------------------------------------------------------------------//
//!
//! \file   Data_ACENuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The ACE nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "Data_ACENuclearDataProperties.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Default constructor
ACENuclearDataProperties::ACENuclearDataProperties()
{ /* ... */ }

// Default constructor
ACENuclearDataProperties::ACENuclearDataProperties(
                                      const double atomic_weight_ratio,
                                      const Energy evaluation_temp,
                                      const boost::filesystem::path& file_path,
                                      const size_t file_start_line,
                                      const ACETableName& file_table_name )
  : d_atomic_weight_ratio( atomic_weight_ratio ),
    d_evaluation_temp( evaluation_temp ),
    d_file_path( file_path ),
    d_file_start_line( file_start_line ),
    d_file_table_name( file_table_name )
{
  // Make sure that the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio >= 0.0 );
  // Make sure that the evaluation temp is valid
  testPrecondition( evaluation_temp >= 0.0*Utility::Units::MeV );
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

// Get the ZAID that the file specifies data for
Data::ZAID ACENuclearDataProperties::zaid() const
{
  return d_file_table_name.zaid();
}

// Get the atomic weight ratio of the nuclide that the file specifies data for
double ACENuclearDataProperties::atomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Get the nuclear data evaluation temperature (MeV)
auto ACENuclearDataProperties::evaluationTemperatureInMeV() const -> Energy
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

// Get the nuclear data file major version
unsigned ACENuclearDataProperties::fileMajorVersion() const
{
  return this->fileVersion()/10;
}

// Get the nuclear data file version
unsigned ACENuclearDataProperties::fileVersion() const
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

EXPLICIT_CLASS_SAVE_LOAD_INST( ACENuclearDataProperties );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ACENuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// end Data_ACENuclearDataProperties.cpp
//---------------------------------------------------------------------------//
