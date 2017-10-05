//---------------------------------------------------------------------------//
//!
//! \file   Utility_CommunicatorHelpers.hpp
//! \author Alex Robinson
//! \brief  The communicator helper method definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMMUNICATOR_HELPERS_DEF_HPP
#define UTILITY_COMMUNICATOR_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_MPICommunicator.hpp"
#include "Utility_SerialCommunicator.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

#define __TEST_FOR_NULL_COMM__( comm )          \
  TEST_FOR_EXCEPTION( comm.size() == 0,         \
                      InvalidCommunicator,      \
                      "A null communicator (size == 0) was encountered!" )

namespace Utility{

// Determine the number of elements that were contained in a message
/*! \ingroup mpi
 */
template<typename T>
inline int count( const Communicator& comm, const CommunicatorStatus& status )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    return mpi_comm->count<T>( status );
  }
  else
    return 0;
}
  
// Send data to another process
/*! \details The value on the calling process of the communicator will be 
 * sent with tag to destination_process of the communicator. This operation
 * will block until the destination process receives the value. This
 * operation can only be done with communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline void send( const Communicator& comm,
                  int destination_process,
                  int tag,
                  const T& value )
{ Utility::send( comm, destination_process, tag, &value, 1 ); }

// Send an array of data to another process
/*! \details The values on the calling process of the communicator will be
 * sent with tag to destination_process of the communicator. This operation
 * will block until the destination process receives the values. This
 * operation can only be done with communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
void send( const Communicator& comm,
           int destination_process,
           int tag,
           const T* values,
           int number_of_values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Blocking send operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator const* mpi_comm =
    dynamic_cast<const MPICommunicator const*>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  try{
    mpi_comm->send( destination_process, tag, values, number_of_values );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct blocking send "
                              "operation to destination process "
                              << destination_process << " with tag " << tag <<
                              " successfully!" );
}

// Receive data from another process
/*! \details The value on the calling process of the communicator will be
 * received with tag from source_process of the communicator. This operation
 * will block until the source process sends the value. This
 * operation can only be done with communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline std::shared_ptr<const CommunicatorStatus>
receive( const Communicator& comm,
         int source_process,
         int tag,
         T& value )
{ return Utility::receive( comm, source_process, tag, &value, 1 ); }

// Receive an array of data from another process
/*! \details The values on the calling process of the communicator will be
 * received with tag from source_process of the communicator. This operation
 * will block until the source process sends the values. This
 * operation can only be done with communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
std::shared_ptr<const CommunicatorStatus>
receive( const Communicator& comm,
         int source_process,
         int tag,
         T* values,
         int number_of_values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Blocking receive operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator const* mpi_comm =
    dynamic_cast<const MPICommunicator const*>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  try{
    mpi_comm->send( source_process, tag, values, number_of_values );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct blocking receive "
                              "operation from source process "
                              << source_process << " with tag " << tag <<
                              " successfully!" );
}

// Send a data to another process without blocking
/*! \details The value on the calling process of the communicator will be 
 * sent with tag to destination_process of the communicator. This operation
 * will not block. Use the returned request to determine when the destination 
 * process has received the value. This operation can only be done with 
 * communicators of size two or greater.
 * \ingroup mpi
 */
inline std::shared_ptr<CommunicatorRequest>
isend( const Communicator& comm,
       int destination_process,
       int tag,
       const T& value )
{
  return Utility::isend( comm, destination_process, tag, &value, 1 );
}

// Send an array of data to another process without blocking
/*! \details The values on the calling process of the communicator will be 
 * sent with tag to destination_process of the communicator. This operation
 * will not block. Use the returned request to determine when the destination 
 * process has received the values. This operation can only be done with 
 * communicators of size two or greater.
 * \ingroup mpi
 */
std::shared_ptr<CommunicatorRequest>
isend( const Communicator& comm,
       int destination_process,
       int tag,
       const T* values,
       int number_of_values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Non-blocking send operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator const* mpi_comm =
    dynamic_cast<const MPICommunicator const*>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  std::shared_ptr<CommunicatorRequest> request;
  
  try{
    request =
      mpi_comm->isend( destination_process, tag, values, number_of_values );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct non-blocking send "
                              "operation to destination process "
                              << destination_process << " with tag " << tag <<
                              " successfully!" );

  return request;
}

