//---------------------------------------------------------------------------//
//!
//! \file   Utility_Communicator.cpp
//! \author Alex Robinson
//! \brief  The communicator class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_SerialCommunicator.hpp"
#include "Utility_MPICommunicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_OpenMPProperties.hpp"

namespace Utility{

/*! The null communicator
 * \ingroup mpi
 */
class NullCommunicator : public Communicator
{

public:

  //! Get the null communicator
  static std::shared_ptr<const NullCommunicator> get()
  {
    if( !s_null_comm )
      s_null_comm.reset( new NullCommunicator );

    return s_null_comm;
  }

  //! Destructor
  ~NullCommunicator()
  { /* ... */ }

  //! Determine the rank of the executing process
  int rank() const
  { return -1; }

  //! Determine the number of processes in a communicator
  int size() const
  { return 0; }

  //! The any source value
  int anySourceValue() const
  { return -1; }

  //! The any tag value
  int anyTagValue() const
  { return -1; }

  //! Wait for all processes within the comm to reach the barrier
  void barrier() const
  { /* ... */ }

  //! Check if this communicator is valid for communication
  bool isValid() const
  { return false; }

  //! Check if this communicator uses mpi
  bool isMPIUsed() const
  { return false; }
  
  // Check if this communicator is this communicator is identical to another
  bool isIdentical( const Communicator& comm ) const
  { return this == &comm; }

  /*! \brief Split the communicator into multiple, disjoint communicators each
   * of which is based on a particular color
   */
  std::shared_ptr<const Communicator> split( int color ) const
  { return s_null_comm; }

  /*! \brief Split the communicator into multiple, disjoint communicators each
   * of which is based on a particular color.
   */
  std::shared_ptr<const Communicator> split( int color, int key ) const override
  { return s_null_comm; }

  //! Create a timer
  std::shared_ptr<Timer> createTimer() const override
  { return OpenMPProperties::createTimer(); }

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override
  { os << "Null Communicator"; }

private:

  //! Default constructor
  NullCommunicator()
  { /* ... */ }

