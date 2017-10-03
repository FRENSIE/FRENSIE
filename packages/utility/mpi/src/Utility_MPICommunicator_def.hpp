//---------------------------------------------------------------------------//
//!
//! \file   Utility_MPICommunicator_def.hpp
//! \author Alex Robinson
//! \brief  The mpi communicator class
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MPI_COMMUNICATOR_DEF_HPP
#define UTILITY_MPI_COMMUNICATOR_DEF_HPP

namespace Utility{

#ifdef HAVE_FRENSIE_MPI

/*! The mpi communicator status class
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

  //! Retrieve the error code
  int error() const override
  { return d_status.error(); }

  //! Check if the communication was cancelled successfully
  bool cancelled() const override
  { return d_status.cancelled(); }

  //! Check if the message was communicated successfully
  bool success() const override
  { return this->error() == MPI_SUCCESS && !this->cancelled(); }

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

  //! Wait until the communicator associated with this request has completed
  std::shared_ptr<const CommunicatorStatus> wait() override
  {
    std::shared_ptr<const CommunicatorStatus>
      status( new MPICommunicatorStatus( d_request.wait() ) );
    
    return status;
  }

  //! Cancel a pending communication
  void cancel() override
  { d_request.cancel(); }

private:

  // The boost request
  boost::mpi::request d_request;
};
  
#endif // end HAVE_FRENSIE_MPI

namespace Details{

#ifdef HAVE_FRENSIE_MPI

/*! Get the boost::mpi operator associated with the object
 * \ingroup mpi
 */
template<typename Op>
struct BoostMPIOperatorTraits
{
  typedef Op BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Op& input_op )
  { return BoostMPIOperator( input_op ); }
};

/*! Specialization of BoostMPIOperatorTraits for Utility::maximum
 * \ingroup mpi
 */
template<typename T>
struct BoostMPIOperatorTraits<Utility::maximum<T> >
{
  typedef boost::mpi::maximum<typename Utility::maximum<T>::InputType> BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Utility::maximum<T>& )
  { return BoostMPIOperator(); }
};

/*! Specialization of BoostMPIOperatorTraits for Utility::minimum
 * \ingroup mpi
 */
template<typename T>
struct BoostMPIOperatorTraits<Utility::minimum<T> >
{
  typedef boost::mpi::minimum<typename Utility::minimum<T>::InputType> BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Utility::minimum<T>& )
  { return BoostMPIOperator(); }
};

/*! Specialization of BoostMPIOperatorTraits for Utility::bitwiseAnd
 * \ingroup mpi
 */
template<typename T>
struct BoostMPIOperatorTraits<Utility::bitwiseAnd<T> >
{
  typedef boost::mpi::bitwise_and<typename Utility::bitwiseAnd<T>::InputType> BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Utility::bitwiseAnd<T>& )
  { return BoostMPIOperator(); }
};

/*! Specialization of BoostMPIOperatorTraits for Utility::bitwiseOr
 * \ingroup mpi
 */
template<typename T>
struct BoostMPIOperatorTraits<Utility::bitwiseOr<T> >
{
  typedef boost::mpi::bitwise_or<typename Utility::bitwiseOr<T>::InputType> BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Utility::bitwiseOr<T>& )
  { return BoostMPIOperator(); }
};

/*! Specialization of BoostMPIOperatorTraits for Utility::bitwiseXor
 * \ingroup mpi
 */
template<typename T>
struct BoostMPIOperatorTraits<Utility::bitwiseXor<T> >
{
  typedef boost::mpi::bitwise_xor<typename Utility::bitwiseXor<T>::InputType> BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Utility::bitwiseXor<T>& )
  { return BoostMPIOperator(); }
};

/*! Specialization of BoostMPIOperatorTraits for Utility::logicalXor
 * \ingroup mpi
 */
template<typename T>
struct BoostMPIOperatorTraits<Utility::logicalXor<T> >
{
  typedef boost::mpi::logical_xor<typename Utility::logicalXor<T>::InputType> BoostMPIOperator;

  //! Convert the operator to a boost::mpi operator
  static inline BoostMPIOperator convert( const Utility::logicalXor<T>& )
  { return BoostMPIOperator(); }
};

//! Convert an operator to an equivalent boost::mpi operator
template<typename Op>
typename BoostMPIOperatorTraits<Op>::BoostMPIOperator convertOperator( const Op& input_op )
{
  return BoostMPIOperatorTraits<Op>::convert( input_op );
}

#endif // end HAVE_FRENSIE_MPI

} // end Details namespace

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
                              int MPI_ENABLED_PARAMETER(number_of_values) )
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
  MPI_ENABLED_LINE( boost::mpi::all_reduce( d_comm, input_values, number_of_input_values, output_values, Details::convertOperator(op) ) );
}

// Combine the values stored by each process into a single value
template<typename T, typename ReduceOperation>
void MPICommunicator::allReduce(
                          T* MPI_ENABLED_PARAMETER(input_output_values),
                          int MPI_ENABLED_PARAMETER(number_of_values),
                          ReduceOperation MPI_ENABLED_PARAMETER(op) ) const
{
  MPI_ENABLED_LINE( boost::mpi::all_reduce( d_comm, input_output_values, number_of_values, Details::convertOperator(op) ) );
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
                          int MPI_ENABLED_PARAMETER(number_of_output_values),
                          int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::scatterv( d_comm, input_values, sizes, output_values, number_of_output_values, root_process ) );
}

// Combine the values stored by each process intoa single value at the root
template<typename T, typename ReduceOperation>
void MPICommunicator::reduce( const T* MPI_ENABLED_PARAMETER(input_values),
                              int MPI_ENABLED_PARAMETER(number_of_input_values),
                              T* MPI_ENABLED_PARAMETER(output_values),
                              ReduceOperation MPI_ENABLED_PARAMETER(op),
                              int MPI_ENABLED_PARAMETER(root_process) ) const
{
  MPI_ENABLED_LINE( boost::mpi::reduce( d_comm, input_values, number_of_input_values, output_values, Details::convertOperator(op), root_process ) );
}

// Compute a prefix reduction of values from all processes
template<typename T, typename ReduceOperation>
void MPICommunicator::scan( const T* MPI_ENABLED_PARAMETER(input_values),
                            int MPI_ENABLED_PARAMETER(number_of_input_values),
                            T* MPI_ENABLED_PARAMETER(output_values),
                            ReduceOperation MPI_ENABLED_PARAMETER(op) ) const
{
  MPI_ENABLED_LINE( boost::mpi::scan( d_comm, input_values, number_of_input_values, output_values, Details::convertOperator(op) ) );
}
  
} // end Utility namespace

#endif // end UTILITY_MPI_COMMUNICATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_MPICommunicator_def.hpp
//---------------------------------------------------------------------------//
