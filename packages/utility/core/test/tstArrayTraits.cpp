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
  typedef Teuchos::ArrayView<const value_type> Teuchos_ArrayView_const_##value_type_name; \
  typedef Teuchos::ArrayRCP<value_type> Teuchos_ArrayRCP_##value_type_name; \
  typedef Teuchos::ArrayRCP<const value_type> Teuchos_ArrayRCP_const_##value_type_name; \
  typedef Teuchos::Tuple<value_type,10> Teuchos_Tuple_10_##value_type_name; \
  typedef Teuchos::TwoDArray<value_type> Teuchos_TwoDArray_##value_type_name

UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( float, float );                         \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( double, double );                       \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( char, char );                           \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( int, int );                             \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( unsigned, unsigned );                   \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( long, long );                           \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( unsigned long, unsigned_long );         \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( long long, long_long );                 \
UNIT_TEST_ONE_D_ARRAY_TYPEDEFS( unsigned long long, unsigned_long_long ); 

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, value_type_name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, std_vector_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Array_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayView_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayView_const_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayRCP_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayRCP_const_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Tuple_10_##value_type_name )

#define UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, value_type_name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, std_vector_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_Array_##value_type_name ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_ArrayRCP_##value_type_name )

#define UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( type, name )       \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, float ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, double ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, char ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, int ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, unsigned ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, long ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, unsigned_long ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, long_long ); \
  UNIT_TEST_ALL_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, unsigned_long_long )

#define UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( type, name )       \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, float ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, double ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, char ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, int ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, unsigned ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, long ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, unsigned_long ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, long_long ); \
  UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION_PLUS_VALUE_TYPE( type, name, unsigned_long_long )

#define UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( type, name )               \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_float ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_char ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_int ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_unsigned ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_unsigned_long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_long_long ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, Teuchos_TwoDArray_unsigned_long_long )


#define UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( type, name )       \
  UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( type, name ) 

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
template<typename T>
inline void initializeArray( std::vector<T>& array )
{
  array.resize( 10, 1 );
}

template<typename T>
inline void initializeArray( Teuchos::Array<T>& array )
{
  array.resize( 10, 1 );
}

template<typename T>
inline void initializeArray( Teuchos::ArrayRCP<T>& array )
{
  array = Teuchos::ArrayRCP<T>( 10, 1 );
}

template<typename T>
inline void initializeArray( Teuchos::ArrayView<T>& array )
{
  static Teuchos::Array<typename boost::remove_const<T>::type>
    global_view_array( 10, 1 );

  array = global_view_array();
}

template<typename T>
inline void initializeArray( Teuchos::Tuple<T,10>& array )
{
  array = Teuchos::tuple<T>( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 );
}

template<typename T>
inline void initializeArray( Teuchos::TwoDArray<T>& array )
{
  array = Teuchos::TwoDArray<T>( 10, 10, 1 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of dimensions of a one-d array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   numberOfDimensions,
                                   OneDArray )
{
  OneDArray test_array;
  
  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::numberOfDimensions( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<const OneDArray>::numberOfDimensions( test_array ), 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, numberOfDimensions );

//---------------------------------------------------------------------------//
// Check that the number of dimensions of a two-d array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   numberOfDimensions,
                                   TwoDArray )
{
  TwoDArray test_array;

  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::numberOfDimensions( test_array ), 2 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<const TwoDArray>::numberOfDimensions( test_array ), 2 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, numberOfDimensions );

//---------------------------------------------------------------------------//
// Check that the dimension sizes of a one-d array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   dimensionSizes,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  std::vector<int> dim_size_array;

  Utility::ArrayTraits<OneDArray>::dimensionSizes( test_array,
                                                   dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 1 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );

  dim_size_array.clear();

  Utility::ArrayTraits<const OneDArray>::dimensionSizes( test_array,
                                                         dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 1 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, dimensionSizes );

//---------------------------------------------------------------------------//
// Check that the dimension sizes of a two-d array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   dimensionSizes,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  std::vector<int> dim_size_array;

  Utility::ArrayTraits<TwoDArray>::dimensionSizes( test_array,
                                                   dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( dim_size_array.back(), 10 );

  dim_size_array.clear();

  Utility::ArrayTraits<const TwoDArray>::dimensionSizes( test_array,
                                                         dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( dim_size_array.back(), 10 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, dimensionSizes );

//---------------------------------------------------------------------------//
// Check that the size of an array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   size,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::size( test_array ), 10 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<const OneDArray>::size( test_array ), 10 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, size );

//---------------------------------------------------------------------------//
// Check that the size of an array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   size,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::size( test_array ), 100 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<const TwoDArray>::size( test_array ), 100 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, size );

//---------------------------------------------------------------------------//
// Check that an array can be resized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   resize,
                                   OneDArray )
{
  OneDArray test_array;

  Utility::ArrayTraits<OneDArray>::resize( test_array, 20 );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::size( test_array ), 20 );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, resize );

//---------------------------------------------------------------------------//
// Check that an array can be resized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   resize,
                                   TwoDArray )
{
  TwoDArray test_array;

  Utility::ArrayTraits<TwoDArray>::resize( test_array, 20 );

  std::vector<int> dim_size_array;

  Utility::ArrayTraits<TwoDArray>::dimensionSizes( test_array,
                                                   dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array[0], 1 );
  TEST_EQUALITY_CONST( dim_size_array[1], 20 );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, resize );

