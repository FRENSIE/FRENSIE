//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestManager.cpp
//! \author Alex Robinson
//! \brief  The unit test manager class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <list>
#include <fstream>
#include <memory>
#include <functional>

// Boost Includes
#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_UnitTestManager.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_StaticOutputFormatterFactory.hpp"
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_DynamicOutputFormatterFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "FRENSIE_config.hpp"

//! Use this to indicate that logs on all processes should be added to the report
#define REPORT_ON_ALL_PROCS -1

namespace Utility{

//! The distributed unit test manager
class DistributedUnitTestManager : public UnitTestManager
{
  
public:
  
  // Constructor
  DistributedUnitTestManager();

  // Destructor
  ~DistributedUnitTestManager()
  { /* ... */ }

protected:

  //! Print the help message
  void printHelpMessage() override;

  //! Print the test details
  void printTestDetails() override;

  //! Print the initialization status notification
  void printInitializationStatusNotification( const double initialization_time,
                                              const bool global_success ) override;

  //! Print the finalization status notification
  void printFinalizationStatusNotification( const double finalization_time,
                                            const bool global_success ) override;

  //! Print the sorting tests notification
  void printSortingTestsNotification() override;

  //! Print the running tests notification
  void printRunningTestsNotification() override;

  //! Print the unit test header
  void printUnitTestHeader( const int unit_test_id,
                            const UnitTest& unit_test ) override;

  //! Print the operation failed notification
  void printOperationFailedNotification() override;

  //! Print the operation passed notification
  void printOperationPassedNotification() override;

  //! Print the operation time
  void printOperationTime( const double time_in_sec,
                           const bool wrapped,
                           const bool goto_newline ) override;

  //! Print the operation location
  void printOperationLocation( const std::string& file_name,
                               const size_t line_number,
                               const std::string& padding ) override;

  //! Print the operation log
  void printOperationLog( const bool local_success,
                          const std::string& log_header,
                          std::ostringstream& log,
                          const bool flush_log ) override;

  //! Print failed test summary header
  void printFailedTestSummaryHeader( const std::string& header_end ) override;

  //! Print failed test name
  void printFailedTestName(const std::string& global_failed_test_name,
                           const std::string& test_details,
                           const std::string& line_padding,
                           const std::set<std::string>& local_failed_tests_set,
                           const bool goto_newline ) override;

  //! Initialize a unit test stats summary table
  void initializeUnitTestStatsSummaryTable(
            std::unique_ptr<UnitTestDataTable>& summary_table ) const override;

  //! Add column names to the unit test stats summary table
  void addUnitTestStatsSummaryTableColumnNames(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int proc_id,
                             const bool add_format ) const override;

  //! Add the number of tests row to the unit test stats summary table
  void addUnitTestStatsSummaryTableTotalTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_tests,
                             const bool new_row ) const override;

  //! Add the number of skipped tests row to the unit test stats summary table
  void addUnitTestStatsSummaryTableSkippedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_skipped_tests,
                             const bool new_row ) const override;

  //! Add the number of run tests row to the unit test stats summary table
  void addUnitTestStatsSummaryTableRunTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_run_tests,
                             const bool new_row ) const override;

  //! Add the number of passed tests row to the unit test stats summary table
  void addUnitTestStatsSummaryTablePassedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_tests,
                             const bool new_row ) const override;

  //! Add the number of failed tests row to the unit test stats summary table
  void addUnitTestStatsSummaryTableFailedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_tests,
                             const bool new_row ) const override;

  //! Add the number of checks row to the unit test stats summary table
  void addUnitTestStatsSummaryTableTotalChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_checks,
                             const bool new_row ) const override;

  //! Add the number of passed checks row to the unit test stats summary table
  void addUnitTestStatsSummaryTablePassedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_checks,
                             const bool new_row ) const override;

  //! Add the number of failed checks row to the unit test stats summary table
  void addUnitTestStatsSummaryTableFailedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_checks,
                             const bool new_row ) const override;

  //! Add the number of unexpected exceptions row to the unit test stats table
  void addUnitTestStatsSummaryTableUnexpectedExceptionsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_unexpected_exceptions,
                             const bool new_row ) const override;

  //! Add the total test time row to the unit test stats table
  void addUnitTestStatsSummaryTableTotalTestTimeRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const double total_test_time,
                             const bool new_row ) const override;

  //! Add the end result row to the unit test stats table
  void addUnitTestStatsSummaryTableEndResultRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const bool local_success,
                             const bool new_row ) const override;

  //! Print the unit test stats summary table
  void printUnitTestStatsSummaryTable(
                  std::unique_ptr<UnitTestDataTable>& summary_table ) override;

  //! Print the program execution time header
  void printProgramExecutionTimeHeader(
                                const double program_execution_time ) override;

  //! Print the test result header
  void printTestResult( const std::string& header,
                        const bool global_success ) override;
};

/*! AddUnitTestsStatsSummaryTableRow (distributed synching)
 *
 * This macro is a work around for the Utility::DistributedUnitTestManager that
 * allows us to reference the base Utility::UnitTestManager protected add row
 * method (the standard does not allow the passing of protected member function
 * pointers outside of the owner class scope).
 */
#define addUnitTestStatsSummaryTableRowImpl( summary_table_ptr, local_data, new_row, addRowMethod ) \
  std::vector<typename std::remove_const<decltype(local_data)>::type> data_on_proc = \
    Utility::GlobalMPISession::gatherData( 0, local_data );             \
                                                                        \
  if( Utility::GlobalMPISession::rank() == 0 )                          \
  {                                                                   \
    typename std::remove_const<decltype(local_data)>::type reduced_data(0); \
                                                                      \
    for( size_t i = 0; i < data_on_proc.size(); ++i )                 \
    {                                                   \
      UnitTestManager::addRowMethod( summary_table_ptr, data_on_proc[i], (i == 0 ? true : false) ); \
                                                                        \
      reduced_data += data_on_proc[i];                                  \
    }                                                                   \
                                                                        \
    if( Utility::GlobalMPISession::size() > 1 )                         \
      UnitTestManager::addRowMethod( summary_table, reduced_data, false ); \
  }                                                                     \
                                                                        \
  Utility::GlobalMPISession::barrier()

/*! The report level
 *
 * This is not nested in the UnitTestManager::Data class so that we can
 * define the operator<< for std::ostream.
 */
enum ReportLevel{ Detailed = 2, Basic = 1, Nothing = 0, Auto = -1 };

