//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Dispatch the particle entering cell event to the observers
void ParticleEnteringCellEventDispatcher::dispatchParticleEnteringCellEvent(
                                const ParticleState& particle,
                                const Geometry::Model::EntityId cell_entering )
{
  DispatcherMap::iterator it = this->getDispatcherMap().find( cell_entering );

  if( it != this->getDispatcherMap().end() )
    it->second->dispatchParticleEnteringCellEvent( particle, cell_entering );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleEnteringCellEventDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleEnteringCellEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
