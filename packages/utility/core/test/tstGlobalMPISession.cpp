//---------------------------------------------------------------------------//
//!
//! \file   tstGlobalMPISession.cpp
//! \author Alex Robinson
//! \brief  Global MPI session unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_GlobalMPISession.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the mpi session can be initialized and finalized correctly
BOOST_AUTO_TEST_CASE( initialize_finalize )
{
#ifdef HAVE_FRENSIE_MPI
  BOOST_CHECK( !Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

  {
    Utility::GlobalMPISession session;

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
  }

  BOOST_CHECK( Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( Utility::GlobalMPISession::finalized() );
#else
  BOOST_CHECK( Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

  {
    Utility::GlobalMPISession session;

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
  }

  BOOST_CHECK( Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
#endif
}

//---------------------------------------------------------------------------//
// end tstGlobalMPISession.cpp
//---------------------------------------------------------------------------//
