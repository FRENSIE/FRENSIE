//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerialCommunicator.cpp
//! \author Alex Robinson
//! \brief  The serial communicator class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SerialCommunicator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

namespace Utility{

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
/*! \details All serial communicators are identical
 */
bool SerialCommunicator::isIdentical( const Communicator& comm ) const
{
  // Attempt to cast the comm to a serial comm
  const SerialCommunicator* const serial_comm =
    static_cast<const SerialCommunicator* const>( &comm );

  return serial_comm != NULL;
}
  
// Split the communicator into multiple, disjoint communicators each
// of which is based on a particular color
std::shared_ptr<const Communicator> SerialCommunicator::split( int color ) const
{
  return std::shared_ptr<const Communicator>( new SerialCommunicator );
}

// Split the communicator into multiple, disjoint communicators each
// of which is based on a particular color.
std::shared_ptr<const Communicator> SerialCommunicator::split( int color, int key ) const
{
  return std::shared_ptr<const Communicator>( new SerialCommunicator );
}

// Create a communicator that is the union of this communicator and
// another communicator
std::shared_ptr<const Communicator> SerialCommunicator::combine(
                                               const Communicator& comm ) const
{
  if( this->isIdentical( comm ) )
    return std::shared_ptr<const Communicator>( new SerialCommunicator );
  else
    return Communicator::getNull();
}

// Create a communicator that is the intersection of this 
// communicator and another communicator
std::shared_ptr<const Communicator> SerialCommunicator::intersect(
                                               const Communicator& comm ) const
{
  if( this->isIdentical( comm ) )
    return std::shared_ptr<const Communicator>( new SerialCommunicator );
  else
    return Communicator::getNull();
}

// Create a communicator that is the difference of this
// communicator and another communicator
std::shared_ptr<const Communicator> SerialCommunicator::subtract(
                                               const Communicator& comm ) const
{
  return Communicator::getNull();
}

// Create a timer
std::shared_ptr<Timer> SerialCommunicator::createTimer() const
{
  return GlobalOpenMPSession::createTimer();
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
