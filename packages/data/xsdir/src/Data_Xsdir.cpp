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
#include "Utility_ContractException.hpp"

namespace Data{

// Split a line of the xsdir file into entry tokens
void Xsdir::splitLineIntoEntryTokens( const std::string& xsdir_line,
                                      const std::vector<std::string>& entry_tokens );
{
  boost::split( entry_tokens,
                xsdir_line,
                boost::is_any_of( " " ),
                boost::token_compress_on );
}

// Check if the line is a table entry
bool Xsdir::isLineTableEntry( const std::vector<std::string>& entry_tokens )
{
  return entry_tokens.size() > 0 &&
    entry_tokens.front().find( "." ) <
    entry_tokens.front().size();
}

// Check if the table is stored in text format
bool Xsdir::isTableHumanReadable( const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isTableHumanReadable( entry_tokens ),
                      std::runtime_error,
                      "The line does not have table data!" );
  
  return Xsdir::isTableHumanReadableQuick( entry_tokens );
}

// Check if the table is stored in text format
bool Xsdir::isTableHumanReadableQuick( const std::vector<std::string>& entry_tokens )
{
  if( entry_tokens[4] == "1" )
    return true;
  else
    return false;
}

// Check if the table type is supported
/*! \details Currently supported tables:
 * <ul>
 *  <li> All c type tables
 *  <li> t type tables with version numbers < 20 or >= 30
 *  <li> only p type tables with version number 12
 *  <li> all u type tables
 * </ul>
 */
bool Xsdir::isTableTypeSupported( const std::vector<std::string>& entry_tokens )
{
  std::tuple<std::string,unsigned,char> table_name_components = 
    Xsdir::extractTableNameComponentsFromEntryTokens();

  return Xsdir::isTableTypeSupportedImpl( table_name_components );
}

// Check if the table type is supported
bool Xsdir::isTableTypeSupportedQuick( const std::vector<std::string>& entry_tokens )
{
  // Make sure the line is a table entry
  testPrecondition( Xsdir::isLineTableEntry( entry_tokens ) );
  
  std::tuple<std::string,unsigned,char> table_name_components =
    Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

  return Xsdir::isTableTypeSupportedImpl( table_name_components );
}

// Check if the table type is supported 
bool Xsdir::isTableTypeSupportedImpl(
          const std::tuple<std::string,unsigned,char>& table_name_components );
{
  // All continuous energy neutron tables are supported
  if( Utility::get<2>(table_name_components) == 'c' )
    return true;

  // All sab tables are supported except for the MCNP6 tables
  // (version in 20s)
  else if( Utility::get<2>(table_name_components) == 't' &&
           (Utility::get<1>(table_name_components) < 20 ||
            Utility::get<1>(table_name_components) >= 30) )
    return true;

  // All photonuclear data tables are supported
  else if( Utility::get<2>(table_name_components) == 'u' )
    return true;

  // Only the new EPR data tables are supported
  else if( Utility::get<2>(table_name_components) == 'p' &&
           Utility::get<1>(table_name_components) == 12 )
    return true;
  
  // Unsupported table type
  else
    return false;
}

// Extract the table type key from the entry tokens
const std::string& Xsdir::extractTableNameComponentsFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::runtime_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractTableNameFromEntryTokens( entry_tokens );
}

// Extract (quickly) the table name from the entry tokens
const std::string& Xsdir::quickExtractTableNameFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  return entry_tokens.front();
}
  
// Extract the table type key from the entry tokens
std::tuple<std::string,unsigned,char> Xsdir::extractTableNameComponentsFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::runtime_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );
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
                      std::runtime_error,
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
                      std::runtime_error,
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
                      std::runtime_error,
                      "The line does not have table data!" );

  TEST_FOR_EXCEPTION( !Xsdir::isTableHumanReadable( entry_tokens ),
                      std::runtime_error,
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
double Xsdir::extractEvaluationTemperatureFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::runtime_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );
}

// Extract the table evaluation temperature from the entry tokens
double Xsdir::quickExtractEvaluationTemperatureFromEntryTokens(
                                 const std::vector<std::string>& entry_tokens )
{
  if( entry_tokens.size() >= 10 )
    return Utility::fromString<double>( entry_tokens[9] );
  else
    return 0.0;
}

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

  LineProcessorFunction line_processor_function =
    std::bind<void>( std::ref(*this),
                     &Xsdir::parseEntryTokensAndCreateDataPropertiesObject );
  
  this->processXsdirFile( d_xsdir_file,
                          &Xsdir::isLineTableEntry,
                          line_processor_function );
}

