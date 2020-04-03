//---------------------------------------------------------------------------//
//!
//! \file   tstMPICommunicatorAssociativeContainer.cpp
//! \author Alex Robinson
//! \brief  MPI communicator unit tests using associative containers
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_MPICommunicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_Tuple.hpp"
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
                   std::pair<float,int>, std::tuple<float,int>,
                   std::pair<double,int>, std::tuple<double,int>,
                   std::pair<long,int>, std::tuple<long,int>,
                   std::pair<int,int>, std::tuple<int,int>,
                   std::pair<short,int>, std::tuple<short,int> > BasicTypes;

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
  typedef typename MergeSetList<T,typename MergeContainerLists<Types...>::SetList>::type SetList;

  typedef decltype(std::tuple_cat( typename MapList<T>::type(), typename MergeContainerLists<Types...>::MapList() )) MapList;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef typename SetList<T>::type SetList;
  typedef typename MapList<T>::type MapList;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef decltype(std::tuple_cat( typename MergeContainerLists<BasicTypes>::SetList(), typename MergeContainerLists<BasicTypes>::MapList() )) AssociativeContainerTypes;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
template<template<typename,typename...> class Set, typename T>
inline typename std::enable_if<std::is_same<Set<T>,std::set<T> >::value || std::is_same<Set<T>,std::unordered_set<T> >::value,void>::type
fillAssociativeContainer( Set<T>& container, int seed = 0 )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
  {
    if( std::is_same<T,char>::value || std::is_same<T,unsigned char>::value )
      container.insert( T(48+seed*size+i) );
    else
      container.insert( T(seed*size+i) );
  }
}

template<template<typename,typename,typename...> class Map, typename Key, typename T>
inline typename std::enable_if<std::is_same<Map<Key,T>,std::map<Key,T> >::value || std::is_same<Map<Key,T>,std::unordered_map<Key,T> >::value,void>::type
fillAssociativeContainer( Map<Key,T>& container, int seed = 0 )
{
  size_t size = 10;
  
  for( size_t i = 0; i < size; ++i )
  {
    std::pair<Key,T> value;
    
    if( std::is_same<Key,char>::value || std::is_same<Key,unsigned char>::value )
      value.first = Key(48+seed*size+i);
    else
      value.first = Key(seed*size+i);

    if( std::is_same<T,char>::value || std::is_same<T,unsigned char>::value )
      Utility::get<0>(value.second) = 48+seed*size+i;
    else
      Utility::get<0>(value.second) = seed*size+i;

    container.insert( value );
  }
}

