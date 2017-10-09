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
  
  std::string expected_comm_string = "MPI World Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( comm_string, expected_comm_string );

  std::shared_ptr<const Utility::Communicator> sub_comm =
    comm->split( comm->rank()%2 );

  if( sub_comm->size() != comm->size() )
  {
    comm_string = Utility::toString( *sub_comm );
    
    expected_comm_string = "MPI Communicator (rank=";
    expected_comm_string += Utility::toString( sub_comm->rank() );
    expected_comm_string += ", size=";
    expected_comm_string += Utility::toString( sub_comm->size() );
    expected_comm_string += ")";
    
    FRENSIE_CHECK_EQUAL( comm_string, expected_comm_string );
  }
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be placed in a stream
FRENSIE_UNIT_TEST( MPICommunicator, toStream )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::ostringstream oss;

  Utility::toStream( oss, *comm );

  std::string expected_comm_string = "MPI World Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );

  std::shared_ptr<const Utility::Communicator> sub_comm =
    comm->split( comm->rank()%2 );

  if( sub_comm->size() != comm->size() )
  {
    oss.str( "" );
    oss.clear();
    
    Utility::toStream( oss, *sub_comm );
    
    expected_comm_string = "MPI Communicator (rank=";
    expected_comm_string += Utility::toString( sub_comm->rank() );
    expected_comm_string += ", size=";
    expected_comm_string += Utility::toString( sub_comm->size() );
    expected_comm_string += ")";
    
    FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );
  }
}

//---------------------------------------------------------------------------//
// Check that a mpi communicator can be placed in a stream
FRENSIE_UNIT_TEST( MPICommunicator, ostream_operator )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::ostringstream oss;

  oss << *comm;

  std::string expected_comm_string = "MPI World Communicator (rank=";
  expected_comm_string += Utility::toString( comm->rank() );
  expected_comm_string += ", size=";
  expected_comm_string += Utility::toString( comm->size() );
  expected_comm_string += ")";

  FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );

  std::shared_ptr<const Utility::Communicator> sub_comm =
    comm->split( comm->rank()%2 );

  if( sub_comm->size() != comm->size() )
  {  
    oss.str( "" );
    oss.clear();
    
    oss << *sub_comm;
    
    expected_comm_string = "MPI Communicator (rank=";
    expected_comm_string += Utility::toString( sub_comm->rank() );
    expected_comm_string += ", size=";
    expected_comm_string += Utility::toString( sub_comm->size() );
    expected_comm_string += ")";
    
    FRENSIE_CHECK_EQUAL( oss.str(), expected_comm_string );
  }
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

// //---------------------------------------------------------------------------//
// // Check that basic messages can be sent and received
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, send_recv_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );
  
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     T value;
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
    
//     int tag = 0;
//     int number_of_values = 10;
    
//     if( comm->rank() > 0 )
//     {
//       std::vector<T> values_to_send( number_of_values, value );

//       mpi_comm.send( 0, tag, values_to_send.data(), number_of_values );
//     }
//     else
//     {
//       std::vector<T> values_to_receive( number_of_values );
//       std::vector<T> expected_values_to_receive( number_of_values, value );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
//           mpi_comm.recv( i, tag, values_to_receive.data(), number_of_values );

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<T>( *comm_status ),
//                              number_of_values );
//         FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

//         values_to_receive.clear();
//         values_to_receive.resize( number_of_values );
//       }
//     }
//   }
// }              

// //---------------------------------------------------------------------------//
// // Check that string messages can be sent and received
// FRENSIE_UNIT_TEST( MPICommunicator, send_recv_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     std::string value = "Hello World";
        
//     int tag = 0;
//     int number_of_values = 10;
    
//     if( comm->rank() > 0 )
//     {
//       std::vector<std::string> values_to_send( number_of_values, value );

//       mpi_comm.send( 0, tag, values_to_send.data(), number_of_values );
//     }
//     else
//     {
//       std::vector<std::string> values_to_receive( number_of_values );
//       std::vector<std::string> expected_values_to_receive( number_of_values, value );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
//           mpi_comm.recv( i, tag, values_to_receive.data(), number_of_values );

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<std::string>( *comm_status ),
//                              number_of_values );
//         FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

//         values_to_receive.clear();
//         values_to_receive.resize( number_of_values );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that sequence containers can be sent and received
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             send_recv_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;
  
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     T value;
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
        
//     int tag = 0;
    
//     if( comm->rank() > 0 )
//     {
//       Container container_to_send;
//       resizeSequenceContainer( container_to_send, value );

//       mpi_comm.send( 0, tag, &container_to_send, 1 );
//     }
//     else
//     {
//       Container container_to_receive;
//       Container expected_container_to_receive;
//       resizeSequenceContainer( expected_container_to_receive, value );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
//           mpi_comm.recv( i, tag, &container_to_receive, 1 );

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
//         FRENSIE_CHECK_EQUAL( container_to_receive,
//                              expected_container_to_receive );

//         clearSequenceContainer( container_to_receive );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that associative containers can be sent and received
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             send_recv_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;
  
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     int tag = 0;
    
//     if( comm->rank() > 0 )
//     {
//       Container container_to_send;
//       fillAssociativeContainer( container_to_send );

//       mpi_comm.send( 0, tag, &container_to_send, 1 );
//     }
//     else
//     {
//       Container container_to_receive;
//       Container expected_container_to_receive;
//       fillAssociativeContainer( expected_container_to_receive );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status = 
//           mpi_comm.recv( i, tag, &container_to_receive, 1 );

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
//         FRENSIE_CHECK_EQUAL( container_to_receive,
//                              expected_container_to_receive );

//         clearAssociativeContainer( container_to_receive );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that basic messages can be sent and received
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, isend_irecv_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );
  
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     T value;
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
    