/*! Specialization of ToStringTraits for ReportLevel
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<ReportLevel>
{
  //! Return the string
  static inline std::string toString( const ReportLevel report_level )
  {
    switch( report_level )
    {
    case Detailed: return "detailed";
    case Basic: return "basic";
    case Nothing: return "nothing";
    case Auto: return "auto";
    default: return "auto";
    }
  }

  //! Place the ReportLevel in a stream
  static inline void toStream( std::ostream& os, const ReportLevel obj )
  { os << ToStringTraits<ReportLevel>::toString( obj ); }
};

/*! Specialization of FromStringTraits for ReportLevel
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<ReportLevel>
{
  //! The type that a string will be converted to
  typedef ReportLevel ReturnType;

  //! Convert the string to a ReportLevel object
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::string obj_rep_copy = boost::algorithm::to_lower_copy( obj_rep );

    if( obj_rep.find( "detail" ) < obj_rep.size() )
      return Detailed;
    else if( obj_rep.find( "basic" ) < obj_rep.size() )
      return Basic;
    else if( obj_rep.find( "nothing" ) < obj_rep.size() )
      return Nothing;
    else if( obj_rep.find( "auto" ) < obj_rep.size() )
      return Auto;
    else
      return Auto;
  }

  //! Extract a ReportLevel object from a stream
  static inline void fromStream( std::istream& is,
                                 ReportLevel& obj,
                                 const std::string& )
  {
    std::string obj_rep;

    // This loop will take care of consecutive white space characters
    while( obj_rep.size() == 0 )
      Utility::fromStream( is, obj_rep, Details::white_space_delims );

    obj = FromStringTraits<ReportLevel>::fromString( obj_rep );
  }
};
  
//! The UnitTestManager private data class
class UnitTestManager::Data
{
  
public:

  //! The unit tests type
  typedef std::list<UnitTest*> UnitTests;

  //! Get the report levels
  static std::string getReportLevels();

  //! Constructor
  Data();

  //! Destructor
  ~Data();

  //! Return the unit test manager initializer
  UnitTestManager::Initializer& getInitializer();

  //! Set the unit test manager initializer
  void setInitializer( UnitTestManager::Initializer& initializer );

  //! Return the unit tests
  UnitTests& getUnitTests();

  //! Return the unit tests
  const UnitTests& getUnitTests() const;

  //! Return the custom command line options
  boost::program_options::options_description& getCustomCommandLineOptions();

  //! Return the custom command line options
  const boost::program_options::options_description& getCustomCommandLineOptions() const;

  //! Parse command line options
  void parseCommandLineOptions( int argc, char** argv );

  //! Redirect std::cout and std::cerr to the string stream
  void redirectStdOutput( std::ostringstream& oss );

  //! Restore std::cout and std::cerr
  void restoreStdOutput();

  //! Get the command line option
  boost::program_options::variable_value
  getCommandLineOptionValue( const std::string& option_name ) const;

  //! Check if a help message was requested
  bool helpMessageRequested() const;

  //! Print the help message
  void printHelpMessage();

  //! Check if a group list was requested
  bool groupListRequested() const;

  //! Print the group list
  void printGroupList();

  //! Check if a test list was requested
  bool testListRequested() const;

  //! Print the test list
  void printTestList();

  //! Check if a data list was requested
  bool dataListRequested() const;

  //! Print the data list
  void printDataList();

  //! Get the report level
  ReportLevel getReportLevel() const;
  
  //! Get the report sink The report sink
  std::ostream& getReportSink();

  //! Get the group filter
  const std::regex& getGroupFilter() const;

  //! Get the test filter
  const std::regex& getTestFilter() const;

  //! Get the data filter
  const std::regex& getDataFilter() const;

  //! Return the run test counter
  int& getRunTestCounter();

  //! Return the run test counter
  const int& getRunTestCounter() const;

  //! Return the passed test counter
  int& getPassedTestCounter();

  //! Return the passed test counter
  const int& getPassedTestCounter() const;

  //! Return the checks counter
  size_t& getChecksCounter();

  //! Return the checks counter
  const size_t& getChecksCounter() const;

  //! Return the passed checks counter
  size_t& getPassedChecksCounter();

  //! Return the passed checks counter
  const size_t& getPassedChecksCounter() const;

  //! Return the unexpected exceptions counter
  size_t& getUnexpectedExceptionsCounter();

  //! Return the unexpected exceptions counter
  const size_t& getUnexpectedExceptionsCounter() const;

  //! Return the total unit test execution time
  double& getTotalUnitTestExecutionTime();

  //! Return the total unit test execution time
  const double& getTotalUnitTestExecutionTime() const;

private:

  // The custom report sink deleter
  struct CustomReportSinkDeleter
  {
    CustomReportSinkDeleter( const bool smart_pointer_has_ownership = true )
      : d_smart_pointer_has_ownership( smart_pointer_has_ownership )
    { /* ... */ }

    CustomReportSinkDeleter( const CustomReportSinkDeleter& other )
      : d_smart_pointer_has_ownership( other.d_smart_pointer_has_ownership )
    { /* ... */ }

    CustomReportSinkDeleter( CustomReportSinkDeleter& other )
      : d_smart_pointer_has_ownership( other.d_smart_pointer_has_ownership )
    { /* ... */ }

    CustomReportSinkDeleter( CustomReportSinkDeleter&& other )
      : d_smart_pointer_has_ownership( std::move(other.d_smart_pointer_has_ownership ) )
    { /* ... */ }

    CustomReportSinkDeleter& operator=( const CustomReportSinkDeleter& that )
    {
      if( this != &that )
        d_smart_pointer_has_ownership = that.d_smart_pointer_has_ownership;

      return *this;
    }

    CustomReportSinkDeleter& operator=( CustomReportSinkDeleter&& that )
    {
      d_smart_pointer_has_ownership =
        std::move( that.d_smart_pointer_has_ownership );

      return *this;
    }

    void operator()( std::ostream* report_sink_ptr ) const
    {
      if( d_smart_pointer_has_ownership )
        delete report_sink_ptr;
    }

  private:

    bool d_smart_pointer_has_ownership;
  };

  // The unit tests
  UnitTests d_unit_tests;

  // The command line options
  boost::program_options::options_description d_command_line_options;

  // The custom command line options
  boost::program_options::options_description d_custom_command_line_options;

  // The command line arguments
  boost::program_options::variables_map d_command_line_arguments;

  // The unit test manager initializer
  UnitTestManager::Initializer* d_initializer;

  // The report level
  ReportLevel d_report_level;
  
  // The report sink
  std::unique_ptr<std::ostream,CustomReportSinkDeleter> d_report_sink;

  // The report sink buffer
  std::streambuf* d_report_sink_buffer;

  // The std::cout buffer
  std::streambuf* d_stdout_buffer;

  // The std::cerr buffer
  std::streambuf* d_stderr_buffer;

  // The group filter
  std::regex d_group_filter;

  // The test filter
  std::regex d_test_filter;

  // The data filter
  std::regex d_data_filter;

  // The run test counter
  int d_run_test_counter;

  // The passed test counter
  int d_passed_test_counter;

  // The checks counter
  size_t d_checks_counter;

  // The passed checks counter
  size_t d_passed_checks_counter;

  // The unexpected exceptions counter
  size_t d_unexpected_exceptions_counter;

  // The total unit test execution time (s)
  double d_total_unit_test_execution_time;
};

// Get the report levels
std::string UnitTestManager::Data::getReportLevels()
{
  std::ostringstream oss;
  
  oss << Utility::toString( Detailed ) << ", "
      << Utility::toString( Basic ) << ", "
      << Utility::toString( Nothing ) << ", "
      << Utility::toString( Auto );

  return oss.str();
}

// Constructor
UnitTestManager::Data::Data()
  : d_unit_tests(),
    d_command_line_options(),
    d_custom_command_line_options(),
    d_command_line_arguments(),
    d_initializer( NULL ),
    d_report_level( Auto ),
    // This must be initialized so that a report sink exists in the event of
    // an initialization error
    d_report_sink( &std::cerr, CustomReportSinkDeleter( false ) ), 
    d_report_sink_buffer( NULL ),
    d_stdout_buffer( NULL ),
    d_stderr_buffer( NULL ),
    d_group_filter(),
    d_test_filter(),
    d_data_filter(),
    d_run_test_counter( 0 ),
    d_passed_test_counter( 0 ),
    d_checks_counter( 0 ),
    d_passed_checks_counter( 0 ),
    d_unexpected_exceptions_counter( 0 ),
    d_total_unit_test_execution_time( 0.0 )
{
  // Initialize the command line options
  d_command_line_options.add_options()
    ("help,h", "produce help message")
    ("show_groups,g",
     "show the group names and exit")
    ("show_tests,t",
     "show the test names and exit")
    ("show_data,d",
     "show the test data tables and exit")
    ("report_level,r",
     boost::program_options::value<std::string>()->default_value( Utility::toString( d_report_level ) ),
     std::string(std::string("set the report level (") + this->getReportLevels() + ")").c_str())
    ("report_sink,o",
     boost::program_options::value<std::string>()->default_value( "stdout" ),
     "set the test report sink (stdout, stderr or file name)")
    ("group_filter",
     boost::program_options::value<std::string>()->default_value( ".*" ),
     "only group names that match the regex will be executed")
    ("test_filter",
     boost::program_options::value<std::string>()->default_value( ".*" ),
     "only test names that match the regex will be executed")
    ("data_filter",
     boost::program_options::value<std::string>()->default_value( ".*" ),
     "only data table row names that match the regex will be executed");
}

// Destructor
UnitTestManager::Data::~Data()
{
  // Restore the sink buffer if it was extracted
  if( d_report_sink_buffer && d_report_sink )
    d_report_sink->rdbuf( d_report_sink_buffer );
}

// Return the unit test manager initializer
UnitTestManager::Initializer& UnitTestManager::Data::getInitializer()
{
  if( d_initializer )
    return *d_initializer;
  else
  {
    static UnitTestManager::Initializer default_initializer;
    
    return default_initializer;
  }
}

// Set the unit test manager initializer
void UnitTestManager::Data::setInitializer(
                                    UnitTestManager::Initializer& initializer )
{
  d_initializer = &initializer;
}

// Return the unit tests
auto UnitTestManager::Data::getUnitTests() -> UnitTests&
{
  return d_unit_tests;
}

