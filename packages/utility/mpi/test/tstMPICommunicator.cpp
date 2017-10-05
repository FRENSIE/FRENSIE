//---------------------------------------------------------------------------//
//!
//! \file   tstMPICommunicator.cpp
//! \author Alex Robinson
//! \brief  MPI communicator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_MPICommunicator.hpp"
#include "Utility_GlobalMPISession.hpp"
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
  typedef decltype(std::tuple_cat( typename SequenceContainerList<T>::type(), typename MergeContainerLists<Types...>::SequenceList() )) SequenceList;

  typedef typename MergeSetList<T,typename MergeContainerLists<Types...>::SetList>::type SetList;

  typedef decltype(std::tuple_cat( typename MapList<T>::type(), typename MergeContainerLists<Types...>::MapList() )) MapList;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef typename SequenceContainerList<T>::type SequenceList;
  typedef typename SetList<T>::type SetList;
  typedef typename MapList<T>::type MapList;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

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
FRENSIE_UNIT_TEST( MPICommunicator, isValid )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK( comm->isValid() );
}

//---------------------------------------------------------------------------//
// Check that a mpi comm does not use MPI
FRENSIE_UNIT_TEST( MPICommunicator, isMPIUsed )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK( comm->isMPIUsed() );
}

//---------------------------------------------------------------------------//
// Check that the rank can be returned
FRENSIE_UNIT_TEST( MPICommunicator, rank )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->rank(), Utility::GlobalMPISession::rank() );
}

//---------------------------------------------------------------------------//
// Check that the size can be returned
FRENSIE_UNIT_TEST( MPICommunicator, size )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->size(), Utility::GlobalMPISession::size() );
}

//---------------------------------------------------------------------------//
// Check that a barrier can be created
FRENSIE_UNIT_TEST( MPICommunicator, barrier )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_NO_THROW( comm->barrier() );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be split
FRENSIE_UNIT_TEST( MPICommunicator, split )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // Split the comm into two sub-communicators consisting of even and odd
  // ranks
  std::shared_ptr<const Utility::Communicator> sub_comm =
    comm->split( comm->rank()%2 );

  FRENSIE_CHECK_EQUAL( sub_comm->rank(), comm->rank()/2 );
  
  if( comm->rank()%2 == 0 )
  {
    FRENSIE_CHECK_EQUAL( sub_comm->size(), (comm->size()+1)/2 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( sub_comm->size(), comm->size()/2 );
  }

  // Split the comm into two sub-communicators consisting of even and odd
  // ranks - use a custom key value (instead of the rank)
   int custom_key = (comm->rank() == 0 ? comm->size() : comm->rank());

   sub_comm = comm->split( comm->rank()%2, custom_key );

  if( comm->rank()%2 == 0 )
  {
    int expected_sub_rank =
      (comm->rank() == 0 ? (comm->size()+1)/2-1 : comm->rank()/2-1);
    
    FRENSIE_CHECK_EQUAL( sub_comm->rank(), expected_sub_rank );
    FRENSIE_CHECK_EQUAL( sub_comm->size(), (comm->size()+1)/2 );
  }
  else
  {
    FRENSIE_CHECK_EQUAL( sub_comm->rank(), comm->rank()/2 );
    FRENSIE_CHECK_EQUAL( sub_comm->size(), comm->size()/2 );
  }
}

//---------------------------------------------------------------------------//
// Check that a timer can be created
FRENSIE_UNIT_TEST( MPICommunicator, createTimer )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_CHECK( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be converted to a string
FRENSIE_UNIT_TEST( MPICommunicator, toString )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::string comm_string = Utility::toString( *comm );
  
  std::string expected_comm_string = "MPI Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( comm_string, expected_comm_string );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be placed in a stream
FRENSIE_UNIT_TEST( MPICommunicator, toStream )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::ostringstream oss;

  Utility::toStream( oss, *comm );

  std::string expected_comm_string = "MPI Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be placed in a stream
FRENSIE_UNIT_TEST( MPICommunicator, ostream_operator )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::ostringstream oss;

  oss << *comm;

  std::string expected_comm_string = "MPI Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );
}

//---------------------------------------------------------------------------//
// Check that the any source value can be returned
FRENSIE_UNIT_TEST( MPICommunicator, anySourceValue )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->anySourceValue(), boost::mpi::any_source );
}

//---------------------------------------------------------------------------//
// Check that the any tag value can be returned
FRENSIE_UNIT_TEST( MPICommunicator, anyTagValue )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_CHECK_EQUAL( comm->anyTagValue(), boost::mpi::any_tag );
}

