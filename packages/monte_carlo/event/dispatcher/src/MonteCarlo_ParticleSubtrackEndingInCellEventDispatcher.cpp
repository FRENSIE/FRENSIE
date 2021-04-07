//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher database def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{
  
// Dispatch the particle subtrack ending in cell event to the observers
void ParticleSubtrackEndingInCellEventDispatcher::dispatchParticleSubtrackEndingInCellEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId cell_of_subtrack,
                              const double track_length )
{
  DispatcherMap::iterator it =
    this->getDispatcherMap().find( cell_of_subtrack );

  if( it != this->getDispatcherMap().end() )
  {
    it->second->dispatchParticleSubtrackEndingInCellEvent( particle,
							   cell_of_subtrack,
							   track_length );
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
