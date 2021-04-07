//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerialCommunicator.cpp
//! \author Alex Robinson
//! \brief  The serial communicator class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SerialCommunicator.hpp"
#include "Utility_OpenMPProperties.hpp"

namespace Utility{

// Initialize static member data
std::shared_ptr<const SerialCommunicator> SerialCommunicator::s_serial_comm;

// Get the serial communicator
std::shared_ptr<const SerialCommunicator> SerialCommunicator::get()
{
  if( !s_serial_comm )
    s_serial_comm.reset( new SerialCommunicator );

  return s_serial_comm;
}

// Default constructor
SerialCommunicator::SerialCommunicator()
{ /* ... */ }

// Destructor
SerialCommunicator::~SerialCommunicator()
{ /* ... */ }

// Determine the rank of the executing process
int SerialCommunicator::rank() const
{
  return s_rank;
}

// Determine the number of processes in a communicator
int SerialCommunicator::size() const
{
  return s_size;
}

// The any source value
int SerialCommunicator::anySourceValue() const
{
  return -1;
}

// The any tag value
int SerialCommunicator::anyTagValue() const
{
  return -1;
}

// Wait for all processes within the comm to reach the barrier
void SerialCommunicator::barrier() const
{ /* ... */ }

// Check if this communicator is valid for communication
bool SerialCommunicator::isValid() const
{
  return true;
}

// Check if this communicator uses mpi
bool SerialCommunicator::isMPIUsed() const
{
  return false;
}

// Check if this communicator is this communicator is identical to another
/*! \details Since the serial communicator is a singleton a simple memory
 * comparison will be done.
 */
bool SerialCommunicator::isIdentical( const Communicator& comm ) const
{
  return this == &comm;
}
  
// Split the communicator into multiple, disjoint communicators each
// of which is based on a particular color
std::shared_ptr<const Communicator> SerialCommunicator::split( int color ) const
{
  return s_serial_comm;
}

// Split the communicator into multiple, disjoint communicators each
// of which is based on a particular color.
std::shared_ptr<const Communicator> SerialCommunicator::split( int color, int key ) const
{
  return s_serial_comm;
}

// Create a timer
std::shared_ptr<Timer> SerialCommunicator::createTimer() const
{
  return OpenMPProperties::createTimer();
}

// Method for placing the object in an output stream
void SerialCommunicator::toStream( std::ostream& os ) const
{
  os << "Serial Communicator";
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SerialCommunicator.cpp
//---------------------------------------------------------------------------//
