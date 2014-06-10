//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleEnteringCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleEnteringCellEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle entering cell event dispatcher class
class ParticleEnteringCellEventDispatcher{
  
public:

  //! Constructor
  ParticleEnteringCellEventDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleEnteringCellEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver( 
		   const ModuleTraits::InternalEstimatorHandle id,
		   Teuchos::RCP<ParticleEnteringCellEventObserver>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const ModuleTraits::InternalEstimatorHandle id );

  //! Dispatch the new event to the observers
  void dispatchParticleEnteringCellEvent( 
	      const ParticleState& particle,
	      const Geometry::ModuleTraits::InternalCellHandle cell_entering );

  //! Get the cell id corresponding to this particle entering cell event disp.
  Geometry::ModuleTraits::InternalCellHandle getCellId() const;

private:

  // The cell handle for which particle entering cell events will be dispatched
  Geometry::ModuleTraits::InternalCellHandle d_cell_id;

  // The observer map
  typedef boost::unordered_map<ModuleTraits::InternalEstimatorHandle,
			      Teuchos::RCP<ParticleEnteringCellEventObserver> >
  ObserverIdMap;

  ObserverIdMap d_observer_map;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleEnteringCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
