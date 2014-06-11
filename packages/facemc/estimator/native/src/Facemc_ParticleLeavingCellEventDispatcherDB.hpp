//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleLeavingCellEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_DP_HPP
#define FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_DP_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleLeavingCellEventDispatcher.hpp"

namespace Facemc{

//! The particle leaving cell event dispatcher database class
class ParticleLeavingCellEventDispatcherDB
{
  
public:

  //! Get the appropriate dispatcher for the given cell id
  static Teuchos::RCP<ParticleLeavingCellEventDispatcher>& getDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id,
		    Teuchos::RCP<ParticleLeavingCellEventObserver>& observer );

  //! Attach an observer to the apropriate dispatcher
  static void attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleLeavingCellEventObserver* observer );

  //! Detach the observer from the appropriate dispatcher
  static void detachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver(
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Dispatch the particle leaving cell event to the observers
  static void dispatchParticleLeavingCellEvent(
	       const ParticleState& particle,
	       const Geometry::ModuleTraits::InternalCellHandle cell_leaving );

private:

  // Constructor
  ParticleLeavingCellEventDispatcherDB();

  // Typedef for the dispatcher map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			     Teuchos::RCP<ParticleLeavingCellEventDispatcher> >
  DispatcherMap;

  static DispatcherMap master_map;
};

// Attach an observer
/*! \details A non-owning Teuchos::RCP will be constructed from the raw 
 * pointer. This function should be used from inside of observer constructors.
 * The observer destructor should call the detachObserver method to avoid
 * null pointer dereferencing in the dispatchers.
 */
inline void ParticleLeavingCellEventDispatcherDB::attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleLeavingCellEventObserver* observer )
{
  Teuchos::RCP<ParticleLeavingCellEventObserver> safe_observer( observer,
								false );
  
  ParticleLeavingCellEventDispatcherDB::attachObserver( cell_id,
							estimator_id,
							safe_observer );
}

// Dispatch the particle leaving cell event to the observers
inline void
ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent( 
	        const ParticleState& particle,
	        const Geometry::ModuleTraits::InternalCellHandle cell_leaving )
{
  DispatcherMap::iterator it = 
    ParticleLeavingCellEventDispatcherDB::master_map.find( cell_leaving );

  if( it != ParticleLeavingCellEventDispatcherDB::master_map.end() )
    it->second->dispatchParticleLeavingCellEvent( particle, cell_leaving );
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_LEAVING_CELL_EVENT_DISPATCHER_DP_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleLeavingCellEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
