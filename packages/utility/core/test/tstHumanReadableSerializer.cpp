//---------------------------------------------------------------------------//
//!
//! \file   tstHumanReadableSerializer.cpp
//! \author Alex Robinson
//! \brief  Human-readable serializer unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_HumanReadableSerializer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef std::string string;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
void initialize( std::string& obj )
{ obj = "100"; }

template<typename T>
void initialize( T& obj )
{ obj = 100; }

template<typename T>
void initialize( Utility::Tuple<T>& tuple )
{
  initialize( Utility::get<0>( tuple ) );
}

template<typename T1, typename T2>
void initialize( Utility::Tuple<T1,T2>& tuple )
{
  initialize( Utility::get<0>( tuple ) );
  initialize( Utility::get<1>( tuple ) );
}

template<typename T1, typename T2>
void initialize( std::pair<T1,T2>& pair )
{
  initialize( pair.first );
  initialize( pair.second );
}

template<typename T1, typename T2, typename T3>
void initialize( Utility::Tuple<T1,T2,T3>& tuple )
{
  initialize( Utility::get<0>( tuple ) );
  initialize( Utility::get<1>( tuple ) );
  initialize( Utility::get<2>( tuple ) );
}

template<typename T1, typename T2, typename T3, typename T4>
void initialize( Utility::Tuple<T1,T2,T3,T4>& tuple )
{
  initialize( Utility::get<0>( tuple ) );
  initialize( Utility::get<1>( tuple ) );
  initialize( Utility::get<2>( tuple ) );
  initialize( Utility::get<3>( tuple ) );
}

template<template<typename,typename...> class Array, typename T>
void initialize( Array<T>& array )
{
  array.resize( 5 );

  initialize( array[0] );
  initialize( array[1] );
  initialize( array[2] );
  initialize( array[3] );
  initialize( array[4] );
}

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, short );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ushort );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulong );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, longlong );        \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ulonglong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, string )

#define UNIT_TEST_TEMPLATE_1_INSTANT_FLOAT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, float );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )

#define UNIT_TEST_TEMPLATE_2_INSTANT( type, name )  \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int );         \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, uint, uint );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, long );       \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ulong, ulong );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, longlong, longlong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, ulonglong, ulonglong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, string, string );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, string );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, string, int )

#define UNIT_TEST_TEMPLATE_3_INSTANT( type, name )  \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, int, int );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, uint, uint, uint ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, long, long, long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, ulong, ulong, ulong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, longlong, longlong, longlong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, ulonglong, ulonglong, ulonglong ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, string, string, string ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, string, ulong, int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, ulong, int, string ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, int, string, ulong )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a basic int type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   serialize_basic,
                                   T )
{
  T object;
  initialize( object );

  // Stream serializer
  std::ostringstream oss;
    
  Utility::HumanReadableSerializer<T>::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "100" );

  // String serializer
  std::string object_string =
    Utility::HumanReadableSerializer<T>::serialize( object );

  TEST_EQUALITY_CONST( object_string, "100" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, serialize_basic );

//---------------------------------------------------------------------------//
// Check that a basic float type can be serialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, serialize_float )
{
  float object;
  initialize( object );

  // Stream serializer
  std::ostringstream oss;
    
  Utility::HumanReadableSerializer<float>::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "1.000000000e+02" );

  // String serializer
  std::string object_string =
    Utility::HumanReadableSerializer<float>::serialize( object );

  TEST_EQUALITY_CONST( object_string, "1.000000000e+02" );
}

//---------------------------------------------------------------------------//
// Check that a basic float type can be serialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, serialize_double )
{
  double object;
  initialize( object );

  // Stream serializer
  std::ostringstream oss;
    
  Utility::HumanReadableSerializer<double>::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "1.000000000000000000e+02" );

  // String serializer
  std::string object_string =
    Utility::HumanReadableSerializer<double>::serialize( object );

  TEST_EQUALITY_CONST( object_string, "1.000000000000000000e+02" );
}

//---------------------------------------------------------------------------//
// Check that a basic type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   deserialize_basic,
                                   T )
{
  T test_object;
  initialize( test_object );
  
  T object = Utility::HumanReadableSerializer<T>::deserialize( "100" );

  TEST_EQUALITY_CONST( object, test_object );

  std::istringstream iss( "100" );

  object = Utility::HumanReadableSerializer<T>::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, deserialize_basic );

