//---------------------------------------------------------------------------//
//!
//! \file   FRENSIE_StandardUnitTestMain.cpp
//! \author Alex Robinson
//! \brief  The standard unit test main for FRENSIE style formatting
//!
//---------------------------------------------------------------------------//

/*! \brief Standard FRENSIE unit testing main program.
 *
 * This file should be used as a standard main program for FRENSIE unit
 * test executables. This program takes care of FRENSIE fancy test output
 * formatting. If the fancy output is not desired, the main program in
 * Teuchos_StandardUnitTestMain.cpp can be used instead.
 */

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <vector>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_TeuchosUnitTestInitializer.hpp"
#include "Utility_LoggingMacros.hpp"

// Report local failure details
void reportLocalFailureDetails( const bool local_success,
                                std::ostringstream& oss )
{
  for( size_t i = 0; i < Teuchos::GlobalMPISession::getNProc(); ++i )
  {
    if( Teuchos::GlobalMPISession::getRank() == i )
    {
      if( !local_success )
      {
        oss << "\nProcess " << i << " Result: TEST FAILED";

        // Format the test output     
        Utility::DynamicOutputFormatter formatter( oss.str() );
        formatter.formatTeuchosUnitTestKeywords();
        
        std::cout << formatter << "\n";

        // Clear the stream
        oss.str( "" );
        oss.clear();
      }
      else
      {
        // Clear the stream (except root)
        if( i != 0 )
        {
          oss.str( "" );
          oss.clear();
        }
      }
    }

    Teuchos::GlobalMPISession::barrier();
  }
}

// Summarize local test results
void summarizeLocalResults( const bool local_success,
                            std::ostringstream& oss )
{
  for( size_t i = 0; i < Teuchos::GlobalMPISession::getNProc(); ++i )
  {
    if( Teuchos::GlobalMPISession::getRank() == i )
    {
      if( i == 0 )
      {
        std::cout << "\n"
                  << Utility::Underlined( "Local Results Summary" )
                  << "\n";
      }
      
      if( !local_success )
        oss << "Process " << i << " Result: TEST FAILED (see details above)";
      else
        oss << "Process " << i << " Result: TEST PASSED";
      
      Utility::DynamicOutputFormatter formatter( oss.str() );
      formatter.formatTeuchosUnitTestKeywords();
      
      std::cout << formatter << "\n";

      oss.str( "" );
      oss.clear();
    }

    Teuchos::GlobalMPISession::barrier();
  }
}

// The standard unit test main
int main( int argc, char** argv )
{
  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpi_session( &argc, &argv );

  // Set up the output streams
  std::ostringstream oss;

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::fancyOStream(Teuchos::rcpFromRef(oss));

  out->setProcRankAndSize( mpi_session.getRank(), mpi_session.getNProc() );

  // Set up the logs
  FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES();

  {
    boost::shared_ptr<std::ostream>
      log_stream( out.get(), boost::null_deleter() );
      //log_stream( &std::cout, boost::null_deleter() );
  
    FRENSIE_SETUP_STANDARD_LOGS( log_stream );
  }

  FRENSIE_LOG_TAGGED_NOTIFICATION( "Testing", "Logger initialized" );
  FRENSIE_FLUSH_ALL_LOGS();
  
  mpi_session.barrier();

  // Initialize the unit test data
  bool success = true;
  
  try{
    Utility::TeuchosUnitTestInitializer::initializeUnitTests( argc, argv, out.get() );
  }
  catch( const std::exception& exception )
  {
    *out << exception.what() << "\n";

    success = false;
  }

  // Make sure every node initialized successfully
  success = (mpi_session.sum(success ? 0 : 1 ) == 0 ? true : false);

  // Record if the unit tests passed on this node
  bool local_unit_test_success = success;

  // Run the unit tests if the initialization was globally successful
  if( success )
  {
    // The unit test repository can reduce the test results for you. We will
    // not do this since we want to keep track of local success/failure so
    // that we can format the local output upon failure
    Teuchos::UnitTestRepository::setGloballyReduceTestResult( false );
    
    local_unit_test_success = Teuchos::UnitTestRepository::runUnitTests(*out);

    success =
      (mpi_session.sum(local_unit_test_success ? 0 : 1) == 0 ? true : false);
  }

  FRENSIE_FLUSH_ALL_LOGS();

  // Report local failure details
  if( mpi_session.getNProc() > 1 )
    reportLocalFailureDetails( local_unit_test_success, oss );

  // Report global results if on the root process
  if( mpi_session.getRank() == 0 )
  {
    Utility::DynamicOutputFormatter formatter( oss.str() );
    formatter.formatTeuchosUnitTestKeywords();

    std::cout << formatter;

    // Clear the stream
    oss.str( "" );
    oss.clear();
  }

  FRENSIE_FLUSH_ALL_LOGS();

  // Summarize the local results
  if( mpi_session.getNProc() > 1 )
    summarizeLocalResults( local_unit_test_success, oss );

  // Summarize the global results
  if( mpi_session.getRank() == 0 )
  {
    if( success )
      *out << "\nEnd Result: TEST PASSED" << std::endl;
    else
      *out << "\nEnd Result: TEST FAILED" << std::endl;
    
    Teuchos::UnitTestRepository::getCLP().printFinalTimerSummary(out.ptr());

    Utility::DynamicOutputFormatter formatter( oss.str() );
    formatter.formatTeuchosUnitTestKeywords();

    std::cout << formatter << std::endl;
  }

  FRENSIE_FLUSH_ALL_LOGS();
  FRENSIE_REMOVE_ALL_LOGS();

  return (success ? 0 : 1 );
}

//---------------------------------------------------------------------------//
// end FRENSIE_StandardUnitTestMain.cpp
//---------------------------------------------------------------------------//
