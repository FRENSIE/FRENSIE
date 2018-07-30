//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher database class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleLeavingCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Dispatch the particle leaving cell event to the observers
void ParticleLeavingCellEventDispatcher::dispatchParticleLeavingCellEvent(
                                 const ParticleState& particle,
	                         const Geometry::Model::EntityId cell_leaving )
{
  DispatcherMap::iterator it = this->getDispatcherMap().find( cell_leaving );

  if( it != this->getDispatcherMap().end() )
    it->second->dispatchParticleLeavingCellEvent( particle, cell_leaving );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleLeavingCellEventDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleLeavingCellEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
