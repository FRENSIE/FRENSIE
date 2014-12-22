//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcherDB.hpp"

namespace MonteCarlo{

//! The particle entering cell event dispatcher database class
class ParticleEnteringCellEventDispatcherDB :
    public ParticleEventDispatcherDB<ParticleEnteringCellEventDispatcher>
{

public:

  //! Dispatch the particle entering cell event to the observers
  static void dispatchParticleEnteringCellEvent( 
	      const ParticleState& particle,
	      const Geometry::ModuleTraits::InternalCellHandle cell_entering );

private:

  // Constructor
  ParticleEnteringCellEventDispatcherDB();
};

// Dispatch the particle entering cell event to the observers
inline void
ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent( 
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  DispatcherMap::iterator it = 
    ParticleEnteringCellEventDispatcherDB::master_disp_map().find( 
							       cell_entering );

  if( it != ParticleEnteringCellEventDispatcherDB::master_disp_map().end() )
    it->second->dispatchParticleEnteringCellEvent( particle, cell_entering );
}

} // end MonteCarlo namespace

#endif // end FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_DP_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
