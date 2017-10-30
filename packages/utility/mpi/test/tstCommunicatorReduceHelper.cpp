//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorReduceHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator reduce helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Types
//---------------------------------------------------------------------------//
typedef std::tuple<char, unsigned char,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double> BasicTypesNoBool;

typedef decltype(std::tuple_cat(BasicTypesNoBool(),std::tuple<bool>())) BasicTypes;

template<typename T, typename Enabled = void>
struct TypeOpPairList
{
  typedef std::tuple<std::tuple<T,std::plus<T> >,
                     std::tuple<T,std::multiplies<T> >,
                     std::tuple<T,std::logical_and<T> >,
                     std::tuple<T,std::logical_or<T> >,
                     std::tuple<T,std::bit_and<T> >,
                     std::tuple<T,std::bit_or<T> >,
                     std::tuple<T,std::bit_xor<T> >,
                     std::tuple<T,Utility::maximum<T> >,
                     std::tuple<T,Utility::minimum<T> >,
                     std::tuple<T,Utility::bitwiseAnd<T> >,
                     std::tuple<T,Utility::bitwiseOr<T> >,
                     std::tuple<T,Utility::bitwiseXor<T> >,
                     std::tuple<T,Utility::logicalXor<T> > > type;
};

template<typename T>
struct TypeOpPairList<T,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  typedef std::tuple<std::tuple<T,std::plus<T> >,
                     std::tuple<T,std::multiplies<T> >,
                     std::tuple<T,Utility::maximum<T> >,
                     std::tuple<T,Utility::minimum<T> > > type;
};

template<>
struct TypeOpPairList<bool>
{
  typedef std::tuple<std::tuple<bool,std::logical_and<bool> >,
                     std::tuple<bool,std::logical_or<bool> >,
                     std::tuple<bool,std::bit_and<bool> >,
                     std::tuple<bool,std::bit_or<bool> >,
                     std::tuple<bool,std::bit_xor<bool> >,
                     std::tuple<bool,Utility::maximum<bool> >,
                     std::tuple<bool,Utility::minimum<bool> >,
                     std::tuple<bool,Utility::bitwiseAnd<bool> >,
                     std::tuple<bool,Utility::bitwiseOr<bool> >,
                     std::tuple<bool,Utility::bitwiseXor<bool> >,
                     std::tuple<bool,Utility::logicalXor<bool> > > type;
};

template<typename... Types>
struct MergeTypeOpPairLists;

template<typename T, typename... Types>
struct MergeTypeOpPairLists<T,Types...>
{
  typedef decltype(std::tuple_cat( typename MergeTypeOpPairLists<T>::type(),
                                   typename MergeTypeOpPairLists<Types...>::type() )) type;
};

template<typename T>
struct MergeTypeOpPairLists<T>
{
  typedef typename TypeOpPairList<T>::type type;
};

template<typename... Types>
struct MergeTypeOpPairLists<std::tuple<Types...> > : public MergeTypeOpPairLists<Types...>
{ /* ... */ };

typedef typename MergeTypeOpPairLists<BasicTypes>::type TypeOpPairs;
typedef typename MergeTypeOpPairLists<BasicTypesNoBool>::type TypeOpPairsNoBool;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline T initializeValue( T, int i )
{ return T(i); }

inline bool initializeValue( bool, int i )
{ return (i%2 == 0 ? true : false); }

inline char initializeValue( char, int i )
{ return 48+i; }

