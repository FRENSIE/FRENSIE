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

  //! Flush logs and add to report
  virtual void flushLogsAndAddToReport( std::ostringstream& log,
                                        const std::string& log_header,
                                        const int proc );

  //! Print the help message
  virtual void printHelpMessage();

  //! Print the test details
  virtual void printTestDetails();

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
                                  std::ostringstream& log );

  //! Print failed test summary header
  virtual void printFailedTestSummaryHeader( const std::string& header_end );

  //! Print failed test name
  virtual void printFailedTestName(
                           const std::string& global_failed_test_name,
                           const std::string& test_details,
                           const std::string& padding,
                           const std::set<std::string>& local_failed_tests_set,
                           const bool goto_newline );

  //! Print the unit test stats
  virtual void printUnitTestStats( const std::string& summary_header );

  //! Print the unit test stats
  void printGivenUnitTestStats( const std::string& summary_header,
                                const int number_of_tests,
                                const int number_of_tests_run,
                                const int number_of_tests_passed,
                                const int number_of_checks,
                                const int number_of_passed_checks,
                                const int number_of_unexpected_exceptions,
                                const double total_test_exec_time );

  //! Print the program execution time header
  virtual void printProgramExecutionTimeHeader(
                                         const double program_execution_time );

  //! Print the test result header
  virtual void printTestResult( const std::string& header,
                                const bool local_success,
                                const bool global_success );

  //! Check if the test details should be reported
  bool shouldUnitTestDetailsBeReported( const bool success ) const;

private:

  // Check if the unit test should be run
  bool shouldUnitTestBeRun( const UnitTest& unit_test );

  // Run the registered unit tets
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

  // Summarize the initialization results
  void summarizeInitializationResults(
                                    std::ostringstream& log,
                                    const double initialization_time,
                                    const bool local_success,
                                    const bool global_success );

  // Summarize failed tests
  void summarizeFailedTests(
                         const std::vector<std::string>& global_failed_tests,
                         const std::set<std::string>& local_failed_tests_set );

  // Summarize the test results
  void summarizeTestStats( const double program_execution_time,
                           const bool local_success,
                           const bool global_success );

  //! Summarize the results
  int summarizeResults( const bool local_success,
                        const bool global_success );

  // The Initializer class is a friend
  friend class UnitTestManager::Initializer;

  // Manager instance
  static std::unique_ptr<UnitTestManager> s_instance;

  // The starting right shift for test details
  static constexpr int s_details_right_shift = 2;

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
