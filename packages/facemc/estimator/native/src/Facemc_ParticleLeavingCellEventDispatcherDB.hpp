//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_DP_HPP
#define FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_DP_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleLeavingCellEventDispatcher.hpp"
#include "Facemc_ParticleEventDispatcherDB.hpp"

namespace Facemc{

//! The particle leaving cell event dispatcher database class
class ParticleLeavingCellEventDispatcherDB :
    public ParticleEventDispatcherDB<ParticleLeavingCellEventDispatcher>
{
  
public:

  //! Dispatch the particle leaving cell event to the observers
  static void dispatchParticleLeavingCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_leaving );

private:

  // Constructor
  ParticleLeavingCellEventDispatcherDB();
};

// Dispatch the particle leaving cell event to the observers
inline void
ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent( 
	        const ParticleState& particle,
	        const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  DispatcherMap::iterator it = 
    ParticleLeavingCellEventDispatcherDB::master_disp_map().find(cell_leaving);

  if( it != ParticleLeavingCellEventDispatcherDB::master_disp_map().end() )
    it->second->dispatchParticleLeavingCellEvent( particle, cell_leaving );
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_DP_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