//     int tag = 0;
//     int number_of_values = 10;
    
//     if( comm->rank() > 0 )
//     {
//       std::vector<T> values_to_send( number_of_values, value );

//       std::shared_ptr<Utility::CommunicatorRequest> request = 
//         mpi_comm.isend( 0, tag, values_to_send.data(), number_of_values );

//       FRENSIE_REQUIRE( request.get() != NULL );

//       std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//         request->wait();

//       FRENSIE_REQUIRE( comm_status.get() != NULL );
//       FRENSIE_CHECK( !comm_status->cancelled() );
//     }
//     else
//     {
//       std::vector<T> values_to_receive( number_of_values );
//       std::vector<T> expected_values_to_receive( number_of_values, value );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<Utility::CommunicatorRequest> request =
//           mpi_comm.irecv( i, tag, values_to_receive.data(), number_of_values );
        
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           request->wait();

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<T>( *comm_status ),
//                              number_of_values );
//         FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

//         values_to_receive.clear();
//         values_to_receive.resize( number_of_values );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that string messages can be sent and received
// FRENSIE_UNIT_TEST( MPICommunicator, isend_irecv_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     std::string value = "Hello World";
        
//     int tag = 0;
//     int number_of_values = 10;
    
//     if( comm->rank() > 0 )
//     {
//       std::vector<std::string> values_to_send( number_of_values, value );

//       std::shared_ptr<Utility::CommunicatorRequest> request = 
//         mpi_comm.isend( 0, tag, values_to_send.data(), number_of_values );

//       FRENSIE_REQUIRE( request.get() != NULL );

//       std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//         request->wait();

//       FRENSIE_REQUIRE( comm_status.get() != NULL );
//       FRENSIE_CHECK( !comm_status->cancelled() );
//     }
//     else
//     {
//       std::vector<std::string> values_to_receive( number_of_values );
//       std::vector<std::string> expected_values_to_receive( number_of_values, value );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<Utility::CommunicatorRequest> request =
//           mpi_comm.irecv( i, tag, values_to_receive.data(), number_of_values );
        
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           request->wait();

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<std::string>( *comm_status ),
//                              number_of_values );
//         FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

//         values_to_receive.clear();
//         values_to_receive.resize( number_of_values );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that sequence containers can be sent and received
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             isend_irecv_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;
  
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     T value;
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);
        
//     int tag = 0;
    
//     if( comm->rank() > 0 )
//     {
//       Container container_to_send;
//       resizeSequenceContainer( container_to_send, value );

//       std::shared_ptr<Utility::CommunicatorRequest> request = 
//         mpi_comm.isend( 0, tag, &container_to_send, 1 );

//       FRENSIE_REQUIRE( request.get() != NULL );

//       std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//         request->wait();

//       FRENSIE_REQUIRE( comm_status.get() != NULL );
//       FRENSIE_CHECK( !comm_status->cancelled() );
//     }
//     else
//     {
//       Container container_to_receive;
//       Container expected_container_to_receive;
//       resizeSequenceContainer( expected_container_to_receive, value );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<Utility::CommunicatorRequest> request =
//           mpi_comm.irecv( i, tag, &container_to_receive, 1 );
        
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           request->wait();

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
//         FRENSIE_CHECK_EQUAL( container_to_receive,
//                              expected_container_to_receive );

//         clearSequenceContainer( container_to_receive );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that associative containers can be sent and received
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             isend_irecv_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;
  
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     int tag = 0;
    
//     if( comm->rank() > 0 )
//     {
//       Container container_to_send;
//       fillAssociativeContainer( container_to_send );

//       std::shared_ptr<Utility::CommunicatorRequest> request = 
//         mpi_comm.isend( 0, tag, &container_to_send, 1 );

//       FRENSIE_REQUIRE( request.get() != NULL );

//       std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//         request->wait();

//       FRENSIE_REQUIRE( comm_status.get() != NULL );
//       FRENSIE_CHECK( !comm_status->cancelled() );
//     }
//     else
//     {
//       Container container_to_receive;
//       Container expected_container_to_receive;
//       fillAssociativeContainer( expected_container_to_receive );

//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<Utility::CommunicatorRequest> request =
//           mpi_comm.irecv( i, tag, &container_to_receive, 1 );
        
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           request->wait();

//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), tag );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<Container>( *comm_status ), 1 );
//         FRENSIE_CHECK_EQUAL( container_to_receive,
//                              expected_container_to_receive );

//         clearAssociativeContainer( container_to_receive );
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a blocking probe can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, probe )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     if( comm->rank() > 0 )
//     {
//       std::vector<double> values_to_send( 10, 10.0 );

//       mpi_comm.send( 0, 0, values_to_send.data(), values_to_send.size() );

//       values_to_send.clear();
//       values_to_send.resize( 20, 20.0 );
      
//       mpi_comm.send( 0, 1, values_to_send.data(), values_to_send.size() );
//     }
//     else
//     {
//       std::vector<double> values_to_receive;

//       // Probe for messages with tag 0
//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           mpi_comm.probe( i, 0 );

//         FRENSIE_REQUIRE( comm_status.get() != NULL );

//         values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
//         comm_status =
//           mpi_comm.recv( i, 0, values_to_receive.data(), values_to_receive.size() );
        
//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), 0 );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 10 );
//         FRENSIE_CHECK_EQUAL( values_to_receive,
//                              std::vector<double>( 10, 10.0 ) );

//         values_to_receive.clear();
//       }

//       // Probe for messages with tag 1
//       for( int i = 1; i < comm->size(); ++i )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           mpi_comm.probe( i, 1 );

//         FRENSIE_REQUIRE( comm_status.get() != NULL );

//         values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
//         comm_status =
//           mpi_comm.recv( i, 1, values_to_receive.data(), values_to_receive.size() );
        
