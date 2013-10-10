//---------------------------------------------------------------------------//
//!
//! \file   tstHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  HDF5FileHandler class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <vector>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "HDF5TypeTraits.hpp"
#include "Tuple.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

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
#define UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( type, name, array )	\
  UNIT_TEST_INSTANTIATION_ARRAY( type, name, Teuchos, array )		\

#define UNIT_TEST_INSTANTIATION_STD_VECTOR( type, name )	\
  UNIT_TEST_INSTANTIATION_ARRAY( type, name, std, vector )	\

#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, space, array )	\
  typedef space::array<float> array##_f;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_f )		\
  typedef space::array<double> array##_d;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_d )		\
  typedef space::array<unsigned> array##_u;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_u )		\
  typedef space::array<int> array##_i;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_i )		\
  typedef space::array<FACEMC::Pair<float,float> > array##_pair_f_f; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_f_f )	\
  typedef space::array<FACEMC::Pair<double,double> > array##_pair_d_d; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_d_d )	\
  typedef space::array<FACEMC::Pair<unsigned,unsigned> >		\
  array##_pair_u_u;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_u_u )	\
  typedef space::array<FACEMC::Pair<int,int> > array##_pair_i_i;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_i_i )	\
  typedef space::array<FACEMC::Pair<float,double> > array##_pair_f_d; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_f_d ) \
  typedef space::array<FACEMC::Pair<float,unsigned> > array##_pair_f_u; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_f_u )	\
  typedef space::array<FACEMC::Pair<float,int> > array##_pair_f_i;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_f_i )	\
  typedef space::array<FACEMC::Pair<double,float> > array##_pair_d_f; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_d_f )	\
  typedef space::array<FACEMC::Pair<double,unsigned> > array##_pair_d_u; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_d_u )	\
  typedef space::array<FACEMC::Pair<double,int> > array##_pair_d_i;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_d_i )	\
  typedef space::array<FACEMC::Pair<unsigned,float> > array##_pair_u_f; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_u_f )	\
  typedef space::array<FACEMC::Pair<unsigned,double> > array##_pair_u_d; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_u_d )	\
  typedef space::array<FACEMC::Pair<unsigned,int> > array##_pair_u_i; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_u_i )	\
  typedef space::array<FACEMC::Pair<int,float> > array##_pair_i_f;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_i_f )	\
  typedef space::array<FACEMC::Pair<int,double> > array##_pair_i_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_i_d )	\
  typedef space::array<FACEMC::Pair<int,unsigned> > array##_pair_i_u; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_pair_i_u )	\
  typedef space::array<FACEMC::Trip<float,float,float> >		\
  array##_trip_f_f_f;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_trip_f_f_f ) \
  typedef space::array<FACEMC::Trip<double,double,double> >		\
  array##_trip_d_d_d;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_trip_d_d_d ) \
  typedef space::array<FACEMC::Trip<unsigned,unsigned,unsigned> >	\
  array##_trip_u_u_u;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_trip_u_u_u ) \
  typedef space::array<FACEMC::Trip<int,int,int> >			\
  array##_trip_i_i_i;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_trip_i_i_i ) \
  typedef space::array<FACEMC::Trip<double,float,int> >		\
  array##_trip_d_f_i;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_trip_d_f_i ) \
  typedef space::array<FACEMC::Trip<unsigned,double,float> >	\
  array##_trip_u_d_f;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_trip_u_d_f ) \
  typedef space::array<FACEMC::Quad<float,float,float,float> >	\
  array##_quad_f_f_f_f;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_quad_f_f_f_f ) \
  typedef space::array<FACEMC::Quad<double,double,double,double> >	\
  array##_quad_d_d_d_d;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_quad_d_d_d_d ) \
  typedef space::array<FACEMC::Quad<unsigned,unsigned,unsigned,unsigned> >\
  array##_quad_u_u_u_u;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_quad_u_u_u_u ) \
  typedef space::array<FACEMC::Quad<int,int,int,int> >		\
  array##_quad_i_i_i_i;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_quad_i_i_i_i ) \
  typedef space::array<FACEMC::Quad<float,double,unsigned,int> >	\
  array##_quad_f_d_u_i;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_quad_f_d_u_i ) \
  typedef space::array<FACEMC::Quad<int,unsigned,double,float> >	\
  array##_quad_i_u_d_f;							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, array##_quad_i_u_d_f ) \
  
