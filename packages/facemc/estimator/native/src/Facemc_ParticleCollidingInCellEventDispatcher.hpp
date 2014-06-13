//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCollidingInCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleEventDispatcher.hpp"
#include "Facemc_ParticleCollidingInCellEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle colliding in cell event dispatcher
class ParticleCollidingInCellEventDispatcher :
    public ParticleEventDispatcher<Geometry::ModuleTraits::InternalCellHandle,
				   ParticleCollidingInCellEventObserver>
{

public:

  //! Constructor
  ParticleCollidingInCellEventDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleCollidingInCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section );
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
