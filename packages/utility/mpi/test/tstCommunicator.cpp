//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicator.cpp
//! \author Alex Robinson
//! \brief  Communicator unit tests
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


template<typename... Types>
struct MergeContainerLists;

template<typename T, typename... Types>
struct MergeContainerLists<T,Types...>
{
  typedef typename MergeTypeOpPairList<T,typename MergeContainerLists<Types...>::TypeOpPairList>::type TypeOpPairList;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef typename TypeOpPairList<T>::type TypeOpPairList;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef typename MergeContainerLists<BasicTypes>::TypeOpPairList BasicTypeOpPairs;

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
template<typename T>
inline void initializeValue( T& value, int i )
{ value = T(i); }

inline void initializeValue( char& value, int i )
{ value = 48+i; }

inline void initializeValue( unsigned char& value, int i )
{ value = 48+i; }

inline void initializeValue( std::string& value, int i )
{ value = Utility::toString(i); }

template<typename T1, typename T2>
inline void initializeValue( std::pair<T1,T2>& value, int i )
{
  initializeValue( value.first, i );
  initializeValue( value.second, i );
}

template<typename... Types>
inline void initializeValue( std::tuple<Types...>& value, int i )
{
  initializeValue( Utility::get<0>( value ), i );
  initializeValue( Utility::get<1>( value ), i );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the default communicator can be created
FRENSIE_UNIT_TEST( Communicator, getDefault )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  FRENSIE_REQUIRE( comm.get() != NULL );
  FRENSIE_REQUIRE( comm->isValid() );
  FRENSIE_REQUIRE( *comm );
  FRENSIE_CHECK_EQUAL( comm->rank(), Utility::GlobalMPISession::rank() );
  FRENSIE_CHECK_EQUAL( comm->size(), Utility::GlobalMPISession::size() );
  FRENSIE_CHECK_EQUAL( comm->isMPIUsed(), Utility::GlobalMPISession::isMPIUsed() );

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_REQUIRE( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the null communicator can be created
FRENSIE_UNIT_TEST( Communicator, getNull )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getNull();

  FRENSIE_REQUIRE( comm.get() != NULL );
  FRENSIE_REQUIRE( !comm->isValid() );
  FRENSIE_REQUIRE( !(*comm) );
  FRENSIE_REQUIRE( !comm->isMPIUsed() );

  std::shared_ptr<Utility::Timer> timer = comm->createTimer();

  FRENSIE_REQUIRE( timer.get() != NULL );
}

//---------------------------------------------------------------------------//
// Check that basic messages can be send and received
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, send_recv, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );
    
