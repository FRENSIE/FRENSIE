//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_LOCAL_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEnteringCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The particle entering cell event dispatcher class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventLocalDispatcher : public ParticleEventLocalDispatcher<Geometry::Model::InternalCellHandle,ParticleEnteringCellEventObserver>
{

public:

  //! Constructor
  ParticleEnteringCellEventLocalDispatcher(
		    const Geometry::Model::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleEnteringCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleEnteringCellEvent(
	      const ParticleState& particle,
	      const Geometry::Model::InternalCellHandle cell_entering );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
