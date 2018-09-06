//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Dispatch the particle entering cell event to the observers
void ParticleCollidingInCellEventDispatcher::dispatchParticleCollidingInCellEvent(
                             const ParticleState& particle,
                             const Geometry::Model::EntityId cell_of_collision,
                             const double inverse_total_cross_section )
{
  DispatcherMap::iterator it =
    this->getDispatcherMap().find( cell_of_collision );

  if( it != this->getDispatcherMap().end() )
  {
    it->second->dispatchParticleCollidingInCellEvent(
						 particle,
						 cell_of_collision,
						 inverse_total_cross_section );
  }
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleCollidingInCellEventDispatcher );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCollidingInCellEventDispatcher );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
