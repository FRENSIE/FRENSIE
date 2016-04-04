//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEnsingGlobalEventHandler.cpp
//! \author Alex Robinson
//! \brief  The particle subtrack ending global event handler definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventHandler.hpp"

namespace MonteCarlo{

// Constructor
ParticleSubtrackEndingGlobalEventHandler::ParticleSubtrackEndingGlobalEventHandler()
  : d_particle_subtrack_ending_global_event_dispatcher()
{ /* ... */ }

// Return the particle subtrack ending global event dispatcher
ParticleSubtrackEndingGlobalEventDispatcher&
ParticleSubtrackEndingGlobalEventHandler::getParticleSubtrackEndingGlobalEventDispatcher()
{
  return d_particle_subtrack_ending_global_event_dispatcher;
}

// Return the particle subtrack ending global event dispatcher
const ParticleSubtrackEndingGlobalEventDispatcher&
ParticleSubtrackEndingGlobalEventHandler::getParticleSubtrackEndingGlobalEventDispatcher() const
{
  return d_particle_subtrack_ending_global_event_dispatcher;
}

// Update the global estimators from a subtrack ending event
void ParticleSubtrackEndingGlobalEventHandler::updateObserversFromParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  d_particle_subtrack_ending_global_event_dispatcher.dispatchParticleSubtrackEndingGlobalEvent(
								   particle,
								   start_point,
								   end_point );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventHandler.cpp
//---------------------------------------------------------------------------//