#define UNIT_TEST_INSTANTIATION( type, name )				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int )		\
  typedef FACEMC::Pair<int,int> pair_i_i;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_i_i )		\
  typedef FACEMC::Pair<unsigned,unsigned> pair_u_u;			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_u_u )		\
  typedef FACEMC::Pair<float,float> pair_f_f;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_f_f )		\
  typedef FACEMC::Pair<double,double> pair_d_d;				\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_d_d )		\
  typedef FACEMC::Pair<unsigned,double> pair_u_d;			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_u_d )		\
  typedef FACEMC::Pair<double,unsigned> pair_d_u;			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_d_u )		\
  typedef FACEMC::Trip<unsigned,unsigned,unsigned> trip_u_u_u;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_u_u_u )	\
  typedef FACEMC::Trip<double,double,double> trip_d_d_d;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_d_d_d )	\
  typedef FACEMC::Trip<unsigned,unsigned,double> trip_u_u_d;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_u_u_d )	\
  typedef FACEMC::Trip<unsigned,double,unsigned> trip_u_d_u;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_u_d_u )	\
  typedef FACEMC::Trip<unsigned,double,double> trip_u_d_d;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_u_d_d )	\
  typedef FACEMC::Trip<double,double,unsigned> trip_d_d_u;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_d_d_u )	\
  typedef FACEMC::Trip<double,unsigned,double> trip_d_u_d;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_d_u_d )	\
  typedef FACEMC::Trip<double,unsigned,unsigned> trip_d_u_u;		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_d_u_u )	\
  typedef FACEMC::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_u_u_u )	\
  typedef FACEMC::Quad<double,double,double,double> quad_d_d_d_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_d_d_d )	\
  typedef FACEMC::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_u_u_d )	\
  typedef FACEMC::Quad<unsigned,unsigned,double,unsigned> quad_u_u_d_u; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_u_d_u )	\
  typedef FACEMC::Quad<unsigned,double,unsigned,unsigned> quad_u_d_u_u; \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_d_u_u )	\
  typedef FACEMC::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_u_d_d )	\
  typedef FACEMC::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_d_u_d )	\
  typedef FACEMC::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_d_d_u )	\
  typedef FACEMC::Quad<unsigned,double,double,double> quad_u_d_d_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_d_d_d )	\
  typedef FACEMC::Quad<double,double,double,unsigned> quad_d_d_d_u;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_d_d_u )	\
  typedef FACEMC::Quad<double,unsigned,double,double> quad_d_u_d_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_u_d_d )	\
  typedef FACEMC::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_d_u_u )	\
  typedef FACEMC::Quad<double,unsigned,double,unsigned> quad_d_u_d_u;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_u_d_u )	\
  typedef FACEMC::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_u_u_d )	\
  typedef FACEMC::Quad<double,unsigned,unsigned,unsigned> quad_d_u_u_u;	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_u_u_u )	\

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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   writeArrayToDataSet,
				   array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  typedef typename FACEMC::Traits::ArrayTraits<array>::value_type value_type;
  
  value_type test_value = FACEMC::Traits::HDF5TypeTraits<value_type>::zero();

  Teuchos::Array<value_type> raw_data( 100, test_value );
  
  array data;
  FACEMC::copyArrayView( data, raw_data() );

  // If the dataset is not written successfuly, an exception will be thrown
  // and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSet( data, DATASET_NAME );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSet, 
				       Array );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSet, 
				       ArrayRCP );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSet, 
				       TwoDArray );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSet, 
				       ArrayView );
UNIT_TEST_INSTANTIATION_STD_VECTOR( HDF5FileHandler, writeArrayToDataSet );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read an Array of Type from a dataset
// in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   readArrayFromDataSet,
				   array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  typedef typename FACEMC::Traits::ArrayTraits<array>::value_type value_type;
  
  value_type test_value = FACEMC::Traits::HDF5TypeTraits<value_type>::one();

  Teuchos::Array<value_type> raw_data( 100, test_value );
  
  array data_original;
  FACEMC::copyArrayView( data_original, raw_data() );

  hdf5_file_handler.writeArrayToDataSet( data_original,
					 DATASET_NAME );

  array data;
  hdf5_file_handler.readArrayFromDataSet( data,
  					  DATASET_NAME );

  FACEMC_TEST_COMPARE_ARRAYS( data_original, data );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromDataSet,
				       Array );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromDataSet,
				       ArrayRCP );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromDataSet,
				       TwoDArray );
UNIT_TEST_INSTANTIATION_STD_VECTOR( HDF5FileHandler, readArrayFromDataSet );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write an Array of Type to a dataset
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   writeArrayToDataSetAttribute,
				   array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  typedef typename FACEMC::Traits::ArrayTraits<array>::value_type value_type;

  value_type test_value = FACEMC::Traits::HDF5TypeTraits<value_type>::one();

  Teuchos::Array<value_type> raw_data( 100, test_value );
  array set_data; 
  FACEMC::copyArrayView( set_data, raw_data() );

  hdf5_file_handler.writeArrayToDataSet( set_data,
					 DATASET_NAME );

  array data;
  FACEMC::copyArrayView( data, raw_data() );

  // If the dataset attribute is not written successfuly, an exception will be 
  // thrown and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToDataSetAttribute( data,
						  DATASET_NAME,
						  ATTRIBUTE_NAME );
  
  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSetAttribute,
				       Array );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSetAttribute,
				       ArrayRCP );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSetAttribute,
				       TwoDArray );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToDataSetAttribute,
				       ArrayView );