// Prepare to receive data from another process
/*! \details The value on the calling process of the communicator will be
 * received with tag from source_process of the communicator. This operation
 * will not block. Use the returned request to determine when the source 
 * process has sent the value. This operation can only be done with 
 * communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline std::shared_ptr<CommunicatorRequest>
ireceive( const Communicator& comm,
          int source_process,
          int tag,
          T& value )
{
  return Utility::ireceive( comm, source_process, tag, &value, number_of_values );
}

// Prepare to receive an array of data from another process
/*! \details The values on the calling process of the communicator will be
 * received with tag from source_process of the communicator. This operation
 * will not block. Use the returned request to determine when the source 
 * process has sent the values. This operation can only be done with 
 * communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
std::shared_ptr<CommunicatorRequest>
ireceive( const Communicator& comm,
          int source_process,
          int tag,
          T* values,
          int number_of_values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Non-blocking receive operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator const* mpi_comm =
    dynamic_cast<const MPICommunicator const*>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  std::shared_ptr<CommunicatorRequest> request;

  try{
    mpi_comm->irecv( source_process, tag, values, number_of_values );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct non-blocking receive "
                              "operation from source process "
                              << source_process << " with tag " << tag <<
                              " successfully!" );
}

// Wait until a message is available to be received
/*! \details The calling process of the communicator will wait until
 * source_process of the communicator has sent a message with tag. Use the
 * returned status to determine the message details before conducting
 * a receive operation. This operation will block until the source 
 * process sends a message to the calling process. This operation can only be 
 * done with communicators of size two or greater.
 * \ingroup mpi
 */
inline std::shared_ptr<const CommunicatorStatus>
probe( const Communicator& comm, int source_process, int tag )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Blocking probe operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator const* mpi_comm =
    dynamic_cast<const MPICommunicator const*>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  std::shared_ptr<const CommunicatorStatus> status;
  
  try{
    status = mpi_comm->probe( source_process, tag );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct blocking probe "
                              "operation to source process "
                              << (source_process == comm.anySourceValue() ? std::string("\"any source\"") : Utility::toString(source_process))
                              << " with tag "
                              << (tag == comm.anyTagValue() ? std::string("\"any tag\"") : Utility::toString(tag))
                              << " successfully!" );

  return status;
}

// Wait until a message is available to be received from any source
/*! \details The calling process of the communicator will wait until
 * any process of the communicator has sent a message with tag. Use the
 * returned status to determine the message details before conducting
 * a receive operation. This operation will block until the a process sends a 
 * message with tag to the calling process. This operation can only be done 
 * with communicators of size two or greater.
 * \ingroup mpi
 */
inline std::shared_ptr<const CommunicatorStatus>
probe( const Communicator& comm, int tag )
{
  return Utility::probe( comm, comm.anySourceValue(), tag );
}

// Wait until a message is available to be received from any source with any tag
/*! \details The calling process of the communicator will wait until
 * any process of the communicator has sent a message with any tag. Use the
 * returned status to determine the message details before conducting
 * a receive operation. This operation will block until the a process sends a 
 * message to the calling process. This operation can only be done with 
 * communicators of size two or greater.
 * \ingroup mpi
 */
inline std::shared_ptr<const CommunicatorStatus>
probe( const Communicator& comm )
{
  return Utility::probe( comm, comm.anySourceValue(), comm.anyTagValue() );
}

// Determine if a message is available to be received
/*! \details The calling process of the communicator will check if
 * source_process of the communicator has sent a message with tag. If the
 * returned status pointer is null, no message has been sent. If the returned
 * status pointer is not null, use it to determine the message details before 
 * conducting a receive operation. This operation will not block. This 
 * operation can only be  done with communicators of size two or greater.
 * \ingroup mpi
 */
std::shared_ptr<const CommunicatorStatus>
iprobe( const Communicator& comm, int source_process, int tag )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Non-blocking probe operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator const* mpi_comm =
    dynamic_cast<const MPICommunicator const*>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  std::shared_ptr<const CommunicatorStatus> status;
  
  try{
    status = mpi_comm->iprobe( source_process, tag );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct non-blocking probe "
                              "operation to source process "
                              << (source_process == comm.anySourceValue() ? std::string("\"any source\"") : Utility::toString(source_process))
                              << " with tag "
                              << (tag == comm.anyTagValue() ? std::string("\"any tag\"") : Utility::toString(tag))
                              << " successfully!" );

  return status;
}

