//---------------------------------------------------------------------------//
//!
//! \file   Utility_Communicator_def.hpp
//! \author Alex Robinson
//! \brief  The communicator class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMMUNICATOR_DEF_HPP
#define UTILITY_COMMUNICATOR_DEF_HPP

// Std Lib Includes
#include <string>
#include <utility>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

#define __TEST_FOR_NULL_COMM__( comm )          \
  TEST_FOR_EXCEPTION( comm.size() == 0,         \
                      InvalidCommunicator,      \
                      "A null communicator (size == 0) was encountered!" )

/*! NOTE: Due to scatterv changes introduced in boost 1.72, 
 *  anything involving scatterv does not function properly 
 * at the moment and its tests are disabled. If you require
 * scatterv, please find the bug, fix it, and submit it for
 * a pull request.
 *  \ingroup mpi
 */

namespace Utility{

namespace Details{

/*! The serial communicator array copy helper
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SerialCommunicatorArrayCopyHelper
{
  //! Copy from input array to output array using a element-by-element deep copy
  static inline void copyFromInputArrayToOutputArray(
                                                    const T* input_values,
                                                    int number_of_input_values,
                                                    T* output_values )
  {
    for( int i = 0; i < number_of_input_values; ++i )
      output_values[i] = input_values[i];
  }
};

/*! \brief Specialization of SerialCommunicatorArrayCopyHelper for arithmetic
 * types
 * \ingroup mpi
 */
template<typename T>
struct SerialCommunicatorArrayCopyHelper<T,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
  //! Copy from input array to output array using memcpy
  static inline void copyFromInputArrayToOutputArray(
                                                    const T* input_values,
                                                    int number_of_input_values,
                                                    T* output_values )
  {
    std::memcpy( output_values,
                 input_values,
                 sizeof(T)*number_of_input_values );
  }
};

/*! The single value send helper class
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SingleValueSendHelper
{
  //! Forward to the correct send method based on type T
  static inline void send( const Communicator& comm,
                           int destination_process,
                           int tag,
                           const T& value )
  {
    Utility::ArrayView<const T> value_view( &value, 1 );

    Utility::send( comm, destination_process, tag, value_view );
  }

  //! Forward to the correct isend method based on type T
  static inline Communicator::Request isend( const Communicator& comm,
                                             int destination_process,
                                             int tag,
                                             const T& value )
  {
    Utility::ArrayView<const T> value_view( &value, 1 );

    return Utility::isend( comm, destination_process, tag, value_view );
  }
};

/*! Partial specialization of SingleValueSendHelper for Utility::ArrayView
 * \ingroup mpi
 */
template<typename T>
struct SingleValueSendHelper<Utility::ArrayView<T>, typename std::enable_if<!std::is_const<T>::value>::type>
{
  //! Forward to the correct send method based on type T
  static inline void send( const Communicator& comm,
                           int destination_process,
                           int tag,
                           const Utility::ArrayView<T>& value )
  { Utility::send( comm, destination_process, tag, value.toConst() ); }

  //! Forward to the correct isend method based on type T
  static inline Communicator::Request isend( const Communicator& comm,
                                             int destination_process,
                                             int tag,
                                             const Utility::ArrayView<T>& value )
  { return Utility::isend( comm, destination_process, tag, value.toConst() ); }
};

/*! The single value receive helper class
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SingleValueReceiveHelper
{
  //! Forward to the correct receive method based on type T
  static inline Communicator::Status receive( const Communicator& comm,
                                              int source_process,
                                              int tag,
                                              T& value )
  {
    Utility::ArrayView<T> value_view( &value, 1 );

    return Utility::receive( comm, source_process, tag, const_cast<const Utility::ArrayView<T>&>( value_view ) );
  }

  //! Forward to the correct ireceive method based on type T
  static inline Communicator::Request ireceive( const Communicator& comm,
                                                int source_process,
                                                int tag,
                                                T& value )
  {
    Utility::ArrayView<T> value_view( &value, 1 );

    return Utility::ireceive( comm, source_process, tag, const_cast<const Utility::ArrayView<T>&>( value_view ) );
  }
};

/*! Partial specialization of SingleValueReceiveHelper for Utility::ArrayView
 * \ingroup mpi
 */
template<typename T>
struct SingleValueReceiveHelper<Utility::ArrayView<T> >
{
  //! Forward to the correct receive method based on type T
  static inline Communicator::Status receive( const Communicator& comm,
                                              int source_process,
                                              int tag,
                                              Utility::ArrayView<T>& value )
  {
    return Utility::receive( comm, source_process, tag, const_cast<const Utility::ArrayView<T>&>( value ) );
  }

  //! Forward to the correct ireceive method based on type T
  static inline Communicator::Request ireceive( const Communicator& comm,
                                                int source_process,
                                                int tag,
                                                Utility::ArrayView<T>& value )
  {
    return Utility::ireceive( comm, source_process, tag, const_cast<const Utility::ArrayView<T>&>( value ) );
  }
};

/*! The single value reduce helper class
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SingleValueReduceHelper
{
  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                const T& input_value,
                                T& value,
                                ReduceOperation op )
  {
    Utility::ArrayView<const T> input_value_view( &input_value, 1 );
    Utility::ArrayView<T> value_view( &value, 1 );

    Utility::allReduce( comm,
                        const_cast<const Utility::ArrayView<const T>&>( input_value_view ),
                        const_cast<const Utility::ArrayView<T>&>( value_view ),
                        op );
  }

  //! Forward to the correct scan method based on type T
  template<typename ReduceOperation>
  static inline void scan( const Communicator& comm,
                           const T& input_value,
                           T& value,
                           ReduceOperation op )
  {
    Utility::ArrayView<const T> input_value_view( &input_value, 1 );
    Utility::ArrayView<T> value_view( &value, 1 );

    Utility::scan( comm,
                   const_cast<const Utility::ArrayView<const T>&>( input_value_view ),
                   const_cast<const Utility::ArrayView<T>&>( value_view ),
                   op );
  }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const T& input_value,
                             T& value,
                             ReduceOperation op,
                             int root_process )
  {
    Utility::ArrayView<const T> input_value_view( &input_value, 1 );
    Utility::ArrayView<T> value_view( &value, 1 );

    Utility::reduce( comm,
                     const_cast<const Utility::ArrayView<const T>&>( input_value_view ),
                     const_cast<const Utility::ArrayView<T>&>( value_view ),
                     op,
                     root_process );
  }

  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                T& input_output_value,
                                ReduceOperation op )
  {
    Utility::ArrayView<T> input_output_value_view( &input_output_value, 1 );

    Utility::allReduce( comm,
                        const_cast<const Utility::ArrayView<T>&>( input_output_value_view ),
                        op );
  }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const T& input_value,
                             ReduceOperation op,
                             int root_process )
  {
    Utility::ArrayView<const T> input_value_view( &input_value, 1 );

    Utility::reduce( comm,
                     const_cast<const Utility::ArrayView<const T>&>( input_value_view ),
                     op,
                     root_process );
  }
};

/*! Partial specialization of SingleValueReduceHelper for Utility::ArrayView
 * \ingroup mpi
 */
template<typename T>
struct SingleValueReduceHelper<Utility::ArrayView<T>, typename std::enable_if<!std::is_const<T>::value>::type>
{
  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                const Utility::ArrayView<T>& input_value,
                                Utility::ArrayView<T>& value,
                                ReduceOperation op )
  { Utility::allReduce( comm, input_value.toConst(), value, op ); }

  //! Forward to the correct scan method based on type T
  template<typename ReduceOperation>
  static inline void scan( const Communicator& comm,
                           const Utility::ArrayView<T>& input_value,
                           Utility::ArrayView<T>& value,
                           ReduceOperation op )
  { Utility::scan( comm, input_value.toConst(), value, op ); }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const Utility::ArrayView<T>& input_value,
                             Utility::ArrayView<T>& value,
                             ReduceOperation op,
                             int root_process )
  {
    Utility::reduce( comm,
                     input_value.toConst(),
                     const_cast<const Utility::ArrayView<T>&>(value),
                     op,
                     root_process );
  }

  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                Utility::ArrayView<T>& input_output_value,
                                ReduceOperation op )
  {
    Utility::allReduce( comm, const_cast<const Utility::ArrayView<T>&>( input_output_value ), op );
  }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const Utility::ArrayView<T>& input_values,
                             ReduceOperation op,
                             int root_process )
  { Utility::reduce( comm, input_values.toConst(), op, root_process ); }
};

