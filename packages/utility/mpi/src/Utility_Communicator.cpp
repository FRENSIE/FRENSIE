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
#include "Utility_GlobalOpenMPSession.hpp"

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
  { return GlobalOpenMPSession::createTimer(); }

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

//---------------------------------------------------------------------------//
// end Utility_Communicator.cpp
//---------------------------------------------------------------------------//
