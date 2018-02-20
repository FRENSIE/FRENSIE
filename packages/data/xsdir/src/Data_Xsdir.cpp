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
auto Xsdir::extractEvaluationTemperatureFromEntryTokens(
                       const std::vector<std::string>& entry_tokens ) -> Energy
{
  TEST_FOR_EXCEPTION( !Xsdir::isLineTableEntry( entry_tokens ),
                      std::runtime_error,
                      "The line does not have table data!" );

  return Xsdir::quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );
}

// Extract the table evaluation temperature from the entry tokens
auto Xsdir::quickExtractEvaluationTemperatureFromEntryTokens(
                       const std::vector<std::string>& entry_tokens ) -> Energy
{
  if( entry_tokens.size() >= 10 )
    return Utility::fromString<double>( entry_tokens[9] );
  else
    return 0.0*Utility::Units::MeV;
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
                                  ScatteringCenterPropertiesDatabase& database,
                                  const std::vector<std::string>& entry_tokens,
                                  const std::string& )
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
      }
      case 't':
      {
        this->createSABTableProperties(
                  database,
                  evaluation_temp,
                  table_file_path,
                  table_start_line,
                  table_major_version,
                  this->quickExtractTableNameFromEntryTokens( entry_tokens ) );
      }
      case 'u':
      {
        this->createPhotonuclearTableProperties( database,
                                                 atomic_weight_ratio,
                                                 table_file_path,
                                                 file_start_line,
                                                 table_major_version,
                                                 table_name_components );
      }
      case 'p':
      {
        this->createAtomicTableProperties( database,
                                           atomic_weight_ratio,
                                           table_file_path,
                                           file_start_line,
                                           table_name_components );
      }
      case 'e':
      {
        this->createAtomicTableProperties( database,
                                           table_file_path,
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
                                ScatteringCenterPropertiesDatabase& database,
                                const double atomic_weight_ratio,
                                const Energy evaluation_temp,
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
                                    evaluation_temp,
                                    table_file_path,
                                    file_start_line,
                                    table_name ) );

  NuclideProperties* nuclide_properties = NULL;
  
  if( database.doPropertiesExist( table_name.zaid() ) )
  {
    try{
      nuclide_properties = &database.getNuclideProperties( table_name.zaid() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not retrieve the nuclide properties from "
                             "the data base for "
                             << table_name.zaid() << "!" );
    
    // Make sure that the reported atomic weight ratios match
    TEST_FOR_EXCEPTION( atomic_weight_ratio !=
                        nuclide_properties->atomicWeightRatio(),
                        std::runtime_error,
                        "The stored atomic weight ratio for nuclide "
                        << table_name.zaid() << " does not match the ratio "
                        "in the current xsdir file entry ("
                        << table_name << ")!" );
  }
  else
  {
    try{
      nuclide_properties =
        &database.initializeNuclideProperties( table_name.zaid(),
                                               atomic_weight_ratio );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not initialize the nuclide properties in "
                             "the database for "
                             << table_name.zaid() << "!" );
  }

  nuclide_properties->setNuclearDataProperties( properties );
}

// Create the S(A,B) table properties
void Xsdir::createSABTableProperties(
                               const Energy evaluation_temp,
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
                                                    evaluation_temp,
                                                    table_file_path,
                                                    file_start_line,
                                                    table_name ) );
  
  for( std::set<ZAID>::const_iterator zaid_it = zaids.begin();
       zaid_it != zaids.end();
       ++zaid_it )
  {
    NuclideProperties* nuclide_properties = NULL;

    if( database.doPropertiesExist( *zaid_it ) )
    {
      try{
        nuclide_properties = &database.getNuclideProperties( *zaid_it );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Could not retrieve the nuclide properties "
                               "from the database for " << *zaid_it << "!" );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Nuclide properties cannot be initialized when "
                       "creating S(A,B) table properties because the "
                       "atomic weight ratio is not available!" );
    }

    nuclide_properties->setThermalNuclearDataProperties( properties );
  }
}

