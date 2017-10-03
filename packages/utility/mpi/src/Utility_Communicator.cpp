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

namespace Utility{

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

  return std::shared_ptr<const Communicator>( new SerialCommunicator );
}

// Determine if this communicator is valid for communication
Communicator::operator bool() const
{ return this->isValid(); }

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_Communicator.cpp
//---------------------------------------------------------------------------//
