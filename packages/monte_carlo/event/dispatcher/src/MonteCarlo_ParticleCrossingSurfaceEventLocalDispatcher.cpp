//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ParticleCrossingSurfaceEventLocalDispatcher::ParticleCrossingSurfaceEventLocalDispatcher()
{ /* ... */ }
  
// Constructor
ParticleCrossingSurfaceEventLocalDispatcher::ParticleCrossingSurfaceEventLocalDispatcher(
                                   const Geometry::Model::EntityId surface_id )
  : BaseType( surface_id )
{ /* ... */ }

// Dispatch the new event ot the observers
void ParticleCrossingSurfaceEventLocalDispatcher::dispatchParticleCrossingSurfaceEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId surface_crossing,
                              const double angle_cosine )
{
  // Make sure the surface being crossed is valid
  testPrecondition( surface_crossing == this->getEntityId() );

  if( this->hasObserverSet( particle.getParticleType() ) )
  {
    ObserverSet& observer_set =
      this->getObserverSet( particle.getParticleType() );
    
    ObserverSet::iterator it = observer_set.begin();
    
    while( it != observer_set.end() )
    {
      (*it)->updateFromParticleCrossingSurfaceEvent( particle,
                                                     surface_crossing,
                                                     angle_cosine );
      
      ++it;
    }
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleCrossingSurfaceEventLocalDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCrossingSurfaceEventLocalDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
