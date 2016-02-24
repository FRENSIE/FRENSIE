//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventDispatcher.hpp"
#include "MonteCarlo_ParticleLeavingCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
