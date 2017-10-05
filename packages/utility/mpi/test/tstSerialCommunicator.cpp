//---------------------------------------------------------------------------//
//!
//! \file   tstSerialCommunicator.cpp
//! \author Alex Robinson
//! \brief  Communicator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_SerialCommunicator.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
#include "Utility_Vector.hpp"
#include "Utility_List.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
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
                   std::pair<float,int>, std::tuple<float,int>,
                   std::pair<double,int>, std::tuple<double,int>,
                   std::pair<long,int>, std::tuple<long,int>,
                   std::pair<int,int>, std::tuple<int,int>,
                   std::pair<short,int>, std::tuple<short,int> > BasicTypes;

template<typename T>
struct TypeOpPairList
{
  typedef std::tuple<std::tuple<T,std::plus<T> >,
                     std::tuple<T,std::minus<T> >,
                     std::tuple<T,std::multiplies<T> >,
                     std::tuple<T,std::divides<T> >,
                     std::tuple<T,std::modulus<T> >,
                     std::tuple<T,std::negate<T> >,
                     std::tuple<T,std::logical_and<T> >,
                     std::tuple<T,std::logical_or<T> >,
                     std::tuple<T,std::bit_and<T> >,
                     std::tuple<T,std::bit_or<T> >,
                     std::tuple<T,std::bit_xor<T> > > type;
};

template<typename T,typename OtherTypeOpPairList,typename Enabled = void>
struct MergeTypeOpPairList
{
  typedef OtherTypeOpPairList type;
};

template<typename T,typename OtherTypeOpPairList>
struct MergeTypeOpPairList<T,OtherTypeOpPairList,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
  typedef decltype(std::tuple_cat( typename TypeOpPairList<T>::type(), OtherTypeOpPairList() )) type;
};


template<typename T>
struct SequenceContainerList
{
  typedef std::tuple<std::array<T,10>,
                     std::vector<T>,
                     std::list<T>,
                     std::forward_list<T>,
                     std::deque<T> > type;
};

template<typename T>
struct SetList
{
  typedef std::tuple<std::set<T>,std::unordered_set<T> > type;
};

template<typename T,typename OtherSetList,typename Enabled = void>
struct MergeSetList
{
  typedef OtherSetList type;
};

template<typename T,typename OtherSetList>
struct MergeSetList<T,OtherSetList,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
  typedef decltype(std::tuple_cat( typename SetList<T>::type(), OtherSetList() )) type;
};

template<typename T>
struct MapList
{
  typedef std::tuple<std::map<typename Utility::TupleElement<0,T>::type,T>,
                     std::unordered_map<typename Utility::TupleElement<0,T>::type,T> > type;
};

template<typename... Types>
struct MergeContainerLists;

template<typename T, typename... Types>
struct MergeContainerLists<T,Types...>
{
  typedef typename MergeTypeOpPairList<T,typename MergeContainerLists<Types...>::TypeOpPairList>::type TypeOpPairList;
  
  typedef decltype(std::tuple_cat( typename SequenceContainerList<T>::type(), typename MergeContainerLists<Types...>::SequenceList() )) SequenceList;

  typedef typename MergeSetList<T,typename MergeContainerLists<Types...>::SetList>::type SetList;