/*! Partial specialization of SingleValueReduceHelper for std::vector
 * \ingroup mpi
 */
template<typename T>
struct SingleValueReduceHelper<std::vector<T> >
{
  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                const std::vector<T>& input_value,
                                std::vector<T>& value,
                                ReduceOperation op )
  {
    // Resize the output value
    value.resize( input_value.size() );

    Utility::allReduce( comm,
                        Utility::arrayViewOfConst( input_value ),
                        Utility::arrayView( value ),
                        op );
  }

  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void scan( const Communicator& comm,
                           const std::vector<T>& input_value,
                           std::vector<T>& value,
                           ReduceOperation op )
  {
    // Resize the output value
    value.resize( input_value.size() );

    Utility::scan( comm,
                   Utility::arrayViewOfConst( input_value ),
                   Utility::arrayView( value ),
                   op );
  }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const std::vector<T>& input_value,
                             std::vector<T>& value,
                             ReduceOperation op,
                             int root_process )
  {
    // Resize the output value if this is the root process
    if( comm.rank() == root_process )
      value.resize( input_value.size() );

    Utility::reduce( comm,
                     Utility::arrayViewOfConst( input_value ),
                     Utility::arrayView( value ),
                     op,
                     root_process );
  }

  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                std::vector<T>& input_output_value,
                                ReduceOperation op )
  { Utility::allReduce( comm, Utility::arrayView( input_output_value ), op ); }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const std::vector<T>& input_value,
                             ReduceOperation op,
                             int root_process )
  {
    Utility::reduce( comm,
                     Utility::arrayViewOfConst( input_value ),
                     op,
                     root_process );
  }
};

/*! Partial specialization of SingleValueReduceHelper for std::array
 * \ingroup mpi
 */
template<typename T, size_t N>
struct SingleValueReduceHelper<std::array<T,N> >
{
  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                const std::array<T,N>& input_value,
                                std::array<T,N>& value,
                                ReduceOperation op )
  {
    Utility::allReduce( comm,
                        Utility::arrayViewOfConst( input_value ),
                        Utility::arrayView( value ),
                        op );
  }

  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void scan( const Communicator& comm,
                           const std::array<T,N>& input_value,
                           std::array<T,N>& value,
                           ReduceOperation op )
  {
    Utility::scan( comm,
                   Utility::arrayViewOfConst( input_value ),
                   Utility::arrayView( value ),
                   op );
  }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const std::array<T,N>& input_value,
                             std::array<T,N>& value,
                             ReduceOperation op,
                             int root_process )
  {
    Utility::reduce( comm,
                     Utility::arrayViewOfConst( input_value ),
                     Utility::arrayView( value ),
                     op,
                     root_process );
  }

  //! Forward to the correct allReduce method based on type T
  template<typename ReduceOperation>
  static inline void allReduce( const Communicator& comm,
                                std::array<T,N>& input_output_value,
                                ReduceOperation op )
  { Utility::allReduce( comm, Utility::arrayView( input_output_value ), op ); }

  //! Forward to the correct reduce method based on type T
  template<typename ReduceOperation>
  static inline void reduce( const Communicator& comm,
                             const std::array<T,N>& input_value,
                             ReduceOperation op,
                             int root_process )
  {
    Utility::reduce( comm,
                     Utility::arrayViewOfConst( input_value ),
                     op,
                     root_process );
  }
};

/*! The single value broadcast helper class
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SingleValueBroadcastHelper
{
  //! Forward to the correct broadcast method based on type T
  static inline void broadcast( const Communicator& comm,
                                T& value,
                                int root_process )
  {
    Utility::ArrayView<T> value_view( &value, 1 );

    Utility::broadcast( comm,
                        const_cast<const Utility::ArrayView<T>&>( value_view ),
                        root_process );
  }
};

/*! Partial specialization of SingleValueBroadcastHelper for Utility::ArrayView
 * \ingroup mpi
 */
template<typename T>
struct SingleValueBroadcastHelper<Utility::ArrayView<T>, typename std::enable_if<!std::is_const<T>::value>::type>
{
  //! Forward to the correct broadcast method based on type T
  static inline void broadcast( const Communicator& comm,
                                Utility::ArrayView<T>& value,
                                int root_process )
  {
    Utility::broadcast( comm,
                        const_cast<const Utility::ArrayView<T>&>( value ),
                        root_process );
  }
};

/*! The single value gather helper class
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SingleValueGatherHelper
{
  //! Forward to the correct gather method based on type T
  static inline void gather( const Communicator& comm,
                             const T& input_value,
                             int root_process )
  {
    Utility::ArrayView<const T> input_value_view( &input_value, 1 );

    Utility::gather( comm,
                     const_cast<const Utility::ArrayView<const T>&>( input_value_view ),
                     root_process );
  }

  //! Forward to the correct gatherv method based on type T
  static inline void gatherv( const Communicator& comm,
                              const T& input_value,
                              int root_process )
  {
    Utility::ArrayView<const T> input_value_view( &input_value, 1 );

    Utility::gatherv( comm,
                      const_cast<const Utility::ArrayView<const T>&>( input_value_view ),
                      root_process );
  }
};

/*! Partial specialization of SingleValueGatherHelper for Utility::ArrayView
 * \ingroup mpi
 */
template<typename T>
struct SingleValueGatherHelper<Utility::ArrayView<T>, typename std::enable_if<!std::is_const<T>::value>::type>
{
  //! Forward to the correct gather method based on type T
  static inline void gather( const Communicator& comm,
                             const Utility::ArrayView<T>& input_value,
                             int root_process )
  { Utility::gather( comm, input_value.toConst(), root_process ); }

  //! Forward to the correct gatherv method based on type T
  static inline void gatherv( const Communicator& comm,
                              const Utility::ArrayView<T>& input_value,
                              int root_process )
  { Utility::gatherv( comm, input_value.toConst(), root_process ); }
};

/*! The single value gather helper class
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SingleValueScatterHelper
{
  //! Forward to the correct scatter method based on type T
  static inline void scatter( const Communicator& comm,
                              T& output_value,
                              int root_process )
  {
    Utility::ArrayView<T> output_value_view( &output_value, 1 );

    Utility::scatter( comm,
                      const_cast<const Utility::ArrayView<T>&>( output_value_view ),
                      root_process );
  }

  //! Forward to the correct scatterv method based on type T
  static inline void scatterv( const Communicator& comm,
                               T& output_value,
                               int root_process )
  {
    Utility::ArrayView<T> output_value_view( &output_value, 1 );

    Utility::scatterv( comm,
                       const_cast<const Utility::ArrayView<T>&>( output_value_view ),
                       root_process );
  }
};

/*! Partial specialization of SingleValueScatterHelper for Utility::ArrayView
 * \ingroup mpi
 */
template<typename T>
struct SingleValueScatterHelper<Utility::ArrayView<T>,typename std::enable_if<!std::is_const<T>::value>::type>
{
  //! Forward to the correct scatter method based on type T
  static inline void scatter( const Communicator& comm,
                              Utility::ArrayView<T>& output_value,
                              int root_process )
  {
    Utility::scatter( comm,
                      const_cast<const Utility::ArrayView<T>&>( output_value ),
                      root_process );
  }

  //! Forward to the correct scatterv method based on type T
  static inline void scatterv( const Communicator& comm,
                               Utility::ArrayView<T>& output_value,
                               int root_process )
  {
    Utility::scatterv( comm,
                       const_cast<const Utility::ArrayView<T>&>(output_value),
                       root_process );
  }
};

} // end Details namespace

