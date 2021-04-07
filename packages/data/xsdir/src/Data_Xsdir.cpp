//---------------------------------------------------------------------------//
//!
//! \file   Data_Xsdir.cpp
//! \author Alex Robinson
//! \brief  The xsdir class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <fstream>
#include <algorithm>

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Data_Xsdir.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Split a line of the xsdir file into entry tokens
void Xsdir::splitLineIntoEntryTokens( const std::string& xsdir_line,
                                      std::vector<std::string>& entry_tokens )
{
  // Trim the line before splitting it to avoid an empty first string
  if( xsdir_line[0] == ' ' )
  {
    std::string trimmed_xsdir_line = boost::algorithm::trim_copy( xsdir_line );

    Xsdir::splitLineIntoEntryTokens( trimmed_xsdir_line, entry_tokens );
  }
  else if( xsdir_line.size() == 0 )
    entry_tokens.clear();
  else
  {
    boost::split( entry_tokens,
                  xsdir_line,
                  boost::is_any_of( " " ),
                  boost::token_compress_on );
  }
}

// Check if the line is an atomic weight ratio entry
bool Xsdir::isLineZaidAtomicWeightRatioEntry(
                                 const std::vector<std::string>& entry_tokens )
{
  if( entry_tokens.size() > 0 )
  {
    if( entry_tokens.front().find_first_not_of( "0123456789" ) >=
        entry_tokens.front().size() )
    {
      unsigned raw_zaid =
        Utility::fromString<unsigned>( entry_tokens.front() );

      if( raw_zaid > 1 && raw_zaid < 101000 )
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}

// Extract the zaids and atomic weight ratios from the entry tokens
void Xsdir::extractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                  const std::vector<std::string>& entry_tokens,
                                  std::vector<std::pair<Data::ZAID,double> >&
                                  zaids_and_atomic_weight_ratios )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have paired zaid and atomic weight "
                      "ratio data!" );

  Xsdir::quickExtractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                              entry_tokens,
                                              zaids_and_atomic_weight_ratios );
}

// Check if the line is a table entry
bool Xsdir::isLineTableEntry( const std::vector<std::string>& entry_tokens )
{
  if( entry_tokens.size() > 0 )
    return entry_tokens.front().find( "." ) < entry_tokens.front().size();
  else
    return false;
}

// Check if the table is stored in text format
bool Xsdir::isTableHumanReadable( const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  return Xsdir::isTableHumanReadableQuick( entry_tokens );
}

// Check if the table is stored in text format
bool Xsdir::isTableHumanReadableQuick( const std::vector<std::string>& entry_tokens )
{
  return entry_tokens[4] == "1";
}

// Extract the table name from the entry tokens
const std::string& Xsdir::extractTableNameFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractTableNameFromEntryTokens( entry_tokens );
}

// Extract the table type key from the entry tokens
std::tuple<std::string,unsigned,char> Xsdir::extractTableNameComponentsFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );
}

// Check if the table type is supported
bool Xsdir::isTableTypeSupported( const std::tuple<std::string,unsigned,char>& table_name_components )
{
  switch( Utility::get<2>( table_name_components ) )
  {
    case 'c': return true;
    case 't': return true;
    case 'u': return true;
    case 'p': return true;
    case 'e': return true;
    default: return false;
  }
}

// Extract (quickly) the zaids and atomic weight ratios from the entry tokens
void Xsdir::quickExtractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                  const std::vector<std::string>& entry_tokens,
                                  std::vector<std::pair<Data::ZAID,double> >&
                                  zaids_and_atomic_weight_ratios )
{
  TEST_FOR_EXCEPTION( entry_tokens.size()%2 != 0,
                      std::runtime_error,
                      "The atomic weight ratio line has an uneven number of "
                      "entries!" );

  zaids_and_atomic_weight_ratios.resize( entry_tokens.size()/2 );

  for( size_t i = 0; i < entry_tokens.size(); i += 2 )
  {
    zaids_and_atomic_weight_ratios[i/2] =
      std::make_pair( Data::ZAID(entry_tokens[i]),
                      Utility::fromString<double>( entry_tokens[i+1] ) );
  }
}

// Extract (quickly) the table name from the entry tokens
const std::string& Xsdir::quickExtractTableNameFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  return entry_tokens.front();
}