template<typename Container>
inline void clearContainer( Container& container )
{ container.clear(); }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that associative containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            send_recv,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    int tag = 0;
    
    if( comm->rank() > 0 )
    {
      Container container_to_send;
      fillAssociativeContainer( container_to_send );

      mpi_comm.send( 0, tag, &container_to_send, 1 );
    }
    else
    {
      Container container_to_receive;
      Container expected_container_to_receive;
      fillAssociativeContainer( expected_container_to_receive );

      for( int i = 1; i < comm->size(); ++i )
      {
        Utility::Communicator::Status comm_status = 
          mpi_comm.recv( i, tag, &container_to_receive, 1 );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        clearContainer( container_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that associative containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            isend_irecv,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    int tag = 0;
    
    if( comm->rank() > 0 )
    {
      Container container_to_send;
      fillAssociativeContainer( container_to_send );

      Utility::Communicator::Request request = 
        mpi_comm.isend( 0, tag, &container_to_send, 1 );

      Utility::Communicator::Status comm_status = request.wait();

      FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
      FRENSIE_CHECK( !comm_status.cancelled() );
    }
    else
    {
      Container container_to_receive;
      Container expected_container_to_receive;
      fillAssociativeContainer( expected_container_to_receive );

      for( int i = 1; i < comm->size(); ++i )
      {
        Utility::Communicator::Request request = 
          mpi_comm.irecv( i, tag, &container_to_receive, 1 );

        Utility::Communicator::Status comm_status = request.wait();

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        clearContainer( container_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            allGather,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );
  
  Container container_to_send;
  fillAssociativeContainer( container_to_send, comm->rank() );

  std::vector<Container> containers_to_receive( comm->size() );
  
  FRENSIE_REQUIRE_NO_THROW( mpi_comm.allGather( &container_to_send, 1, containers_to_receive.data() ) );

  for( int i = 0; i < comm->size(); ++i )
  {
    Container expected_container;
    fillAssociativeContainer( expected_container, i );
    
    FRENSIE_CHECK_EQUAL( containers_to_receive[i], expected_container );
  }
}

//---------------------------------------------------------------------------//
// Check that an all-to-all operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            allToAll,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  std::vector<Container> data_to_send( comm->size() );

  for( size_t i = 0; i < comm->size(); ++i )
    fillAssociativeContainer( data_to_send[i], i );

  std::vector<Container> data_to_receive( data_to_send.size() );

  // Each proc will gather the values that are equal to its rank
  FRENSIE_REQUIRE_NO_THROW( mpi_comm.allToAll( data_to_send.data(), 1, data_to_receive.data() ) );

  std::vector<Container> expected_data_to_receive( data_to_send.size() );

  for( size_t i = 0; i < expected_data_to_receive.size(); ++i )
    fillAssociativeContainer( expected_data_to_receive[i], comm->rank() );

  FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a broadcast operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            broadcast,
                            AssociativeContainerTypes )
{
   FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  Container data;

  // Broadcast from proc with rank==0
  if( comm->rank() == 0 )
    fillAssociativeContainer( data, 0 );    

  FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 0 ) );

  Container expected_data;
  fillAssociativeContainer( expected_data, 0 );

  FRENSIE_CHECK_EQUAL( data, expected_data );

  if( comm->size() > 1 )
  {
    clearContainer( data );
    clearContainer( expected_data );
    
    // Broadcast from proc with rank==1
    if( comm->rank() == 1 )
      fillAssociativeContainer( data, 1 );

    FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 1 ) );

    fillAssociativeContainer( expected_data, 1 );

    FRENSIE_CHECK_EQUAL( data, expected_data );
  }
}

//---------------------------------------------------------------------------//
// Check that a gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            gather,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  Container data;
  fillAssociativeContainer( data, comm->rank() );

  // Gather on proc with rank==0
  if( comm->rank() == 0 )
  {
    std::vector<Container> gathered_data( comm->size() );
    
    FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 0 ) );

    std::vector<Container> expected_data( gathered_data.size() );

    for( size_t i = 0; i < comm->size(); ++i )
    {
      fillAssociativeContainer( expected_data[i], i );
    }
    
    FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
  }
  else
  {
    FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, Utility::NullPointer<Container>::value, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      std::vector<Container> gathered_data( comm->size() );
    
      FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 1 ) );

      std::vector<Container> expected_data( gathered_data.size() );
    
      for( size_t i = 0; i < comm->size(); ++i )
      {
        fillAssociativeContainer( expected_data[i], i );
      }
      
      FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
    }
    else
    {
      FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, Utility::NullPointer<Container>::value, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a gatherv operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            gatherv,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  std::vector<int> sizes( comm->size() ), offsets( comm->size() );

  // We want the gathered values to be contiguous on root
  for( int i = 0; i < comm->size(); ++i )
  {
    sizes[i] = i+1;

    if( i != 0 )
      offsets[i] = offsets[i-1] + sizes[i-1];
    else
      offsets[i] = 0;
  }
  
  std::vector<Container> data( comm->rank()+1 );

  for( size_t i = 0; i < data.size(); ++i )
    fillAssociativeContainer( data[i], comm->rank() );
  
  // Gather on proc with rank==0
  if( comm->rank() == 0 )
  {
    int number_of_values = 0;
    for( size_t i = 0; i < sizes.size(); ++i )
      number_of_values += sizes[i];
    
    std::vector<Container> gathered_data_advanced( number_of_values );
    std::vector<Container> gathered_data_basic( number_of_values );
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 0 ) );

    std::vector<Container> expected_data( number_of_values );

    size_t index = 0;
    for( size_t i = 0; i < comm->size(); ++i )
    {
      for( size_t j = 0; j < sizes[i]; ++j )
      {
        fillAssociativeContainer( expected_data[index], i );
        ++index;
      }
    }
    
    FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
    FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, offsets, 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, 0 ) );
  }

  if( comm->size() > 1 )
  {
    if( comm->rank() == 1 )
    {
      int number_of_values = 0;
      for( size_t i = 0; i < sizes.size(); ++i )
        number_of_values += sizes[i];
      
      std::vector<Container> gathered_data_advanced( number_of_values );
      std::vector<Container> gathered_data_basic( number_of_values );
      
      FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 1 ) );
      
      std::vector<Container> expected_data( number_of_values );
      
      size_t index = 0;
      for( size_t i = 0; i < comm->size(); ++i )
      {
        for( size_t j = 0; j < sizes[i]; ++j )
        {
          fillAssociativeContainer( expected_data[index], i );
          ++index;
        }
      }
    
      FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
      FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
    }
    else
    {
      FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, offsets, 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, 1 ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a scatter operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            scatter,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  Container scattered_data;

  // Scatter from proc with rank==0
  if( comm->rank() == 0 )
  {
    std::vector<Container> data( comm->size() );

    for( size_t i = 0; i < comm->size(); ++i )
      fillAssociativeContainer( data[i], i );
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 0 ) );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 0 ) );
  }

  Container expected_data;
  fillAssociativeContainer( expected_data, comm->rank() );

  FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  
  if( comm->size() > 1 )
  {
    clearContainer( scattered_data );

    // Scatter from proc with rank==1
    if( comm->rank() == 1 )
    {
      std::vector<Container> data( comm->size() );

      for( size_t i = 0; i < comm->size(); ++i )
        fillAssociativeContainer( data[i], i );
    
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 1 ) );
    }
    else
    {
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  }
}