  typedef decltype(std::tuple_cat( typename MapList<T>::type(), typename MergeContainerLists<Types...>::MapList() )) MapList;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef typename TypeOpPairList<T>::type TypeOpPairList;
  typedef typename SequenceContainerList<T>::type SequenceList;
  typedef typename SetList<T>::type SetList;
  typedef typename MapList<T>::type MapList;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef typename MergeContainerLists<BasicTypes>::TypeOpPairList BasicTypeOpPairs;

typedef typename MergeContainerLists<BasicTypes>::SequenceList SequenceContainerTypes;

typedef decltype(std::tuple_cat( typename MergeContainerLists<BasicTypes>::SetList(), typename MergeContainerLists<BasicTypes>::MapList() )) AssociativeContainerTypes;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
template<typename SequenceContainer>
inline void resizeSequenceContainer( SequenceContainer& container,
                                     const typename SequenceContainer::value_type& init_value )
{ container.resize( 10, init_value ); }

template<typename T, size_t N>
inline void resizeSequenceContainer( std::array<T,N>& container,
                                     const T& init_value )
{ container.fill( init_value ); }

template<typename SequenceContainer>
inline void clearSequenceContainer( SequenceContainer& container )
{ container.clear(); }

template<typename T, size_t N>
inline void clearSequenceContainer( std::array<T,N>& container )
{ container.fill( T() ); }

template<template<typename,typename...> class Set, typename T>
inline typename std::enable_if<std::is_same<Set<T>,std::set<T> >::value || std::is_same<Set<T>,std::unordered_set<T> >::value,void>::type
fillAssociativeContainer( Set<T>& container )
{
  for( size_t i = 0; i < 10; ++i )
  {
    if( std::is_same<T,char>::value || std::is_same<T,unsigned char>::value )
      container.insert( T(i+48) );
    else
      container.insert( T(i) );
  }
}

template<template<typename,typename,typename...> class Map, typename Key, typename T>
inline typename std::enable_if<std::is_same<Map<Key,T>,std::map<Key,T> >::value || std::is_same<Map<Key,T>,std::unordered_map<Key,T> >::value,void>::type
fillAssociativeContainer( Map<Key,T>& container )
{
  for( size_t i = 0; i < 10; ++i )
  {
    std::pair<Key,T> value;
    
    if( std::is_same<Key,char>::value || std::is_same<Key,unsigned char>::value )
      value.first = Key(i+48);
    else
      value.first = Key(i);

    if( std::is_same<T,char>::value || std::is_same<T,unsigned char>::value )
      Utility::get<0>(value.second) = i+48;
    else
      Utility::get<0>(value.second) = i;

    container.insert( value );
  }
}

template<typename AssociativeContainer>
inline void clearAssociativeContainer( AssociativeContainer& container )
{ container.clear(); }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a serial comm is valid
FRENSIE_UNIT_TEST( SerialCommunicator, isValid )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  FRENSIE_CHECK( comm->isValid() );
}

//---------------------------------------------------------------------------//
// Check that a serial comm does not use MPI
FRENSIE_UNIT_TEST( SerialCommunicator, isMPIUsed )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  FRENSIE_CHECK( !comm->isMPIUsed() );
}