//---------------------------------------------------------------------------//
// Check that an array can be reshaped
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   reshape,
                                   OneDArray )
{
  OneDArray test_array;

  std::vector<int> dim_size_array( 1, 10 );

  Utility::ArrayTraits<OneDArray>::reshape( test_array, dim_size_array );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::size( test_array ), 10 );

  dim_size_array.resize( 2, 10 );

  Utility::ArrayTraits<OneDArray>::reshape( test_array, dim_size_array );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::size( test_array ), 100 );

  dim_size_array.resize( 3, 10 );

  Utility::ArrayTraits<OneDArray>::reshape( test_array, dim_size_array );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::size( test_array ), 1000 );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, reshape );

//---------------------------------------------------------------------------//
// Check that an array can be reshaped
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   reshape,
                                   TwoDArray )
{
  TwoDArray test_array;

  std::vector<int> dim_size_array( 1, 10 );

  Utility::ArrayTraits<TwoDArray>::reshape( test_array, dim_size_array );

  std::vector<int> copy_dim_size_array;

  Utility::ArrayTraits<TwoDArray>::dimensionSizes( test_array, copy_dim_size_array );

  TEST_EQUALITY_CONST( copy_dim_size_array[0], 1 );
  TEST_EQUALITY_CONST( copy_dim_size_array[1], 10 );

  dim_size_array.resize( 2, 10 );

  Utility::ArrayTraits<TwoDArray>::reshape( test_array, dim_size_array );

  Utility::ArrayTraits<TwoDArray>::dimensionSizes( test_array, copy_dim_size_array );

  TEST_EQUALITY_CONST( copy_dim_size_array[0], 10 );
  TEST_EQUALITY_CONST( copy_dim_size_array[1], 10 );

  dim_size_array.resize( 3, 10 );

  Utility::ArrayTraits<TwoDArray>::reshape( test_array, dim_size_array );

  Utility::ArrayTraits<TwoDArray>::dimensionSizes( test_array, copy_dim_size_array );

  TEST_EQUALITY_CONST( copy_dim_size_array[0], 100 );
  TEST_EQUALITY_CONST( copy_dim_size_array[1], 10 );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, reshape );

//---------------------------------------------------------------------------//
// Check that the front of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   front,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::reference test_array_front =
    Utility::ArrayTraits<OneDArray>::front( test_array );

  TEST_EQUALITY_CONST( test_array_front, 1 );

  OneDArray const_test_array = test_array;

  {
    typename Utility::ArrayTraits<OneDArray>::const_reference
      test_array_const_front =
      Utility::ArrayTraits<OneDArray>::front( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_front, 1 );
  }

  {
    typename Utility::ArrayTraits<const OneDArray>::const_reference
      test_array_const_front =
      Utility::ArrayTraits<const OneDArray>::front( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_front, 1 );
  }
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, front );

//---------------------------------------------------------------------------//
// Check that the front of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   front,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::reference test_array_front =
    Utility::ArrayTraits<TwoDArray>::front( test_array );

  TEST_EQUALITY_CONST( test_array_front, 1 );

  TwoDArray const_test_array = test_array;

  {
    typename Utility::ArrayTraits<TwoDArray>::const_reference
      test_array_const_front =
      Utility::ArrayTraits<TwoDArray>::front( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_front, 1 );
  }

  {
    typename Utility::ArrayTraits<const TwoDArray>::const_reference
      test_array_const_front =
      Utility::ArrayTraits<const TwoDArray>::front( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_front, 1 );
  }
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, front );

//---------------------------------------------------------------------------//
// Check that the back of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   back,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::reference test_array_back =
    Utility::ArrayTraits<OneDArray>::back( test_array );

  TEST_EQUALITY_CONST( test_array_back, 1 );

  OneDArray const_test_array = test_array;

  {
    typename Utility::ArrayTraits<OneDArray>::const_reference
      test_array_const_back =
      Utility::ArrayTraits<OneDArray>::back( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_back, 1 );
  }

  {
    typename Utility::ArrayTraits<const OneDArray>::const_reference
      test_array_const_back =
      Utility::ArrayTraits<const OneDArray>::back( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_back, 1 );
  }
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, back );

//---------------------------------------------------------------------------//
// Check that the back of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   back,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::reference test_array_back =
    Utility::ArrayTraits<TwoDArray>::back( test_array );

  TEST_EQUALITY_CONST( test_array_back, 1 );

  TwoDArray const_test_array = test_array;

  {
    typename Utility::ArrayTraits<TwoDArray>::const_reference
      test_array_const_back =
      Utility::ArrayTraits<TwoDArray>::back( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_back, 1 );
  }

  {
    typename Utility::ArrayTraits<const TwoDArray>::const_reference
      test_array_const_back =
      Utility::ArrayTraits<const TwoDArray>::back( const_test_array );

    TEST_EQUALITY_CONST( test_array_const_back, 1 );
  }
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, back );

//---------------------------------------------------------------------------//
// Check that iterators to the beginning and end of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   begin_end,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::iterator test_array_begin_it =
    Utility::ArrayTraits<OneDArray>::begin( test_array );

  typename Utility::ArrayTraits<OneDArray>::iterator test_array_end_it =
    Utility::ArrayTraits<OneDArray>::end( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_it, test_array_end_it ), 10 );

  typename Utility::ArrayTraits<OneDArray>::const_iterator
    test_array_begin_const_it =
    Utility::ArrayTraits<OneDArray>::begin( test_array );

  typename Utility::ArrayTraits<OneDArray>::const_iterator
    test_array_end_const_it =
    Utility::ArrayTraits<OneDArray>::end( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_const_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_const_it, test_array_end_const_it ), 10 );

  const OneDArray const_test_array = test_array;

  test_array_begin_const_it =
    Utility::ArrayTraits<const OneDArray>::begin( const_test_array );

  test_array_end_const_it =
    Utility::ArrayTraits<const OneDArray>::end( const_test_array );

  TEST_EQUALITY_CONST( *test_array_begin_const_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_const_it, test_array_end_const_it ), 10 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, begin_end );