// Return the unit tests
auto UnitTestManager::Data::getUnitTests() const -> const UnitTests&
{
  return d_unit_tests;
}

// Return the custom command line options
boost::program_options::options_description&
UnitTestManager::Data::getCustomCommandLineOptions()
{
  return d_custom_command_line_options;
}

// Return the custom command line options
const boost::program_options::options_description&
UnitTestManager::Data::getCustomCommandLineOptions() const
{
  return d_custom_command_line_options;
}

// Parse command line options
void UnitTestManager::Data::parseCommandLineOptions( int argc, char** argv )
{
  // Merge the command line options with the custom command line options
  boost::program_options::options_description
    cmdline_options( "Allowed options" );
  
  cmdline_options.add( d_command_line_options );
  cmdline_options.add( d_custom_command_line_options );

  // Parse the command line arguments
  boost::program_options::store(
       boost::program_options::command_line_parser(argc, argv).options(cmdline_options).run(),
       d_command_line_arguments );

  boost::program_options::notify( d_command_line_arguments );

  // Extract the report level
  d_report_level =
    Utility::fromString<ReportLevel>( d_command_line_arguments["report_level"].as<std::string>() );

  // Extract the report sink name and create the sink - only the root process
  // will interact with the report sink
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    std::string report_sink_name =
      d_command_line_arguments["report_sink"].as<std::string>();

    boost::algorithm::to_lower(report_sink_name);
    
    if( report_sink_name == "stdout" )
    {
      d_report_sink.reset( &std::cout );
      d_report_sink.get_deleter() = CustomReportSinkDeleter( false );
    }
    else if( report_sink_name == "stderr" )
    {
      d_report_sink.reset( &std::cerr );
      d_report_sink.get_deleter() = CustomReportSinkDeleter( false );
    }
    else
    {
      std::string report_sink_file_name =
        d_command_line_arguments["report_sink"].as<std::string>();
    
      d_report_sink.reset( new std::ofstream( report_sink_file_name ) );
      d_report_sink.get_deleter() = CustomReportSinkDeleter( true );
    }
    
    // Suppress all output
    if( d_report_level == Nothing )
    {
      if( d_report_sink->rdbuf() )
        d_report_sink_buffer = d_report_sink->rdbuf();

      d_report_sink->rdbuf( NULL );
    }
  }

  // Extract the filters
  d_group_filter = d_command_line_arguments["group_filter"].as<std::string>();
  d_test_filter = d_command_line_arguments["test_filter"].as<std::string>();
  d_data_filter = d_command_line_arguments["data_filter"].as<std::string>();
}

// Redirect std::cout and std::cerr to the string stream
void UnitTestManager::Data::redirectStdOutput( std::ostringstream& oss )
{
  d_stdout_buffer = std::cout.rdbuf();
  std::cout.rdbuf( oss.rdbuf() );

  d_stderr_buffer = std::cerr.rdbuf();
  std::cerr.rdbuf( oss.rdbuf() );
}

// Restore std::cout and std::cerr
void UnitTestManager::Data::restoreStdOutput()
{
  std::cout.rdbuf( d_stdout_buffer );
  std::cerr.rdbuf( d_stderr_buffer );
}

// Get the command line option
boost::program_options::variable_value
UnitTestManager::Data::getCommandLineOptionValue(
                                         const std::string& option_name ) const
{
  if( d_command_line_arguments.count( option_name ) )
    return d_command_line_arguments[option_name];
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Command line option " << option_name <<
                     " does not exist!" );
  }
}

// Check if a help message was requested
bool UnitTestManager::Data::helpMessageRequested() const
{
  if( d_command_line_arguments.count( "help" ) )
    return true;
  else
    return false;
}

// Print the help message
void UnitTestManager::Data::printHelpMessage()
{
  boost::program_options::options_description
    cmdline_options( "Allowed options" );
  
  cmdline_options.add( d_command_line_options );
  cmdline_options.add( d_custom_command_line_options );

  this->getReportSink() << cmdline_options << std::endl;
}

// Check if a group list was requested
bool UnitTestManager::Data::groupListRequested() const
{
  if( d_command_line_arguments.count( "show_groups" ) )
    return true;
  else
    return false;
}

// Print the group list
void UnitTestManager::Data::printGroupList()
{
  std::set<std::string> group_list;

  for( UnitTests::const_iterator it = d_unit_tests.begin();
       it != d_unit_tests.end();
       ++it )
  {
    group_list.insert( (*it)->getGroupName() );
  }

  if( group_list.size() > 0 )
  {
    this->getReportSink() << "Groups: " << std::endl;
    
    for( std::set<std::string>::const_iterator it = group_list.begin();
         it != group_list.end();
         ++it )
    {
      this->getReportSink() << "  " << *it << std::endl;
    }
  }
  else
    this->getReportSink() << "No groups present!" << std::endl;
}

// Check if a test list was requested
bool UnitTestManager::Data::testListRequested() const
{
  if( d_command_line_arguments.count( "show_tests" ) )
    return true;
  else
    return false;
}

// Print the test list
void UnitTestManager::Data::printTestList()
{
  if( d_unit_tests.size() > 0 )
  {
    // Sort the tests
    d_unit_tests.sort( &Utility::compareUnitTestPointers );

    std::string current_group_name( "" );

    for( UnitTests::const_iterator it = d_unit_tests.begin();
       it != d_unit_tests.end();
       ++it )
    {
      if( current_group_name != (*it)->getGroupName() )
      {
        current_group_name = (*it)->getGroupName();
        
        this->getReportSink() << "\nTests for group " << current_group_name
                              << ": " << std::endl;
      }
      
      this->getReportSink() << "  " << (*it)->getTestName() << std::endl;
    }
  }
  else
    this->getReportSink() << "No tests present!" << std::endl;
}

// Check if a data list was requested
bool UnitTestManager::Data::dataListRequested() const
{
  if( d_command_line_arguments.count( "show_data" ) )
    return true;
  else
    return false;
}

// Print the data list
void UnitTestManager::Data::printDataList()
{
  if( d_unit_tests.size() > 0 )
  {
    // Sort the tests
    d_unit_tests.sort( &Utility::compareUnitTestPointers );

    std::string current_combined_name( "" );

    for( UnitTests::const_iterator it = d_unit_tests.begin();
       it != d_unit_tests.end();
       ++it )
    {
      std::string combined_name = (*it)->getCombinedGroupTestName();
      
      if( current_combined_name != combined_name )
      {
        current_combined_name = combined_name;

        if( (*it)->getDataName().size() > 0 )
        {
          this->getReportSink() << "\nData for test " << current_combined_name
                                << ": " << std::endl;
        }
      }

      if( (*it)->getDataName().size() > 0 )
        this->getReportSink() << "  " << (*it)->getDataName() << std::endl;
    }
  }
  else
    this->getReportSink() << "No data present!" << std::endl;
}
  
// Get the report level
ReportLevel UnitTestManager::Data::getReportLevel() const
{
  return d_report_level;
}
  
// Get the report sink The report sink
std::ostream& UnitTestManager::Data::getReportSink()
{
  return *d_report_sink;
}

// Get the group filter
const std::regex& UnitTestManager::Data::getGroupFilter() const
{
  return d_group_filter;
}

// Get the test filter
const std::regex& UnitTestManager::Data::getTestFilter() const
{
  return d_test_filter;
}

// Get the data filter
const std::regex& UnitTestManager::Data::getDataFilter() const
{
  return d_data_filter;
}
  
// Return the run test counter
int& UnitTestManager::Data::getRunTestCounter()
{
  return d_run_test_counter;
}

// Return the run test counter
/*! \details A constant reference is returned so that any attempt to 
 * increment the return directly will result in a compilation error.
 */
const int& UnitTestManager::Data::getRunTestCounter() const
{
  return d_run_test_counter;
}

// Return the passed test counter
int& UnitTestManager::Data::getPassedTestCounter()
{
  return d_passed_test_counter;
}

// Return the passed test counter
/*! \details A constant reference is returned so that any attempt to 
 * increment the return directly will result in a compilation error.
 */
const int& UnitTestManager::Data::getPassedTestCounter() const
{
  return d_passed_test_counter;
}

// Return the checks counter
size_t& UnitTestManager::Data::getChecksCounter()
{
  return d_checks_counter;
}

// Return the checks counter
const size_t& UnitTestManager::Data::getChecksCounter() const
{
  return d_checks_counter;
}

