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
#include "Utility_LoggingMacros.hpp"

namespace Utility{

//! The unit test manager
class UnitTestManager
{

public:

  //! The initializer
  class Initializer
  {
    
  public:

    //! Constructor
    Initializer();

    //! Initialize the unit test manager
    void initializeUnitTestManager( int argc, char** argv );

    //! Destructor
    virtual ~Initializer()
    { /* ... */ }

  protected:

    //! Get command line option value
    template<typename T>
    T getOptionValue( const std::string& option_name ) const
    { return this->getRawOptionValue( option_name ).as<T>(); }

    //! Set the custom command line options
    virtual void setCustomCommandLineOptions();

    //! Custom manager initialization method
    virtual void customUnitTestManagerInitialization() const;

    //! Shortcut for adding command line options (functor)
    boost::program_options::options_description_easy_init setOption;

  private:

    //! Get command line option raw value
    boost::program_options::variable_value
    getRawOptionValue( const std::string& option_name ) const;
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
  int runUnitTests( int* argc, char*** argv );

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
                                       const size_t line_number );

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
                           const std::set<std::string>& local_failed_tests_set,
                           const bool goto_newline );

  //! Print the unit test stats
  virtual void printUnitTestStats( const std::string& summary_header );

  //! Print the unit test stats
  void printGivenUnitTestStats( const std::string& summary_header,
                                const int number_of_tests,
                                const int number_of_tests_run,
                                const int number_of_tests_passed,
                                const double total_test_exec_time );

  //! Print the program execution time header
  virtual void printProgramExecutionTimeHeader(
                                         const double program_execution_time );

  //! Return the number of tests
  int getNumberOfTests() const;

  //! Return the current number of run tests
  int getNumberOfRunTests() const;

  //! Return the current number of passed tests
  int getNumberOfPassedTests() const;

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
                         std::set<std::string>& local_failed_tests_set );

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

  // We will use the PIMPL idiom
  class Data;

  std::unique_ptr<Data> d_data;
};

#define FRENSIE_TEST_CATCH_STATEMENTS( LOG_STREAM, VERBOSE, SUCCESS_VALUE, CHECKPOINT_LINE_NUMBER ) \
  catch( const std::exception& exception )                              \
  {                                                                   \
    SUCCESS_VALUE = false;                                            \
                                                                      \
    if( VERBOSE )                                              \
    {                                                               \
      FRENSIE_FLUSH_ALL_LOGS();                                       \
                                                                      \
      LOG_STREAM << "Caught unexpected std::exception";              \
                                                                        \
      if( Utility::GlobalMPISession::getSize() > 1 )                    \
        LOG_STREAM << " on proc " << Utility::GlobalMPISession::getRank(); \
                                                                        \
      if( CHECKPOINT_LINE_NUMBER > 0 )                                  \
      {                                                               \
          LOG_STREAM << "(last checkpoint at line "                     \
                     << CHECKPOINT_LINE_NUMBER << ")";               \
      }                                                            \
                                                                     \
      LOG_STREAM << "!\n" << exception.what() << std::flush;         \
    }                                                                   \
  }                                                                     \
                                                                        \
  catch( ... )                                                          \
  {                                                                   \
    SUCCESS_VALUE = false;                                            \
                                                                      \
    if( VERBOSE )                                              \
    {                                                               \
      FRENSIE_FLUSH_ALL_LOGS();                                       \
                                                                      \
      LOG_STREAM << "Caught unexpected unknown exception";           \
                                                                        \
      if( Utility::GlobalMPISession::getSize() > 1 )                  \
        LOG_STREAM << " on proc " << Utility::GlobalMPISession::getRank(); \
                                                                        \
      LOG_STREAM << "!"<< std::endl;                                   \
    }                                                                   \
  }
  
} // end Utility namespace

#endif // end UTILITY_UNIT_TEST_MANAGER_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestManager.hpp
//---------------------------------------------------------------------------//
