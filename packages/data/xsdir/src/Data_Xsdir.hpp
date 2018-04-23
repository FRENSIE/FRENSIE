//---------------------------------------------------------------------------//
//!
//! \file   Data_Xsdir.hpp
//! \author Alex Robinson
//! \brief  The xsdir class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSDIR_HPP
#define DATA_XSDIR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// Boost Includes
#include <boost/filesystem/path.hpp>

// FRENSIE Includes
#include "Data_ACETableName.hpp"
#include "Data_NuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace Data{

//! The xsdir
class Xsdir
{

public:

  //! The energy unit
  typedef NuclearDataProperties::EnergyUnit EnergyUnit;

  //! The energy quantity
  typedef NuclearDataProperties::Energy Energy;

  //! Constructor
  Xsdir( const boost::filesystem::path& xsdir_file_name,
         const bool verbose = false );

  //! Destructor
  virtual ~Xsdir()
  { /* ... */ }

  //! Show all entries with table data
  void showEntriesWithTableData(
                                std::ostream& os,
                                const bool human_readable_only = false ) const;

  //! Show all entries with the desired table type key
  void showEntriesWithTableTypeKey(
                                std::ostream& os,
                                const char key,
                                const bool human_readable_only = false ) const;

  //! Show all entries with the desired table type key and version
  void showEntriesWithTableTypeKeyAndVersion(
                                std::ostream& os,
                                const unsigned version,
                                const char key,
                                const bool human_readable_only = false ) const;

  //! Show all entries with the desired zaid
  void showEntriesWithZAID( std::ostream& os,
                            const Data::ZAID& zaid,
                            const bool human_readable_only = false ) const;

  //! Show all entries with the basic table name
  void showEntriesWithBasicTableName(
                                std::ostream& os,
                                const std::string& basic_table_name,
                                const bool human_readable_only = false ) const;

  //! Show all entries with the desired zaid and table type key
  void showEntriesWithZAIDAndTableTypeKey(
                                std::ostream& os,
                                const Data::ZAID& zaid,
                                const char key,
                                const bool human_readable_only = false ) const;

  //! Show all entries with the desired zaid and table evaluation temp
  void showEntriesWithZAIDAndTableEvaluationTemp(
                                std::ostream& os,
                                const Data::ZAID& zaid,
                                const Energy evaluation_temp,
                                const bool human_readable_only = false ) const;

  //! Export the xsdir data to a properties database
  void exportData( ScatteringCenterPropertiesDatabase& database ) const;

protected:

  //! Default constructor
  Xsdir();

  //! Split a line of the xsdir file into entry tokens
  static void splitLineIntoEntryTokens( const std::string& xsdir_line,
                                        std::vector<std::string>& entry_tokens );

  //! Check if the line is a zaid, atomic weight ratio entry
  static bool isLineZaidAtomicWeightRatioEntry(
                                const std::vector<std::string>& entry_tokens );

  //! Extract the zaids and atomic weight ratios from the entry tokens
  static void extractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                  const std::vector<std::string>& entry_tokens,
                                  std::vector<std::pair<Data::ZAID,double> >&
                                  zaids_and_atomic_weight_ratios );
  
  //! Check if the line is a table entry
  static bool isLineTableEntry( const std::vector<std::string>& entry_tokens );

  //! Check if the table is stored in text format
  static bool isTableHumanReadable( const std::vector<std::string>& entry_tokens );

  //! Extract the table name from the entry tokens
  static const std::string& extractTableNameFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );
  
  //! Extract the table name components from the entry tokens
  static std::tuple<std::string,unsigned,char>
  extractTableNameComponentsFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  //! Check if the table type is supported
  static bool isTableTypeSupported( const std::tuple<std::string,unsigned,char>& table_name_components );

  //! Extract the atomic weight ratio from the entry tokens
  static double extractAtomicWeightRatioFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  //! Extract the file name with path where the table is stored
  static boost::filesystem::path extractPathFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  //! Extract the file start line of the table
  static size_t extractFileStartLineFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  //! Extract the table evaluation temperature from the entry tokens
  static Energy extractEvaluationTemperatureFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

