//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicator.cpp
//! \author Alex Robinson
//! \brief  Communicator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( Communicator, getDefault )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_REQUIRE( comm.get() != NULL );
  FRENSIE_REQUIRE( comm->isValid() );
  FRENSIE_REQUIRE( *comm );
  FRENSIE_CHECK_EQUAL( comm->rank(), Utility::GlobalMPISession::rank() );
  FRENSIE_CHECK_EQUAL( comm->size(), Utility::GlobalMPISession::size() );
  FRENSIE_CHECK_EQUAL( comm->isMPIUsed(), Utility::GlobalMPISession::isMPIUsed() );

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_REQUIRE( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// end tstCommunicator.cpp
//---------------------------------------------------------------------------//
