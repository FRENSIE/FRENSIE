//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventHandler.cpp
//! \author Alex Robinson
//! \brief  The particle entering cell event handler definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventHandler.hpp"

namespace MonteCarlo{

// Constructor
ParticleEnteringCellEventHandler::ParticleEnteringCellEventHandler()
  : d_particle_entering_cell_event_dispatcher()
{ /* ... */ }

// Return the particle entering cell event dispatcher
ParticleEnteringCellEventDispatcher&
ParticleEnteringCellEventHandler::getParticleEnteringCellEventDispatcher()
{
  return d_particle_entering_cell_event_dispatcher;
}

// Return the particle entering cell event dispatcher
const ParticleEnteringCellEventDispatcher&
ParticleEnteringCellEventHandler::getParticleEnteringCellEventDispatcher() const
{
  return d_particle_entering_cell_event_dispatcher;
}

// Update the observers from a particle entering cell event
void ParticleEnteringCellEventHandler::updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  d_particle_entering_cell_event_dispatcher.dispatchParticleEnteringCellEvent(
                                                               particle,
                                                               cell_entering );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventHandler.cpp
//---------------------------------------------------------------------------//

