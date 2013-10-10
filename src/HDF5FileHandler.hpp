//---------------------------------------------------------------------------//
//!
//! \file HDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief HDF5 File handling class declaration
//!
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

/*! \brief A class which wraps the HDF5 interface and adds some additional
 * functionality useful for FACEMC.
 *
 * This class wraps the HDF5 file interface. It is used to either write data to 
 * an HDF5 file or to read data from an HDF5 file. Depending on how the file
 * is opened, write operations might be disabled. 
 */
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

  //! Open an HDF5 file and read data
  void openHDF5FileAndReadOnly( const std::string &file_name );

  //! Close an HDF5 file
  void closeHDF5File();

  //! Write data in array to HDF5 file data set
  template<typename Array>
  void writeArrayToDataSet( const Array &data,
			    const std::string &location_in_file );

  //! Read in HDF5 file dataset and save the data to an array
  template<typename Array>
  void readArrayFromDataSet( Array &data,
			     const std::string &location_in_file );

  //! Write an attribute to an HDF5 file data set
  template<typename Array>
  void writeArrayToDataSetAttribute( const Array &data,
				     const std::string &dataset_location,
				     const std::string &attribute_name );

  //! Read in HDF5 file dataset attribute and save the data to an array
  template<typename Array>
  void readArrayFromDataSetAttribute( Array &data,
				      const std::string &dataset_location,
				      const std::string &attribute_name );

  //! Write an attribute to an HDF5 file data set
  template<typename T>
  void writeValueToDataSetAttribute( const T &value,
				     const std::string &dataset_location,
				     const std::string &attribute_name );

  //! Read in HDF5 file dataset attribute and save the single value
  template<typename T>
  void readValueFromDataSetAttribute( T &value,
				      const std::string &dataset_location,
				      const std::string &attribute_name );

  //! Write an attribute to an HDF5 file group
  template<typename Array>
  void writeArrayToGroupAttribute( const Array &data,
				   const std::string &group_location,
				   const std::string &attribute_name );

  //! Read in HDF5 file group attribute and save the data to an array
  template<typename Array>
  void readArrayFromGroupAttribute( Array &data,
				    const std::string &group_location,
				    const std::string &attribute_name );

  //! Write an attribute to an HDF5 file group
  template<typename T>
  void writeValueToGroupAttribute( const T &value,
				   const std::string &group_location,
				   const std::string &attribute_name );

  //! Read in HDF5 file group attribute and save the single value
  template<typename T>
  void readValueFromGroupAttribute( T &value,
				    const std::string &group_location,
				    const std::string &attribute_name );

protected:

  //! Create the parent groups, if necessary, for the specified path
  void createParentGroups( const std::string &path_name );

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