// Process the xsdir file
void Xsdir::processXsdirFile( const boost::filesystem::path& xsdir_file,
                              const LineFilterFunction& line_filter,
                              const LineProcessorFunction& line_processor )
{
  // Open the xsdir file
  std::ifstream xsdir_file( xsdir_file.c_str() );

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

// Parse the entry tokens and create the data properties object
void Xsdir::parseEntryTokensAndCreateDataPropertiesObject(
                                  const std::vector<std::string>& entry_tokens,
                                  const std::string& )
{
  const std::tuple<std::string,unsigned,char> table_name_components = 
    this->quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

  // Only parse supported tables that are human readable
  if( this->isTableTypeSupportedImpl( table_name_components ) &&
      this->isTableHumanReadableQuick( entry_tokens ) )
  {
    const double atomic_weight_ratio =
      this->quickExtractAtomicWeightRatioFromEntryTokens( entry_tokens );

    const double evaluation_temp_in_mev =
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
                                                       atomic_weight_ratio,
                                                       evaluation_temp_in_mev,
                                                       table_file_path,
                                                       file_start_line,
                                                       table_major_version,
                                                       table_name_components );
      }
      case 't':
      {
        this->createSABTableProperties(
                  evaluation_temp_in_mev,
                  table_file_path,
                  table_start_line,
                  table_major_version,
                  this->quickExtractTableNameFromEntryTokens( entry_tokens ) );
      }
      case 'u':
      {
        this->createPhotonuclearTableProperties( atomic_weight_ratio,
                                                 table_file_path,
                                                 file_start_line,
                                                 table_major_version,
                                                 table_name_components );
      }
      case 'p':
      {
        this->createAtomicTableProperties( table_file_path,
                                           file_start_line,
                                           table_name_components );
      }
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "An unexpected '"
                         << Utility::get<2>( table_name_components ) <<
                         "' type table has been encountered!" );
      }
    }

    FRENSIE_LOG_TAGGED_NOTIFICATION( "Xsdir", "Parsed table " << this->quickExtractTableNameFromEntryTokens( entry_tokens ) << " data." );
  }
  // Log skipped table entry
  else if( d_verbose )
  {
    FRENSIE_LOG_TAGGED_NOTIFICATION( "Xsdir", "Ignoring table " << this->quickExtractTableNameFromEntryTokens( entry_tokens ) << " data." );
  }
}

// Create the continuous energy neutron table properties
void Xsdir::createContinuousEnergyNeutronTableProperties(
                                const double atomic_weight_ratio,
                                const double evaluation_temp_in_mev,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name )
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
                                                        evaluation_temp_in_mev,
                                                        table_file_path,
                                                        file_start_line,
                                                        table_name ) );
  
  d_ce_neutron_data_properties[table_major_version][evaluation_temp_in_mev][table_name.zaid()] = properties;
}

// Create the S(A,B) table properties
void Xsdir::createSABTableProperties(
                                const double evaluation_temp_in_mev,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const std::string& table_name )
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
                                                        evaluation_temp_in_mev,
                                                        table_file_path,
                                                        file_start_line,
                                                        table_name ) );
  for( std::set<ZAID>::const_iterator zaid_it = zaids.begin();
       zaid_it != zaids.end();
       ++zaid_it )
  {
    d_sab_data_properties_map[table_major_version][evaluation_temp_in_mev][*zaid_it] = properties;
  }
}

// Create the photonuclear table properties
void Xsdir::createPhotonuclearTableProperties(
                                const double atomic_weight_ratio,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name )
{
  // Verify that the table file exists
  boost::filesystem::path complete_table_file_path =
    this->constructCompleteTableFilePath( table_file_path );

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores photonuclear table "
                      << table_name << " does not exist at the specified path "
                      "(" << complete_table_file_path.string() << ")!" );

  // Convert the atomic weight ratio to the atomic weight
  const double atomic_weight =
    atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu;
  
  std::shared_ptr<const PhotonuclearDataProperties> properties(
                     new ACEPhotonuclearDataProperties( atomic_weight,
                                                        table_file_path,
                                                        file_start_line,
                                                        table_name ) );

  d_photonuclear_data_properties_map[table_major_version][table_name.zaid()] = properties;
}

