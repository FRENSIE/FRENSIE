//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventHandler.cpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event handler definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleLeavingCellEventHandler.hpp"

namespace MonteCarlo{

// Constructor
ParticleLeavingCellEventHandler::ParticleLeavingCellEventHandler()
  : d_particle_leaving_cell_event_dispatcher()
{ /* ... */ }

// Return the particle leaving cell event dispatcher
ParticleLeavingCellEventDispatcher&
ParticleLeavingCellEventHandler::getParticleLeavingCellEventDispatcher()
{
  return d_particle_leaving_cell_event_dispatcher;
}

// Return the particle leaving cell event dispatcher
const ParticleLeavingCellEventDispatcher&
ParticleLeavingCellEventHandler::getParticleLeavingCellEventDispatcher() const
{
  return d_particle_leaving_cell_event_dispatcher;
}

// Update the observers from a particle leaving cell event
void ParticleLeavingCellEventHandler::updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  d_particle_leaving_cell_event_dispatcher.dispatchParticleLeavingCellEvent(
                                                                particle,
                                                                cell_leaving );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventHandler.cpp
//---------------------------------------------------------------------------//