//---------------------------------------------------------------------------//
// Check that a basic type can be deserialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, deserialize_float )
{
  float test_object;
  initialize( test_object );
  
  float object = Utility::HumanReadableSerializer<float>::deserialize( "100" );

  TEST_EQUALITY_CONST( object, test_object );

  std::istringstream iss( "100" );

  object = Utility::HumanReadableSerializer<float>::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  iss.str( "1.0e2" );
  iss.clear();

  object = Utility::HumanReadableSerializer<float>::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

//---------------------------------------------------------------------------//
// Check that a basic type can be deserialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, deserialize_double )
{
  double test_object;
  initialize( test_object );
  
  double object = Utility::HumanReadableSerializer<double>::deserialize( "100" );

  TEST_EQUALITY_CONST( object, test_object );

  std::istringstream iss( "100" );

  object = Utility::HumanReadableSerializer<double>::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  iss.str( "1.0e2" );
  iss.clear();

  object = Utility::HumanReadableSerializer<double>::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   serialize_tuple_1,
                                   T )
{
  Utility::Tuple<T> object;
  initialize( object );

  std::ostringstream oss;
  
  Utility::HumanReadableSerializer<Utility::Tuple<T> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{100}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<T> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<T> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100}" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, serialize_tuple_1 );

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, serialize_tuple_1_float )
{
  Utility::Tuple<float> object;
  initialize( object );

  std::ostringstream oss;
  
  Utility::HumanReadableSerializer<Utility::Tuple<float> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<float> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<float> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000e+02}" );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, serialize_tuple_1_double )
{
  Utility::Tuple<double> object;
  initialize( object );

  std::ostringstream oss;
  
  Utility::HumanReadableSerializer<Utility::Tuple<double> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<double> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<double> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000000000000e+02}" );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   deserialize_tuple_1,
                                   T )
{
  Utility::Tuple<T> test_object;
  initialize( test_object );
  
  Utility::Tuple<T> object = 
    Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( "{100}" );

  TEST_EQUALITY_CONST( object, test_object );

  std::istringstream iss( "{100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100} " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( " { 100 } " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T> >::deserialize( iss );
  
  TEST_EQUALITY_CONST( object, test_object );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, deserialize_tuple_1 );


//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, deserialize_tuple_float )
{
  Utility::Tuple<float> test_object;
  initialize( test_object );
  
  Utility::Tuple<float> object = 
    Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( "{100}" );

  TEST_EQUALITY_CONST( object, test_object );

  std::istringstream iss( "{100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100. }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 1e2 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100.0} " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( " { 1.0e+02 } " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<float> >::deserialize( iss );
  
  TEST_EQUALITY_CONST( object, test_object );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, deserialize_tuple_double )
{
  Utility::Tuple<double> test_object;
  initialize( test_object );
  
  Utility::Tuple<double> object = 
    Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( "{100}" );

  TEST_EQUALITY_CONST( object, test_object );

  std::istringstream iss( "{100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100. }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 1e2 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100.0} " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( " { 1.0e+02 } " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double> >::deserialize( iss );
  
  TEST_EQUALITY_CONST( object, test_object );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( HumanReadableSerializer,
                                   serialize_tuple_2,
                                   T1, T2 )
{
  Utility::Tuple<T1,T2> object;
  initialize( object );

  std::ostringstream oss;

  Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{100, 100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100, 100}" );
}

UNIT_TEST_TEMPLATE_2_INSTANT( HumanReadableSerializer, serialize_tuple_2 );

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, serialize_tuple_2_float )
{
  Utility::Tuple<float,float> object;
  initialize( object );

  std::ostringstream oss;

  Utility::HumanReadableSerializer<Utility::Tuple<float,float> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02, 1.000000000e+02}" );

  std::string object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<float,float> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000e+02, 1.000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<double,double> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02, 1.000000000000000000e+02}" );

  object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<double,double> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000000000000e+02, 1.000000000000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<float,double> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02, 1.000000000000000000e+02}" );

  object_string = Utility::HumanReadableSerializer<Utility::Tuple<float,double> >::serialize( object );

  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02, 1.000000000000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02, 1.000000000e+02}" );

  object_string = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::serialize( object );

  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02, 1.000000000e+02}" );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( HumanReadableSerializer,
                                   deserialize_tuple_2,
                                   T1, T2 )
{
  Utility::Tuple<T1,T2> test_object;
  initialize( test_object );

  Utility::Tuple<T1,T2> object = 
    Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( "{100,100}" );

  TEST_EQUALITY_CONST( object, test_object );

  // no white space
  std::istringstream iss( "{100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100, 100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100,100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100, 100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100,100} " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( "  { 100 , 100 }  " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

UNIT_TEST_TEMPLATE_2_INSTANT( HumanReadableSerializer, deserialize_tuple_2 );

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, deserialize_tuple_2_float )
{
  Utility::Tuple<double,float> test_object;
  initialize( test_object );

  Utility::Tuple<double,float> object = 
    Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( "{100.0,100}" );

  TEST_EQUALITY_CONST( object, test_object );

  // no white space
  std::istringstream iss( "{100,100.}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {1.0e2,1.0000000e+02}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100, 100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100,100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100, 100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100,100} " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( "  { 100 , 100 }  " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<double,float> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( HumanReadableSerializer,
                                   serialize_pair_2,
                                   T1, T2 )
{
  std::pair<T1,T2> object;
  initialize( object );

  std::ostringstream oss;

  Utility::HumanReadableSerializer<std::pair<T1,T2> >::serialize( oss, object );
  
  TEST_EQUALITY_CONST( oss.str(), "{100, 100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<std::pair<T1,T2> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100, 100}" );
}

UNIT_TEST_TEMPLATE_2_INSTANT( HumanReadableSerializer, serialize_pair_2 );

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, serialize_pair_float )
{
  std::pair<float,float> object;
  initialize( object );

  std::ostringstream oss;

  Utility::HumanReadableSerializer<std::pair<float,float> >::serialize( oss, object );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02, 1.000000000e+02}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<std::pair<float,float> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000e+02, 1.000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<std::pair<double,double> >::serialize( oss, object );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02, 1.000000000000000000e+02}" );
  
  object_string =
    Utility::HumanReadableSerializer<std::pair<double,double> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000000000000e+02, 1.000000000000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<std::pair<float,double> >::serialize( oss, object );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000e+02, 1.000000000000000000e+02}" );
  
  object_string =
    Utility::HumanReadableSerializer<std::pair<float,double> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000e+02, 1.000000000000000000e+02}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<std::pair<double,float> >::serialize( oss, object );
  
  TEST_EQUALITY_CONST( oss.str(), "{1.000000000000000000e+02, 1.000000000e+02}" );
  
  object_string =
    Utility::HumanReadableSerializer<std::pair<double,float> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{1.000000000000000000e+02, 1.000000000e+02}" );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( HumanReadableSerializer,
                                   deserialize_pair_2,
                                   T1, T2 )
{
  std::pair<T1,T2> test_object;
  initialize( test_object );

  std::pair<T1,T2> object = 
    Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( "{100,100}" );

  TEST_EQUALITY_CONST( object, test_object );

  // no white space
  std::istringstream iss( "{100,100}" );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {100,100}" );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100,100}" );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100, 100}" );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100,100 }" );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100, 100 }" );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100,100} " );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( "  { 100 , 100 }  " );

  object = Utility::HumanReadableSerializer<std::pair<T1,T2> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

