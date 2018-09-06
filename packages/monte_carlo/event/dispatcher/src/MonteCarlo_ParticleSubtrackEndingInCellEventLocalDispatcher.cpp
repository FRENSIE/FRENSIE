//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ParticleSubtrackEndingInCellEventLocalDispatcher::ParticleSubtrackEndingInCellEventLocalDispatcher()
{ /* ... */ }
  
// Constructor
ParticleSubtrackEndingInCellEventLocalDispatcher::ParticleSubtrackEndingInCellEventLocalDispatcher(
                                      const Geometry::Model::EntityId cell_id )
  : BaseType( cell_id )
{ /* ... */ }

// Dispatch the new event to the observers
void ParticleSubtrackEndingInCellEventLocalDispatcher::dispatchParticleSubtrackEndingInCellEvent(
                              const ParticleState& particle,
	                      const Geometry::Model::EntityId cell_of_subtrack,
                              const double track_length )
{
  // Make sure the cell being collided with is valid
  testPrecondition( cell_of_subtrack == this->getEntityId() );

  if( this->hasObserverSet( particle.getParticleType() ) )
  {
    ObserverSet& observer_set =
      this->getObserverSet( particle.getParticleType() );
    
    ObserverSet::iterator it = observer_set.begin();
    
    while( it != observer_set.end() )
    {
      (*it)->updateFromParticleSubtrackEndingInCellEvent( particle,
                                                          cell_of_subtrack,
                                                          track_length );
      
      ++it;
    }
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
