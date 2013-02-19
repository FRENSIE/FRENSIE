//---------------------------------------------------------------------------//
// \file HDF5FileHandler.cpp
// \author Alex Robinson
// \brief HDF5 file handler non-template member function definitions
//---------------------------------------------------------------------------//

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "HDF5ExceptionCatchMacro.hpp"

namespace FACEMC{

//! Default Constructor
HDF5FileHandler::HDF5FileHandler()
{
  // Turn off HDF5 error auto printing: All errors will be handled through
  // exceptions
  try
  {
    H5::Exception::dontPrint();
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Open an HDF5 file and overwrite any existing data
void HDF5FileHandler::openHDF5FileAndOverwrite( const std::string &file_name )
{
  // The H5File contructor can throw a H5::FileIException exception
  try
  {
    d_hdf5_file.reset( new H5::H5File( file_name, H5F_ACC_TRUNC ) );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Open an HDF5 file and append to any existing data
void HDF5FileHandler::openHDF5FileAndAppend( const std::string &file_name )
{
  // The H5File constructor can throw a H5::FileIException exception
  try
  {
    d_hdf5_file.reset( new H5::H5File( file_name, H5F_ACC_RDWR ) );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Close an HDF5 file
void HDF5FileHandler::closeHDF5File()
{
  d_hdf5_file.reset();
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end HDF5FileHandler.cpp
//---------------------------------------------------------------------------//
