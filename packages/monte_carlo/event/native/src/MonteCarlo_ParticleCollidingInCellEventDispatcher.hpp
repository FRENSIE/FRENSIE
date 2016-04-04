//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle colliding in cell event dispatcher class
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventDispatcher :
    public ParticleEventDispatcher<ParticleCollidingInCellEventLocalDispatcher>
{

public:

  //! Constructor
  ParticleCollidingInCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleCollidingInCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle colliding in cell event to the observers
  void dispatchParticleCollidingInCellEvent( 
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section );
};

// Dispatch the particle entering cell event to the observers
inline void
ParticleCollidingInCellEventDispatcher::dispatchParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section )
{
  DispatcherMap::iterator it = this->dispatcher_map().find(cell_of_collision );

  if( it != this->dispatcher_map().end() )
  {
    it->second->dispatchParticleCollidingInCellEvent( 
						 particle, 
						 cell_of_collision,
						 inverse_total_cross_section );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