// Return the passed checks counter
size_t& UnitTestManager::Data::getPassedChecksCounter()
{
  return d_passed_checks_counter;
}

// Return the passed checks counter
const size_t& UnitTestManager::Data::getPassedChecksCounter() const
{
  return d_passed_checks_counter;
}

// Return the unexpected exception counter
size_t& UnitTestManager::Data::getUnexpectedExceptionsCounter()
{
  return d_unexpected_exceptions_counter;
}

// Return the unexpected exception counter
const size_t& UnitTestManager::Data::getUnexpectedExceptionsCounter() const
{
  return d_unexpected_exceptions_counter;
}

// Return the total unit test execution time
double& UnitTestManager::Data::getTotalUnitTestExecutionTime()
{
  return d_total_unit_test_execution_time;
}

// Return the total unit test execution time
/*! \details A constant reference is returned so that any attempt to 
 * increment the return directly will result in a compilation error.
 */
const double& UnitTestManager::Data::getTotalUnitTestExecutionTime() const
{
  return d_total_unit_test_execution_time;
}

// Initialize static member data
std::unique_ptr<UnitTestManager> UnitTestManager::s_instance;

// Get the unit test manager instance
UnitTestManager& UnitTestManager::getInstance()
{
  if( !s_instance )
  {
    s_instance.reset( 
#ifdef HAVE_FRENSIE_MPI
                     new DistributedUnitTestManager
#else
                     new UnitTestManager
#endif
                      );
  }
      
  return *s_instance;
}

// Constructor
UnitTestManager::UnitTestManager()
  : d_data( new UnitTestManager::Data )
{ /* ... */ }

// Destructor
UnitTestManager::~UnitTestManager()
{ /* ... */ }

// Constructor
DistributedUnitTestManager::DistributedUnitTestManager()
  : UnitTestManager()
{ /* ... */ }

// Set the initializer
/*! \details This method should never be called directly (only through the
 * test framework macros)
 */
void UnitTestManager::setInitializer( UnitTestManager::Initializer& initializer )
{
  d_data->setInitializer( initializer );
}

// Add a unit test
/*! \details This method should never be called directly (only through the
 * test framework macros)
 */
void UnitTestManager::addUnitTest( UnitTest& test )
{
  d_data->getUnitTests().push_back( &test );
}

// Parse command-line options and run registered unit tests
/*! \details Call this from the main function when the mpi session needs
 * to be initialized before and persist after running the unit tests.
 */
int UnitTestManager::runUnitTests( int argc,
                                   char** argv,
                                   const GlobalMPISession& mpi_session )
{
  // Set up the logs - we will use an ostringstream as the log sink so that
  // we can intercept log entries and format them before passing them to
  // the actual test sink
  std::ostringstream log;
  
  {
    boost::shared_ptr<std::ostream> log_stream( &log, boost::null_deleter() );

    FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES();
    FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS( log_stream );
  }

  // Initialize the unit test manager
  bool local_success = true;

  // All output will be redirected to the log
  d_data->redirectStdOutput( log );

  std::shared_ptr<Timer> init_timer = mpi_session.createTimer();
  init_timer->start();
  
  size_t init_checkpoint = 0;
  
  try{
    d_data->getInitializer().initializeUnitTestManager( argc, argv, init_checkpoint );
  }
  __FRENSIE_TEST_CATCH_STATEMENTS__( log, true, local_success, init_checkpoint, d_data->getUnexpectedExceptionsCounter(), s_details_right_shift );

  init_timer->stop();

  d_data->restoreStdOutput();

  // Make sure that every node initialized successfully
  bool global_success = mpi_session.isGloballyTrue( local_success );

  // Summarize the initialization results
  this->summarizeInitializationResults( log,
                                        init_timer->elapsed().count(),
                                        local_success,
                                        global_success );

  // Initialization was globally successful - proceed to unit test execution
  if( global_success )
  {
    // Check if the help message was requested
    if( d_data->helpMessageRequested() )
    {
      this->printHelpMessage();
      
      return 0;
    }
    // Check if any test details were requested
    else if( d_data->groupListRequested() ||
             d_data->testListRequested() ||
             d_data->dataListRequested() )
    {
      this->printTestDetails();
      
      return 0;
    }
    
    std::shared_ptr<Timer> test_timer = mpi_session.createTimer();
    test_timer->start();
    
    // Run unit tests
    local_success = this->runUnitTests( log );
      
    global_success = mpi_session.isGloballyTrue( local_success );

    test_timer->stop();
      
    this->summarizeTestStats( local_success );

    // All output will be redirected to the log
    d_data->redirectStdOutput( log );

    std::shared_ptr<Timer> finalization_timer = mpi_session.createTimer();
    finalization_timer->start();
    
    size_t finalize_checkpoint = 0;
    bool local_finalization_success = true;

    try{
      d_data->getInitializer().finalizeUnitTestManager( finalize_checkpoint );
    }
    __FRENSIE_TEST_CATCH_STATEMENTS__( log, true, local_finalization_success, finalize_checkpoint, d_data->getUnexpectedExceptionsCounter(), s_details_right_shift );

    finalization_timer->stop();

    d_data->restoreStdOutput();

    // Make sure that every node initialized successfully
    bool global_finalization_success =
      mpi_session.isGloballyTrue( local_finalization_success );

    // Summarize the finalization results
    this->summarizeFinalizationResults( log,
                                        finalization_timer->elapsed().count(),
                                        local_finalization_success,
                                        global_finalization_success );

    // Total program execution time
    this->printProgramExecutionTimeHeader( init_timer->elapsed().count()+
                                           test_timer->elapsed().count()+
                                           finalization_timer->elapsed().count() );

    global_success = global_success && global_finalization_success;
  }

  // Summarize the test results
  return this->summarizeResults( global_success );
}

// Parse command-line options and run registered unit tests
/*! \details This is all that needs be called from the main function (return
 * the value that is returned from this method).
 */
int UnitTestManager::runUnitTests( int& argc, char**& argv )
{
  Utility::GlobalMPISession mpi_session(
                  argc, argv, Utility::GlobalMPISession::SerializedThreading );
  
  return this->runUnitTests( argc, argv, mpi_session );
}

// Print the help message
void UnitTestManager::printHelpMessage()
{
  d_data->printHelpMessage();
}

// Print the help message
void DistributedUnitTestManager::printHelpMessage()
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printHelpMessage();

  Utility::GlobalMPISession::barrier();
}

// Print the test details
void UnitTestManager::printTestDetails()
{
  if( d_data->groupListRequested() )
    d_data->printGroupList();

  if( d_data->testListRequested() )
    d_data->printTestList();
  
  if( d_data->dataListRequested() )
    d_data->printDataList();
}

// Print the test details
void DistributedUnitTestManager::printTestDetails()
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printTestDetails();

  Utility::GlobalMPISession::barrier();
}

// Run the registered unit tests
bool UnitTestManager::runUnitTests( std::ostringstream& log )
{
  bool local_success = true;
  
  std::vector<std::string> global_failed_tests;
  std::set<std::string> local_failed_tests_set;

  try{
    this->printSortingTestsNotification();

    d_data->getUnitTests().sort( &Utility::compareUnitTestPointers );

    this->printRunningTestsNotification();
  }
  __FRENSIE_TEST_CATCH_STATEMENTS__( log, true, local_success, 0, d_data->getUnexpectedExceptionsCounter(), s_details_right_shift );

  const std::string details_padding( s_details_right_shift, ' ' );
  
  for( Data::UnitTests::const_iterator test_it = d_data->getUnitTests().begin();
       test_it != d_data->getUnitTests().end();
       ++test_it )
  {
    Utility::UnitTest& unit_test = *(*test_it);
    
    if( this->shouldUnitTestBeRun( unit_test ) )
    {
      // Increment the run test counter
      ++(d_data->getRunTestCounter());
      
      // Print the unit tests header
      this->printUnitTestHeader( d_data->getRunTestCounter(), unit_test );
      
      // Run the test
      std::shared_ptr<Timer> test_timer =
        Utility::GlobalMPISession::createTimer();
      test_timer->start();
      
      const bool local_test_success =
        this->runUnitTest( unit_test, log );

      test_timer->stop();
      
      // Update test stats
      if( local_test_success )
        ++(d_data->getPassedTestCounter());
      
      d_data->getTotalUnitTestExecutionTime() += test_timer->elapsed().count();
      
      // Report the test results
      const bool global_test_success =
        Utility::GlobalMPISession::isGloballyTrue( local_test_success );
      
      this->reportTestResult( unit_test,
                              log,
                              test_timer->elapsed().count(),
                              local_test_success,
                              global_test_success,
                              global_failed_tests,
                              local_failed_tests_set,
                              details_padding );
      
      if( !local_test_success )
        local_success = false;
    }
  }
  
  // If there are any failed tests provide a summary of them now
  this->summarizeFailedTests( global_failed_tests, local_failed_tests_set );
  
  return local_success;
}