//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), i );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), 1 );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 20 );
//         FRENSIE_CHECK_EQUAL( values_to_receive,
//                              std::vector<double>( 20, 20.0 ) );

//         values_to_receive.clear();
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a non-blocking probe can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, iprobe )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   // These operations can only be done with comms that have at least 2 procs
//   if( comm->size() > 1 )
//   {
//     if( comm->rank() > 0 )
//     {
//       std::vector<double> values_to_send( 10, 10.0 );

//       mpi_comm.send( 0, 0, values_to_send.data(), values_to_send.size() );

//       values_to_send.clear();
//       values_to_send.resize( 20, 20.0 );
      
//       mpi_comm.send( 0, 1, values_to_send.data(), values_to_send.size() );
//     }
//     else
//     {
//       std::vector<double> values_to_receive;

//       int message_count = 0;
//       int source_proc = 1;
      
//       // Probe for messages with tag 0
//       while( message_count < comm->size() - 1 )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           mpi_comm.iprobe( source_proc, 0 );

//         // A null comm status indicates that no messages have been posted
//         if( !comm_status )
//           continue;

//         values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
//         comm_status =
//           mpi_comm.recv( source_proc, 0, values_to_receive.data(), values_to_receive.size() );
        
//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), source_proc );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), 0 );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 10 );
//         FRENSIE_CHECK_EQUAL( values_to_receive,
//                              std::vector<double>( 10, 10.0 ) );

//         ++message_count;
//         ++source_proc;
//         values_to_receive.clear();
//       }

//       message_count = 0;
//       source_proc = 1;

//       // Probe for messages with tag 1
//       while( message_count < comm->size() - 1 )
//       {
//         std::shared_ptr<const Utility::CommunicatorStatus> comm_status =
//           mpi_comm.probe( source_proc, 1 );

//         // A null comm status indicates that no messages have been posted
//         if( !comm_status )
//           continue;
          
//         values_to_receive.resize( mpi_comm.count<double>( *comm_status ) );
        
//         comm_status =
//           mpi_comm.recv( source_proc, 1, values_to_receive.data(), values_to_receive.size() );
        
//         FRENSIE_REQUIRE( comm_status.get() != NULL );
//         FRENSIE_CHECK_EQUAL( comm_status->source(), source_proc );
//         FRENSIE_CHECK_EQUAL( comm_status->tag(), 1 );
//         FRENSIE_CHECK_EQUAL( mpi_comm.count<double>( *comm_status ), 20 );
//         FRENSIE_CHECK_EQUAL( values_to_receive,
//                              std::vector<double>( 20, 20.0 ) );

//         ++message_count;
//         ++source_proc;
//         values_to_receive.clear();
//       }
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that an all gather operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, allGather_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());
  
//   std::vector<T> data_to_send( 10, value );

//   std::vector<T> data_to_receive( data_to_send.size()*comm->size() );

//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allGather( data_to_send.data(), data_to_send.size(), data_to_receive.data() ) );

//   for( size_t i = 0; i < comm->size(); ++i )
//   {
//     T value;
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
    
//     std::vector<T> expected_data( data_to_send.size(), value );

//     FRENSIE_CHECK_EQUAL( data_to_receive | Utility::Slice( i*data_to_send.size(), data_to_send.size() ),
//                          expected_data | Utility::Slice( 0, data_to_send.size() ) );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that an all gather operation can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, allGather_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<std::string> data_to_send( 10 );

//   for( size_t i = 0; i < data_to_send.size(); ++i )
//   {
//     data_to_send[i] = std::string("test element " ) +
//       Utility::toString(comm->rank()*data_to_send.size() + i);
//   }

//   std::vector<std::string> data_to_receive( data_to_send.size()*comm->size() );

//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allGather( data_to_send.data(), data_to_send.size(), data_to_receive.data() ) );

//   for( size_t i = 0; i < data_to_receive.size(); ++i )
//   {
//     FRENSIE_CHECK_EQUAL( data_to_receive[i],
//                          std::string("test element " )+Utility::toString(i) );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that an all gather operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             allGather_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );
  
//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   Container container_to_send;
//   resizeSequenceContainer( container_to_send, value );

//   std::vector<Container> containers_to_receive( comm->size() );
  
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allGather( &container_to_send, 1, containers_to_receive.data() ) );

//   for( int i = 0; i < comm->size(); ++i )
//   {
//     T expected_value;
//     Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
    
//     Container expected_container;
//     resizeSequenceContainer( expected_container, expected_value );
    
//     FRENSIE_CHECK_EQUAL( containers_to_receive[i], expected_container );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that an all gather operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             allGather_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );
  
//   Container container_to_send;
//   fillAssociativeContainer( container_to_send, comm->rank() );

//   std::vector<Container> containers_to_receive( comm->size() );
  
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allGather( &container_to_send, 1, containers_to_receive.data() ) );

//   for( int i = 0; i < comm->size(); ++i )
//   {
//     Container expected_container;
//     fillAssociativeContainer( expected_container, i );
    
//     FRENSIE_CHECK_EQUAL( containers_to_receive[i], expected_container );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that an all reduce operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MPICommunicator,
//                                    allReduce,
//                                    BasicTypeOpPairs )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );
//   FETCH_TEMPLATE_PARAM( 1, ReduceOp );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   T value = comm->rank();
  
//   std::vector<T> data_to_send( 10, value );

//   std::vector<T> data_to_receive( data_to_send.size() );

//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allReduce( data_to_send.data(), data_to_send.size(), data_to_receive.data(), ReduceOp() ) );

//   T reduced_value = 0;

//   for( int i = 0; i < comm->size()-1; ++i )
//     reduced_value = ReduceOp()( reduced_value, T(i+1) );
  
//   std::vector<T> expected_data_to_receive( data_to_send.size(), reduced_value );

