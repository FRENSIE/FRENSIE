//---------------------------------------------------------------------------//
//!
//! \file   tstMPICommunicatorSequenceContainer.cpp
//! \author Alex Robinson
//! \brief  MPI Communicator unit tests using sequence containers
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
#include "Utility_Deque.hpp"
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
struct SequenceContainerList
{
  typedef std::tuple<std::array<T,10>,
                     std::vector<T>,
                     std::list<T>,
                     std::forward_list<T>,
                     std::deque<T> > type;
};

template<typename... Types>
struct MergeContainerLists;

template<typename T, typename... Types>
struct MergeContainerLists<T,Types...>
{
  typedef decltype(std::tuple_cat( typename SequenceContainerList<T>::type(), typename MergeContainerLists<Types...>::SequenceList() )) SequenceList;
};

template<typename T>
struct MergeContainerLists<T>
{
  typedef typename SequenceContainerList<T>::type SequenceList;
};

template<typename... Types>
struct MergeContainerLists<std::tuple<Types...> > : public MergeContainerLists<Types...>
{ /* ... */ };

typedef typename MergeContainerLists<BasicTypes>::SequenceList SequenceContainerTypes;

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

template<typename Container>
inline void clearContainer( Container& container )
{ container.clear(); }

template<typename T, size_t N>
inline void clearContainer( std::array<T,N>& container )
{ container.fill( T() ); }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that sequence containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            send_recv,
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
// Check that sequence containers can be sent and received
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            isend_irecv,
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
      resizeSequenceContainer( expected_container_to_receive, value );

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
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );
  
  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  Container container_to_send;
  resizeSequenceContainer( container_to_send, value );

  std::vector<Container> containers_to_receive( comm->size() );
  
  FRENSIE_REQUIRE_NO_THROW( mpi_comm.allGather( &container_to_send, 1, containers_to_receive.data() ) );

  for( int i = 0; i < comm->size(); ++i )
  {
    T expected_value;
    Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
    
    Container expected_container;
    resizeSequenceContainer( expected_container, expected_value );
    
    FRENSIE_CHECK_EQUAL( containers_to_receive[i], expected_container );
  }
}

//---------------------------------------------------------------------------//
// Check that an all-to-all operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            allToAll,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  std::vector<Container> data_to_send( comm->size() );

  for( size_t i = 0; i < comm->size(); ++i )
  {
    T value;
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

    resizeSequenceContainer( data_to_send[i], value );
  }

  std::vector<Container> data_to_receive( data_to_send.size() );

  // Each proc will gather the values that are equal to its rank
  FRENSIE_REQUIRE_NO_THROW( mpi_comm.allToAll( data_to_send.data(), 1, data_to_receive.data() ) );

  T expected_value;

  Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  std::vector<Container> expected_data_to_receive( data_to_send.size() );

  for( size_t i = 0; i < expected_data_to_receive.size(); ++i )
    resizeSequenceContainer( expected_data_to_receive[i], expected_value );

  FRENSIE_CHECK_EQUAL( data_to_receive, expected_data_to_receive );
}

//---------------------------------------------------------------------------//
// Check that a broadcast operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            broadcast,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  Container data;

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 49 : 1);

  // Broadcast from proc with rank==0
  if( comm->rank() == 0 )
    resizeSequenceContainer( data, value );
  
  FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 0 ) );

  Container expected_data;
  resizeSequenceContainer( expected_data, value );

  FRENSIE_CHECK_EQUAL( data, expected_data );

  if( comm->size() > 1 )
  {
    clearContainer( data );
    clearContainer( expected_data );
    
    Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 50 : 2);

    // Broadcast from proc with rank==1
    if( comm->rank() == 1 )
      resizeSequenceContainer( data, value );
   
    FRENSIE_REQUIRE_NO_THROW( mpi_comm.broadcast( &data, 1, 1 ) );

    resizeSequenceContainer( expected_data, value );

    FRENSIE_CHECK_EQUAL( data, expected_data );
  }
}

//---------------------------------------------------------------------------//
// Check that a gather operation can be conducted
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            gather,
                            SequenceContainerTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Container );

  typedef typename Container::value_type T;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  const Utility::MPICommunicator& mpi_comm =
    dynamic_cast<const Utility::MPICommunicator&>( *comm );

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  Container data;
  resizeSequenceContainer( data, value );

  // Gather on proc with rank==0
  if( comm->rank() == 0 )
  {
    std::vector<Container> gathered_data( comm->size() );
    
    FRENSIE_REQUIRE_NO_THROW( mpi_comm.gather( &data, 1, gathered_data.data(), 0 ) );

    std::vector<Container> expected_data( gathered_data.size() );

    for( size_t i = 0; i < comm->size(); ++i )
    {
      T expected_value;
      Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

      resizeSequenceContainer( expected_data[i], expected_value );
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
        T expected_value;
        Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
        resizeSequenceContainer( expected_data[i], expected_value );
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
                            SequenceContainerTypes )
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

  T value;
  Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  std::vector<Container> data( comm->rank()+1 );

  for( size_t i = 0; i < data.size(); ++i )
    resizeSequenceContainer( data[i], value );
  
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
      T expected_value;
        Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
      for( size_t j = 0; j < sizes[i]; ++j )
      {
        resizeSequenceContainer( expected_data[index], expected_value );
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
        T expected_value;
        Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
        for( size_t j = 0; j < sizes[i]; ++j )
        {
          resizeSequenceContainer( expected_data[index], expected_value );
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
                            SequenceContainerTypes )
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
    {
      T value;
      Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

      resizeSequenceContainer( data[i], value );
    }
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( data.data(), &scattered_data, 1, 0 ) );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatter( Utility::NullPointer<Container>::value, &scattered_data, 1, 0 ) );
  }

  T expected_value;
  Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  Container expected_data;
  resizeSequenceContainer( expected_data, expected_value );

  FRENSIE_CHECK_EQUAL( scattered_data, expected_data );
  
  if( comm->size() > 1 )
  {
    clearContainer( scattered_data );

    // Scatter from proc with rank==1
    if( comm->rank() == 1 )
    {
      std::vector<Container> data( comm->size() );

      for( size_t i = 0; i < comm->size(); ++i )
      {
        T value;
        Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
        resizeSequenceContainer( data[i], value );
      }
    
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
/*
FRENSIE_UNIT_TEST_TEMPLATE( MPICommunicator,
                            scatterv,
                            SequenceContainerTypes )
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
    {
      T value;
      Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);

      resizeSequenceContainer( data[i], value );
    }
    
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, offsets, &scattered_data_advanced, 1, 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( data.data(), sizes, &scattered_data_basic, 1, 0 ) );
  }
  else
  {
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<Container>::value, sizes, offsets, &scattered_data_advanced, 1, 0 ) );
    FRENSIE_CHECK_NO_THROW( mpi_comm.scatterv( Utility::NullPointer<Container>::value, sizes, &scattered_data_basic, 1, 0 ) );
  }

  T expected_value;
  Utility::get<0>( expected_value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+comm->rank() : comm->rank());

  Container expected_data;
  resizeSequenceContainer( expected_data, expected_value );

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
      {
        T value;
        Utility::get<0>( value ) = (std::is_same<T,char>::value || std::is_same<T,unsigned char>::value ? 48+i : i);
        
        resizeSequenceContainer( data[i], value );
      }
    
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
*/
//---------------------------------------------------------------------------//
// end tstMPICommunicatorSequenceContainer.cpp
//---------------------------------------------------------------------------//
