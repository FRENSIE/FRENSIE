//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorIsendIrecvHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator isend/irecv helper function unit tests
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
                   std::pair<float,int>, 
                   std::pair<double,int>, 
                   std::pair<long,int>, 
                   std::pair<int,int>, 
                   std::pair<short,int> > BasicNativeTypes;

typedef std::tuple<std::string, std::tuple<float,int>, std::tuple<double,int>,std::tuple<long,int>,std::tuple<int,int>,std::tuple<short,int> > BasicNonNativeTypes;

typedef decltype(std::tuple_cat(BasicNativeTypes(), BasicNonNativeTypes())) BasicTypes;

typedef std::tuple<bool,char,short,int,long,long long,double,std::string,std::pair<float,int>, std::tuple<float,int> > BasicTypesSubset;

// std::array taken out of list due to it working properly with the boost 1.72 mpi bug. if mpi bug is fixed, reintroduce std::array<T, 10> into tuple.
template<typename T>
struct SequenceContainerList
{
  typedef std::tuple<std::vector<T>,
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
inline void fillContainer( SequenceContainer<T>& container, int seed = 0 )
{
  container.clear();
  container.resize( 10, initializeValue( T(), seed ) );
}

template<typename T, size_t N>
inline void fillContainer( std::array<T,N>& container, int seed = 0 )
{ container.fill( initializeValue( T(), seed ) ); }

template<template<typename,typename...> class Set, typename T>
inline void fillSet( Set<T>& container, const int seed )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
    container.insert( initializeValue( T(), seed*size+i ) );
}

template<typename T>
inline void fillContainer( std::set<T>& container, int seed = 0 )
{ fillSet( container, seed ); }

template<typename T>
inline void fillContainer( std::unordered_set<T>& container, int seed = 0 )
{ fillSet( container, seed ); }

template<template<typename,typename,typename...> class Map,
         typename Key, typename T>
inline void fillMap( Map<Key,T>& container, const int seed )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
    container.insert( initializeValue( std::pair<const Key,T>(), seed*size+i ) );
}

template<typename Key, typename T>
inline void fillContainer( std::map<Key,T>& container, int seed = 0 )
{ fillMap( container, seed ); }

template<typename Key, typename T>
inline void fillContainer( std::unordered_map<Key,T>& container, int seed = 0 )
{ fillMap( container, seed ); }

template<typename Container>
inline void clearContainer( Container& container )
{ container.clear(); }

