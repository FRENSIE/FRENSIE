//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGoneGlobalEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle gone global event dispatcher declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleGoneGlobalEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Dispatch the new event to the observers
void ParticleGoneGlobalEventDispatcher::dispatchParticleGoneGlobalEvent(
                                                const ParticleState& particle )
{
  if( this->hasObserverSet( particle.getParticleType() ) )
  {
    ObserverSet& observer_set =
      this->getObserverSet( particle.getParticleType() );
    
    ObserverSet::iterator it = observer_set.begin();
    
    while( it != observer_set.end() )
    {
      (*it)->updateFromGlobalParticleGoneEvent( particle );
      
      ++it;
    }
  }
}
  
} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleGoneGlobalEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGoneGlobalEventDispatcher.cpp
//---------------------------------------------------------------------------//
