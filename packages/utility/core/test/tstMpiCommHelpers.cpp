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

#define UNIT_TEST_2_INSTANTIATION( type, name ) \
  typedef long long int64;                      \
  typedef unsigned long long uint64;            \
  typedef unsigned long uint32;                 \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int64, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, unsigned, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uint32, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uint64, double )    \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, float )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int )          \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, long )         \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int64 )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, unsigned )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, uint32 )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, uint64 )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, char )         \

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_source_no_status,
                                   Ordinal )
{
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();
  
  // No message sent yet
  if( comm->getRank() == 0 )
  {
    TEST_ASSERT( !Utility::iprobe( *comm, 0 ) );
    if( comm->getSize() > 1 )
      TEST_ASSERT( !Utility::iprobe( *comm, 1 ) );
    if( comm->getSize() > 2 )
      TEST_ASSERT( !Utility::iprobe( *comm, 2 ) );
    if( comm->getSize() > 3 )
      TEST_ASSERT( !Utility::iprobe( *comm, 3 ) );
  }

  comm->barrier();

  // Send messages
  if( comm->getRank() != 0 && comm->getRank() < 4 )
  {
    Teuchos::RCP<const double> message( new double( comm->getRank() ) );

    Teuchos::RCP<Teuchos::CommRequest<Ordinal> > request =
      Teuchos::isend( *comm, message, 0 );
  }

  comm->barrier();

  // Probe for and receive messages
  if( comm->getRank() == 0 )
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 1 ) );

      Teuchos::receive( *comm, 1, &message );

      TEST_EQUALITY_CONST( message, 1.0 );
    }
    if( comm->getSize() > 2 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 2 ) );

      Teuchos::receive( *comm, 2, &message );

      TEST_EQUALITY_CONST( message, 2.0 );
    }
    if( comm->getSize() > 3 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 3 ) );

      Teuchos::receive( *comm, 3, &message );

      TEST_EQUALITY_CONST( message, 3.0 );
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
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;
  
  // No message sent yet
  if( comm->getRank() == 0 )
  {
    TEST_ASSERT( !Utility::iprobe( *comm, 0, status ) );
    if( comm->getSize() > 1 )
      TEST_ASSERT( !Utility::iprobe( *comm, 1, status ) );
    if( comm->getSize() > 2 )
      TEST_ASSERT( !Utility::iprobe( *comm, 2, status ) );
    if( comm->getSize() > 3 )
      TEST_ASSERT( !Utility::iprobe( *comm, 3, status ) );
  }

  comm->barrier();

  // Send messages
  if( comm->getRank() != 0 && comm->getRank() < 4 )
  {
    Teuchos::RCP<const double> message( new double( comm->getRank() ) );

    Teuchos::RCP<Teuchos::CommRequest<Ordinal> > request =
      Teuchos::isend( *comm, message, 0 );
  }

  comm->barrier();

  // Probe for and receive messages
  if( comm->getRank() == 0 )
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 1, status ) );
      TEST_EQUALITY_CONST( status->getSourceRank(), 1 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );
      
      Teuchos::receive( *comm, 1, &message );

      TEST_EQUALITY_CONST( message, 1.0 );
    }
    if( comm->getSize() > 2 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 2, status ) );
      TEST_EQUALITY_CONST( status->getSourceRank(), 2 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, 2, &message );

      TEST_EQUALITY_CONST( message, 2.0 );
    }
    if( comm->getSize() > 3 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 3, status ) );
      TEST_EQUALITY_CONST( status->getSourceRank(), 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, 3, &message );

      TEST_EQUALITY_CONST( message, 3.0 );
    }
  }

  comm->barrier();
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_source_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_no_status,
                                   Ordinal )
{
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();
  
  // No message sent yet
  if( comm->getRank() == 0 )
    TEST_ASSERT( !Utility::iprobe( *comm ) );

  comm->barrier();

  // Send messages
  if( comm->getRank() != 0 && comm->getRank() < 4 )
  {
    Teuchos::RCP<const double> message( new double( comm->getRank() ) );

    Teuchos::RCP<Teuchos::CommRequest<Ordinal> > request =
      Teuchos::isend( *comm, message, 0 );
  }

  comm->barrier();

  // Probe for and receive messages
  if( comm->getRank() == 0 )
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      TEST_ASSERT( Utility::iprobe( *comm ) );

      Teuchos::receive( *comm, 1, &message );

      TEST_EQUALITY_CONST( message, 1.0 );
    }
    if( comm->getSize() > 2 )
    {
      TEST_ASSERT( Utility::iprobe( *comm ) );

      Teuchos::receive( *comm, 2, &message );

      TEST_EQUALITY_CONST( message, 2.0 );
    }
    if( comm->getSize() > 3 )
    {
      TEST_ASSERT( Utility::iprobe( *comm ) );

      Teuchos::receive( *comm, 3, &message );

      TEST_EQUALITY_CONST( message, 3.0 );
    }
  }

  comm->barrier();
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_no_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_status,
                                   Ordinal )
{
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;
  
  // No message sent yet
  if( comm->getRank() == 0 )
    TEST_ASSERT( !Utility::iprobe( *comm, status ) );

  comm->barrier();

  // Send messages
  if( comm->getRank() != 0 && comm->getRank() < 4 )
  {
    Teuchos::RCP<const double> message( new double( comm->getRank() ) );

    Teuchos::RCP<Teuchos::CommRequest<Ordinal> > request =
      Teuchos::isend( *comm, message, 0 );
  }

  comm->barrier();

  // Probe for and receive messages
  if( comm->getRank() == 0 )
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, status ) );
      TEST_COMPARE( status->getSourceRank(), >=, 1 );
      TEST_COMPARE( status->getSourceRank(), <=, 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );
      
      Teuchos::receive( *comm, status->getSourceRank(), &message );

      TEST_EQUALITY_CONST( message, (double)status->getSourceRank() );
    }
    if( comm->getSize() > 2 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, status ) );
      TEST_COMPARE( status->getSourceRank(), >=, 1 );
      TEST_COMPARE( status->getSourceRank(), <=, 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, status->getSourceRank(), &message );

      TEST_EQUALITY_CONST( message, (double)status->getSourceRank() );
    }
    if( comm->getSize() > 3 )
    {
      TEST_ASSERT( Utility::iprobe( *comm, 3, status ) );
      TEST_COMPARE( status->getSourceRank(), >=, 1 );
      TEST_COMPARE( status->getSourceRank(), <=, 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, status->getSourceRank(), &message );

      TEST_EQUALITY_CONST( message, (double)status->getSourceRank() );
    }
  }

  comm->barrier();
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_status );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   probe_source,
                                   Ordinal )
{
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;
  
  // Send messages
  if( comm->getRank() != 0 && comm->getRank() < 4 )
  {
    double message = comm->getRank();

    Teuchos::send( *comm, message, 0 );
  }
  // Probe for and receive messages
  else if( comm->getRank() == 0 )
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      Utility::probe( *comm, 1, status );
      TEST_EQUALITY_CONST( status->getSourceRank(), 1 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );
      
      Teuchos::receive( *comm, 1, &message );

      TEST_EQUALITY_CONST( message, 1.0 );
    }
    if( comm->getSize() > 2 )
    {
      Utility::probe( *comm, 2, status );
      TEST_EQUALITY_CONST( status->getSourceRank(), 2 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, 2, &message );

      TEST_EQUALITY_CONST( message, 2.0 );
    }
    if( comm->getSize() > 3 )
    {
      Utility::probe( *comm, 3, status );
      TEST_EQUALITY_CONST( status->getSourceRank(), 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, 3, &message );

      TEST_EQUALITY_CONST( message, 3.0 );
    }
  }

  comm->barrier();
}

