//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleEventDispatcher.hpp"
#include "Facemc_ParticleCrossingSurfaceEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle crossing surface event dispatcher class
class ParticleCrossingSurfaceEventDispatcher : 
    public ParticleEventDispatcher<Geometry::ModuleTraits::InternalSurfaceHandle,
				   ParticleCrossingSurfaceEventObserver>
{

public:

  //! Constructor
  ParticleCrossingSurfaceEventDispatcher(
	      const Geometry::ModuleTraits::InternalSurfaceHandle surface_id );

  //! Destructor
  ~ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventDispatcher.hpp
//---------------------------------------------------------------------------//