// Extract the table type key from the entry tokens
std::tuple<std::string,unsigned,char> Xsdir::quickExtractTableNameComponentsFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  std::tuple<std::string,unsigned,char> table_name_components;

  ACETableName::splitTableNameIntoComponents(
                                      entry_tokens.front(),
                                      Utility::get<0>(table_name_components),
                                      Utility::get<1>(table_name_components),
                                      Utility::get<2>(table_name_components) );

  return table_name_components;
}

// Extract the atomic weight ratio from the entry tokens
double Xsdir::extractAtomicWeightRatioFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractAtomicWeightRatioFromEntryTokens( entry_tokens );
}

// Extract the atomic weight ratio from the entry tokens
double Xsdir::quickExtractAtomicWeightRatioFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  return Utility::fromString<double>( entry_tokens[1] );
}

// Extract the file name with path where the table is stored
boost::filesystem::path Xsdir::extractPathFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractPathFromEntryTokens( entry_tokens );
}

// Extract the file name with path where the table is stored
boost::filesystem::path Xsdir::quickExtractPathFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  boost::filesystem::path table_path;

  if( entry_tokens[3] == "0" )
    table_path = entry_tokens[2];

  else
  {
    table_path = entry_tokens[3];
    table_path /= entry_tokens[2];
  }

  table_path.make_preferred();

  return table_path;
}

// Extract the file start line of the table
size_t Xsdir::extractFileStartLineFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  TEST_FOR_EXCEPTION( !Xsdir::isTableHumanReadable( entry_tokens ),
                      std::logic_error,
                      "The line does not specify data for a human readable "
                      "table!" );

  return Xsdir::quickExtractFileStartLineFromEntryTokens( entry_tokens );
}

// Extract the file start line of the table
size_t Xsdir::quickExtractFileStartLineFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  return Utility::fromString<size_t>( entry_tokens[5] );
}

// Extract the table evaluation temperature from the entry tokens
auto Xsdir::extractEvaluationTemperatureFromEntryTokens(
                       const std::vector<std::string>& entry_tokens ) -> Energy
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::logic_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );
}

// Extract the table evaluation temperature from the entry tokens
auto Xsdir::quickExtractEvaluationTemperatureFromEntryTokens(
                       const std::vector<std::string>& entry_tokens ) -> Energy
{
  if( entry_tokens.size() >= 10 )
    return Utility::fromString<double>( entry_tokens[9] )*Utility::Units::MeV;
  else
    return 0.0*Utility::Units::MeV;
}

// Default constructor
Xsdir::Xsdir()
{ /* ... */ }

// Constructor
Xsdir::Xsdir( const boost::filesystem::path& xsdir_file_name,
              const bool verbose )
  : d_xsdir_path( xsdir_file_name ),
    d_verbose( verbose )
{
  // Convert to the preferred path format
  d_xsdir_path.make_preferred();

  // Verify that the xsdir file exists
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( d_xsdir_path ),
                      std::runtime_error,
                      "The xsdir file does not exist!" );

  // Check if the xsdir file contains a custom datapath
  std::ifstream xsdir_file( d_xsdir_path.c_str() );

  TEST_FOR_EXCEPTION( !xsdir_file.good(),
		      std::runtime_error,
		      "The xsdir file cannot be opened!" );

  // Loop through the xsdir file and process each unfiltered line
  std::string first_xsdir_line;

  std::getline( xsdir_file, first_xsdir_line );
  boost::algorithm::to_lower( first_xsdir_line );

  TEST_FOR_EXCEPTION( first_xsdir_line.find( "datapath" ) <
                      first_xsdir_line.size(),
                      std::runtime_error,
                      "The custom datapath entry is not currently "
                      "supported!" );
}

// Process the xsdir file
void Xsdir::processXsdirFile( const boost::filesystem::path& xsdir_file_path,
                              const LineFilterFunction& line_filter,
                              const LineProcessorFunction& line_processor )
{
  // Open the xsdir file
  std::ifstream xsdir_file( xsdir_file_path.c_str() );

  TEST_FOR_EXCEPTION( !xsdir_file.good(),
		      std::runtime_error,
		      "The xsdir file cannot be opened!" );

  // Loop through the xsdir file and process each unfiltered line
  std::string xsdir_line;
  std::vector<std::string> entry_tokens;

  while( !xsdir_file.eof() )
  {
    std::getline( xsdir_file, xsdir_line );

    Xsdir::splitLineIntoEntryTokens( xsdir_line, entry_tokens );

    // Process the line if it passes through the filter
    if( line_filter( entry_tokens ) )
      line_processor( entry_tokens, xsdir_line );

    xsdir_line.clear();
    entry_tokens.clear();
  }
}

