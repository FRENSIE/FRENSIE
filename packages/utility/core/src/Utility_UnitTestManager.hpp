//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestManager.hpp
//! \author Alex Robinson
//! \brief  The unit test manager class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_MANAGER_HPP
#define UTILITY_UNIT_TEST_MANAGER_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

// FRENSIE Includes
#include "Utility_UnitTest.hpp"
#include "Utility_UnitTestDataTable.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_UnitTestHelpers.hpp"
#include "Utility_LoggingMacros.hpp"

namespace Utility{

//! The unit test manager
class UnitTestManager
{

public:

  //! Get the test details starting right shift
  static constexpr int getTestDetailsStartingRightShift()
  { return s_details_right_shift; }

  //! The initializer
  class Initializer
  {

  public:

    //! Constructor
    Initializer( const size_t start_checkpoint = 0 );

    //! Initialize the unit test manager
    void initializeUnitTestManager( int argc, char** argv, size_t& checkpoint );

    //! Finalize the unit test manager
    void finalizeUnitTestManager( size_t& checkpoint );

    //! Destructor
    virtual ~Initializer()
    { /* ... */ }

  protected:

    //! Get command line option value
    template<typename T>
    T getOptionValue( const std::string& option_name ) const
    { return this->getRawOptionValue( option_name ).as<T>(); }

    //! Get the start checkpoint for the custom command line options method
    virtual size_t getCustomCommandLineOptionsStartCheckpoint() const;

    //! Set the custom command line options
    virtual void setCustomCommandLineOptions( size_t& checkpoint );

    //! Get the start checkpoint for the custom manager initialization method
    virtual size_t getCustomUnitTestManagerInitializationCheckpoint() const;

    //! Custom manager initialization method
    virtual void customUnitTestManagerInitialization( size_t& checkpoint );

    //! Get the start checkpoint for the manager finalization method
    virtual size_t getCustomUnitTestManagerFinalizationCheckpoint() const;

    //! Custom manager finalization method
    virtual void customUnitTestManagerFinalization( size_t& checkpoint );

    //! Shortcut for adding command line options (functor)
    boost::program_options::options_description_easy_init setOption;

  private:

    //! Get command line option raw value
    boost::program_options::variable_value
    getRawOptionValue( const std::string& option_name ) const;

    // The start checkpoint
    size_t d_start_checkpoint;
  };

  //! Get the unit test manager instance
  static UnitTestManager& getInstance();

  //! Destructor
  virtual ~UnitTestManager();

  //! Set the initializer
  void setInitializer( UnitTestManager::Initializer& initializer );

  //! Add a unit test
  void addUnitTest( UnitTest& test );

  //! Parse command-line options and run registered unit tests
  int runUnitTests( int& argc, char**& argv );

  //! Parse command-line options and run registered unit tests
  int runUnitTests( int argc, char** argv, const GlobalMPISession& mpi_session );

  //! Return the number of tests
  int getNumberOfTests() const;

  //! Return the current number of run tests
  int getNumberOfRunTests() const;

  //! Return the current number of passed tests
  int getNumberOfPassedTests() const;

  //! Return the number of checks
  int getNumberOfChecks() const;

  //! Return the number of passed checks
  int getNumberOfPassedChecks() const;

  //! Return the number of unexpected exceptions
  int getNumberOfUnexpectedExceptions() const;

protected:

  // Constructor
  UnitTestManager();

  //! Print the help message
  virtual void printHelpMessage();

  //! Print the test details
  virtual void printTestDetails();

  //! Print the initialization status notification
  virtual void printInitializationStatusNotification(
                                              const double initialization_time,
                                              const bool global_success );

  //! Print the finalization status notification
  virtual void printFinalizationStatusNotification(
                                                const double finalization_time,
                                                const bool global_success );

  //! Print the sorting tests notification
  virtual void printSortingTestsNotification();

  //! Print the running tests notification
  virtual void printRunningTestsNotification();

  //! Print the unit test header
  virtual void printUnitTestHeader( const int unit_test_id,
                                    const UnitTest& unit_test );

  //! Print the operation failed notification
  virtual void printOperationFailedNotification();