//---------------------------------------------------------------------------//
// Check that iterators to the beginning and end of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   begin_end,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::iterator test_array_begin_it =
    Utility::ArrayTraits<TwoDArray>::begin( test_array );

  typename Utility::ArrayTraits<TwoDArray>::iterator test_array_end_it =
    Utility::ArrayTraits<TwoDArray>::end( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_it, test_array_end_it ), 100 );

  typename Utility::ArrayTraits<TwoDArray>::const_iterator
    test_array_begin_const_it =
    Utility::ArrayTraits<TwoDArray>::begin( test_array );

  typename Utility::ArrayTraits<TwoDArray>::const_iterator
    test_array_end_const_it =
    Utility::ArrayTraits<TwoDArray>::end( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_const_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_const_it, test_array_end_const_it ), 100 );

  const TwoDArray const_test_array = test_array;

  test_array_begin_const_it =
    Utility::ArrayTraits<const TwoDArray>::begin( const_test_array );

  test_array_end_const_it =
    Utility::ArrayTraits<const TwoDArray>::end( const_test_array );

  TEST_EQUALITY_CONST( *test_array_begin_const_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_const_it, test_array_end_const_it ), 100 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, begin_end );

//---------------------------------------------------------------------------//
// Check that the head of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   headPtr,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::pointer test_array_head =
    Utility::ArrayTraits<OneDArray>::headPtr( test_array );

  TEST_ASSERT( test_array_head );
  TEST_EQUALITY_CONST( *test_array_head, 1 );

  const OneDArray test_const_array = test_array;

  typename Utility::ArrayTraits<OneDArray>::const_pointer test_const_array_head =
    Utility::ArrayTraits<OneDArray>::headPtr( test_const_array );

  TEST_ASSERT( test_const_array_head );
  TEST_EQUALITY_CONST( *test_const_array_head, 1 );

  test_const_array_head =
    Utility::ArrayTraits<const OneDArray>::headPtr( test_const_array );

  TEST_ASSERT( test_const_array_head );
  TEST_EQUALITY_CONST( *test_const_array_head, 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, headPtr );

//---------------------------------------------------------------------------//
// Check that the head of the array can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   headPtr,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::pointer test_array_head =
    Utility::ArrayTraits<TwoDArray>::headPtr( test_array );

  TEST_ASSERT( test_array_head );
  TEST_EQUALITY_CONST( *test_array_head, 1 );

  const TwoDArray test_const_array = test_array;

  typename Utility::ArrayTraits<TwoDArray>::const_pointer test_const_array_head =
    Utility::ArrayTraits<TwoDArray>::headPtr( test_const_array );

  TEST_ASSERT( test_const_array_head );
  TEST_EQUALITY_CONST( *test_const_array_head, 1 );

  test_const_array_head =
    Utility::ArrayTraits<const TwoDArray>::headPtr( test_const_array );

  TEST_ASSERT( test_const_array_head );
  TEST_EQUALITY_CONST( *test_const_array_head, 1 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, headPtr );

//---------------------------------------------------------------------------//
// Check that an array can be converted to a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   toString,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  std::string test_array_string =
    Utility::ArrayTraits<OneDArray>::toString( test_array );

  TEST_ASSERT( test_array_string.size() > 1 );
  TEST_EQUALITY_CONST( test_array_string.front(), '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );

  test_array_string.clear();
  
  test_array_string =
    Utility::ArrayTraits<const OneDArray>::toString( test_array );

  TEST_ASSERT( test_array_string.size() > 1 );
  TEST_EQUALITY_CONST( test_array_string.front(), '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, toString );

//---------------------------------------------------------------------------//
// Check that an array can be converted to a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   toString,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  std::string test_array_string =
    Utility::ArrayTraits<TwoDArray>::toString( test_array );
  
  TEST_EQUALITY_CONST( test_array_string.substr( 0, 6 ), "10x10:" );
  TEST_EQUALITY_CONST( test_array_string[6], '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );

  test_array_string.clear();
  
  test_array_string =
    Utility::ArrayTraits<const TwoDArray>::toString( test_array );

  TEST_EQUALITY_CONST( test_array_string.substr( 0, 6 ), "10x10:" );
  TEST_EQUALITY_CONST( test_array_string[6], '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, toString );

//---------------------------------------------------------------------------//
// Check that an array can be initialized from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   fromString,
                                   OneDArray )
{
  std::string test_array_string;
  {
    OneDArray array;
    initializeArray( array );

    test_array_string = Utility::ArrayTraits<OneDArray>::toString( array );
  }

  OneDArray test_array = 
    Utility::ArrayTraits<OneDArray>::fromString( test_array_string );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::size( test_array ), 10 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::front( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<OneDArray>::back( test_array ), 1 );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, fromString );

//---------------------------------------------------------------------------//
// CHeck that an array can be initialized from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   fromString,
                                   TwoDArray )
{
  std::string test_array_string;
  {
    TwoDArray array;
    initializeArray( array );

    test_array_string = Utility::ArrayTraits<TwoDArray>::toString( array );
  }

  TwoDArray test_array =
    Utility::ArrayTraits<TwoDArray>::fromString( test_array_string );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::size( test_array ), 100 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::front( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::back( test_array ), 1 );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, fromString );

//---------------------------------------------------------------------------//
// Check that the array can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   toStream,
                                   OneDArray )
{
  std::ostringstream oss;
  {
    OneDArray array;
    initializeArray( array );

    Utility::ArrayTraits<OneDArray>::toStream( oss, array );
  }

  TEST_ASSERT( oss.str().size() > 1 );
  TEST_EQUALITY_CONST( oss.str().front(), '{' );
  TEST_EQUALITY_CONST( oss.str().back(), '}' );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, toStream );

//---------------------------------------------------------------------------//
// Check that the array can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   toStream,
                                   TwoDArray )
{
  std::ostringstream oss;
  {
    TwoDArray array;
    initializeArray( array );

    Utility::ArrayTraits<TwoDArray>::toStream( oss, array );
  }

  TEST_EQUALITY_CONST( oss.str().substr( 0, 6 ), "10x10:" );
  TEST_EQUALITY_CONST( oss.str()[6], '{' );
  TEST_EQUALITY_CONST( oss.str().back(), '}' );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, toStream );