// Parse the entry tokens and initialize the data properties object
void Xsdir::parseEntryTokensAndInitializeDataPropertiesObject(
                                  ScatteringCenterPropertiesDatabase& database,
                                  const std::vector<std::string>& entry_tokens,
                                  const std::string& ) const
{
  std::vector<std::pair<Data::ZAID,double> > zaids_and_atomic_weight_ratios;

  this->quickExtractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                              entry_tokens,
                                              zaids_and_atomic_weight_ratios );

  for( size_t i = 0; i < zaids_and_atomic_weight_ratios.size(); ++i )
  {
    const Data::ZAID& zaid =
      Utility::get<0>( zaids_and_atomic_weight_ratios[i] );

    const double atomic_weight_ratio =
      Utility::get<1>( zaids_and_atomic_weight_ratios[i] );

    if( !database.doAtomPropertiesExist( zaid ) )
      database.initializeAtomProperties( zaid, atomic_weight_ratio );

    if( !database.doNuclidePropertiesExist( zaid ) )
      database.initializeNuclideProperties( zaid, atomic_weight_ratio );
  }
}

// Parse the entry tokens and create the data properties object
void Xsdir::parseEntryTokensAndCreateDataPropertiesObject(
                                  ScatteringCenterPropertiesDatabase& database,
                                  const std::vector<std::string>& entry_tokens,
                                  const std::string&,
                                  const bool log_parsed_entries ) const
{
  const std::tuple<std::string,unsigned,char> table_name_components =
    this->quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

  const double atomic_weight_ratio =
    this->quickExtractAtomicWeightRatioFromEntryTokens( entry_tokens );

  const Energy evaluation_temp =
    this->quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );

  const boost::filesystem::path table_file_path =
    this->quickExtractPathFromEntryTokens( entry_tokens );

  const size_t file_start_line =
    this->quickExtractFileStartLineFromEntryTokens( entry_tokens );

  const unsigned table_major_version =
    Utility::get<1>( table_name_components )/10;

  switch( Utility::get<2>( table_name_components ) )
  {
    case 'c':
    {
      this->createContinuousEnergyNeutronTableProperties(
                                                       database,
                                                       atomic_weight_ratio,
                                                       evaluation_temp,
                                                       table_file_path,
                                                       file_start_line,
                                                       table_major_version,
                                                       table_name_components );
      break;
    }
    case 't':
    {
      this->createSABTableProperties(
                  database,
                  evaluation_temp,
                  table_file_path,
                  file_start_line,
                  table_major_version,
                  this->quickExtractTableNameFromEntryTokens( entry_tokens ) );
      break;
    }
    case 'u':
    {
      this->createPhotonuclearTableProperties( database,
                                               atomic_weight_ratio,
                                               table_file_path,
                                               file_start_line,
                                               table_major_version,
                                               table_name_components );
      break;
    }
    case 'p':
    {
      this->createAtomicTableProperties( database,
                                         atomic_weight_ratio,
                                         table_file_path,
                                         file_start_line,
                                         table_name_components );
      break;
    }
    case 'e':
    {
      this->createAtomicTableProperties( database,
                                         atomic_weight_ratio,
                                         table_file_path,
                                         file_start_line,
                                         table_name_components );
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "An unexpected '"
                       << Utility::get<2>( table_name_components ) <<
                       "' table type has been encountered!" );
    }
  }

  if( log_parsed_entries )
  {
    FRENSIE_LOG_NOTIFICATION( "  Parsed table " << this->quickExtractTableNameFromEntryTokens( entry_tokens ) << " data." );
  }
}

// Create the continuous energy neutron table properties
void Xsdir::createContinuousEnergyNeutronTableProperties(
                                ScatteringCenterPropertiesDatabase& database,
                                const double atomic_weight_ratio,
                                const Energy evaluation_temp,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name ) const
{
  // Verify that the table file exists
  boost::filesystem::path complete_table_file_path =
    this->constructCompleteTableFilePath( d_xsdir_path, table_file_path );

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores continuous energy neutron table "
                      << table_name << " does not exist at the specified path "
                      "(" << complete_table_file_path.string() << ")!" );

  std::shared_ptr<const NuclearDataProperties> properties(
      new ACENuclearDataProperties( atomic_weight_ratio,
                                    evaluation_temp,
                                    table_file_path,
                                    file_start_line,
                                    table_name ) );

  // Add the nuclear properties to the corresponding nuclide properties entry
  // in the database
  TEST_FOR_EXCEPTION( !database.doNuclidePropertiesExist( table_name.zaid() ),
                      std::runtime_error,
                      "The database entry for zaid " << table_name.zaid() <<
                      " was not initialized during the initialization "
                      "step!" );
  try{
      Data::NuclideProperties& nuclide_properties =
        database.getNuclideProperties( table_name.zaid() );

      nuclide_properties.setNuclearDataProperties( properties );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not set the nuclear data properties in "
                             "the database entry for zaid "
                             << table_name.zaid() << "!" );
}

