//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventDispatcher.hpp"
#include "MonteCarlo_ParticleEnteringCellEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The particle entering cell event dispatcher class
class ParticleEnteringCellEventDispatcher :
    public ParticleEventDispatcher<Geometry::ModuleTraits::InternalCellHandle,
				   ParticleEnteringCellEventObserver>
{
  
public:

  //! Constructor
  ParticleEnteringCellEventDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleEnteringCellEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleEnteringCellEvent( 
	      const ParticleState& particle,
	      const Geometry::ModuleTraits::InternalCellHandle cell_entering );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