//---------------------------------------------------------------------------//
// Check that a view of the array can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   view,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  // Create a full view
  typename Utility::ArrayTraits<OneDArray>::ArrayViewType view =
    Utility::ArrayTraits<OneDArray>::view( test_array );

  TEST_EQUALITY_CONST( view.size(), 10 );
  TEST_EQUALITY_CONST( &view[0], Utility::ArrayTraits<OneDArray>::headPtr( test_array ) );

  // Create a partial view
  view = Utility::ArrayTraits<OneDArray>::view( test_array, 4, 5 );

  TEST_EQUALITY_CONST( view.size(), 5 );
  TEST_EQUALITY_CONST( &view[0], &test_array[4] );

  const OneDArray const_test_array = test_array;

  // Create a full const view
  typename Utility::ArrayTraits<OneDArray>::ArrayConstViewType const_view =
    Utility::ArrayTraits<OneDArray>::view( const_test_array );

  TEST_EQUALITY_CONST( const_view.size(), 10 );
  TEST_EQUALITY_CONST( &const_view[0], Utility::ArrayTraits<OneDArray>::headPtr( const_test_array ) );

  const_view = Utility::ArrayTraits<const OneDArray>::view( const_test_array );

  TEST_EQUALITY_CONST( const_view.size(), 10 );
  TEST_EQUALITY_CONST( &const_view[0], Utility::ArrayTraits<const OneDArray>::headPtr( const_test_array ) );

  // Create a partial const view
  const_view = Utility::ArrayTraits<OneDArray>::view( const_test_array, 4, 5 );

  TEST_EQUALITY_CONST( const_view.size(), 5 );
  TEST_EQUALITY_CONST( &const_view[0], &const_test_array[4] );

  const_view = Utility::ArrayTraits<const OneDArray>::view( const_test_array, 4, 5 );

  TEST_EQUALITY_CONST( const_view.size(), 5 );
  TEST_EQUALITY_CONST( &const_view[0], &const_test_array[4] );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, view );

//---------------------------------------------------------------------------//
// Check that a view of the array can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   view,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  // Create a full view
  typename Utility::ArrayTraits<TwoDArray>::ArrayViewType view =
    Utility::ArrayTraits<TwoDArray>::view( test_array );

  TEST_EQUALITY_CONST( view.size(), 100 );
  TEST_EQUALITY_CONST( &view[0], Utility::ArrayTraits<TwoDArray>::headPtr( test_array ) );

  // Create a partial view
  view = Utility::ArrayTraits<TwoDArray>::view( test_array, 10, 10 );

  TEST_EQUALITY_CONST( view.size(), 10 );
  TEST_EQUALITY_CONST( &view[0], &test_array( 1, 0 ) );

  const TwoDArray const_test_array = test_array;

  // Create a full const view
  typename Utility::ArrayTraits<TwoDArray>::ArrayConstViewType const_view =
    Utility::ArrayTraits<TwoDArray>::view( const_test_array );

  TEST_EQUALITY_CONST( const_view.size(), 100 );
  TEST_EQUALITY_CONST( &const_view[0], Utility::ArrayTraits<TwoDArray>::headPtr( const_test_array ) );

  const_view = Utility::ArrayTraits<const TwoDArray>::view( const_test_array );

  TEST_EQUALITY_CONST( const_view.size(), 100 );
  TEST_EQUALITY_CONST( &const_view[0], Utility::ArrayTraits<const TwoDArray>::headPtr( const_test_array ) );

  // Create a partial const view
  const_view = Utility::ArrayTraits<TwoDArray>::view( const_test_array, 10, 10 );

  TEST_EQUALITY_CONST( const_view.size(), 10 );
  TEST_EQUALITY_CONST( &const_view[0], &const_test_array( 1, 0 ) );

  const_view = Utility::ArrayTraits<const TwoDArray>::view( const_test_array, 10, 10 );

  TEST_EQUALITY_CONST( const_view.size(), 10 );
  TEST_EQUALITY_CONST( &const_view[0], &const_test_array( 1, 0 ) );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, view );