//   FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
// }

// //---------------------------------------------------------------------------//
// // Check that an all-to-all operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, allToAll_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   int values_to_send_per_proc = 2;

//   std::vector<T> data_to_send( comm->size()*values_to_send_per_proc );

//   for( size_t i = 0; i < comm->size(); ++i )
//   {
//     for( size_t j = 0; j < values_to_send_per_proc; ++j )
//     {
//       Utility::get<0>( data_to_send[i*values_to_send_per_proc+j] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//     }
//   }

//   std::vector<T> data_to_receive( data_to_send.size() );

//   // Each proc will gather the values that are equal to its rank
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allToAll( data_to_send.data(), values_to_send_per_proc, data_to_receive.data() ) );

//   T expected_value;

//   Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   std::vector<T> expected_data_to_receive( data_to_send.size(), expected_value );

//   FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
// }

// //---------------------------------------------------------------------------//
// // Check that an all-to-all operation can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, allToAll_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   int values_to_send_per_proc = 2;

//   std::vector<std::string> data_to_send( comm->size()*values_to_send_per_proc );

//   for( size_t i = 0; i < comm->size(); ++i )
//   {
//     for( size_t j = 0; j < values_to_send_per_proc; ++j )
//     {
//       data_to_send[i*values_to_send_per_proc+j] = Utility::toString(i);
//     }
//   }

//   std::vector<std::string> data_to_receive( data_to_send.size() );

//   // Each proc will gather the values that are equal to its rank
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allToAll( data_to_send.data(), values_to_send_per_proc, data_to_receive.data() ) );

//   std::vector<std::string> expected_data_to_receive( data_to_send.size(), Utility::toString(comm->rank()) );

//   FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
// }

// //---------------------------------------------------------------------------//
// // Check that an all-to-all operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             allToAll_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<Container> data_to_send( comm->size() );

//   for( size_t i = 0; i < comm->size(); ++i )
//   {
//     T value;
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

//     resizeSequenceContainer( data_to_send[i], value );
//   }

//   std::vector<Container> data_to_receive( data_to_send.size() );

//   // Each proc will gather the values that are equal to its rank
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allToAll( data_to_send.data(), 1, data_to_receive.data() ) );

//   T expected_value;

//   Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   std::vector<Container> expected_data_to_receive( data_to_send.size() );

//   for( size_t i = 0; i < expected_data_to_receive.size(); ++i )
//     resizeSequenceContainer( expected_data_to_receive[i], expected_value );

//   FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
// }

// //---------------------------------------------------------------------------//
// // Check that an all-to-all operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             allToAll_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<Container> data_to_send( comm->size() );

//   for( size_t i = 0; i < comm->size(); ++i )
//     fillAssociativeContainer( data_to_send[i], i );

//   std::vector<Container> data_to_receive( data_to_send.size() );

//   // Each proc will gather the values that are equal to its rank
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.allToAll( data_to_send.data(), 1, data_to_receive.data() ) );

//   std::vector<Container> expected_data_to_receive( data_to_send.size() );

//   for( size_t i = 0; i < expected_data_to_receive.size(); ++i )
//     fillAssociativeContainer( expected_data_to_receive[i], comm->rank() );

//   FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
// }

// //---------------------------------------------------------------------------//
// // Check that a broadcast operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, broadcast_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<T> data;

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

//   // Broadcast from proc with rank==0
//   if( comm->rank() == 0 )
//     data.resize( 10, value );
//   else
//     data.resize( 10 );

//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( data.data(), data.size(), 0 ) );

//   std::vector<T> expected_data( data.size(), value );

//   FRENSIE_CHECK_EQUAL( data, expected_data );

//   if( comm->size() > 1 )
//   {
//     data.clear();
//     expected_data.clear();
    
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 50 : 2);

//     // Broadcast from proc with rank==1
//     if( comm->rank() == 1 )
//       data.resize( 10, value );
//     else
//       data.resize( 10 );

//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( data.data(), data.size(), 1 ) );

//     expected_data.resize( data.size(), value );

//     FRENSIE_CHECK_EQUAL( data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a broadcast operation can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, broadcast_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<std::string> data;

//   // Broadcast from proc with rank==0
//   if( comm->rank() == 0 )
//     data.resize( 10, "1" );
//   else
//     data.resize( 10 );

//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( data.data(), data.size(), 0 ) );

//   std::vector<std::string> expected_data( data.size(), "1" );

//   FRENSIE_CHECK_EQUAL( data, expected_data );

//   if( comm->size() > 1 )
//   {
//     data.clear();
//     expected_data.clear();
    
//     // Broadcast from proc with rank==1
//     if( comm->rank() == 1 )
//       data.resize( 10, "2" );
//     else
//       data.resize( 10 );

//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( data.data(), data.size(), 1 ) );

//     expected_data.resize( data.size(), "2" );

//     FRENSIE_CHECK_EQUAL( data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a broadcast operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             broadcast_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   Container data;

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

//   // Broadcast from proc with rank==0
//   if( comm->rank() == 0 )
//     resizeSequenceContainer( data, value );
  
//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 0 ) );

//   Container expected_data;
//   resizeSequenceContainer( expected_data, value );

//   FRENSIE_CHECK_EQUAL( data, expected_data );

//   if( comm->size() > 1 )
//   {
//     clearSequenceContainer( data );
//     clearSequenceContainer( expected_data );
    
//     Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 50 : 2);

//     // Broadcast from proc with rank==1
//     if( comm->rank() == 1 )
//       resizeSequenceContainer( data, value );
   
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 1 ) );

//     resizeSequenceContainer( expected_data, value );

//     FRENSIE_CHECK_EQUAL( data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a broadcast operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             broadcast_associative_containers,
//                             AssociativeContainerTypes )
// {
//    FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   Container data;

