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

  //! The event tag type
  struct ParticleCrossingSurfaceEvent{};

  //! Typedef for the observer event tag
  typedef ParticleCrossingSurfaceEvent EventTag;

  //! Constructor
  ParticleCrossingSurfaceEventObserver()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleCrossingSurfaceEventObserver()
  { /* ... */ }

  //! Update the observer
  virtual void updateFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine ) = 0;
};
  
} // end Facemc namespace

#endif // end FACEMC_PARTICLE_CROSSING_SURFACE_EVENT_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCrossingSurfaceEventObserver.hpp
//---------------------------------------------------------------------------//
