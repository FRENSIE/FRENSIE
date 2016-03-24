//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle entering cell event dispatcher database class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventDispatcher : public ParticleEventDispatcher<ParticleEnteringCellEventLocalDispatcher>
{

public:

  //! Constructor
  ParticleEnteringCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleEnteringCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle entering cell event to the observers
  void dispatchParticleEnteringCellEvent( 
	      const ParticleState& particle,
	      const Geometry::ModuleTraits::InternalCellHandle cell_entering );
};

// Dispatch the particle entering cell event to the observers
inline void
ParticleEnteringCellEventDispatcher::dispatchParticleEnteringCellEvent( 
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  DispatcherMap::iterator it = this->dispatcher_map().find( cell_entering );

  if( it != this->dispatcher_map().end() )
    it->second->dispatchParticleEnteringCellEvent( particle, cell_entering );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