//   // Broadcast from proc with rank==0
//   if( comm->rank() == 0 )
//     fillAssociativeContainer( data, 0 );    

//   FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 0 ) );

//   Container expected_data;
//   fillAssociativeContainer( expected_data, 0 );

//   FRENSIE_CHECK_EQUAL( data, expected_data );

//   if( comm->size() > 1 )
//   {
//     clearAssociativeContainer( data );
//     clearAssociativeContainer( expected_data );
    
//     // Broadcast from proc with rank==1
//     if( comm->rank() == 1 )
//       fillAssociativeContainer( data, 1 );

//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 1 ) );

//     fillAssociativeContainer( expected_data, 1 );

//     FRENSIE_CHECK_EQUAL( data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gather operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, gather_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<T> data;

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   int number_of_values_per_proc = 2;

//   // Gather on proc with rank==0
//   data.resize( number_of_values_per_proc, value );

//   if( comm->rank() == 0 )
//   {
//     std::vector<T> gathered_data( number_of_values_per_proc*comm->size() );
    
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), number_of_values_per_proc, gathered_data.data(), 0 ) );

//     std::vector<T> expected_data( gathered_data.size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < number_of_values_per_proc; ++j )
//       {
//         Utility::get<0>( expected_data[i*number_of_values_per_proc+j] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//       }
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//   }
//   else
//   {
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), data.size(), Utility::NullPointer<T>::value, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       std::vector<T> gathered_data( number_of_values_per_proc*comm->size());
      
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), number_of_values_per_proc, gathered_data.data(), 1 ) );
      
//       std::vector<T> expected_data( gathered_data.size() );
      
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < number_of_values_per_proc; ++j )
//         {
//           Utility::get<0>( expected_data[i*number_of_values_per_proc+j] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//         }
//       }
      
//       FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//     }
//     else
//     {
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), data.size(), Utility::NullPointer<T>::value, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gather operation can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, gather_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<std::string> data;

//   int number_of_values_per_proc = 2;

//   // Gather on proc with rank==0
//   data.resize( number_of_values_per_proc, Utility::toString(comm->rank()) );

//   if( comm->rank() == 0 )
//   {
//     std::vector<std::string> gathered_data( number_of_values_per_proc*comm->size() );
    
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), number_of_values_per_proc, gathered_data.data(), 0 ) );

//     std::vector<std::string> expected_data( gathered_data.size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < number_of_values_per_proc; ++j )
//       {
//         expected_data[i*number_of_values_per_proc+j] = Utility::toString(i);
//       }
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//   }
//   else
//   {
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), data.size(), Utility::NullPointer<std::string>::value, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       std::vector<std::string> gathered_data( number_of_values_per_proc*comm->size());
      
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), number_of_values_per_proc, gathered_data.data(), 1 ) );
      
//       std::vector<std::string> expected_data( gathered_data.size() );
      
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < number_of_values_per_proc; ++j )
//         {
//           expected_data[i*number_of_values_per_proc+j] = Utility::toString(i);
//         }
//       }
      
//       FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//     }
//     else
//     {
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( data.data(), data.size(), Utility::NullPointer<std::string>::value, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gather operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             gather_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   Container data;
//   resizeSequenceContainer( data, value );

//   // Gather on proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     std::vector<Container> gathered_data( comm->size() );
    
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 0 ) );

//     std::vector<Container> expected_data( gathered_data.size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       T expected_value;
//       Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

//       resizeSequenceContainer( expected_data[i], expected_value );
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//   }
//   else
//   {
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, Utility::NullPointer<Container>::value, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       std::vector<Container> gathered_data( comm->size() );
    
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 1 ) );

//       std::vector<Container> expected_data( gathered_data.size() );
    
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         T expected_value;
//         Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
//         resizeSequenceContainer( expected_data[i], expected_value );
//       }
      
//       FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//     }
//     else
//     {
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, Utility::NullPointer<Container>::value, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gather operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             gather_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   Container data;
//   fillAssociativeContainer( data, comm->rank() );

//   // Gather on proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     std::vector<Container> gathered_data( comm->size() );
    
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 0 ) );

//     std::vector<Container> expected_data( gathered_data.size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       fillAssociativeContainer( expected_data[i], i );
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//   }
//   else
//   {
//     FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, Utility::NullPointer<Container>::value, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       std::vector<Container> gathered_data( comm->size() );
    
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 1 ) );

//       std::vector<Container> expected_data( gathered_data.size() );
    
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         fillAssociativeContainer( expected_data[i], i );
//       }
      
//       FRENSIE_CHECK_EQUAL( gathered_data, expected_data );
//     }
//     else
//     {
//       FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, Utility::NullPointer<Container>::value, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gatherv operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, gatherv_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<int> sizes( comm->size() ), offsets( comm->size() );

//   // We want the gathered values to be contiguous on root
//   for( int i = 0; i < comm->size(); ++i )
//   {
//     sizes[i] = i+1;

//     if( i != 0 )
//       offsets[i] = offsets[i-1] + sizes[i-1];
//     else
//       offsets[i] = 0;
//   }

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   std::vector<T> data( comm->rank()+1, value );
  
//   // Gather on proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     int number_of_values = 0;
//     for( size_t i = 0; i < sizes.size(); ++i )
//       number_of_values += sizes[i];
    
//     std::vector<T> gathered_data_advanced( number_of_values );
//     std::vector<T> gathered_data_basic( number_of_values );
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 0 ) );

//     std::vector<T> expected_data( number_of_values );

//     size_t index = 0;
//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < sizes[i]; ++j )
//       {
//         Utility::get<0>( expected_data[index] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//         ++index;
//       }
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//     FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<T>::value, sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<T>::value, sizes, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       int number_of_values = 0;
//       for( size_t i = 0; i < sizes.size(); ++i )
//         number_of_values += sizes[i];
    