//---------------------------------------------------------------------------//
// Check that the array can copy an array view object
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   copyView,
                                   OneDArray )
{
  typename Utility::ArrayTraits<OneDArray>::ArrayViewType view;
  initializeArray( view );

  OneDArray test_array;

  Utility::ArrayTraits<OneDArray>::copyView( test_array, view );

  TEST_COMPARE_ARRAYS( test_array, view );
  
  typename Utility::ArrayTraits<OneDArray>::ArrayConstViewType const_view;
  initializeArray( const_view );

  Utility::ArrayTraits<OneDArray>::copyView( test_array, const_view );

  TEST_COMPARE_ARRAYS( test_array, const_view );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, copyView );

//---------------------------------------------------------------------------//
// Check that the array can copy an array view object
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   copyView,
                                   TwoDArray )
{
  typename Utility::ArrayTraits<TwoDArray>::ArrayViewType view;
  initializeArray( view );

  TwoDArray test_array;

  Utility::ArrayTraits<TwoDArray>::copyView( test_array, view );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::size( test_array ), view.size() );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::front( test_array ), view.front() );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::back( test_array ), view.back() );
  
  typename Utility::ArrayTraits<TwoDArray>::ArrayConstViewType const_view;
  initializeArray( const_view );

  Utility::ArrayTraits<TwoDArray>::copyView( test_array, const_view );

  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::size( test_array ), const_view.size() );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::front( test_array ), const_view.front() );
  TEST_EQUALITY_CONST( Utility::ArrayTraits<TwoDArray>::back( test_array ), const_view.back() );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, copyView );

//---------------------------------------------------------------------------//
// Check that the standalone getNumberOfArrayDimensions can return the
// number of dimensions of an array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getNumberOfArrayDimensions,
                                   OneDArray )
{
  OneDArray test_array;

  TEST_EQUALITY_CONST( Utility::getNumberOfArrayDimensions( test_array ), 1 );

  const OneDArray const_test_array;

  TEST_EQUALITY_CONST( Utility::getNumberOfArrayDimensions( const_test_array ), 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD,
                                     getNumberOfArrayDimensions );

//---------------------------------------------------------------------------//
// Check that the standalone getNumberOfArrayDimensions method can return the
// number of dimensions of an array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getNumberOfArrayDimensions,
                                   TwoDArray )
{
  TwoDArray test_array;

  TEST_EQUALITY_CONST( Utility::getNumberOfArrayDimensions( test_array ), 2 );

  const TwoDArray const_test_array;

  TEST_EQUALITY_CONST( Utility::getNumberOfArrayDimensions( const_test_array ), 2 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD,
                                     getNumberOfArrayDimensions );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayDimensionSizes method can return the
// shape of the array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArrayDimensionSizes,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  std::vector<int> dim_size_array;

  Utility::getArrayDimensionSizes( test_array, dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 1 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );

  dim_size_array.clear();

  const OneDArray const_test_array = test_array;

  Utility::getArrayDimensionSizes( const_test_array, dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 1 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD,
                                     getArrayDimensionSizes );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayDimensionSizes method can return the
// shape of the array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArrayDimensionSizes,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  std::vector<int> dim_size_array;

  Utility::getArrayDimensionSizes( test_array, dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( dim_size_array.back(), 10 );

  dim_size_array.clear();

  const TwoDArray const_test_array = test_array;

  Utility::getArrayDimensionSizes( const_test_array, dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( dim_size_array.back(), 10 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD,
                                     getArrayDimensionSizes );

//---------------------------------------------------------------------------//
// Check that the standalone getArraySize method can return the size of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArraySize,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 10 );

  const OneDArray const_test_array = test_array;

  TEST_EQUALITY_CONST( Utility::getArraySize( const_test_array ), 10 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, getArraySize );

//---------------------------------------------------------------------------//
// Check that the standalone getArraySize method can return the size of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArraySize,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 100 );

  const TwoDArray const_test_array = test_array;

  TEST_EQUALITY_CONST( Utility::getArraySize( const_test_array ), 100 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, getArraySize );

//---------------------------------------------------------------------------//
// Check that an array can be resized using the standalone resizeArray method
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   resizeArray,
                                   OneDArray )
{
  OneDArray test_array;

  Utility::resizeArray( test_array, 10 );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 10 );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, resizeArray );

//---------------------------------------------------------------------------//
// Check that an array can be resized using the standalone resizeArray method
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   resizeArray,
                                   TwoDArray )
{
  TwoDArray test_array;

  Utility::resizeArray( test_array, 100 );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 100 );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, resizeArray );

//---------------------------------------------------------------------------//
// Check that an array can be reshaped using the standalone reshapeArray method
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   reshapeArray,
                                   OneDArray )
{
  OneDArray test_array;

  std::vector<int> dim_size_array( 1, 10 );
  
  Utility::reshapeArray( test_array, dim_size_array );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 10 );

  dim_size_array.resize( 2, 10 );

  Utility::reshapeArray( test_array, dim_size_array );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 100 );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, reshapeArray );

