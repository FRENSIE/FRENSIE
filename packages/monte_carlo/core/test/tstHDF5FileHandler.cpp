//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  Monte Carlo package base HDF5 file handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <vector>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#define protected public // hack into the protected class members for testing
#include "MonteCarlo_HDF5FileHandler.hpp"
#undef protected

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the hdf5 file can be constructed
TEUCHOS_UNIT_TEST( HDF5FileHandler, constructor_ownership )
{
  const std::string file_name( "test_hdf5_file.h5" );
  const std::string data_set_name( "/test_data" );
  const std::string attribute_name( "test_attribute" );

  // Create a new HDF5 file - exception thrown on error
  {
    MonteCarlo::HDF5FileHandler hdf5_file( file_name );

    std::vector<double> data( 10, 0 );
    hdf5_file.getHDF5File().writeArrayToDataSet( data, data_set_name );
  }

  // Load an old HDF5 file - read only
  {
    MonteCarlo::HDF5FileHandler
      hdf5_file( file_name, MonteCarlo::HDF5FileHandler::READ_ONLY_FILE );

    TEST_ASSERT( hdf5_file.getHDF5File().doesDataSetExist( data_set_name ) );
    TEST_THROW( hdf5_file.getHDF5File().writeValueToDataSetAttribute( 0.0, data_set_name, attribute_name ),
                std::runtime_error );
  }

  // Append an old HDF5 file
  {
    MonteCarlo::HDF5FileHandler
      hdf5_file( file_name, MonteCarlo::HDF5FileHandler::APPEND_FILE );

    TEST_ASSERT( hdf5_file.getHDF5File().doesDataSetExist( data_set_name ) );

    hdf5_file.getHDF5File().writeValueToDataSetAttribute( 0.0, data_set_name, attribute_name );
  }

  // Overwrite an old HDF5 file
  {
    MonteCarlo::HDF5FileHandler
      hdf5_file( file_name, MonteCarlo::HDF5FileHandler::OVERWRITE_FILE );

    TEST_ASSERT( !hdf5_file.getHDF5File().doesDataSetExist( data_set_name ) );
    TEST_ASSERT( !hdf5_file.getHDF5File().doesDataSetAttributeExist( data_set_name, attribute_name ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the hdf5 file can be constructed
TEUCHOS_UNIT_TEST( HDF5FileHandler, constructor_file_sharing )
{
  std::shared_ptr<Utility::HDF5FileHandler>
    shared_hdf5_file( new Utility::HDF5FileHandler );

  shared_hdf5_file->openHDF5FileAndOverwrite( "test_hdf5_file.h5" );

  {
    MonteCarlo::HDF5FileHandler hdf5_file_wrapper( shared_hdf5_file );

    TEST_EQUALITY( shared_hdf5_file.get(), &hdf5_file_wrapper.getHDF5File() );
    TEST_EQUALITY_CONST( shared_hdf5_file.use_count(), 2 );
  }

  TEST_ASSERT( shared_hdf5_file->hasOpenFile() );
  TEST_EQUALITY_CONST( shared_hdf5_file.use_count(), 1 );
}

//---------------------------------------------------------------------------//
// end tstHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
