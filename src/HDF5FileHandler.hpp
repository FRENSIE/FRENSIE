//---------------------------------------------------------------------------//
// \file HDF5FileHandler.hpp
// \author Alex Robinson
// \brief HDF5 File handling class
//---------------------------------------------------------------------------//

#ifndef HDF5_FILE_HANDLER_HPP
#define HDF5_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// HDF5 Inludes
#include <hdf5.h>

// FACEMC Includes

namespace FACEMC{

class HDF5FileHandler
{

public:

  //! Default Constructor
  HDF5FileHandler();

  //! Destructor
  ~HDF5FileHandler();
  
  //! Open an HDF5 file and overwrite any existing data
  void openHDF5FileAndOverwrite( const std::string &file_name );

  //! Open an HDF5 file and append to any existing data
  void openHDF5FileAndAppend( const std::string &file_name );

  //! Close an HDF5 file
  void closeHDF5File();

  //! Write data in array to HDF5 file
  // \param file_id HDF5 identifier for the binary file to write to
  // \param data NxM data array to write to HDF5 file
  // \param location_in_file location in HDF5 file where data will be written
  template<typename T, int N=2>
  void writeArrayToHDF5File( const Teuchos::Array<T> &data,
			     const std::string &location_in_file );

  //! Write a multi value attribute to HDF5 file ( 1xN array )
  // \param file_id HDF5 identifier for the binary file to write to
  template<typename T>
  void writeAttributToHDF5File( const Teuchos::Array<T>& data,
				const std::string &location_in_file,
				const std::string &attribute_name );

private:
  
  // HDF5 file identifier
  hid_t d_file_id;

};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "HDF5FileHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end HDF5FileHandler.hpp
//---------------------------------------------------------------------------//


