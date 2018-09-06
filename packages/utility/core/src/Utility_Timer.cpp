//---------------------------------------------------------------------------//
//!
//! \file   Utility_Timer.cpp
//! \author Alex Robinson
//! \brief  The timer base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_Timer.hpp"
#include "Utility_StandardTimer.hpp"

namespace Utility{

// Create a default timer
std::shared_ptr<Timer> createDefaultTimer()
{
  return std::shared_ptr<Timer>( new StandardTimer<std::chrono::high_resolution_clock>() );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_Timer.cpp
//---------------------------------------------------------------------------//
