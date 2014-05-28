//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  HDF5 file handler non-template member function definitions
//!
//---------------------------------------------------------------------------//

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

//Default Constructor
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

// Open an HDF5 file and overwrite any existing data
/*! \param[in] file_name The name of the HDF5 file that will be opened and
 * overwritten
 */
void HDF5FileHandler::openHDF5FileAndOverwrite( const std::string &file_name )
{
  // The H5File contructor can throw a H5::FileIException exception
  try
  {
    d_hdf5_file.reset( new H5::H5File( file_name, H5F_ACC_TRUNC ) );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//Open an HDF5 file and append to any existing data
/*! \param[in] file_name The name of the HDF5 file that will be opened and
 * appended to.
 */
void HDF5FileHandler::openHDF5FileAndAppend( const std::string &file_name )
{
  // The H5File constructor can throw a H5::FileIException exception
  try
  {
    d_hdf5_file.reset( new H5::H5File( file_name, H5F_ACC_RDWR ) );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

// Open an HDF5 file and read data
/*! \param[in] file_name The name of the HDF5 file that will be opened and
 * read.
 */
void HDF5FileHandler::openHDF5FileAndReadOnly( const std::string &file_name )
{
  // The H5File constructor can throw a H5::FileIException exception
  try
  {
    d_hdf5_file.reset( new H5::H5File( file_name, H5F_ACC_RDONLY ) );
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

// Close an HDF5 file
void HDF5FileHandler::closeHDF5File()
{
  d_hdf5_file.reset();
}

/*! \details This function can be used to create a group heirarchy or to
 * create a directory at the desired location of the HDF5 file.
 * \param[in] path_name The name of the path containing parent groups that
 * need to be created.
 */
void HDF5FileHandler::createParentGroups( const std::string &path_name )
{
  // Separate the group names from the dataset name
  Teuchos::Array<std::string> group_names;
  unsigned int loc = path_name.find( "/", 1 );
  
  while( loc < path_name.size() )
  {
    group_names.push_back( path_name.substr( 0, loc ) );
    loc = path_name.find( "/", loc+1 );
  }
  
  // Check if each group has been created and create the group if it hasn't
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
    

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5FileHandler.cpp
//---------------------------------------------------------------------------//