// Create the S(A,B) table properties
void Xsdir::createSABTableProperties(
                                ScatteringCenterPropertiesDatabase& database,
                                const Energy evaluation_temp,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const std::string& table_name ) const
{
  // Extract the S(A,B) table zaids
  std::set<ZAID> zaids;

  this->extractSABTableZaids( d_xsdir_path,
                              table_file_path,
                              table_name,
                              file_start_line,
                              zaids );

  std::shared_ptr<const ACEThermalNuclearDataProperties> properties(
               new ACEThermalNuclearDataProperties( zaids,
                                                    evaluation_temp,
                                                    table_file_path,
                                                    file_start_line,
                                                    table_name ) );

  for( std::set<ZAID>::const_iterator zaid_it = zaids.begin();
       zaid_it != zaids.end();
       ++zaid_it )
  {
    // Add the thermal nuclear properties to the corresponding nuclide
    // properties in the database
    TEST_FOR_EXCEPTION( !database.doNuclidePropertiesExist( *zaid_it ),
                        std::runtime_error,
                        "The database entry for zaid " << *zaid_it <<
                        " was not initialized during the initialization "
                        "step!" );

    try{
      Data::NuclideProperties& nuclide_properties =
        database.getNuclideProperties( *zaid_it );

      nuclide_properties.setThermalNuclearDataProperties( properties );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not set the thermal nuclear data "
                             "properties in the database entry for zaid "
                             << *zaid_it << "!" );
  }
}

// Create the photonuclear table properties
void Xsdir::createPhotonuclearTableProperties(
                                ScatteringCenterPropertiesDatabase& database,
                                const double atomic_weight_ratio,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name ) const
{
  // Verify that the table file exists
  boost::filesystem::path complete_table_file_path =
    this->constructCompleteTableFilePath( d_xsdir_path, table_file_path );

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores photonuclear table "
                      << table_name << " does not exist at the specified path "
                      "(" << complete_table_file_path.string() << ")!" );

  // Convert the atomic weight ratio to the atomic weight
  const auto atomic_weight =
    atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  std::shared_ptr<const PhotonuclearDataProperties> properties(
                     new ACEPhotonuclearDataProperties( atomic_weight,
                                                        table_file_path,
                                                        file_start_line,
                                                        table_name ) );

  // Add the photonuclear properties to the corresponding nuclide properties
  // in the database
  TEST_FOR_EXCEPTION( !database.doNuclidePropertiesExist( table_name.zaid() ),
                      std::runtime_error,
                      "The database entry for zaid " << table_name.zaid() <<
                      " was not initialized during the initialization step!" );

  try{
    Data::NuclideProperties& nuclide_properties =
      database.getNuclideProperties( table_name.zaid() );

    nuclide_properties.setPhotonuclearDataProperties( properties );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not set the photonuclear data properties in "
                           "the database entry for zaid "
                           << table_name.zaid() << "!" );
}

