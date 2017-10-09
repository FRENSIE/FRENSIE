//---------------------------------------------------------------------------//
//!
//! \file   Utility_MPICommunicator_def.hpp
//! \author Alex Robinson
//! \brief  The mpi communicator class
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MPI_COMMUNICATOR_DEF_HPP
#define UTILITY_MPI_COMMUNICATOR_DEF_HPP

// Std Lib Includes
#include <algorithm>
#include <functional>

namespace Utility{

#ifdef HAVE_FRENSIE_MPI

/*! The mpi communicator status class
 *
 * The status class does not expose the raw MPI error code because the error 
 * code is not used to indicate errors. All of the wrapped mpi methods that 
 * return a MPICommunicatorStatus will throw a std::exception to indicate that 
 * an  error has occurred.
 * \ingroup mpi
 */
class MPICommunicatorStatus : public CommunicatorStatus
{

public:

  //! boost::mpi::status constructor
  MPICommunicatorStatus( const boost::mpi::status& status )
    : d_status( status )
  { /* ... */ }

  //! Destructor
  ~MPICommunicatorStatus()
  { /* ... */ }

  //! Retrieve the source of the message
  int source() const override
  { return d_status.source(); }

  //! Retrieve the message tag
  int tag() const override
  { return d_status.tag(); }

  //! Check if the communication was cancelled successfully
  bool cancelled() const override
  { return d_status.cancelled(); }

  //! Determine the number of elements that were contained in a message
  template<typename T>
  int count() const
  {
    if( boost::optional<int> wrapped_count = d_status.count<T>() )
      return *wrapped_count;
    else
      return 0;
  }

private:

  // The boost status
  boost::mpi::status d_status;
};

/*! The mpi communicator request class
 * \ingroup mpi
 */
class MPICommunicatorRequest : public CommunicatorRequest
{

public:

  //! boost::mpi::request constructor
  MPICommunicatorRequest( const boost::mpi::request& request )
    : d_request( request )
  { /* ... */ }

  //! Destructor
  ~MPICommunicatorRequest()
  { /* ... */ }

  /*! Wait until the communicator associated with this request has completed
   * \details This will throw a std::exception if the wait fails.
   */
  std::shared_ptr<const CommunicatorStatus> wait() override
  {
    return std::shared_ptr<const CommunicatorStatus>(
                               new MPICommunicatorStatus( d_request.wait() ) );
  }

  //! Cancel a pending communication
  void cancel() override
  { d_request.cancel(); }

private:

  // The boost request
  boost::mpi::request d_request;
};

namespace Details{

/*! Convert the reduce operation to the equivalent boost reduce operation
 * \ingroup mpi
 */
template<typename ReduceOp>
struct ReduceOpConversionHelper
{
  typedef ReduceOp BoostReduceOp;
  
  static inline const ReduceOp& convertToBoostReduceOp( const ReduceOp& op )
  { return op; }
};

/*! Partial specialization of ReduceOpConversionHelper for Utility::maximum
 * \ingroup mpi
 */
template<typename T>
struct ReduceOpConversionHelper<Utility::maximum<T> >
{
  typedef boost::mpi::maximum<typename Utility::maximum<T>::InputType> BoostReduceOp;
  
  static inline BoostReduceOp convertToBoostReduceOp( const Utility::maximum<T>& op )
  { return BoostReduceOp(); }
};

/*! Partial specialization of ReduceOpConversionHelper for Utility::minimum
 * \ingroup mpi
 */
template<typename T>
struct ReduceOpConversionHelper<Utility::minimum<T> >
{
  typedef boost::mpi::minimum<typename Utility::minimum<T>::InputType> BoostReduceOp;
  
  static inline BoostReduceOp convertToBoostReduceOp( const Utility::minimum<T>& op )
  { return BoostReduceOp(); }
};

/*! Partial specialization of ReduceOpConversionHelper for Utility::bitwiseAnd
 * \ingroup mpi
 */
template<typename T>
struct ReduceOpConversionHelper<Utility::bitwiseAnd<T> >
{
  typedef boost::mpi::bitwise_and<typename Utility::bitwiseAnd<T>::InputType> BoostReduceOp;
  
  static inline BoostReduceOp convertToBoostReduceOp( const Utility::bitwiseAnd<T>& op )
  { return BoostReduceOp(); }
};

/*! Partial specialization of ReduceOpConversionHelper for Utility::bitwiseOr
 * \ingroup mpi
 */
template<typename T>
struct ReduceOpConversionHelper<Utility::bitwiseOr<T> >
{
  typedef boost::mpi::bitwise_or<typename Utility::bitwiseOr<T>::InputType> BoostReduceOp;
  
