//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_DB_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcherDB.hpp"

namespace MonteCarlo{

//! The particle crossing surface event dispatcher database class
class ParticleCrossingSurfaceEventDispatcherDB :
    public ParticleEventDispatcherDB<ParticleCrossingSurfaceEventDispatcher>
{

public:

  //! Dispatch the particle crossing surface event to the observers
  static void dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );

private:

  // Constructor
  ParticleCrossingSurfaceEventDispatcherDB();
};

// Dispatch the particle crossing surface event to the observers
inline void
ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine )
{
  DispatcherMap::iterator it = 
    ParticleCrossingSurfaceEventDispatcherDB::master_disp_map().find( 
							    surface_crossing );

  if( it != ParticleCrossingSurfaceEventDispatcherDB::master_disp_map().end() )
  {
    it->second->dispatchParticleCrossingSurfaceEvent( particle,
						      surface_crossing,
						      angle_cosine );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
