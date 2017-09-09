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
#include "Utility_ToStringTraits.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
struct InitFixture
{
  InitFixture()
    : mpi_session( boost::unit_test::framework::master_test_suite().argc,
                   boost::unit_test::framework::master_test_suite().argv )
  { /* ... */ }

  Utility::GlobalMPISession mpi_session;
};

// Register the InitFixture with the test suite
BOOST_FIXTURE_TEST_SUITE( GlobalMPISession, InitFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an output stream can be initialized
BOOST_AUTO_TEST_CASE( initializeOutputStream )
{
  boost::shared_ptr<std::ostream> oss( new std::ostringstream );

  mpi_session.initializeOutputStream( oss );

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();

  BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(), std::string("Hello from ") + Utility::toString( Utility::GlobalMPISession::rank() ) );

  dynamic_cast<std::ostringstream*>(oss.get())->str( "" );
  oss->clear();

  mpi_session.initializeOutputStream( oss, 0, true );

  (*oss) << "Hello from " << Utility::GlobalMPISession::rank();

  if( Utility::GlobalMPISession::rank() == 0 )
  {
    BOOST_CHECK_EQUAL( dynamic_cast<std::ostringstream*>(oss.get())->str(),
                       "Hello from 0" );
  }
  else
  {
    BOOST_CHECK( dynamic_cast<std::ostringstream*>(oss.get())->str().empty() );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstGlobalMPISession.cpp
//---------------------------------------------------------------------------//
