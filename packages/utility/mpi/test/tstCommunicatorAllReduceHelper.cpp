//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorAllReduceHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator allReduce helper function unit tests
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
                   float, double> BasicTypes;

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

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline T initializeValue( T, int i )
{ return T(i); }

inline char initializeValue( char, int i )
{ return 48+i; }

inline unsigned char initializeValue( unsigned char, int i )
{ return 48+i; }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an all reduce operation can be conducted with bools
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, allReduce_bool,
                            std::logical_and<bool>,
                            std::logical_or<bool>,
                            std::bit_and<bool>,
                            std::bit_or<bool>,
                            std::bit_xor<bool>,
                            Utility::maximum<bool>,
                            Utility::minimum<bool>,
                            Utility::bitwiseAnd<bool>,
                            Utility::bitwiseOr<bool>,
                            Utility::bitwiseXor<bool>,
                            Utility::logicalXor<bool> )
{
  FETCH_TEMPLATE_PARAM( 0, ReduceOp );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // Reduce a single value
  {
    bool value_to_reduce = (comm->rank()%2 == 0 ? true : false);
    bool reduced_value;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, value_to_reduce, reduced_value, ReduceOp() ) );

    bool expected_reduced_value = true;
    
    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, (i%2 == 0 ? true : false) );
    }
    
    FRENSIE_CHECK_EQUAL( reduced_value, expected_reduced_value );
  }
  
  // Reduce a value inline
  {
    bool value_to_reduce_inline = (comm->rank()%2 == 0 ? true : false);

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, value_to_reduce_inline, ReduceOp() ) );

    bool expected_reduced_value = true;

    
    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, (i%2 == 0 ? true : false) );
    }
    
    FRENSIE_CHECK_EQUAL( value_to_reduce_inline, expected_reduced_value );
  }

  // Reduce an array
  {
    std::array<bool,5> data_to_reduce;

    if( comm->rank()%2 == 0 )
      data_to_reduce = std::array<bool,5>( {true, false, true, false, true} );
    else
      data_to_reduce = std::array<bool,5>( {false, true, false, true, false} );

    std::array<bool,5> reduced_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, data_to_reduce, reduced_data, ReduceOp() ) );

    std::array<bool,5>
      expected_reduced_data( {true, false, true, false, true} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? true : false) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? false : true) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce an array inline
  {
    std::array<bool,5> data_to_reduce;

    if( comm->rank()%2 == 0 )
      data_to_reduce = std::array<bool,5>( {true, false, true, false, true} );
    else
      data_to_reduce = std::array<bool,5>( {false, true, false, true, false} );

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, data_to_reduce, ReduceOp() ) );

    std::array<bool,5>
      expected_reduced_data( {true, false, true, false, true} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? true : false) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? false : true) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( data_to_reduce, expected_reduced_data );
  }

  // Reduce an array using a view rvalue
  {
    std::array<bool,5> data_to_reduce;

    if( comm->rank()%2 == 0 )
      data_to_reduce = std::array<bool,5>( {true, false, true, false, true} );
    else
      data_to_reduce = std::array<bool,5>( {false, true, false, true, false} );

    std::array<bool,5> reduced_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, Utility::arrayView(data_to_reduce), Utility::arrayView(reduced_data), ReduceOp() ) );

    std::array<bool,5>
      expected_reduced_data( {true, false, true, false, true} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? true : false) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? false : true) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce an array using a view lvalue
  {
    std::array<bool,5> data_to_reduce;

    if( comm->rank()%2 == 0 )
      data_to_reduce = std::array<bool,5>( {true, false, true, false, true} );
    else
      data_to_reduce = std::array<bool,5>( {false, true, false, true, false} );

    Utility::ArrayView<const bool> view_of_data_to_reduce( data_to_reduce );
    
    std::array<bool,5> reduced_data;

    Utility::ArrayView<bool> view_of_reduced_data( reduced_data );

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, view_of_data_to_reduce, view_of_reduced_data, ReduceOp() ) );

    std::array<bool,5>
      expected_reduced_data( {true, false, true, false, true} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? true : false) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? false : true) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce an array inline using a view
  {
    std::array<bool,5> data_to_reduce;

    if( comm->rank()%2 == 0 )
      data_to_reduce = std::array<bool,5>( {true, false, true, false, true} );
    else
      data_to_reduce = std::array<bool,5>( {false, true, false, true, false} );

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, Utility::arrayView(data_to_reduce), ReduceOp() ) );

    std::array<bool,5>
      expected_reduced_data( {true, false, true, false, true} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? true : false) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? false : true) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( data_to_reduce, expected_reduced_data );
  }
}

