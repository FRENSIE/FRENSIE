//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  HDF5 file handler wrapper base class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_HDF5FileHandler.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor (file ownership)
/*! \details The MonteCarlo::HDF5FileHandler::FileOps enum will determine
 * how the HDF5 file will be opened. If the read only option is used, calling
 * any of the set methods will result in an exception.
 */
HDF5FileHandler::HDF5FileHandler( const std::string& hdf5_file_name,
                                  const FileOps file_op )
  : d_hdf5_file( new Utility::HDF5FileHandler ),
    d_hdf5_file_ownership( true )
{
  // Make sure that the name is valid
  testPrecondition( hdf5_file_name.size() > 0 );

  Utility::HDF5FileHandler::throwExceptions();

  try{
    switch( file_op )
    {
    case OVERWRITE_FILE:
      d_hdf5_file->openHDF5FileAndOverwrite( hdf5_file_name );
      break;
    case APPEND_FILE:
      d_hdf5_file->openHDF5FileAndAppend( hdf5_file_name );
      break;
    case READ_ONLY_FILE:
      d_hdf5_file->openHDF5FileAndReadOnly( hdf5_file_name );
      break;
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to open the HDF5 file!" );
}

// Constructor (file sharing)
HDF5FileHandler::HDF5FileHandler(
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : d_hdf5_file( hdf5_file ),
    d_hdf5_file_ownership( false )
{
  // Make sure that the file is valid
  testPrecondition( hdf5_file.get() );
  testPrecondition( hdf5_file->hasOpenFile() );

  Utility::HDF5FileHandler::throwExceptions();
}

// Destructor
HDF5FileHandler::~HDF5FileHandler()
{
  if( d_hdf5_file_ownership )
    d_hdf5_file->closeHDF5File();
}

// Access the HDF5 file
Utility::HDF5FileHandler& HDF5FileHandler::getHDF5File()
{
  return *d_hdf5_file;
}

// Access the HDF5 file
const Utility::HDF5FileHandler& HDF5FileHandler::getHDF5File() const
{
  return *d_hdf5_file;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HDF5FileHandler.cpp
//---------------------------------------------------------------------------//
