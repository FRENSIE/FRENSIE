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

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleCollidingInCellEventObserver* observer );
  
  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

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

// Attach an observer
/*! \details A non-owning Teuchos::RCP will be constructed from the raw 
 * pointer. This function should be used from inside of observer constructors.
 * The observer destructor should call the detachObserver method to avoid
 * null pointer dereferencing in the dispatchers.
 */
inline void ParticleCollidingInCellEventDispatcherDB::attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleCollidingInCellEventObserver* observer )
{
  Teuchos::RCP<ParticleCollidingInCellEventObserver> safe_observer( observer,
								    false );
  
  ParticleCollidingInCellEventDispatcherDB::attachObserver( cell_id,
							    estimator_id,
							    safe_observer );
}

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

} // end Facemc

#endif // end FACEMC_PARTICLE_COLLIDING_IN_CELL_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleCollidingInCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
