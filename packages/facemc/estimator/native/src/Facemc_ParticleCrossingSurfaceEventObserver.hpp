//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCrossingSurfaceEventObserver.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event observer base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP
#define FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_ModuleTraits.hpp"
#include "Facemc_ParticleState.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle crossing surface event observer base class
class ParticleCrossingSurfaceEventObserver
{

public:

  //! Constructor
  ParticleCrossingSurfaceEventObserver(
           const ModuleTraits::InternalEstimatorHandle id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
           const bool auto_register_with_dispatchers );

  //! Destructor
  virtual ~ParticleCrossingSurfaceEventObserver();

  //! Register the observer
  void registerWithParticleCrossingSurfaceEventDispatcher(
	   const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids );

  //! Update the observer
  virtual void updateFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine ) = 0;

private:

  // The estimator id corresponding to this observer
  ModuleTraits::InternalEstimatorHandle d_id;

  // Indicates if the observer has registered
  bool d_is_registered;
};
  
} // end Facemc namespace

#endif // end FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventObserver.hpp
//---------------------------------------------------------------------------//