// Create the photonuclear table properties
void Xsdir::createPhotonuclearTableProperties(
                                ScatteringCenterPropertiesDatabase& database,
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
  const auto atomic_weight =
    atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q;
  
  std::shared_ptr<const PhotonuclearDataProperties> properties(
                     new ACEPhotonuclearDataProperties( atomic_weight,
                                                        table_file_path,
                                                        file_start_line,
                                                        table_name ) );

  // Add the photonuclear properties to the corresponding nuclide properties
  // in the database
  NuclideProperties* nuclide_properties = NULL;

  if( database.doPropertiesExist( table_name.zaid() ) )
  {
    try{
      nuclide_properties = &database.getNuclideProperties( table_name.zaid() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not retrieve the nuclide properties from "
                             "the data base for "
                             << table_name.zaid() << "!" );

    // Make sure that the reported atomic weight ratios match
    TEST_FOR_EXCEPTION( atomic_weight_ratio !=
                        nuclide_properties->atomicWeightRatio(),
                        std::runtime_error,
                        "The stored atomic weight ratio for nuclide "
                        << table_name.zaid() << " does not match the ratio "
                        "in the current xsdir file entry ("
                        << table_name << ")!" );
  }
  else
  {
    try{
      nuclide_properties =
        &database.initializeNuclideProperties( table_name.zaid(),
                                               atomic_weight_ratio );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not initialize the nuclide properties in "
                             "the database for "
                             << table_name.zaid() << "!" );
  }

  nuclide_properties->setPhotonuclearDataProperties( properties );
}

// Create the photoatomic and electroatomic table properties
void Xsdir::createAtomicTableProperties(
            ScatteringCenterPropertiesDatabase& database,
            const boost::filesystem::path& table_file_path,
            const size_t file_start_line,
            const std::tuple<std::string,unsigned,char> table_name_components )
{
  // Verify that the table file exists
  boost::filesystem::path complete_table_file_path =
    this->constructCompleteTableFilePath( table_file_path );

  TEST_FOR_EXCEPTION( !boost::filesystem::exists( complete_table_file_path ),
                      std::runtime_error,
                      "The file that stores epr table "
                      << table_name << " does not exist at the specified path "
                      "(" << complete_table_file_path.string() << ")!" );

  if( Utility::get<2>( table_name_components ) == 'p' )
  {
    std::shared_ptr<const PhotoatomicDataPropeties> photoatomic_properties(
                   new ACEPhotoatomicDataProperties( table_file_path,
                                                     file_start_line,
                                                     table_name_components ) );

    this->addPhotoatomicPropertiesToDatabase( database,
                                              photoatomic_properties );

    if( Utility::get<1>( table_name_components ) == 12 )
    {
      std::shared_ptr<const ElectroatomicDataProperties> electroatomic_properties(
                 new ACEElectroatomicDataProperties( table_file_path,
                                                     file_start_line,
                                                     table_name_components ) );

      this->addElectroatomicPropertiesToDatabase( database,
                                                  electroatomic_properties );
    }
  }
  else if( Utility::get<2>( table_name_components ) == 'e' )
  {
    std::shared_ptr<const ElectroatomicDataProperties> electroatomic_properties(
                 new ACEElectroatomicDataProperties( table_file_path,
                                                     file_start_line,
                                                     table_name_components ) );

      this->addElectroatomicPropertiesToDatabase( database,
                                                  electroatomic_properties );
  }
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "Only tables with type keys of 'p' or 'e' are treated "
                     "as photoatomic data table entries!" );
  }
}

