//---------------------------------------------------------------------------//
//!
//! \file   tstArrayTraits.cpp
//! \author Alex Robinson
//! \brief  Array traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <cstdint>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_ArrayTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs
//---------------------------------------------------------------------------//
#define UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( value_type, value_type_name )   \
  typedef std::vector<value_type> std_vector_##value_type_name;         \
  typedef Teuchos::Array<value_type> Teuchos_Array_##value_type_name;   \
  typedef Teuchos::ArrayView<value_type> Teuchos_ArrayView_##value_type_name; \
  typedef Teuchos::ArrayRCP<value_type> Teuchos_ArrayRCP_##value_type_name; \
  typedef Teuchos::Tuple<value_type,1> Teuchos_Tuple_1_##value_type_name; \
  typedef Teuchos::Tuple<value_type,2> Teuchos_Tuple_2_##value_type_name; \
  typedef Teuchos::Tuple<value_type,3> Teuchos_Tuple_3_##value_type_name

UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( float, float );                         \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( double, double );                       \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( char, char );                           \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( int, int );                             \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( unsigned, unsigned );                   \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( long, long );                           \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( unsigned long, unsigned_long );         \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( long long, long_long );                 \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( unsigned long long, unsigned_long_long ); \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( int32_t, int32 );                         \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( uint32_t, uint32 );                       \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( int64_t, int64 );                         \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( uint64_t, uint64 );

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, value_type_name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, std_vector_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Array_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayView_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayRCP_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Tuple_1_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Tuple_2_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Tuple_3_##value_type_name );
#define UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( type, name )       \
  UNIT_TEST_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, double ) \

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of dimensions of an array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   numberOfDimensions,
                                   OneDArray )
{
  OneDArray test_array;
  
  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::numberOfDimensions( test_array ), 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, numberOfDimensions );

//---------------------------------------------------------------------------//
// end tstArrayTraits.cpp
//---------------------------------------------------------------------------//
