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

// HDF5 includes
#include <hdf5.h>

// FACEMC includes
#include "HDF5ScalarTraits.hpp"
#include "FACEMC_Assertion.hpp"

namespace FACEMC{

//! Write Data in NxM array to HDF5 file
template<typename T, int N=2>
void HDF5FileHandler::writeArrayToHDF5File( const Teuchos::Array<T>,
					    const std::string &location_in_file
					    )
{
  hid_t dataset_id, dataspace_id;
  Teuchos::Array<hsize_t> dims;
  herr_t status;
  
  if( N > 0 )
  dims[0] = N;
  dims[1] = data[0].size();
  
  dataspace_id = H5Screate_simple( 2, dims, NULL );
  dataset_id = H5Dcreate( d_file_id, 
			  location_in_file.c_str(),
			  HDF5ScalarTraits<T>::fileTypeBE(),
			  dataspace_id,
			  H5P_DEFAULT,
			  H5P_DEFAULT,
			  H5P_DEFAULT );
  
  status = H5Dwrite( dataset_id,
		     HDF5ScalarTraits<T>::memoryType(),
		     H5S_ALL,
		     H5S_ALL,
		     H5P_DEFAULT,
		     &data[0][0] );
  assertAlways( status == SUCCEED );
  
  status = H5Sclose( dataspace_id );
  assertAlways( status == SUCCEED );
  
  status = H5Dclose( dataset_id );
  assertAlways( status == SUCCEED );
}

//! Write attribute to HDF5 file
// \brief Warning, N should never be set to a value < 2 - runtime errors will
// result because the HDF5 function calls expect a pointer.
template<typename T>
void HDF5FileHandler::writeMultiValueAttributeToHDF5File( 
						 const Teuchos::Array<T> &data,
						 const std::string 
						  &location_in_file,
						 const std::string
						  &attribute_name )
{
  hid_t dataset_id, attribute_id, dataspace_id;
  hsize_t attribute_dim = data.size();
  herr_t status;
  
  dataset_id = H5Dopen( d_file_id,
			loation_in_file.c_str(),
			H5P_DEFULT );
  dataspace_id = H5create_simple( 1, &attribute_dim, NULL );
  attribute_id = H5Acreate( dataset_id,
			    attribute_name.c_str(),
			    HDF5ScalarTraits<T>::fileTypeBE(),
			    dataspace_id,
			    H5P_DEFAULT,
			    H5P_DEFAULT );
  status = H5Awrite( attribute_id,
		     HDF5ScalarTraits<T>::memoryType(),
		     &data[0] );
  assertAlways( status == SUCCEED );

  // Close the current attribute, dataspace and dataset
  status = H5Aclose( attribute_id );
  assertAlways( status == SUCCEED );
  
  status = H5Sclose( dataspace_id );
  assertAlways( status == SUCCEED );
  
  status = H5Dclose( dataset_id );
  assertAlways( status == SUCCEED );
}

} // end FACEMC namespace

#endif // end HDF5_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end HDF5FileHandler_def.hpp
//---------------------------------------------------------------------------//
