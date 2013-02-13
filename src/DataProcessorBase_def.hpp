//---------------------------------------------------------------------------//
// \file DataProcessorBase_def.hpp
// \author Alex Robinson
// \brief Data Processor Base template definitions
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_BASE_DEF_HPP
#define DATA_PROCESSOR_BASE_DEF_HPP

// Std Lib Includes
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Trilinos Includes
#include "Teuchos_Array.hpp"

// HDF5 includes
#include "hdf5.h"

// FACEMC includes
#include "HDF5ScalarTraits.hpp"
#include "Exception.hpp"

namespace FAPMC{

//! Write attribute to HDF5 file
// \brief Warning, N should never be set to a value < 2 - runtime errors will
// result because the HDF5 function calls expect a pointer.
template<typename T, int N=2>
void DataProcessorBase::writeMultiValueAttributeToHDF5File( const hid_t file_id,
							    const T data[N],
							    const std::string 
							    &location_in_file,
							    const std::string
							    &attribute_name )
{
  hid_t dataset_id, attribute_id, dataspace_id;
  hsize_t attribute_dim = N;
  herr_t status;
  
  dataset_id = H5Dopen( file_id,
			loation_in_file.c_str(),
			H5P_DEFAULT );
  dataspace_id = H5create_simple( 1, &attribute_dim, NULL );
  attribute_id = H5Acreate( dataset_id,
			    attribute_name.c_str(),
			    HDF5ScalarTraits<T>::fileTypeBE,
			    dataspace_id,
			    H5P_DEFAULT,
			    H5P_DEFAULT );
  status = H5Awrite( attribute_id,
		     HDF5ScalarTraits<T>::memoryType,
		     data );
  testHDF5( status == SUCCEED,
	    "HDF5 attribute write error" );

  // Close the current attribute, dataspace and dataset
  status = H5Aclose( attribute_id );
  testHDF5( status == SUCCEED,
	    "HDF5 attribute close error" );
  
  status = H5Sclose( dataspace_id );
  testHDF5( status == SUCCEED,
	    "HDF5 dataspace close error" );
  
  status = H5Dclose( dataset_id );
  testHDF5( status == SUCCEED,
	    "HDF5 dataset close error" );
}

//! Write attribute to HDF5 file
template<typename T>
void DataProcessorBase<double, 1>::writeSingleValueAttributeToHDF5File( 
						        const hid_t file_id,
							const T data,
							const std::string 
							&location_in_file,
							const std::string
							&attribute_name )
{
  hid_t dataset_id, attribute_id, dataspace_id;
  hsize_t attribute_dim = 1;
  herr_t status;
  
  dataset_id = H5Dopen( file_id,
			loation_in_file.c_str(),
			H5P_DEFAULT );
  dataspace_id = H5create_simple( 1, &attribute_dim, NULL );
  attribute_id = H5Acreate( dataset_id,
			    attribute_name.c_str(),
			    HDF5ScalarTraits<T>::fileTypeBE,
			    dataspace_id,
			    H5P_DEFAULT,
			    H5P_DEFAULT );
  status = H5Awrite( attribute_id,
		     HDF5ScalarTraits<T>::memoryType,
		     &data );
  testHDF5( status == SUCCEED,
	    "HDF5 attribute write error" );

  // Close the current attribute, dataspace and dataset
  status = H5Aclose( attribute_id );
  testHDF5( status == SUCCEED,
	    "HDF5 attribute close error" );
  
  status = H5Sclose( dataspace_id );
  testHDF5( status == SUCCEED,
	    "HDF5 dataspace close error" );
  
  status = H5Dclose( dataset_id );
  testHDF5( status == SUCCEED,
	    "HDF5 dataset close error" );
}

//! Write data in 1D array to HDF5 file
template<typename T>
void DataProcessorBase::writeArrayToHDF5File( 
					     const hid_t file_id,
					     const Teuchos::Array<T>& data,
					     const std::string &location_in_file
					      )
{
  hid_t dataset_id, dataspace_id;
  hsize_t dims;
  herr_t status;
  
  dims = data.size();

  dataspace_id = H5Screate_simple( 1, dims, NULL );
  dataset_id = H5Dcreate( file_id, 
			  location_in_file.c_str(),
			  HDF5ScalarTraits<T>::fileTypeBE,
			  dataspace_id,
			  H5P_DEFAULT,
			  H5P_DEFAULT,
			  H5P_DEFAULT );
  
  status = H5Dwrite( dataset_id,
		     HDF5ScalarTraits<T>::memoryType,
		     H5S_ALL,
		     H5S_ALL,
		     H5P_DEFAULT,
		     &data[0] );
  testHDF5( status == SUCCEED,
	    "HDF5 dataset write error" );
  
  status = H5Sclose( dataspace_id );
  testHDF5Status( status == SUCCEED,
		  "HDF5 dataspace close error" );
  
  status = H5Dclose( dataset_id );
  testHDF5Status( status == SUCCEED,
		  "HDF5 dataset close error" );
}
  

//! Write Data in NxM array to HDF5 file
template<typename T, int N=2>
void DataProcessorBase::write2DArrayToHDF5File( 
					     const hid_t file_id,
					     const Teuchos::Array<T>& data[N],
					     const std::string &location_in_file
						)
{
  hid_t dataset_id, dataspace_id;
  hsize_t dims[2];
  herr_t status;
  
  dims[0] = N;
  dims[1] = data[0].size();
  
  dataspace_id = H5Screate_simple( 2, dims, NULL );
  dataset_id = H5Dcreate( file_id, 
			  location_in_file.c_str(),
			  HDF5ScalarTraits<T>::fileTypeBE,
			  dataspace_id,
			  H5P_DEFAULT,
			  H5P_DEFAULT,
			  H5P_DEFAULT );
  
  status = H5Dwrite( dataset_id,
		     HDF5ScalarTraits<T>::memoryType,
		     H5S_ALL,
		     H5S_ALL,
		     H5P_DEFAULT,
		     &data[0][0] );
  testHDF5( status == SUCCEED,
	    "HDF5 dataset write error" );
  
  status = H5Sclose( dataspace_id );
  testHDF5Status( status == SUCCEED,
		  "HDF5 dataspace close error" );
  
  status = H5Dclose( dataset_id );
  testHDF5Status( status == SUCCEED,
		  "HDF5 dataset close error" );
}

//! Read two column table in EPDL file within specified range
template<typename DataProcessingPolicy>
void DataProcessorBase::readTwoColumnTableInRange( FILE* datafile,
						   Teuchos::Array<double> 
						   &data[2],
						   const double indep_var_min,
						   const double indep_var_max )
{
  // Variables for reading in a two column table
  char data1_l [10];
  data1_l[9] = '\0';
  data1_l[0] = 'n';
  char data1_r [3];
  data1_r[2] = '\0';
  char data2_l [10];
  data2_l[9] = '\0';
  char data2_r [3];
  data2_r[2] = '\0';
  char nwln [2];
  nwln[1] = '\0';
  char end_of_table [51];
  end_of_table[50] = '\0';
  char test []=  "         ";
  int rv;
  
  // Values extracted from the table
  double indep_prev = 0.0, indep = 0.0;
  double dep_prev = 0.0, dep = 0.0;

  // Make sure that the data array is empty
  data[0].clear();
  data[1].clear();

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( datafile, "%9c%2c%9c%2c%1c", data1_l, data1_r, data2_l,
		 data2_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      indep = extractValue<double>( data1_l, 
				    data1_r );
      dep = extractValue<double>( data2_l,
				  data2_r );
      
      // Remove values outside of independent variable range
      if( (indep > indep_var_min && indep_prev > indep_var_min) &&
	  (indep_prev < indep_var_max && indep < indep_var_max) )
      {
	data[0].push_back( DataProcessingPolicy::processIndependentVar(indep) );
	data[1].push_back( DataProcessingPolicy::processDependentVar(dep) );
	
	indep_prev = indep;
	dep_prev = dep;
      }
      else if( (indep > indep_var_min && indep_prev < indep_var_min) ||
	       (indep_prev < indep_var_max && indep > indep_var_max) )
      {
	if( indep_prev > 0.0 )
	{
	  data[0].push_back( DataProcessingPolicy::processIndependentVar(indep_prev) );
	  data[1].push_back( DataProcessingPolicy::processDependentVar(dep_prev) );
	}
	data[0].push_back( DataProcessingPolicy::processIndependentVar(indep) );
	data[1].push_back( DataProcessingPolicy::processDepenedentVar(dep) );

	indep_prev = indep;
	dep_prev = dep;
      }
      else
      {
	indep_prev = indep;
	dep_prev = dep;
      }
    }
  }