//---------------------------------------------------------------------------//
// Check that a scatterv operation can be conducted. Currently broken due to implementation change in Boost 1.72. Not used in FRENSIE, so not needed to fix.
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            scatterv,
                            AssociativeContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  std::vector<int> sizes( comm->size() ), offsets( comm->size() );

  // We want the data to scatter to be contiguous
  for( int i = 0; i < comm->size(); ++i )
  {
    sizes[i] = 1;
    offsets[i] = i;
  }
  
  Container scattered_data_advanced, scattered_data_basic;

  // Scatter from proc with rank==0
  if( comm->rank() == 0 )
  {
    std::vector<Container> data( comm->size() );

    for( size_t i = 0; i < comm->size(); ++i )
      fillAssociativeContainer( data[i], i );
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, &scattered_data_advanced, 1, 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, &scattered_data_basic, 1, 0 ) );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<Container>::value, sizes, offsets, &scattered_data_advanced, 1, 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<Container>::value, sizes, &scattered_data_basic, 1, 0 ) );
  }

  Container expected_data;
  fillAssociativeContainer( expected_data, comm->rank() );

  FRENSIE_CHECK_EQUAL( scattered_data_advanced, expected_data );
  FRENSIE_CHECK_EQUAL( scattered_data_basic, expected_data );
  
  if( comm->size() > 1 )
  {
    clearContainer( scattered_data_advanced );
    clearContainer( scattered_data_basic );

    // Scatter from proc with rank==1
    if( comm->rank() == 1 )
    {
      std::vector<Container> data( comm->size() );

      for( size_t i = 0; i < comm->size(); ++i )
        fillAssociativeContainer( data[i], i );
    
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, &scattered_data_advanced, 1, 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, &scattered_data_basic, 1, 1 ) );
    }
    else
    {
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<Container>::value, sizes, offsets, &scattered_data_advanced, 1, 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<Container>::value, sizes, &scattered_data_basic, 1, 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_data_advanced, expected_data );
    FRENSIE_CHECK_EQUAL( scattered_data_basic, expected_data );
  }
}

//---------------------------------------------------------------------------//
// end tstMPICommunicatorAssociativeContainers.cpp
//---------------------------------------------------------------------------//