// Create the photoatomic and electroatomic table properties
void Xsdir::createAtomicTableProperties(
            ScatteringCenterPropertiesDatabase& database,
            const double atomic_weight_ratio,
            const boost::filesystem::path& table_file_path,
            const size_t file_start_line,
            const std::tuple<std::string,unsigned,char> table_name_components ) const
{
  // Verify that the table file exists
  boost::filesystem::path complete_table_file_path =
    this->constructCompleteTableFilePath( d_xsdir_path, table_file_path );

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores epr table "
                      << ACETableName(table_name_components).toRaw() <<
                      " does not exist at the specified path ("
                      << complete_table_file_path.string() << ")!" );

  // Convert the atomic weight ratio to the atomic weight
  const auto atomic_weight =
    atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q;

  if( Utility::get<2>( table_name_components ) == 'p' )
  {
    std::shared_ptr<const PhotoatomicDataProperties> photoatomic_properties(
                   new ACEPhotoatomicDataProperties( atomic_weight,
                                                     table_file_path,
                                                     file_start_line,
                                                     table_name_components ) );

    this->addPhotoatomicPropertiesToDatabase( database,
                                              photoatomic_properties );

    if( Utility::get<1>( table_name_components ) == 12 ||
        Utility::get<1>( table_name_components ) == 14 )
    {
      std::shared_ptr<const ElectroatomicDataProperties> electroatomic_properties(
                 new ACEElectroatomicDataProperties( atomic_weight,
                                                     table_file_path,
                                                     file_start_line,
                                                     table_name_components ) );

      this->addElectroatomicPropertiesToDatabase( database,
                                                  electroatomic_properties );
    }
  }
  else if( Utility::get<2>( table_name_components ) == 'e' )
  {
    std::shared_ptr<const ElectroatomicDataProperties> electroatomic_properties(
                 new ACEElectroatomicDataProperties( atomic_weight,
                                                     table_file_path,
                                                     file_start_line,
                                                     table_name_components ) );

      this->addElectroatomicPropertiesToDatabase( database,
                                                  electroatomic_properties );
  }
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "Only tables with type keys of 'p' or 'e' are treated "
                     "as atomic data table entries!" );
  }
}

// Add photoatomic properties to the database
void Xsdir::addPhotoatomicPropertiesToDatabase(
                        ScatteringCenterPropertiesDatabase& database,
                        const std::shared_ptr<const PhotoatomicDataProperties>&
                        photoatomic_properties )
{
  TEST_FOR_EXCEPTION( !database.doAtomPropertiesExist( photoatomic_properties->atom() ),
                      std::runtime_error,
                      "The database entry for zaid "
                      << Data::ZAID(photoatomic_properties->atom()) <<
                      " was not initialized during the initialization step!" );
  try{
    Data::AtomProperties& atom_properties =
      database.getAtomProperties( photoatomic_properties->atom() );

    atom_properties.setPhotoatomicDataProperties( photoatomic_properties );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not set the photoatomic data properties in "
                           "the database entry for zaid "
                           << Data::ZAID(photoatomic_properties->atom()) <<
                           "!" );
}

// Add electroatomic properties to the database
void Xsdir::addElectroatomicPropertiesToDatabase(
                      ScatteringCenterPropertiesDatabase& database,
                      const std::shared_ptr<const ElectroatomicDataProperties>&
                      electroatomic_properties )
{
  TEST_FOR_EXCEPTION( !database.doAtomPropertiesExist( electroatomic_properties->atom() ),
                      std::runtime_error,
                      "The database entry for zaid "
                      << Data::ZAID(electroatomic_properties->atom()) <<
                      " was not initialized during the initialization step!" );

  try{
    Data::AtomProperties& atom_properties =
        database.getAtomProperties( electroatomic_properties->atom() );

    atom_properties.setElectroatomicDataProperties( electroatomic_properties );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not set the electroatomic data properties "
                           "in the database entry for zaid "
                           << Data::ZAID(electroatomic_properties->atom()) <<
                           "!" );
}

// Construct the complete path to a table file
boost::filesystem::path Xsdir::constructCompleteTableFilePath(
                      const boost::filesystem::path& xsdir_path,
                      const boost::filesystem::path& relative_table_file_path )
{
  boost::filesystem::path complete_table_file_path;

  if( xsdir_path.has_parent_path() )
  {
    complete_table_file_path = xsdir_path.parent_path();
    complete_table_file_path /= relative_table_file_path;
  }
  else
    complete_table_file_path = relative_table_file_path;

  return complete_table_file_path.make_preferred();
}

// Extract the zaids associated with an S(A,B) table
void Xsdir::extractSABTableZaids(
                              const boost::filesystem::path& xsdir_path,
                              const boost::filesystem::path& relative_sab_path,
                              const std::string& table_name,
                              const size_t file_start_line,
                              std::set<ZAID>& table_zaids )
{
  // To extract the zaids we have to actually load the file and read
  // the header
  boost::filesystem::path complete_table_file_path =
    Xsdir::constructCompleteTableFilePath( xsdir_path, relative_sab_path );

  // Verify that the table file exists
  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores S(A,B) table "
                      << table_name << " does not exist at the specified path "
                      "(" << complete_table_file_path.string() << ")!" );

  // Open the table file - the header will be parsed automatically
  std::unique_ptr<ACEFileHandler> file_handler;

  try{
    file_handler.reset( new ACEFileHandler( complete_table_file_path.string(),
                                            table_name,
                                            file_start_line,
                                            true ) );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "The S(A,B) table " << table_name <<
                           "header could not be parsed!" );

  Utility::ArrayView<const ZAID> extracted_zaids =
    file_handler->getTableZAIDs();

  table_zaids.insert( extracted_zaids.begin(), extracted_zaids.end() );
}