// Send data to another process
/*! \details The value on the calling process of the communicator will be
 * sent with tag to destination_process of the communicator.This operation will
 * block until the destination process receives the value. This operation can
 * only be done with communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline void send( const Communicator& comm,
                  int destination_process,
                  int tag,
                  const T& value )
{
  Details::SingleValueSendHelper<T>::send( comm, destination_process, tag, value );
}

// Send a std::initializer_list of data to another process
/*! \details The underlying values of the initializer list on the calling
 * process of the communicator will be sent with tag to destination_process of
 * the communicator. This operation will block until the destination process
 * receives the values. This operation can only be done with communicators of
 * size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline void send( const Communicator& comm,
                  int destination_process,
                  int tag,
                  std::initializer_list<T> values )
{
  Utility::ArrayView<const T> init_list_view( values.begin(), values.size() );

  Utility::send( comm, destination_process, tag, init_list_view );
}

// Send a Utility::ArrayView of data to another process
/*! \details The underlying values of the array view on the calling
 * process of the communicator will be sent with tag to destination_process of
 * the communicator. This operation will block until the destination process
 * receives the values. This operation can only be done with communicators of
 * size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline void send( const Communicator& comm,
                  int destination_process,
                  int tag,
                  const Utility::ArrayView<const T>& values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Blocking send operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator* const mpi_comm =
    dynamic_cast<const MPICommunicator* const>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  try{
    mpi_comm->send( destination_process, tag, values.data(), values.size() );
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
inline Communicator::Status receive( const Communicator& comm,
                                     int source_process,
                                     int tag,
                                     T& value )
{
  return Details::SingleValueReceiveHelper<T>::receive( comm, source_process, tag, value );
}

// Receive an array of data from another process
/*! \details The values on the calling process of the communicator will be
 * received with tag from source_process of the communicator. This operation
 * will block until the source process sends the values. This
 * operation can only be done with communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline Communicator::Status receive( const Communicator& comm,
                                     int source_process,
                                     int tag,
                                     const ArrayView<T>& values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Blocking receive operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator* const mpi_comm =
    dynamic_cast<const MPICommunicator* const>( &comm );

  Communicator::Status status;

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  try{
    status =
      mpi_comm->recv( source_process, tag, values.data(), values.size() );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct blocking receive "
                              "operation from source process "
                              << source_process << " with tag " << tag <<
                              " successfully!" );

  return status;
}

// Send a data to another process without blocking
/*! \details The value on the calling process of the communicator will be
 * sent with tag to destination_process of the communicator. This operation
 * will not block. Use the returned request to determine when the destination
 * process has received the value. This operation can only be done with
 * communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
inline Communicator::Request isend( const Communicator& comm,
                                    int destination_process,
                                    int tag,
                                    const T& value )
{
  return Details::SingleValueSendHelper<T>::isend( comm, destination_process, tag, value );
}

// Send an array of data to another process without blocking
/*! \details The values on the calling process of the communicator will be
 * sent with tag to destination_process of the communicator. This operation
 * will not block. Use the returned request to determine when the destination
 * process has received the values. This operation can only be done with
 * communicators of size two or greater.
 * \ingroup mpi
 */
