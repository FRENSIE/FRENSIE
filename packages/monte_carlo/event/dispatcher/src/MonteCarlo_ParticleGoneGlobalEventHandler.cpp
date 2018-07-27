//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGoneGlobalEventHandler.cpp
//! \author Alex Robinson
//! \brief  The particle subtrack ending global event handler definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleGoneGlobalEventHandler.hpp"

namespace MonteCarlo{

// Constructor
ParticleGoneGlobalEventHandler::ParticleGoneGlobalEventHandler()
  : d_particle_gone_global_event_dispatcher()
{ /* ... */ }

// Return the particle subtrack ending global event dispatcher
ParticleGoneGlobalEventDispatcher&
ParticleGoneGlobalEventHandler::getParticleGoneGlobalEventDispatcher()
{
  return d_particle_gone_global_event_dispatcher;
}

// Return the particle subtrack ending global event dispatcher
const ParticleGoneGlobalEventDispatcher&
ParticleGoneGlobalEventHandler::getParticleGoneGlobalEventDispatcher() const
{
  return d_particle_gone_global_event_dispatcher;
}

// Update the global estimators from a subtrack ending event
void ParticleGoneGlobalEventHandler::updateObserversFromParticleGoneGlobalEvent(
                                                const ParticleState& particle )
{
  d_particle_gone_global_event_dispatcher.dispatchParticleGoneGlobalEvent( particle );
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleGoneGlobalEventHandler );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGoneGlobalEventHandler.cpp
//---------------------------------------------------------------------------//