// Print the entry line
void Xsdir::printEntryLine( std::ostream& os,
                            const std::vector<std::string>&,
                            const std::string& entry_line )
{
  os << entry_line << "\n";
}

// Get the printEntryLine LineProcessorFunction
auto Xsdir::getPrintEntryLineFunction( std::ostream& os ) -> LineProcessorFunction
{
  return std::bind<void>( &Xsdir::printEntryLine,
                          std::ref(os),
                          std::placeholders::_1,
                          std::placeholders::_2 );
}

// Filter all but zaid and atomic weight ratio lines
bool Xsdir::filterAllButZaidAtomicWeightRatioEntryLines(
                        const std::vector<std::string>& entry_tokens,
                        const std::vector<LineFilterFunction>& partial_filters,
                        const bool log_filtered_zaid_awr_entries )
{
  // Filter all non-zaid/awr entry lines
  if( !Xsdir::isLineZaidAtomicWeightRatioEntry( entry_tokens ) )
    return false;

  // Use partial filters
  for( size_t i = 0; i < partial_filters.size(); ++i )
  {
    if( !partial_filters[i]( entry_tokens ) )
      return Xsdir::logFilteredZaidAtomicWeightRatioEntryLine( entry_tokens, log_filtered_zaid_awr_entries );
  }

  // This entry passed through all filters
  return true;
}

// Log a filtered table entry line
bool Xsdir::logFilteredZaidAtomicWeightRatioEntryLine(
                                  const std::vector<std::string>& entry_tokens,
                                  const bool logging_requested )
{
  if( logging_requested )
  {
    std::vector<std::pair<Data::ZAID,double> > zaids_and_atomic_weight_ratios;

    Xsdir::quickExtractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                              entry_tokens,
                                              zaids_and_atomic_weight_ratios );

    FRENSIE_LOG_TAGGED_NOTIFICATION( "Xsdir",
                                     "Ignoring zaid/awr entries "
                                     << zaids_and_atomic_weight_ratios );
  }

  return false;
}

// Get the standard line filter function for zaid atomic weight ratio entries
auto Xsdir::getStandardZaidAtomicWeightRatioLineFilterFunction(
               const std::vector<LineFilterFunction>& partial_filters,
               const bool log_filtered_zaid_awr_entries ) -> LineFilterFunction
{
  return std::bind<bool>( &Xsdir::filterAllButZaidAtomicWeightRatioEntryLines,
                          std::placeholders::_1,
                          partial_filters,
                          log_filtered_zaid_awr_entries );
}

// Filter all but the table entry lines
bool Xsdir::filterAllButTableEntryLines(
                       const bool human_readable_only,
                       const std::vector<std::string>& entry_tokens,
                       const std::vector<LineFilterFunction>& partial_filters,
                       const bool log_filtered_table_entries )
{
  // Filter all non-table entry lines
  if( !Xsdir::isLineTableEntry( entry_tokens ) )
    return false;

  // Filter all binary table entries if requested
  if( human_readable_only && !Xsdir::isTableHumanReadable( entry_tokens ) )
    return Xsdir::logFilteredTableEntryLine( entry_tokens, log_filtered_table_entries );

  // Use partial filters
  for( size_t i = 0; i < partial_filters.size(); ++i )
  {
    if( !partial_filters[i]( entry_tokens ) )
      return Xsdir::logFilteredTableEntryLine( entry_tokens, log_filtered_table_entries );
  }

  // This entry passed through all filters
  return true;
}

// Log a filtered table entry line
bool Xsdir::logFilteredTableEntryLine(
                                  const std::vector<std::string>& entry_tokens,
                                  const bool logging_requested )
{
  if( logging_requested )
  {
    FRENSIE_LOG_TAGGED_NOTIFICATION( "Xsdir", "Ignoring table " << Xsdir::quickExtractTableNameFromEntryTokens( entry_tokens ) << " data." );
  }

  return false;
}

// Get the LineFilterFunction
auto Xsdir::getStandardTableEntryLineFilterFunction(
                      const bool human_readable_only,
                      const std::vector<LineFilterFunction>& partial_filters,
                      const bool log_filtered_table_entries )
  -> LineFilterFunction
{
  return std::bind<bool>( &Xsdir::filterAllButTableEntryLines,
                          human_readable_only,
                          std::placeholders::_1,
                          partial_filters,
                          log_filtered_table_entries );
}

