//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher database decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending in cell event dispatcher database class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventDispatcher : public ParticleEventDispatcher<ParticleSubtrackEndingInCellEventLocalDispatcher>
{

public:

  //! Constructor
  ParticleSubtrackEndingInCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleSubtrackEndingInCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle subtrack ending in cell event to the observers
  void dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
	     const double track_length );
};

// Dispatch the particle subtrack ending in cell event to the observers
inline void 
ParticleSubtrackEndingInCellEventDispatcher::dispatchParticleSubtrackEndingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle  cell_of_subtrack,
	    const double track_length )
{
  DispatcherMap::iterator it = this->dispatcher_map().find( cell_of_subtrack );

  if( it != this->dispatcher_map().end() )
  {
    it->second->dispatchParticleSubtrackEndingInCellEvent( particle, 
							   cell_of_subtrack,
							   track_length );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
