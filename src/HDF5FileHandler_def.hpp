//---------------------------------------------------------------------------//
// \file HDF5FileHandler_def.hpp
// \author Alex Robinson
// \brief HDF5 file handler template member function definitions
//---------------------------------------------------------------------------//

#ifndef HDF5_FILE_HANDLER_DEF_HPP
#define HDF5_FILE_HANDLER_DEF_HPP

//Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// HDF5 includes
#include <H5Cpp.h>

// FACEMC includes
#include "HDF5TypeTraits.hpp"
#include "HDF5ExceptionCatchMacro.hpp"

namespace FACEMC{

//! Write Data in array to HDF5 file dataset
template<typename T>
void HDF5FileHandler::writeArrayToDataSet( const Teuchos::Array<T> data,
					   const std::string &location_in_file
					   )
{
  // HDF5 exceptions can be thrown when creating a dataset or writing to a 
  // dataset
  try
  {
    hsize_t dim = data.size();
    H5::DataSpace space( 1, dim );
    H5::DataSet dataset(d_hdf5_file->createDataSet( 
						 location_in_file,
						 HDF5TypeTraits<T>::dataType(),
						 space ) ) );
    dataset.write( &data[0], 
		   HDF5TypeTraits<T>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Write attribute to HDF5 file group
template<typename T>
void HDF5FileHandler::writeArrayToDataSetAttribute( 
						 const Teuchos::Array<T> &data,
						 const std::string 
						   &dataset_location,
						 const std::string
						   &attribute_name )
{
  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = data.size();
    DataSpace space( 1, dim );
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) ) ); 
    H5::Attribute attribute(dataset.createAttribute( 
					  attribute_name, 
					  HDF5TypeTraits<T>::dataType() ) ) );
    
    attribute.write( H5DTypeTraits<T>::dataType(),
		     &data[0] );  
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Write attribute to HDF5 file group
template<typename T>
void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::Array<T> &data,
						  const std::string 
						    &group_location,
						  const std::string
						    &attribute_name )
{
  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = data.size();
    DataSpace space( 1, dim );
    H5::Group group(d_hdf5_file->openGroup( group_location ) ) ); 
    H5::Attribute attribute(group.createAttribute( 
					  attribute_name, 
					  HDF5TypeTraits<T>::dataType() ) ) );
    
    attribute.write( H5DTypeTraits<T>::dataType(),
		     &data[0] );  
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

} // end FACEMC namespace

#endif // end HDF5_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end HDF5FileHandler_def.hpp
//---------------------------------------------------------------------------//