// Show all entries with table data
void Xsdir::showEntriesWithTableData( std::ostream& os,
                                      const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters;

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, partial_filters );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Show all entries with the desired table type key
void Xsdir::showEntriesWithTableTypeKey( std::ostream& os,
                                         const char key,
                                         const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    [&key](const std::vector<std::string>& entry_tokens)
    {
      const std::tuple<std::string,unsigned,char> table_name_components =
        Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

      if( Utility::get<2>( table_name_components ) == key )
        return true;
      else
        return false;
    };

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, partial_filters );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Show all entries with the desired table type key and version
void Xsdir::showEntriesWithTableTypeKeyAndVersion(
                                         std::ostream& os,
                                         const unsigned version,
                                         const char key,
                                         const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    [&version,&key](const std::vector<std::string>& entry_tokens)
    {
      const std::tuple<std::string,unsigned,char> table_name_components =
        Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

      if( Utility::get<2>( table_name_components ) == key )
      {
        // Check the major version
        if( (key == 'c' || key == 't') && version < 10 )
        {
          if( Utility::get<1>( table_name_components )/10 == version )
            return true;
          else
            return false;
        }
        // Check the exact version
        else
        {
          if( Utility::get<1>( table_name_components ) == version )
            return true;
          else
            return false;
        }
      }
      else
        return false;
    };

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, partial_filters );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Show all entries with the basic table name
void Xsdir::showEntriesWithBasicTableName(
                                         std::ostream& os,
                                         const std::string& basic_table_name,
                                         const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    [&basic_table_name](const std::vector<std::string>& entry_tokens)
    {
      const std::tuple<std::string,unsigned,char> table_name_components =
        Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

      if( Utility::get<0>( table_name_components ) == basic_table_name )
        return true;
      else
        return false;
    };

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, partial_filters );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Show all entries with the desired zaid
void Xsdir::showEntriesWithZAID( std::ostream& os,
                                 const Data::ZAID& zaid,
                                 const bool human_readable_only ) const
{
  LineFilterFunction partial_filter =
    std::bind<bool>( &Xsdir::filterEntryLineByZAIDAndTableTypeKey,
                     std::cref(zaid),
                     '*',
                     -1.0*Utility::Units::MeV,
                     std::cref(d_xsdir_path),
                     std::placeholders::_1 );

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, {partial_filter} );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Show all entries with the desired zaid and table type key
void Xsdir::showEntriesWithZAIDAndTableTypeKey(
                                         std::ostream& os,
                                         const Data::ZAID& zaid,
                                         const char key,
                                         const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    std::bind<bool>( &Xsdir::filterEntryLineByZAIDAndTableTypeKey,
                     std::cref(zaid),
                     key,
                     -1.0*Utility::Units::MeV,
                     std::cref(d_xsdir_path),
                     std::placeholders::_1 );

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, partial_filters );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Show all entries with the desired zaid and table evaluation temp
void Xsdir::showEntriesWithZAIDAndTableEvaluationTemp(
                                         std::ostream& os,
                                         const Data::ZAID& zaid,
                                         const Energy evaluation_temp,
                                         const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    std::bind<bool>( &Xsdir::filterEntryLineByZAIDAndTableTypeKey,
                     std::cref(zaid),
                     '*',
                     evaluation_temp,
                     std::cref(d_xsdir_path),
                     std::placeholders::_1 );

  LineFilterFunction line_filter_function =
    Xsdir::getStandardTableEntryLineFilterFunction( human_readable_only, partial_filters );

  LineProcessorFunction line_processor_function =
    Xsdir::getPrintEntryLineFunction( os );

  this->processXsdirFile( d_xsdir_path,
                          line_filter_function,
                          line_processor_function );
}

