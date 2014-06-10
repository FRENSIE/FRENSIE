//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleGenerationEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Source event dispatcher singleton class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_GENERATION_EVENT_DISPATCHER_HPP
#define FACEMC_PARTICLE_GENERATION_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleGenerationEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The source event dispatcher class
class ParticleGenerationEventDispatcher{
  
public:

  //! Constructor
  ParticleGenerationEventDispatcher( 
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~ParticleGenerationEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver( const ModuleTraits::InternalEstimatorHandle id,
		       Teuchos::RCP<ParticleGenerationEventObserver>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const ModuleTraits::InternalEstimatorHandle id );

  //! Set a new event and dispatch to the observers
  void dispatchParticleGenerationEvent( const ParticleState& particle );

  //! Get the cell id corresponding to this source event dispatcher
  Geometry::ModuleTraits::InternalCellHandle getCellId() const;
  
private:

  // The cell handle for which source events will be dispatched
  Geometry::ModuleTraits::InternalCellHandle d_cell_id;

  // The observer map
  typedef boost::unordered_map<ModuleTraits::InternalEstimatorHandle,
			       Teuchos::RCP<ParticleGenerationEventObserver> > 
  ObserverIdMap;
  
  ObserverIdMap d_observer_map;
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_GENERATION_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleGenerationEventDispatcher.hpp
//---------------------------------------------------------------------------//
