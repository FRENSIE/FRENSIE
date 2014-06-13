//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCollidingInCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleCollidingInCellEventDispatcher.hpp"
#include "Facemc_ParticleEventDispatcherDB.hpp"

namespace Facemc{

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

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
