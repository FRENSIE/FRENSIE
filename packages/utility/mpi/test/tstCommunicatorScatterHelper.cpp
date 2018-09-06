//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorScatterHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator scatter helper function unit tests
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
typedef std::tuple<bool,
                   char, unsigned char,
                   short, unsigned short,
                   int, unsigned int,
                   long, unsigned long,
                   long long, unsigned long long,
                   float, double,
                   std::string,
                   std::pair<float,int>, std::tuple<float,int>,
                   std::pair<double,int>, std::tuple<double,int>,
                   std::pair<long,int>, std::tuple<long,int>,
                   std::pair<int,int>, std::tuple<int,int>,
                   std::pair<short,int>, std::tuple<short,int> > BasicTypes;

typedef std::tuple<bool,char,short,int,long,long long,double,std::string,std::pair<float,int>, std::tuple<float,int> > BasicTypesSubset;
typedef std::tuple<char,int,double> BasicTypesMinSubset;

template<typename T>
struct SequenceContainerList
{
  typedef std::tuple<std::array<T,10>,
                     std::vector<T>,
                     std::list<T>,
                     std::forward_list<T>,
                     std::deque<T> > type;
};

template<typename T, typename Enabled = void>
struct SetList;

template<typename T>
struct SetList<T,typename std::enable_if<Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<std::set<T>,std::unordered_set<T> > type;
};

template<typename T>
struct SetList<T,typename std::enable_if<!Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<> type;
};

template<typename T, typename Enabled = void>
struct MapList;

template<typename T>
struct MapList<T,typename std::enable_if<Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<std::map<T,T>,std::unordered_map<T,T> > type;
};

template<typename T>
struct MapList<T,typename std::enable_if<!Utility::IsHashable<T>::value>::type>
{
  typedef std::tuple<> type;
};

template<typename... Types>
struct MergeContainerLists;

template<typename T, typename... Types>
struct MergeContainerLists<T,Types...>
{
  typedef decltype(std::tuple_cat( typename MergeContainerLists<T>::type(),
                                   typename MergeContainerLists<Types...>::type() )) type;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef decltype(std::tuple_cat( typename SequenceContainerList<T>::type(),
                                   typename SetList<T>::type(),
                                   typename MapList<T>::type() )) type;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef typename MergeContainerLists<BasicTypesSubset>::type ContainerTypes;
typedef typename MergeContainerLists<BasicTypesMinSubset>::type ContainerTypesSubset;

typedef decltype(std::tuple_cat(BasicTypes(), ContainerTypes())) Types;
typedef decltype(std::tuple_cat(BasicTypes(), ContainerTypesSubset())) TypesSubset;

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

inline std::string initializeValue( std::string, int i )
{ return Utility::toString(i); }

template<typename T1, typename T2>
inline std::pair<T1,T2> initializeValue( std::pair<T1,T2>, int i )
{
  return std::make_pair( initializeValue( T1(), i ),
                         initializeValue( T2(), i ) );
}

template<typename... Types>
inline std::tuple<Types...> initializeValue( std::tuple<Types...>, int i )
{
  return std::make_tuple( initializeValue<Types>( Types(), i )... );
}

template<template<typename,typename...> class SequenceContainer,
         typename T>
inline SequenceContainer<T> initializeValue( SequenceContainer<T>, int i )
{
  return SequenceContainer<T>( 10, initializeValue( T(), i ) );
}

template<typename T, size_t N>
inline std::array<T,N> initializeValue( std::array<T,N>, int i )
{
  std::array<T,N> container;
  container.fill( initializeValue( T(), i ) );

  return container;
}

template<template<typename,typename...> class Set, typename T>
inline void fillSet( Set<T>& container, const int seed )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
    container.insert( initializeValue( T(), seed*size+i ) );
}

template<typename T>
inline std::set<T> initializeValue( std::set<T>, int i )
{
  std::set<T> container;
  fillSet( container, i );
  return container;
}

template<typename T>
inline std::unordered_set<T> initializeValue( std::unordered_set<T>, int i )
{
  std::unordered_set<T> container;
  fillSet( container, i );
  return container;
}

template<template<typename,typename,typename...> class Map,
         typename Key, typename T>
inline void fillMap( Map<Key,T>& container, const int seed )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
    container.insert( initializeValue( std::pair<const Key,T>(), seed*size+i ) );
}

template<typename Key, typename T>
inline std::map<Key,T> initializeValue( std::map<Key,T>, int i )
{
  std::map<Key,T> container;
  fillMap( container, i );
  return container;
}