//---------------------------------------------------------------------------//
// Check that the rank is always 0
FRENSIE_UNIT_TEST( SerialCommunicator, rank )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  FRENSIE_CHECK_EQUAL( comm->rank(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the size is always 1
FRENSIE_UNIT_TEST( SerialCommunicator, size )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  FRENSIE_CHECK_EQUAL( comm->size(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a barrier can be created
FRENSIE_UNIT_TEST( SerialCommunicator, barrier )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  FRENSIE_CHECK_NO_THROW( comm->barrier() );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be split
FRENSIE_UNIT_TEST( SerialCommunicator, split )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  // The color should be ignored
  std::shared_ptr<const Utility::Communicator> new_comm = comm->split( 0 );

  FRENSIE_REQUIRE( new_comm.get() != NULL );
  FRENSIE_REQUIRE( new_comm->isValid() );
  FRENSIE_CHECK_EQUAL( new_comm->rank(), 0 );
  FRENSIE_CHECK_EQUAL( new_comm->size(), 1 );

  // The color and key should be ignored
  new_comm = comm->split( 0, 0 );

  FRENSIE_REQUIRE( new_comm.get() != NULL );
  FRENSIE_REQUIRE( new_comm->isValid() );
  FRENSIE_CHECK_EQUAL( new_comm->rank(), 0 );
  FRENSIE_CHECK_EQUAL( new_comm->size(), 1 );
}

//---------------------------------------------------------------------------//
// Check that a timer can be created
FRENSIE_UNIT_TEST( SerialCommunicator, createTimer )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_CHECK( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be converted to a string
FRENSIE_UNIT_TEST( SerialCommunicator, toString )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );

  std::string comm_string = Utility::toString( *comm );

  FRENSIE_CHECK_EQUAL( comm_string, "Serial Communicator" );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be placed in a stream
FRENSIE_UNIT_TEST( SerialCommunicator, toStream )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );
  
  std::ostringstream oss;

  Utility::toStream( oss, *comm );

  FRENSIE_CHECK_EQUAL( oss.str(), "Serial Communicator" );
}

//---------------------------------------------------------------------------//
// Check that a serial communicator can be placed in a stream
FRENSIE_UNIT_TEST( SerialCommunicator, ostream_operator )
{
  std::shared_ptr<const Utility::Communicator>
    comm( new Utility::SerialCommunicator );
  
  std::ostringstream oss;

  oss << *comm;

  FRENSIE_CHECK_EQUAL( oss.str(), "Serial Communicator" );
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, allGather_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.allGather( data_to_send.data(), 1, data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.allGather( data_to_send.data(), data_to_send.size(), data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST( SerialCommunicator, allGather_string )
{
  Utility::SerialCommunicator comm;

  std::vector<std::string> data_to_send( 10 );
  
  for( size_t i = 0; i < data_to_send.size(); ++i )
    data_to_send[i] = std::string("test element ") + Utility::toString(i);

  std::vector<std::string> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.allGather( data_to_send.data(), 1, data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send[0], "test element 0" );

  // Send all the data
  comm.allGather( data_to_send.data(), data_to_send.size(), data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            allGather_sequence_containers,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

  Container container_to_send;
  resizeSequenceContainer( container_to_send, value );

  Container container_to_receive;
  
  comm.allGather( &container_to_send, 1, &container_to_receive );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            allGather_associative_containers,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  Container container_to_send;
  fillAssociativeContainer( container_to_send );

  Container container_to_receive;

  comm.allGather( &container_to_send, 1, &container_to_receive );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SerialCommunicator,
                                   allReduce,
                                   BasicTypeOpPairs )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 0, ReduceOp );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.allReduce( data_to_send.data(), 1, data_to_receive.data(), ReduceOp() );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.allReduce( data_to_send.data(), data_to_send.size(), data_to_receive.data(), ReduceOp() );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all-to-all operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, allToAll_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.allToAll( data_to_send.data(), 1, data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.allToAll( data_to_send.data(), data_to_send.size(), data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all-to-all operation can be conducted
FRENSIE_UNIT_TEST( SerialCommunicator, allToAll_string )
{
  Utility::SerialCommunicator comm;

  std::vector<std::string> data_to_send( 10 );
  
  for( size_t i = 0; i < data_to_send.size(); ++i )
    data_to_send[i] = std::string("test element ") + Utility::toString(i);

  std::vector<std::string> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.allToAll( data_to_send.data(), 1, data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send[0], "test element 0" );

  // Send all the data
  comm.allToAll( data_to_send.data(), data_to_send.size(), data_to_receive.data() );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all-to-all operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            allToAll_sequence_containers,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

  Container container_to_send;
  resizeSequenceContainer( container_to_send, value );

  Container container_to_receive;
  
  comm.allToAll( &container_to_send, 1, &container_to_receive );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an all-to-all operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            allToAll_associative_containers,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  Container container_to_send;
  fillAssociativeContainer( container_to_send );

  Container container_to_receive;

  comm.allToAll( &container_to_send, 1, &container_to_receive );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that an broadcast operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, broadcast_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_send_copy = data_to_send;

  // Send all the data
  FRENSIE_CHECK_NO_THROW( comm.broadcast( data_to_send.data(), data_to_send.size(), 0 ) );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_send_copy );
}

//---------------------------------------------------------------------------//
// Check that an broadcast operation can be conducted
FRENSIE_UNIT_TEST( SerialCommunicator, broadcast_string )
{
  Utility::SerialCommunicator comm;

  std::vector<std::string> data_to_send( 10 );
  
  for( size_t i = 0; i < data_to_send.size(); ++i )
    data_to_send[i] = std::string("test element ") + Utility::toString(i);

  std::vector<std::string> data_to_send_copy = data_to_send;

  // Send all the data
  FRENSIE_CHECK_NO_THROW( comm.broadcast( data_to_send.data(), data_to_send.size(), 0 ) );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_send_copy );
}

//---------------------------------------------------------------------------//
// Check that an broadcast operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            broadcast_sequence_containers,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

  Container container_to_send;
  resizeSequenceContainer( container_to_send, value );

  Container container_to_send_copy = container_to_send;
  
  FRENSIE_CHECK_NO_THROW( comm.broadcast( &container_to_send, 1, 0 ) );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_send_copy );
}

//---------------------------------------------------------------------------//
// Check that an broadcast operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            broadcast_associative_containers,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  Container container_to_send;
  fillAssociativeContainer( container_to_send );

  Container container_to_send_copy = container_to_send;

  FRENSIE_CHECK_NO_THROW( comm.broadcast( &container_to_send, 1, 0 ) );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_send_copy );
}

