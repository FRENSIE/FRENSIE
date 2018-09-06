//---------------------------------------------------------------------------//
//!
//! \file   tstCommunicatorIprobeHelper.cpp
//! \author Alex Robinson
//! \brief  Communicator iprobe helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
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
                   std::pair<short,int>, std::tuple<short,int> > Types;

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

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a non-blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, iprobe, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value = initializeValue( T(), comm->rank() );

    std::vector<int> number_of_values( {10, 8, 4, 1} );
    int raw_data_send_tag = 0;
    int view_data_send_tag = 1;
    int init_list_data_send_tag = 2;
    int container_data_send_tag = 3;
    
    if( comm->rank() > 0 )
    {
      T values_to_send[number_of_values[raw_data_send_tag]];
      Utility::ArrayView<T> view_of_values_to_send( values_to_send, values_to_send+number_of_values[raw_data_send_tag] );

      view_of_values_to_send.fill( value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, view_of_values_to_send );

      // Send all but the first and last values using a view 
      Utility::send( *comm, 0, view_data_send_tag, view_of_values_to_send( 1, number_of_values[view_data_send_tag] ) );

      // Send data using an initializer list temporary 
      Utility::send<T>( *comm, 0, init_list_data_send_tag, {value,value,value,value} );

      // Send a container of data directly
      std::array<T,10> container_to_send;
      container_to_send.fill( value );
      
      Utility::send( *comm, 0, container_data_send_tag, container_to_send );
    }
    else
    {
      for( int i = 1; i < comm->size(); ++i )
      {
        // Probe for and receive c-array style messages
        for( int j = 0; j < number_of_values.size()-1; ++j )
        {
          Utility::Communicator::Status comm_status;

          // A null comm status indicates that no messages have been posted
          // from the specified source and/or with the specified tag
          while( !comm_status )
            comm_status = Utility::iprobe<T>( *comm, i, j );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

          if( std::is_arithmetic<T>::value )
          {
            FRENSIE_REQUIRE_EQUAL( comm_status.count(), number_of_values[j] );
          }

          T values_to_receive[number_of_values[j]];
          Utility::ArrayView<T> view_of_values_to_receive( values_to_receive, values_to_receive+number_of_values[j] );

          T expected_values_to_receive[number_of_values[j]];
          Utility::ArrayView<const T> view_of_expected_values_to_receive;

          {
            Utility::ArrayView<T> tmp_view_of_expected_values_to_receive( expected_values_to_receive, expected_values_to_receive+number_of_values[j] );
            
            tmp_view_of_expected_values_to_receive.fill( initializeValue( T(), i ) );
            
            view_of_expected_values_to_receive = 
              tmp_view_of_expected_values_to_receive.toConst();
          }
          
          comm_status =
            Utility::receive( *comm, i, j, view_of_values_to_receive );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_EQUAL( comm_status.source(), i );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), j );
          FRENSIE_CHECK_EQUAL( comm_status.count(), number_of_values[j] );
          FRENSIE_CHECK_EQUAL( view_of_values_to_receive,
                               view_of_expected_values_to_receive );
        }

        // Probe for and receive container message
        // Note: When probing for a std::vector message the status will not
        //       have a count that reflects the number of vectors sent (due
        //       to the implementation of send, which internally conducts
        //       multiple mpi send ops).
        Utility::Communicator::Status comm_status;

        while( !comm_status )
        {
          comm_status = Utility::iprobe<std::array<T,10> >( *comm, i, container_data_send_tag );
        }

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

        // View data receive
        std::array<T,10> container_to_receive;
        std::array<T,10> expected_container_to_receive;
        expected_container_to_receive.fill( initializeValue( T(), i ) );
        
        comm_status = Utility::receive( *comm, i, container_data_send_tag, container_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_EQUAL( comm_status.source(), i );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), container_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( container_to_receive,
                             expected_container_to_receive );
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::iprobe<T>( *comm, 0, 0 ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( (Utility::iprobe<std::array<T,10> >( *comm, 0, 0 )),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// Check that a non-blocking probe can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, iprobe_any_source, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value = initializeValue( T(), comm->rank() );

    int raw_data_send_tag = 0;
    int array_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      std::array<T,10> values_to_send;
      values_to_send.fill( value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, Utility::arrayView(values_to_send) );

      // Send the array of data directly 
      Utility::send( *comm, 0, array_data_send_tag, values_to_send );
    }
    else
    {
      // Raw data receive from any source
      int number_of_messages_received = 0;

      while( number_of_messages_received < comm->size()-1 )
      {
        Utility::Communicator::Status comm_status;

        while( !comm_status )
          comm_status = Utility::iprobe<T>( *comm, raw_data_send_tag );

        std::array<T,10> values_to_receive;
        std::array<T,10> expected_values_to_receive;
        expected_values_to_receive.fill( initializeValue( T(), comm_status.source() ) );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );

        if( std::is_arithmetic<T>::value )
        {
          FRENSIE_REQUIRE_EQUAL( comm_status.count(), 10 );
        }
        
        comm_status = Utility::receive( *comm, comm_status.source(), raw_data_send_tag, Utility::arrayView(values_to_receive) );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 10 );
        FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );

        ++number_of_messages_received;
      }

      // Array data receive from any source
      number_of_messages_received = 0;

      while( number_of_messages_received < comm->size()-1 )
      {
        Utility::Communicator::Status comm_status;

        while( !comm_status )
        {
          comm_status = Utility::iprobe<std::array<T,10> >( *comm, array_data_send_tag );
        }

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        
        std::array<T,10> array_to_receive;
        std::array<T,10> expected_array_to_receive;
        expected_array_to_receive.fill( initializeValue( T(), comm_status.source() ) );
        
        comm_status = Utility::receive( *comm, comm_status.source(), array_data_send_tag, array_to_receive );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
        FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
        FRENSIE_CHECK_EQUAL( comm_status.tag(), array_data_send_tag );
        FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
        FRENSIE_CHECK_EQUAL( array_to_receive, expected_array_to_receive );

        ++number_of_messages_received;
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
FRENSIE_UNIT_TEST_TEMPLATE( Communicator, iprobe_any_source_any_tag, Types )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  // These operations can only be done with comms that have at least 2 procs
  if( comm->size() > 1 )
  {
    T value = initializeValue( T(), comm->rank() );

    int raw_data_send_tag = 0;
    int array_data_send_tag = 1;
    
    if( comm->rank() > 0 )
    {
      std::array<T,10> values_to_send;
      values_to_send.fill( value );

      // Raw data send 
      Utility::send( *comm, 0, raw_data_send_tag, Utility::arrayView(values_to_send) );

      // Send the vector of data directly 
      Utility::send( *comm, 0, array_data_send_tag, values_to_send );
    }
    else
    {
      // Raw data receive from any source with any tag
      int number_of_messages_received = 0;

      while( number_of_messages_received < 2*(comm->size()-1) )
      {
        Utility::Communicator::Status comm_status;

        while( !comm_status )
          comm_status = Utility::iprobe<T>( *comm );

        std::array<T,10> values_to_receive;
        std::array<T,10> expected_values_to_receive;
        expected_values_to_receive.fill( initializeValue( T(), comm_status.source() ) );

        FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
        FRENSIE_CHECK( comm_status.tag() == raw_data_send_tag ||
                       comm_status.tag() == array_data_send_tag );

        if( comm_status.tag() == raw_data_send_tag )
        {
          if( std::is_arithmetic<T>::value )
          {
            FRENSIE_CHECK_EQUAL( comm_status.count(), 10 );
          }
          
          comm_status = Utility::receive( *comm, comm_status.source(), raw_data_send_tag, Utility::arrayView(values_to_receive) );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
          FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), raw_data_send_tag );
          FRENSIE_CHECK_EQUAL( comm_status.count(), 10 );
          FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );
        }
        else
        {
          comm_status = Utility::receive( *comm, comm_status.source(), array_data_send_tag, values_to_receive );

          FRENSIE_REQUIRE( comm_status.hasMessageDetails() );
          FRENSIE_CHECK_GREATER( comm_status.source(), 0 );
          FRENSIE_CHECK_LESS( comm_status.source(), comm->size() );
          FRENSIE_CHECK_EQUAL( comm_status.tag(), array_data_send_tag );
          FRENSIE_CHECK_EQUAL( comm_status.count(), 1 );
          FRENSIE_CHECK_EQUAL( values_to_receive, expected_values_to_receive );
        }
        
        ++number_of_messages_received;
      }
    }
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::iprobe<T>( *comm ),
                         Utility::InvalidCommunicator );
    FRENSIE_CHECK_THROW( (Utility::iprobe<std::array<T,10> >( *comm )),
                         Utility::InvalidCommunicator );
  }
}

//---------------------------------------------------------------------------//
// end tstCommunicatorIprobeHelper.cpp
//---------------------------------------------------------------------------//
