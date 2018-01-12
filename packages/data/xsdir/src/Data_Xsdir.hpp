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
#include "Data_NuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_ScatteringCenterPropertiesCache.hpp"
#include "Utility_Tuple.hpp"

namespace Data{

//! The xsdir
class Xsdir
{

public:

  //! Constructor
  Xsdir( const boost::filesystem::path& xsdir_file_name,
         const bool verbose = false );

  //! Destructor
  ~Xsdir()
  { /* ... */ }

  //! Split a line of the xsdir file into entry tokens
  static void splitLineIntoEntryTokens( const std::string& xsdir_line,
                                        const std::vector<std::string>& entry_tokens );

  //! Check if the line is a table entry
  static bool isLineTableEntry( const std::vector<std::string>& entry_tokens );

  //! Check if the table is stored in text format
  static bool isTableHumanReadable( const std::vector<std::string>& entry_tokens );

  //! Check if the table type is supported
  static bool isTableTypeSupported(
                                const std::vector<std::string>& entry_tokens );

  //! Extract the table name from the entry tokens
  static const std::string& extractTableNameFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );
  
  //! Extract the table type key from the entry tokens
  static std::tuple<std::string,unsigned,char>
  extractTableNameComponentsFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

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
  static double extractEvaluationTemperatureFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

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
                                const double evalution_temp_in_mev,
                                const bool human_readable_only = false ) const;

  //! Export the xsdir data to a properties cache
  void exportData( ScatteringCenterPropertiesCache& cache,
                   const std::map<std::string,std::string>& sab_table_aliases =
                   std::map<std::string,std::string>() ) const;