// Create the photoatomic and electroatomic table properties
void Xsdir::createAtomicTableProperties(
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const ACETableName& table_name )
{
  // Verify that the table file exists
  boost::filesystem::path complete_table_file_path =
    this->constructCompleteTableFilePath( table_file_path );

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores epr table "
                      << table_name << " does not exist at the specified path "
                      "(" << complete_table_file_path.string() << ")!" );

  std::shared_ptr<const PhotoatomicDataPropeties> photoatomic_properties(
                             new ACEPhotoatomicDataProperties( table_file_path,
                                                               file_start_line,
                                                               table_name ) );
  
  std::shared_ptr<const ElectroatomicDataProperties> electroatomic_properties(
                           new ACEElectroatomicDataProperties( table_file_path,
                                                               file_start_line,
                                                               table_name ) );

  d_epr_data_properties[table_name.zaid().atom()] =
    std::make_pair( photoatomic_properties, electroatomic_properties );
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
    Xsdir::constructCompleteTableFilePath( xsdir_path, table_file_path );

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

  Utility::ArrayView<const int> raw_zaids =
    file_handler->getTableZAIDs();
    
  for( size_t i = 0; i < raw_zaids.size(); ++i )
    table_zaids.insert( (unsigned)raw_zaids[i] );
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
                          os,
                          std::placeholders::_1,
                          std::placeholders::_2 );
}

// Filter the entry line
bool Xsdir::filterEntryLine(
                       const bool human_readable_only,
                       const std::vector<std::string>& entry_tokens,
                       const std::vector<LineFilterFunction>& partial_filters )
{
  // Filter all non-table entry lines
  if( !Xsdir::isLineTableEntry( entry_tokens ) )
    return false;

  // Filter all binary table entries if requested
  if( human_readable_only && !Xsdir::isTableHumanReadable( entry_tokens ) )
    return false;

  // Use partial filters
  for( size_t i = 0; i < partial_filters.size(); ++i )
  {
    if( !partial_filters[i]( entry_tokens ) )
      return false;
  }

  // This entry passed through all filters
  return true;
}

// Get the LineFilterFunction
auto Xsdir::getLineFilterFunction(
                      const bool human_readable_only,
                      const std::vector<LineFilterFunction>& partial_filters )
  -> LineFilterFunction
{
  return std::bind<bool>( &Xsdir::filterEntryLine,
                          human_readable_only,
                          std::placeholders::_1,
                          partial_filters );
}

// Show all entries with table data
void Xsdir::showEntriesWithTableData( std::ostream& os,
                                      const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters;

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
    [](const std::vector<std::string>& entry_tokens)
    {
      const std::tuple<std::string,unsigned,char> table_name_components = 
        Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

      if( Utility::get<2>( table_name_components ) == key )
        return true;
      else
        return false;
    };

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
    [](const std::vector<std::string>& entry_tokens)
    {
      const std::tuple<std::string,unsigned,char> table_name_components = 
        Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

      if( Utility::get<1>( table_name_components ) == version &&
          Utility::get<2>( table_name_components ) == key )
        return true;
      else
        return false;
    };

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
    [](const std::vector<std::string>& entry_tokens)
    {
      const std::tuple<std::string,unsigned,char> table_name_components = 
        Xsdir::quickExtractTableNameComponentsFromEntryTokens( entry_tokens );

      if( Utility::get<0>( table_name_components ) == basic_table_name )
        return true;
      else
        return false;
    };

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    boost::bind<bool>( &Xsdir::filterEntryLineByZAIDAndTableTypeKey,
                       zaid,
                       '*',
                       -1.0,
                       d_xsdir_path,
                       std::placeholders::_1 );

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
    boost::bind<bool>( &Xsdir::filterEntryLineByZAIDAndTableTypeKey,
                       zaid,
                       key,
                       -1.0,
                       d_xsdir_path,
                       std::placeholders::_1 );

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
                                         const double evalution_temp_in_mev,
                                         const bool human_readable_only ) const
{
  std::vector<LineFilterFunction> partial_filters( 1 );
  partial_filters.front() =
    boost::bind<bool>( &Xsdir::filterEntryLineByZAIDAndTableTypeKey,
                       zaid,
                       '*',
                       evaluation_temp_in_mev,
                       d_xsdir_path,
                       std::placeholders::_1 );

  LineFilterFunction line_filter_function =
    Xsdir::getLineFilterFunction( human_readable_only, partial_filters );

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
                                 const double evaluation_temp_in_mev,
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
  if( evalution_temp_in_mev >= 0.0 )
  {
    const double table_evaluation_temp_in_mev =
      this->quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );

    const bool equal_evaluation_temps = 
      Utility::RelativeErrorComparisonPolicy::compare(
                                                  table_evaluation_temp_in_mev,
                                                  evaluation_temp_in_mev,
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
      this->quickExtractPathFromEntryTokens( entry_tokens );

    const std::string& table_name =
      this->quickExtractTableNameFromEntryTokens( entry_tokens );
    
    const size_t file_start_line =
      this->quickExtractFileStartLineFromEntryTokens( entry_tokens );
    
    std::set<ZAID> zaids;
    
    this->extractSABTableZaids( xsdir_path,
                                relative_sab_path,
                                table_name,
                                file_start_line,
                                zaids );
    
    if( zaids.find( zaid ) == zaids.end() )
      return false;
  }

  // This entry line passed through the filter
  return true;
}

