//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleLeavingCellEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle leaving cell event dispatcher database class
 * \ingroup particle_leaving_cell_event
 */
class ParticleLeavingCellEventDispatcher : public ParticleEventDispatcher<ParticleLeavingCellEventLocalDispatcher>
{
  
public:

  //! Constructor
  ParticleLeavingCellEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleLeavingCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle leaving cell event to the observers
  void dispatchParticleLeavingCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_leaving );
};

// Dispatch the particle leaving cell event to the observers
inline void
ParticleLeavingCellEventDispatcher::dispatchParticleLeavingCellEvent( 
	        const ParticleState& particle,
	        const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  DispatcherMap::iterator it = this->dispatcher_map().find( cell_leaving );

  if( it != this->dispatcher_map().end() )
    it->second->dispatchParticleLeavingCellEvent( particle, cell_leaving );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