//---------------------------------------------------------------------------//
// Check that an array can be reshaped using the standalone reshapeArray method
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   reshapeArray,
                                   TwoDArray )
{
  TwoDArray test_array;

  std::vector<int> dim_size_array( 1, 10 );
  
  Utility::reshapeArray( test_array, dim_size_array );

  std::vector<int> copy_dim_size_array;

  Utility::getArrayDimensionSizes( test_array, copy_dim_size_array );
  
  TEST_EQUALITY_CONST( copy_dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( copy_dim_size_array.front(), 1 );
  TEST_EQUALITY_CONST( copy_dim_size_array.back(), 10 );

  dim_size_array.resize( 2, 10 );

  Utility::reshapeArray( test_array, dim_size_array );

  Utility::getArrayDimensionSizes( test_array, copy_dim_size_array );

  TEST_EQUALITY_CONST( copy_dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( copy_dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( copy_dim_size_array.back(), 10 );

  dim_size_array.resize( 3, 10 );

  Utility::reshapeArray( test_array, dim_size_array );

  Utility::getArrayDimensionSizes( test_array, copy_dim_size_array );

  TEST_EQUALITY_CONST( copy_dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( copy_dim_size_array.front(), 100 );
  TEST_EQUALITY_CONST( copy_dim_size_array.back(), 10 );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, reshapeArray );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayFront method can return the front of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArrayFront,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::reference test_array_front =
    Utility::getArrayFront( test_array );
  
  TEST_EQUALITY_CONST( test_array_front, 1 );
  TEST_EQUALITY_CONST( &test_array_front,
                       Utility::ArrayTraits<OneDArray>::headPtr( test_array ) );

  const OneDArray const_test_array = test_array;

  typename Utility::ArrayTraits<const OneDArray>::const_reference
    test_array_const_front = Utility::getArrayFront( const_test_array );

  TEST_EQUALITY_CONST( test_array_const_front, 1 );
  TEST_EQUALITY_CONST( &test_array_const_front,
                       Utility::ArrayTraits<const OneDArray>::headPtr( const_test_array ) );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, getArrayFront );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayFront method can return the front of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArrayFront,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::reference test_array_front =
    Utility::getArrayFront( test_array );
  
  TEST_EQUALITY_CONST( test_array_front, 1 );
  TEST_EQUALITY_CONST( &test_array_front,
                       Utility::ArrayTraits<TwoDArray>::headPtr( test_array ) );

  const TwoDArray const_test_array = test_array;

  typename Utility::ArrayTraits<const TwoDArray>::const_reference
    test_array_const_front = Utility::getArrayFront( const_test_array );

  TEST_EQUALITY_CONST( test_array_const_front, 1 );
  TEST_EQUALITY_CONST( &test_array_const_front,
                       Utility::ArrayTraits<TwoDArray>::headPtr( const_test_array ) );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, getArrayFront );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayBack method can return the back of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArrayBack,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::reference test_array_back =
    Utility::getArrayBack( test_array );
  
  TEST_EQUALITY_CONST( test_array_back, 1 );
  TEST_EQUALITY_CONST( &test_array_back,
                       Utility::ArrayTraits<OneDArray>::headPtr( test_array ) +
                       Utility::ArrayTraits<OneDArray>::size( test_array )-1 );

  const OneDArray const_test_array = test_array;

  typename Utility::ArrayTraits<const OneDArray>::const_reference
    test_array_const_back = Utility::getArrayBack( const_test_array );

  TEST_EQUALITY_CONST( test_array_const_back, 1 );
  TEST_EQUALITY_CONST( &test_array_const_back,
                       Utility::ArrayTraits<const OneDArray>::headPtr( const_test_array ) +
                       Utility::ArrayTraits<const OneDArray>::size( const_test_array ) - 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, getArrayBack );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayBack method can return the back of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArrayBack,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::reference test_array_back =
    Utility::getArrayBack( test_array );
  
  TEST_EQUALITY_CONST( test_array_back, 1 );
  TEST_EQUALITY_CONST( &test_array_back,
                       Utility::ArrayTraits<TwoDArray>::headPtr( test_array ) +
                       Utility::ArrayTraits<TwoDArray>::size( test_array )-1 );

  const TwoDArray const_test_array = test_array;

  typename Utility::ArrayTraits<const TwoDArray>::const_reference
    test_array_const_back = Utility::getArrayBack( const_test_array );

  TEST_EQUALITY_CONST( test_array_const_back, 1 );
  TEST_EQUALITY_CONST( &test_array_const_back,
                       Utility::ArrayTraits<const TwoDArray>::headPtr( const_test_array ) +
                       Utility::ArrayTraits<const TwoDArray>::size( const_test_array ) - 1 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, getArrayBack );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayBegin and getArrayEnd methods
// can return iterators to the beginning and one past the end of the array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArrayBegin_getArrayEnd,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<OneDArray>::iterator test_array_begin_it =
    Utility::getArrayBegin( test_array );

  typename Utility::ArrayTraits<OneDArray>::iterator test_array_end_it =
    Utility::getArrayEnd( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_it, test_array_end_it ), 10 );

  const OneDArray const_test_array = test_array;

  typename Utility::ArrayTraits<const OneDArray>::const_iterator
    test_array_begin_const_it = Utility::getArrayBegin( test_array );

  typename Utility::ArrayTraits<OneDArray>::const_iterator
    test_array_end_const_it = Utility::getArrayEnd( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_const_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_const_it, test_array_end_const_it ), 10 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD,
                                     getArrayBegin_getArrayEnd );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayBegin and getArrayEnd methods can return
