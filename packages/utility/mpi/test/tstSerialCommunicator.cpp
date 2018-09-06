//---------------------------------------------------------------------------//
//!
//! \file   tstSerialCommunicator.cpp
//! \author Alex Robinson
//! \brief  Communicator unit tests
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SerialCommunicator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a serial comm is valid
FRENSIE_UNIT_TEST( SerialCommunicator, isValid )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  FRENSIE_CHECK( comm->isValid() );
}

//---------------------------------------------------------------------------//
// Check that a serial comm does not use MPI
FRENSIE_UNIT_TEST( SerialCommunicator, isMPIUsed )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  FRENSIE_CHECK( !comm->isMPIUsed() );
}

//---------------------------------------------------------------------------//
// Check that the rank is always 0
FRENSIE_UNIT_TEST( SerialCommunicator, rank )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  FRENSIE_CHECK_EQUAL( comm->rank(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the size is always 1
FRENSIE_UNIT_TEST( SerialCommunicator, size )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  FRENSIE_CHECK_EQUAL( comm->size(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a barrier can be created
FRENSIE_UNIT_TEST( SerialCommunicator, barrier )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  FRENSIE_CHECK_NO_THROW( comm->barrier() );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be split
FRENSIE_UNIT_TEST( SerialCommunicator, split )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  // The color should be ignored
  std::shared_ptr<const Utility::Communicator> new_comm = comm->split( 0 );

  FRENSIE_REQUIRE( new_comm.get() != NULL );
  FRENSIE_REQUIRE( new_comm->isValid() );
  FRENSIE_REQUIRE( *new_comm != *Utility::Communicator::getNull() );
  FRENSIE_CHECK( *new_comm == *comm );
  FRENSIE_CHECK_EQUAL( new_comm->rank(), 0 );
  FRENSIE_CHECK_EQUAL( new_comm->size(), 1 );

  // The color and key should be ignored
  new_comm = comm->split( 0, 0 );

  FRENSIE_REQUIRE( new_comm.get() != NULL );
  FRENSIE_REQUIRE( new_comm->isValid() );
  FRENSIE_REQUIRE( *new_comm != *Utility::Communicator::getNull() );
  FRENSIE_CHECK( *new_comm == *comm );
  FRENSIE_CHECK_EQUAL( new_comm->rank(), 0 );
  FRENSIE_CHECK_EQUAL( new_comm->size(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a timer can be created
FRENSIE_UNIT_TEST( SerialCommunicator, createTimer )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_CHECK( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be converted to a string
FRENSIE_UNIT_TEST( SerialCommunicator, toString )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();

  std::string comm_string = Utility::toString( *comm );

  FRENSIE_CHECK_EQUAL( comm_string, "Serial Communicator" );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be placed in a stream
FRENSIE_UNIT_TEST( SerialCommunicator, toStream )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();
  
  std::ostringstream oss;

  Utility::toStream( oss, *comm );

  FRENSIE_CHECK_EQUAL( oss.str(), "Serial Communicator" );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be placed in a stream
FRENSIE_UNIT_TEST( SerialCommunicator, ostream_operator )
{
  std::shared_ptr<const Utility::Communicator> comm = 
    Utility::SerialCommunicator::get();
  
  std::ostringstream oss;

  oss << *comm;

  FRENSIE_CHECK_EQUAL( oss.str(), "Serial Communicator" );
}

//---------------------------------------------------------------------------//
// end tstSerialCommunicator.cpp
//---------------------------------------------------------------------------//
