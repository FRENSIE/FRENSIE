//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcherDB.hpp"

namespace MonteCarlo{

//! The particle colliding in cell event dispatcher database class
class ParticleCollidingInCellEventDispatcherDB :
    public ParticleEventDispatcherDB<ParticleCollidingInCellEventDispatcher>
{

public:

  //! Dispatch the particle colliding in cell event to the observers
  static void dispatchParticleCollidingInCellEvent( 
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section );

private:

  // Constructor
  ParticleCollidingInCellEventDispatcherDB();
};

// Dispatch the particle entering cell event to the observers
inline void
ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section )
{
  DispatcherMap::iterator it = 
    ParticleCollidingInCellEventDispatcherDB::master_disp_map().find( 
							   cell_of_collision );

  if( it != ParticleCollidingInCellEventDispatcherDB::master_disp_map().end() )
  {
    it->second->dispatchParticleCollidingInCellEvent( 
						 particle, 
						 cell_of_collision,
						 inverse_total_cross_section );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
