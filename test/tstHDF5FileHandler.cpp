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

// HDF5 Test File Names
#define HDF5_TEST_FILE_NAME "hdf5_test_file.h5"
#define DOUBLE_ARRAY_DATASET_NAME "/simple_types/double_array"
#define INT_ARRAY_DATASET_NAME "/simple_types/int_array"
#define UINT_ARRAY_DATASET_NAME "/simple_types/uint_array"
#define PAIR_DOUBLE_DOUBLE_ARRAY_DATASET_NAME "/compound_types/pair_double_double_array"
#define TRIP_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME "/compound_types/trip_uint_double_double_array"
#define QUAD_UINT_UINT_DOUBLE_DOUBLE_ARRAY_DATASET_NAME "/compound_types/quad_uint_uint_double_double_array"

// Test Values
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
// Check that the HDF5FileHandler can write an Teuchos::Array of FACEMC::Quad 
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
// Check that the HDF5FileHandler can write an Teuchos::ArrayRCP of 
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
// Check that the HDF5FileHandler can write an Teuchos::ArrayView of 
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
// Check that the HDF5FileHandler can write an Teuchos::TwoDArray of 
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
// end tstHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
