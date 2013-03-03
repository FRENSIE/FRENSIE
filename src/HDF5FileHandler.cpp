//---------------------------------------------------------------------------//
// \file HDF5FileHandler.cpp
// \author Alex Robinson
// \brief HDF5 file handler non-template member function definitions
//---------------------------------------------------------------------------//

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "ExceptionCatchMacros.hpp"

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

//! Create the parent groups, if necessary, for the dataset
void HDF5FileHandler::createParentGroups( const std::string &dataset_name )
{
  // Separate the group names from the dataset name
  Teuchos::Array<std::string> group_names;
  unsigned int loc = dataset_name.find( "/", 1 );
  
  while( loc < dataset_name.size() )
  {
    group_names.push_back( dataset_name.substr( 0, loc ) );
    loc = dataset_name.find( "/", loc+1 );
  }
  
  // Check that each of the groups has been created and create the group if it 
  // hasn't
  for( unsigned int i = 0; i < group_names.size(); ++i )
  {
    // The H5::File openGroup member function can throw a H5::FileIException 
    // exception
    try
    {
      H5::Group group( d_hdf5_file->openGroup( group_names[i] ) );
    }
    // The H5::Group has not been created so create it now
    catch( const H5::FileIException &exception )
    {
      H5::Group new_group( d_hdf5_file->createGroup( group_names[i] ) );
    }
    // Any other exceptions will cause the program to exit
    HDF5_EXCEPTION_CATCH_AND_EXIT();
  }
}
    

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end HDF5FileHandler.cpp
//---------------------------------------------------------------------------//