// Determine if a message is available to be received from any source
/*! \details The calling process of the communicator will check if
 * any process of the communicator has sent a message with tag. If the
 * returned status pointer is null, no message has been sent to the calling
 * process. If the returned status pointer is not null, use it to determine the
 * message details before conducting a receive operation. This operation will 
 * not block. This operation can only be  done with communicators of size two 
 * or greater.
 * \ingroup mpi
 */
inline std::shared_ptr<const CommunicatorStatus>
iprobe( const Communicator& comm, int tag )
{
  return Utility::iprobe( comm, comm.anySourceValue(), tag );
}

// Determine if a message is available to be received from any source with any tag
/*! \details The calling process of the communicator will check if
 * any process of the communicator has sent a message. If the
 * returned status pointer is null, no message has been sent to the calling
 * process. If the returned status pointer is not null, use it to determine the
 * message details before conducting a receive operation. This operation will 
 * not block. This operation can only be done with communicators of size two 
 * or greater.
 * \ingroup mpi
 */
inline std::shared_ptr<const CommunicatorStatus>
iprobe( const Communicator& comm )
{
  return Utility::iprobe( comm, comm.anySourceValue(), comm.anyTagValue() );
}

// Wait for the request to finish
/*! \details The calling process of the communicator will wait until
 * the request has completed. The returned status can be used to determine
 * the details of the completed request.
 * \ingroup mpi
 */
std::shared_ptr<const CommunicatorStatus>
wait( const Communicator& comm,
      const std::shared_ptr<CommunicatorRequest>& request )
{
  if( comm.size() > 1 && request.get() )
  {
    std::shared_ptr<const CommunicatorStatus> status;
    try{
      status = request->wait();
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " was not able to wait for the for "
                                "the request to complete successfully!" );
    return status;
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    return std::shared_ptr<const CommunicatorStatus>();
  }
}

// Wait for the request to finish
/*! \details The calling process of the communicator will wait until
 * the request has completed. The returned status can be used to determine
 * the details of the completed request.
 * \ingroup mpi
 */
inline void wait( const Communicator& comm,
                  const std::shared_ptr<CommunicatorRequest>& request,
                  std::shared_ptr<const CommunicatorRequest>& status )
{
  status = Utility::wait( comm, request );
}

// Wait for the requests to finish
/*! \details The calling process of the communicator will wait until
 * all of the requests have completed. The returned statuses can be used to 
 * determine the details of each completed request.
 * \ingroup mpi
 */
template<template<typename T,typename...> class STLCompliantInputSequenceContainer,
         template<typename T,typename...> class STLCompliantOutputSequenceContainer,
         typename T>
void wait( const Communicator& comm,
           const STLCompliantInputSequenceContainer<std::shared_ptr<CommunicatorRequest> >& requests,
           STLCompliantOutputSequenceContainer<std::shared_ptr<const CommunicatorStatus> >& statuses )
{
  // Resize the statuses array
  statuses.resize( requests.size() );

  for( size_t i = 0; i < requests.size(); ++i )
    Utility::wait( comm, requests[i], statuses[i] );
}

// Gather the values stored at every process into vectors of values 
// from each process.
/*! \details The input_value on every process of the communicator will be 
 * collected in the output_values vector on every process. The input_value 
 * associated with a process will be located at the index that is equal to the 
 * process's rank. The output_values vector will be resized appropriately. This
 * operation can be done with communicators of any size.
 * \ingroup mpi
 */ 
template<typename T>
inline void allGather( const Communicator& comm,
                       const T& input_value,
                       std::vector<T>& output_values )
{
  Utility::allGather( comm, &input_value, 1, output_values );
}

