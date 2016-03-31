//---------------------------------------------------------------------------//
//!
//! \file   tstMpiCommHelpers.cpp
//! \author Alex Robinson
//! \brief  Comm helper and extensions mpi unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>

// FRENSIE Includes
#include "Utility_CommHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm;

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )   \
  typedef long long int64;            \
  typedef unsigned long long uint64;            \
  typedef unsigned long uint32;                 \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int64 )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint32 )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint64 )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_source_no_status,
                                   Ordinal )
{
  // No message sent yet
  if( comm->getRank() == 0 )
  {
    TEST_ASSERT( !Utility::iprobe( *comm, 0 ) );
    if( comm->getSize() > 1 )
      TEST_ASSERT( !Utility::iprobe( *comm, 1 ) );
    if( comm->getSize() > 2 )
      TEST_ASSERT( !Utility::iprobe( *comm, 2 ) );
    if( comm->getSize() > 3 )
      TEST_ASSERT( !Utility::iprobe( *comm, 4 ) );
  }

  comm->barrier();

  // Send messages and probe
  if( comm->getRank() != 0 )
  {
    double message = 1.0;
    
    Teuchos::send( *comm, message, 0 );
  }
  else
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 1 ) );

      Teuchos::receive( *comm, 1, &message );
    }
    if( comm->getSize() > 2 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 2 ) );

      Teuchos::receive( *comm, 2, &message );
    }
    if( comm->getSize() > 3 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 3 ) );

      Teuchos::receive( *comm, 3, &message );
    }
  }

  comm->barrier();
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_source_no_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_source_status,
                                   Ordinal )
{
  
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_source_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_no_status,
                                   Ordinal )
{
  
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_no_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_status,
                                   Ordinal )
{
  
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_status );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   probe_source,
                                   Ordinal )
{
  
}

UNIT_TEST_INSTANTIATION( CommHelpers, probe_source );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   probe,
                                   Ordinal )
{
  
}

UNIT_TEST_INSTANTIATION( CommHelpers, probe );

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );

  mpiSession.barrier();

  // Initialize the mpi comm
  comm = Teuchos::DefaultComm<unsigned long long>::getComm();

  // Run the unit tests
  Teuchos::UnitTestRepository::setGloballyReduceTestResult( true );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  mpiSession.barrier();

  out->setOutputToRootOnly( 0 );

  if( success )
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstMpiCommHelpers.cpp
//---------------------------------------------------------------------------//
