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

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_TeuchosUnitTestInitializer.hpp"

int main( int argc, char** argv )
{
  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpi_session( &argc, &argv );

  // Set up the output streams
  std::ostringstream oss;

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::fancyOStream(Teuchos::rcpFromRef(oss));

  out->setProcRankAndSize( mpi_session.getRank(), mpi_session.getNProc() );

  mpi_session.barrier();

  // Initialize the unit test data
  bool success = true;
  
  try{
    Utility::TeuchosUnitTestInitializer::initializeUnitTests( argc, argv, out.get() );
  }
  catch( const std::exception& exception )
  {
    *out << exception.what() << std::endl;
    *out << "End Result: TEST FAILED" << std::endl;

    success = false;
  }

  // Make sure every node initialized successfully
  success = (mpi_session.sum(success ? 0 : 1 ) == 0 ? true : false);

  // Run the unit tests if the initialization was globally successful
  if( success )
  {
    Teuchos::UnitTestRepository::setGloballyReduceTestResult( true );
    
    success = Teuchos::UnitTestRepository::runUnitTests(*out);
  }

  // Report the test results
  out->setOutputToRootOnly( 0 );
    
  if( success )
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  Teuchos::UnitTestRepository::getCLP().printFinalTimerSummary(out.ptr());
  
  // Format the test output
  if( mpi_session.getRank() == 0 )
  {
    Utility::DynamicOutputFormatter formatter( oss.str() );
    formatter.formatTeuchosUnitTestKeywords();

    std::cout << formatter << std::endl;
  }

  return (success ? 0 : 1 );
}

//---------------------------------------------------------------------------//
// end FRENSIE_StandardUnitTestMain.cpp
//---------------------------------------------------------------------------//
