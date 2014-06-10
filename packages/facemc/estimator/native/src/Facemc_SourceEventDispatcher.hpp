//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Source event dispatcher singleton class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SOURCE_EVENT_DISPATCHER_HPP
#define FACEMC_SOURCE_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_SourceEventObserver.hpp"
#include "Facemc_ParticleState.hpp"
#include "Facemc_Estimator.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The source event dispatcher class
class SourceEventDispatcher{
  
public:

  //! Constructor
  SourceEventDispatcher( 
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~SourceEventDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver( const Estimator::idType id,
		       const Teuchos::RCP<SourceEventObserver>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const Estimator::idType id );

  //! Set a new event and dispatch to the observers
  void dispatchSourceEvent( const ParticleState& particle );

  //! Get the cell id corresponding to this source event dispatcher
  Geometry::ModuleTraits::InternalCellHandle getCellId() const;
  
private:

  // The cell handle for which source events will be dispatched
  Geometry::ModuleTraits::InternalCellHandle d_cell_id

  // The observer map
  typedef boost::unordered_map<Estimator::idType,
			       Teuchos::RCP<SourceEventObserver> > 
  ObserverIdMap
  
  ObserverIdMap d_observer_map;
};

} // end Facemc namespace

#endif // end FACEMC_SOURCE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end Facemc_SourceEventDispatcher.hpp
//---------------------------------------------------------------------------//