// Gather the values stored at every process into vectors of values 
// from each process.
/*! \details The input_value on every process of the communicator will be
 * collected in the output_values array on every process. The input_value
 * associated with a process will be located at the index that is equal to the
 * process's rank. The output_values array must be sized appropriately before
 * passing it the this method. This operation can be done with communicators
 * of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       const T& input_value,
                       T* output_values )
{
  Utility::allGather( comm, &input_value, 1, output_values );
}

// Gather the array of values stored at every process into vectors of
// values from each process.
/*! \details The input_values on every process of the communicator will be
 * collected in the output_values vector on every process. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by the number_of_input_values. The output_values
 * will be resized appropriately. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       const T* input_values,
                       int number_of_input_values,
                       std::vector<T>& output_values )
{
  if( comm.size() >= 1 )
    output_values.resize( number_of_input_values*comm.size() );
  else
    output_values.resize( number_of_input_values );
  
  Utility::allGather( comm, input_values, number_of_input_values, output_values.data() );
}

// Gather the array of values stored at every process into vectors of
// values from each process.
/*! \details The input_values on every process of the communicator will be
 * collected in the output_values array on every process. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by the number_of_input_values. The output_values
 * array must be sized appropriately before passing it in to this method. This
 * operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void allGather( const Communicator& comm,
                const T* input_values,
                int number_of_input_values,
                T* output_values )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->allGather( input_values, number_of_input_values, output_values );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allGather "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::allGather( input_values, number_of_input_values, output_values );
  }
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The input_values on every process of the communicator will be
 * reduced in the output_values array on every process. The output_values
 * array must be sized appropriately before passing it in to this method. This
 * operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                const T* input_values,
                int number_of_input_values,
                T* output_values,
                ReduceOperation op )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->allReduce( input_values, number_of_input_values, output_values, op );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allReduce "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    SerialCommunicator::allReduce( input_values, number_of_input_values, output_values );
  }
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The input_value on every process of the communicator will be
 * reduced in the output_value on every process. This operation can be done
 * with communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void allReduce( const Communicator& comm,
                       const T& input_value,
                       T& output_value,
                       ReduceOperation op )
{
  Utility::allReduce( comm, &input_value, 1, &output_value, op );
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The input_output_values on every process of the communicator will 
 * be reduced inline on every process. This operation can be done
 * with communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                T* input_output_values,
                int number_of_values,
                ReduceOperation op )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->allReduce( input_values, number_of_input_values, output_values, op );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allReduce "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
  }
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The input_output_value on every process of the communicator will 
 * be reduced inline on every process. This operation can be done
 * with communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void allReduce( const Communicator& comm,
                       T& input_output_value,
                       ReduceOperation op )
{
  Utility::allReduce( comm, &input_output_value, 1, op );
}

// Send data from every process to every other process
/*! \details The input_values on every process of the communicator will 
 * be sent to every other process of the communicator. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by the number of input values. The output_values
 * will be resized appropriately. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allToAll( const Communicator& comm,
                      const std::vector<T>& input_values,
                      std::vector<T>& output_values )
{
  Utility::allToAll( comm, input_values, input_values.size(), output_values );
}

// Send data from every process to every other process
/*! \details The input_values on every process of the communicator will 
 * be sent to every other process of the communicator. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by number_of_input_values. The output_values
 * will be resized appropriately. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allToAll( const Communicator& comm,
                      const std::vector<T>& input_values,
                      int number_of_input_values,
                      std::vector<T>& output_values )
{
  // Resize the output values
  if( comm.size() >= 1 )
    output_values.resize( number_of_input_values*comm.size() );
  else
    output_values.resize( number_of_input_values );

  Utility::allToAll( comm, input_values.data(), number_of_input_values, output_values.data();
}

// Send data from every process to every other process
/*! \details The input_values on every process of the communicator will 
 * be sent to every other process of the communicator. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by number_of_input_values. The output_values
 * must be sized appropriately before passing it to this method. This 
 * operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void allToAll( const Communicator& comm,
               const T* input_values,
               int number_of_input_values,
               T* output_values )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->allToAll( input_values, number_of_input_values, output_values );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allToAll "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    SerialCommuniator::allToAll( input_values, number_of_input_values, output_values );
  }
}

// Broadcast a value from a root process to all other processes
/*! \details The value on the root process of the communicator will be sent 
 * to all other processes of the communicator. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void broadcast( const Communicator& comm, T& value, int root_process )
{
  Utility::broadcast( comm, &value, 1, root_process );
}

// Broadcast a value from a root process to all other processes
/*! \details The values on the root process of the communicator will be sent 
 * to all other processes of the communicator. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void broadcast( const Communicator& comm,
                T* values,
                int number_of_values,
                int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->broadcast( values, number_of_values, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct broadcast "
                                "operation from root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::broadcast( values, number_of_values, root_process );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details The value on every process of the communicator will be sent 
 * to root_process of the communicator. The output_values will be resized
 * appropriately. The value sent by a process will be located at the index in 
 * output_values that is equal to the process's rank. This operation can be 
 * done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const T& input_value,
                    std::vector<T>& output_values,
                    int root_process )
{
  Utility::gather( comm, &input_value, 1, output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The value on every process of the communicator will be sent 
 * to root_process of the communicator. The output_values must be sized
 * appropriately before passing it to this method. The value sent by a process 
 * will be located at the index in output_values that is equal to the process's
 * rank. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const T& input_value,
                    T* output_values,
                    int root_process )
{
  Utility::gather( comm, &input_value, 1, output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values on every process of the communicator will be sent 
 * to root_process of the communicator. The output_values will be resized
 * appropriately. The values sent by a process will start at the index in 
 * output_values that is equal to the process's rank multiplied by 
 * number_of_input_values. This operation can be done with communicators of any
 * size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const T* input_values,
                    int number_of_input_values,
                    std::vector<T>& output_values,
                    int root_process )
{
  // Resize the output values
  if( comm.size() >= 1 )
    output_values.resize( number_of_input_values*comm.size() );
  else
    output_values.resize( number_of_input_values );

  Utility::gather( comm, input_values, number_of_input_values, output_values.data(), root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values on every process of the communicator will be sent 
 * to root_process of the communicator. The output_values must be sized
 * appropriately before passing it to this method. The values sent by a process
 * will start at the index in output_values that is equal to the process's rank
 * multiplied by number_of_input_values. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void gather( const Communicator& comm,
             const T* input_values,
             int number_of_input_values,
             T* output_values,
             int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->gather( input_values, number_of_input_values, output_values, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct gather "
                                "operation to root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::gather( input_values, number_of_input_values, output_values, root_process );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The sizes and offsets vectors 
 * determine the ranges of input values on each process that will be sent.
 * The output_values must be sized appropriatedly before passing it to this
 * method. The values sent by a process will be located at the index in 
 * output_values that is equal to the process's rank multipled by
 * the processes sent size (sizes[rank]). This operation can be 
 * done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const std::vector<T>& input_values,
                     T* output_values,
                     const std::vector<int>& sizes,
                     const std::vector<int>& offsets,
                     const int root_process )
{
  Utility::gatherv( comm, input_values.data(), input_values.size(), output_values, sizes, offsets, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The sizes and offsets vectors 
 * determine the ranges of input values on each process that will be sent.
 * The output_values must be sized appropriatedly before passing it to this
 * method. The values sent by a process will be located at the index in 
 * output_values that is equal to the process's rank multipled by
 * the processes sent size (sizes[rank]). This operation can be 
 * done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const T* input_values,
                     int number_of_input_values,
                     T* output_values,
                     const std::vector<int>& sizes,
                     const std::vector<int>& offsets,
                     const int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->gatherv( input_values, number_of_input_values, output_values, sizes, offests, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct gatherv "
                                "operation to root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::gatherv( input_values,
                                 number_of_input_values,
                                 output_values,
                                 sizes,
                                 offsets,
                                 root_process );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The sizes determine the ranges of input
 * values on each process that will be sent. The output_values must be sized 
 * appropriatedly before passing it to this method. The values sent by a 
 * process will be located at the index in output_values that is equal to the 
 * process's rank multipled by the processes sent size (sizes[rank]). 
 * This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const std::vector<T>& input_values,
                     T* output_values,
                     const std::vector<int>& sizes,
                     const int root_process )
{
  Utility::gatherv( comm, input_values.data(), input_values.size(), output_values, sizes, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The sizes determine the ranges of input
 * values on each process that will be sent. The output_values must be sized 
 * appropriatedly before passing it to this method. The values sent by a 
 * process will be located at the index in output_values that is equal to the 
 * process's rank multipled by the processes sent size (sizes[rank]). 
 * This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void gatherv( const Communicator& comm,
              const T* input_values,
              int number_of_input_values,
              T* output_values,
              const std::vector<int>& sizes,
              const int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->gatherv( input_values, number_of_input_values, output_values, sizes, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct gatherv "
                                "operation to root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::gatherv( input_values,
                                 number_of_input_values,
                                 output_values,
                                 sizes,
                                 root_process );
  }
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The value that a process
 * receives from the root process will be from the input values array at the
 * index that is equal to the process's rank. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void scatter( const Communicator& comm,
              const std::vector<T>& input_values,
              T& output_value,
              int root_process )
{
  Utility::scatter( comm, input_values.data(), &output_value, 1, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The value that a process
 * receives from the root process will be from the input values array at the
 * index that is equal to the process's rank. This operation can be done with 
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     const T* input_values,
                     T& output_value,
                     int root_process )
{
  Utility::scatter( comm, input_values, &output_value, 1, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The values that a process
 * receives from the root process will be from the input values array 
 * starting at the index that is equal to the process's rank multiplied by
 * number_of_values_per_proc. This operation can be done with communicators of 
 * any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     const std::vector<T>& input_values,
                     T* output_values,
                     int number_of_values_per_proc,
                     int root_process )
{
  Utility::scatter( comm, input_values.data(), output_values, number_of_values_per_proc, root_process );
}

// Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const T* input_values,
              T* output_values,
              int number_of_values_per_proc,
              int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->scatter( input_values, output_values, number_of_values_per_proc, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct scatter "
                                "operation from root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::scatter( input_values, output_values, number_of_values_per_proc, root_process );
  }
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The range of values that a 
 * process receives from the root process will be determined by the sizes
 * and offsets arrays. This operation can be done with communicators of 
 * any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatterv( const Communicator& comm,
                      const std::vector<T>& input_values,
                      const std::vector<int>& sizes,
                      const std::vector<int>& offsets,
                      T* output_values,
                      int number_of_output_values,
                      int root_process )
{
  Utility::scatterv( comm, input_values.data(), sizes, offsets, output_values, number_of_output_values, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The range of values that a 
 * process receives from the root process will be determined by the sizes
 * and offsets arrays. This operation can be done with communicators of 
 * any size.
 * \ingroup mpi
 */
