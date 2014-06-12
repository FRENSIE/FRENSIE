//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleCollidingInCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleCollidingInCellEventDispatcher.hpp"

namespace Facemc{

//! The particle colliding in cell event dispatcher database class
class ParticleCollidingInCellEventDispatcherDB
{

public:

  //! Get the appropriate dispatcher for the given cell id
  static Teuchos::RCP<ParticleCollidingInCellEventDispatcher>& getDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		const Geometry::ModuleTraits::InternalCellHandle cell_id,
		const ModuleTraits::InternalEstimatorHandle estimator_id,
		Teuchos::RCP<ParticleCollidingInCellEventObserver>& observer );
  
  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach all observers
  static void detachAllObservers();

  //! Dispatch the particle colliding in cell event to the observers
  static void dispatchParticleCollidingInCellEvent( 
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section );

private:

  // Constructor
  ParticleCollidingInCellEventDispatcherDB();

  // Typedef for the dispatcher map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			 Teuchos::RCP<ParticleCollidingInCellEventDispatcher> >
  DispatcherMap;

  static DispatcherMap master_map;
};

// Dispatch the particle entering cell event to the observers
inline void
ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
	    const ParticleState& particle,
	    const Geometry::ModuleTraits::InternalCellHandle cell_of_collision,
	    const double inverse_total_cross_section )
{
  DispatcherMap::iterator it = 
    ParticleCollidingInCellEventDispatcherDB::master_map.find( 
							   cell_of_collision );

  if( it != ParticleCollidingInCellEventDispatcherDB::master_map.end() )
  {
    it->second->dispatchParticleCollidingInCellEvent( 
						 particle, 
						 cell_of_collision,
						 inverse_total_cross_section );
  }
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
