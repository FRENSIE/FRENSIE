//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorAllGatherHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator allGather helper function unit tests
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
                   float, double,
                   std::string,
                   std::pair<float,int>, std::tuple<float,int>,
                   std::pair<double,int>, std::tuple<double,int>,
                   std::pair<long,int>, std::tuple<long,int>,
                   std::pair<int,int>, std::tuple<int,int>,
                   std::pair<short,int>, std::tuple<short,int> > BasicTypes;

typedef std::tuple<bool,char,short,int,long,long long,double,std::string,std::pair<float,int>, std::tuple<float,int> > BasicTypesSubset;

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

typedef decltype(std::tuple_cat(BasicTypes(), ContainerTypes())) Types;

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
// Check that an all gather operation can be conducted with bools
FRENSIE_UNIT_TEST( Communicator, allGather_bool )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  bool value = (comm->rank()%2 == 0 ? true : false);
  
  std::array<bool,10> data_to_send;
  data_to_send.fill( value );
  
  Utility::ArrayView<const bool> view_of_data_to_send( data_to_send );

  // Gather the first values only - store using pre-sized array view
  bool data_to_receive[data_to_send.size()*comm->size()];

  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, data_to_send.front(), Utility::ArrayView<bool>(data_to_receive, data_to_receive+comm->size()) ) );

  for( int i = 0; i < comm->size(); ++i )
  {
    bool expected_value = (i%2 == 0 ? true : false);
    
    FRENSIE_CHECK_EQUAL( data_to_receive[i], expected_value );
  }

  // Gather all values - store using pre-sized array view
  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, Utility::arrayView(data_to_send), Utility::ArrayView<bool>(data_to_receive, data_to_receive+data_to_send.size()*comm->size()) ) );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    std::array<bool,10> expected_values;
    expected_values.fill( (i%2 == 0 ? true : false) );

    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const bool>( data_to_receive+i*data_to_send.size(), data_to_receive+(i+1)*data_to_send.size() ),
                         Utility::arrayView(expected_values) );
  }

  // Gather values sent using initializer list temporary - store using
  // pre-sized array view
  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, {value, value, value, value, value}, Utility::ArrayView<bool>( data_to_receive, data_to_receive+5*comm->size() ) ) );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    std::array<bool,5> expected_values;
    expected_values.fill( (i%2 == 0 ? true : false) );

    FRENSIE_CHECK_EQUAL( Utility::ArrayView<const bool>( data_to_receive+i*5, data_to_receive+(i+1)*5 ),
                         Utility::arrayView(expected_values) );
  }
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, allGather, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T value = initializeValue( T(), comm->rank() );
  
  std::vector<T> data_to_send( 10, value );
  
  Utility::ArrayView<const T> view_of_data_to_send( data_to_send );

  // Gather the first values only - the receive vector should be resized
  std::vector<T> data_to_receive;

  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, data_to_send.front(), data_to_receive ) );
  FRENSIE_REQUIRE_EQUAL( data_to_receive.size(), comm->size() );
    
  for( int i = 0; i < comm->size(); ++i )
  {
    T expected_value = initializeValue( T(), i );
    
    FRENSIE_CHECK_EQUAL( data_to_receive[i], expected_value );
  }

  // Gather the first values only - store using pre-sized array view
  data_to_receive.clear();
  data_to_receive.resize( comm->size() );
  
  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, data_to_send.front(), Utility::arrayView(data_to_receive) ) );

  for( int i = 0; i < comm->size(); ++i )
  {
    T expected_value = initializeValue( T(), i );
    
    FRENSIE_CHECK_EQUAL( data_to_receive[i], expected_value );
  }

  // Gather all values - the receive vector should be resized
  data_to_receive.clear();

  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, Utility::arrayView(data_to_send), data_to_receive ) );
  FRENSIE_REQUIRE_EQUAL( data_to_receive.size(), data_to_send.size()*comm->size() );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    T expected_value = initializeValue( T(), i );

    FRENSIE_CHECK_EQUAL( data_to_receive | Utility::Slice( i*data_to_send.size(), data_to_send.size() ),
                         Utility::arrayView(std::vector<T>(data_to_send.size(), expected_value)) );
  }

  // Gather all values - store using pre-sized array view
  data_to_receive.clear();
  data_to_receive.resize( data_to_send.size()*comm->size() );

  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, Utility::arrayView(data_to_send), Utility::arrayView(data_to_receive) ) );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    T expected_value = initializeValue( T(), i );

    FRENSIE_CHECK_EQUAL( data_to_receive | Utility::Slice( i*data_to_send.size(), data_to_send.size() ),
                         Utility::arrayView(std::vector<T>(data_to_send.size(), expected_value)) );
  }

  // Gather values sent using initializer list temporary - the receive vector
  // should be resized
  data_to_receive.clear();

  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, {value, value, value, value, value}, data_to_receive ) );
  FRENSIE_REQUIRE_EQUAL( data_to_receive.size(), 5*comm->size() );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    T expected_value = initializeValue( T(), i );

    FRENSIE_CHECK_EQUAL( data_to_receive | Utility::Slice( i*5, 5 ),
                         Utility::arrayView(std::vector<T>(5, expected_value)) );
  }

  // Gather values sent using initializer list temporary - store using
  // pre-sized array view
  data_to_receive.clear();
  data_to_receive.resize( 5*comm->size() );

  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, {value, value, value, value, value}, Utility::arrayView(data_to_receive) ) );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    T expected_value = initializeValue( T(), i );

    FRENSIE_CHECK_EQUAL( data_to_receive | Utility::Slice( i*5, 5 ),
                         Utility::arrayView(std::vector<T>(5, expected_value)) );
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorAllGatherHelper.cpp
//---------------------------------------------------------------------------//
