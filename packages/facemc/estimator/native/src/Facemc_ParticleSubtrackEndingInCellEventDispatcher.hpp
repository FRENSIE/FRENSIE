//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_ParticleSubtrackEndingInCellEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event dispatcher class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The particle subtrack ending in cell event dispatcher class
class ParticleSubtrackEndingInCellEventDispatcher
{
  
public:

  //! Constructor
  ParticleSubtrackEndingInCellEventDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleSubtrackEndingInCellEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver(
	   const ModuleTraits::InternalEstimatorHandle id,
	   Teuchos::RCP<ParticleSubtrackEndingInCellEventObserver>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const ModuleTraits::InternalEstimatorHandle id );

  //! Dispatch the new event to the observers
  void dispatchParticleSubtrackEndingInCellEvent(
	     const ParticleState& particle,
	     const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
	     const double track_length );

  //! Get the cell id corresponding to this particle entering cell event disp.
  Geometry::ModuleTraits::InternalCellHandle getCellId() const;

private:

  // The cell handle for which particle entering cell events will be dispatched
  Geometry::ModuleTraits::InternalCellHandle d_cell_id;

  // The observer map
  typedef boost::unordered_map<ModuleTraits::InternalEstimatorHandle,
		      Teuchos::RCP<ParticleSubtrackEndingInCellEventObserver> >
  ObserverIdMap;

  ObserverIdMap d_observer_map;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSubtrackEndingInCellEventDispatcher.hpp
//---------------------------------------------------------------------------//
