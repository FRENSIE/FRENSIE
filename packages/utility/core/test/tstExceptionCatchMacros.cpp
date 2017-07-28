//---------------------------------------------------------------------------//
//!
//! \file   tstExceptionCatchMacros.cpp
//! \author Alex Robinson
//! \brief  Exception catch macros unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <vector>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the caught exception can be properly logged
BOOST_AUTO_TEST_CASE( std_exception_catch_error_logging )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_STANDARD_SYNCHRONOUS_LOGS( os_array );

  std::cout << std::endl;
  try{
    try{
      TEST_FOR_EXCEPTION( true, std::logic_error, "testing 1" );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                std::runtime_error,
                                "testing 2");
  }
  EXCEPTION_CATCH_AND_LOG( std::runtime_error, "testing 3" );
  
  BOOST_CHECK( os_ptr->str().find( "Caught Exception Error: testing 3" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Exception Type: std::runtime_error" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Beginning nested errors..." ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Error: testing 2" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Exception Type: std::logic_error  ->  std::runtime_error" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Error: testing 1" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Throw test that evaluated to true: true" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Exception Type: std::logic_error" ) <
               os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Location: " ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "Stack: " ) < os_ptr->str().size() );
  BOOST_CHECK( os_ptr->str().find( "**" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// end tstExceptionCatchMacros.cpp
//---------------------------------------------------------------------------//
