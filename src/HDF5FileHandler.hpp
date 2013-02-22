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
#include <Teuchos_RCP.hpp>

// HDF5 Inludes
#include <H5Cpp.h>

// FACEMC Includes

namespace FACEMC{

class HDF5FileHandler
{

public:

  //! Default Constructor
  HDF5FileHandler();

  //! Destructor
  ~HDF5FileHandler()
  { /* ... */ }
  
  //! Open an HDF5 file and overwrite any existing data
  void openHDF5FileAndOverwrite( const std::string &file_name );

  //! Open an HDF5 file and append to any existing data
  void openHDF5FileAndAppend( const std::string &file_name );

  //! Close an HDF5 file
  void closeHDF5File();

  //! Write data in array to HDF5 file data set
  // \param data data array to write to HDF5 file dataset
  // \param location_in_file location in HDF5 file where data will be written
  template<typename T, template<typename> class Array>
  void writeArrayToDataSet( const Array<T> &data,
			    const std::string &location_in_file );

  //! Write an attribute to an HDF5 file data set
  // \param data attribute data array to write to HDF5 file dataset
  // \param dataset_location location and name of the HDF5 file data set that
  // the attribute will be written to
  // \param attribute_name name that will be given to the attribute
  template<typename T, template<typename> class Array>
  void writeArrayToDataSetAttribute( const Array<T> &data,
				     const std::string &dataset_location,
				     const std::string &attribute_name );

  //! Write an attribute to an HDF5 file group
  // \param data attribute data array to write to HDF5 file group
  // \param group_location location and name of the HDF5 file group that
  // the attribute will be written to
  // \param attribute_name name that will be given to the attribute
  template<typename T, template<typename> class Array>
  void writeArrayToGroupAttribute( const Array<T> &data,
				   const std::string &group_location,
				   const std::string &attribute_name );

protected:

  //! Create the parent groups, if necessary, for the dataset
  void createParentGroups( const std::string &dataset_name );

private:
  
  // HDF5 file identifier
  Teuchos::RCP<H5::H5File> d_hdf5_file;

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