  static inline BoostReduceOp convertToBoostReduceOp( const Utility::bitwiseOr<T>& op )
  { return BoostReduceOp(); }
};

/*! Partial specialization of ReduceOpConversionHelper for Utility::bitwiseXor
 * \ingroup mpi
 */
template<typename T>
struct ReduceOpConversionHelper<Utility::bitwiseXor<T> >
{
  typedef boost::mpi::bitwise_xor<typename Utility::bitwiseXor<T>::InputType> BoostReduceOp;
  
  static inline BoostReduceOp convertToBoostReduceOp( const Utility::bitwiseXor<T>& op )
  { return BoostReduceOp(); }
};

/*! Partial specialization of ReduceOpConversionHelper for Utility::logicalXor
 * \ingroup mpi
 */
template<typename T>
struct ReduceOpConversionHelper<Utility::logicalXor<T> >
{
  typedef boost::mpi::logical_xor<typename Utility::logicalXor<T>::InputType> BoostReduceOp;
  
  static inline BoostReduceOp convertToBoostReduceOp( const Utility::logicalXor<T>& op )
  { return BoostReduceOp(); }
};
  
} // end Details namespace
  
#endif // end HAVE_FRENSIE_MPI

template<typename T>
inline const T& maximum<T>::operator()( const T& lhs, const T& rhs ) const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::maximum<T>()( lhs, rhs );
#else // HAVE_FRENSIE_MPI
  return std::max( lhs, rhs );
#endif // end HAVE_FRENSIE_MPI
}

template<typename T>
inline const T& minimum<T>::operator()( const T& lhs, const T& rhs ) const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::minimum<T>()( lhs, rhs );
#else // HAVE_FRENSIE_MPI
  return std::min( lhs, rhs );
#endif // end HAVE_FRENSIE_MPI
}

template<typename T>
inline T bitwiseAnd<T>::operator()( const T& lhs, const T& rhs ) const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::bitwise_and<T>()( lhs, rhs );
#else // HAVE_FRENSIE_MPI
  return std::bit_and<T>()( lhs, rhs );
#endif // end HAVE_FRENSIE_MPI
}

template<typename T>
inline T bitwiseOr<T>::operator()( const T& lhs, const T& rhs ) const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::bitwise_or<T>()( lhs, rhs );
#else // HAVE_FRENSIE_MPI
  return std::bit_or<T>()( lhs, rhs );
#endif // end HAVE_FRENSIE_MPI
}

template<typename T>
inline T bitwiseXor<T>::operator()( const T& lhs, const T& rhs ) const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::bitwise_xor<T>()( lhs, rhs );
#else // HAVE_FRENSIE_MPI
  return std::bit_xor<T>()( lhs, rhs );
#endif // end HAVE_FRENSIE_MPI
}

template<typename T>
inline T logicalXor<T>::operator()( const T& lhs, const T& rhs ) const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::logical_xor<T>()( lhs, rhs );
#else // HAVE_FRENSIE_MPI
  return (lhs || rhs) && !(lhs && rhs);
#endif // end HAVE_FRENSIE_MPI
}

// Count the number of elements that were contained in a message
template<typename T>
int MPICommunicator::count(
                const CommunicatorStatus& MPI_ENABLED_PARAMETER(status) ) const
{
#ifdef HAVE_FRENSIE_MPI
  const MPICommunicatorStatus* const mpi_status =
    dynamic_cast<const MPICommunicatorStatus* const>( &status );

  if( mpi_status )
    return mpi_status->count<T>();
  else
    return 0;
#else // HAVE_FRENSIE_MPI
  return 0;
#endif // end HAVE_FRENSIE_MPI
}

// Send a message to another process (blocking)
template<typename T>
void MPICommunicator::send( int MPI_ENABLED_PARAMETER(dest),
                            int MPI_ENABLED_PARAMETER(tag),
                            const T* MPI_ENABLED_PARAMETER(values),
                            int MPI_ENABLED_PARAMETER(number_of_values) ) const
{
  MPI_ENABLED_LINE( d_comm.send( dest, tag, values, number_of_values ) );
}
// Receive a message from another process (blocking)
template<typename T>
std::shared_ptr<const CommunicatorStatus> MPICommunicator::recv(
                        int MPI_ENABLED_PARAMETER(source),
                        int MPI_ENABLED_PARAMETER(tag),
                        T* MPI_ENABLED_PARAMETER(values),
                        int MPI_ENABLED_PARAMETER(number_of_values) ) const
{
  MPI_ENABLED_LINE( return std::shared_ptr<const CommunicatorStatus>( new MPICommunicatorStatus( d_comm.recv( source, tag, values, number_of_values ) ) ) );
  MPI_DISABLED_LINE( return std::shared_ptr<const CommunicatorStatus>() );
}