template<typename T, size_t N>
inline void clearContainer( std::array<T,N>& container )
{ container.fill( initializeValue( T(), 0 ) ); }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that basic messages can be send and received for BasicNativeTypes (separated with subsequent test due to MPI bug)
FRENSIE_UNIT_TEST_TEMPLATE( Communicator_Native, isend_irecv_basic, BasicNativeTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value = initializeValue( T(), 1 );

    std::vector<int> number_of_values( {10, 8} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      T* values_to_send = new T[number_of_values[raw_data_send_tag]];
      Utility::ArrayView<T> view_of_values_to_send( values_to_send, values_to_send+number_of_values[raw_data_send_tag] );
      
      view_of_values_to_send.fill( value );

      std::vector<Utility::Communicator::Request> requests( 2 );

      // Raw data send
      requests[raw_data_send_tag] = 
        Utility::isend( *comm, 0, raw_data_send_tag, view_of_values_to_send );

      // Send all but the first and last values using a view
      requests[view_data_send_tag] = 
        Utility::isend( *comm, 0, view_data_send_tag, view_of_values_to_send( 1, number_of_values[view_data_send_tag] ) );

      std::vector<Utility::Communicator::Status> statuses( 2 );

      // Wait for all sends to complete
      Utility::wait( requests, statuses );

      FRENSIE_REQUIRE( statuses[raw_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[raw_data_send_tag].cancelled() );

      FRENSIE_REQUIRE( statuses[view_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[view_data_send_tag].cancelled() );
    }
    else
    {
      for( int i = 1; i < comm->size(); ++i )
      {
        T raw_values_to_receive[number_of_values[raw_data_send_tag]];
        Utility::ArrayView<T> view_of_raw_values_to_receive( raw_values_to_receive, raw_values_to_receive+number_of_values[raw_data_send_tag] );
        
        T view_values_to_receive[number_of_values[view_data_send_tag]];
        Utility::ArrayView<T> view_of_view_values_to_receive( view_values_to_receive, view_values_to_receive+number_of_values[view_data_send_tag] );

        T expected_raw_values_to_receive[number_of_values[raw_data_send_tag]];
        T expected_view_values_to_receive[number_of_values[view_data_send_tag]];
        Utility::ArrayView<const T> view_of_expected_raw_values_to_receive;
        Utility::ArrayView<const T> view_of_expected_view_values_to_receive;

        {
          Utility::ArrayView<T> tmp_view_of_expected_raw_values_to_receive( expected_raw_values_to_receive, expected_raw_values_to_receive+number_of_values[raw_data_send_tag] );
          tmp_view_of_expected_raw_values_to_receive.fill( value );

          view_of_expected_raw_values_to_receive =
            tmp_view_of_expected_raw_values_to_receive.toConst();

          Utility::ArrayView<T> tmp_view_of_expected_view_values_to_receive( expected_view_values_to_receive, expected_view_values_to_receive+number_of_values[view_data_send_tag] );
          tmp_view_of_expected_view_values_to_receive.fill( value );

          view_of_expected_view_values_to_receive =
            tmp_view_of_expected_view_values_to_receive.toConst();
        }
        
        std::vector<Utility::Communicator::Request> requests( 2 );
        
        // Raw data receive
        requests[raw_data_send_tag] = 
          Utility::ireceive( *comm, i, raw_data_send_tag, view_of_raw_values_to_receive );

        // View data receive
        requests[view_data_send_tag] =
          Utility::ireceive( *comm, i, view_data_send_tag, view_of_view_values_to_receive );

        std::vector<Utility::Communicator::Status> statuses( 2 );

        // Wait for all receives to complete
        Utility::wait( requests, statuses );

        FRENSIE_REQUIRE( statuses[raw_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].count(), number_of_values[raw_data_send_tag] );
        FRENSIE_CHECK_EQUAL( view_of_raw_values_to_receive,
                             view_of_expected_raw_values_to_receive );

        FRENSIE_REQUIRE( statuses[view_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].count(), number_of_values[view_data_send_tag] );
        FRENSIE_CHECK_EQUAL( view_of_view_values_to_receive,
                             view_of_expected_view_values_to_receive );
      }
    }
  }
  else
  {
    T dummy_data;
    
    FRENSIE_CHECK_THROW( Utility::isend( *comm, 0, 0, Utility::ArrayView<const T>(&dummy_data, &dummy_data+1) ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::ireceive( *comm, 0, 0, Utility::ArrayView<T>(&dummy_data, &dummy_data+1) ),
                         Utility::InvalidCommunicator );
  }
}

// Check that basic messages can be send and received for BasicNonNativeTypes (separated with previous test due to MPI bug)
// Delete and remerge BasicNativeTypes and BasicNonNativeTypes if boost MPI bug is fixed.
FRENSIE_UNIT_TEST_TEMPLATE( Communicator_Non_Native, isend_irecv_basic, BasicNonNativeTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value = initializeValue( T(), 1 );

    std::vector<int> number_of_values( {10, 8} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      T* values_to_send = new T[number_of_values[raw_data_send_tag]];
      Utility::ArrayView<T> view_of_values_to_send( values_to_send, values_to_send+number_of_values[raw_data_send_tag] );
      
      view_of_values_to_send.fill( value );

      std::vector<Utility::Communicator::Request> requests( 2 );

      // Raw data send
      requests[raw_data_send_tag] = 
        Utility::isend( *comm, 0, raw_data_send_tag, view_of_values_to_send );

      // Send all but the first and last values using a view
      requests[view_data_send_tag] = 
        Utility::isend( *comm, 0, view_data_send_tag, view_of_values_to_send( 1, number_of_values[view_data_send_tag] ) );

      std::vector<Utility::Communicator::Status> statuses( 2 );

      // Wait for all sends to complete
      Utility::wait( requests, statuses );

      FRENSIE_REQUIRE( statuses[raw_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[raw_data_send_tag].cancelled() );

      FRENSIE_REQUIRE( statuses[view_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[view_data_send_tag].cancelled() );
    }
    else
    {
      for( int i = 1; i < comm->size(); ++i )
      {
        T raw_values_to_receive[number_of_values[raw_data_send_tag]];
        Utility::ArrayView<T> view_of_raw_values_to_receive( raw_values_to_receive, raw_values_to_receive+number_of_values[raw_data_send_tag] );
        
        T view_values_to_receive[number_of_values[view_data_send_tag]];
        Utility::ArrayView<T> view_of_view_values_to_receive( view_values_to_receive, view_values_to_receive+number_of_values[view_data_send_tag] );

        T expected_raw_values_to_receive[number_of_values[raw_data_send_tag]];
        T expected_view_values_to_receive[number_of_values[view_data_send_tag]];
        Utility::ArrayView<const T> view_of_expected_raw_values_to_receive;
        Utility::ArrayView<const T> view_of_expected_view_values_to_receive;

        {
          Utility::ArrayView<T> tmp_view_of_expected_raw_values_to_receive( expected_raw_values_to_receive, expected_raw_values_to_receive+number_of_values[raw_data_send_tag] );
          tmp_view_of_expected_raw_values_to_receive.fill( value );

          view_of_expected_raw_values_to_receive =
            tmp_view_of_expected_raw_values_to_receive.toConst();

          Utility::ArrayView<T> tmp_view_of_expected_view_values_to_receive( expected_view_values_to_receive, expected_view_values_to_receive+number_of_values[view_data_send_tag] );
          tmp_view_of_expected_view_values_to_receive.fill( value );

          view_of_expected_view_values_to_receive =
            tmp_view_of_expected_view_values_to_receive.toConst();
        }
        
        std::vector<Utility::Communicator::Request> requests( 2 );
        
        // Raw data receive
        requests[raw_data_send_tag] = 
          Utility::ireceive( *comm, i, raw_data_send_tag, view_of_raw_values_to_receive );

        // View data receive
        requests[view_data_send_tag] =
          Utility::ireceive( *comm, i, view_data_send_tag, view_of_view_values_to_receive );

        std::vector<Utility::Communicator::Status> statuses( 2 );

        // Wait for all receives to complete
        Utility::wait( requests, statuses );

        FRENSIE_REQUIRE( statuses[raw_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].count(), 1 );
        FRENSIE_CHECK_EQUAL( view_of_raw_values_to_receive,
                             view_of_expected_raw_values_to_receive );

        FRENSIE_REQUIRE( statuses[view_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].count(), 1 );
        FRENSIE_CHECK_EQUAL( view_of_view_values_to_receive,
                             view_of_expected_view_values_to_receive );
      }
    }
  }
  else
  {
    T dummy_data;
    
    FRENSIE_CHECK_THROW( Utility::isend( *comm, 0, 0, Utility::ArrayView<const T>(&dummy_data, &dummy_data+1) ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::ireceive( *comm, 0, 0, Utility::ArrayView<T>(&dummy_data, &dummy_data+1) ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that sequence containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( CommunicatorHelpers, send_recv, ContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    int single_container_tag = 0;
    int multiple_containers_tag = 1;

    std::vector<int> number_of_containers( {1, 3} );
    
    if( comm->rank() > 0 )
    {
      std::vector<Container>
        containers_to_send( number_of_containers[multiple_containers_tag] );
    
      for( size_t i = 0; i < containers_to_send.size(); ++i )
        fillContainer( containers_to_send[i], comm->rank() );

      std::vector<Utility::Communicator::Request> requests( 2 );

      requests[single_container_tag] = 
        Utility::isend( *comm, 0, single_container_tag, containers_to_send.front() );
      requests[multiple_containers_tag] = 
        Utility::isend( *comm, 0, multiple_containers_tag, Utility::arrayView(containers_to_send) );

      std::vector<Utility::Communicator::Status> statuses;

      // Wait for all sends to complete
      Utility::wait( requests, statuses );

      FRENSIE_REQUIRE( statuses[single_container_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[single_container_tag].cancelled() );

      FRENSIE_REQUIRE( statuses[multiple_containers_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[multiple_containers_tag].cancelled() );
    }
    else
    {
      Container container_to_receive;
      
      std::vector<Container>
        containers_to_receive( number_of_containers[multiple_containers_tag] );

      for( int i = 1; i < comm->size(); ++i )
      {
        Container expected_container_to_receive;
        fillContainer( expected_container_to_receive, i );
        
        std::vector<Container> expected_containers_to_receive( number_of_containers[multiple_containers_tag] );

        for( size_t j = 0; j < expected_containers_to_receive.size(); ++j )
          fillContainer( expected_containers_to_receive[j], i );

        std::vector<Utility::Communicator::Request> requests( 2 );

        requests[single_container_tag] =
          Utility::ireceive( *comm, i, single_container_tag, container_to_receive );

        requests[multiple_containers_tag] =
          Utility::ireceive( *comm, i, multiple_containers_tag, Utility::arrayView(containers_to_receive) );

        std::vector<Utility::Communicator::Status> statuses( 2 );

        // Wait for all receives to complete
        Utility::wait( requests, statuses );
        
        FRENSIE_REQUIRE( statuses[single_container_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[single_container_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[single_container_tag].tag(), single_container_tag );
        FRENSIE_CHECK_EQUAL( statuses[single_container_tag].count(), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        FRENSIE_REQUIRE( statuses[multiple_containers_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[multiple_containers_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[multiple_containers_tag].tag(), multiple_containers_tag );
        // Set to check equal to 1 due to MPI bug with non-native types.
        FRENSIE_CHECK_EQUAL( statuses[multiple_containers_tag].count(), 1 );
        FRENSIE_CHECK_EQUAL( containers_to_receive,
                             expected_containers_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorIsendIrecvHelper.cpp
//---------------------------------------------------------------------------//