inline unsigned char initializeValue( unsigned char, int i )
{ return 48+i; }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a reduce operation can be conducted - single value
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Communicator, reduce_single_value, TypeOpPairs )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 1, ReduceOp );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  T reduced_values[2] = {initializeValue( T(), 0 ), initializeValue( T(), 0 )};

  FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, value, reduced_values[0], ReduceOp(), 0 ) );

  // Pass the reduced value to the root proc only
  if( comm->rank() == 0 )
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, value, reduced_values[1], ReduceOp(), 0 ) );

    T expected_reduced_value = initializeValue(T(), 0);

    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, initializeValue(T(), i) );
    }

    FRENSIE_CHECK_EQUAL( reduced_values[0], expected_reduced_value );
    FRENSIE_CHECK_EQUAL( reduced_values[1], expected_reduced_value );
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, value, ReduceOp(), 0 ) );

    FRENSIE_CHECK_EQUAL( reduced_values[0], initializeValue( T(), 0 ) );
    FRENSIE_CHECK_EQUAL( reduced_values[1], initializeValue( T(), 0 ) );
  }

  if( comm->size() > 1 )
  {
    reduced_values[0] = initializeValue( T(), 0 );
    reduced_values[1] = initializeValue( T(), 0 );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, value, reduced_values[0], ReduceOp(), 1 ) );
    
    // Pass the reduced value to the root proc only
    if( comm->rank() == 1 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, value, reduced_values[1], ReduceOp(), 1 ) );
      
      T expected_reduced_value = initializeValue(T(), 0);
      
      for( int i = 1; i <= comm->size()-1; ++i )
      {
        expected_reduced_value =
          ReduceOp()( expected_reduced_value, initializeValue(T(), i) );
      }

      FRENSIE_CHECK_EQUAL( reduced_values[0], expected_reduced_value );
      FRENSIE_CHECK_EQUAL( reduced_values[1], expected_reduced_value );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, value, ReduceOp(), 1 ) );
      
      FRENSIE_CHECK_EQUAL( reduced_values[0], initializeValue( T(), 0 ) );
      FRENSIE_CHECK_EQUAL( reduced_values[1], initializeValue( T(), 0 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a reduce operation can be conducted - multiple values
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Communicator, reduce_multiple_values, TypeOpPairs )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 1, ReduceOp );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  
  std::array<T,3> reduced_values;
  reduced_values.fill( initializeValue( T(), 0 ) );

  std::array<T,3> expected_reduced_values;

  if( comm->rank() == 0 )
  {
    T expected_reduced_value = initializeValue(T(), 0);

    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, initializeValue(T(), i) );
    }

    expected_reduced_values.fill( expected_reduced_value );
  }
  else
    expected_reduced_values.fill( initializeValue( T(), 0 ) );

  // Reduce using an initializer list input, view rvalue output
  FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, {value, value, value}, Utility::arrayView(reduced_values), ReduceOp(), 0 ) );
  FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

  reduced_values.fill( initializeValue(T(), 0) );

  // Reduce using an initializer list input, view lvalue output
  {
    Utility::ArrayView<T> reduced_values_view( reduced_values );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, {value, value, value}, reduced_values_view, ReduceOp(), 0 ) );

    FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

    reduced_values.fill( initializeValue(T(), 0) );
  }

  // Reduce using arrays directly
  {
    std::array<T,3> values_array;
    values_array.fill( value );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values_array, reduced_values, ReduceOp(), 0 ) );
  
    FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

    reduced_values.fill( initializeValue(T(), 0) );
  }

  // Reduce using array view lvalues
  {
    std::array<T,3> values_array;
    values_array.fill( value );

    Utility::ArrayView<T> values_array_view( values_array );
    Utility::ArrayView<T> reduced_values_view( reduced_values );

    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values_array_view, reduced_values_view, ReduceOp(), 0 ) );

    FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

    reduced_values.fill( initializeValue(T(), 0) );
  }

  // Reduce using array view rvalues
  {
    std::array<T,3> values_array;
    values_array.fill( value );

    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, Utility::arrayView(values_array), Utility::arrayView(reduced_values), ReduceOp(), 0 ) );

    FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

    reduced_values.fill( initializeValue(T(), 0) );

    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, Utility::arrayViewOfConst(values_array), Utility::arrayView(reduced_values), ReduceOp(), 0 ) );

    FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

    reduced_values.fill( initializeValue(T(), 0) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      T expected_reduced_value = initializeValue(T(), 0);
      
      for( int i = 1; i <= comm->size()-1; ++i )
      {
        expected_reduced_value =
          ReduceOp()( expected_reduced_value, initializeValue(T(), i) );
      }
      
      expected_reduced_values.fill( expected_reduced_value );

      // Reduce using an initializer list input, view rvalue output
      FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, {value, value, value}, Utility::arrayView(reduced_values), ReduceOp(), 1 ) );

      FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

      reduced_values.fill( initializeValue(T(), 0) );

      // Reduce using an initializer list input, view lvalue output
      {
        Utility::ArrayView<T> reduced_values_view( reduced_values );
    
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, {value, value, value}, reduced_values_view, ReduceOp(), 1 ) );

        FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );

        reduced_values.fill( initializeValue(T(), 0) );
      }

      // Reduce using arrays directly
      {
        std::array<T,3> values_array;
        values_array.fill( value );
        
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values_array, reduced_values, ReduceOp(), 1 ) );
        
        FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );
        
        reduced_values.fill( initializeValue(T(), 0) );
      }

      // Reduce using array view lvalues
      {
        std::array<T,3> values_array;
        values_array.fill( value );
        
        Utility::ArrayView<T> values_array_view( values_array );
        Utility::ArrayView<T> reduced_values_view( reduced_values );
        
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values_array_view, reduced_values_view, ReduceOp(), 1 ) );
        
        FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );
        
        reduced_values.fill( initializeValue(T(), 0) );
      }

      // Reduce using array view rvalues
      {
        std::array<T,3> values_array;
        values_array.fill( value );
        
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, Utility::arrayView(values_array), Utility::arrayView(reduced_values), ReduceOp(), 1 ) );
        
        FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );
        
        reduced_values.fill( initializeValue(T(), 0) );
        
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, Utility::arrayViewOfConst(values_array), Utility::arrayView(reduced_values), ReduceOp(), 1 ) );
        
        FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );
        
        reduced_values.fill( initializeValue(T(), 0) );
      }
    }
    else
    {
      // Reduce using an initializer list input
      FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, {value, value, value}, ReduceOp(), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, {value, value, value}, ReduceOp(), 1 ) );
      
      // Reduce using arrays directly
      {
        std::array<T,3> values_array;
        values_array.fill( value );
    
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values_array, ReduceOp(), 1 ) );
      }

      // Reduce using array view lvalues
      {
        std::array<T,3> values_array;
        values_array.fill( value );

        Utility::ArrayView<T> values_array_view( values_array );

        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values_array_view, ReduceOp(), 1 ) );
      }

      // Reduce using array view rvalues
      {
        std::array<T,3> values_array;
        values_array.fill( value );

        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, Utility::arrayView(values_array), ReduceOp(), 1 ) );
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, Utility::arrayViewOfConst(values_array), ReduceOp(), 1 ) );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a reduce operation can be conducted - vectors of values
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Communicator, reduce_vectors, TypeOpPairsNoBool )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 1, ReduceOp );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const T value = initializeValue( T(), comm->rank() );
  
  std::vector<T> reduced_values( 10, initializeValue(T(), 0) );

  std::vector<T> expected_reduced_values;

  if( comm->rank() == 0 )
  {
    T expected_reduced_value = initializeValue(T(), 0);

    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, initializeValue(T(), i) );
    }

    expected_reduced_values.resize( 10, expected_reduced_value );
  }
  else
    expected_reduced_values.resize( 10, initializeValue( T(), 0 ) );

  // Reduce using vectors directly
  {
    std::vector<T> values( 10, value );
    
    FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values, reduced_values, ReduceOp(), 0 ) );
  
    FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );
  }

  if( comm->size() > 1 )
  {
    expected_reduced_values.clear();
    
    if( comm->rank() == 1 )
    {
      T expected_reduced_value = initializeValue(T(), 0);
      
      for( int i = 1; i <= comm->size()-1; ++i )
      {
        expected_reduced_value =
          ReduceOp()( expected_reduced_value, initializeValue(T(), i) );
      }
      
      expected_reduced_values.resize( 10, expected_reduced_value );

      // Reduce using vectors directly
      {
        std::vector<T> values( 10, value );
        
        FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values, reduced_values, ReduceOp(), 1 ) );
        
        FRENSIE_CHECK_EQUAL( reduced_values, expected_reduced_values );
      }
    }
    else
    {
      std::vector<T> values( 10, value );
    
      FRENSIE_REQUIRE_NO_THROW( Utility::reduce( *comm, values, ReduceOp(), 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorReduceHelper.cpp
//---------------------------------------------------------------------------//