UNIT_TEST_INSTANTIATION_STD_VECTOR( HDF5FileHandler, 
				    writeArrayToDataSetAttribute );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read an Array of Type from a dataset
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   readArrayFromDataSetAttribute,
				   array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  typedef typename FACEMC::Traits::ArrayTraits<array>::value_type  value_type;

  value_type test_value = FACEMC::Traits::HDF5TypeTraits<value_type>::one();

  Teuchos::Array<value_type> raw_data( 100, test_value );
  array set_data;
  FACEMC::copyArrayView( set_data, raw_data() );

  hdf5_file_handler.writeArrayToDataSet( set_data,
					 DATASET_NAME );

  array data_original;
  FACEMC::copyArrayView( data_original, raw_data() );
  
  hdf5_file_handler.writeArrayToDataSetAttribute( data_original,
						  DATASET_NAME,
						  ATTRIBUTE_NAME );

  array data;
  hdf5_file_handler.readArrayFromDataSetAttribute( data,
						   DATASET_NAME,
						   ATTRIBUTE_NAME );
  
  FACEMC_TEST_COMPARE_ARRAYS( data_original, data );
  
  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromDataSetAttribute,
				       Array );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromDataSetAttribute,
				       ArrayRCP );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromDataSetAttribute,
				       TwoDArray );
UNIT_TEST_INSTANTIATION_STD_VECTOR( HDF5FileHandler, 
				    readArrayFromDataSetAttribute );
				    
//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a single value to a dataset
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   writeValueToDataSetAttribute, 
				   Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value = FACEMC::Traits::HDF5TypeTraits<Type>::one();

  Teuchos::Array<Type> data( 100, test_value ); 
  
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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   readValueFromDataSetAttribute, 
				   Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value_original = FACEMC::Traits::HDF5TypeTraits<Type>::one();
  
  Teuchos::Array<Type> data( 100, test_value_original ); 

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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   writeArrayToGroupAttribute,
				   array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  typedef typename FACEMC::Traits::ArrayTraits<array>::value_type value_type;

  value_type test_value = FACEMC::Traits::HDF5TypeTraits<value_type>::one();

  Teuchos::Array<value_type> raw_data( 100, test_value );
  array data;
  FACEMC::copyArrayView( data, raw_data() );

  // If the group attribute is not written successfuly, an exception will be 
  // thrown and caught inside of the member function, causing a program exit.
  // Therefore, no TEST macro is needed.
  hdf5_file_handler.writeArrayToGroupAttribute( data,
						CHILD_GROUP,
						ATTRIBUTE_NAME );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToGroupAttribute,
				       Array );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToGroupAttribute,
				       ArrayRCP );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToGroupAttribute,
				       TwoDArray );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       writeArrayToGroupAttribute,
				       ArrayView );
UNIT_TEST_INSTANTIATION_STD_VECTOR( HDF5FileHandler, 
				    writeArrayToGroupAttribute );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can read an Array of Type from a group
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, 
				   readArrayFromGroupAttribute,
				   array )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  typedef typename FACEMC::Traits::ArrayTraits<array>::value_type value_type;

  value_type test_value = FACEMC::Traits::HDF5TypeTraits<value_type>::one();
 
  Teuchos::Array<value_type> raw_data( 100, test_value );
  array data_original;
  FACEMC::copyArrayView( data_original, raw_data() );
  
  hdf5_file_handler.writeArrayToGroupAttribute( data_original,
						CHILD_GROUP,
						ATTRIBUTE_NAME );

  array data;
  hdf5_file_handler.readArrayFromGroupAttribute( data,
						 CHILD_GROUP,
						 ATTRIBUTE_NAME );

  FACEMC_TEST_COMPARE_ARRAYS( data_original, data );

  hdf5_file_handler.closeHDF5File();
}

UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromGroupAttribute,
				       Array );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromGroupAttribute,
				       ArrayRCP );
UNIT_TEST_INSTANTIATION_TEUCHOS_ARRAY( HDF5FileHandler, 
				       readArrayFromGroupAttribute,
				       TwoDArray );
UNIT_TEST_INSTANTIATION_STD_VECTOR( HDF5FileHandler, 
				    readArrayFromGroupAttribute );

//---------------------------------------------------------------------------//
// Check that the HDF5FileHandler can write a single value to a group
// attribute in an HDF5 file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HDF5FileHandler, writeValueToGroupAttribute, Type )
{
  FACEMC::HDF5FileHandler hdf5_file_handler;

  hdf5_file_handler.openHDF5FileAndOverwrite( HDF5_TEST_FILE_NAME );

  Type test_value = FACEMC::Traits::HDF5TypeTraits<Type>::one();
 
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
  test_value_original = FACEMC::Traits::HDF5TypeTraits<Type>::zero();

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
