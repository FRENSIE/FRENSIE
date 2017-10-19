//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5File.cpp
//! \author Alex Robinson
//! \brief  HDF5 file unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_HDF5File.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the filename can be returned
FRENSIE_UNIT_TEST( HDF5File, getFilename )
{
  std::string hdf5_file_name( "test_file.h5" );
  
  Utility::HDF5File hdf5_file( hdf5_file_name );

  FRENSIE_CHECK_EQUAL( hdf5_file.getFilename(), hdf5_file_name );
}

//---------------------------------------------------------------------------//
// end tstHDF5File.cpp
//---------------------------------------------------------------------------//