  //! Print the operation passed notification
  virtual void printOperationPassedNotification();

  //! Print the operation time
  virtual void printOperationTime( const double time_in_sec,
                                   const bool wrapped,
                                   const bool goto_newline );

  //! Print the operation location
  virtual void printOperationLocation( const std::string& file_name,
                                       const size_t line_number,
                                       const std::string& padding );

  //! Print the operation log
  virtual void printOperationLog( const bool local_success,
                                  const std::string& log_header,
                                  std::ostringstream& log,
                                  const bool flush_log );

  //! Print the operation log
  void printOperationLog( const bool local_success,
                          const std::string& log_header,
                          const std::string& log_contents );

  //! Print failed test summary header
  virtual void printFailedTestSummaryHeader( const std::string& header_end );

  //! Print failed test name
  virtual void printFailedTestName(
                           const std::string& global_failed_test_name,
                           const std::string& test_details,
                           const std::string& padding,
                           const std::set<std::string>& local_failed_tests_set,
                           const bool goto_newline );

  //! Initialize a unit test stats summary table
  virtual void initializeUnitTestStatsSummaryTable(
                     std::unique_ptr<UnitTestDataTable>& summary_table ) const;

  //! Add column names to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableColumnNames(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int proc_id,
                             const bool add_format ) const;

  //! Add the number of tests row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableTotalTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_tests,
                             const bool new_row ) const;

  //! Add the number of skipped tests row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableSkippedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_skipped_tests,
                             const bool new_row ) const;

  //! Add the number of run tests row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableRunTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_run_tests,
                             const bool new_row ) const;

  //! Add the number of passed tests row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTablePassedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_tests,
                             const bool new_row ) const;

  //! Add the number of failed tests row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableFailedTestsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_tests,
                             const bool new_row ) const;

  //! Add the number of checks row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableTotalChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_checks,
                             const bool new_row ) const;

  //! Add the number of passed checks row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTablePassedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_passed_checks,
                             const bool new_row ) const;

  //! Add the number of failed checks row to the unit test stats summary table
  virtual void addUnitTestStatsSummaryTableFailedChecksRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_failed_checks,
                             const bool new_row ) const;

  //! Add the number of unexpected exceptions row to the unit test stats table
  virtual void addUnitTestStatsSummaryTableUnexpectedExceptionsRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const int number_of_unexpected_exceptions,
                             const bool new_row ) const;

  //! Add the total test time row to the unit test stats table
  virtual void addUnitTestStatsSummaryTableTotalTestTimeRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const double total_test_time,
                             const bool new_row ) const;

  //! Add the end result row to the unit test stats table
  virtual void addUnitTestStatsSummaryTableEndResultRow(
                             std::unique_ptr<UnitTestDataTable>& summary_table,
                             const bool local_success,
                             const bool new_row ) const;

  //! Print the unit test stats summary table
  virtual void printUnitTestStatsSummaryTable(
                           std::unique_ptr<UnitTestDataTable>& summary_table );

  //! Print the program execution time header
  virtual void printProgramExecutionTimeHeader(
                                         const double program_execution_time );

  //! Print the test result header
  virtual void printTestResult( const std::string& header,
                                const bool global_success );

  //! Check if the test details should be reported
  bool shouldUnitTestDetailsBeReported( const bool success ) const;

  //! Get the details right shift
  static constexpr int getDetailsRightShift()
  { return s_details_right_shift; }