    std::vector<int> number_of_values( {10, 8, 4, 1} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    int init_list_data_send_tag = 2;
    int vector_data_send_tag = 3;
    
    if( comm->rank() > 0 )
    {
      std::vector<T>
        values_to_send( number_of_values[raw_data_send_tag], value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), number_of_values[raw_data_send_tag] );

      // Send all but the first and last values using a view 
      Utility::send( *comm, 0, view_data_send_tag, values_to_send | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

      // Send data using an initializer list temporary 
      Utility::send<T>( *comm, 0, init_list_data_send_tag, {value,value,value,value} );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      for( int i = 1; i < comm->size(); ++i )
      {
        // Raw data receive 
        std::vector<T>
          values_to_receive( number_of_values[raw_data_send_tag] );
        std::vector<T>
          expected_values_to_receive( values_to_receive.size(), value );

        Utility::Communicator::Status comm_status = 
          Utility::receive( *comm, i, raw_data_send_tag, values_to_receive.data(), number_of_values[raw_data_send_tag] );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        // View data receive
        values_to_receive.clear();
        values_to_receive.resize( number_of_values[raw_data_send_tag] );
        expected_values_to_receive.front() = T();
        expected_values_to_receive.back() = T();

        comm_status = Utility::receive( *comm, i, view_data_send_tag, values_to_receive | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        // Initializer list temporary receive
        values_to_receive.clear();
        values_to_receive.resize( number_of_values[init_list_data_send_tag] );
        expected_values_to_receive.clear();
        expected_values_to_receive.resize( values_to_receive.size(), value );

        comm_status = Utility::receive( *comm, i, init_list_data_send_tag, values_to_receive.data(), number_of_values[init_list_data_send_tag] );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), init_list_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        // Vector receive
        values_to_receive.clear();
        expected_values_to_receive.clear();
        expected_values_to_receive.resize( number_of_values[raw_data_send_tag], value );

        comm_status = Utility::receive( *comm, i, vector_data_send_tag, values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );
      }
    }
  }
  else
  {
    std::vector<T> dummy_values;
    
    FRENSIE_CHECK_THROW( Utility::send( *comm, 0, 0, dummy_values ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::receive( *comm, 0, 0, dummy_values ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that basic messages can be send and received
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, isend_irecv, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    std::vector<int> number_of_values( {10, 8, 1} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    int vector_data_send_tag = 2;
    
    if( comm->rank() > 0 )
    {
      std::vector<T>
        values_to_send( number_of_values[raw_data_send_tag], value );

      std::vector<Utility::Communicator::Request> requests( 3 );

      // Raw data send
      requests[raw_data_send_tag] = 
        Utility::isend( *comm, 0, raw_data_send_tag, values_to_send.data(), number_of_values[raw_data_send_tag] );

      // Send all but the first and last values using a view
      requests[view_data_send_tag] = 
        Utility::isend( *comm, 0, view_data_send_tag, values_to_send | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

      // Send the vector of data directly
      requests[vector_data_send_tag] = 
        Utility::isend( *comm, 0, vector_data_send_tag, values_to_send );

      std::vector<Utility::Communicator::Status> statuses( 3 );
      
      Utility::wait( requests, statuses );

      FRENSIE_REQUIRE( statuses[raw_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[raw_data_send_tag].cancelled() );

      FRENSIE_REQUIRE( statuses[view_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[view_data_send_tag].cancelled() );

      FRENSIE_REQUIRE( statuses[vector_data_send_tag].hasMessageDetails() );
      FRENSIE_CHECK( !statuses[vector_data_send_tag].cancelled() );
    }
    else
    {
      for( int i = 1; i < comm->size(); ++i )
      {
        std::vector<std::vector<T> > values_to_receive( 3 );
        std::vector<Utility::Communicator::Request> requests( 3 );
        
        // Raw data receive
        values_to_receive[raw_data_send_tag].resize( number_of_values[raw_data_send_tag] );
        
        requests[raw_data_send_tag] = 
          Utility::ireceive( *comm, i, raw_data_send_tag, values_to_receive[raw_data_send_tag].data(), values_to_receive[raw_data_send_tag].size() );

        // View data receive
        values_to_receive[view_data_send_tag].resize( number_of_values[raw_data_send_tag] );

        requests[view_data_send_tag] =
          Utility::ireceive( *comm, i, view_data_send_tag, values_to_receive[view_data_send_tag] | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

        // Vector data receive
        requests[vector_data_send_tag] =
          Utility::ireceive( *comm, i, vector_data_send_tag, values_to_receive[vector_data_send_tag] );

        std::vector<Utility::Communicator::Status> statuses( 3 );
      
        Utility::wait( requests, statuses );

        FRENSIE_REQUIRE( statuses[raw_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[raw_data_send_tag].count(), number_of_values[raw_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive[raw_data_send_tag], std::vector<T>( number_of_values[raw_data_send_tag], value ) );

        FRENSIE_REQUIRE( statuses[view_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[view_data_send_tag].count(), number_of_values[view_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive[view_data_send_tag].front(), T() );
        FRENSIE_CHECK_EQUAL( values_to_receive[view_data_send_tag].back(), T() );
        FRENSIE_CHECK_EQUAL( values_to_receive[view_data_send_tag] | Utility::Slice( 1, number_of_values[view_data_send_tag] ),
                             Utility::arrayView( std::vector<T>( number_of_values[view_data_send_tag], value ) ) );

        FRENSIE_REQUIRE( statuses[vector_data_send_tag].hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( statuses[vector_data_send_tag].source(), i );
        FRENSIE_CHECK_EQUAL( statuses[vector_data_send_tag].tag(), vector_data_send_tag );
        FRENSIE_CHECK_EQUAL( statuses[vector_data_send_tag].count(), 1 );
        FRENSIE_CHECK_EQUAL( values_to_receive[vector_data_send_tag], std::vector<T>( number_of_values[raw_data_send_tag], value ) );
      }
    }
  }
  else
  {
    std::vector<T> dummy_values;
    
    FRENSIE_CHECK_THROW( Utility::isend( *comm, 0, 0, dummy_values ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::ireceive( *comm, 0, 0, dummy_values ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, probe, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    std::vector<int> number_of_values( {10, 8, 4, 1} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    int init_list_data_send_tag = 2;
    int vector_data_send_tag = 3;
    
    if( comm->rank() > 0 )
    {
      std::vector<T>
        values_to_send( number_of_values[raw_data_send_tag], value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), number_of_values[raw_data_send_tag] );

      // Send all but the first and last values using a view 
      Utility::send( *comm, 0, view_data_send_tag, values_to_send | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

      // Send data using an initializer list temporary 
      Utility::send<T>( *comm, 0, init_list_data_send_tag, {value,value,value,value} );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      for( int i = 1; i < comm->size(); ++i )
      {
        // Raw data receive
        Utility::Communicator::Status comm_status =
          Utility::probe<T>( *comm, i, raw_data_send_tag );

        std::vector<T> values_to_receive;

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
          
          values_to_receive.resize( comm_status.count() );
        }
        else
        {
          values_to_receive.resize( number_of_values[raw_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, i, raw_data_send_tag, values_to_receive.data(), values_to_receive.size() );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[raw_data_send_tag], value ) );

        // View data receive
        values_to_receive.clear();
        values_to_receive.resize( number_of_values[raw_data_send_tag] );

        Utility::ArrayView<T> view_of_values_to_receive;
        
        comm_status = Utility::probe<T>( *comm, i, view_data_send_tag );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );

          view_of_values_to_receive =
            Utility::ArrayView<T>( values_to_receive.data()+1,
                                   values_to_receive.data()+1+comm_status.count() );
        }
        else
        {
          view_of_values_to_receive =
            Utility::ArrayView<T>( values_to_receive.data()+1,
                                   values_to_receive.data()+1+number_of_values[view_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, i, view_data_send_tag, view_of_values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive.front(), T() );
        FRENSIE_CHECK_EQUAL( values_to_receive.back(), T() );
        FRENSIE_CHECK_EQUAL( view_of_values_to_receive,
                             Utility::arrayView( std::vector<T>( number_of_values[view_data_send_tag], value ) ) );
        

        // Initializer list temporary receive
        values_to_receive.clear();
        
        comm_status = Utility::probe<T>( *comm, i, init_list_data_send_tag );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        
          values_to_receive.resize( comm_status.count() );
        }
        else
        {
          values_to_receive.resize( number_of_values[init_list_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, i, init_list_data_send_tag, values_to_receive.data(), number_of_values[init_list_data_send_tag] );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), init_list_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[init_list_data_send_tag], value ) );

        // Vector receive
        // Note: When probing for a std::vector message the status will not
        //       have a count that reflects the number of vectors sent (due
        //       to the implementation of send, which internally conducts
        //       multiple mpi send ops).
        comm_status =
          Utility::probe<std::vector<T> >( *comm, i, vector_data_send_tag );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        
        values_to_receive.clear();
        
        comm_status = Utility::receive( *comm, i, vector_data_send_tag, values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[raw_data_send_tag], value ) );
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::probe<T>( *comm, 0, 0 ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::probe<std::vector<T> >( *comm, 0, 0 ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, probe_any_source, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    int number_of_values = 10;
    int raw_data_send_tag = 0;
    int vector_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      std::vector<T>
        values_to_send( number_of_values, value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), values_to_send.size() );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      // Raw data receive from any source
      int number_of_messages_received = 0;

      while( number_of_messages_received < comm->size()-1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::probe<T>( *comm, raw_data_send_tag );

        std::vector<T> values_to_receive;

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values );
        
          values_to_receive.resize( comm_status.count() );
        }
        else
          values_to_receive.resize( number_of_values );

        comm_status = Utility::receive( *comm, comm_status.source(), raw_data_send_tag, values_to_receive.data(), values_to_receive.size() );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values );
        FRENSIE_CHECK_EQUAL( values_to_receive,
                             std::vector<T>( number_of_values, value ) );

        ++number_of_messages_received;
      }

      // Vector data receive from any source
      number_of_messages_received = 0;

      while( number_of_messages_received < comm->size()-1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::probe<std::vector<T> >( *comm, vector_data_send_tag );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        
        std::vector<T> values_to_receive;
        
        comm_status = Utility::receive( *comm, comm_status.source(), vector_data_send_tag, values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( values_to_receive,
                             std::vector<T>( number_of_values, value ) );

        ++number_of_messages_received;
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::probe<T>( *comm, 0 ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::probe<std::vector<T> >( *comm, 0 ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, probe_any_source_any_tag, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    int number_of_values = 10;
    int raw_data_send_tag = 0;
    int vector_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      std::vector<T> values_to_send( number_of_values, value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), values_to_send.size() );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      // Raw data receive from any source with any tag
      int number_of_messages_received = 0;

      while( number_of_messages_received < 2*(comm->size()-1) )
      {
        Utility::Communicator::Status comm_status =
          Utility::probe<T>( *comm );

        std::vector<T> values_to_receive;

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK( comm_status.tag() == raw_data_send_tag ||
                       comm_status.tag() == vector_data_send_tag );

        if( comm_status.tag() == raw_data_send_tag )
        {
          if( std::is_arithmetic<T>::value )
          {
            FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values );
        
            values_to_receive.resize( comm_status.count() );
          }
          else
            values_to_receive.resize( number_of_values );

          comm_status = Utility::receive( *comm, comm_status.source(), raw_data_send_tag, values_to_receive.data(), values_to_receive.size() );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
          FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
          FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values );
          FRENSIE_CHECK_EQUAL( values_to_receive,
                               std::vector<T>( number_of_values, value ) );
        }
        else
        {
          comm_status = Utility::receive( *comm, comm_status.source(), vector_data_send_tag, values_to_receive );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
          FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
          FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
          FRENSIE_CHECK_EQUAL( values_to_receive,
                               std::vector<T>( number_of_values, value ) );
        }
        
        ++number_of_messages_received;
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::probe<T>( *comm ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::probe<std::vector<T> >( *comm ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a non-blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, iprobe, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    std::vector<int> number_of_values( {10, 8, 4, 1} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    int init_list_data_send_tag = 2;
    int vector_data_send_tag = 3;
    
    if( comm->rank() > 0 )
    {
      std::vector<T>
        values_to_send( number_of_values[raw_data_send_tag], value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), number_of_values[raw_data_send_tag] );

      // Send all but the first and last values using a view 
      Utility::send( *comm, 0, view_data_send_tag, values_to_send | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

      // Send data using an initializer list temporary 
      Utility::send<T>( *comm, 0, init_list_data_send_tag, {value,value,value,value} );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      std::vector<T> values_to_receive;

      int message_count = 0;
      int source_proc = 1;

      // Raw data receive
      while( message_count < comm->size() - 1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm, source_proc, raw_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_EQUAL( comm_status.source(), source_proc );
        
        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
          
          values_to_receive.resize( comm_status.count() );
        }
        else
        {
          values_to_receive.resize( number_of_values[raw_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, source_proc, raw_data_send_tag, values_to_receive.data(), values_to_receive.size() );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), source_proc );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[raw_data_send_tag], value ) );

        ++message_count;
        ++source_proc;
        values_to_receive.clear();
      }

      message_count = 0;
      source_proc = 1;

      // View data receive
      while( message_count < comm->size() - 1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm, source_proc, view_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_EQUAL( comm_status.source(), source_proc );
        
        values_to_receive.resize( number_of_values[raw_data_send_tag] );

        Utility::ArrayView<T> view_of_values_to_receive;
        
        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );

          view_of_values_to_receive =
            Utility::ArrayView<T>( values_to_receive.data()+1,
                                   values_to_receive.data()+1+comm_status.count() );
        }
        else
        {
          view_of_values_to_receive =
            Utility::ArrayView<T>( values_to_receive.data()+1,
                                   values_to_receive.data()+1+number_of_values[view_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, source_proc, view_data_send_tag, view_of_values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), source_proc );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive.front(), T() );
        FRENSIE_CHECK_EQUAL( values_to_receive.back(), T() );
        FRENSIE_CHECK_EQUAL( view_of_values_to_receive,
                             Utility::arrayView( std::vector<T>( number_of_values[view_data_send_tag], value ) ) );

        ++message_count;
        ++source_proc;
        values_to_receive.clear();
      }

      message_count = 0;
      source_proc = 1;

      // Initializer list temporary receive
      while( message_count < comm->size() - 1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm, source_proc, init_list_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_EQUAL( comm_status.source(), source_proc );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        
          values_to_receive.resize( comm_status.count() );
        }
        else
        {
          values_to_receive.resize( number_of_values[init_list_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, source_proc, init_list_data_send_tag, values_to_receive.data(), number_of_values[init_list_data_send_tag] );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), source_proc );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), init_list_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[init_list_data_send_tag], value ) );

        ++message_count;
        ++source_proc;
        values_to_receive.clear();
      }

      message_count = 0;
      source_proc = 1;

      // Vector receive
      while( message_count < comm->size()-1 )
      {
        // Note: When probing for a std::vector message the status will not
        //       have a count that reflects the number of vectors sent (due
        //       to the implementation of send, which internally conducts
        //       multiple mpi send ops).
        Utility::Communicator::Status comm_status =
          Utility::iprobe<std::vector<T> >( *comm, source_proc, vector_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_EQUAL( comm_status.source(), source_proc );
        
        comm_status = Utility::receive( *comm, source_proc, vector_data_send_tag, values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), source_proc );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[raw_data_send_tag], value ) );

        ++message_count;
        ++source_proc;
        values_to_receive.clear();
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::iprobe<T>( *comm, 0, 0 ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::iprobe<std::vector<T> >( *comm, 0, 0 ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a non-blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, iprobe_any_source, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    std::vector<int> number_of_values( {10, 8, 4, 1} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    int init_list_data_send_tag = 2;
    int vector_data_send_tag = 3;
    
    if( comm->rank() > 0 )
    {
      std::vector<T>
        values_to_send( number_of_values[raw_data_send_tag], value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), number_of_values[raw_data_send_tag] );

      // Send all but the first and last values using a view 
      Utility::send( *comm, 0, view_data_send_tag, values_to_send | Utility::Slice( 1, number_of_values[view_data_send_tag] ) );

      // Send data using an initializer list temporary 
      Utility::send<T>( *comm, 0, init_list_data_send_tag, {value,value,value,value} );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      std::vector<T> values_to_receive;

      int message_count = 0;
      
      // Raw data receive
      while( message_count < comm->size() - 1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm, raw_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_GREATER( comm_status.source(), 0 );
        FRENSIE_REQUIRE_LESS( comm_status.source(), comm->size() );
        
        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
          
          values_to_receive.resize( comm_status.count() );
        }
        else
        {
          values_to_receive.resize( number_of_values[raw_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, comm_status.source(), raw_data_send_tag, values_to_receive.data(), values_to_receive.size() );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[raw_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[raw_data_send_tag], value ) );

        ++message_count;
        values_to_receive.clear();
      }

      message_count = 0;

      // View data receive
      while( message_count < comm->size() - 1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm, view_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_GREATER( comm_status.source(), 0 );
        FRENSIE_REQUIRE_LESS( comm_status.source(), comm->size() );
        
        values_to_receive.resize( number_of_values[raw_data_send_tag] );

        Utility::ArrayView<T> view_of_values_to_receive;
        
        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );

          view_of_values_to_receive =
            Utility::ArrayView<T>( values_to_receive.data()+1,
                                   values_to_receive.data()+1+comm_status.count() );
        }
        else
        {
          view_of_values_to_receive =
            Utility::ArrayView<T>( values_to_receive.data()+1,
                                   values_to_receive.data()+1+number_of_values[view_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, comm_status.source(), view_data_send_tag, view_of_values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), view_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[view_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive.front(), T() );
        FRENSIE_CHECK_EQUAL( values_to_receive.back(), T() );
        FRENSIE_CHECK_EQUAL( view_of_values_to_receive,
                             Utility::arrayView( std::vector<T>( number_of_values[view_data_send_tag], value ) ) );

        ++message_count;
        values_to_receive.clear();
      }

      message_count = 0;
      
      // Initializer list temporary receive
      while( message_count < comm->size() - 1 )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm, init_list_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_GREATER( comm_status.source(), 0 );
        FRENSIE_REQUIRE_LESS( comm_status.source(), comm->size() );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        
          values_to_receive.resize( comm_status.count() );
        }
        else
        {
          values_to_receive.resize( number_of_values[init_list_data_send_tag] );
        }
        
        comm_status = Utility::receive( *comm, comm_status.source(), init_list_data_send_tag, values_to_receive.data(), number_of_values[init_list_data_send_tag] );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), init_list_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[init_list_data_send_tag] );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[init_list_data_send_tag], value ) );

        ++message_count;
        values_to_receive.clear();
      }

      message_count = 0;
      
      // Vector receive
      while( message_count < comm->size()-1 )
      {
        // Note: When probing for a std::vector message the status will not
        //       have a count that reflects the number of vectors sent (due
        //       to the implementation of send, which internally conducts
        //       multiple mpi send ops).
        Utility::Communicator::Status comm_status =
          Utility::iprobe<std::vector<T> >( *comm, vector_data_send_tag );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_GREATER( comm_status.source(), 0 );
        FRENSIE_REQUIRE_LESS( comm_status.source(), comm->size() );
        
        comm_status = Utility::receive( *comm, comm_status.source(), vector_data_send_tag, values_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( values_to_receive, std::vector<T>( number_of_values[raw_data_send_tag], value ) );

        ++message_count;
        values_to_receive.clear();
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::iprobe<T>( *comm, 0 ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::iprobe<std::vector<T> >( *comm, 0 ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a non-blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, iprobe_any_source_any_tag, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value;
    initializeValue( value, 1 );

    int number_of_values = 10;
    int raw_data_send_tag = 0;
    int vector_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      std::vector<T> values_to_send( number_of_values, value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, values_to_send.data(), values_to_send.size() );

      // Send the vector of data directly 
      Utility::send( *comm, 0, vector_data_send_tag, values_to_send );
    }
    else
    {
      std::vector<T> values_to_receive;

      int message_count = 0;
      
      // Raw data receive
      while( message_count < 2*(comm->size() - 1) )
      {
        Utility::Communicator::Status comm_status =
          Utility::iprobe<T>( *comm );

        // A null comm status indicates that no messages have been posted
        // from the specified source and/or with the specified tag
        if( !comm_status )
          continue;

        FRENSIE_REQUIRE_GREATER( comm_status.source(), 0 );
        FRENSIE_REQUIRE_LESS( comm_status.source(), comm->size() );
        FRENSIE_REQUIRE( comm_status.tag() == raw_data_send_tag ||
                         comm_status.tag() == vector_data_send_tag );

        if( comm_status.tag() == raw_data_send_tag )
        {
          if( std::is_arithmetic<T>::value )
          {
            FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values );
            
            values_to_receive.resize( comm_status.count() );
          }
          else
          {
            values_to_receive.resize( number_of_values );
          }
        
          comm_status = Utility::receive( *comm, comm_status.source(), comm_status.tag(), values_to_receive.data(), values_to_receive.size() );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
          FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
          FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values );
          FRENSIE_CHECK_EQUAL( values_to_receive,
                               std::vector<T>( number_of_values, value ) );
        }
        else
        {
          comm_status = Utility::receive( *comm, comm_status.source(), comm_status.tag(), values_to_receive );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
          FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), vector_data_send_tag );
          FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
          FRENSIE_CHECK_EQUAL( values_to_receive,
                               std::vector<T>( number_of_values, value ) );
        }

        ++message_count;
        values_to_receive.clear();
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::iprobe<T>( *comm ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( Utility::iprobe<std::vector<T> >( *comm ),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that an all gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, allGather, BasicTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  T value;
  initializeValue( value, comm->rank() );

  std::vector<T> data_to_send( 10, value );
  Utility::ArrayView<const T> view_of_data_to_send( data_to_send );

  std::vector<T> data_to_receive( comm->size() );

  // Gather the first values only
  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, data_to_send.front(), data_to_receive ) );
    
  for( size_t i = 0; i < comm->size(); ++i )
  {
    T expected_value;
    initializeValue( expected_value, i );
    
    FRENSIE_CHECK_EQUAL( data_to_receive[i], expected_value );
  }
  
  data_to_receive.clear();
  data_to_receive.resize( comm->size() );
  
  // Gather the first values only
  FRENSIE_REQUIRE_NO_THROW( Utility::allGather( *comm, data_to_send.front(), data_to_receive.data() ) );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    T expected_value;
    initializeValue( expected_value, i );
    
    FRENSIE_CHECK_EQUAL( data_to_receive[i], expected_value );
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicator.cpp
//---------------------------------------------------------------------------//