// iterators to the beginning and one past the end of the array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArrayBegin_getArrayEnd,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  typename Utility::ArrayTraits<TwoDArray>::iterator test_array_begin_it =
    Utility::getArrayBegin( test_array );

  typename Utility::ArrayTraits<TwoDArray>::iterator test_array_end_it =
    Utility::getArrayEnd( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_it, test_array_end_it ), 100 );

  const TwoDArray const_test_array = test_array;

  typename Utility::ArrayTraits<const TwoDArray>::const_iterator
    test_array_begin_const_it = Utility::getArrayBegin( test_array );

  typename Utility::ArrayTraits<TwoDArray>::const_iterator
    test_array_end_const_it = Utility::getArrayEnd( test_array );

  TEST_EQUALITY_CONST( *test_array_begin_const_it, 1 );
  TEST_EQUALITY_CONST( std::distance( test_array_begin_const_it, test_array_end_const_it ), 100 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD,
                                     getArrayBegin_getArrayEnd );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayHeadPtr method can return the head of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArrayHeadPtr,
                                   OneDArray )
{
  OneDArray test_array;
  initializeArray( test_array );

  auto head_ptr = Utility::getArrayHeadPtr( test_array );

  TEST_ASSERT( head_ptr );
  TEST_EQUALITY_CONST( *head_ptr, 1 );

  const OneDArray const_test_array = test_array;

  auto const_head_ptr = Utility::getArrayHeadPtr( const_test_array );

  TEST_ASSERT( const_head_ptr );
  TEST_EQUALITY_CONST( *const_head_ptr, 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, getArrayHeadPtr );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayHeadPtr method can return the head of the
// array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArrayHeadPtr,
                                   TwoDArray )
{
  TwoDArray test_array;
  initializeArray( test_array );

  auto head_ptr = Utility::getArrayHeadPtr( test_array );

  TEST_ASSERT( head_ptr );
  TEST_EQUALITY_CONST( *head_ptr, 1 );

  const TwoDArray const_test_array = test_array;

  auto const_head_ptr = Utility::getArrayHeadPtr( const_test_array );

  TEST_ASSERT( const_head_ptr );
  TEST_EQUALITY_CONST( *const_head_ptr, 1 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, getArrayHeadPtr );

//---------------------------------------------------------------------------//
// Check that the standalone arrayToString method can convert the array to
// a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   arrayToString,
                                   OneDArray )
{
  std::string test_array_string;
  {
    OneDArray array;
    initializeArray( array );

    test_array_string = Utility::arrayToString( array );
  }

  TEST_ASSERT( test_array_string.size() > 1 );
  TEST_EQUALITY_CONST( test_array_string.front(), '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );

  test_array_string.clear();

  {
    OneDArray array;
    initializeArray( array );

    const OneDArray const_array = array;

    test_array_string = Utility::arrayToString( const_array );
  }

  TEST_ASSERT( test_array_string.size() > 1 );
  TEST_EQUALITY_CONST( test_array_string.front(), '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, arrayToString );

//---------------------------------------------------------------------------//
// Check that the standalone arrayToString method can convert the array to
// a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   arrayToString,
                                   TwoDArray )
{
  std::string test_array_string;
  {
    TwoDArray array;
    initializeArray( array );

    test_array_string = Utility::arrayToString( array );
  }

  TEST_EQUALITY_CONST( test_array_string.substr( 0, 6 ), "10x10:" );
  TEST_EQUALITY_CONST( test_array_string[6], '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );

  test_array_string.clear();

  {
    TwoDArray array;
    initializeArray( array );

    const TwoDArray const_array = array;

    test_array_string = Utility::arrayToString( const_array );
  }

  TEST_EQUALITY_CONST( test_array_string.substr( 0, 6 ), "10x10:" );
  TEST_EQUALITY_CONST( test_array_string[6], '{' );
  TEST_EQUALITY_CONST( test_array_string.back(), '}' );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, arrayToString );

//---------------------------------------------------------------------------//
// Check that the standalone stringToArray method can create an array from
// a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   stringToArray,
                                   OneDArray )
{
  std::string test_array_string;
  {
    OneDArray array;
    initializeArray( array );

    test_array_string = Utility::arrayToString( array );
  }

  OneDArray test_array =
    Utility::stringToArray<OneDArray>( test_array_string );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayFront( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::getArrayBack( test_array ), 1 );

  test_array_string.clear();
  test_array.clear();

  {
    OneDArray array;
    initializeArray( array );

    const OneDArray const_array = array;

    test_array_string = Utility::arrayToString( const_array );
  }

  test_array = Utility::stringToArray<OneDArray>( test_array_string );

  TEST_EQUALITY_CONST( Utility::getArraySize( test_array ), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayFront( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::getArrayBack( test_array ), 1 );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, stringToArray );

//---------------------------------------------------------------------------//
// Check that the standalone stringToArray method can create an array from
// a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   stringToArray,
                                   TwoDArray )
{
  std::string test_array_string;
  {
    TwoDArray array;
    initializeArray( array );

    test_array_string = Utility::arrayToString( array );
  }

  TwoDArray test_array =
    Utility::stringToArray<TwoDArray>( test_array_string );

  std::vector<int> dim_size_array;

  Utility::getArrayDimensionSizes( test_array, dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( dim_size_array.back(), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayFront( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::getArrayBack( test_array ), 1 );

  test_array_string.clear();
  test_array.clear();
  dim_size_array.clear();

  {
    TwoDArray array;
    initializeArray( array );

    const TwoDArray const_array = array;

    test_array_string = Utility::arrayToString( const_array );
  }

  test_array = Utility::stringToArray<TwoDArray>( test_array_string );

  Utility::getArrayDimensionSizes( test_array, dim_size_array );

  TEST_EQUALITY_CONST( dim_size_array.size(), 2 );
  TEST_EQUALITY_CONST( dim_size_array.front(), 10 );
  TEST_EQUALITY_CONST( dim_size_array.back(), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayFront( test_array ), 1 );
  TEST_EQUALITY_CONST( Utility::getArrayBack( test_array ), 1 );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, stringToArray );

//---------------------------------------------------------------------------//
// Check that an array can be placed in a stream using the stream operator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   stream_operator,
                                   OneDArray )
{
  OneDArray array;
  initializeArray( array );

  std::ostringstream oss;
  oss << array;

  TEST_ASSERT( oss.str().size() > 1 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, stream_operator );

//---------------------------------------------------------------------------//
// Check that an array can be placed in a stream using the stream operator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   stream_operator,
                                   TwoDArray )
{
  TwoDArray array;
  initializeArray( array );

  std::ostringstream oss;
  oss << array;
  
  TEST_EQUALITY_CONST( oss.str().substr( 0, 6 ), "10x10:" );
  TEST_EQUALITY_CONST( oss.str()[6], '{' );
  TEST_EQUALITY_CONST( oss.str().back(), '}' );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, stream_operator );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayView method can return a view of the array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   getArrayView,
                                   OneDArray )
{
  OneDArray array;
  initializeArray( array );

  // Get a full view
  auto view = Utility::getArrayView( array );

  TEST_EQUALITY_CONST( Utility::getArraySize( view ), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( view ), Utility::getArrayHeadPtr( array ) );

  // Get a partial view
  view = Utility::getArrayView( array, 5, 5 );

  TEST_EQUALITY_CONST( Utility::getArraySize( view ), 5 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( view ), Utility::getArrayHeadPtr( array )+5 );

  const OneDArray& const_array = array;
  
  // Get a full const view
  auto const_view = Utility::getArrayView( const_array );

  TEST_EQUALITY_CONST( Utility::getArraySize( const_view ), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( const_view ), Utility::getArrayHeadPtr( const_array ) );

  // Get a partial const view
  const_view = Utility::getArrayView( const_array, 5, 5 );

  TEST_EQUALITY_CONST( Utility::getArraySize( const_view ), 5 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( const_view ), Utility::getArrayHeadPtr( const_array )+5 );

  // Verify that an incorrect size will be adjusted
  const_view = Utility::getArrayView( const_array, 5, 10 );

  TEST_EQUALITY_CONST( Utility::getArraySize( const_view ), 5 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( const_view ), Utility::getArrayHeadPtr( const_array )+5 );
}

UNIT_TEST_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, getArrayView );

//---------------------------------------------------------------------------//
// Check that the standalone getArrayView method can return a view of the array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   getArrayView,
                                   TwoDArray )
{
  TwoDArray array;
  initializeArray( array );

  // Get a full view
  auto view = Utility::getArrayView( array );

  TEST_EQUALITY_CONST( Utility::getArraySize( view ), 100 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( view ), Utility::getArrayHeadPtr( array ) );

  // Get a partial view
  view = Utility::getArrayView( array, 10, 10 );

  TEST_EQUALITY_CONST( Utility::getArraySize( view ), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( view ), Utility::getArrayHeadPtr( array )+10 );

  const TwoDArray& const_array = array;
  
  // Get a full const view
  auto const_view = Utility::getArrayView( const_array );

  TEST_EQUALITY_CONST( Utility::getArraySize( const_view ), 100 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( const_view ), Utility::getArrayHeadPtr( const_array ) );

  // Get a partial const view
  const_view = Utility::getArrayView( const_array, 10, 10 );

  TEST_EQUALITY_CONST( Utility::getArraySize( const_view ), 10 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( const_view ), Utility::getArrayHeadPtr( const_array )+10 );

  // Verify that an incorrect size will be adjusted
  const_view = Utility::getArrayView( const_array, 10, 100 );

  TEST_EQUALITY_CONST( Utility::getArraySize( const_view ), 90 );
  TEST_EQUALITY_CONST( Utility::getArrayHeadPtr( const_view ), Utility::getArrayHeadPtr( const_array )+10 );
}

