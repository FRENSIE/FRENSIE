//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleEnteringCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleEnteringCellEventDispatcher.hpp"

namespace Facemc{

//! The particle entering cell event dispatcher database class
class ParticleEnteringCellEventDispatcherDB
{

public:

  //! Get the appropriate dispatcher for the given cell id
  static Teuchos::RCP<ParticleEnteringCellEventDispatcher>& getDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		   const Geometry::ModuleTraits::InternalCellHandle cell_id,
		   const ModuleTraits::InternalEstimatorHandle estimator_id,
		   Teuchos::RCP<ParticleEnteringCellEventObserver>& observer );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleEnteringCellEventObserver* observer );
  
  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Dispatch the particle entering cell event to the observers
  static void dispatchParticleEnteringCellEvent( 
	      const ParticleState& particle,
	      const Geometry::ModuleTraits::InternalCellHandle cell_entering );

private:

  // Constructor
  ParticleEnteringCellEventDispatcherDB();

  // Typedef for the dispatcher map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			    Teuchos::RCP<ParticleEnteringCellEventDispatcher> >
  DispatcherMap;

  static DispatcherMap master_map;
};

// Attach an observer
/*! \details A non-owning Teuchos::RCP will be constructed from the raw 
 * pointer. This function should be used from inside of observer constructors.
 * The observer destructor should call the detachObserver method to avoid
 * null pointer dereferencing in the dispatchers.
 */
inline void ParticleEnteringCellEventDispatcherDB::attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleEnteringCellEventObserver* observer )
{
  Teuchos::RCP<ParticleEnteringCellEventObserver> safe_observer( observer,
								 false );
  
  ParticleEnteringCellEventDispatcherDB::attachObserver( cell_id,
							 estimator_id,
							 safe_observer );
}

// Dispatch the particle entering cell event to the observers
inline void
ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent( 
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_entering )
{
  DispatcherMap::iterator it = 
    ParticleEnteringCellEventDispatcherDB::master_map.find( cell_entering );

  if( it != ParticleEnteringCellEventDispatcherDB::master_map.end() )
    it->second->dispatchParticleEnteringCellEvent( particle, cell_entering );
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_ENTERING_CELL_EVENT_DISPATCHER_DP_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleEnteringCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