// Print the sorting tests notification
void UnitTestManager::printSortingTestsNotification()
{
  d_data->getReportSink() << "\nSorting tests by group name and then "
                          << "by definition order ..."
                          << std::endl;
}

// Print the sorting tests notification
void DistributedUnitTestManager::printSortingTestsNotification()
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printSortingTestsNotification();

  Utility::GlobalMPISession::barrier();
}

// Print the running tests notification
void UnitTestManager::printRunningTestsNotification()
{
  d_data->getReportSink() << "Running unit tests ...\n" << std::endl;
}

// Print the running tests notification
void DistributedUnitTestManager::printRunningTestsNotification()
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printRunningTestsNotification();

  Utility::GlobalMPISession::barrier();
}

// Print the unit test header
void UnitTestManager::printUnitTestHeader( const int unit_test_id,
                                           const UnitTest& unit_test )
{
  d_data->getReportSink() << unit_test_id << ". "
                          << unit_test.getFullName() << " ... ";
  d_data->getReportSink().flush();
}

// Print the unit test header
void DistributedUnitTestManager::printUnitTestHeader(
                                                    const int unit_test_id,
                                                    const UnitTest& unit_test )
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printUnitTestHeader( unit_test_id, unit_test );

  Utility::GlobalMPISession::barrier();
}

// Check if the unit test should be run
bool UnitTestManager::shouldUnitTestBeRun( const UnitTest& unit_test )
{
  if( std::regex_search(unit_test.getGroupName(), d_data->getGroupFilter()) )
  {
    if( std::regex_search(unit_test.getTestName(), d_data->getTestFilter()) )
    {
      if( std::regex_search(unit_test.getDataName(), d_data->getDataFilter()) )
      {
        return true;
      }
    }
  }

  return false;
}

// Check if the test details should be reported
bool UnitTestManager::shouldUnitTestDetailsBeReported(
                                                     const bool success ) const
{
  return d_data->getReportLevel() == Detailed ||
    (!success && d_data->getReportLevel() == Auto);
}

// Run a single unit tests
bool UnitTestManager::runUnitTest( const UnitTest& unit_test,
                                   std::ostringstream& log )
{
  // All output will be redirected to the log
  d_data->redirectStdOutput( log );

  const bool result =
    unit_test.run( log, d_data->getChecksCounter(), d_data->getPassedChecksCounter(), d_data->getUnexpectedExceptionsCounter() );
  
  // Flush all logs
  FRENSIE_FLUSH_ALL_LOGS();

  // Restore the output streams
  d_data->restoreStdOutput();

  return result;
}

// Report the test result
void UnitTestManager::reportTestResult(
                                const UnitTest& unit_test,
                                std::ostringstream& log,
                                const double test_run_time,
                                const bool local_success,
                                const bool global_success,
                                std::vector<std::string>& global_failed_tests,
                                std::set<std::string>& local_failed_tests_set,
                                const std::string& padding )
{
  // Record the tests that failed on this processes
  if( !local_success )
    local_failed_tests_set.insert( unit_test.getFullName() );

  // Report the result of the test
  if( !global_success )
  {
    global_failed_tests.push_back( unit_test.getFullName() );
    
    this->printOperationFailedNotification();
  }
  else
    this->printOperationPassedNotification();

  this->printOperationTime( test_run_time, true, true );
  
  // Report the test details
  if( this->shouldUnitTestDetailsBeReported( global_success ) )
  {
    this->printOperationLocation( unit_test.getFile(),
                                  unit_test.getLineNumber(),
                                  padding );
    this->printOperationLog( local_success, "", log, true );
  }
  else
  {
    log.str( "" );
    log.clear();
  }
}

// Print the operation failed notification
void UnitTestManager::printOperationFailedNotification()
{
  d_data->getReportSink() << "[" << Utility::Red("FAILED") << "] ";
  d_data->getReportSink().flush();
}

// Print the operation failed notification
void DistributedUnitTestManager::printOperationFailedNotification()
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printOperationFailedNotification();

  Utility::GlobalMPISession::barrier();
}

// Print the operation passed notification
void UnitTestManager::printOperationPassedNotification()
{
  d_data->getReportSink() << "[" << Utility::Green("Passed") << "] ";
  d_data->getReportSink().flush();
}

// Print the operation passed notification
void DistributedUnitTestManager::printOperationPassedNotification()
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printOperationPassedNotification();

  Utility::GlobalMPISession::barrier();
}

// Print the operation time
void UnitTestManager::printOperationTime( std::ostream& os,
                                          const double time_in_sec,
                                          const bool wrapped,
                                          const bool goto_newline,
                                          const bool display_units )
{
  os.precision( 6 );
  os << std::fixed;

  if( wrapped )
    os << "(";
  
  if( time_in_sec >= 1e-6 )
    os << time_in_sec;
  else
    os << "<" << 1e-6;

  if( display_units )
    os << " sec";

  if( wrapped )
    os << ")";

  if( goto_newline )
    os << "\n";

  os.flush();
}

// Print the operation time
void UnitTestManager::printOperationTime( const double time_in_sec,
                                          const bool wrapped,
                                          const bool goto_newline )
{
  this->printOperationTime( d_data->getReportSink(),
                            time_in_sec,
                            wrapped,
                            goto_newline );
}
  
// Print the operation time
void DistributedUnitTestManager::printOperationTime( const double time_in_sec,
                                                     const bool wrapped,
                                                     const bool goto_newline )
{
  // Gather the operation time data
  std::vector<double> operation_times =
    Utility::GlobalMPISession::gatherData( 0, time_in_sec );

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    for( size_t i = 0; i < operation_times.size(); ++i )
    {
      if( i < operation_times.size() - 1 )
        UnitTestManager::printOperationTime( operation_times[i], wrapped, false );
      else
        UnitTestManager::printOperationTime( operation_times[i], wrapped, goto_newline );
    }
  }

  Utility::GlobalMPISession::barrier();
}

// Print the operation location
void UnitTestManager::printOperationLocation( const std::string& file_name,
                                              const size_t line_number,
                                              const std::string& padding )
{
  Utility::reportCheckLocationWithPadding( file_name,
                                           line_number,
                                           d_data->getReportSink(),
                                           padding );
  d_data->getReportSink() << std::endl;
}

// Print the operation location
void DistributedUnitTestManager::printOperationLocation(
                                                  const std::string& file_name,
                                                  const size_t line_number,
                                                  const std::string& padding )
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printOperationLocation( file_name, line_number, padding );

  Utility::GlobalMPISession::barrier();
}

// Print the operation log
void UnitTestManager::printOperationLog( const bool local_success,
                                         const std::string& log_header,
                                         const std::string& log_contents )
{
  if( log_header.size() > 0 )
  {
    d_data->getReportSink() << log_header << " ";

    if( local_success )
      UnitTestManager::printOperationPassedNotification();
    else
      UnitTestManager::printOperationFailedNotification();

    d_data->getReportSink() << std::endl;
  }

  if( log_contents.size() > 0 )
  {
    Utility::DynamicOutputFormatter formatter( log_contents );
    formatter.formatUnitTestKeywords();
    
    d_data->getReportSink() << formatter << std::endl;
  }
}

// Print the operation log
void UnitTestManager::printOperationLog( const bool local_success,
                                         const std::string& log_header,
                                         std::ostringstream& log,
                                         const bool flush_log )
{
  // This will flush all pending log entries to the global log
  if( flush_log )
  {
    FRENSIE_FLUSH_ALL_LOGS();
  }
  
  this->printOperationLog( local_success, log_header, log.str() );

  if( flush_log )
  {
    log.str( "" );
    log.clear();
  }
}