// Export the xsdir file to a parameter list
void Xsdir::exportData( Teuchos::ParameterList& parameter_list ) const
{
  this->exportCENeutronEntries( parameter_list );
  this->exportSAlphaBetaEntries( parameter_list );
  this->exportEPREntries( parameter_list );

  Teuchos::ParameterList& misc_list =
    parameter_list.sublist( "Miscellaneous" );

  exportPhotonuclearEntries( misc_list );
}

// Export the continuous energy neutron properties
void Xsdir::exportCENeutronProperties(
                                 ScatteringCenterPropertiesCache& cache ) const
{
  for( unsigned i = 0; i < d_ce_neutron_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sublist = parameter_list.sublist(
			      d_ce_neutron_xsdir_entries[i]->getTableAlias() );

    d_ce_neutron_xsdir_entries[i]->addInfoToParameterList( sublist );

    // Add the photonuclear data if there is any (use most recent - sorted)
    unsigned zaid = XsdirEntry::extractZaidFromTableName(
			       d_ce_neutron_xsdir_entries[i]->getTableName() );

    IdEntriesMap::const_iterator zaid_entries_pair =
      d_photonuclear_xsdir_entries_map.find( zaid );

    if( zaid_entries_pair != d_photonuclear_xsdir_entries_map.end() )
      zaid_entries_pair->second.front()->addInfoToParameterList( sublist );

    // Add the photoatomic and electroatomic data
    unsigned atomic_number = XsdirEntry::extractAtomicNumberFromZaid( zaid );

    IdEntryMap::const_iterator z_entries_pair =
      d_epr_xsdir_entries_map.find( atomic_number );

    if( z_entries_pair != d_epr_xsdir_entries_map.end() )
      z_entries_pair->second->addInfoToParameterList( sublist );
  }
}

// Export the S(alpha,beta) entries
void Xsdir::exportSAlphaBetaEntries(
				 Teuchos::ParameterList& parameter_list ) const
{
  for( unsigned i = 0; i < d_sab_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sab_list =
      parameter_list.sublist( d_sab_xsdir_entries[i]->getTableAlias() );

    d_sab_xsdir_entries[i]->addInfoToParameterList( sab_list );
  }
}

// Export the photonuclear entries
void Xsdir::exportPhotonuclearEntries(
				  Teuchos::ParameterList& parameter_list) const
{
  for( unsigned i = 0; i < d_photonuclear_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sublist = parameter_list.sublist(
			    d_photonuclear_xsdir_entries[i]->getTableAlias() );

    d_photonuclear_xsdir_entries[i]->addInfoToParameterList( sublist );
  }
}

// Export the epr entries
void Xsdir::exportEPREntries( Teuchos::ParameterList& parameter_list ) const
{
  for( unsigned i = 0; i < d_epr_xsdir_entries.size(); ++i )
  {
    Teuchos::ParameterList& sublist = parameter_list.sublist(
				     d_epr_xsdir_entries[i]->getTableAlias() );

    d_epr_xsdir_entries[i]->addInfoToParameterList( sublist );
  }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_Xsdir.cpp
//---------------------------------------------------------------------------//