private:

  // Check if the unit test should be run
  bool shouldUnitTestBeRun( const UnitTest& unit_test );

  // Run the registered unit tests
  bool runUnitTests( std::ostringstream& log );

  // Run a single unit tests
  bool runUnitTest( const UnitTest& unit_test, std::ostringstream& log );

  //! Report the test result
  void reportTestResult( const UnitTest& unit_test,
                         std::ostringstream& log,
                         const double test_run_time,
                         const bool local_success,
                         const bool global_success,
                         std::vector<std::string>& global_failed_tests,
                         std::set<std::string>& local_failed_tests_set,
                         const std::string& padding );

  //! Print the operation time
  static void printOperationTime( std::ostream& os,
                                  const double time_in_sec,
                                  const bool wrapped,
                                  const bool goto_newline,
                                  const bool display_units = true );

  // Summarize the initialization results
  void summarizeInitializationResults(
                                    std::ostringstream& log,
                                    const double initialization_time,
                                    const bool local_success,
                                    const bool global_success );

  // Summarize the finalization results
  void summarizeFinalizationResults(
                                    std::ostringstream& log,
                                    const double finalization_time,
                                    const bool local_success,
                                    const bool global_success );

  // Summarize failed tests
  void summarizeFailedTests(
                         const std::vector<std::string>& global_failed_tests,
                         const std::set<std::string>& local_failed_tests_set );

  // Summarize the test results
  void summarizeTestStats( const bool local_success );

  // Add a unit test stats summary table row
  void addUnitTestStatsSummaryTableRow(
              std::unique_ptr<UnitTestDataTable>& summary_table,
              const std::string& row_name,
              const Utility::Variant& cell_data,
              const bool new_row,
              const int row_padding = 0,
              const std::shared_ptr<const OutputFormatterFactory>& row_format =
              std::shared_ptr<const OutputFormatterFactory>() ) const;

  // Summarize the results
  int summarizeResults( const bool global_success );

  // The Initializer class is a friend
  friend class UnitTestManager::Initializer;

  // Manager instance
  static std::unique_ptr<UnitTestManager> s_instance;

  // The starting right shift for test details
  static constexpr int s_details_right_shift = 2;

  // The starting summary table cell length
  static constexpr int s_summary_table_start_cell_length = 26;

  // The summary table cell length
  static constexpr int s_summary_table_cell_length = 13;

  // We will use the PIMPL idiom
  class Data;

  std::unique_ptr<Data> d_data;
};

#define __FRENSIE_TEST_CATCH_STATEMENTS__( LOG_STREAM, VERBOSE, SUCCESS_VALUE, CHECKPOINT_LINE_NUMBER, UNEXPECTED_EXCEPTION_COUNTER, RIGHT_SHIFT ) \
  catch( const std::exception& exception )                              \
  {                                                                   \
    SUCCESS_VALUE = false;                                            \
                                                                      \
    ++UNEXPECTED_EXCEPTION_COUNTER;                                   \
                                                                      \
    if( VERBOSE )                                              \
    {                                                               \
      FRENSIE_FLUSH_ALL_LOGS();                                       \
                                                                        \
      std::ostringstream proc_id( "" );                                \
                                                                        \
      if( Utility::GlobalMPISession::size() > 1 )                       \
        proc_id << "on proc " << Utility::GlobalMPISession::rank();    \
                                                                        \
      Utility::logExceptionDetails<RIGHT_SHIFT>( exception, __FILE__, __LINE__, LOG_STREAM, proc_id.str() ); \
                                                                        \
      Utility::logLastCheckpoint<RIGHT_SHIFT>( CHECKPOINT_LINE_NUMBER, LOG_STREAM ); \
    }                                                                   \
  }                                                                     \
                                                                        \
  catch( ... )                                                          \
  {                                                                   \
    SUCCESS_VALUE = false;                                            \
                                                                      \
    ++UNEXPECTED_EXCEPTION_COUNTER;                                   \
                                                                      \
    if( VERBOSE )                                                     \
    {                                                               \
      FRENSIE_FLUSH_ALL_LOGS();                                       \
                                                                      \
      std::ostringstream proc_id( "" );                                \
                                                                        \
      if( Utility::GlobalMPISession::size() > 1 )                       \
        proc_id << "on proc " << Utility::GlobalMPISession::rank();    \
                                                                      \
      Utility::logUnknownExceptionDetails<RIGHT_SHIFT>( __FILE__, __LINE__, LOG_STREAM, proc_id.str() ); \
                                                                        \
      Utility::logLastCheckpoint<RIGHT_SHIFT>( CHECKPOINT_LINE_NUMBER, LOG_STREAM ); \
    }                                                                   \
  }

} // end Utility namespace

#endif // end UTILITY_UNIT_TEST_MANAGER_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestManager.hpp
//---------------------------------------------------------------------------//
