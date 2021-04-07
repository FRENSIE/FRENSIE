//---------------------------------------------------------------------------//
//!
//! \file   tstGlobalMPISessionInit.cpp
//! \author Alex Robinson
//! \brief  Global MPI session initialization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

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

  std::string constructor_type = "default";

  if( boost::unit_test::framework::master_test_suite().argc >= 2 )
  {
    std::string constructor_type_input =
      boost::unit_test::framework::master_test_suite().argv[1];

    std::vector<std::string> constructor_type_input_elements;

    boost::split( constructor_type_input_elements,
                  boost::unit_test::framework::master_test_suite().argv[1],
                  boost::is_any_of( "=" ) );

    if( constructor_type_input_elements.size() == 2 )
      constructor_type = constructor_type_input_elements[1];
  }

  if( constructor_type == "default" )
  {
    Utility::GlobalMPISession session;

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
  }
  else if( constructor_type == "advanced" )
  {
    Utility::GlobalMPISession session(
                       boost::unit_test::framework::master_test_suite().argc,
                       boost::unit_test::framework::master_test_suite().argv );

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
  }
  else if( constructor_type == "basic_single" )
  {
    Utility::GlobalMPISession
      session( Utility::GlobalMPISession::SingleThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::threadLevel(),
                       Utility::GlobalMPISession::SingleThreading );
    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::thread_level(),
                       Utility::GlobalMPISession::SingleThreading );
  }
  else if( constructor_type == "advanced_single" )
  {
    Utility::GlobalMPISession
      session( boost::unit_test::framework::master_test_suite().argc,
               boost::unit_test::framework::master_test_suite().argv,
               Utility::GlobalMPISession::SingleThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::threadLevel(),
                       Utility::GlobalMPISession::SingleThreading );
    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::thread_level(),
                       Utility::GlobalMPISession::SingleThreading );
  }
  else if( constructor_type == "basic_funneled" )
  {
    Utility::GlobalMPISession
      session( Utility::GlobalMPISession::FunneledThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::threadLevel(),
                       Utility::GlobalMPISession::FunneledThreading );
    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::thread_level(),
                       Utility::GlobalMPISession::FunneledThreading );
  }
  else if( constructor_type == "advanced_funneled" )
  {
    Utility::GlobalMPISession
      session( boost::unit_test::framework::master_test_suite().argc,
               boost::unit_test::framework::master_test_suite().argv,
               Utility::GlobalMPISession::FunneledThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::threadLevel(),
                       Utility::GlobalMPISession::FunneledThreading );
    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::thread_level(),
                       Utility::GlobalMPISession::FunneledThreading );
  }
  else if( constructor_type == "basic_serialized" )
  {
    Utility::GlobalMPISession
      session( Utility::GlobalMPISession::SerializedThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::threadLevel(),
                       Utility::GlobalMPISession::SerializedThreading );
    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::thread_level(),
                       Utility::GlobalMPISession::SerializedThreading );
  }
  else if( constructor_type == "advanced_serialized" )
  {
    Utility::GlobalMPISession
      session( boost::unit_test::framework::master_test_suite().argc,
               boost::unit_test::framework::master_test_suite().argv,
               Utility::GlobalMPISession::SerializedThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::threadLevel(),
                       Utility::GlobalMPISession::SerializedThreading );
    BOOST_CHECK_EQUAL( Utility::GlobalMPISession::thread_level(),
                       Utility::GlobalMPISession::SerializedThreading );
  }
  else if( constructor_type == "basic_multiple" )
  {
    Utility::GlobalMPISession
      session( Utility::GlobalMPISession::MultipleThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK( Utility::GlobalMPISession::threadLevel() ==
                 Utility::GlobalMPISession::MultipleThreading ||
                 Utility::GlobalMPISession::threadLevel() ==
                 Utility::GlobalMPISession::SerializedThreading );
    BOOST_CHECK( Utility::GlobalMPISession::thread_level() ==
                 Utility::GlobalMPISession::MultipleThreading ||
                 Utility::GlobalMPISession::threadLevel() ==
                 Utility::GlobalMPISession::SerializedThreading );
  }
  else if( constructor_type == "advanced_multiple" )
  {
    Utility::GlobalMPISession
      session( boost::unit_test::framework::master_test_suite().argc,
               boost::unit_test::framework::master_test_suite().argv,
               Utility::GlobalMPISession::MultipleThreading );
    session.barrier();

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

    BOOST_CHECK( Utility::GlobalMPISession::threadLevel() ==
                 Utility::GlobalMPISession::MultipleThreading ||
                 Utility::GlobalMPISession::threadLevel() ==
                 Utility::GlobalMPISession::SerializedThreading );
    BOOST_CHECK( Utility::GlobalMPISession::thread_level() ==
                 Utility::GlobalMPISession::MultipleThreading ||
                 Utility::GlobalMPISession::threadLevel() ==
                 Utility::GlobalMPISession::SerializedThreading );
  }
  else
  {
    BOOST_FAIL( std::string("Unknown constructor requested: ") + constructor_type );
  }

  BOOST_CHECK( Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( Utility::GlobalMPISession::finalized() );
#else // HAVE_FRENSIE_MPI
  BOOST_CHECK( Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( !Utility::GlobalMPISession::finalized() );

  {
    Utility::GlobalMPISession session;

    BOOST_CHECK( Utility::GlobalMPISession::initialized() );
    BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
  }

  BOOST_CHECK( Utility::GlobalMPISession::initialized() );
  BOOST_CHECK( !Utility::GlobalMPISession::finalized() );
#endif // end HAVE_FRENSIE_MPI
}

//---------------------------------------------------------------------------//
// end tstGlobalMPISessionInit.cpp
//---------------------------------------------------------------------------//
