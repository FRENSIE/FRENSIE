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

// Default constructor
ParticleCollidingInCellEventLocalDispatcher::ParticleCollidingInCellEventLocalDispatcher()
{ /* ... */ }

// Constructor
ParticleCollidingInCellEventLocalDispatcher::ParticleCollidingInCellEventLocalDispatcher(
                                      const Geometry::Model::EntityId cell_id )
  : BaseType( cell_id )
{ /* ... */ }

// Dispatch the new event to the observers
void
ParticleCollidingInCellEventLocalDispatcher::dispatchParticleCollidingInCellEvent(
                             const ParticleState& particle,
                             const Geometry::Model::EntityId cell_of_collision,
                             const double inverse_total_cross_section )
{
  // Make sure the cell being collided in is valid
  testPrecondition( cell_of_collision == this->getEntityId() );

  if( this->hasObserverSet( particle.getParticleType() ) )
  {
    ObserverSet& observer_set =
      this->getObserverSet( particle.getParticleType() );
  
    ObserverSet::iterator it = observer_set.begin();

    while( it != observer_set.end() )
    {
      (*it)->updateFromParticleCollidingInCellEvent( particle,
                                                     cell_of_collision,
                                                     inverse_total_cross_section );

      ++it;
    }
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleCollidingInCellEventLocalDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCollidingInCellEventLocalDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