private:

  //! Check (quickly) if the table is stored in text format
  static bool isTableHumanReadableQuick( const std::vector<std::string>& entry_tokens );

  // Check (quickly) if the table type is supported 
  static bool isTableTypeSupportedQuick(
                                const std::vector<std::string>& entry_tokens );

  // Check if the table type is supported 
  static bool isTableTypeSupportedImpl(
               const std::tuple<std::string,unsigned,char>& version_type_key );

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
  static double quickExtractEvaluationTemperatureFromEntryTokens(
                                const std::vector<std::string>& entry_tokens );

  // Extract the zaids associated with an S(A,B) table
  static void extractSABTableZaids( const boost::filesystem::path& xsdir_path,
                                    const boost::filesystem::path& relative_sab_path,
                                    const std::string& table_name,
                                    const size_t file_start_line,
                                    std::set<ZAID>& table_zaids );

  // Process the xsdir file
  typedef std::function<bool(const std::vector<std::string>&)> LineFilterFunction;
  typedef std::function<void(const std::vector<std::string>&, const std::string& ) LineProcessorFunction;
  
  static void processXsdirFile( const boost::filesystem::path& xsdir_file,
                                const LineFilterFunction& line_filter,
                                const LineProcessorFunction& line_processor );

  // Print the entry line
  static void printEntryLine( std::ostream& os,
                              const std::vector<std::string>& entry_tokens,
                              const std::string& entry_line );

  // Get the printEntryLine LineProcessorFunction
  static LineProcessorFunction getPrintEntryLineFunction( std::ostream& os );

  // Parse the entry tokens and create the data properties object
  void parseEntryTokensAndCreateDataPropertiesObject(
                                  const std::vector<std::string>& entry_tokens,
                                  const std::string& );

  // Filter the entry line
  static bool filterEntryLine(
                      const bool human_readable_only,
                      const std::vector<std::string>& entry_tokens,
                      const std::vector<LineFilterFunction>& partial_filters );
  
  // Get the LineFilterFunction
  static LineFilterFunction getLineFilterFunction(
                      const bool human_readable_only,
                      const std::vector<LineFilterFunction>& partial_filters );

  // Filter line entries by zaid, table type key, table version and eval. temp
  static bool filterEntryLineByZAIDAndTableTypeKey(
                                const Data::ZAID& zaid,
                                const char key,
                                const double evaluation_temp_in_mev,
                                const boost::filesystem::path& xsdir_path,
                                const std::vector<std::string>& entry_tokens );

  // Create the continuous energy neutron table properties
  void createContinuousEnergyNeutronTableProperties(
                                const double atomic_weight_ratio,
                                const double evaluation_temp_in_mev,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name );

  // Create the S(A,B) table properties
  void createSABTableProperties( const double evaluation_temp_in_mev,
                                 const boost::filesystem::path& table_file_path,
                                 const size_t file_start_line,
                                 const unsigned table_major_version,
                                 const std::string& table_name );

  // Create the photonuclear table properties
  void createPhotonuclearTableProperties(
                                const double atomic_weight_ratio,
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const unsigned table_major_version,
                                const ACETableName& table_name );

  // Create the photoatomic and electroatomic table properties
  void createAtomicTableProperties(
                                const boost::filesystem::path& table_file_path,
                                const size_t file_start_line,
                                const ACETableName& table_name );

  // Construct the complete path to a table file
  static boost::filesystem::path constructCompleteTableFilePath(
                     const boost::filesystem::path& xsdir_path,
                     const boost::filesystem::path& relative_table_file_path );
  
  // Export the continuous energy neutron properties
  void exportCENeutronProperties( ScatteringCenterPropertiesCache& cache ) const;

  // Export the S(alpha,beta) properties
  void exportSAlphaBetaProperties( ScatteringCenterPropertiesCache& cache ) const;

  // Export the photonuclear properties
  void exportPhotonuclearProperties(
				ScatteringCenterPropertiesCache& cache ) const;

  //! Export the epr properties
  void exportEPRProperties( ScatteringCenterPropertiesCache& cache ) const;

  // The xsdir file name with path
  boost::filesystem::path d_xsdir_path;

  // Verbose output (through logging)
  bool d_verbose;

  // The continuous energy neutron data properties
  typedef std::map<ZAID,std::shared_ptr<const NuclearDataProperties> >
  ZaidNuclearDataPropertiesMap;
  
  typedef std::map<double,ZaidNuclearDataPropertiesMap>
  TempZaidNuclearDataPropertiesMap;

  typedef std::map<unsigned,TempZaidNuclearDataPropertiesMap>
  VersionTempZaidNuclearDataPropetiesMap;

  VersionTempZaidNuclearDataPropetiesMap d_ce_neutron_data_properties_map;

  // The S(alpha,beta) properties
  typedef std::map<ZAID,std::shared_ptr<const ThermalNuclearDataProperties> >
  ZaidThermalNuclearDataPropertiesMap;

  typedef std::map<double,ZaidThermalNuclearDataPropertiesMap>
  TempZaidThermalNuclearDataPropertiesMap;

  typedef std::map<unsigned,TempZaidThermalNuclearDataPropertiesMap>
  VersionTempZaidThermalNuclearDataPropertiesMap;
  
  VersionTempZaidThermalNuclearDataPropertiesMap d_sab_data_properties_map;

  // The photonuclear xsdir properties map - for quick lookup
  typedef std::map<ZAID,std::shared_ptr<const PhotonuclearDataProperties> >
  ZaidPhotonuclearDataPropertiesMap;
  
  typedef std::map<unsigned,ZaidPhotonuclearDataPropertiesMap>
  VersionZaidPhotonuclearDataPropertiesMap;

  VersionZaidPhotonuclearDataPropertiesMap d_photonuclear_data_properties_map;

  // The electron-photon-relaxation xsdir properties map - for quick lookup
  typedef std::pair<std::shared_ptr<const PhotoatomicDataProperties>,std::shared_ptr<const ElectroatomicDataProperties> > EPRDataPropertiesPair;
  
  typedef std::map<AtomType,EPRDataPropertiesPair> AtomEPRDataPropertiesMap;

  AtomEPRDataPropertiesMap d_epr_data_properties_map;
};

} // end Data namespace

#endif // end DATA_XSDIR_HPP

//---------------------------------------------------------------------------//
// end Data_Xsdir.hpp
//---------------------------------------------------------------------------//