UNIT_TEST_INSTANTIATION( CommHelpers, probe_source );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   probe,
                                   Ordinal )
{
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;
  
  // Send messages
  if( comm->getRank() != 0 && comm->getRank() < 4 )
  {
    double message = comm->getRank();

    Teuchos::send( *comm, message, 0 );
  }
  // Probe for and receive messages
  else if( comm->getRank() == 0 )
  {
    double message = 0.0;
    
    if( comm->getSize() > 1 )
    {
      Utility::probe( *comm, status );
      TEST_COMPARE( status->getSourceRank(), >=, 1 );
      TEST_COMPARE( status->getSourceRank(), <=, 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );
      
      Teuchos::receive( *comm, status->getSourceRank(), &message );

      TEST_EQUALITY_CONST( message, (double)status->getSourceRank() );
    }
    if( comm->getSize() > 2 )
    {
      Utility::probe( *comm, status );
      TEST_COMPARE( status->getSourceRank(), >=, 1 );
      TEST_COMPARE( status->getSourceRank(), <=, 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, status->getSourceRank(), &message );

      TEST_EQUALITY_CONST( message, (double)status->getSourceRank() );
    }
    if( comm->getSize() > 3 )
    {
      Utility::probe( *comm, status );
      TEST_COMPARE( status->getSourceRank(), >=, 1 );
      TEST_COMPARE( status->getSourceRank(), <=, 3 );
      TEST_EQUALITY_CONST( Utility::getMessageSize<double>( *status ), 1 );

      Teuchos::receive( *comm, status->getSourceRank(), &message );

      TEST_EQUALITY_CONST( message, (double)status->getSourceRank() );
    }
  }

  comm->barrier();
}

UNIT_TEST_INSTANTIATION( CommHelpers, probe );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( CommHelpers,
                                   getMessageSize,
                                   Ordinal,
                                   Packet )
{
  Teuchos::RCP<const Teuchos::Comm<Ordinal> > comm =
    Teuchos::DefaultComm<Ordinal>::getComm();

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;

  // Send a message
  if( comm->getRank() == 1 )
  {
    Teuchos::Array<Packet> message( 100 );
    
    Teuchos::send( *comm, (Ordinal)message.size(), message.getRawPtr(), 0 );
  }
  // Probe to get the message size
  else if( comm->getRank() == 0 )
  {
    if( comm->getSize() > 1 )
    {
      Utility::probe( *comm, status );

      int message_size = Utility::getMessageSize<Packet>( *status );
      
      TEST_EQUALITY_CONST( message_size, 100 );

      Teuchos::Array<Packet> message( message_size );
      
      Teuchos::receive( *comm, 1, (Ordinal)message_size, message.getRawPtr() );
    }
  }

  comm->barrier();
}

UNIT_TEST_2_INSTANTIATION( CommHelpers, getMessageSize );

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
