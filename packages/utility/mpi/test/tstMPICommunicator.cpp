//---------------------------------------------------------------------------//
//!
//! \file   tstMPICommunicator.cpp
//! \author Alex Robinson
//! \brief  MPI communicator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_MPICommunicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( MPICommunicator, isValid )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK( comm->isValid() );
}

//---------------------------------------------------------------------------//
// Check that a mpi comm does not use MPI
FRENSIE_UNIT_TEST( MPICommunicator, isMPIUsed )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK( comm->isMPIUsed() );
}

//---------------------------------------------------------------------------//
// Check that the rank can be returned
FRENSIE_UNIT_TEST( MPICommunicator, rank )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->rank(), Utility::GlobalMPISession::rank() );
}

//---------------------------------------------------------------------------//
// Check that the size can be returned
FRENSIE_UNIT_TEST( MPICommunicator, size )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->size(), Utility::GlobalMPISession::size() );
}

//---------------------------------------------------------------------------//
// Check that a barrier can be created
FRENSIE_UNIT_TEST( MPICommunicator, barrier )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_NO_THROW( comm->barrier() );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be split
FRENSIE_UNIT_TEST( MPICommunicator, split )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // Split the comm into two sub-communicators consisting of even and odd
  // ranks
  std::shared_ptr<const Utility::Communicator> sub_comm =
    comm->split( comm->rank()%2 );

  FRENSIE_CHECK_EQUAL( sub_comm->rank(), comm->rank()/2 );
  
  if( comm->rank()%2 == 0 )
  {
    FRENSIE_CHECK_EQUAL( sub_comm->size(), (comm->size()+1)/2 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( sub_comm->size(), comm->size()/2 );
  }

  // Split the comm into two sub-communicators consisting of even and odd
  // ranks - use a custom key value (instead of the rank)
   int custom_key = (comm->rank() == 0 ? comm->size() : comm->rank());

   sub_comm = comm->split( comm->rank()%2, custom_key );

  if( comm->rank()%2 == 0 )
  {
    int expected_sub_rank =
      (comm->rank() == 0 ? (comm->size()+1)/2-1 : comm->rank()/2-1);
    
    FRENSIE_CHECK_EQUAL( sub_comm->rank(), expected_sub_rank );
    FRENSIE_CHECK_EQUAL( sub_comm->size(), (comm->size()+1)/2 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( sub_comm->rank(), comm->rank()/2 );
    FRENSIE_CHECK_EQUAL( sub_comm->size(), comm->size()/2 );
  }
}

//---------------------------------------------------------------------------//
// Check that a timer can be created
FRENSIE_UNIT_TEST( MPICommunicator, createTimer )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_CHECK( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be converted to a string
FRENSIE_UNIT_TEST( MPICommunicator, toString )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::string comm_string = Utility::toString( *comm );
  
  std::string expected_comm_string = "MPI Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( comm_string, expected_comm_string );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be placed in a stream
FRENSIE_UNIT_TEST( MPICommunicator, toStream )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::ostringstream oss;

  Utility::toStream( oss, *comm );

  std::string expected_comm_string = "MPI Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be placed in a stream
FRENSIE_UNIT_TEST( MPICommunicator, ostream_operator )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::ostringstream oss;

  oss << *comm;

  std::string expected_comm_string = "MPI Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );
}

//---------------------------------------------------------------------------//
// Check that the any source value can be returned
FRENSIE_UNIT_TEST( MPICommunicator, anySourceValue )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->anySourceValue(), boost::mpi::any_source );
}

//---------------------------------------------------------------------------//
// Check that the any tag value can be returned
FRENSIE_UNIT_TEST( MPICommunicator, anyTagValue )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->anyTagValue(), boost::mpi::any_tag );
}

//---------------------------------------------------------------------------//
// Check that basic messages can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, send_recv_basic,
                            char, unsigned char, short, unsigned short,
                            int, unsigned int, long, unsigned long,
                            long long, unsigned long long,
                            float, double, std::pair<float,int>,
                            std::pair<double,int>, std::pair<long,int>,
                            std::pair<int,int>, std::pair<short,int> )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
    
    int tag = 0;
    int number_of_values = 10;
    
    if( comm->rank() > 0 )
    {
      std::vector<T> values_to_send( number_of_values, value );

      mpi_comm.send( 0, tag, values_to_send.data(), number_of_values );
    }
    else
    {
      std::vector<T> values_to_receive( number_of_values );
      std::vector<T> expected_values_to_receive( number_of_values, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
          mpi_comm.recv( i, tag, values_to_receive.data(), number_of_values );

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( comm_status->error(), MPI_SUCCESS );
        FRENSIE_CHECK( !comm_status->cancelled() );
        FRENSIE_CHECK( comm_status->success() );
        FRENSIE_CHECK( *comm_status );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<T>( *comm_status ),
                             number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        values_to_receive.clear();
        values_to_receive.resize( number_of_values );
      }
    }

    comm->barrier();
  }
}

//---------------------------------------------------------------------------//
// Check that basic messages can be sent and received
FRENSIE_UNIT_TEST( MPICommunicator, send_recv_string )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    std::string value = "Hello World";
        
    int tag = 0;
    int number_of_values = 10;
    
    if( comm->rank() > 0 )
    {
      std::vector<std::string> values_to_send( number_of_values, value );

      mpi_comm.send( 0, tag, values_to_send.data(), number_of_values );
    }
    else
    {
      std::vector<std::string> values_to_receive( number_of_values );
      std::vector<std::string> expected_values_to_receive( number_of_values, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
          mpi_comm.recv( i, tag, values_to_receive.data(), number_of_values );

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( comm_status->error(), MPI_SUCCESS );
        FRENSIE_CHECK( !comm_status->cancelled() );
        FRENSIE_CHECK( comm_status->success() );
        FRENSIE_CHECK( *comm_status );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<std::string>( *comm_status ),
                             number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        values_to_receive.clear();
        values_to_receive.resize( number_of_values );
      }
    }

    comm->barrier();
  }
}

//---------------------------------------------------------------------------//
// end tstMPICommunicator.cpp
//---------------------------------------------------------------------------//
