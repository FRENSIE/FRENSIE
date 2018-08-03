//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventHandler.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event handler definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventHandler.hpp"

namespace MonteCarlo{

// Constructor
ParticleSubtrackEndingInCellEventHandler::ParticleSubtrackEndingInCellEventHandler()
  : d_particle_subtrack_ending_in_cell_event_dispatcher()
{ /* ... */ }

// Return the particle subtrack ending in cell event dispatcher
ParticleSubtrackEndingInCellEventDispatcher&
ParticleSubtrackEndingInCellEventHandler::getParticleSubtrackEndingInCellEventDispatcher()
{
  return d_particle_subtrack_ending_in_cell_event_dispatcher;
}

// Return the particle subtrack ending in cell event dispatcher
const ParticleSubtrackEndingInCellEventDispatcher&
ParticleSubtrackEndingInCellEventHandler::getParticleSubtrackEndingInCellEventDispatcher() const
{
  return d_particle_subtrack_ending_in_cell_event_dispatcher;
}

// Update the observers from a particle subtrack ending in cell event
void ParticleSubtrackEndingInCellEventHandler::updateObserversFromParticleSubtrackEndingInCellEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId cell_of_subtrack,
                              const double particle_subtrack_length )
{
  d_particle_subtrack_ending_in_cell_event_dispatcher.dispatchParticleSubtrackEndingInCellEvent(
						    particle,
						    cell_of_subtrack,
						    particle_subtrack_length );
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleSubtrackEndingInCellEventHandler );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventHandler.cpp
//---------------------------------------------------------------------------//