template<typename T>
Communicator::Request isend( const Communicator& comm,
                             int destination_process,
                             int tag,
                             const ArrayView<const T>& values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Non-blocking send operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator* const mpi_comm =
    dynamic_cast<const MPICommunicator* const>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  Communicator::Request request;

  try{
    request =
      mpi_comm->isend( destination_process, tag, values.data(), values.size() );
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
inline Communicator::Request ireceive( const Communicator& comm,
                                       int source_process,
                                       int tag,
                                       T& value )
{
  return Details::SingleValueReceiveHelper<T>::ireceive( comm, source_process, tag, value );
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
Communicator::Request ireceive( const Communicator& comm,
                                int source_process,
                                int tag,
                                const Utility::ArrayView<T>& values )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Non-blocking receive operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator* const mpi_comm =
    dynamic_cast<const MPICommunicator* const>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  Communicator::Request request;

  try{
    request = mpi_comm->irecv( source_process, tag, values.data(), values.size() );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did not conduct non-blocking receive "
                              "operation from source process "
                              << source_process << " with tag " << tag <<
                              " successfully!" );
  return request;
}

// Wait until a message is available to be received
/*! \details The calling process of the communicator will wait until
 * source_process of the communicator has sent a message with tag. Use the
 * returned status to determine the message details before conducting
 * a receive operation. This operation will block until the source
 * process sends a message to the calling process. This operation can only be
 * done with communicators of size two or greater.
 * \warning When probing types that must be serialized before they can be sent
 * the returned status object will not have a count that reflects the number
 * of objects of that type that were sent. This is because the implementation
 * of the send and isend operations may require multiple MPI send operations,
 * each of which only sends a part of the object data.
 * \ingroup mpi
 */
template<typename T>
Communicator::Status probe( const Communicator& comm,
                            int source_process,
                            int tag )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Blocking probe operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator* const mpi_comm =
    dynamic_cast<const MPICommunicator* const>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  if( !std::is_arithmetic<T>::value )
  {
    FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                "Utility::probe will only return the correct "
                                "count for arithmetic types." );
  }

  Communicator::Status status;

  try{
    status = mpi_comm->probe<T>( source_process, tag );
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
template<typename T>
inline Communicator::Status probe( const Communicator& comm, int tag )
{
  return Utility::probe<T>( comm, comm.anySourceValue(), tag );
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
template<typename T>
inline Communicator::Status probe( const Communicator& comm )
{
  return Utility::probe<T>( comm, comm.anySourceValue(), comm.anyTagValue() );
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
template<typename T>
Communicator::Status iprobe( const Communicator& comm,
                             int source_process,
                             int tag )
{
  TEST_FOR_EXCEPTION( comm.size() <= 1,
                      InvalidCommunicator,
                      "Non-blocking probe operations can only be done with "
                      "communicators of size 2 or greater!" );

  const MPICommunicator* const mpi_comm =
    dynamic_cast<const MPICommunicator* const>( &comm );

  TEST_FOR_EXCEPTION( mpi_comm == NULL,
                      InvalidCommunicator,
                      "An unknown communicator type was encountered!" );

  if( !std::is_arithmetic<T>::value )
  {
    FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                "Utility::iprobe will only return the correct "
                                "count for arithmetic types." );
  }

  Communicator::Status status;

  try{
    status = mpi_comm->iprobe<T>( source_process, tag );
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
template<typename T>
inline Communicator::Status iprobe( const Communicator& comm, int tag )
{
  return Utility::iprobe<T>( comm, comm.anySourceValue(), tag );
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
template<typename T>
inline Communicator::Status iprobe( const Communicator& comm )
{
  return Utility::iprobe<T>( comm, comm.anySourceValue(), comm.anyTagValue() );
}

// Wait for the requests to finish
/*! \details The calling process will wait until all of the requests have
 * completed. The returned statuses can be used to determine the details of
 * each completed request.
 * \ingroup mpi
 */
template<template<typename T,typename...> class STLCompliantInputSequenceContainer,
         template<typename T,typename...> class STLCompliantOutputSequenceContainer>
void wait( STLCompliantInputSequenceContainer<Communicator::Request>& requests,
           STLCompliantOutputSequenceContainer<Communicator::Status>& statuses )
{
  // Resize the statuses array
  statuses.resize( requests.size() );

  for( size_t i = 0; i < requests.size(); ++i )
  {
    try{
      statuses[i] = requests[i].wait();
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                "A request was not able to wait for the for "
                                "the operation to complete!" );
  }
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
  Utility::ArrayView<const T> input_value_view( &input_value, 1 );

  Utility::allGather( comm, input_value_view, output_values );
}

// Gather the values stored at every process into vectors of values
// from each process.
/*! \details The input_value on every process of the communicator will be
 * collected in the output_values vector on every process. The input_value
 * associated with a process will be located at the index that is equal to the
 * process's rank. The output_values view must be sized appropriately before
 * passing it to this method. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       const T& input_value,
                       const Utility::ArrayView<T>& output_values )
{
  Utility::ArrayView<const T> input_value_view( &input_value, 1 );

  Utility::allGather( comm, input_value_view, output_values );
}

// Gather the values stored at every process into an array of values
// from each process.
/*! \details The input_values on every process of the communicator will be
 * collected in the output_values vector on every process. The input_values
 * may be passed in as a brace-initialized list (e.g. {1, 2, ..., 10}). The
 * input_values associated with a process will start at the index that is equal
 * to the process's rank multiplied by the number of input values. The
 * output_values vector will be resized appropriately. This operation can be
 * done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       std::initializer_list<T> input_values,
                       std::vector<T>& output_values )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::allGather( comm, input_values_view, output_values );
}

// Gather the values stored at every process into an array of values
// from each process.
/*! \details The input_values on every process of the communicator will be
 * collected in the output_values array on every process. The input_values
 * may be passed in as a brace-initialized list (e.g. {1, 2, ..., 10}). The
 * input_values associated with a process will start at the index that is equal
 * to the process's rank multiplied by the number of input values. The
 * output_values array must be sized appropriately before passing it in to this
 * method. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       std::initializer_list<T> input_values,
                       const Utility::ArrayView<T>& output_values )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::allGather( comm, input_values_view, output_values );
}

// Gather the values stored at every process into an array of values
// from each process.
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       const Utility::ArrayView<T>& input_values,
                       std::vector<T>& output_values )
{
  Utility::allGather( comm, input_values.toConst(), output_values );
}

// Gather the values stored at every process into an array of values
// from each process.
/*! \details The input_values on every process of the communicator will be
 * collected in the output_values vector on every process. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by the number of input values. The output_values
 * vector will be resized appropriately. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       const Utility::ArrayView<const T>& input_values,
                       std::vector<T>& output_values )
{
  // Resize the output values vector
  output_values.resize( input_values.size()*comm.size() );

  Utility::allGather( comm, input_values, Utility::arrayView(output_values) );
}

// Gather the values stored at every process into an array of values
// from each process.
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void allGather( const Communicator& comm,
                       const Utility::ArrayView<T>& input_values,
                       const Utility::ArrayView<T>& output_values )
{
  Utility::allGather( comm, input_values.toConst(), output_values );
}

// Gather the values stored at every process into an array of values
// from each process.
/*! \details The input_values on every process of the communicator will be
 * collected in the output_values array on every process. The input_values
 * associated with a process will start at the index that is equal to the
 * process's rank multiplied by the number of input values. The output_values
 * array must be sized appropriately before passing it in to this method. This
 * operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void allGather( const Communicator& comm,
                const Utility::ArrayView<const T>& input_values,
                const Utility::ArrayView<T>& output_values )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->allGather( input_values.data(), input_values.size(), output_values.data() );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allGather "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The input_value on every process of the communicator will be
 * reduced in the output_value on every process. It is acceptable to pass
 * in std::vector and std::array types to this method. The reduce operation
 * will be applied to each element and stored in the output_value container.
 * A std::vector output_value will be sized appropriately. This operation can
 * be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void allReduce( const Communicator& comm,
                       const T& input_value,
                       T& output_value,
                       ReduceOperation op )
{
  Details::SingleValueReduceHelper<T>::allReduce( comm, input_value, output_value, op );
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The input_output_value on every process of the communicator will
 * be reduced inline on every process. It is acceptable to pass in std::vector
 * and std::array types to this method. The reduce operation will be applied to
 * each element and stored in the output_value container. This operation can be
 * done with communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void allReduce( const Communicator& comm,
                       T& input_output_value,
                       ReduceOperation op )
{
  Details::SingleValueReduceHelper<T>::allReduce( comm, input_output_value, op );
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void allReduce( const Communicator& comm,
                       const Utility::ArrayView<T>& input_values,
                       const Utility::ArrayView<T>& output_values,
                       ReduceOperation op )
{ Utility::allReduce( comm, input_values.toConst(), output_values, op ); }

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
                const Utility::ArrayView<const T>& input_values,
                const Utility::ArrayView<T>& output_values,
                ReduceOperation op )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    TEST_FOR_EXCEPTION( output_values.size() < input_values.size(),
                        CommunicationError,
                        comm << " could not conduct allReduce operation "
                        "because the output array is not large enough!" );

    try{
      mpi_comm->allReduce( input_values.data(), input_values.size(), output_values.data(), op );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allReduce "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
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
                const Utility::ArrayView<T>& input_output_values,
                ReduceOperation op )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->allReduce( input_output_values.data(), input_output_values.size(), op );
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

// Send data from every process to every other process
/*! \details This method is provided to help with overload resolution
 * \ingroup mpi
 */
template<typename T>
inline void allToAll( const Communicator& comm,
                      const Utility::ArrayView<T>& input_values,
                      std::vector<T>& output_values )
{
  Utility::allToAll( comm, input_values.toConst(), output_values );
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
                      const Utility::ArrayView<const T>& input_values,
                      std::vector<T>& output_values )
{
  // Resize the output values
  output_values.resize( input_values.size() );

  Utility::allToAll( comm, input_values, Utility::arrayView(output_values) );
}

// Send data from every process to every other process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void allToAll( const Communicator& comm,
                      const Utility::ArrayView<T>& input_values,
                      const Utility::ArrayView<T>& output_values )
{
  Utility::allToAll( comm, input_values.toConst(), output_values );
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
               const Utility::ArrayView<const T>& input_values,
               const Utility::ArrayView<T>& output_values )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      int values_to_send_per_proc;

      if( input_values.size() != 0 )
        values_to_send_per_proc = input_values.size()/comm.size();
      else
        values_to_send_per_proc = 0;

      mpi_comm->allToAll( input_values.data(), values_to_send_per_proc, output_values.data() );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct allToAll "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
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
  Details::SingleValueBroadcastHelper<T>::broadcast( comm, value, root_process );
}

// Broadcast a value from a root process to all other processes
/*! \details The values on the root process of the communicator will be sent
 * to all other processes of the communicator. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void broadcast( const Communicator& comm,
                const Utility::ArrayView<T>& values,
                int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->broadcast( values.data(), values.size(), root_process );
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

    if( root_process != comm.rank() )
    {
      FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                  "The only process available for the "
                                  "broadcast operation is "
                                  << comm.rank() << "! The requested root "
                                  "process " << root_process <<
                                  " will be ignored!" );
    }
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
  Utility::ArrayView<const T> input_value_view( &input_value, 1 );

  Utility::gather( comm, input_value_view, output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The value on every process of the communicator will be sent
 * to root_process of the communicator. The output_values must be sized
 * appropriately before being passed to this method. The value sent by a
 * process will be located at the index in output_values that is equal to the
 * process's rank. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const T& input_value,
                    const Utility::ArrayView<T>& output_values,
                    int root_process )
{
  Utility::ArrayView<const T> input_value_view( &input_value, 1 );

  Utility::gather( comm, input_value_view, output_values, root_process );
}

// Gather the value stored at every process into a vector at the root process
/*! \details The value on every process of the communicator will be sent
 * to root_process of the communicator. This version of the gather method can
 * only be called by non-root processes (since the output values array is not
 * needed).
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const T& input_value,
                    int root_process )
{
  Details::SingleValueGatherHelper<T>::gather( comm, input_value, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The input_values can be passed in
 * as a brace-initialized list (e.g. {1, 2, ..., 10}). The output_values will
 * be resized appropriately. The values sent by a process will start at the
 * index in output_values that is equal to the process's rank multiplied by
 * number_of_input_values. This operation can be done with communicators of any
 * size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    std::initializer_list<T> input_values,
                    std::vector<T>& output_values,
                    int root_process )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::gather( comm, input_values_view, output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The input_values can be passed in
 * as a brace-initialized list (e.g. {1, 2, ..., 10}). The output_values must
 * be sized appropriately before passing it to this method. The values sent by
 * a process will start at the index in output_values that is equal to the
 * process's rank multiplied by number_of_input_values. This operation can be
 * done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    std::initializer_list<T> input_values,
                    const Utility::ArrayView<T>& output_values,
                    int root_process )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::gather( comm, input_values_view, output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on every process of the communicator will be sent
 * to root_process of the communicator. The input_values can be passed in
 * as a brace-initialized list (e.g. {1, 2, ..., 10}). This version of the
 * gather method can only be called by non-root processes (since the output
 * values array is not needed).
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    std::initializer_list<T> input_values,
                    int root_process )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::gather( comm, input_values_view, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const Utility::ArrayView<T>& input_values,
                    std::vector<T>& output_values,
                    int root_process )
{
  Utility::gather( comm, input_values.toConst(), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values on every process of the communicator will be sent
 * to root_process of the communicator. The output_values will be resized
 * appropriately. The values sent by a process will start at the index in
 * output_values that is equal to the process's rank multiplied by the
 * number of input values. This operation can be done with communicators of any
 * size.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const Utility::ArrayView<const T>& input_values,
                    std::vector<T>& output_values,
                    int root_process )
{
  // Resize the output values vector if we're on the root process
  if( comm.rank() == root_process )
    output_values.resize( input_values.size()*comm.size() );

  Utility::gather( comm, input_values, Utility::arrayView(output_values), root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
void gather( const Communicator& comm,
             const Utility::ArrayView<T>& input_values,
             const Utility::ArrayView<T>& output_values,
             int root_process )
{
  Utility::gather( comm, input_values.toConst(), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values on every process of the communicator will be sent
 * to root_process of the communicator. The output_values must be sized
 * appropriately before passing it to this method. The values sent by a process
 * will start at the index in output_values that is equal to the process's rank
 * multiplied by the number of input values. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void gather( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             const Utility::ArrayView<T>& output_values,
             int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->gather( input_values.data(), input_values.size(), output_values.data(), root_process );
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

    if( root_process != comm.rank() )
    {
      FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                  "The only process available for the "
                                  "gather operation is " << comm.rank() << "! "
                                  "The requested root process "
                                  << root_process <<
                                  " will be ignored!" );
    }

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const Utility::ArrayView<T>& input_values,
                    int root_process )
{
  Utility::gather( comm, input_values.toConst(), root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values on every process of the communicator will be sent
 * to root_process of the communicator. This version of the gather method can
 * only be called by non-root processes (since the output values array is not
 * needed).
 * \ingroup mpi
 */
template<typename T>
inline void gather( const Communicator& comm,
                    const Utility::ArrayView<const T>& input_values,
                    int root_process )
{
  TEST_FOR_EXCEPTION( comm.rank() == root_process,
                      CommunicationError,
                      "Root process " << root_process << " of " << comm <<
                      " attempted to call Utility::gather method reserved for "
                      "non-root processes!" );

  Utility::gather( comm, input_values, Utility::ArrayView<T>(), root_process );
}

namespace Details{

/*! Determine the number of values that each process will send
 * \ingroup mpi
 */
inline void gathervGetSizes( const Communicator& comm,
                             const int local_size,
                             std::vector<int>& sizes )
{
  try{
    Utility::allGather( comm, local_size, sizes );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              CommunicationError,
                              comm << " did could not conduct gatherv "
                              "operation because the number of "
                              "elements sent by each process could not be "
                              "determined!" );
}

/*! Gather the values stored at every process into a vector at the root process
 * \ingroup mpi
 */
template<typename T>
void gathervImpl( const Communicator& comm,
                  const Utility::ArrayView<const T>& input_values,
                  const Utility::ArrayView<T>& output_values,
                  const std::vector<int>& sizes,
                  const int root_process )
{
  if( comm.rank() == root_process )
  {
    int total_size = 0;

    for( size_t i = 0; i < sizes.size(); ++i )
      total_size += sizes[i];

    TEST_FOR_EXCEPTION( output_values.size() < total_size,
                        CommunicationError,
                        comm << " could not conduct gatherv operation because "
                        "the output array is not large enough!" );
  }

  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->gatherv( input_values.data(), input_values.size(), output_values.data(), sizes, root_process );
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

    if( root_process != comm.rank() )
    {
      FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                  "The only process available for the "
                                  "gatherv operation is " << comm.rank() << "!"
                                  " The requested root process "
                                  << root_process <<
                                  " will be ignored!" );
    }

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
}

} // end Details namespace

// Gather the values stored at every process into a vector at the root process
/*! \details The input_value on this process of the communicator will be sent
 * to root_process of the communicator. The output_values will be resized
 * appropriately. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const T& input_value,
                     std::vector<T>& output_values,
                     int root_process )
{
  Utility::gatherv( comm, Utility::ArrayView<const T>( &input_value, 1 ), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. The output_values must be sized
 * appropriately before passing it to this method. This operation can be done
 * with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const T& input_value,
                     const Utility::ArrayView<T>& output_values,
                     int root_process )
{
  Utility::gatherv( comm, Utility::ArrayView<const T>( &input_value, 1 ), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. The output_values will be resized
 * appropriately. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     std::initializer_list<T> input_values,
                     std::vector<T>& output_values,
                     int root_process )
{
  Utility::gatherv( comm, Utility::ArrayView<const T>( input_values.begin(), input_values.end() ), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. The output_values must be sized
 * appropriately before passing it to this method. This operation can be done
 * with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     std::initializer_list<T> input_values,
                     const Utility::ArrayView<T>& output_values,
                     int root_process )
{
  Utility::gatherv( comm, Utility::ArrayView<const T>( input_values.begin(), input_values.end() ), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const Utility::ArrayView<T>& input_values,
                     std::vector<T>& output_values,
                     const int root_process )
{
  Utility::gatherv( comm, input_values.toConst(), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. The output_values will be resized
 * appropriately. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void gatherv( const Communicator& comm,
                     const Utility::ArrayView<const T>& input_values,
                     std::vector<T>& output_values,
                     const int root_process )
{
  // Get the size of the gathered values on each process
  std::vector<int> sizes;

  Details::gathervGetSizes( comm, input_values.size(), sizes );

  // Resize the output values vector
  if( comm.rank() == root_process )
  {
    int total_size = 0;

    for( size_t i = 0; i < sizes.size(); ++i )
      total_size += sizes[i];

    output_values.resize( total_size );
  }

  Details::gathervImpl( comm, input_values, Utility::arrayView(output_values), sizes, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const Utility::ArrayView<T>& input_values,
                     const Utility::ArrayView<T>& output_values,
                     int root_process )
{
  Utility::gatherv( comm, input_values.toConst(), output_values, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. The output_values must be sized
 * appropriately before passing it to this method. This operation can be done
 * with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void gatherv( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              const Utility::ArrayView<T>& output_values,
              int root_process )
{
  // Get the size of the gathered values on each process
  std::vector<int> sizes;

  Details::gathervGetSizes( comm, input_values.size(), sizes );

  // Gather the values on the root process
  Details::gathervImpl( comm, input_values, output_values, sizes, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_value on this process of the communicator will be sent
 * to root_process of the communicator. This version of the gatherv method can
 * only be called by non-root processes (since the output values are not
 * needed)
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const T& input_value,
                     const int root_process )
{
  Details::SingleValueGatherHelper<T>::gatherv( comm, input_value, root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. The input_values can be passed in as
 * a brace-initialized list (e.g. {1, 2, ..., 10}). This version of the gatherv
 * method can only be called by non-root processes (since the output values
 * are not needed).
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     std::initializer_list<T> input_values,
                     const int root_process )
{
  Utility::gatherv( comm, Utility::ArrayView<const T>( input_values.begin(), input_values.end() ), root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void gatherv( const Communicator& comm,
                     const Utility::ArrayView<T>& input_values,
                     const int root_process )
{
  Utility::gatherv( comm, input_values.toConst(), root_process );
}

// Gather the values stored at every process into a vector at the root process
/*! \details The input_values on this process of the communicator will be sent
 * to root_process of the communicator. This version of the gatherv method can
 * only be called by non-root processes (since the output values are not
 * needed).
 * \ingroup mpi
 */
template<typename T>
void gatherv( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              const int root_process )
{
  TEST_FOR_EXCEPTION( comm.rank() == root_process,
                      CommunicationError,
                      "Root process " << root_process << " of " << comm <<
                      " attempted to call Utility::gatherv method reserved "
                      "for non-root processes!" );

  Utility::gatherv( comm, input_values, Utility::ArrayView<T>(), root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The values that a process
 * receives from the root process will be from the input values array
 * starting at the index that is equal to the process's rank multiplied by
 * number of values sent to each process
 * (i.e. input_values.size()/comm.size()). This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     std::initializer_list<T> input_values,
                     T& output_value,
                     int root_process )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::ArrayView<T> output_value_view( &output_value, 1 );

  Utility::scatter( comm, input_values_view, output_value_view, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details This method is provided to help with overload resolution.
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     const Utility::ArrayView<T>& input_values,
                     T& output_value,
                     int root_process )
{
  Utility::ArrayView<T> output_value_view( &output_value, 1 );

  Utility::scatter( comm, input_values.toConst(), output_value_view, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The values that a process
 * receives from the root process will be from the input values array
 * starting at the index that is equal to the process's rank multiplied by
 * number of values sent to each process
 * (i.e. input_values.size()/comm.size()). This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     const Utility::ArrayView<const T>& input_values,
                     T& output_value,
                     int root_process )
{
  Utility::ArrayView<T> output_value_view( &output_value, 1 );

  Utility::scatter( comm, input_values, output_value_view, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. This version of the
 * scatter method can only be called by non-root processes (since the
 * input values array is not needed).
 * \ingroup mpi
 */
template<typename T>
void scatter( const Communicator& comm,
              T& output_value,
              int root_process )
{
  Details::SingleValueScatterHelper<T>::scatter( comm, output_value, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The values that a process
 * receives from the root process will be from the input values array
 * starting at the index that is equal to the process's rank multiplied by
 * number of values sent to each process
 * (i.e. input_values.size()/comm.size()). This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     std::initializer_list<T> input_values,
                     const Utility::ArrayView<T>& output_values,
                     int root_process )
{
  Utility::ArrayView<const T>
    input_values_view( input_values.begin(), input_values.size() );

  Utility::scatter( comm, input_values_view, output_values, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void scatter( const Communicator& comm,
                     const Utility::ArrayView<T>& input_values,
                     const Utility::ArrayView<T>& output_values,
                     int root_process )
{
  Utility::scatter( comm, input_values.toConst(), output_values, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The values that a process
 * receives from the root process will be from the input values array
 * starting at the index that is equal to the process's rank multiplied by
 * number of values sent to each process
 * (i.e. input_values.size()/comm.size()). This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void scatter( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              const Utility::ArrayView<T>& output_values,
              int root_process )
{
  if( comm.rank() == root_process )
  {
    TEST_FOR_EXCEPTION( input_values.size() < comm.size(),
                        CommunicationError,
                        comm << " could not conduct scatter operation from "
                        "the root process because there were not enough input "
                        "values provided!" );
  }

  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    // Determine the number of values that will be sent to each process
    int number_of_values_per_proc = 0;

    if( comm.rank() == root_process )
      number_of_values_per_proc = input_values.size()/comm.size();

    try{
      mpi_comm->broadcast( &number_of_values_per_proc, 1, root_process );

      TEST_FOR_EXCEPTION( output_values.size() < number_of_values_per_proc,
                          CommunicationError,
                          "The output values array does not have "
                          "sufficient space to store the scattered values!" );

      mpi_comm->scatter( input_values.data(), output_values.data(), number_of_values_per_proc, root_process );
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

    if( root_process != comm.rank() )
    {
      FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                  "The only process available for the "
                                  "scatter operation is " << comm.rank() << "!"
                                  " The requested root process "
                                  << root_process <<
                                  " will be ignored!" );
    }

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. This version of the
 * scatter method can only be called by non-root processes (since the
 * input values array is not needed).
 * \ingroup mpi
 */
template<typename T>
void scatter( const Communicator& comm,
              const Utility::ArrayView<T>& output_values,
              int root_process )
{
  TEST_FOR_EXCEPTION( comm.rank() == root_process,
                      CommunicationError,
                      "Root process " << root_process << " of " << comm <<
                      " attempted to call Utility::scatter method reserved "
                      "for non-root processes!" );

  Utility::scatter( comm, Utility::ArrayView<const T>(), output_values, root_process );
}

namespace Details{

/*! Get the number of values that will be sent to this process
 * \ingroup mpi
 */
inline void scattervGetSizes( const Communicator& comm,
                              std::vector<int>& sizes,
                              int root_process )
{
  Utility::broadcast( comm, sizes, root_process );

  TEST_FOR_EXCEPTION( sizes.size() < comm.size(),
                      CommunicationError,
                      comm << " could not conduct scatterv operation "
                      "from root process " << root_process << " because the "
                      "number of values to send to each process could not "
                      "be determined!" );
}

/*! Scatter the values stored at the root process to all other processes
 *
 * The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The range of values that a
 * process receives from the root process will be determined by the sizes
 * array. This operation can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void scattervImpl( const Communicator& comm,
                   const Utility::ArrayView<const T>& input_values,
                   const std::vector<int>& sizes,
                   const Utility::ArrayView<T>& output_values,
                   int root_process )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->scatterv( input_values.data(), sizes, output_values.data(), output_values.size(), root_process );
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

    if( root_process != comm.rank() )
    {
      FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                  "The only process available for the "
                                  "scatterv operation is " << comm.rank() <<
                                  "! The requested root process "
                                  << root_process <<
                                  " will be ignored!" );
    }

    if( input_values.size() < output_values.size() )
    {
      Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
    }
    else
    {
      Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), output_values.size(), output_values.data() );
    }
  }
}

} // end Details namespace

// Scatter the values stored at the root process to all other processes
/*! \details This method is provided to help with overload resolution.
 * \ingroup mpi
 */
template<typename T>
inline void scatterv( const Communicator& comm,
                      const Utility::ArrayView<T>& input_values,
                      const std::vector<int>& sizes,
                      std::vector<T>& output_values,
                      int root_process )
{
  Utility::scatterv( comm, input_values.toConst(), sizes, output_values, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input_values on root_process of the communicator will be
 * sent to every other process in the communicator. The range of values that a
 * process receives from the root process will be determined by the sizes
 * array. The output_values vector will be resize appropriately. This operation
 * can be done with communicators of any size.
 * \ingroup mpi
 */
template<typename T>
void scatterv( const Communicator& comm,
               const Utility::ArrayView<const T>& input_values,
               const std::vector<int>& sizes,
               std::vector<T>& output_values,
               int root_process )
{
  std::vector<int> sizes_copy = sizes;

  Details::scattervGetSizes( comm, sizes_copy, root_process );

  output_values.resize( sizes_copy[comm.rank()] );

  Details::scattervImpl( comm, input_values, sizes_copy, Utility::arrayView(output_values), root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details This method is provided to help with overload resolution
 * \ingroup mpi
 */
template<typename T>
inline void scatterv( const Communicator& comm,
                      const Utility::ArrayView<T>& input_values,
                      const std::vector<int>& sizes,
                      const Utility::ArrayView<T>& output_values,
                      int root_process )
{
  Utility::scatterv( comm, input_values.toConst(), sizes, output_values, root_process );
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
               const Utility::ArrayView<const T>& input_values,
               const std::vector<int>& sizes,
               const Utility::ArrayView<T>& output_values,
               int root_process )
{
  std::vector<int> sizes_copy = sizes;

  Details::scattervGetSizes( comm, sizes_copy, root_process );

  // Chop the array view so that is has the correct size
  if( output_values.size() >= sizes_copy[comm.rank()] )
  {

    Details::scattervImpl( comm, input_values, sizes_copy, output_values( 0, sizes_copy[comm.rank()] ), root_process );
  }
  // The output values array does not have the correct size
  else
  {
    THROW_EXCEPTION( CommunicationError,
                     comm << " could not conduct the scatterv operation "
                     "because the output array is too small!" );
  }
}

// Scatter the values stored at the root process to all other processes
/*! \details The input values on root_process of the communicator will be
 * sent to every other process in the communicator. The output_values vector
 * will be resize appropriately. This method can only be called by non-root
 * processes (since the input values are not needed).
 * \ingroup mpi
 */
template<typename T>
inline void scatterv( const Communicator& comm,
                      std::vector<T>& output_values,
                      int root_process )
{
  Utility::scatterv( comm, Utility::ArrayView<const T>(), std::vector<int>(), output_values, root_process );
}

// Scatter the values stored at the root process to all other processes
/*! \details The input values on root_process of the communicator will be
 * sent to every other process in the communicator. The output_values array
 * must be sized appropriately before passing it to this method. This method
 * can only be called by non-root processes (since the input values are not
 * needed).
 * \ingroup mpi
 */
template<typename T>
void scatterv( const Communicator& comm,
               const Utility::ArrayView<T>& output_values,
               int root_process )
{
  Utility::scatterv( comm, Utility::ArrayView<const T>(), std::vector<int>(), output_values, root_process );
}

// Combine the values stored by each process into a single value at the root
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
  Details::SingleValueReduceHelper<T>::reduce( comm, input_value, output_value, op, root_process );
}

// Combine the values stored by each process into a single value at the root
/*! \details The input_values on every process of the communicator will be
 * reduced on root_process of the communicator. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             std::initializer_list<T> input_values,
             const Utility::ArrayView<T>& output_values,
             ReduceOperation op,
             int root_process )
{
  Utility::reduce( comm, Utility::ArrayView<const T>( input_values.begin(), input_values.end() ), output_values, op, root_process );
}

// Combine the values stored by each process into a single value at the root
/*! \details This method is provided to help with overload resolution
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void reduce( const Communicator& comm,
                    const Utility::ArrayView<T>& input_values,
                    const Utility::ArrayView<T>& output_values,
                    ReduceOperation op,
                    int root_process )
{
  Utility::reduce( comm, input_values.toConst(), output_values, op, root_process );
}

// Combine the values stored by each process into a single value at the root
/*! \details The input_values on every process of the communicator will be
 * reduced on root_process of the communicator. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             const Utility::ArrayView<T>& output_values,
             ReduceOperation op,
             int root_process )
{
  if( comm.rank() == root_process )
  {
    TEST_FOR_EXCEPTION( output_values.size() < input_values.size(),
                        CommunicationError,
                        comm << " could not conduct reduce operation from "
                        "the root process because the output values array is "
                        "not large enough!" );
  }

  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    try{
      mpi_comm->reduce( input_values.data(), input_values.size(), output_values.data(), op, root_process );
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

    if( root_process != comm.rank() )
    {
      FRENSIE_LOG_TAGGED_WARNING( Utility::toString(comm),
                                  "The only process available for the "
                                  "reduce operation is " << comm.rank() << "! "
                                  "The requested root process "
                                  << root_process <<
                                  " will be ignored!" );
    }

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
}

// Combine the values stored by each process into a single value at the root
/*! \details The input_value on every process of the communicator will be
 * reduced on root_process of the communicator. This version of the reduce
 * method can only be called by non-root processes (since the output value
 * is not needed).
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const T& input_value,
             ReduceOperation op,
             int root_process )
{
  Details::SingleValueReduceHelper<T>::reduce( comm, input_value, op, root_process );
}

// Combine the values stored by each process into a single value at the root
/*! \details The input_values on every process of the communicator will be
 * reduced on root_process of the communicator. This version of the reduce
 * method can only be called by non-root processes (since the output values
 * array is not needed).
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void reduce( const Communicator& comm,
                    std::initializer_list<T> input_values,
                    ReduceOperation op,
                    int root_process )
{
  Utility::reduce( comm, Utility::ArrayView<const T>( input_values.begin(), input_values.end() ), op, root_process );
}

// Combine the values stored by each process into a single value at the root
/*! \details The input_values on every process of the communicator will be
 * reduced on root_process of the communicator. This version of the reduce
 * method can only be called by non-root processes (since the output values
 * array is not needed).
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             ReduceOperation op,
             int root_process )
{
  Utility::reduce( comm, input_values, Utility::ArrayView<T>(), op, root_process );
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
  Details::SingleValueReduceHelper<T>::scan( comm, input_value, output_value, op );
}

// Compute a prefix reduction of values from all processes
/*! \details This method if provided to help with overload resolution
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
inline void scan( const Communicator& comm,
                  const Utility::ArrayView<T>& input_values,
                  const Utility::ArrayView<T>& output_values,
                  ReduceOperation op )
{
  Utility::scan( comm, input_values.toConst(), output_values, op );
}

// Compute a prefix reduction of values from all processes
/*! \details The input_values on every process of the communicator will be
 * reduced using a prefix reduction. This operation can be done with
 * communicators of any size.
 * \ingroup mpi
 */
template<typename T, typename ReduceOperation>
void scan( const Communicator& comm,
           const Utility::ArrayView<const T>& input_values,
           const Utility::ArrayView<T>& output_values,
           ReduceOperation op )
{
  if( comm.size() > 1 )
  {
    const MPICommunicator* const mpi_comm =
      dynamic_cast<const MPICommunicator* const>( &comm );

    TEST_FOR_EXCEPTION( mpi_comm == NULL,
                        InvalidCommunicator,
                        "An unknown communicator type was encountered!" );

    TEST_FOR_EXCEPTION( output_values.size() < input_values.size(),
                        CommunicationError,
                        comm << " could not conduct scan operation "
                        "because the output array is not large enough!" );

    try{
      mpi_comm->scan( input_values.data(), input_values.size(), output_values.data(), op );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                CommunicationError,
                                comm << " did not conduct scan "
                                "operation successfully!" );
  }
  else
  {
    __TEST_FOR_NULL_COMM__( comm );

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values.data(), input_values.size(), output_values.data() );
  }
}

} // end Utility namespace

// Explicit templateinstantiations for comm helpers
#define __EXPLICIT_COMM_HELPER_BASIC_INST__( MACRO )     \
  MACRO( bool );                                         \
  MACRO( char );                                         \
  MACRO( unsigned char );                                \
  MACRO( int );                                          \
  MACRO( unsigned int );                                 \
  MACRO( long );                                         \
  MACRO( unsigned long );                                \
  MACRO( long long );                                    \
  MACRO( unsigned long long );                           \
  MACRO( float );                                        \
  MACRO( double )

#define __EXPLICIT_COMM_HELPER_INST__( MACRO )          \
  __EXPLICIT_COMM_HELPER_BASIC_INST__( MACRO );         \
  MACRO( std::string );                                 \
  MACRO( std::pair<float,int> );                        \
  MACRO( std::tuple<float,int> );                       \
  MACRO( std::pair<double,int> );                       \
  MACRO( std::tuple<double,int> );                      \
  MACRO( std::pair<long,int> );                         \
  MACRO( std::tuple<long,int> );                        \
  MACRO( std::pair<int,int> );                          \
  MACRO( std::tuple<int,int> );                         \
  MACRO( std::pair<short,int> );                        \
  MACRO( std::tuple<short,int> )

// Explicit template instantiations for send/receive helpers
#define __EXTERN_EXPLICIT_COMM_SEND_RECV_HELPER_TYPE_INST__( ... )  \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::send( const Utility::Communicator&, int, int, const Utility::ArrayView<const __VA_ARGS__>& ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Status Utility::receive( const Utility::Communicator&, int, int, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXPLICIT_COMM_SEND_RECV_HELPER_TYPE_INST__( ... )  \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::send( const Utility::Communicator&, int, int, const Utility::ArrayView<const __VA_ARGS__>& ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Status Utility::receive( const Utility::Communicator&, int, int, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXTERN_EXPLICIT_COMM_SEND_RECV_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_SEND_RECV_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_SEND_RECV_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_SEND_RECV_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_SEND_RECV_HELPER_INST__;

// Explicit template instantiations for isend/ireceive helpers
#define __EXTERN_EXPLICIT_COMM_ISEND_IRECV_HELPER_TYPE_INST__( ... )  \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Request Utility::isend( const Utility::Communicator&, int, int, const Utility::ArrayView<const __VA_ARGS__>& ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Request Utility::ireceive( const Utility::Communicator&, int, int, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXPLICIT_COMM_ISEND_IRECV_HELPER_TYPE_INST__( ... )  \
  EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Request Utility::isend( const Utility::Communicator&, int, int, const Utility::ArrayView<const __VA_ARGS__>& ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Request Utility::ireceive( const Utility::Communicator&, int, int, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXTERN_EXPLICIT_COMM_ISEND_IRECV_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_ISEND_IRECV_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_ISEND_IRECV_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_ISEND_IRECV_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_ISEND_IRECV_HELPER_INST__;

// Explicit template instantiations for probe helper
#define __EXTERN_EXPLICIT_COMM_PROBE_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Status Utility::probe<__VA_ARGS__>( const Utility::Communicator&, int, int ) )

#define __EXPLICIT_COMM_PROBE_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Status Utility::probe<__VA_ARGS__>( const Utility::Communicator&, int, int ) )

#define __EXTERN_EXPLICIT_COMM_PROBE_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_PROBE_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_PROBE_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_PROBE_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_PROBE_HELPER_INST__;

// Explicit template instantiations for iprobe helper
#define __EXTERN_EXPLICIT_COMM_IPROBE_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Status Utility::iprobe<__VA_ARGS__>( const Utility::Communicator&, int, int ) )

#define __EXPLICIT_COMM_IPROBE_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( Utility::Communicator::Status Utility::iprobe<__VA_ARGS__>( const Utility::Communicator&, int, int ) )

#define __EXTERN_EXPLICIT_COMM_IPROBE_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_IPROBE_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_IPROBE_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_IPROBE_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_IPROBE_HELPER_INST__;

// Explicit template instantiations for allGather helper
#define __EXTERN_EXPLICIT_COMM_ALL_GATHER_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allGather( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXPLICIT_COMM_ALL_GATHER_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allGather( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXTERN_EXPLICIT_COMM_ALL_GATHER_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_ALL_GATHER_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_ALL_GATHER_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_ALL_GATHER_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_ALL_GATHER_HELPER_INST__;

// Explicit template instantiations for allReduce helper
#define __EXTERN_EXPLICIT_COMM_ALL_REDUCE_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::plus<__VA_ARGS__> ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::multiplies<__VA_ARGS__> ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::minimum<__VA_ARGS__> ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::maximum<__VA_ARGS__> ) )

#define __EXPLICIT_COMM_ALL_REDUCE_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::plus<__VA_ARGS__> ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::multiplies<__VA_ARGS__> ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::minimum<__VA_ARGS__> ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allReduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::maximum<__VA_ARGS__> ) )

#define __EXTERN_EXPLICIT_COMM_ALL_REDUCE_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_BASIC_INST__( \
              __EXTERN_EXPLICIT_COMM_ALL_REDUCE_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_ALL_REDUCE_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_BASIC_INST__( \
              __EXPLICIT_COMM_ALL_REDUCE_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_ALL_REDUCE_HELPER_INST__;

// Explicit template instantiations for allToAll helper
#define __EXTERN_EXPLICIT_COMM_ALL_TO_ALL_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allToAll( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXPLICIT_COMM_ALL_TO_ALL_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::allToAll( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>& ) )

#define __EXTERN_EXPLICIT_COMM_ALL_TO_ALL_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_ALL_TO_ALL_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_ALL_TO_ALL_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_ALL_TO_ALL_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_ALL_TO_ALL_HELPER_INST__;

// Explicit template instantiations for broadcast helper
#define __EXTERN_EXPLICIT_COMM_BROADCAST_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::broadcast( const Utility::Communicator&, const Utility::ArrayView<__VA_ARGS__>&, int ) )

#define __EXPLICIT_COMM_BROADCAST_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::broadcast( const Utility::Communicator&, const Utility::ArrayView<__VA_ARGS__>&, int ) )

#define __EXTERN_EXPLICIT_COMM_BROADCAST_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_BROADCAST_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_BROADCAST_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_BROADCAST_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_BROADCAST_HELPER_INST__;

// Explicit template instantiations for gather helper
#define __EXTERN_EXPLICIT_COMM_GATHER_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gather( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gather( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, int ) )

#define __EXPLICIT_COMM_GATHER_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gather( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gather( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, int ) )

#define __EXTERN_EXPLICIT_COMM_GATHER_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_GATHER_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_GATHER_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_GATHER_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_GATHER_HELPER_INST__;

// Explicit template instantiations for gatherv helper
#define __EXTERN_EXPLICIT_COMM_GATHERV_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gatherv( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gatherv( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, int ) )

#define __EXPLICIT_COMM_GATHERV_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gatherv( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::gatherv( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, int ) )

#define __EXTERN_EXPLICIT_COMM_GATHERV_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_GATHERV_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_GATHERV_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_GATHERV_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_GATHERV_HELPER_INST__;

// Explicit template instantiations for scatter helper
#define __EXTERN_EXPLICIT_COMM_SCATTER_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, __VA_ARGS__&, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, const Utility::ArrayView<__VA_ARGS__>&, int ) )

#define __EXPLICIT_COMM_SCATTER_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, __VA_ARGS__&, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatter( const Utility::Communicator&, const Utility::ArrayView<__VA_ARGS__>&, int ) )

#define __EXTERN_EXPLICIT_COMM_SCATTER_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_SCATTER_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_SCATTER_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_SCATTER_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_SCATTER_HELPER_INST__;

// Explicit template instantiations for scatter helper
#define __EXTERN_EXPLICIT_COMM_SCATTERV_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatterv( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const std::vector<int>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatterv( const Utility::Communicator&, const Utility::ArrayView<__VA_ARGS__>&, int ) )

#define __EXPLICIT_COMM_SCATTERV_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatterv( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const std::vector<int>&, const Utility::ArrayView<__VA_ARGS__>&, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scatterv( const Utility::Communicator&, const Utility::ArrayView<__VA_ARGS__>&, int ) )

#define __EXTERN_EXPLICIT_COMM_SCATTERV_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_INST__( \
              __EXTERN_EXPLICIT_COMM_SCATTERV_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_SCATTERV_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_INST__( \
              __EXPLICIT_COMM_SCATTERV_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_SCATTERV_HELPER_INST__;

// Explicit template instantiations for reduce helper
#define __EXTERN_EXPLICIT_COMM_REDUCE_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::plus<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::multiplies<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::minimum<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::maximum<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, std::plus<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, std::multiplies<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, Utility::minimum<__VA_ARGS__>, int ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, Utility::maximum<__VA_ARGS__>, int ) )

#define __EXPLICIT_COMM_REDUCE_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::plus<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::multiplies<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::minimum<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::maximum<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, std::plus<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, std::multiplies<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, Utility::minimum<__VA_ARGS__>, int ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::reduce( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, Utility::maximum<__VA_ARGS__>, int ) )

#define __EXTERN_EXPLICIT_COMM_REDUCE_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_BASIC_INST__( \
              __EXTERN_EXPLICIT_COMM_REDUCE_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_REDUCE_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_BASIC_INST__( \
              __EXPLICIT_COMM_REDUCE_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_REDUCE_HELPER_INST__;

// Explicit template instantiations for scan helper
#define __EXTERN_EXPLICIT_COMM_SCAN_HELPER_TYPE_INST__( ... ) \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::plus<__VA_ARGS__> ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::multiplies<__VA_ARGS__> ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::minimum<__VA_ARGS__> ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::maximum<__VA_ARGS__> ) )

#define __EXPLICIT_COMM_SCAN_HELPER_TYPE_INST__( ... ) \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::plus<__VA_ARGS__> ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, std::multiplies<__VA_ARGS__> ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::minimum<__VA_ARGS__> ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void Utility::scan( const Utility::Communicator&, const Utility::ArrayView<const __VA_ARGS__>&, const Utility::ArrayView<__VA_ARGS__>&, Utility::maximum<__VA_ARGS__> ) )

#define __EXTERN_EXPLICIT_COMM_SCAN_HELPER_INST__  \
  __EXPLICIT_COMM_HELPER_BASIC_INST__( \
              __EXTERN_EXPLICIT_COMM_SCAN_HELPER_TYPE_INST__ \
                                 )

#define __EXPLICIT_COMM_SCAN_HELPER_INST__  \
 __EXPLICIT_COMM_HELPER_BASIC_INST__( \
              __EXPLICIT_COMM_SCAN_HELPER_TYPE_INST__ \
                                 )

__EXTERN_EXPLICIT_COMM_SCAN_HELPER_INST__;

#endif // end UTILITY_COMMUNICATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Communicator_def.hpp
//---------------------------------------------------------------------------//