  // Read rest of end of table line
  rv = fscanf( datafile, "%50c", end_of_table );
}

//! Read two column table in EPDL file
template<typename DataProcessingPolicy>
void DataProcessorBase::readTwoColumnTable( FILE* datafile,
					    Teuchos::Array<double> &data[2] )
{
  // Variables for reading in a two column table
  char data1_l [10];
  data1_l[9] = '\0';
  data1_l[0] = 'n';
  char data1_r [3];
  data1_r[2] = '\0';
  char data2_l [10];
  data2_l[9] = '\0';
  char data2_r [3];
  data2_r[2] = '\0';
  char nwln [2];
  nwln[1] = '\0';
  char end_of_table [51];
  end_of_table[50] = '\0';
  char test []=  "         ";
  int rv;
  
  // Values extracted from the table
  double indep = 0.0;
  double dep = 0.0;

  // Make sure that the data array is empty
  data[0].clear();
  data[1].clear();

  // Read the table one line at a time
  while( strcmp( data1_l, test ) != 0 )
  {
    rv = fscanf( datafile, "%9c%2c%9c%2c%1c", data1_l, data1_r, data2_l,
		 data2_r, nwln);
    if( strcmp( data1_l, test ) != 0 )
    {
      indep = extractValue<double>( data1_l, 
				    data1_r );
      dep = extractValue<double>( data2_l,
				  data2_r );
      
      data[0].push_back( DataProcessingPolicy::processIndependentVar(indep) );
      data[1].push_back( DataProcessingPolicy::processDependentVar(dep) );
    }
  }

  // Read rest of end of table line
  rv = fscanf( datafile, "%50c", end_of_table );
}