//---------------------------------------------------------------------------//
// Check that an all reduce operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Communicator, allReduce, TypeOpPairs )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 1, ReduceOp );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // Reduce a single value
  {
    T value_to_reduce =
      (comm->rank()%2 == 0 ? initializeValue(T(), 0) : initializeValue(T(), 1));
    T reduced_value;

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, value_to_reduce, reduced_value, ReduceOp() ) );

    T expected_reduced_value = initializeValue(T(), 0);

    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, (i%2 == 0 ? initializeValue(T(), 0) : initializeValue(T(), 1)) );
    }

    FRENSIE_CHECK_EQUAL( reduced_value, expected_reduced_value );
  }

  // Reduce a value inline
  {
    T value_to_reduce_inline =
      (comm->rank()%2 == 0 ? initializeValue(T(), 0) : initializeValue(T(), 1));

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, value_to_reduce_inline, ReduceOp() ) );

    T expected_reduced_value = initializeValue(T(), 0);

    for( int i = 1; i <= comm->size()-1; ++i )
    {
      expected_reduced_value =
        ReduceOp()( expected_reduced_value, (i%2 == 0 ? initializeValue(T(), 0) : initializeValue(T(), 1)) );
    }

    FRENSIE_CHECK_EQUAL( value_to_reduce_inline, expected_reduced_value );
  }

  // Reduce an array
  {
    std::array<T,5> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::array<T,5>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::array<T,5>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    std::array<T,5> reduced_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, data_to_reduce, reduced_data, ReduceOp() ) );

    std::array<T,5> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce an array inline
  {
    std::array<T,5> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::array<T,5>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::array<T,5>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, data_to_reduce, ReduceOp() ) );

    std::array<T,5> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( data_to_reduce, expected_reduced_data );
  }

  // Reduce a vector
  {
    std::vector<T> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::vector<T>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::vector<T>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    std::vector<T> reduced_data;

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, data_to_reduce, reduced_data, ReduceOp() ) );

    std::vector<T> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce a vector inline
  {
    std::vector<T> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::vector<T>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::vector<T>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, data_to_reduce, ReduceOp() ) );

    std::vector<T> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( data_to_reduce, expected_reduced_data );
  }

  // Reduce an array using a view rvalue
  {
    std::vector<T> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::vector<T>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::vector<T>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    std::vector<T> reduced_data( data_to_reduce.size() );

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, Utility::arrayView(data_to_reduce), Utility::arrayView(reduced_data), ReduceOp() ) );

    std::vector<T> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce an array using a view lvalue
  {
    std::vector<T> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::vector<T>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::vector<T>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    Utility::ArrayView<const T> view_of_data_to_reduce( data_to_reduce );

    std::vector<T> reduced_data( data_to_reduce.size() );

    Utility::ArrayView<T> view_of_reduced_data( reduced_data );

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, view_of_data_to_reduce, view_of_reduced_data, ReduceOp() ) );

    std::vector<T> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( reduced_data, expected_reduced_data );
  }

  // Reduce an array inline using a view
  {
    std::vector<T> data_to_reduce;

    const T zero_value = initializeValue(T(), 0);
    const T one_value = initializeValue(T(), 1);

    if( comm->rank()%2 == 0 )
    {
      data_to_reduce = std::vector<T>( {zero_value, one_value, zero_value, one_value, zero_value} );
    }
    else
    {
      data_to_reduce = std::vector<T>( {one_value, zero_value, one_value, zero_value, one_value} );
    }

    FRENSIE_REQUIRE_NO_THROW( Utility::allReduce( *comm, Utility::arrayView(data_to_reduce), ReduceOp() ) );

    std::vector<T> expected_reduced_data( {zero_value, one_value, zero_value, one_value, zero_value} );

    for( int i = 0; i < expected_reduced_data.size(); ++i )
    {
      for( int j = 1; j <= comm->size()-1; ++j )
      {
        if( i%2 == 0 )
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? zero_value : one_value) );
        }
        else
        {
          expected_reduced_data[i] =
            ReduceOp()( expected_reduced_data[i], (j%2 == 0 ? one_value : zero_value) );
        }
      }
    }

    FRENSIE_CHECK_EQUAL( data_to_reduce, expected_reduced_data );
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorAllReduceHelper.cpp
//---------------------------------------------------------------------------//