// Add photoatomic properties to the database
void Xsdir::addPhotoatomicPropertiesToDatabase(
                         ScatteringCenterPropertiesDatabase& database,
                         const double atomic_weight_ratio,
                         const std::shared_ptr<const PhotoatomicDataPropeties>&
                         photoatomic_properties )
{
  AtomProperties* atom_properties = NULL;

  if( database.doPropertiesExist( photoatomic_properties->atom() ) )
  {
    try{
      atom_properties =
        &database.getAtomProperties( photoatomic_properties->atom() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not retrieve the atom properties from "
                             "the database for "
                             << photoatomic_properties->atom() << "!" );

    // Make sure that the reported atomic weight ratios match
    TEST_FOR_EXCEPTION( atomic_weight_ratio !=
                        atom_properties->atomicWeightRatio(),
                        std::runtime_error,
                        "The stored atomic weight ratio for atom "
                        << photoatomic_properties->atom() <<
                        " does not match the ratio in the current xsdir file "
                        "entry (" << photoatomic_properties->tableName() <<
                        "!" );
  }
  else
  {
    try{
      atom_properties =
        &database.initializeAtomProperties( photoatomic_properties->atom(),
                                            atomic_weight_ratio );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                "Could not initialize the atom properties in "
                                "the database for "
                                << photoatomic_properties->atom() << "!" );
  }

  atom_properties->setPhotoatomicDataProperties( properties );
}

// Add electroatomic properties to the database
void Xsdir::addElectroatomicPropertiesToDatabase(
                       ScatteringCenterPropertiesDatabase& database,
                       const double atomic_weight_ratio,
                       const std::shared_ptr<const ElectroatomicDataPropeties>&
                       electroatomic_properties )
{
  AtomProperties* atom_properties = NULL;

  if( database.doPropertiesExist( electroatomic_properties->atom() ) )
  {
    try{
      atom_properties =
        &database.getAtomProperties( electroatomic_properties->atom() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not retrieve the atom properties from "
                             "the database for "
                             << electroatomic_properties->atom() << "!" );

    // Make sure that the reported atomic weight ratios match
    TEST_FOR_EXCEPTION( atomic_weight_ratio !=
                        atom_properties->atomicWeightRatio(),
                        std::runtime_error,
                        "The stored atomic weight ratio for atom "
                        << electroatomic_properties->atom() <<
                        " does not match the ratio in the current xsdir file "
                        "entry (" << electroatomic_properties->tableName() <<
                        "!" );
  }
  else
  {
    try{
      atom_properties =
        &database.initializeAtomProperties( electroatomic_properties->atom(),
                                            atomic_weight_ratio );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                "Could not initialize the atom properties in "
                                "the database for "
                                << electroatomic_properties->atom() << "!" );
  }

  atom_properties->setElectroatomicDataProperties( properties );
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
                                         const Energy evalution_temp,
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
  if( evalution_temp >= 0.0*Utility::Units::MeV )
  {
    const Energy table_evaluation_temp =
      this->quickExtractEvaluationTemperatureFromEntryTokens( entry_tokens );

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


// Export the xsdir file to a properties cache
void Xsdir::exportData( ScatteringCenterPropertiesDatabase& database ) const
{
  LineProcessorFunction line_processor_function =
    std::bind<void>( &Xsdir::parseEntryTokensAndCreateDataPropertiesObject,
                     std::cref( *this ),
                     std::ref( database ),
                     std::placeholders::_1,
                     std::placeholders::_2 );

  // Process atomic data - this data will be used to initialize the
  // nuclide properties
  {
    std::set<char> atomic_data_table_keys( {'p', 'e'} );
    
    LineFilterFunction table_type_key_partial_line_filter_function =
      std::bind<bool>( &Xsdir::filterEntryLineByTableTypeKeys,
                       atomic_data_table_keys,
                       std::placeholders::_1 );
    
    LineFilterFunction line_filter_function =
      this->getLineFilterFunction( true, {table_type_key_partial_line_filter_function} );
  
    this->processXsdirFile( d_xsdir_file,
                            line_filter_function,
                            line_processor_function );
  }

  // Process nuclear data
  {
    std::set<char> nuclear_data_table_keys( {'c', 'u'} );

    LineFilterFunction table_type_key_partial_line_filter_function =
      std::bind<bool>( &Xsdir::filterEntryLineByTableTypeKeys,
                       nuclear_data_table_keys,
                       std::placeholders::_1 );
    
    LineFilterFunction line_filter_function =
      this->getLineFilterFunction( true, {table_type_key_partial_line_filter_function} );
  
    this->processXsdirFile( d_xsdir_file,
                            line_filter_function,
                            line_processor_function );
  }

  // Process the thermal nuclear data - the corresponding nuclide must
  // already exist in the database
  {
    std::set<char> thermal_nuclear_data_table_keys( {'t'} );

    LineFilterFunction table_type_key_partial_line_filter_function =
      std::bind<bool>( &Xsdir::filterEntryLineByTableTypeKeys,
                       thermal_nuclear_data_table_keys,
                       std::placeholders::_1 );
    
    LineFilterFunction line_filter_function =
      this->getLineFilterFunction( true, {table_type_key_partial_line_filter_function} );
  
    this->processXsdirFile( d_xsdir_file,
                            line_filter_function,
                            line_processor_function );
  }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_Xsdir.cpp
//---------------------------------------------------------------------------//