  // The null communicator
  static std::shared_ptr<const NullCommunicator> s_null_comm;
};

// Initialize static member data
std::shared_ptr<const NullCommunicator> NullCommunicator::s_null_comm;

// Create a default communicator
std::shared_ptr<const Communicator> Communicator::getDefault()
{
  if( Utility::GlobalMPISession::isMPIUsed() )
  {
    if( Utility::GlobalMPISession::initialized() &&
        !Utility::GlobalMPISession::finalized() )
    {
      return std::shared_ptr<const Communicator>( new MPICommunicator );
    }
  }

  return SerialCommunicator::get();
}

// Create a null communicator
std::shared_ptr<const Communicator> Communicator::getNull()
{ return NullCommunicator::get(); }

// Determine if this communicator is valid for communication
Communicator::operator bool() const
{ return this->isValid(); }

// Default constructor
Communicator::Status::Status()
{ /* ... */ }

// Copy constructor
Communicator::Status::Status( const Status& other_status )
  : d_impl( other_status.d_impl )
{ /* ... */ }

// Implementation constructor
Communicator::Status::Status( const std::shared_ptr<const Impl>& impl )
  : d_impl( impl )
{ /* ... */ }

// Assignment operator
Communicator::Status& Communicator::Status::operator=(
                                     const Communicator::Status& other_status )
{
  if( this != &other_status )
    d_impl = other_status.d_impl;

  return *this;
}

// Check if there are message details
/*! \details An example of when this will be false is after a call to
 * Utility::iprobe.
 */
bool Communicator::Status::hasMessageDetails() const
{
  return d_impl.get() != NULL;
}

// Check if there are message details
/*! \details An example of when this will be false is after a call to
 * Utility::iprobe.
 */
Communicator::Status::operator bool() const
{
  return d_impl.get() != NULL;
}

// Check if the communication was cancelled successfully
/*! \details If there are no message details, the return value is always false.
 */
bool Communicator::Status::cancelled() const
{
  if( d_impl )
    return d_impl->cancelled();
  else
    return false;
}
  
// Retrieve the source of the message
/*! \details If there are no message details, the return value is always -1.
 */
int Communicator::Status::source() const
{
  if( d_impl )
    return d_impl->source();
  else
    return -1;
}

// Retrieve the message tag
/*! \details If there are no message details, the return value is always -1.
 */
int Communicator::Status::tag() const
{
  if( d_impl )
    return d_impl->tag();
  else
    return -1;
}

// Count the number of elements that were contained in the message
/*! \details If there are no message details, the return value is always -1. 
 *NOTE: Currently does not function properly for non-native types due to bug in boost 1.72 that always returns count of 1.
 */
int Communicator::Status::count() const
{
  if( d_impl )
    return d_impl->count();
  else
    return -1;
}

// Default constructor
Communicator::Request::Request()
{ /* ... */ }

// Copy constructor
Communicator::Request::Request( const Request& other_request )
  : d_impl( other_request.d_impl )
{ /* ... */ }

// Implementation constructor
Communicator::Request::Request( const std::shared_ptr<Impl>& impl )
  : d_impl( impl )
{ /* ... */ }

// Assignment operator
Communicator::Request& Communicator::Request::operator=(
                                   const Communicator::Request& other_request )
{
  if( this != &other_request )
    d_impl = other_request.d_impl;

  return *this;
}

// Wait until the operation associated with this request has completed
Communicator::Status Communicator::Request::wait()
{
  if( d_impl )
  {
    std::shared_ptr<const Communicator::Status::Impl>
      status_impl( d_impl->wait() );

    return Communicator::Status( status_impl );
  }
  else
    return Communicator::Status();
}

// Cancel the pending operation associated with this request
void Communicator::Request::cancel()
{
  if( d_impl )
    d_impl->cancel();
}

// Create a new status object
Communicator::Status Communicator::createStatus(
                const std::shared_ptr<const Communicator::Status::Impl>& impl )
{
  return Communicator::Status( impl );
}

// Create a new request object
Communicator::Request Communicator::createRequest(
                     const std::shared_ptr<Communicator::Request::Impl>& impl )
{
  return Communicator::Request( impl );
}

/*! Determine if two communicators are identical
 * \ingroup mpi
 */
bool operator==( const Communicator& comm_a, const Communicator& comm_b )
{ return comm_a.isIdentical( comm_b ); }

/*! Determine if two communicators are different
 * \ingroup mpi
 */
bool operator!=( const Communicator& comm_a, const Communicator& comm_b )
{ return !comm_a.isIdentical( comm_b ); }

} // end Utility namespace

/*! NOTE: Due to scatterv changes introduced in boost 1.72, 
 *  anything involving scatterv does not function properly 
 * at the moment and its tests are disabled. If you require
 * scatterv, please find the bug, fix it, and submit it for
 * a pull request.
 *  \ingroup mpi
 */

// Explicit instantiations
__EXPLICIT_COMM_SEND_RECV_HELPER_INST__;
__EXPLICIT_COMM_ISEND_IRECV_HELPER_INST__;
__EXPLICIT_COMM_PROBE_HELPER_INST__;
__EXPLICIT_COMM_IPROBE_HELPER_INST__;
__EXPLICIT_COMM_ALL_GATHER_HELPER_INST__;
__EXPLICIT_COMM_ALL_REDUCE_HELPER_INST__;
__EXPLICIT_COMM_ALL_TO_ALL_HELPER_INST__;
__EXPLICIT_COMM_BROADCAST_HELPER_INST__;
__EXPLICIT_COMM_GATHER_HELPER_INST__;
__EXPLICIT_COMM_GATHERV_HELPER_INST__;
__EXPLICIT_COMM_SCATTER_HELPER_INST__;
__EXPLICIT_COMM_SCATTERV_HELPER_INST__;
__EXPLICIT_COMM_REDUCE_HELPER_INST__;
__EXPLICIT_COMM_SCAN_HELPER_INST__;

//---------------------------------------------------------------------------//
// end Utility_Communicator.cpp
//---------------------------------------------------------------------------//