//---------------------------------------------------------------------------//
// Check that a gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, gather_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.gather( data_to_send.data(), 1, data_to_receive.data(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.gather( data_to_send.data(), data_to_send.size(), data_to_receive.data(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a gather operation can be conducted
FRENSIE_UNIT_TEST( SerialCommunicator, gather_string )
{
  Utility::SerialCommunicator comm;

  std::vector<std::string> data_to_send( 10 );
  
  for( size_t i = 0; i < data_to_send.size(); ++i )
    data_to_send[i] = std::string("test element ") + Utility::toString(i);

  std::vector<std::string> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.gather( data_to_send.data(), 1, data_to_receive.data(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send[0], "test element 0" );

  // Send all the data
  comm.gather( data_to_send.data(), data_to_send.size(), data_to_receive.data(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            gather_sequence_containers,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

  Container container_to_send;
  resizeSequenceContainer( container_to_send, value );

  Container container_to_receive;
  
  comm.gather( &container_to_send, 1, &container_to_receive, 0 );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            gather_associative_containers,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  Container container_to_send;
  fillAssociativeContainer( container_to_send );

  Container container_to_receive;

  comm.gather( &container_to_send, 1, &container_to_receive, 0 );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, gatherv_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  std::vector<T> data_to_send( 10 );
  for( size_t i = 0; i < data_to_send.size(); ++i )
  {
    Utility::get<0>( data_to_send[i] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49+i : 1+i);
  }

  std::vector<int> sizes( 1, 1 );
  std::vector<int> offsets( 1, 0 );
  
  T received_value;
  Utility::get<0>( received_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48 : 0);

  // Just send the first value
  comm.gatherv( data_to_send.data(), data_to_send.size(), &received_value, sizes, offsets, 0 );

  FRENSIE_CHECK_EQUAL( received_value, data_to_send.front() );

  // Just send the last value
  offsets.front() = data_to_send.size()-1;

  comm.gatherv( data_to_send.data(), data_to_send.size(), &received_value, sizes, offsets, 0 );

  FRENSIE_CHECK_EQUAL( received_value, data_to_send.back() );

  // Send all but the first and last value
  sizes.front() = data_to_send.size()-2;
  std::vector<T> data_to_receive( sizes.front() );
  
  offsets.front() = 1;
  
  comm.gatherv( data_to_send.data(), data_to_send.size(), data_to_receive.data(), sizes, offsets, 0 );

  FRENSIE_CHECK_EQUAL( data_to_send | Utility::Slice(offsets.front(), sizes.front()),
                       Utility::arrayView( data_to_receive ) );

  // Send all but the last value
  sizes.front() = data_to_send.size()-1;
  data_to_receive.clear();
  data_to_receive.resize( sizes.front() );

  comm.gatherv( data_to_send.data(), data_to_send.size(), data_to_receive.data(), sizes, 0 );

  FRENSIE_CHECK_EQUAL( data_to_send | Utility::Slice(0, sizes.front()),
                       Utility::arrayView( data_to_receive ) );
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, scatter_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.scatter( data_to_send.data(), data_to_receive.data(), 1, 0 );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.scatter( data_to_send.data(), data_to_receive.data(), data_to_send.size(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted
FRENSIE_UNIT_TEST( SerialCommunicator, scatter_string )
{
  Utility::SerialCommunicator comm;

  std::vector<std::string> data_to_send( 10 );
  
  for( size_t i = 0; i < data_to_send.size(); ++i )
    data_to_send[i] = std::string("test element ") + Utility::toString(i);

  std::vector<std::string> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.scatter( data_to_send.data(), data_to_receive.data(), 1, 0 );

  FRENSIE_CHECK_EQUAL( data_to_send[0], "test element 0" );

  // Send all the data
  comm.scatter( data_to_send.data(), data_to_receive.data(), data_to_send.size(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            scatter_sequence_containers,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

  Container container_to_send;
  resizeSequenceContainer( container_to_send, value );

  Container container_to_receive;
  
  comm.scatter( &container_to_send, &container_to_receive, 1, 0 );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator,
                            scatter_associative_containers,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  Utility::SerialCommunicator comm;

  Container container_to_send;
  fillAssociativeContainer( container_to_send );

  Container container_to_receive;

  comm.scatter( &container_to_send, &container_to_receive, 1, 0 );

  FRENSIE_CHECK_EQUAL( container_to_send, container_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a scatterv operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( SerialCommunicator, scatterv_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SerialCommunicator comm;

  std::vector<T> data_to_send( 10 );
  for( size_t i = 0; i < data_to_send.size(); ++i )
  {
    Utility::get<0>( data_to_send[i] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49+i : 1+i);
  }

  std::vector<int> sizes( 1, 1 );
  std::vector<int> offsets( 1, 0 );
  
  T received_value;
  Utility::get<0>( received_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48 : 0);

  // Just send the first value
  comm.scatterv( data_to_send.data(), sizes, offsets, &received_value, 1, 0 );

  FRENSIE_CHECK_EQUAL( received_value, data_to_send.front() );

  // Just send the last value
  offsets.front() = data_to_send.size()-1;

  comm.scatterv( data_to_send.data(), sizes, offsets, &received_value, 1, 0 );

  FRENSIE_CHECK_EQUAL( received_value, data_to_send.back() );

  // Send all but the first and last value
  sizes.front() = data_to_send.size()-2;
  std::vector<T> data_to_receive( sizes.front() );
  
  offsets.front() = 1;
  
  comm.scatterv( data_to_send.data(), sizes, offsets, data_to_receive.data(), data_to_receive.size(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send | Utility::Slice(offsets.front(), sizes.front()),
                       Utility::arrayView( data_to_receive ) );

  // Send all but the last value
  sizes.front() = data_to_send.size()-1;
  data_to_receive.clear();
  data_to_receive.resize( sizes.front() );

  comm.scatterv( data_to_send.data(), sizes, data_to_receive.data(), data_to_receive.size(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send | Utility::Slice(0, sizes.front()),
                       Utility::arrayView( data_to_receive ) );
}

//---------------------------------------------------------------------------//
// Check that a reduce operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SerialCommunicator,
                                   reduce,
                                   BasicTypeOpPairs )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 0, ReduceOp );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.reduce( data_to_send.data(), 1, data_to_receive.data(), ReduceOp(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.reduce( data_to_send.data(), data_to_send.size(), data_to_receive.data(), ReduceOp(), 0 );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a prefix scan operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SerialCommunicator,
                                   scan,
                                   BasicTypeOpPairs )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  FETCH_TEMPLATE_PARAM( 0, ReduceOp );
  
  Utility::SerialCommunicator comm;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
  
  std::vector<T> data_to_send( 10, value );

  std::vector<T> data_to_receive( data_to_send.size() );

  // Just send the first value
  comm.scan( data_to_send.data(), 1, data_to_receive.data(), ReduceOp() );

  FRENSIE_CHECK_EQUAL( data_to_send[0], data_to_receive[0] );

  // Send all the data
  comm.scan( data_to_send.data(), data_to_send.size(), data_to_receive.data(), ReduceOp() );

  FRENSIE_CHECK_EQUAL( data_to_send, data_to_receive );
}

//---------------------------------------------------------------------------//
// end tstSerialCommunicator.cpp
//---------------------------------------------------------------------------//
