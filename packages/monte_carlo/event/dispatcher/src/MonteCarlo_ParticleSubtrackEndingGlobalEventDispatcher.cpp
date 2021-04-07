//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending global event dispatcher
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Dispatch the new event to the observers
void ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  if( this->hasObserverSet( particle.getParticleType() ) )
  {
    ObserverSet& observer_set =
      this->getObserverSet( particle.getParticleType() );
  
    ObserverSet::iterator it = observer_set.begin();
    
    while( it != observer_set.end() )
    {
      (*it)->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                          start_point,
                                                          end_point );
      
      ++it;
    }
  }
}

} // end namespace MonteCarlo

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.cpp
//---------------------------------------------------------------------------//
