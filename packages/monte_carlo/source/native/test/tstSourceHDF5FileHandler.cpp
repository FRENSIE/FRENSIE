//---------------------------------------------------------------------------//
//!
//! \file   tstSourceHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  Source hdf5 file handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HDF5FileHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

const std::string hdf5_file_name( "test_source.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the handler can be constructed
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, constructor_ownership_rw )
{
  std::shared_ptr<MonteCarlo::SourceHDF5FileHandler> file_handler;

  // Create a handler with Read/Write ops
  TEST_NOTHROW( file_handler.reset(
                   new MonteCarlo::SourceHDF5FileHandler( hdf5_file_name ) ) );

  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setNumberOfSourceSamplingTrials( 0, 0ull ) );
  TEST_NOTHROW( file_handler->setNumberOfDefaultSourceSamplingTrials( 0ull ) );
  TEST_NOTHROW( file_handler->setNumberOfSourceSamples( 0, 0ull ) );
  TEST_NOTHROW( file_handler->setNumberOfDefaultSourceSamples( 0ull ) );
}

//---------------------------------------------------------------------------//
// Check that the handler can be constructed
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, constructor_sharing )
{
  std::shared_ptr<Utility::HDF5FileHandler> shared_handler(
                                                new Utility::HDF5FileHandler );

  shared_handler->openHDF5FileAndOverwrite( hdf5_file_name );

  std::shared_ptr<MonteCarlo::SourceHDF5FileHandler> source_file_handler(
                     new MonteCarlo::SourceHDF5FileHandler( shared_handler ) );

  // Make sure setter methods work
  TEST_NOTHROW( source_file_handler->setNumberOfSourceSamplingTrials( 0, 0ull ) );
  TEST_NOTHROW( source_file_handler->setNumberOfDefaultSourceSamplingTrials( 0ull ) );
  TEST_NOTHROW( source_file_handler->setNumberOfSourceSamples( 0, 0ull ) );
  TEST_NOTHROW( source_file_handler->setNumberOfDefaultSourceSamples( 0ull ) );
}

//---------------------------------------------------------------------------//
// Check that source trials can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, setNumberOfSourceSamplingTrials )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceSamplingTrials( 0, 10000ull );
  file_handler.setNumberOfSourceSamplingTrials( 1, 1001ull );
  
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamplingTrials( 0 ),
                       10000ull );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamplingTrials( 1 ),
                       1001ull );
}

//---------------------------------------------------------------------------//
// Check that default source trials can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, 
                   setNumberOfDefaultSourceSamplingTrials )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfDefaultSourceSamplingTrials( 100000ull );
  
  
  TEST_EQUALITY_CONST( file_handler.getNumberOfDefaultSourceSamplingTrials(),
                       100000ull );
}

//---------------------------------------------------------------------------//
// Check that source samples can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, setNumberOfSourceSamples )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceSamples( 0, 10000ull );
  file_handler.setNumberOfSourceSamples( 1, 1001ull );
  
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamples( 0 ), 10000ull );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamples( 1 ), 1001ull );
}

//---------------------------------------------------------------------------//
// Check that default source samples can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, setNumberOfDefaultSourceSamples )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfDefaultSourceSamples( 100001ull );
  
  
  TEST_EQUALITY_CONST( file_handler.getNumberOfDefaultSourceSamples(),
                       100001ull );
}

//---------------------------------------------------------------------------//
// Check if sources exist
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, doesSourceExist )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  // Make sure setter methods work
  file_handler.setNumberOfSourceSamplingTrials( 0, 0ull );
  file_handler.setNumberOfSourceSamples( 0, 0ull );

  file_handler.setNumberOfSourceSamplingTrials( 1, 0ull );
  file_handler.setNumberOfSourceSamples( 1, 0ull );

  TEST_ASSERT( file_handler.doesSourceExist( 0 ) );
  TEST_ASSERT( file_handler.doesSourceExist( 1 ) );
  TEST_ASSERT( !file_handler.doesSourceExist( 2 ) );
  
}

//---------------------------------------------------------------------------//
// Check that a read-only handler can be constructed
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, constructor_ownership_r )
{
  std::shared_ptr<MonteCarlo::SourceHDF5FileHandler> file_handler;

  // Create a handler with Read/Write ops
  TEST_NOTHROW( file_handler.reset(
                   new MonteCarlo::SourceHDF5FileHandler( hdf5_file_name ) ) );

  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setNumberOfSourceSamplingTrials( 0, 0ull ) );
  TEST_NOTHROW( file_handler->setNumberOfDefaultSourceSamplingTrials( 0ull ) );
  TEST_NOTHROW( file_handler->setNumberOfSourceSamples( 0, 0ull ) );
  TEST_NOTHROW( file_handler->setNumberOfDefaultSourceSamples( 0ull ) );

  file_handler.reset();

  // Create a handler with Read-only ops
  TEST_NOTHROW( file_handler.reset(
           new MonteCarlo::SourceHDF5FileHandler( hdf5_file_name, MonteCarlo::SourceHDF5FileHandler::READ_ONLY_SOURCE_HDF5_FILE ) ) );

  // Make sure the file has not been overwritten
  TEST_ASSERT( file_handler->doesSourceExist( 0u ) );

  // Make sure setters are disabled
  TEST_THROW( file_handler->setNumberOfSourceSamplingTrials( 1, 0ull ),
              std::runtime_error );
  TEST_THROW( file_handler->setNumberOfDefaultSourceSamplingTrials( 0ull ),
              std::runtime_error );
  TEST_THROW( file_handler->setNumberOfSourceSamples( 1, 0ull ),
              std::runtime_error );
  TEST_THROW( file_handler->setNumberOfDefaultSourceSamples( 0ull ),
              std::runtime_error );

  file_handler.reset();

  // Reset the file
  file_handler.reset( new MonteCarlo::SourceHDF5FileHandler( hdf5_file_name ));
}

//---------------------------------------------------------------------------//
// end tstSourceHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
