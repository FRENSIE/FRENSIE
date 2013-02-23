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
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// HDF5 includes
#include <H5Cpp.h>

// FACEMC includes
#include "HDF5TypeTraits.hpp"
#include "HDF5ArrayPolicy.hpp"
#include "HDF5ExceptionCatchMacro.hpp"
#include "FACEMC_Assertion.hpp"

namespace FACEMC{

//! Write data in array to HDF5 file dataset
template<typename T, template<typename> class Array>
void HDF5FileHandler::writeArrayToDataSet( const Array<T> &data,
					   const std::string &location_in_file
					   )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( location_in_file.compare( 0, 1, "/" ) == 0 ); 
  
  // Create any parent groups that do not exist yet in the location path
  createParentGroups( location_in_file );
  
  // HDF5 exceptions can be thrown when creating a dataset or writing to a 
  // dataset
  try
  {
    hsize_t dim = HDF5ArrayPolicy<T,Array>::size(data);
    H5::DataSpace space( 1, &dim );
    H5::DataSet dataset(d_hdf5_file->createDataSet( 
						 location_in_file,
						 HDF5TypeTraits<T>::dataType(),
						 space ) );
    dataset.write( HDF5ArrayPolicy<T,Array>::getRawPtr(data), 
		   HDF5TypeTraits<T>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Read in HDF5 file dataset and save the data to an array
template<typename T, template<typename> class Array>
void HDF5FileHandler::readArrayFromDataSet( Array<T> &data,
					    const std::string &location_in_file
					    )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( location_in_file.compare( 0, 1, "/" ) == 0 ); 
  
  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::DataSet dataset(d_hdf5_file->openDataSet( location_in_file ) );
    
    // Get the dataspace of the dataset
    H5::DataSpace dataspace = dataset.getSpace();
    
    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();
    
    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );
    
    // Resize the output array to the size of the dataspace
    typename Array<T>::size_type size = dims[0];
    for( unsigned int i = 1; i < rank; ++i )
      size *= dims[i];
    
    HDF5ArrayPolicy<T,Array>::resize( data, size );
    
    // Read the data in the dataset and save it to the output array
    dataset.read( HDF5ArrayPolicy<T,Array>::getRawPtr(data),
		  HDF5TypeTraits<T>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Write attribute to HDF5 file dataset
template<typename T, template<typename> class Array>
void HDF5FileHandler::writeArrayToDataSetAttribute( const Array<T> &data,
						    const std::string 
						      &dataset_location,
						    const std::string
						      &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
    
  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = HDF5ArrayPolicy<T,Array>::size(data);
    H5::DataSpace space( 1, &dim );
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) ); 
    H5::Attribute attribute(dataset.createAttribute( 
					  attribute_name, 
					  HDF5TypeTraits<T>::dataType(),
					  space ) );
    
    attribute.write( HDF5TypeTraits<T>::dataType(),
		     HDF5ArrayPolicy<T,Array>::getRawPtr(data) );  
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Read in HDF5 file dataset attribute and save the data to an array
template<typename T, template<typename> class Array>
void HDF5FileHandler::readArrayFromDataSetAttribute( Array<T> &data,
						     const std::string 
						       &dataset_location,
						     const std::string 
						       &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
  
  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) );

    // Get the attribute associated with the dataset
    H5::Attribute attribute(dataset.openAttribute( attribute_name) );
    
    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();
    
    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();
    
    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );
    
    // Resize the output array to the size of the dataspace
    typename Array<T>::size_type size = dims[0];
    for( unsigned int i = 1; i < rank; ++i )
      size *= dims[i];
    
    HDF5ArrayPolicy<T,Array>::resize( data, size );
    
    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<T>::dataType(),
		    HDF5ArrayPolicy<T,Array>::getRawPtr(data) );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Write attribute to HDF5 file dataset
