//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleLeavingCellEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle leaving cell event dispatcher 
class ParticleLeavingCellEventDispatcher{

public:

  //! Constructor
  ParticleLeavingCellEventDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleLeavingCellEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver(
		    const ModuleTraits::InternalEstimatorHandle id,
		    Teuchos::RCP<ParticleLeavingCellEventObserver>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const ModuleTraits::InternalEstimatorHandle id );

  //! Dispatch the new event to the observers
  void dispatchParticleLeavingCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_leaving );

  //! Get the cell id corresponding to this particle leaving cell event disp.
  Geometry::ModuleTraits::InternalCellHandle getCellId() const;

private:

  // The cell handle for which particle leaving cell events will be dispatched
  Geometry::ModuleTraits::InternalCellHandle d_cell_id;

  // The observer map
  typedef boost::unordered_map<ModuleTraits::InternalEstimatorHandle,
			       Teuchos::RCP<ParticleLeavingCellEventObserver> >
  ObserverIdMap;

  ObserverIdMap d_observer_map;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