private:

  // The line filter function type (return true if the input should pass
  // through the filter)
  typedef std::function<bool(const std::vector<std::string>&)> LineFilterFunction;

  // The line processor function type
  typedef std::function<void(const std::vector<std::string>&, const std::string& )> LineProcessorFunction;

  //! Extract (quickly) the zaids and atomic weight ratios from the entry tokens
  static void quickExtractZaidsAndAtomicWeightRatiosFromEntryTokens(
                                  const std::vector<std::string>& entry_tokens,
                                  std::vector<std::pair<Data::ZAID,double> >&
                                  zaids_and_atomic_weight_ratios );

  // Check (quickly) if the table is stored in text format
  static bool isTableHumanReadableQuick( const std::vector<std::string>& entry_tokens );

  // Extract (quickly) the table name from the entry tokens
  static const std::string& quickExtractTableNameFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract (quickly) the table name components from the entry tokens
  static std::tuple<std::string,unsigned,char>
  quickExtractTableNameComponentsFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract (quickly) the atomic weight ratio from the entry tokens
  static double quickExtractAtomicWeightRatioFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract (quickly) the file name with path where the table is stored
  static boost::filesystem::path quickExtractPathFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract (quickly) the file start line of the table
  static size_t quickExtractFileStartLineFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract the table evaluation temperature from the entry tokens
  static Energy quickExtractEvaluationTemperatureFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract the zaids associated with an S(A,B) table
  static void extractSABTableZaids( const boost::filesystem::path& xsdir_path,
                                    const boost::filesystem::path& relative_sab_path,
                                    const std::string& table_name,
                                    const size_t file_start_line,
                                    std::set<ZAID>& table_zaids );

  // Process the xsdir file  
  static void processXsdirFile( const boost::filesystem::path& xsdir_file,
                                const LineFilterFunction& line_filter,
                                const LineProcessorFunction& line_processor );

  // Print the entry line
  static void printEntryLine( std::ostream& os,
                              const std::vector<std::string>& entry_tokens,
                              const std::string& entry_line );

  // Get the printEntryLine LineProcessorFunction
  static LineProcessorFunction getPrintEntryLineFunction( std::ostream& os );

  // Parse the entry tokens and initialize the data properties object
  void parseEntryTokensAndInitializeDataPropertiesObject(
                                  ScatteringCenterPropertiesDatabase& database,
                                  const std::vector<std::string>& entry_tokens,
                                  const std::string& ) const;

  // Parse the entry tokens and create the data properties object
  void parseEntryTokensAndCreateDataPropertiesObject(
                                 ScatteringCenterPropertiesDatabase& database,
                                 const std::vector<std::string>& entry_tokens,
                                 const std::string&,
                                 const bool log_parsed_entries = false ) const;

  // Filter all but zaid and atomic weight ratio lines
  static bool filterAllButZaidAtomicWeightRatioEntryLines(
                        const std::vector<std::string>& entry_tokens,
                        const std::vector<LineFilterFunction>& partial_filters,
                        const bool log_filtered_zaid_awr_entries  = false );

  // Log a filtered zaid and atomic weight ratio line
  static bool logFilteredZaidAtomicWeightRatioEntryLine(
                                  const std::vector<std::string>& entry_tokens,
                                  const bool logging_requested );

  // Get the standard line filter function for zaid atomic weight ratio entries
  static LineFilterFunction getStandardZaidAtomicWeightRatioLineFilterFunction(
                        const std::vector<LineFilterFunction>& partial_filters,
                        const bool log_filtered_zaid_awr_entries = false );
  
  // Filter all but table entry lines
  static bool filterAllButTableEntryLines(
                      const bool human_readable_only,
                      const std::vector<std::string>& entry_tokens,
                      const std::vector<LineFilterFunction>& partial_filters,
                      const bool log_filtered_table_entries = false );

  // Log a filtered table entry line
  static bool logFilteredTableEntryLine(
                                  const std::vector<std::string>& entry_tokens,
                                  const bool logging_requested );
  
  // Get the standard line filter function for table entries
  static LineFilterFunction getStandardTableEntryLineFilterFunction(
                      const bool human_readable_only,
                      const std::vector<LineFilterFunction>& partial_filters,
                      const bool log_filtered_table_entries = false );

  // Filter line entries by zaid, table type key, table version and eval. temp
  static bool filterEntryLineByZAIDAndTableTypeKey(
                               const Data::ZAID& zaid,
                               const char key,
                               const Energy evaluation_temp,
                               const boost::filesystem::path& xsdir_path,
                               const std::vector<std::string>& entry_tokens );

  // Filter line entries by table type keys
  static bool filterEntryLineByTableTypeKeys( const std::set<char>& keys,
                                              const std::vector<std::string>& entry_tokens );

  // Filter line entries by keys not in set
  static bool filterEntryLineByTableTypeKeysNotInSet( const std::set<char>& keys,
                                                      const std::vector<std::string>& entry_tokens );

  // Create the continuous energy neutron table properties
  void createContinuousEnergyNeutronTableProperties(
                               ScatteringCenterPropertiesDatabase& database,
                               const double atomic_weight_ratio,
                               const Energy evaluation_temp,
                               const boost::filesystem::path& table_file_path,
                               const size_t file_start_line,
                               const unsigned table_major_version,
                               const ACETableName& table_name ) const;

  // Create the S(A,B) table properties
  void createSABTableProperties( ScatteringCenterPropertiesDatabase& database,
                                 const Energy evaluation_temp,
                                 const boost::filesystem::path& table_file_path,
                                 const size_t file_start_line,
                                 const unsigned table_major_version,
                                 const std::string& table_name ) const;

  // Create the photonuclear table properties
  void createPhotonuclearTableProperties(
                                ScatteringCenterPropertiesDatabase& database,
                                const double atomic_weight_ratio,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name ) const;

  // Create the photoatomic and electroatomic table properties
  void createAtomicTableProperties(
           ScatteringCenterPropertiesDatabase& database,
           const double atomic_weight_ratio,
           const boost::filesystem::path& table_file_path,
           const size_t file_start_line,
           const std::tuple<std::string,unsigned,char> table_name_components ) const ;

  // Add photoatomic properties to the database
  static void addPhotoatomicPropertiesToDatabase(
                        ScatteringCenterPropertiesDatabase& database,
                        const std::shared_ptr<const PhotoatomicDataProperties>&
                        photoatomic_properties );

  // Add electroatomic properties to the database
  static void addElectroatomicPropertiesToDatabase(
                      ScatteringCenterPropertiesDatabase& database,
                      const std::shared_ptr<const ElectroatomicDataProperties>&
                      electroatomic_properties );

  // Construct the complete path to a table file
  static boost::filesystem::path constructCompleteTableFilePath(
                     const boost::filesystem::path& xsdir_path,
                     const boost::filesystem::path& relative_table_file_path );

  // The xsdir file name with path
  boost::filesystem::path d_xsdir_path;

  // Verbose output (through logging)
  bool d_verbose;
};

} // end Data namespace

#endif // end DATA_XSDIR_HPP

//---------------------------------------------------------------------------//
// end Data_Xsdir.hpp
//---------------------------------------------------------------------------//