template<typename T>
void scatterv( const Communicator& comm,
               const T* input_values,
               const std::vector<int>& sizes,
               const std::vector<int>& offsets,
               T* output_values,
               int number_of_output_values,
               int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->scatterv( input_values, sizes, offsets, output_values, number_of_output_values, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct scatterv "
                                "operation from root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::scatterv( input_values, sizes, offsets, output_values, number_of_output_values, root_process );
  }
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The range of values that a 
 * process receives from the root process will be determined by the sizes
 * array. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatterv( const Communicator& comm,
                      const std::vector<T>& input_values,
                      const std::vector<int>& sizes,
                      T* output_values,
                      int number_of_output_values,
                      int root_process )
{
  Utility::scatterv( comm, input_values.data(), sizes, output_values, number_of_output_values, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The range of values that a 
 * process receives from the root process will be determined by the sizes
 * array. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void scatterv( const Communicator& comm,
               const T* input_values,
               const std::vector<int>& sizes,
               T* output_values,
               int number_of_output_values,
               int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->scatterv( input_values, sizes, offsets, output_values, number_of_output_values, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct scatterv "
                                "operation from root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::scatterv( input_values, sizes, offsets, output_values, number_of_output_values, root_process );
  }
}

// Combine the values stored by each process intoa single value at the root
/*! \details The input_value on every process of the communicator will be
 * reduced on root_process of the communicator. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void reduce( const Communicator& comm,
                    const T& input_value,
                    T& output_value,
                    ReduceOperation op,
                    int root_process )
{
  Utility::reduce( comm, &input_value, 1, &output_value, op );
}

// Combine the values stored by each process intoa single value at the root
/*! \details The input_values on every process of the communicator will be
 * reduced on root_process of the communicator. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const T* input_values,
             int number_of_input_values,
             T* output_values,
             ReduceOperation op,
             int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->reduce( input_values, number_of_input_values, output_values, op, root_process );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct reduce "
                                "operation to root process "
                                << root_process << " successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );
    
    SerialCommunicator::reduce( input_values, number_of_input_values, output_values, op, root_process );
  }
}

// Compute a prefix reduction of values from all processes
/*! \details The input_value on every process of the communicator will be
 * reduced using a prefix reduction. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void scan( const Communicator& comm,
                  const T& input_value,
                  T& output_value,
                  ReduceOperation op )
{
  Utility::scan( comm, &input_value, 1, &output_value, op );
}

// Compute a prefix reduction of values from all processes
/*! \details The input_values on every process of the communicator will be
 * reduced using a prefix reduction. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void scan( const Communicator& comm,
           const T* input_values,
           int number_of_input_values,
           T* output_value,
           ReduceOperation op )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator const* mpi_comm =
      dynamic_cast<const MPICommunicator const*>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->scan( input_values, number_of_input_values, output_values, op );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct scan "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    SerialCommunicator::scan( input_values, number_of_input_values, output_values, op );
  }
}
  
} // end Utility namespace

#endif // end UTILITY_COMMUNICATOR_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_CommunicatorHelpers_def.hpp
//---------------------------------------------------------------------------//
