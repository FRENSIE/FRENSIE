//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5ExceptionCatchMacros.cpp
//! \author Alex Robinson
//! \brief  HDF5 exception catch macros unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_FancyOStream.hpp>

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_HDF5ExceptionCatchMacros.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the error logs can handle HDF5 exception info
TEUCHOS_UNIT_TEST( LoggingMacros, hdf5_rethrow_exception_catch_error_logging )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &out, boost::null_deleter() );

  FRENSIE_SETUP_STANDARD_LOGS( os_array );

  out << std::endl;
  try{
    try{
      throw H5::Exception( "dummy_h5_func", "dummy hdf5 message" );
    }
    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::runtime_error, "testing 1");
  }
  EXCEPTION_CATCH_AND_LOG( std::runtime_error, "testing 2" );

  TEST_ASSERT( os_ptr->str().find( "Caught Exception Error: testing 2" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Exception Type: std::runtime_error" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Beginning nested errors..." ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Error: testing 1" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Exception Type: H5::Exception  ->  std::runtime_error" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "HDF5 Stack: dummy_h5_func" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "HDF5 Error Msg: dummy hdf5 message" ) <
               os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that the error logs can handle HDF5 exception info
TEUCHOS_UNIT_TEST( LoggingMacros, hdf5_exception_catch_error_logging )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &out, boost::null_deleter() );

  FRENSIE_SETUP_STANDARD_LOGS( os_array );
  
  out << std::endl;
  try{
    throw H5::Exception( "dummy_h5_func", "dummy hdf5 message" );
  }
  HDF5_EXCEPTION_CATCH_AND_LOG( "testing" );

  TEST_ASSERT( os_ptr->str().find( "Caught Exception Error: testing" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Exception Type: H5::Exception" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "HDF5 Stack: dummy_h5_func" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "HDF5 Error Msg: dummy hdf5 message" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Location:" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Stack:" ) <
               os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// end tstHDF5ExceptionCatchMacros.cpp
//---------------------------------------------------------------------------//