template<typename Key, typename T>
inline std::unordered_map<Key,T> initializeValue( std::unordered_map<Key,T>, int i )
{
  std::unordered_map<Key,T> container;
  fillMap( container, i );
  return container;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted - init list to single value
// per proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, scatter_init_list_single_value, TypesSubset )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T scattered_value = initializeValue( T(), 0 );

  if( comm->rank() == 0 )
  {
    if( comm->size() == 1 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 2 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 3 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 4 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 5 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 6 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 5)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 7 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 6)}, scattered_value, 0 ) );
    }
    else if( comm->size() == 8 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 6), initializeValue(T(), 7)}, scattered_value, 0 ) );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "This test does not support more that 8 procs!" );
    }
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {}, scattered_value, 0 ) );
  }

  const T expected_scattered_value = initializeValue( T(), comm->rank() );
  
  FRENSIE_CHECK_EQUAL( scattered_value, expected_scattered_value );

  if( comm->size() > 1 )
  {
    scattered_value = initializeValue( T(), 0 );
    
    if( comm->rank() == 1 )
    {
      if( comm->size() == 2 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1)}, scattered_value, 1 ) );
      }
      else if( comm->size() == 3 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2)}, scattered_value, 1 ) );
      }
      else if( comm->size() == 4 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3)}, scattered_value, 1 ) );
      }
      else if( comm->size() == 5 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4)}, scattered_value, 1 ) );
      }
      else if( comm->size() == 6 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 5)}, scattered_value, 1 ) );
      }
      else if( comm->size() == 7 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 6)}, scattered_value, 1 ) );
      }
      else if( comm->size() == 8 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 6), initializeValue(T(), 7)}, scattered_value, 1 ) );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                         "This test does not support more that 8 procs!" );
      }
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, scattered_value, 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_value, expected_scattered_value );
  }
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted - view to single value
// per proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, scatter_view_single_value, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T scattered_values[4] = {initializeValue( T(), 0 ),
                           initializeValue( T(), 0 ),
                           initializeValue( T(), 0 ),
                           initializeValue( T(), 0 )};

  if( comm->rank() == 0 )
  {
    T values[comm->size()];

    for( int i = 0; i < comm->size(); ++i )
      values[i] = initializeValue( T(), i );

    Utility::ArrayView<T> values_view( values, comm->size() );
    Utility::ArrayView<const T> values_view_of_const = values_view.toConst();

    // Scatter using a view lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view, scattered_values[0], 0 ) );
    
    // Scatter using a view-of-const lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view_of_const, scattered_values[1], 0 ) );

    // Scatter using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>( values, comm->size() ), scattered_values[2], 0 ) );

    // Scatter using a view-of-const rvalues
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>( values, comm->size() ), scattered_values[3], 0 ) );
  }
  else
  {
    Utility::ArrayView<T> dummy_view;
    Utility::ArrayView<const T> dummy_view_of_const;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, dummy_view, scattered_values[0], 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, dummy_view_of_const, scattered_values[1], 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>(), scattered_values[2], 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>(), scattered_values[3], 0 ) );
  }

  const T expected_scattered_values[4] = {initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() )};

  Utility::ArrayView<const T> scattered_values_view( scattered_values, 4 );
  Utility::ArrayView<const T> expected_scattered_values_view( expected_scattered_values, 4 );
  FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );

  if( comm->size() > 1 )
  {
    scattered_values[0] = initializeValue( T(), 0 );
    scattered_values[1] = initializeValue( T(), 0 );
    scattered_values[2] = initializeValue( T(), 0 );
    scattered_values[3] = initializeValue( T(), 0 );
    
    if( comm->rank() == 1 )
    {
      T values[comm->size()];

      for( int i = 0; i < comm->size(); ++i )
        values[i] = initializeValue( T(), i );

      Utility::ArrayView<T> values_view( values, comm->size() );
      Utility::ArrayView<const T> values_view_of_const = values_view.toConst();

      // Scatter using a view lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view, scattered_values[0], 1 ) );
      
      // Scatter using a view-of-const lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view_of_const, scattered_values[1], 1 ) );
      
      // Scatter using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>( values, comm->size() ), scattered_values[2], 1 ) );
      
      // Scatter using a view-of-const rvalues
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>( values, comm->size() ), scattered_values[3], 1 ) );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>(), scattered_values[0], 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>(), scattered_values[1], 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, scattered_values[2], 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, scattered_values[3], 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );
  }
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted - init list to multiple
// values per proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, scatter_init_list_multiple_values, TypesSubset )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T scattered_values[2] = {initializeValue( T(), 0 ),
                           initializeValue( T(), 0 )};
  
  Utility::ArrayView<T> scattered_values_view( scattered_values, 2 );

  if( comm->rank() == 0 )
  {
    if( comm->size() == 1 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 2 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 3 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 4 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 5 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 6 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 5)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 7 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 5), initializeValue(T(), 6), initializeValue(T(), 6)}, scattered_values_view, 0 ) );
    }
    else if( comm->size() == 8 )
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 5), initializeValue(T(), 6), initializeValue(T(), 6), initializeValue(T(), 7), initializeValue(T(), 7)}, scattered_values_view, 0 ) );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "This test does not support more that 8 procs!" );
    }
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter<T>( *comm, scattered_values_view, 0 ) );
  }

  const T expected_scattered_values[2] = {initializeValue( T(), comm->rank() ),
                                          initializeValue( T(), comm->rank() )};
  Utility::ArrayView<const T> expected_scattered_values_view( expected_scattered_values, 2 );
  
  FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );

  if( comm->size() > 1 )
  {
    scattered_values[0] = initializeValue( T(), 0 );
    scattered_values[1] = initializeValue( T(), 0 );
    
    if( comm->rank() == 1 )
    {
      if( comm->size() == 2 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1)}, scattered_values_view, 1 ) );
      }
      else if( comm->size() == 3 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2)}, scattered_values_view, 1 ) );
      }
      else if( comm->size() == 4 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3)}, scattered_values_view, 1 ) );
      }
      else if( comm->size() == 5 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4)}, scattered_values_view, 1 ) );
      }
      else if( comm->size() == 6 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 5)}, scattered_values_view, 1 ) );
      }
      else if( comm->size() == 7 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 5), initializeValue(T(), 6), initializeValue(T(), 6)}, scattered_values_view, 1 ) );
      }
      else if( comm->size() == 8 )
      {
        FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, {initializeValue(T(), 0), initializeValue(T(), 0), initializeValue(T(), 1), initializeValue(T(), 1), initializeValue(T(), 2), initializeValue(T(), 2), initializeValue(T(), 3), initializeValue(T(), 3), initializeValue(T(), 4), initializeValue(T(), 4), initializeValue(T(), 5), initializeValue(T(), 5), initializeValue(T(), 6), initializeValue(T(), 6), initializeValue(T(), 7), initializeValue(T(), 7)}, scattered_values_view, 1 ) );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                         "This test does not support more that 8 procs!" );
      }
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter<T>( *comm, scattered_values_view, 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );
  }
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted - view to multiple values
// per proc
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, scatter_view_multiple_values, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T scattered_values[8];
  
  Utility::ArrayView<T> scattered_values_view( scattered_values, 8 );
  scattered_values_view.fill( initializeValue( T(), 0 ) );

  if( comm->rank() == 0 )
  {
    T values[comm->size()*2];

    for( int i = 0; i < comm->size(); ++i )
    {
      values[i*2] = initializeValue( T(), i );
      values[i*2+1] = initializeValue( T(), i );
    }

    Utility::ArrayView<T> values_view( values, comm->size()*2 );
    Utility::ArrayView<const T> values_view_of_const = values_view.toConst();

    // Scatter using a view lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view, scattered_values_view(0, 2), 0 ) );
    
    // Scatter using a view-of-const lvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view_of_const, scattered_values_view(2, 2), 0 ) );

    // Scatter using a view rvalue
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>( values, comm->size()*2 ), scattered_values_view(4, 2), 0 ) );

    // Scatter using a view-of-const rvalues
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>( values, comm->size()*2 ), scattered_values_view(6, 2), 0 ) );
  }
  else
  {
    Utility::ArrayView<T> dummy_view;
    Utility::ArrayView<const T> dummy_view_of_const;
    
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, dummy_view, scattered_values_view(0, 2), 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, dummy_view_of_const, scattered_values_view(2, 2), 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>(), scattered_values_view(4, 2), 0 ) );
    FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>(), scattered_values_view(6, 2), 0 ) );
  }

  T expected_scattered_values[8];

  Utility::ArrayView<T> expected_scattered_values_view( expected_scattered_values, 8 );
  expected_scattered_values_view.fill( initializeValue( T(), comm->rank() ) );
                                       
  FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );

  if( comm->size() > 1 )
  {
    scattered_values_view.fill( initializeValue( T(), 0 ) );
    
    if( comm->rank() == 1 )
    {
      T values[comm->size()*2];

      for( int i = 0; i < comm->size(); ++i )
      {
        values[i*2] = initializeValue( T(), i );
        values[i*2+1] = initializeValue( T(), i );
      }

      Utility::ArrayView<T> values_view( values, comm->size()*2 );
      Utility::ArrayView<const T> values_view_of_const = values_view.toConst();

      // Scatter using a view lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view, scattered_values_view(0, 2), 1 ) );
      
      // Scatter using a view-of-const lvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, values_view_of_const, scattered_values_view(2, 2), 1 ) );
      
      // Scatter using a view rvalue
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<T>( values, comm->size()*2 ), scattered_values_view(4, 2), 1 ) );
      
      // Scatter using a view-of-const rvalues
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, Utility::ArrayView<const T>( values, comm->size()*2 ), scattered_values_view(6, 2), 1 ) );
    }
    else
    {
      Utility::ArrayView<T> dummy_view;
      Utility::ArrayView<const T> dummy_view_of_const;
      
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, dummy_view, scattered_values_view(0, 2), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, dummy_view_of_const, scattered_values_view(2, 2), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, scattered_values_view(4, 2), 1 ) );
      FRENSIE_REQUIRE_NO_THROW( Utility::scatter( *comm, scattered_values_view(6, 2), 1 ) );
    }
    
    FRENSIE_CHECK_EQUAL( scattered_values_view, expected_scattered_values_view );
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorScatterHelper.cpp
//---------------------------------------------------------------------------//