// Print the operation log
void DistributedUnitTestManager::printOperationLog( const bool local_success,
                                                    const std::string&,
                                                    std::ostringstream& log,
                                                    const bool flush_log )
{
  if( Utility::GlobalMPISession::size() == 1 )
    UnitTestManager::printOperationLog( local_success, "", log, flush_log );
  else
  {
    // Gather the results
    std::vector<bool> results =
      Utility::GlobalMPISession::gatherData( 0, local_success );

    // Flush the logs
    if( flush_log )
    {
      FRENSIE_FLUSH_ALL_LOGS();
    }
    
    // Gather the logs
    std::vector<std::string> logs =
      Utility::GlobalMPISession::gatherMessages( 0, log.str() );

    if( Utility::GlobalMPISession::rank() == 0 )
    {
      for( size_t i = 0; i < results.size(); ++i )
      {
        if( this->shouldUnitTestDetailsBeReported( results[i] ) )
        {
          std::ostringstream oss;
          oss << std::string( UnitTestManager::getDetailsRightShift(), ' ' )
              << "Proc " << i;

          UnitTestManager::printOperationLog( results[i], oss.str(), logs[i] );
        }
      }
    }

    // Clear the logs
    if( flush_log )
    {
      log.str( "" );
      log.clear();
    }

    Utility::GlobalMPISession::barrier();
  }
}

// Summarize failed tests
void UnitTestManager::summarizeFailedTests(
                          const std::vector<std::string>& global_failed_tests,
                          const std::set<std::string>& local_failed_tests_set )
{
  if( global_failed_tests.size() > 0 )
  {
    this->printFailedTestSummaryHeader( "" );
    
    for( size_t i = 0; i < global_failed_tests.size(); ++i )
    {
      this->printFailedTestName( global_failed_tests[i],
                                 "",
                                 std::string( s_details_right_shift, ' ' ),
                                 local_failed_tests_set,
                                 true );
    }
  }
}

// Print failed test summary header
void UnitTestManager::printFailedTestSummaryHeader(
                                                const std::string& header_end )
{
  d_data->getReportSink() << "\nThe following tests "
                          << Utility::Red("FAILED");

  if( header_end.size() > 0 )
    d_data->getReportSink() << " " << header_end;

  d_data->getReportSink() << ":" << std::endl;
}

// Print failed test summary header
void DistributedUnitTestManager::printFailedTestSummaryHeader(
                                                           const std::string& )
{
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    if( Utility::GlobalMPISession::size() == 1 )
      UnitTestManager::printFailedTestSummaryHeader( "" );
    else
      UnitTestManager::printFailedTestSummaryHeader( "on at least one proc" );
  }

  Utility::GlobalMPISession::barrier();
}

// Print failed test name
void UnitTestManager::printFailedTestName(
                                const std::string& global_failed_test_name,
                                const std::string& test_details,
                                const std::string& padding,
                                const std::set<std::string>&,
                                const bool goto_newline )
{
  d_data->getReportSink() << padding << global_failed_test_name;

  if( test_details.size() > 0 )
    d_data->getReportSink() << test_details;

  if( goto_newline )
    d_data->getReportSink() << std::endl;
  else
    d_data->getReportSink() << std::flush;
}

// Print failed test name
void DistributedUnitTestManager::printFailedTestName(
                           const std::string& global_failed_test_name,
                           const std::string&,
                           const std::string& padding,
                           const std::set<std::string>& local_failed_tests_set,
                           const bool goto_newline )
{
  if( Utility::GlobalMPISession::size() == 1 )
  {
    UnitTestManager::printFailedTestName( global_failed_test_name,
                                          "",
                                          padding,
                                          local_failed_tests_set,
                                          goto_newline );
  }
  else
  {
    // Collect the procs that this test failed on
    std::vector<bool> local_failed_tests =
      Utility::GlobalMPISession::gatherData( 0, (local_failed_tests_set.count(global_failed_test_name) ? true : false) );

    if( Utility::GlobalMPISession::rank() == 0 )
    {
      // Print the failed test name only
      UnitTestManager::printFailedTestName( global_failed_test_name,
                                            "",
                                            padding,
                                            local_failed_tests_set,
                                            false );

      // Print the procs that the test failed on
      std::ostringstream oss;
      oss << "(";
      
      bool proc_list_started = false;
      
      for( size_t i = 0; i < local_failed_tests.size(); ++i )
      {
        if( local_failed_tests[i] )
        {
          if( proc_list_started )
            oss << ", ";
          else
            proc_list_started = true;

          oss << i;
        }
      }

      oss << ")";

      // Print the proc list
      UnitTestManager::printFailedTestName( " ", oss.str(), "",
                                            local_failed_tests_set,
                                            goto_newline );
    }

    Utility::GlobalMPISession::barrier();
  }
}

// Summarize the initialization results
void UnitTestManager::summarizeInitializationResults(
                                              std::ostringstream& log,
                                              const double initialization_time,
                                              const bool local_success,
                                              const bool global_success )
{
  this->printInitializationStatusNotification( initialization_time,
                                               global_success );

  // Report the initialization details
  if( this->shouldUnitTestDetailsBeReported( global_success ) )
    this->printOperationLog( local_success, "", log, true );
}

// Print the initialization status notification
void UnitTestManager::printInitializationStatusNotification(
                                              const double initialization_time,
                                              const bool global_success )
{
  // Report the results of the initialization
  d_data->getReportSink() << "Initialization ";
  
  if( global_success )
    d_data->getReportSink() << "completed";
  else
    d_data->getReportSink() << Utility::Red("Failed");

  d_data->getReportSink() << " ";

  // Report the initialization time for each process
  UnitTestManager::printOperationTime( initialization_time, true, true );
}

void DistributedUnitTestManager::printInitializationStatusNotification(
                                              const double initialization_time,
                                              const bool global_success )
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printInitializationStatusNotification( initialization_time, global_success );

  Utility::GlobalMPISession::barrier();
}

// Summarize the finalization results
void UnitTestManager::summarizeFinalizationResults(
                                              std::ostringstream& log,
                                              const double finalization_time,
                                              const bool local_success,
                                              const bool global_success )
{
  this->printFinalizationStatusNotification( finalization_time,
                                             global_success );

  // Report the finalization details
  if( this->shouldUnitTestDetailsBeReported( global_success ) )
    this->printOperationLog( local_success, "", log, true );
}

// Print the finalization status notification
void UnitTestManager::printFinalizationStatusNotification(
                                              const double finalization_time,
                                              const bool global_success )
{
  // Report the results of the finalization
  d_data->getReportSink() << "Finalization ";
  
  if( global_success )
    d_data->getReportSink() << "completed";
  else
    d_data->getReportSink() << Utility::Red("Failed");

  d_data->getReportSink() << " ";

  // Report the finalization time for each process
  UnitTestManager::printOperationTime( finalization_time, true, true );
}

void DistributedUnitTestManager::printFinalizationStatusNotification(
                                              const double finalization_time,
                                              const bool global_success )
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printFinalizationStatusNotification( finalization_time, global_success );

  Utility::GlobalMPISession::barrier();
}

// Summarize the test results
void UnitTestManager::summarizeTestStats( const bool local_success )
{
  // Construct the summary table
  std::unique_ptr<UnitTestDataTable> summary_table;
  
  this->initializeUnitTestStatsSummaryTable( summary_table );
  this->addUnitTestStatsSummaryTableColumnNames( summary_table, 0, true );
  this->addUnitTestStatsSummaryTableTotalTestsRow( summary_table, d_data->getUnitTests().size(), true );
  this->addUnitTestStatsSummaryTableSkippedTestsRow( summary_table, d_data->getUnitTests().size() - d_data->getRunTestCounter(), true );
  this->addUnitTestStatsSummaryTableRunTestsRow( summary_table, d_data->getRunTestCounter(), true );
  this->addUnitTestStatsSummaryTablePassedTestsRow( summary_table, d_data->getPassedTestCounter(), true );
  this->addUnitTestStatsSummaryTableFailedTestsRow( summary_table, d_data->getRunTestCounter() - d_data->getPassedTestCounter(), true );
  this->addUnitTestStatsSummaryTableTotalChecksRow( summary_table, d_data->getChecksCounter(), true );
  this->addUnitTestStatsSummaryTablePassedChecksRow( summary_table, d_data->getPassedChecksCounter(), true );
  this->addUnitTestStatsSummaryTableFailedChecksRow( summary_table, d_data->getChecksCounter() - d_data->getPassedChecksCounter(), true );
  this->addUnitTestStatsSummaryTableUnexpectedExceptionsRow( summary_table, d_data->getUnexpectedExceptionsCounter(), true );
  this->addUnitTestStatsSummaryTableTotalTestTimeRow( summary_table, d_data->getTotalUnitTestExecutionTime(), true );
  this->addUnitTestStatsSummaryTableEndResultRow( summary_table, local_success, true );
  
  this->printUnitTestStatsSummaryTable( summary_table );
}

