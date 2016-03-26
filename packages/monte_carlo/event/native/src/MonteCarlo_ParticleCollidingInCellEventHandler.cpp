//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventHandler.cpp
//! \author Alex Robinson
//! \brief  The particle colliding in cell event handler definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventHandler.hpp"

namespace MonteCarlo{

// Constructor
ParticleCollidingInCellEventHandler::ParticleCollidingInCellEventHandler()
  : d_particle_colliding_in_cell_event_dispatcher()
{ /* ... */ }

// Return the particle colliding in cell event dispatcher
ParticleCollidingInCellEventDispatcher& 
ParticleCollidingInCellEventHandler::getParticleCollidingInCellEventDispatcher()
{
  return d_particle_colliding_in_cell_event_dispatcher;
}

// Return the particle colliding in cell event dispatcher
const ParticleCollidingInCellEventDispatcher&
ParticleCollidingInCellEventHandler::getParticleCollidingInCellEventDispatcher() const
{
  return d_particle_colliding_in_cell_event_dispatcher;
}

// Update the observers from a particle colliding in cell event
void ParticleCollidingInCellEventHandler::updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section )
{
  d_particle_colliding_in_cell_event_dispatcher.dispatchParticleCollidingInCellEvent(
						 particle,
						 particle.getCell(),
						 inverse_total_cross_section );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventHandler.hpp
//---------------------------------------------------------------------------//
