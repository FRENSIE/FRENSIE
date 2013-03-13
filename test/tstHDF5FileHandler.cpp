//---------------------------------------------------------------------------//
// \file   tstHDF5FileHandler.cpp
// \author Alex Robinson
// \brief  HDF5FileHandler class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"
#include "TestingHelperFunctions.hpp"
#include "HDF5FileHandlerTestingTypedefs.hpp"

//---------------------------------------------------------------------------//
// HDF5 Test File Names.
//---------------------------------------------------------------------------//
#define HDF5_TEST_FILE_NAME "hdf5_test_file.h5"
#define DATASET_NAME "/data/data_array"
#define ROOT_GROUP "/"
#define CHILD_GROUP "/child/"
#define ATTRIBUTE_NAME "attribute"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )		\
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, unsigned, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, pair_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, pair_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, pair_uint_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, pair_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_uint_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_double_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_uint_uint_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, trip_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_double_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_uint_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_double_uint_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_uint_double_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_double_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_uint_double_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_double_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_uint_double_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_uint_uint_double, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_double_uint_uint_uint, array ) \
  FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_INSTANT( type, name, quad_pair_pair_trip_quad, array ) \

#define UNIT_TEST_INSTANTIATION( type, name )				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_uint_uint )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_uint_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_uint_uint_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_double_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_uint_uint_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_uint_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_uint_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_double_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_double_uint_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_double_uint_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_uint_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_double_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_uint_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_double_uint_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_uint_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_double_uint_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_double_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_uint_double_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_double_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_uint_double_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_double_uint_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_uint_double_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_uint_uint_double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_double_uint_uint_uint ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_pair_pair_trip_quad ) \

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingHDF5FileHandler : public FACEMC::HDF5FileHandler
{
public:
  TestingHDF5FileHandler()
    : HDF5FileHandler()
  { /* ... */ }
  
  virtual ~TestingHDF5FileHandler()
  { /* ... */ }

  using FACEMC::HDF5FileHandler::createParentGroups;

};  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can open and overwrite a file
TEUCHOS_UNIT_TEST( HDF5FileHandler, openHDF5FileAndOverwrite )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  // If the file is not opened successfully, an exception will be thrown
  // and caught inside the member function, causing a program exit. 
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can open a file for read-write
TEUCHOS_UNIT_TEST( HDF5FileHandler, openHDF5FileAndAppend )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  // If the file is not opened successfully, an exception will be thrown
  // and caught inside the member function, causing a program exit. 
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.openHDF5FileAndAppend( HDF5_TEST_FILE_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can open a file for read-only
TEUCHOS_UNIT_TEST( HDF5FileHandler, openHDF5FileAndReadOnly )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  // If the file is not opened successfully, an exception will be thrown
  // and caught inside the member function, causing a program exit. 
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.openHDF5FileAndReadOnly( HDF5_TEST_FILE_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can create the necessary parent groups
// for a dataset
TEUCHOS_UNIT_TEST( HDF5FileHandler, createParentGroups )
{
  TestingHDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  // If the groups are not made successfully, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.createParentGroups( DATASET_NAME );
  
  hdf5_file_handler.createParentGroups( CHILD_GROUP );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write an Array of Type to a dataset in 
// an HDF5 file
FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL( HDF5FileHandler, 
						writeArrayToDataSet,
						Type,
						Array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Array<Type> data;
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( data, test_value );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSet, Array );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSet, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSet, ArrayView );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSet, TwoDArray );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read an Array of Type from a dataset
// in an HDF5 file
FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL( HDF5FileHandler, 
						readArrayFromDataSet,
						Type,
						Array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Array<Type> data_original;
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( data_original,
						      test_value );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 DATASET_NAME );

  Array<Type> data;
  //FACEMC::ArrayTestingPolicy<Type,Array>::resize( data, 
  //						  data_original.size() );
  hdf5_file_handler.readArrayFromDataSet( data,
  					  DATASET_NAME );

  FACEMC_TEST_COMPARE_ARRAYS( data_original, data );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromDataSet, Array );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromDataSet, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromDataSet, TwoDArray );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write an Array of Type to a dataset
// attribute in an HDF5 file
FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL( HDF5FileHandler, 
						writeArrayToDataSetAttribute,
						Type,
						Array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Array<Type> set_data;
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( set_data, test_value );

  hdf5_file_handler.writeArrayToDataSet( set_data,
					 DATASET_NAME );

  Array<Type> data;
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( data, test_value );

  // If the dataset attribute is not written successfuly, an exception will be 
  // thrown and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSetAttribute( data,
						  DATASET_NAME,
						  ATTRIBUTE_NAME );
  
  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSetAttribute, Array );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSetAttribute, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSetAttribute, ArrayView );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToDataSetAttribute, TwoDArray );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read an Array of Type from a dataset
