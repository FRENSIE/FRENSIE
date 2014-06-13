//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleEventDispatcher.hpp"
#include "Facemc_ParticleLeavingCellEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle leaving cell event dispatcher 
class ParticleLeavingCellEventDispatcher :
    public ParticleEventDispatcher<Geometry::ModuleTraits::InternalCellHandle,
				   ParticleLeavingCellEventObserver>
{

public:

  //! Constructor
  ParticleLeavingCellEventDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleLeavingCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleLeavingCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_leaving );
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