template<typename T>
inline T DataProcessorBase::extractValue( std::string mantissa,
					  std::string exponent )
  {
    std::string string_value;
    
    // test for all possible output cases
    if( strncmp( &mantissa[8], "+", 1 ) == 0 )
    {
      mantissa[8] = '0';
      string_value = mantissa + "e+";
    }
    else if( strncmp( &mantissa[8], "-", 1 ) == 0 )
    {
      mantissa[8] = '0';
      string_value = mantissa + "e-";
    }
    else
      string_value = mantissa;
    
    if( strncmp( &exponent[0], " ", 1 ) == 0 )
      exponent[0] = '0';
    else if( strncmp( &exponent[0], "+", 1 ) == 0 )
    {
      exponent[0] = '0';
      string_value += "e+";
    }
    else if( strncmp( &exponent[0], "-", 1 ) == 0 )
    {
      exponent[0] = '0';
      string_value += "e-";
    }
    
    string_value += exponent;
    
    double_value = atof( string_value.c_str() );
    
    return static_cast<T>(double_value);
  }

} // end FACEMC namespace

#endif // end DATA_PROCESSOR_BASE_DEF_HPP

//---------------------------------------------------------------------------//
// end DataProcessorBase_def.hpp
//---------------------------------------------------------------------------//
