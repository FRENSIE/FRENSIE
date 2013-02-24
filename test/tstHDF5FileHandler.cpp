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

//---------------------------------------------------------------------------//
// HDF5 Test File Names.
//---------------------------------------------------------------------------//
#define HDF5_TEST_FILE_NAME "hdf5_test_file.h5"
#define DOUBLE_ARRAY_DATASET_NAME "/simple_types/double_array"
#define INT_ARRAY_DATASET_NAME "/simple_types/int_array"
#define UINT_ARRAY_DATASET_NAME "/simple_types/uint_array"
#define PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME "/compound_types/pair_double_double_array"
#define TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME "/compound_types/trip_uint_double_double_array"
#define QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME "/compound_types/quad_uint_uint_double_double_array"
#define QUAD_QUAD_QUAD_TRIP_PAIR_ARRAY_DATASET_NAME "/compound_types/quad_quad_quad_trip_pair_array"

//---------------------------------------------------------------------------//
// Test Values.
//---------------------------------------------------------------------------//
#define DOUBLE_TEST_VALUE 1.1
#define INT_TEST_VALUE 1
#define UINT_TEST_VALUE 2

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
TEUCHOS_UNIT_TEST( HDF5FileHandler, open_and_overwrite_file_test )
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
TEUCHOS_UNIT_TEST( HDF5FileHandler, open_and_read_write_file_test )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  // If the file is not opened successfully, an exception will be thrown
  // and caught inside the member function, causing a program exit. 
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.openHDF5FileAndAppend( HDF5_TEST_FILE_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can create the necessary parent groups
// for a dataset
TEUCHOS_UNIT_TEST( HDF5FileHandler, create_parent_groups_test )
{
  TestingHDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  // If the groups are not made successfully, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  
  hdf5_file_handler.createParentGroups( "/group1/group2/group3/dataset" );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of doubles to a 
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<double> data( 10, DOUBLE_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of ints to a 
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_int_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<int> data( 20, INT_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 INT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of unsigned ints 
// to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_uint_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<unsigned int> data( 30, UINT_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 UINT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of FACEMC::Pair 
// structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_pair_double_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Pair<double,double> > data( 5 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = DOUBLE_TEST_VALUE;
    data[i].second = DOUBLE_TEST_VALUE;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of FACEMC::Trip 
// structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_trip_uint_double_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data( 4 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = UINT_TEST_VALUE;
    data[i].second = DOUBLE_TEST_VALUE;
    data[i].third = DOUBLE_TEST_VALUE;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of FACEMC::Quad 
// structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_quad_uint_uint_double_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data( 3 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = UINT_TEST_VALUE;
    data[i].second = UINT_TEST_VALUE;
    data[i].third = DOUBLE_TEST_VALUE;
    data[i].fourth = DOUBLE_TEST_VALUE;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayRCP of doubles to a 
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<double> data( 10, DOUBLE_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayRCP of ints to a 
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_int_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<int> data( 20, INT_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 INT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayRCP of unsigned 
// ints to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_uint_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<unsigned int> data( 30, UINT_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 UINT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayRCP of FACEMC::Pair 
// structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_pair_double_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<FACEMC::Pair<double,double> > data( 5 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = DOUBLE_TEST_VALUE;
    data[i].second = DOUBLE_TEST_VALUE;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayRCP of FACEMC::Trip 
// structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_trip_uint_double_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<FACEMC::Trip<unsigned int,double,double> > data( 4 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = UINT_TEST_VALUE;
    data[i].second = DOUBLE_TEST_VALUE;
    data[i].third = DOUBLE_TEST_VALUE;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayRCP of 
// FACEMC::Quad structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_quad_uint_uint_double_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data( 3 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = UINT_TEST_VALUE;
    data[i].second = UINT_TEST_VALUE;
    data[i].third = DOUBLE_TEST_VALUE;
    data[i].fourth = DOUBLE_TEST_VALUE;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayView of doubles 
// to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_double_teuchos_arrayview )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<double> data_array( 10, DOUBLE_TEST_VALUE );
  Teuchos::ArrayView<double> data( data_array() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayView of ints to a 
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_int_teuchos_arrayview )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<int> data_array( 20, INT_TEST_VALUE );
  Teuchos::ArrayView<int> data( data_array() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 INT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayView of unsigned 
// ints to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_uint_teuchos_arrayview )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<unsigned int> data_array( 30, UINT_TEST_VALUE );
  Teuchos::ArrayView<unsigned int> data( data_array() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 UINT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayView of 
// FACEMC::Pair structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_pair_double_double_teuchos_arrayview )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Pair<double,double> > data_array( 5 );
  for( unsigned int i = 0; i < data_array.size(); ++i )
  {
    data_array[i].first = DOUBLE_TEST_VALUE;
    data_array[i].second = DOUBLE_TEST_VALUE;
  }
  Teuchos::ArrayView<FACEMC::Pair<double,double> > data( data_array() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayView of 
// FACEMC::Trip structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_trip_uint_double_double_teuchos_arrayview )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data_array( 4 );
  for( unsigned int i = 0; i < data_array.size(); ++i )
  {
    data_array[i].first = UINT_TEST_VALUE;
    data_array[i].second = DOUBLE_TEST_VALUE;
    data_array[i].third = DOUBLE_TEST_VALUE;
  }
  Teuchos::ArrayView<FACEMC::Trip<unsigned int,double,double> > 
    data( data_array() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::ArrayView of 
// FACEMC::Quad structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_quad_uint_uint_double_double_teuchos_arrayview )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data_array( 3 );
  for( unsigned int i = 0; i < data_array.size(); ++i )
  {
    data_array[i].first = UINT_TEST_VALUE;
    data_array[i].second = UINT_TEST_VALUE;
    data_array[i].third = DOUBLE_TEST_VALUE;
    data_array[i].fourth = DOUBLE_TEST_VALUE;
  }
  Teuchos::ArrayView<FACEMC::Quad<unsigned int,unsigned int,double,double> >
    data( data_array() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::TwoDArray of doubles 
// to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<double> data( 2, 10, DOUBLE_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::TwoDArray of ints to a 
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_int_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<int> data( 2, 20, INT_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 INT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::TwoDArray of unsigned 
// ints to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_uint_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<unsigned int> data( 3, 30, UINT_TEST_VALUE );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 UINT_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::TwoDArray of 
// FACEMC::Pair structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_pair_double_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<FACEMC::Pair<double,double> > data( 5, 5 );
  for( unsigned int i = 0; i < data.getNumRows(); ++i )
  {
    for( unsigned int j = 0; j < data.getNumCols(); ++j )
    {
      data[i][j].first = DOUBLE_TEST_VALUE;
      data[i][j].second = DOUBLE_TEST_VALUE;
    }
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::TwoDArray of 
// FACEMC::Trip structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_trip_uint_double_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<FACEMC::Trip<unsigned int,double,double> > data( 4, 4 );
  for( unsigned int i = 0; i < data.getNumRows(); ++i )
  {
    for( unsigned int j = 0; j < data.getNumCols(); ++j )
    {
      data[i][j].first = UINT_TEST_VALUE;
      data[i][j].second = DOUBLE_TEST_VALUE;
      data[i][j].third = DOUBLE_TEST_VALUE;
    }
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::TwoDArray of 
// FACEMC::Quad structs to a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_quad_uint_uint_double_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data( 3, 3 );
  for( unsigned int i = 0; i < data.getNumRows(); ++i )
  {
    for( unsigned int j = 0; j < data.getNumCols(); ++j )
    {
      data[i][j].first = UINT_TEST_VALUE;
      data[i][j].second = UINT_TEST_VALUE;
      data[i][j].third = DOUBLE_TEST_VALUE;
      data[i][j].fourth = DOUBLE_TEST_VALUE;
    }
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of
// FACEMC::Quad<FACEMC::Quad,FACEMC::Quad,FACEMC::Trip,FACEMC::Pair> structs
// to a dataset in an HDF5 file (recursive compound HDF5 type creation)
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_tuple_tuple_teuchos_array )
{
  typedef FACEMC::Quad<int,unsigned int,double,double> quad;
  typedef FACEMC::Trip<int,unsigned int,double> trip;
  typedef FACEMC::Pair<int,unsigned int> pair;

  quad quad_data;
  quad_data.first = INT_TEST_VALUE;
  quad_data.second = UINT_TEST_VALUE;
  quad_data.third = DOUBLE_TEST_VALUE;
  quad_data.fourth = DOUBLE_TEST_VALUE;

  trip trip_data;
  trip_data.first = INT_TEST_VALUE;
  trip_data.second = UINT_TEST_VALUE;
  trip_data.third = DOUBLE_TEST_VALUE;

  pair pair_data;
  pair_data.first = INT_TEST_VALUE;
  pair_data.second = UINT_TEST_VALUE;
  
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  Teuchos::Array<FACEMC::Quad<quad,quad,trip,pair> > data( 4 );
  for( unsigned int i = 0; i < data.size(); ++i )
  {
    data[i].first = quad_data;
    data[i].second = quad_data;
    data[i].third = trip_data;
    data[i].fourth = pair_data;
  }

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data,
					 QUAD_QUAD_QUAD_TRIP_PAIR_ARRAY_DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a single double to group attribute
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_double_to_group_attribute )
{
  TestingHDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  hdf5_file_handler.createParentGroups( "group1/garbage" );

  double value = DOUBLE_TEST_VALUE;

  // If the attribute is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeValueToGroupAttribute( value,
						"/",
						"attribute1" );
  hdf5_file_handler.writeValueToGroupAttribute( value,
						"/group1",
						"attribute2" );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a single int to dataset attribute
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_int_to_dataset_attribute )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<int> dataset_data( 10, INT_TEST_VALUE );

  int value = INT_TEST_VALUE;

  hdf5_file_handler.writeArrayToDataSet( dataset_data,
					 INT_ARRAY_DATASET_NAME );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeValueToDataSetAttribute( value,
						  INT_ARRAY_DATASET_NAME,
						  "attribute1");
  
  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a Teuchos::Array of unsigned ints
// to a group attribute
TEUCHOS_UNIT_TEST( HDF5FileHandler, write_uint_teuchos_array_to_group_attribute )
{
  TestingHDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  hdf5_file_handler.createParentGroups( "group1/garbage" );

  Teuchos::Array<unsigned int> data( 20, UINT_TEST_VALUE );

  // If the attribute is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToGroupAttribute( data,
						"/group1",
						"attribute1" );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of doubles from a
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<double> data_original( 10, DOUBLE_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::Array<double> data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of ints from a
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_int_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<int> data_original( 20, INT_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 INT_ARRAY_DATASET_NAME );

  Teuchos::Array<int> data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  INT_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of unsigned ints 
// from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_uint_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<unsigned int> data_original( 30, UINT_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 UINT_ARRAY_DATASET_NAME );

  Teuchos::Array<unsigned int> data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  UINT_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of FACEMC::Pair 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_pair_double_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Pair<double,double> > data_original( 5 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = DOUBLE_TEST_VALUE;
    data_original[i].second = DOUBLE_TEST_VALUE;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::Array<FACEMC::Pair<double,double> > data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of FACEMC::Trip 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_trip_unit_double_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data_original( 5 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = UINT_TEST_VALUE;
    data_original[i].second = DOUBLE_TEST_VALUE;
    data_original[i].third = DOUBLE_TEST_VALUE;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );
  
  hdf5_file_handler.closeHDF5File();
}

// Check that the HDF5FileHandler can read a Teuchos::Array of FACEMC::Quad 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_quad_uint_unit_double_double_teuchos_array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data_original( 3 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = UINT_TEST_VALUE;
    data_original[i].second = UINT_TEST_VALUE;
    data_original[i].third = DOUBLE_TEST_VALUE;
    data_original[i].fourth = DOUBLE_TEST_VALUE;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );
  
  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::ArrayRCP of doubles from a
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<double> data_original( 10, DOUBLE_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::ArrayRCP<double> data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::ArrayRCP of ints from a
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_int_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<int> data_original( 20, INT_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 INT_ARRAY_DATASET_NAME );

  Teuchos::ArrayRCP<int> data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  INT_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::ArrayRCP of unsigned ints 
// from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_uint_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<unsigned int> data_original( 30, UINT_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 UINT_ARRAY_DATASET_NAME );

  Teuchos::ArrayRCP<unsigned int> data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  UINT_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::ArrayRCP of FACEMC::Pair 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_pair_double_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<FACEMC::Pair<double,double> > data_original( 5 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = DOUBLE_TEST_VALUE;
    data_original[i].second = DOUBLE_TEST_VALUE;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::ArrayRCP<FACEMC::Pair<double,double> > data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::ArrayRCP of FACEMC::Trip 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_trip_unit_double_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<FACEMC::Trip<unsigned int,double,double> > 
    data_original( 5 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = UINT_TEST_VALUE;
    data_original[i].second = DOUBLE_TEST_VALUE;
    data_original[i].third = DOUBLE_TEST_VALUE;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::ArrayRCP<FACEMC::Trip<unsigned int,double,double> > data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );
  
  hdf5_file_handler.closeHDF5File();
}

// Check that the HDF5FileHandler can read a Teuchos::ArrayRCP of FACEMC::Quad 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_quad_uint_unit_double_double_teuchos_arrayrcp )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::ArrayRCP<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data_original( 3 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = UINT_TEST_VALUE;
    data_original[i].second = UINT_TEST_VALUE;
    data_original[i].third = DOUBLE_TEST_VALUE;
    data_original[i].fourth = DOUBLE_TEST_VALUE;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::ArrayRCP<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data;
  hdf5_file_handler.readArrayFromDataSet( data,
					  QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );
  
  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::TwoDArray of doubles 
// from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<double> data_original( 10, 10, DOUBLE_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::TwoDArray<double> data( 1, 10 );
  hdf5_file_handler.readArrayFromDataSet( data,
					  DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data.getDataArray(), data_original.getDataArray() );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::TwoDArray of ints from a
// dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_int_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<int> data_original( 20, 20, INT_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 INT_ARRAY_DATASET_NAME );

  Teuchos::TwoDArray<int> data( 1, 20 );
  hdf5_file_handler.readArrayFromDataSet( data,
					  INT_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data.getDataArray(), data_original.getDataArray() );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::TwoDArray of unsigned 
//ints from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_uint_teuchos_twoDarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<unsigned int> data_original( 30, 30, UINT_TEST_VALUE );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 UINT_ARRAY_DATASET_NAME );

  Teuchos::TwoDArray<unsigned int> data( 1, 30);
  hdf5_file_handler.readArrayFromDataSet( data,
					  UINT_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data.getDataArray(), data_original.getDataArray() );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::TwoDArray of FACEMC::Pair 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_pair_double_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<FACEMC::Pair<double,double> > data_original( 5, 5 );
  for( unsigned int i = 0; i < data_original.getNumRows(); ++i )
  {
    for( unsigned int j = 0; j < data_original.getNumCols(); ++j )
    {
      data_original[i][j].first = DOUBLE_TEST_VALUE;
      data_original[i][j].second = DOUBLE_TEST_VALUE;
    }
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::TwoDArray<FACEMC::Pair<double,double> > data( 1, 5 );
  hdf5_file_handler.readArrayFromDataSet( data,
					  PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data.getDataArray(), data_original.getDataArray() );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::TwoDArray of FACEMC::Trip 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_trip_unit_double_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<FACEMC::Trip<unsigned int,double,double> > 
    data_original( 5, 5 );
  for( unsigned int i = 0; i < data_original.getNumRows(); ++i )
  {
    for( unsigned int j = 0; j < data_original.getNumCols(); ++j )
    {
      data_original[i][j].first = UINT_TEST_VALUE;
      data_original[i][j].second = DOUBLE_TEST_VALUE;
      data_original[i][j].third = DOUBLE_TEST_VALUE;
    }
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::TwoDArray<FACEMC::Trip<unsigned int,double,double> > data( 1, 5 );
  hdf5_file_handler.readArrayFromDataSet( data,
					  TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data.getDataArray(), data_original.getDataArray() );
  
  hdf5_file_handler.closeHDF5File();
}

// Check that the HDF5FileHandler can read a Teuchos::TwoDArray of FACEMC::Quad 
// structs from a dataset in an HDF5 file
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_quad_uint_unit_double_double_teuchos_twodarray )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::TwoDArray<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data_original( 3, 3 );
  for( unsigned int i = 0; i < data_original.getNumRows(); ++i )
  {
    for( unsigned int j = 0; j < data_original.getNumCols(); ++j )
    {
      data_original[i][j].first = UINT_TEST_VALUE;
      data_original[i][j].second = UINT_TEST_VALUE;
      data_original[i][j].third = DOUBLE_TEST_VALUE;
      data_original[i][j].fourth = DOUBLE_TEST_VALUE;
    }
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  Teuchos::TwoDArray<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data( 1, 3);
  hdf5_file_handler.readArrayFromDataSet( data,
					  QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data.getDataArray(), data_original.getDataArray() );
  
  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of
// FACEMC::Quad<FACEMC::Quad,FACEMC::Quad,FACEMC::Trip,FACEMC::Pair> structs
// from a dataset in an HDF5 file (recursive compound HDF5 type creation)
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_tuple_tuple_teuchos_array )
{
  typedef FACEMC::Quad<int,unsigned int,double,double> quad;
  typedef FACEMC::Trip<int,unsigned int,double> trip;
  typedef FACEMC::Pair<int,unsigned int> pair;

  quad quad_data;
  quad_data.first = INT_TEST_VALUE;
  quad_data.second = UINT_TEST_VALUE;
  quad_data.third = DOUBLE_TEST_VALUE;
  quad_data.fourth = DOUBLE_TEST_VALUE;

  trip trip_data;
  trip_data.first = INT_TEST_VALUE;
  trip_data.second = UINT_TEST_VALUE;
  trip_data.third = DOUBLE_TEST_VALUE;

  pair pair_data;
  pair_data.first = INT_TEST_VALUE;
  pair_data.second = UINT_TEST_VALUE;
  
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  Teuchos::Array<FACEMC::Quad<quad,quad,trip,pair> > data_original( 4 );
  for( unsigned int i = 0; i < data_original.size(); ++i )
  {
    data_original[i].first = quad_data;
    data_original[i].second = quad_data;
    data_original[i].third = trip_data;
    data_original[i].fourth = pair_data;
  }

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 QUAD_QUAD_QUAD_TRIP_PAIR_ARRAY_DATASET_NAME );
  
  Teuchos::Array<FACEMC::Quad<quad,quad,trip,pair> > data;

  hdf5_file_handler.readArrayFromDataSet( data,
					  QUAD_QUAD_QUAD_TRIP_PAIR_ARRAY_DATASET_NAME );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a single double from a group 
// attribute
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_double_from_group_attribute )
{
  TestingHDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  hdf5_file_handler.createParentGroups( "group1/garbage" );

  double value_original = DOUBLE_TEST_VALUE;

  hdf5_file_handler.writeValueToGroupAttribute( value_original,
						"/group1",
						"attribute1" );
  
  double value;

  hdf5_file_handler.readValueFromGroupAttribute( value,
						 "/group1",
						 "attribute1" );

  TEST_EQUALITY( value, value_original )

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a single int from a dataset attribute
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_int_from_dataset_attribute )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Teuchos::Array<int> dataset_data( 10, INT_TEST_VALUE );

  int value_original = INT_TEST_VALUE;

  hdf5_file_handler.writeArrayToDataSet( dataset_data,
					 INT_ARRAY_DATASET_NAME );

  hdf5_file_handler.writeValueToDataSetAttribute( value_original,
						  INT_ARRAY_DATASET_NAME,
						  "attribute1" );

  int value;

  hdf5_file_handler.readValueFromDataSetAttribute( value,
						   INT_ARRAY_DATASET_NAME,
						   "attribute1" );

  TEST_EQUALITY( value, value_original );
  
  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read a Teuchos::Array of unsigned ints
// from a group attribute
TEUCHOS_UNIT_TEST( HDF5FileHandler, read_uint_teuchos_array_to_group_attribute )
{
  TestingHDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );
  
  hdf5_file_handler.createParentGroups( "group1/garbage" );

  Teuchos::Array<unsigned int> data_original( 20, UINT_TEST_VALUE );

  hdf5_file_handler.writeArrayToGroupAttribute( data_original,
						"/group1",
						"attribute1" );

  Teuchos::Array<unsigned int> data;

  hdf5_file_handler.readArrayFromGroupAttribute( data,
						 "/group1",
						 "attribute1" );

  TEST_COMPARE_ARRAYS( data, data_original );

  hdf5_file_handler.closeHDF5File();
}

//---------------------------------------------------------------------------//
// end tstHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
