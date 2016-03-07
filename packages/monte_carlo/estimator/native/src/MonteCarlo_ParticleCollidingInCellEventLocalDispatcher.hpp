//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

/*! The particle colliding in cell event dispatcher
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventLocalDispatcher :
    public ParticleEventLocalDispatcher<Geometry::ModuleTraits::InternalCellHandle,
                                        ParticleCollidingInCellEventObserver>
{

public:

  //! Constructor
  ParticleCollidingInCellEventLocalDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleCollidingInCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
