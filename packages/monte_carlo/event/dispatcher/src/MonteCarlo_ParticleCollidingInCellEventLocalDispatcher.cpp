//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
ParticleCollidingInCellEventLocalDispatcher::ParticleCollidingInCellEventLocalDispatcher(
	                       const Geometry::ModuleTraits::EntityId cell_id )
  : BaseType( cell_id )
{ /* ... */ }

// Dispatch the new event to the observers
void
ParticleCollidingInCellEventLocalDispatcher::dispatchParticleCollidingInCellEvent(
                      const ParticleState& particle,
                      const Geometry::ModuleTraits::EntityId cell_of_collision,
                      const double inverse_total_cross_section )
{
  // Make sure the cell being collided in is valid
  testPrecondition( cell_of_collision == this->getEntityId() );

  ObserverSet& observer_set =
    this->getObserverSet( particle.getParticleType() );
  
  ObserverSet::iterator it = observer_set.begin();

  while( it != observer_set.end() )
  {
    it->second->updateFromParticleCollidingInCellEvent(
						 particle,
						 cell_of_collision,
						 inverse_total_cross_section );

    ++it;
  }
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCollidingInCellEventLocalDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
