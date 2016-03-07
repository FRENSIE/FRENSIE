//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending in cell event dispatcher class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventLocalDispatcher : public ParticleEventLocalDispatcher<Geometry::ModuleTraits::InternalCellHandle,ParticleSubtrackEndingInCellEventObserver>
{
  
public:

  //! Constructor
  ParticleSubtrackEndingInCellEventLocalDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleSubtrackEndingInCellEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
	     const double track_length );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