// Send a message to another process (non-blocking)
template<typename T>
std::shared_ptr<CommunicatorRequest> MPICommunicator::isend(
                            int MPI_ENABLED_PARAMETER(dest),
                            int MPI_ENABLED_PARAMETER(tag),
                            const T* MPI_ENABLED_PARAMETER(values),
                            int MPI_ENABLED_PARAMETER(number_of_values) ) const
{
  MPI_ENABLED_LINE( return std::shared_ptr<CommunicatorRequest>( new MPICommunicatorRequest( d_comm.isend( dest, tag, values, number_of_values ) ) ) );
  MPI_DISABLED_LINE( return std::shared_ptr<CommunicatorRequest>() );
}

// Receive a message from another process (non-blocking)
template<typename T>
std::shared_ptr<CommunicatorRequest> MPICommunicator::irecv(
                        int MPI_ENABLED_PARAMETER(source),
                        int MPI_ENABLED_PARAMETER(tag),
                        T* MPI_ENABLED_PARAMETER(values),
                        int MPI_ENABLED_PARAMETER(number_of_values) ) const
{
  MPI_ENABLED_LINE( return std::shared_ptr<CommunicatorRequest>( new MPICommunicatorRequest( d_comm.irecv( source, tag, values, number_of_values ) ) ) );
  MPI_DISABLED_LINE( return std::shared_ptr<CommunicatorRequest>() );
}

// Wait until a message is available to be received
inline std::shared_ptr<const CommunicatorStatus>
MPICommunicator::probe( int MPI_ENABLED_PARAMETER(source),
                        int MPI_ENABLED_PARAMETER(tag) ) const
{
  MPI_ENABLED_LINE( return std::shared_ptr<const CommunicatorStatus>( new MPICommunicatorStatus( d_comm.probe( source, tag ) ) ) );
  MPI_DISABLED_LINE( return std::shared_ptr<const CommunicatorStatus>() );
}

// Determine if a message is available to be received
inline std::shared_ptr<const CommunicatorStatus>
MPICommunicator::iprobe( int source, int tag ) const
{
#ifdef HAVE_FRENSIE_MPI
  if( boost::optional<boost::mpi::status> wrapped_status = d_comm.iprobe( source, tag ) )
    return std::shared_ptr<const CommunicatorStatus>( new MPICommunicatorStatus( *wrapped_status ) );
  else
    return std::shared_ptr<const CommunicatorStatus>();
#else // HAVE_FRENSIE_MPI
  return std::shared_ptr<const CommunicatorStatus>();
#endif // end HAVE_FRENSIE_MPI
}
  
// Gather the array of values stored at every process into vectors of
// values from each process.
template<typename T>
void MPICommunicator::allGather(
                         const T* MPI_ENABLED_PARAMETER(input_values),
                         int MPI_ENABLED_PARAMETER(number_of_input_values),
                         T* MPI_ENABLED_PARAMETER(output_values) ) const
{
  MPI_ENABLED_LINE( boost::mpi::all_gather( d_comm, input_values, number_of_input_values, output_values ) );
}

// Combine the values stored by each process into a single value
// available to all processes.
template<typename T, typename ReduceOperation>
void MPICommunicator::allReduce(
                         const T* MPI_ENABLED_PARAMETER(input_values),
                         int MPI_ENABLED_PARAMETER(number_of_input_values),
                         T* MPI_ENABLED_PARAMETER(output_values),
                         ReduceOperation MPI_ENABLED_PARAMETER(op) ) const
{
  MPI_ENABLED_LINE( boost::mpi::all_reduce( d_comm, input_values, number_of_input_values, output_values, Details::ReduceOpConversionHelper<ReduceOperation>::convertToBoostReduceOp(op) ) );
}

// Combine the values stored by each process into a single value
template<typename T, typename ReduceOperation>
void MPICommunicator::allReduce(
                          T* MPI_ENABLED_PARAMETER(input_output_values),
                          int MPI_ENABLED_PARAMETER(number_of_values),
                          ReduceOperation MPI_ENABLED_PARAMETER(op) ) const
{
  MPI_ENABLED_LINE( boost::mpi::all_reduce( d_comm, input_output_values, number_of_values, Details::ReduceOpConversionHelper<ReduceOperation>::convertToBoostReduceOp(op) ) );
}

// Send data from every process to every other process
template<typename T>
void MPICommunicator::allToAll(
                         const T* MPI_ENABLED_PARAMETER(input_values),
                         int MPI_ENABLED_PARAMETER(number_of_input_values),
                         T* MPI_ENABLED_PARAMETER(output_values) ) const
{
  MPI_ENABLED_LINE( boost::mpi::all_to_all( d_comm, input_values, number_of_input_values, output_values ) );
}