UNIT_TEST_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, getArrayView );

//---------------------------------------------------------------------------//
// Check that the standalone copyArrayView method can copy the array view
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_OneD,
                                   copyArrayView,
                                   OneDArray )
{
  typename Utility::ArrayTraits<OneDArray>::ArrayViewType view;
  initializeArray( view );

  OneDArray array;
  Utility::copyArrayView( array, view );

  TEST_COMPARE_ARRAYS( array, view );

  array.clear();

  typename Utility::ArrayTraits<OneDArray>::ArrayConstViewType const_view;
  initializeArray( const_view );

  Utility::copyArrayView( array, const_view );

  TEST_COMPARE_ARRAYS( array, const_view );
}

UNIT_TEST_DYNAMIC_ONE_D_ARRAY_INSTANTIATION( ArrayTraits_OneD, copyArrayView );

//---------------------------------------------------------------------------//
// Check that the standalone copyArrayView method can copy the array view
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ArrayTraits_TwoD,
                                   copyArrayView,
                                   TwoDArray )
{
  typename Utility::ArrayTraits<TwoDArray>::ArrayViewType view;
  initializeArray( view );

  TwoDArray array;
  Utility::copyArrayView( array, view );

  TEST_COMPARE_ARRAYS( Utility::getArrayView( array ), view );

  array.clear();

  typename Utility::ArrayTraits<TwoDArray>::ArrayConstViewType const_view;
  initializeArray( const_view );

  Utility::copyArrayView( array, const_view );

  TEST_COMPARE_ARRAYS( Utility::getArrayView( array ), const_view );
}

UNIT_TEST_DYNAMIC_TWO_D_ARRAY_INSTANTIATION( ArrayTraits_TwoD, copyArrayView );

//---------------------------------------------------------------------------//
// end tstArrayTraits.cpp
//---------------------------------------------------------------------------//