UNIT_TEST_TEMPLATE_2_INSTANT( HumanReadableSerializer, deserialize_pair_2 );

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST( HumanReadableSerializer, deserialize_pair_2_float )
{
  std::pair<float,double> test_object;
  initialize( test_object );

  std::pair<float,double> object = 
    Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( "{100,100}" );

  TEST_EQUALITY_CONST( object, test_object );

  // no white space
  std::istringstream iss( "{100,100}" );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( " {100,100.}" );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100.,100}" );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100.0, 100}" );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100,100.0 }" );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 1e2, 100 }" );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100,1.0e+02} " );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( "  { 100 , 100 }  " );

  object = Utility::HumanReadableSerializer<std::pair<float,double> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

//---------------------------------------------------------------------------//
// Check that a tuple type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( HumanReadableSerializer,
                                   serialize_tuple_3,
                                   T1, T2, T3 )
{
  Utility::Tuple<T1,T2,T3> object;
  initialize( object );

  std::ostringstream oss;

  Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100, 100, 100}" );
}

UNIT_TEST_TEMPLATE_3_INSTANT( HumanReadableSerializer, serialize_tuple_3 );

//---------------------------------------------------------------------------//
// Check that a tuple type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( HumanReadableSerializer,
                                   deserialize_tuple_3,
                                   T1, T2, T3 )
{
  Utility::Tuple<T1,T2,T3> test_object;
  initialize( test_object );

  Utility::Tuple<T1,T2,T3> object = 
    Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( "{100,100,100}" );

  TEST_EQUALITY_CONST( object, test_object );

  // no white space
  std::istringstream iss( "{100,100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // initial white space
  iss.str( "  {100,100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100,100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100 , 100,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{100,100 ,100}" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // middle white space
  iss.str( "{ 100, 100 , 100 }" );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // trailing white space
  iss.str( "{100,100,100}   " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );

  // white space everywhere
  iss.str( " {  100 , 100 , 100  }  " );

  object = Utility::HumanReadableSerializer<Utility::Tuple<T1,T2,T3> >::deserialize( iss );

  TEST_EQUALITY_CONST( object, test_object );
}

UNIT_TEST_TEMPLATE_3_INSTANT( HumanReadableSerializer, deserialize_tuple_3 );

//---------------------------------------------------------------------------//
// Check that a std::vector type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   serialize_vector,
                                   T )
{
  std::vector<T> object;
  initialize( object );

  std::ostringstream oss;
  
  Utility::HumanReadableSerializer<std::vector<T> >::serialize( oss, object );
  
  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100, 100, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<std::vector<T> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100, 100, 100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<std::vector<T> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100, 100, 100, 100, 100}" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, serialize_vector );

//---------------------------------------------------------------------------//
// Check that a std::vector type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   deserialize_vector,
                                   T )
{
  std::vector<T> test_object;
  initialize( test_object );
  
  std::vector<T> object = 
    Utility::HumanReadableSerializer<std::vector<T> >::deserialize( "{100,100,100,100,100}" );

  TEST_COMPARE_ARRAYS( object, test_object );

  std::istringstream iss( "{100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // initial white space
  iss.str( "  {100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{ 100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{100, 100, 100, 100, 100}" );

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{ 100 , 100 , 100 , 100 , 100 }" );

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // trailing white space
  iss.str( "{100,100,100,100,100}  ");

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // white space everywhere
  iss.str( "  { 100, 100 , 100, 100  ,  100  }    " );

  object = Utility::HumanReadableSerializer<std::vector<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, deserialize_vector );

//---------------------------------------------------------------------------//
// Check that a Teuchos::Array type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   serialize_array,
                                   T )
{
  Teuchos::Array<T> object;
  initialize( object );

  std::ostringstream oss;
  
  Utility::HumanReadableSerializer<Teuchos::Array<T> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100, 100, 100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Teuchos::Array<T> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100, 100, 100, 100, 100}" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, serialize_array );

