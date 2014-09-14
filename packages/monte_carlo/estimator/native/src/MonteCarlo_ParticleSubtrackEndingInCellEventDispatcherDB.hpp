//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher database decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcherDB.hpp"

namespace MonteCarlo{

//! The particle subtrack ending in cell event dispatcher database class
class ParticleSubtrackEndingInCellEventDispatcherDB :
    public ParticleEventDispatcherDB<ParticleSubtrackEndingInCellEventDispatcher>
{

public:

  //! Dispatch the particle subtrack ending in cell event to the observers
  static void dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
	     const double track_length );

private:

  // Constructor
  ParticleSubtrackEndingInCellEventDispatcherDB();
};

// Dispatch the particle subtrack ending in cell event to the observers
inline void 
ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle  cell_of_subtrack,
	    const double track_length )
{
  DispatcherMap::iterator it = 
    ParticleSubtrackEndingInCellEventDispatcherDB::master_disp_map().find( 
							    cell_of_subtrack );

  if( it != ParticleSubtrackEndingInCellEventDispatcherDB::master_disp_map().end() )
  {
    it->second->dispatchParticleSubtrackEndingInCellEvent( particle, 
							   cell_of_subtrack,
							   track_length );
  }
}

} // end MonteCarlo namespace

#endif // end FACEMC_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
