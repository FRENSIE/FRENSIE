//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Dispatch the particle crossing surface event to the observers
void ParticleCrossingSurfaceEventDispatcher::dispatchParticleCrossingSurfaceEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId surface_crossing,
                              const double angle_cosine )
{
  DispatcherMap::iterator it = this->getDispatcherMap().find( surface_crossing );

  if( it != this->getDispatcherMap().end() )
  {
    it->second->dispatchParticleCrossingSurfaceEvent( particle,
						      surface_crossing,
						      angle_cosine );
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleCrossingSurfaceEventDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCrossingSurfaceEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventDispatcher.cpp
//---------------------------------------------------------------------------//