//---------------------------------------------------------------------------//
// Check that a Teuchos::Array type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   deserialize_array,
                                   T )
{
  Teuchos::Array<T> test_object;
  initialize( test_object );
  
  Teuchos::Array<T> object = 
    Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( "{100,100,100,100,100}" );

  TEST_COMPARE_ARRAYS( object, test_object );

  std::istringstream iss( "{100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // initial white space
  iss.str( "  {100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{ 100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{100, 100, 100, 100, 100}" );

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{ 100 , 100 , 100 , 100 , 100 }" );

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // trailing white space
  iss.str( "{100,100,100,100,100}  ");

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // white space everywhere
  iss.str( "  { 100, 100 , 100, 100  ,  100  }    " );

  object = Utility::HumanReadableSerializer<Teuchos::Array<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, deserialize_array );

//---------------------------------------------------------------------------//
// Check that a Teuchos::ArrayRCP type can be serialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   serialize_arrayrcp,
                                   T )
{
  Teuchos::ArrayRCP<T> object;
  initialize( object );

  std::ostringstream oss;
  
  Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::serialize( oss, object );
  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100, 100, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::serialize( oss, object );

  TEST_EQUALITY_CONST( oss.str(), "{100, 100, 100, 100, 100}" );
  
  std::string object_string =
    Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::serialize( object );

  TEST_EQUALITY_CONST( object_string, "{100, 100, 100, 100, 100}" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, serialize_arrayrcp );

//---------------------------------------------------------------------------//
// Check that a Teuchos::ArrayRCP type can be deserialized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( HumanReadableSerializer,
                                   deserialize_arrayrcp,
                                   T )
{
  Teuchos::ArrayRCP<T> test_object;
  initialize( test_object );
  
  Teuchos::ArrayRCP<T> object = 
    Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( "{100,100,100,100,100}" );

  TEST_COMPARE_ARRAYS( object, test_object );

  std::istringstream iss( "{100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // initial white space
  iss.str( "  {100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{ 100,100,100,100,100}" );

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{100, 100, 100, 100, 100}" );

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // middle white space
  iss.str( "{ 100 , 100 , 100 , 100 , 100 }" );

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // trailing white space
  iss.str( "{100,100,100,100,100}  ");

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );

  // white space everywhere
  iss.str( "  { 100, 100 , 100, 100  ,  100  }    " );

  object = Utility::HumanReadableSerializer<Teuchos::ArrayRCP<T> >::deserialize( iss );

  TEST_COMPARE_ARRAYS( object, test_object );
}

UNIT_TEST_TEMPLATE_1_INSTANT( HumanReadableSerializer, deserialize_arrayrcp );

//---------------------------------------------------------------------------//
// end tstHumanReadableSerializer.cpp
//---------------------------------------------------------------------------//