template<typename T>
void HDF5FileHandler::writeValueToDataSetAttribute( const T &value,
						    const std::string 
						      &dataset_location,
						    const std::string
						      &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
  
  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = 1;
    H5::DataSpace space( 1, &dim );
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) ); 
    H5::Attribute attribute(dataset.createAttribute( 
					  attribute_name, 
					  HDF5TypeTraits<T>::dataType(),
					  space ) );
    
    attribute.write( HDF5TypeTraits<T>::dataType(),
		     &value );  
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Read in HDF5 file dataset attribute and save the single value
template<typename T>
void HDF5FileHandler::readValueFromDataSetAttribute( T &value,
						     const std::string 
						       &dataset_location,
						     const std::string 
						       &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
  
  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) );

    // Get the attribute associated with the dataset
    H5::Attribute attribute(dataset.openAttribute( attribute_name) );
    
    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();
    
    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();
    
    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );

    FACEMC_ASSERT_ALWAYS( (rank == 1 && dims[0] == 1) );
    
    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<T>::dataType(),
		    &value );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Write attribute to HDF5 file group
template<typename T, template<typename> class Array>
void HDF5FileHandler::writeArrayToGroupAttribute( const Array<T> &data,
						  const std::string 
						    &group_location,
						  const std::string
						    &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
    
  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = HDF5ArrayPolicy<T,Array>::size(data);
    H5::DataSpace space( 1, &dim );
    H5::Group group(d_hdf5_file->openGroup( group_location ) ); 
    H5::Attribute attribute(group.createAttribute( 
					  attribute_name, 
					  HDF5TypeTraits<T>::dataType(),
					  space ) );
    
    attribute.write( HDF5TypeTraits<T>::dataType(),
		     HDF5ArrayPolicy<T,Array>::getRawPtr(data) );  
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Read in HDF5 file group attribute and save the data to an array
template<typename T, template<typename> class Array>
void HDF5FileHandler::readArrayFromGroupAttribute( Array<T> &data,
						   const std::string 
						     &group_location,
						   const std::string 
						     &attribute_name )
{
  // The group_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
  
  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::Group group(d_hdf5_file->openGroup( group_location ) );

    // Get the attribute associated with the group
    H5::Attribute attribute(group.openAttribute( attribute_name) );
    
    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();
    
    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();
    
    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );
    
    // Resize the output array to the size of the dataspace
    typename Array<T>::size_type size = dims[0];
    for( unsigned int i = 1; i < rank; ++i )
      size *= dims[i];
    
    HDF5ArrayPolicy<T,Array>::resize( data, size );
    
    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<T>::dataType(),
		    HDF5ArrayPolicy<T,Array>::getRawPtr(data) );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Write attribute to HDF5 file group
template<typename T>
void HDF5FileHandler::writeValueToGroupAttribute( const T &value,
						  const std::string 
						    &group_location,
						  const std::string
						    &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
    
  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = 1;
    H5::DataSpace space( 1, &dim );
    H5::Group group(d_hdf5_file->openGroup( group_location ) ); 
    H5::Attribute attribute(group.createAttribute( 
					  attribute_name, 
					  HDF5TypeTraits<T>::dataType(),
					  space ) );
    
    attribute.write( HDF5TypeTraits<T>::dataType(),
		     &value );  
  }

  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

//! Read in HDF5 file group attribute and save the single value
template<typename T>
void HDF5FileHandler::readValueFromGroupAttribute( T &value,
						   const std::string 
						     &group_location,
						   const std::string 
						     &attribute_name )
{
  // The group_location must be absolute (start with /)
  FACEMC_ASSERT_ALWAYS( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  FACEMC_ASSERT_ALWAYS( (attribute_name.find( "/" ) == std::string::npos ) );
  
  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::Group group(d_hdf5_file->openGroup( group_location ) );

    // Get the attribute associated with the group
    H5::Attribute attribute(group.openAttribute( attribute_name) );
    
    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();
    
    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();
    
    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );
    
    FACEMC_ASSERT_ALWAYS( (rank == 1 && dims[0] == 1) );

    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<T>::dataType(),
		    &value );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
}

} // end FACEMC namespace

#endif // end HDF5_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end HDF5FileHandler_def.hpp
//---------------------------------------------------------------------------//
