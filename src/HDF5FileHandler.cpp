//---------------------------------------------------------------------------//
// \file HDF5FileHandler.cpp
// \author Alex Robinson
// \brief HDF5 file handler non-template member function definitions
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "FACEMC_assertion.hpp"

namespace FACEMC{

//! Default Constructor
// \brief HDF5 will assign a negative number to an invalid file_id
HDF5FileHandler::HDF5FileHandler()
  : d_file_id(-1)
{ /* ... */ }

//! Destructor
HDF5FileHandler::~HDF5FileHandler()
{
  // Make sure that a current file is closed before destroying the handler
  if( d_file_id >= 0 )
    closeHDF5File( d_file_id );
}

//! Open an HDF5 file and overwrite any existing data
hid_t HDF5FileHandler::openHDF5FileAndOverwrite( const std::string &file_name )
{
  // Make sure that a current file is closed before opening a new one 
  if( d_file_id >= 0 )
    closeHDF5File( d_file_id );

  d_file_id = H5Fcreate( file_name.c_str(),
			 H5F_ACC_TRUNC,
			 H5P_DEFAULT,
			 H5P_DEFAULT );
  assertAlways( d_file_id >= 0 );
}

//! Open an HDF5 file and append to any existing data
hid_t HDF5FileHandler::openHDF5FileAndAppend( const std::string &file_name )
{
  // Make sure that a current file is closed before opening a new on
  if( d_file_id >= 0 )
    closeHDF5File( d_file_id );
  
  d_file_id = H5Fopen( file_name.c_str(),
		       H5F_ACC_RDWR,
		       H5P_DEFAULT,
		       H5P_DEFAULT );
  assertAlways( d_file_id >= 0 );
}

//! Close an HDF5 file
void HDF5FileHandler::closeHDF5File( hid_t file_id )
{
  herr_t status = H5Fclose( file_id );
  assertAlways( status == SUCCEED );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end HDF5FileHandler.cpp
//---------------------------------------------------------------------------//