//---------------------------------------------------------------------------//
// Check that basic messages can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, send_recv_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
    
    int tag = 0;
    int number_of_values = 10;
    
    if( comm->rank() > 0 )
    {
      std::vector<T> values_to_send( number_of_values, value );

      mpi_comm.send( 0, tag, values_to_send.data(), number_of_values );
    }
    else
    {
      std::vector<T> values_to_receive( number_of_values );
      std::vector<T> expected_values_to_receive( number_of_values, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
          mpi_comm.recv( i, tag, values_to_receive.data(), number_of_values );

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<T>( *comm_status ),
                             number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        values_to_receive.clear();
        values_to_receive.resize( number_of_values );
      }
    }
  }
}              

//---------------------------------------------------------------------------//
// Check that string messages can be sent and received
FRENSIE_UNIT_TEST( MPICommunicator, send_recv_string )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    std::string value = "Hello World";
        
    int tag = 0;
    int number_of_values = 10;
    
    if( comm->rank() > 0 )
    {
      std::vector<std::string> values_to_send( number_of_values, value );

      mpi_comm.send( 0, tag, values_to_send.data(), number_of_values );
    }
    else
    {
      std::vector<std::string> values_to_receive( number_of_values );
      std::vector<std::string> expected_values_to_receive( number_of_values, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
          mpi_comm.recv( i, tag, values_to_receive.data(), number_of_values );

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<std::string>( *comm_status ),
                             number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        values_to_receive.clear();
        values_to_receive.resize( number_of_values );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that sequence containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            send_recv_sequence_containers,
                            SequenceContainerTypes )
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
    T value;
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
        
    int tag = 0;
    
    if( comm->rank() > 0 )
    {
      Container container_to_send;
      resizeSequenceContainer( container_to_send, value );

      mpi_comm.send( 0, tag, &container_to_send, 1 );
    }
    else
    {
      Container container_to_receive;
      Container expected_container_to_receive;
      resizeSequenceContainer( expected_container_to_receive, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
          mpi_comm.recv( i, tag, &container_to_receive, 1 );

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        clearSequenceContainer( container_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that associative containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            send_recv_associative_containers,
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
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
          mpi_comm.recv( i, tag, &container_to_receive, 1 );

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        clearAssociativeContainer( container_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that basic messages can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, isend_irecv_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
    
    int tag = 0;
    int number_of_values = 10;
    
    if( comm->rank() > 0 )
    {
      std::vector<T> values_to_send( number_of_values, value );

      std::shared_ptr<Utility::CommunicatorRequest> request = 
        mpi_comm.isend( 0, tag, values_to_send.data(), number_of_values );

      FRENSIE_REQUIRE( request.get() != NULL );

      std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
        request->wait();

      FRENSIE_REQUIRE( comm_status.get() != NULL );
      FRENSIE_CHECK( !comm_status->cancelled() );
    }
    else
    {
      std::vector<T> values_to_receive( number_of_values );
      std::vector<T> expected_values_to_receive( number_of_values, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<Utility::CommunicatorRequest> request =
          mpi_comm.irecv( i, tag, values_to_receive.data(), number_of_values );
        
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          request->wait();

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<T>( *comm_status ),
                             number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        values_to_receive.clear();
        values_to_receive.resize( number_of_values );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that string messages can be sent and received
FRENSIE_UNIT_TEST( MPICommunicator, isend_irecv_string )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    std::string value = "Hello World";
        
    int tag = 0;
    int number_of_values = 10;
    
    if( comm->rank() > 0 )
    {
      std::vector<std::string> values_to_send( number_of_values, value );

      std::shared_ptr<Utility::CommunicatorRequest> request = 
        mpi_comm.isend( 0, tag, values_to_send.data(), number_of_values );

      FRENSIE_REQUIRE( request.get() != NULL );

      std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
        request->wait();

      FRENSIE_REQUIRE( comm_status.get() != NULL );
      FRENSIE_CHECK( !comm_status->cancelled() );
    }
    else
    {
      std::vector<std::string> values_to_receive( number_of_values );
      std::vector<std::string> expected_values_to_receive( number_of_values, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<Utility::CommunicatorRequest> request =
          mpi_comm.irecv( i, tag, values_to_receive.data(), number_of_values );
        
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          request->wait();

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<std::string>( *comm_status ),
                             number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        values_to_receive.clear();
        values_to_receive.resize( number_of_values );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that sequence containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            isend_irecv_sequence_containers,
                            SequenceContainerTypes )
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
    T value;
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
        
    int tag = 0;
    
    if( comm->rank() > 0 )
    {
      Container container_to_send;
      resizeSequenceContainer( container_to_send, value );

      std::shared_ptr<Utility::CommunicatorRequest> request = 
        mpi_comm.isend( 0, tag, &container_to_send, 1 );

      FRENSIE_REQUIRE( request.get() != NULL );

      std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
        request->wait();

      FRENSIE_REQUIRE( comm_status.get() != NULL );
      FRENSIE_CHECK( !comm_status->cancelled() );
    }
    else
    {
      Container container_to_receive;
      Container expected_container_to_receive;
      resizeSequenceContainer( expected_container_to_receive, value );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<Utility::CommunicatorRequest> request =
          mpi_comm.irecv( i, tag, &container_to_receive, 1 );
        
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          request->wait();

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        clearSequenceContainer( container_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that associative containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            isend_irecv_associative_containers,
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

      std::shared_ptr<Utility::CommunicatorRequest> request = 
        mpi_comm.isend( 0, tag, &container_to_send, 1 );

      FRENSIE_REQUIRE( request.get() != NULL );

      std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
        request->wait();

      FRENSIE_REQUIRE( comm_status.get() != NULL );
      FRENSIE_CHECK( !comm_status->cancelled() );
    }
    else
    {
      Container container_to_receive;
      Container expected_container_to_receive;
      fillAssociativeContainer( expected_container_to_receive );

      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<Utility::CommunicatorRequest> request =
          mpi_comm.irecv( i, tag, &container_to_receive, 1 );
        
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          request->wait();

        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );

        clearAssociativeContainer( container_to_receive );
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a blocking probe can be conducted
FRENSIE_UNIT_TEST( MPICommunicator, probe )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    if( comm->rank() > 0 )
    {
      std::vector<double> values_to_send( 10, 10.0 );

      mpi_comm.send( 0, 0, values_to_send.data(), values_to_send.size() );

      values_to_send.clear();
      values_to_send.resize( 20, 20.0 );
      
      mpi_comm.send( 0, 1, values_to_send.data(), values_to_send.size() );
    }
    else
    {
      std::vector<double> values_to_receive;

      // Probe for messages with tag 0
      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          mpi_comm.probe( i, 0 );

        FRENSIE_REQUIRE( comm_status.get() != NULL );

        values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
        comm_status =
          mpi_comm.recv( i, 0, values_to_receive.data(), values_to_receive.size() );
        
        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), 0 );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 10 );
        FRENSIE_CHECK_EQUAL( values_to_receive,
                             std::vector<double>( 10, 10.0 ) );

        values_to_receive.clear();
      }

      // Probe for messages with tag 1
      for( int i = 1; i < comm->size(); ++i )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          mpi_comm.probe( i, 1 );

        FRENSIE_REQUIRE( comm_status.get() != NULL );

        values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
        comm_status =
          mpi_comm.recv( i, 1, values_to_receive.data(), values_to_receive.size() );
        
        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), i );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), 1 );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 20 );
        FRENSIE_CHECK_EQUAL( values_to_receive,
                             std::vector<double>( 20, 20.0 ) );

        values_to_receive.clear();
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that a non-blocking probe can be conducted
FRENSIE_UNIT_TEST( MPICommunicator, iprobe )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    if( comm->rank() > 0 )
    {
      std::vector<double> values_to_send( 10, 10.0 );

      mpi_comm.send( 0, 0, values_to_send.data(), values_to_send.size() );

      values_to_send.clear();
      values_to_send.resize( 20, 20.0 );
      
      mpi_comm.send( 0, 1, values_to_send.data(), values_to_send.size() );
    }
    else
    {
      std::vector<double> values_to_receive;

      int message_count = 0;
      int source_proc = 1;
      
      // Probe for messages with tag 0
      while( message_count < comm->size() - 1 )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          mpi_comm.iprobe( source_proc, 0 );

        // A null comm status indicates that no messages have been posted
        if( !comm_status )
          continue;

        values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
        comm_status =
          mpi_comm.recv( source_proc, 0, values_to_receive.data(), values_to_receive.size() );
        
        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), source_proc );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), 0 );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 10 );
        FRENSIE_CHECK_EQUAL( values_to_receive,
                             std::vector<double>( 10, 10.0 ) );

        ++message_count;
        ++source_proc;
        values_to_receive.clear();
      }

      message_count = 0;
      source_proc = 1;

      // Probe for messages with tag 1
      while( message_count < comm->size() - 1 )
      {
        std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
          mpi_comm.probe( source_proc, 1 );

        // A null comm status indicates that no messages have been posted
        if( !comm_status )
          continue;
          
        values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
        comm_status =
          mpi_comm.recv( source_proc, 1, values_to_receive.data(), values_to_receive.size() );
        
        FRENSIE_REQUIRE( comm_status.get() != NULL );
        FRENSIE_CHECK_EQUAL( comm_status->source(), source_proc );
        FRENSIE_CHECK_EQUAL( comm_status->tag(), 1 );
        FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 20 );
        FRENSIE_CHECK_EQUAL( values_to_receive,
                             std::vector<double>( 20, 20.0 ) );

        ++message_count;
        ++source_proc;
        values_to_receive.clear();
      }
    }
  }
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, allGather_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );
  
  std::vector<T> input_values
}

//---------------------------------------------------------------------------//
// end tstMPICommunicator.cpp
//---------------------------------------------------------------------------//