// Initialize a unit test stats summary table
void UnitTestManager::initializeUnitTestStatsSummaryTable(
                      std::unique_ptr<UnitTestDataTable>& summary_table ) const
{
  summary_table.reset( new UnitTestDataTable( "Results Summary Table" ) );

  std::shared_ptr<OutputFormatterFactory> title_format(
       new Utility::StaticOutputFormatterFactory<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

  summary_table->setTableNameOutputFormat( title_format );
}

// Initialize a unit test stats summary table
void DistributedUnitTestManager::initializeUnitTestStatsSummaryTable(
                      std::unique_ptr<UnitTestDataTable>& summary_table ) const
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::initializeUnitTestStatsSummaryTable( summary_table );

  Utility::GlobalMPISession::barrier();
}

// Add column names to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableColumnNames(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int proc_id,
                             const bool add_format ) const
{
  if( summary_table )
  {
    std::ostringstream oss;

    if( proc_id >= 0 )
      oss << "Proc " << proc_id;
    else
      oss << "All Procs";
        
    summary_table->addColumn( oss.str() );

    if( add_format )
    {
      std::shared_ptr<OutputFormatterFactory> default_column_name_format(
              new Utility::StaticOutputFormatterFactory<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

      summary_table->setDefaultColumnNameOutputFormat( default_column_name_format );
    }
  }
}

// Add column names to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableColumnNames(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int proc_id,
                             const bool ) const
{
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    for( int i = 0; i < Utility::GlobalMPISession::size(); ++i )
    {
      UnitTestManager::addUnitTestStatsSummaryTableColumnNames(
                                   summary_table, i, (i == 0 ? true : false) );
    }

    // Add a column for the total
    if( Utility::GlobalMPISession::size() > 1 )
    {
      UnitTestManager::addUnitTestStatsSummaryTableColumnNames(
                                                    summary_table, -1, false );
    }
  }

  Utility::GlobalMPISession::barrier();
}

// Add a unit test stats summary table row
void UnitTestManager::addUnitTestStatsSummaryTableRow(
        std::unique_ptr<UnitTestDataTable>& summary_table,
        const std::string& row_name,
        const Utility::Variant& cell_data,
        const bool new_row,
        const int row_padding,
        const std::shared_ptr<const OutputFormatterFactory>& row_format ) const
{
  if( summary_table )
  {
    if( new_row )
    {
      summary_table->addRow( row_name ) << cell_data;

      summary_table->setRowOutputPadding( row_name, row_padding );

      if( row_format )
        summary_table->setRowOutputFormat( row_name, row_format );
    }
    else
      summary_table->getRow( row_name ) << cell_data;
  }
}

// Add the number of tests row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableTotalTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_tests,
                             const bool new_row ) const
{
  this->addUnitTestStatsSummaryTableRow( summary_table,
                                         "total tests:",
                                         Utility::Variant( number_of_tests ),
                                         new_row,
                                         s_details_right_shift );
}

// Add the number of tests row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableTotalTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_tests,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_tests,
                                       new_row,
                                       addUnitTestStatsSummaryTableTotalTestsRow );
}

// Add the number of skipped tests row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableSkippedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_skipped_tests,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    row_format.reset( new StaticOutputFormatterFactory<BoldTextFormat,MagentaTextColor,DefaultTextBackgroundColor> );
  }
  
  this->addUnitTestStatsSummaryTableRow(
                           summary_table,
                           "skipped:",
                           Utility::Variant( number_of_skipped_tests ),
                           new_row,
                           Details::incrementRightShift(s_details_right_shift),
                           row_format );
}

// Add the number of skipped tests row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableSkippedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_skipped_tests,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_skipped_tests,
                                       new_row,
                                       addUnitTestStatsSummaryTableSkippedTestsRow );
}

// Add the number of run tests row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableRunTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_run_tests,
                             const bool new_row ) const
{
  this->addUnitTestStatsSummaryTableRow(
                         summary_table,
                         "run:",
                         Utility::Variant( number_of_run_tests ),
                         new_row,
                         Details::incrementRightShift(s_details_right_shift) );
}

// Add the number of run tests row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableRunTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_run_tests,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_run_tests,
                                       new_row,
                                       addUnitTestStatsSummaryTableRunTestsRow );
}

// Add the number of passed tests row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTablePassedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_tests,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    row_format.reset( new StaticOutputFormatterFactory<DefaultTextFormat,GreenTextColor,DefaultTextBackgroundColor> );
  }
  
  this->addUnitTestStatsSummaryTableRow(
                           summary_table,
                           "passed:",
                           Utility::Variant( number_of_passed_tests ),
                           new_row,
                           Details::incrementRightShift(Details::incrementRightShift(s_details_right_shift)),
                           row_format );
}

// Add the number of passed tests row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTablePassedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_tests,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_passed_tests,
                                       new_row,
                                       addUnitTestStatsSummaryTablePassedTestsRow );
}

// Add the number of failed tests row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableFailedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_tests,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    row_format.reset( new StaticOutputFormatterFactory<DefaultTextFormat,RedTextColor,DefaultTextBackgroundColor> );
  }
  
  this->addUnitTestStatsSummaryTableRow(
                           summary_table,
                           "failed:",
                           Utility::Variant( number_of_failed_tests ),
                           new_row,
                           Details::incrementRightShift(Details::incrementRightShift(s_details_right_shift)),
                           row_format );
}

// Add the number of failed tests row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableFailedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_tests,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_failed_tests,
                                       new_row,
                                       addUnitTestStatsSummaryTableFailedTestsRow );
}

// Add the number of checks row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableTotalChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_checks,
                             const bool new_row ) const
{
  this->addUnitTestStatsSummaryTableRow( summary_table,
                                         "total checks:",
                                         Utility::Variant( number_of_checks ),
                                         new_row,
                                         s_details_right_shift );
}

// Add the number of checks row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableTotalChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_checks,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_checks,
                                       new_row,
                                       addUnitTestStatsSummaryTableTotalChecksRow );
}

// Add the number of passed checks row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTablePassedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_checks,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    row_format.reset( new StaticOutputFormatterFactory<DefaultTextFormat,GreenTextColor,DefaultTextBackgroundColor> );
  }
  
  this->addUnitTestStatsSummaryTableRow(
                           summary_table,
                           "passed: ",
                           Utility::Variant( number_of_passed_checks ),
                           new_row,
                           Details::incrementRightShift(s_details_right_shift),
                           row_format );
}

// Add the number of passed checks row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTablePassedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_checks,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_passed_checks,
                                       new_row,
                                       addUnitTestStatsSummaryTablePassedChecksRow );
}

// Add the number of failed checks row to the unit test stats summary table
void UnitTestManager::addUnitTestStatsSummaryTableFailedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_checks,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    row_format.reset( new StaticOutputFormatterFactory<DefaultTextFormat,RedTextColor,DefaultTextBackgroundColor> );
  }
  
  this->addUnitTestStatsSummaryTableRow(
                           summary_table,
                           "failed: ",
                           Utility::Variant( number_of_failed_checks ),
                           new_row,
                           Details::incrementRightShift(s_details_right_shift),
                           row_format );
}

// Add the number of failed checks row to the unit test stats summary table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableFailedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_checks,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_failed_checks,
                                       new_row,
                                       addUnitTestStatsSummaryTableFailedChecksRow );
}

// Add the number of unexpected exceptions row to the unit test stats table
void UnitTestManager::addUnitTestStatsSummaryTableUnexpectedExceptionsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_unexpected_exceptions,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    row_format.reset( new StaticOutputFormatterFactory<ItalicizedTextFormat,DefaultTextColor,DefaultTextBackgroundColor> );
  }
  
  this->addUnitTestStatsSummaryTableRow(
                           summary_table,
                           "unexpected exceptions:",
                           Utility::Variant( number_of_unexpected_exceptions ),
                           new_row,
                           s_details_right_shift,
                           row_format );
}