// Broadcast a value from a root process to all other processes
template<typename T>
void MPICommunicator::broadcast(
                               T* MPI_ENABLED_PARAMETER(values),
                               int MPI_ENABLED_PARAMETER(number_of_values),
                               int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::broadcast( d_comm, values, number_of_values, root_process ) );
}

// Gather the values stored at every process into a vector at the root process
template<typename T>
void MPICommunicator::gather( const T* MPI_ENABLED_PARAMETER(input_values),
                              int MPI_ENABLED_PARAMETER(number_of_input_values),
                              T* MPI_ENABLED_PARAMETER(output_values),
                              int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::gather( d_comm, input_values, number_of_input_values, output_values, root_process ) );
}

// Gather the values stored at every process into a vector at the root process
template<typename T>
void MPICommunicator::gatherv(
                        const T* MPI_ENABLED_PARAMETER(input_values),
                        int MPI_ENABLED_PARAMETER(number_of_input_values),
                        T* MPI_ENABLED_PARAMETER(output_values),
                        const std::vector<int>& MPI_ENABLED_PARAMETER(sizes),
                        const std::vector<int>& MPI_ENABLED_PARAMETER(offsets),
                        const int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::gatherv( d_comm, input_values, number_of_input_values, output_values, sizes, offsets, root_process ) );
}

// Gather the values stored at every process into a vector at the root process
template<typename T>
void MPICommunicator::gatherv(
                          const T* MPI_ENABLED_PARAMETER(input_values),
                          int MPI_ENABLED_PARAMETER(number_of_input_values),
                          T* MPI_ENABLED_PARAMETER(output_values),
                          const std::vector<int>& MPI_ENABLED_PARAMETER(sizes),
                          const int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::gatherv( d_comm, input_values, number_of_input_values, output_values, sizes, root_process ) );
}

// Scatter the values stored at the root process to all other processes
template<typename T>
void MPICommunicator::scatter(
                          const T* MPI_ENABLED_PARAMETER(input_values),
                          T* MPI_ENABLED_PARAMETER(output_values),
                          int MPI_ENABLED_PARAMETER(number_of_values_per_proc),
                          int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::scatter( d_comm, input_values, output_values, number_of_values_per_proc, root_process ) );
}

// Scatter the values stored at the root process to all other processes
template<typename T>
void MPICommunicator::scatterv(
                        const T* MPI_ENABLED_PARAMETER(input_values),
                        const std::vector<int>& MPI_ENABLED_PARAMETER(sizes),
                        const std::vector<int>& MPI_ENABLED_PARAMETER(offsets),
                        T* MPI_ENABLED_PARAMETER(output_values),
                        int MPI_ENABLED_PARAMETER(number_of_output_values),
                        int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::scatterv( d_comm, input_values, sizes, offsets, output_values, number_of_output_values, root_process ) );
}

// Scatter the values stored at the root process to all other processes
template<typename T>
void MPICommunicator::scatterv(
                          const T* MPI_ENABLED_PARAMETER(input_values),
                          const std::vector<int>& MPI_ENABLED_PARAMETER(sizes),
                          T* MPI_ENABLED_PARAMETER(output_values),
                          int,
                          int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::scatterv( d_comm, input_values, sizes, output_values, root_process ) );
}

// Combine the values stored by each process intoa single value at the root
template<typename T, typename ReduceOperation>
void MPICommunicator::reduce( const T* MPI_ENABLED_PARAMETER(input_values),
                              int MPI_ENABLED_PARAMETER(number_of_input_values),
                              T* MPI_ENABLED_PARAMETER(output_values),
                              ReduceOperation MPI_ENABLED_PARAMETER(op),
                              int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::reduce( d_comm, input_values, number_of_input_values, output_values, Details::ReduceOpConversionHelper<ReduceOperation>::convertToBoostReduceOp(op), root_process ) );
}

// Compute a prefix reduction of values from all processes
template<typename T, typename ReduceOperation>
void MPICommunicator::scan( const T* MPI_ENABLED_PARAMETER(input_values),
                            int MPI_ENABLED_PARAMETER(number_of_input_values),
                            T* MPI_ENABLED_PARAMETER(output_values),
                            ReduceOperation MPI_ENABLED_PARAMETER(op) ) const
{
  MPI_ENABLED_LINE( boost::mpi::scan( d_comm, input_values, number_of_input_values, output_values, Details::ReduceOpConversionHelper<ReduceOperation>::convertToBoostReduceOp(op) ) );
}
  
} // end Utility namespace

#endif // end UTILITY_MPI_COMMUNICATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_MPICommunicator_def.hpp
//---------------------------------------------------------------------------//
