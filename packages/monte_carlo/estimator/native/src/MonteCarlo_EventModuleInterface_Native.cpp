//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventModuleInterface_Native.cpp
//! \author Alex Robinson
//! \brief  Event module interface class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EventModuleInterface_Native.hpp"

namespace MonteCarlo{

// Initialize the static member data
std::shared_ptr<MonteCarlo::EventHandler> 
EventModuleInterface<MonteCarlo::EventHandler>::s_event_handler;

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EventModuleInterface_Native.cpp
//---------------------------------------------------------------------------//
