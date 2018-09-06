//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ParticleEnteringCellEventLocalDispatcher::ParticleEnteringCellEventLocalDispatcher()
{ /* ... */ }
  
// Constructor
ParticleEnteringCellEventLocalDispatcher::ParticleEnteringCellEventLocalDispatcher(
                                      const Geometry::Model::EntityId cell_id )
  : BaseType( cell_id )
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleEnteringCellEventLocalDispatcher::dispatchParticleEnteringCellEvent(
                                const ParticleState& particle,
                                const Geometry::Model::EntityId cell_entering )
{
  // Make sure the cell being entered is valid
  testPrecondition( cell_entering == this->getEntityId() );

  if( this->hasObserverSet( particle.getParticleType() ) )
  {
    ObserverSet& observer_set =
      this->getObserverSet( particle.getParticleType() );
    
    ObserverSet::iterator it = observer_set.begin();
    
    while( it != observer_set.end() )
    {
      (*it)->updateFromParticleEnteringCellEvent( particle, cell_entering );
      
      ++it;
    }
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleEnteringCellEventLocalDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleEnteringCellEventLocalDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