//       std::vector<T> gathered_data_advanced( number_of_values );
//       std::vector<T> gathered_data_basic( number_of_values );
      
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 1 ) );
      
//       std::vector<T> expected_data( number_of_values );

//       size_t index = 0;
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < sizes[i]; ++j )
//         {
//           Utility::get<0>( expected_data[index] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//           ++index;
//         }
//       }
    
//       FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//       FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<T>::value, sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<T>::value, sizes, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gatherv operation can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, gatherv_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<int> sizes( comm->size() ), offsets( comm->size() );

//   // We want the gathered values to be contiguous on root
//   for( int i = 0; i < comm->size(); ++i )
//   {
//     sizes[i] = i+1;

//     if( i != 0 )
//       offsets[i] = offsets[i-1] + sizes[i-1];
//     else
//       offsets[i] = 0;
//   }

//   std::vector<std::string> data( comm->rank()+1, Utility::toString(comm->rank()) );
  
//   // Gather on proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     int number_of_values = 0;
//     for( size_t i = 0; i < sizes.size(); ++i )
//       number_of_values += sizes[i];
    
//     std::vector<std::string> gathered_data_advanced( number_of_values );
//     std::vector<std::string> gathered_data_basic( number_of_values );
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 0 ) );

//     std::vector<std::string> expected_data( number_of_values );

//     size_t index = 0;
//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < sizes[i]; ++j )
//       {
//         expected_data[index] = Utility::toString(i);
//         ++index;
//       }
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//     FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<std::string>::value, sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<std::string>::value, sizes, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       int number_of_values = 0;
//       for( size_t i = 0; i < sizes.size(); ++i )
//         number_of_values += sizes[i];
    
//       std::vector<std::string> gathered_data_advanced( number_of_values );
//       std::vector<std::string> gathered_data_basic( number_of_values );
      
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 1 ) );
      
//       std::vector<std::string> expected_data( number_of_values );

//       size_t index = 0;
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < sizes[i]; ++j )
//         {
//           expected_data[index] = Utility::toString(i);
//           ++index;
//         }
//       }
    
//       FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//       FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<std::string>::value, sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<std::string>::value, sizes, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gatherv operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             gatherv_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<int> sizes( comm->size() ), offsets( comm->size() );

//   // We want the gathered values to be contiguous on root
//   for( int i = 0; i < comm->size(); ++i )
//   {
//     sizes[i] = i+1;

//     if( i != 0 )
//       offsets[i] = offsets[i-1] + sizes[i-1];
//     else
//       offsets[i] = 0;
//   }

//   T value;
//   Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   std::vector<Container> data( comm->rank()+1 );

//   for( size_t i = 0; i < data.size(); ++i )
//     resizeSequenceContainer( data[i], value );
  
//   // Gather on proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     int number_of_values = 0;
//     for( size_t i = 0; i < sizes.size(); ++i )
//       number_of_values += sizes[i];
    
//     std::vector<Container> gathered_data_advanced( number_of_values );
//     std::vector<Container> gathered_data_basic( number_of_values );
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 0 ) );

//     std::vector<Container> expected_data( number_of_values );

//     size_t index = 0;
//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       T expected_value;
//         Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
//       for( size_t j = 0; j < sizes[i]; ++j )
//       {
//         resizeSequenceContainer( expected_data[index], expected_value );
//         ++index;
//       }
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//     FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       int number_of_values = 0;
//       for( size_t i = 0; i < sizes.size(); ++i )
//         number_of_values += sizes[i];
      
//       std::vector<Container> gathered_data_advanced( number_of_values );
//       std::vector<Container> gathered_data_basic( number_of_values );
      
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 1 ) );
      
//       std::vector<Container> expected_data( number_of_values );
      
//       size_t index = 0;
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         T expected_value;
//         Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
//         for( size_t j = 0; j < sizes[i]; ++j )
//         {
//           resizeSequenceContainer( expected_data[index], expected_value );
//           ++index;
//         }
//       }
    
//       FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//       FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a gatherv operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             gatherv_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   std::vector<int> sizes( comm->size() ), offsets( comm->size() );

//   // We want the gathered values to be contiguous on root
//   for( int i = 0; i < comm->size(); ++i )
//   {
//     sizes[i] = i+1;

//     if( i != 0 )
//       offsets[i] = offsets[i-1] + sizes[i-1];
//     else
//       offsets[i] = 0;
//   }
  
//   std::vector<Container> data( comm->rank()+1 );

//   for( size_t i = 0; i < data.size(); ++i )
//     fillAssociativeContainer( data[i], comm->rank() );
  
//   // Gather on proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     int number_of_values = 0;
//     for( size_t i = 0; i < sizes.size(); ++i )
//       number_of_values += sizes[i];
    
//     std::vector<Container> gathered_data_advanced( number_of_values );
//     std::vector<Container> gathered_data_basic( number_of_values );
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 0 ) );

//     std::vector<Container> expected_data( number_of_values );

//     size_t index = 0;
//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < sizes[i]; ++j )
//       {
//         fillAssociativeContainer( expected_data[index], i );
//         ++index;
//       }
//     }
    
//     FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//     FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, offsets, 0 ) );
//     FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, 0 ) );
//   }

//   if( comm->size() > 1 )
//   {
//     if( comm->rank() == 1 )
//     {
//       int number_of_values = 0;
//       for( size_t i = 0; i < sizes.size(); ++i )
//         number_of_values += sizes[i];
      
//       std::vector<Container> gathered_data_advanced( number_of_values );
//       std::vector<Container> gathered_data_basic( number_of_values );
      
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_advanced.data(), sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), gathered_data_basic.data(), sizes, 1 ) );
      
//       std::vector<Container> expected_data( number_of_values );
      