// attribute in an HDF5 file
FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL( HDF5FileHandler, 
						readArrayFromDataSetAttribute,
						Type,
						Array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Array<Type> set_data;
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( set_data, test_value );

  hdf5_file_handler.writeArrayToDataSet( set_data,
					 DATASET_NAME );

  Array<Type> data_original;
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( data_original, 
						      test_value );

  hdf5_file_handler.writeArrayToDataSetAttribute( data_original,
						  DATASET_NAME,
						  ATTRIBUTE_NAME );

  Array<Type> data;
  hdf5_file_handler.readArrayFromDataSetAttribute( data,
						   DATASET_NAME,
						   ATTRIBUTE_NAME );
  
  FACEMC_TEST_COMPARE_ARRAYS( data_original, data );
  
  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromDataSetAttribute, Array );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromDataSetAttribute, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromDataSetAttribute, TwoDArray );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a single value to a dataset
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, writeValueToDataSetAttribute, Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Teuchos::Array<Type> data; 
  FACEMC::ArrayTestingPolicy<Type,Teuchos::Array>::initialize( data, 
							       test_value );

  hdf5_file_handler.writeArrayToDataSet( data,
					 DATASET_NAME );

  // If the dataset attribute is not written successfuly, an exception will be 
  // thrown and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeValueToDataSetAttribute( test_value,
						  DATASET_NAME,
						  ATTRIBUTE_NAME );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION( HDF5FileHandler, writeValueToDataSetAttribute );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a single value from a dataset
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, readValueFromDataSetAttribute, Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value_original;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value_original );

  Teuchos::Array<Type> data; 
  FACEMC::ArrayTestingPolicy<Type,Teuchos::Array>::initialize( data, 
							       test_value_original );

  hdf5_file_handler.writeArrayToDataSet( data,
					 DATASET_NAME );

  hdf5_file_handler.writeValueToDataSetAttribute( test_value_original,
						  DATASET_NAME,
						  ATTRIBUTE_NAME );
  
  Type test_value;
  hdf5_file_handler.readValueFromDataSetAttribute( test_value,
						   DATASET_NAME,
						   ATTRIBUTE_NAME );

  FACEMC_TEST_EQUALITY( test_value_original, test_value );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION( HDF5FileHandler, readValueFromDataSetAttribute );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write an Array of Type to a group
// attribute in an HDF5 file
FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL( HDF5FileHandler, 
						writeArrayToGroupAttribute,
						Type,
						Array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Array<Type> data; 
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( data, test_value );

  // If the group attribute is not written successfuly, an exception will be 
  // thrown and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToGroupAttribute( data,
						CHILD_GROUP,
						ATTRIBUTE_NAME );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToGroupAttribute, Array );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToGroupAttribute, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToGroupAttribute, ArrayView );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, writeArrayToGroupAttribute, TwoDArray );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read an Array of Type from a group
// attribute in an HDF5 file
FACEMC_UNIT_TEST_TEUCHOS_ARRAY_TEMPLATE_1_DECL( HDF5FileHandler, 
						readArrayFromGroupAttribute,
						Type,
						Array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  Array<Type> data_original; 
  FACEMC::ArrayTestingPolicy<Type,Array>::initialize( data_original, 
						      test_value );

  hdf5_file_handler.writeArrayToGroupAttribute( data_original,
						CHILD_GROUP,
						ATTRIBUTE_NAME );

  Array<Type> data;
  hdf5_file_handler.readArrayFromGroupAttribute( data,
						 CHILD_GROUP,
						 ATTRIBUTE_NAME );

  FACEMC_TEST_COMPARE_ARRAYS( data_original, data );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromGroupAttribute, Array );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromGroupAttribute, ArrayRCP );
UNIT_TEST_INSTANTIATION_ARRAY( HDF5FileHandler, readArrayFromGroupAttribute, TwoDArray );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a single value to a group
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, writeValueToGroupAttribute, Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value );

  // If the group attribute is not written successfuly, an exception will be 
  // thrown and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeValueToGroupAttribute( test_value,
						ROOT_GROUP,
						ATTRIBUTE_NAME );
  hdf5_file_handler.writeValueToGroupAttribute( test_value,
						CHILD_GROUP,
						ATTRIBUTE_NAME );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION( HDF5FileHandler, writeValueToGroupAttribute );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a single value from a group
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, readValueFromGroupAttribute, Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value_original, test_value;
  FACEMC::TypeTestingPolicy<Type>::initialize( test_value_original );

  hdf5_file_handler.writeValueToGroupAttribute( test_value_original,
						ROOT_GROUP,
						ATTRIBUTE_NAME );
  hdf5_file_handler.writeValueToGroupAttribute( test_value_original,
						CHILD_GROUP,
						ATTRIBUTE_NAME );

  hdf5_file_handler.readValueFromGroupAttribute( test_value,
  						 ROOT_GROUP,
  						 ATTRIBUTE_NAME );

  FACEMC_TEST_EQUALITY( test_value_original, test_value );
  
  hdf5_file_handler.readValueFromGroupAttribute( test_value,
						 CHILD_GROUP,
						 ATTRIBUTE_NAME );

  FACEMC_TEST_EQUALITY( test_value_original, test_value );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION( HDF5FileHandler, readValueFromGroupAttribute );

//---------------------------------------------------------------------------//
// end tstHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