// Filter line entries by zaid, table type key, table version  and eval. temp
bool Xsdir::filterEntryLineByZAIDAndTableTypeKey(
                                 const Data::ZAID& zaid,
                                 const char key,
                                 const Energy evaluation_temp,
                                 const boost::filesystem::path& xsdir_path,
                                 const std::vector<std::string>& entry_tokens )
{
  const std::tuple<std::string,unsigned,char> table_name_components =
    Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

  // Check if the keys match - this line will not pass through the filter if
  // they do not match (NOTE: the wildcard key '*' will be ignored)
  if( key != '*' )
  {
    if( Utility::get<2>( table_name_components ) != key )
      return false;
  }

  // Check if the evaluation temps match - this line will not pass through the
  // filter if they do not have a relative error < 1e-9 (NOTE: any filter
  // temp < 0.0 will be ignored)
  if( evaluation_temp >= 0.0*Utility::Units::MeV )
  {
    const Energy table_evaluation_temp =
      Xsdir::quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );

    const bool equal_evaluation_temps =
      Utility::RelativeErrorComparisonPolicy::compare(
                                                  table_evaluation_temp,
                                                  evaluation_temp,
                                                  1e-9 );
    if( !equal_evaluation_temps )
      return false;
  }

  // Check if the table name zaid matches the filter zaid - this line will not
  // pass through the filter if they do not match
  if( Utility::get<2>( table_name_components ) != 't' )
  {
    if( ZAID( Utility::get<0>( table_name_components ) ) != zaid )
      return false;
  }

  // Check if there is a zaid associated with the S(A,B) table that matches
  // the filter zaid - this line will not pass through the filter if there
  // is not one
  else
  {
    boost::filesystem::path relative_table_path =
      Xsdir::quickExtractPathFromEntryTokens( entry_tokens );

    const std::string& table_name =
      Xsdir::quickExtractTableNameFromEntryTokens( entry_tokens );

    const size_t file_start_line =
      Xsdir::quickExtractFileStartLineFromEntryTokens( entry_tokens );

    std::set<ZAID> zaids;

    Xsdir::extractSABTableZaids( xsdir_path,
                                 relative_table_path,
                                 table_name,
                                 file_start_line,
                                 zaids );

    if( zaids.find( zaid ) == zaids.end() )
      return false;
  }

  // This entry line passed through the filter
  return true;
}

// Filter line entries by table type keys
bool Xsdir::filterEntryLineByTableTypeKeys( const std::set<char>& keys,
                                            const std::vector<std::string>& entry_tokens )
{
  std::tuple<std::string,unsigned,char> table_name_components =
    Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

  if( keys.find( Utility::get<2>(table_name_components) ) != keys.end() )
    return true;
  else
    return false;
}

// Filter line entries by table type keys
bool Xsdir::filterEntryLineByTableTypeKeysNotInSet( const std::set<char>& keys,
                                                    const std::vector<std::string>& entry_tokens )
{
  std::tuple<std::string,unsigned,char> table_name_components =
    Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

  if( keys.find( Utility::get<2>(table_name_components) ) == keys.end() )
    return true;
  else
    return false;
}

// Export the xsdir file to a properties cache
void Xsdir::exportData( ScatteringCenterPropertiesDatabase& database ) const
{
  // Initialize the database entries
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "Initializing atom and nuclide properties ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  LineProcessorFunction line_processor_function =
    std::bind<void>( &Xsdir::parseEntryTokensAndInitializeDataPropertiesObject,
                     std::cref( *this ),
                     std::ref( database ),
                     std::placeholders::_1,
                     std::placeholders::_2 );

  {
    LineFilterFunction line_filter_function =
      this->getStandardZaidAtomicWeightRatioLineFilterFunction( {} );

    this->processXsdirFile( d_xsdir_path,
                            line_filter_function,
                            line_processor_function );

  }

  FRENSIE_LOG_NOTIFICATION( "done." );

  // Populate the database with the table data in the xsdir file
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "Populating database entries ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  line_processor_function =
    std::bind<void>( &Xsdir::parseEntryTokensAndCreateDataPropertiesObject,
                     std::cref( *this ),
                     std::ref( database ),
                     std::placeholders::_1,
                     std::placeholders::_2,
                     d_verbose );

  {
    std::set<char> data_table_keys( {'p', 'e', 'c', 't', 'u'} );

    LineFilterFunction table_type_key_partial_line_filter_function =
      std::bind<bool>( &Xsdir::filterEntryLineByTableTypeKeys,
                       data_table_keys,
                       std::placeholders::_1 );

    LineFilterFunction line_filter_function =
      this->getStandardTableEntryLineFilterFunction( true, {table_type_key_partial_line_filter_function}, d_verbose );

    this->processXsdirFile( d_xsdir_path,
                            line_filter_function,
                            line_processor_function );
  }

  FRENSIE_LOG_NOTIFICATION( "done." );

  // Clean up the database
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "Cleaning up database ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  database.removeEmptyProperties( true );

  FRENSIE_LOG_NOTIFICATION( "done." );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_Xsdir.cpp
//---------------------------------------------------------------------------//