//       size_t index = 0;
//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < sizes[i]; ++j )
//         {
//           fillAssociativeContainer( expected_data[index], i );
//           ++index;
//         }
//       }
    
//       FRENSIE_CHECK_EQUAL( gathered_data_advanced, expected_data );
//       FRENSIE_CHECK_EQUAL( gathered_data_basic, expected_data );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, offsets, 1 ) );
//       FRENSIE_CHECK_NO_THROW( mpi_comm.gatherv( data.data(), data.size(), Utility::NullPointer<Container>::value, sizes, 1 ) );
//     }
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a scatter operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, scatter_basic, BasicTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, T );

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   int number_of_values_per_proc = 2;
  
//   std::vector<T> scattered_data( number_of_values_per_proc );

//   // Scatter from proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     std::vector<T> data( number_of_values_per_proc*comm->size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < number_of_values_per_proc; ++j )
//       {
//         Utility::get<0>( data[i*number_of_values_per_proc+j] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//       }
//     }
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), scattered_data.data(), number_of_values_per_proc, 0 ) );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<T>::value, scattered_data.data(), number_of_values_per_proc, 0 ) );
//   }

//   T expected_value;
//   Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   std::vector<T> expected_data( scattered_data.size(), expected_value );

//   FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  
//   if( comm->size() > 1 )
//   {
//     scattered_data.clear();
//     scattered_data.resize( number_of_values_per_proc );

//     // Scatter from proc with rank==1
//     if( comm->rank() == 1 )
//     {
//       std::vector<T> data( number_of_values_per_proc*comm->size() );

//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < number_of_values_per_proc; ++j )
//         {
//           Utility::get<0>( data[i*number_of_values_per_proc+j] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
//         }
//       }
    
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), scattered_data.data(), number_of_values_per_proc, 1 ) );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<T>::value, scattered_data.data(), number_of_values_per_proc, 1 ) );
//     }

//     FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a scatter operation can be conducted
// FRENSIE_UNIT_TEST( MPICommunicator, scatter_string )
// {
//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   int number_of_values_per_proc = 2;
  
//   std::vector<std::string> scattered_data( number_of_values_per_proc );

//   // Scatter from proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     std::vector<std::string> data( number_of_values_per_proc*comm->size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       for( size_t j = 0; j < number_of_values_per_proc; ++j )
//       {
//         data[i*number_of_values_per_proc+j] = Utility::toString(i);
//       }
//     }
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), scattered_data.data(), number_of_values_per_proc, 0 ) );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<std::string>::value, scattered_data.data(), number_of_values_per_proc, 0 ) );
//   }

//   std::vector<std::string>
//     expected_data( scattered_data.size(), Utility::toString(comm->rank()) );

//   FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  
//   if( comm->size() > 1 )
//   {
//     scattered_data.clear();
//     scattered_data.resize( number_of_values_per_proc );

//     // Scatter from proc with rank==1
//     if( comm->rank() == 1 )
//     {
//       std::vector<std::string> data( number_of_values_per_proc*comm->size() );

//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         for( size_t j = 0; j < number_of_values_per_proc; ++j )
//         {
//           data[i*number_of_values_per_proc+j] = Utility::toString(i);
//         }
//       }
    
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), scattered_data.data(), number_of_values_per_proc, 1 ) );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<std::string>::value, scattered_data.data(), number_of_values_per_proc, 1 ) );
//     }

//     FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a scatter operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             scatter_sequence_containers,
//                             SequenceContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   Container scattered_data;

//   // Scatter from proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     std::vector<Container> data( comm->size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//     {
//       T value;
//       Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

//       resizeSequenceContainer( data[i], value );
//     }
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 0 ) );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 0 ) );
//   }

//   T expected_value;
//   Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

//   Container expected_data;
//   resizeSequenceContainer( expected_data, expected_value );

//   FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  
//   if( comm->size() > 1 )
//   {
//     clearSequenceContainer( scattered_data );

//     // Scatter from proc with rank==1
//     if( comm->rank() == 1 )
//     {
//       std::vector<Container> data( comm->size() );

//       for( size_t i = 0; i < comm->size(); ++i )
//       {
//         T value;
//         Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
//         resizeSequenceContainer( data[i], value );
//       }
    
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 1 ) );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 1 ) );
//     }

//     FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
//   }
// }

// //---------------------------------------------------------------------------//
// // Check that a scatter operation can be conducted
// FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
//                             scatter_associative_containers,
//                             AssociativeContainerTypes )
// {
//   FETCH_TEMPLATE_PARAM( 0, Container );

//   typedef typename Container::value_type T;

//   std::shared_ptr<const Utility::Communicator> comm =
//     Utility::Communicator::getDefault();

//   const Utility::MPICommunicator& mpi_comm =
//     dynamic_cast<const Utility::MPICommunicator&>( *comm );

//   Container scattered_data;

//   // Scatter from proc with rank==0
//   if( comm->rank() == 0 )
//   {
//     std::vector<Container> data( comm->size() );

//     for( size_t i = 0; i < comm->size(); ++i )
//       fillAssociativeContainer( data[i], i );
    
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 0 ) );
//   }
//   else
//   {
//     FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 0 ) );
//   }

//   Container expected_data;
//   fillAssociativeContainer( expected_data, comm->rank() );

//   FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  
//   if( comm->size() > 1 )
//   {
//     clearSequenceContainer( scattered_data );

//     // Scatter from proc with rank==1
//     if( comm->rank() == 1 )
//     {
//       std::vector<Container> data( comm->size() );

//       for( size_t i = 0; i < comm->size(); ++i )
//         fillAssociativeContainer( data[i], i );
    
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 1 ) );
//     }
//     else
//     {
//       FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 1 ) );
//     }

//     FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
//   }
// }