// Add the number of unexpected exceptions row to the unit test stats table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableUnexpectedExceptionsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_unexpected_exceptions,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       number_of_unexpected_exceptions,
                                       new_row,
                                       addUnitTestStatsSummaryTableUnexpectedExceptionsRow );
}

// Add the total test time row to the unit test stats table
void UnitTestManager::addUnitTestStatsSummaryTableTotalTestTimeRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const double total_test_time,
                             const bool new_row ) const
{
  std::ostringstream oss;
  this->printOperationTime( oss, total_test_time, false, false, false );
  
  this->addUnitTestStatsSummaryTableRow( summary_table,
                                         "total test time (sec):",
                                         Utility::Variant( oss.str() ),
                                         new_row,
                                         s_details_right_shift );
}

// Add the total test time row to the unit test stats table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableTotalTestTimeRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const double total_test_time,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       total_test_time,
                                       new_row,
                                       addUnitTestStatsSummaryTableTotalTestTimeRow );
}

// Add the end result row to the unit test stats table
void UnitTestManager::addUnitTestStatsSummaryTableEndResultRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const bool local_success,
                             const bool new_row ) const
{
  std::shared_ptr<OutputFormatterFactory> row_format;
  
  if( new_row )
  {
    DynamicOutputFormatterFactory::FormattingFunctionArray formatting_functions;
    formatting_functions.push_back( std::bind<void>( &DynamicOutputFormatter::formatKeyword<DefaultTextFormat,GreenTextColor,DefaultTextBackgroundColor>,
                                                       std::placeholders::_1,
                                                       "passed" ) );
    formatting_functions.push_back( std::bind<void>( &DynamicOutputFormatter::formatKeyword<DefaultTextFormat,RedTextColor,DefaultTextBackgroundColor>,
                                                       std::placeholders::_1,
                                                       "failed" ) );
    
    row_format.reset( new DynamicOutputFormatterFactory( formatting_functions ) );
  }
  
  this->addUnitTestStatsSummaryTableRow(
     summary_table,
     "End Result:",
     (local_success ? Utility::Variant("passed") : Utility::Variant("failed")),
     new_row,
     s_details_right_shift,
     row_format );
}

// Add the end result row to the unit test stats table
void DistributedUnitTestManager::addUnitTestStatsSummaryTableEndResultRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const bool local_success,
                             const bool new_row ) const
{
  addUnitTestStatsSummaryTableRowImpl( summary_table,
                                       local_success,
                                       new_row,
                                       addUnitTestStatsSummaryTableEndResultRow );
}

// Print the unit test stats summary table
void UnitTestManager::printUnitTestStatsSummaryTable(
                           std::unique_ptr<UnitTestDataTable>& summary_table )
{
  if( summary_table )
    d_data->getReportSink() << "\n" << *summary_table << std::endl;
}

// Print the unit test stats summary table
void DistributedUnitTestManager::printUnitTestStatsSummaryTable(
                            std::unique_ptr<UnitTestDataTable>& summary_table )
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printUnitTestStatsSummaryTable( summary_table );

  Utility::GlobalMPISession::barrier();
}

// Print the program execution time header
void UnitTestManager::printProgramExecutionTimeHeader(
                                          const double program_execution_time )
{
  d_data->getReportSink() << "\nProgram Execution Time: ";

  UnitTestManager::printOperationTime( program_execution_time, false, true );
}

// Print the program execution time header
void DistributedUnitTestManager::printProgramExecutionTimeHeader(
                                          const double program_execution_time )
{
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printProgramExecutionTimeHeader( program_execution_time );

  Utility::GlobalMPISession::barrier();
}

// Return the number of tests
int UnitTestManager::getNumberOfTests() const
{
  return d_data->getUnitTests().size();
}

// Return the current number of run tests
int UnitTestManager::getNumberOfRunTests() const
{
  return d_data->getRunTestCounter();
}

// Return the current number of passed tests
int UnitTestManager::getNumberOfPassedTests() const
{
  return d_data->getPassedTestCounter();
}

// Return the number of checks
int UnitTestManager::getNumberOfChecks() const
{
  return d_data->getChecksCounter();
}

// Return the number of passed checks
int UnitTestManager::getNumberOfPassedChecks() const
{
  return d_data->getPassedChecksCounter();
}

// Return the number of unexpected exceptions
int UnitTestManager::getNumberOfUnexpectedExceptions() const
{
  return d_data->getUnexpectedExceptionsCounter();
}

// Summarize the results
int UnitTestManager::summarizeResults( const bool global_success )
{
  this->printTestResult( "End Result", global_success );

  return (global_success ? 0 : 1);
}

// Print the test result header
void UnitTestManager::printTestResult( const std::string& header,
                                       const bool global_success )
{
  d_data->getReportSink() << header << ": ";

  if( global_success )
    d_data->getReportSink() << Utility::Green("TEST PASSED");
  else
    d_data->getReportSink() << Utility::Red("TEST FAILED");

  d_data->getReportSink() << std::endl;
}

// Print the test result header
void DistributedUnitTestManager::printTestResult( const std::string& header,
                                                  const bool global_success )
{
  // Print the overall result
  if( Utility::GlobalMPISession::rank() == 0 )
    UnitTestManager::printTestResult( "\n"+header, global_success );

  Utility::GlobalMPISession::barrier();
}

// Constructor
UnitTestManager::Initializer::Initializer( const size_t checkpoint )
  : setOption( UnitTestManager::getInstance().d_data->getCustomCommandLineOptions().add_options() ),
    d_start_checkpoint( checkpoint )
{ /* ... */ }

// Initialize the unit test manager
void UnitTestManager::Initializer::initializeUnitTestManager( int argc,
                                                              char** argv,
                                                              size_t& checkpoint )
{
  checkpoint = d_start_checkpoint;

  // Set the custom command line options
  if( this->getCustomCommandLineOptionsStartCheckpoint() > 0 )
    checkpoint = this->getCustomCommandLineOptionsStartCheckpoint();
  
  this->setCustomCommandLineOptions( checkpoint );

  // Parse the command line options
  UnitTestManager::getInstance().d_data->parseCommandLineOptions( argc, argv );

  // Initialize the manager
  if( this->getCustomUnitTestManagerInitializationCheckpoint() > 0 )
    checkpoint = this->getCustomUnitTestManagerInitializationCheckpoint();
  
  this->customUnitTestManagerInitialization( checkpoint );
}

// Finalize the unit test manager
void UnitTestManager::Initializer::finalizeUnitTestManager( size_t& checkpoint )
{
  checkpoint = d_start_checkpoint;

  // Finalize the manager
  if( this->getCustomUnitTestManagerFinalizationCheckpoint() > 0 )
    checkpoint = this->getCustomUnitTestManagerFinalizationCheckpoint();

  this->customUnitTestManagerFinalization( checkpoint );
}

// Get command line option value
boost::program_options::variable_value
UnitTestManager::Initializer::getRawOptionValue( const std::string& option_name ) const
{
  return UnitTestManager::getInstance().d_data->getCommandLineOptionValue( option_name );
}

//! Get the start checkpoint for the custom command line options method
size_t  UnitTestManager::Initializer::getCustomCommandLineOptionsStartCheckpoint() const
{
  return d_start_checkpoint;
}

// Set the custom command line options
/*! \details Derived classes can override this method if a unit test suite
 * needs additional command line options. Note: this method is non-const
 * because of how it can be used by derived classes.
 */
void UnitTestManager::Initializer::setCustomCommandLineOptions( size_t& checkpoint )
{ /* ... */ }

// Get the start checkpoint for the custom manager initialization method
size_t UnitTestManager::Initializer::getCustomUnitTestManagerInitializationCheckpoint() const
{
  return d_start_checkpoint;
}

// Custom manager initialization method
/*! \details Derived classes can override this method if test data needs
 * to be initialized in a specific way.
 */
void UnitTestManager::Initializer::customUnitTestManagerInitialization( size_t& checkpoint )
{ /* ... */ }

// Get the start checkpoint for the manager finalization method
size_t UnitTestManager::Initializer::getCustomUnitTestManagerFinalizationCheckpoint() const
{
  return d_start_checkpoint;
}
    
// Custom manager finalization method
/*! \details Derived classes can override this method if test data needs
 * to be cleared in a specific way (e.g. created files need to be deleted)
 */
void UnitTestManager::Initializer::customUnitTestManagerFinalization( size_t& checkpoint )
{ /* ... */ }
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnitTestManager.cpp
//---------------------------------------------------------------------------//