//---------------------------------------------------------------------------//
// Check that a scatterv operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator, scatterv_basic, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  std::vector<int> sizes( comm->size() ), offsets( comm->size() );

  // We want the data to scatter to be contiguous
  for( int i = 0; i < comm->size(); ++i )
  {
    sizes[i] = i+1;

    if( i != 0 )
      offsets[i] = offsets[i-1] + sizes[i-1];
    else
      offsets[i] = 0;
  }
  
  std::vector<T> scattered_data_advanced( sizes[comm->rank()] );
  std::vector<T> scattered_data_basic( sizes[comm->rank()] );

  // Scatter from proc with rank==0
  if( comm->rank() == 0 )
  {
    int number_of_values = 0;
    for( size_t i = 0; i < sizes.size(); ++i )
      number_of_values += sizes[i];
    
    std::vector<T> data( number_of_values );

    size_t index = 0;
    for( size_t i = 0; i < comm->size(); ++i )
    {
      for( size_t j = 0; j < sizes[i]; ++j )
      {
        Utility::get<0>( data[index] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        ++index;
      }
    }
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, scattered_data_basic.data(), scattered_data_basic.size(), 0 ) );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<T>::value, sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<T>::value, sizes, scattered_data_basic.data(), scattered_data_basic.size(), 0 ) );
  }

  T expected_value;
  Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  std::vector<T> expected_data( scattered_data_basic.size(), expected_value );

  FRENSIE_CHECK_EQUAL( scattered_data_advanced, expected_data );
  FRENSIE_CHECK_EQUAL( scattered_data_basic, expected_data );
  
  if( comm->size() > 1 )
  {
    scattered_data_advanced.clear();
    scattered_data_advanced.resize( sizes[comm->rank()] );
    
    scattered_data_basic.clear();
    scattered_data_basic.resize( sizes[comm->rank()] );

    // Scatter from proc with rank==1
    if( comm->rank() == 1 )
    {
      int number_of_values = 0;
      for( size_t i = 0; i < sizes.size(); ++i )
        number_of_values += sizes[i];
      
      std::vector<T> data( number_of_values );
      
      size_t index = 0;
      for( size_t i = 0; i < comm->size(); ++i )
      {
        for( size_t j = 0; j < sizes[i]; ++j )
        {
          Utility::get<0>( data[index] ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
          ++index;
        }
      }
    
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, scattered_data_basic.data(), scattered_data_basic.size(), 1 ) );
    }
    else
    {
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<T>::value, sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<T>::value, sizes, scattered_data_basic.data(), scattered_data_basic.size(), 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_data_advanced, expected_data );
    FRENSIE_CHECK_EQUAL( scattered_data_basic, expected_data );
  }
}

//---------------------------------------------------------------------------//
// Check that a scatterv operation can be conducted
FRENSIE_UNIT_TEST( MPICommunicator, scatterv_string )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  std::vector<int> sizes( comm->size() ), offsets( comm->size() );

  // We want the data to scatter to be contiguous
  for( int i = 0; i < comm->size(); ++i )
  {
    sizes[i] = i+1;

    if( i != 0 )
      offsets[i] = offsets[i-1] + sizes[i-1];
    else
      offsets[i] = 0;
  }
  
  std::vector<std::string> scattered_data_advanced( sizes[comm->rank()] );
  std::vector<std::string> scattered_data_basic( sizes[comm->rank()] );

  // Scatter from proc with rank==0
  if( comm->rank() == 0 )
  {
    int number_of_values = 0;
    for( size_t i = 0; i < sizes.size(); ++i )
      number_of_values += sizes[i];
    
    std::vector<std::string> data( number_of_values );

    size_t index = 0;
    for( size_t i = 0; i < comm->size(); ++i )
    {
      for( size_t j = 0; j < sizes[i]; ++j )
      {
        data[index] = Utility::toString(i);
        ++index;
      }
    }
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, scattered_data_basic.data(), scattered_data_basic.size(), 0 ) );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<std::string>::value, sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<std::string>::value, sizes, scattered_data_basic.data(), scattered_data_basic.size(), 0 ) );
  }

  std::vector<std::string> expected_data( scattered_data_basic.size(), Utility::toString(comm->rank()) );

  FRENSIE_CHECK_EQUAL( scattered_data_advanced, expected_data );
  FRENSIE_CHECK_EQUAL( scattered_data_basic, expected_data );
  
  if( comm->size() > 1 )
  {
    scattered_data_advanced.clear();
    scattered_data_advanced.resize( sizes[comm->rank()] );
    
    scattered_data_basic.clear();
    scattered_data_basic.resize( sizes[comm->rank()] );

    // Scatter from proc with rank==1
    if( comm->rank() == 1 )
    {
      int number_of_values = 0;
      for( size_t i = 0; i < sizes.size(); ++i )
        number_of_values += sizes[i];
      
      std::vector<std::string> data( number_of_values );
      
      size_t index = 0;
      for( size_t i = 0; i < comm->size(); ++i )
      {
        for( size_t j = 0; j < sizes[i]; ++j )
        {
          data[index] = Utility::toString(i);
          ++index;
        }
      }
    
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, scattered_data_basic.data(), scattered_data_basic.size(), 1 ) );
    }
    else
    {
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<std::string>::value, sizes, offsets, scattered_data_advanced.data(), scattered_data_advanced.size(), 1 ) );
      FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<std::string>::value, sizes, scattered_data_basic.data(), scattered_data_basic.size(), 1 ) );
    }

    FRENSIE_CHECK_EQUAL( scattered_data_advanced, expected_data );
    FRENSIE_CHECK_EQUAL( scattered_data_basic, expected_data );
  }
}

//---------------------------------------------------------------------------//
// end tstMPICommunicator.cpp
//---------------------------------------------------------------------------//
