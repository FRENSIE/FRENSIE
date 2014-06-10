//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleGenerationEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Source event dispatcher database declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_GENERATION_EVENT_DISPATCHER_DB_HPP
#define FACEMC_PARTICLE_GENERATION_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_ParticleGenerationEventDispatcher.hpp"

namespace Facemc{

//! The source event dispatcher class 
class ParticleGenerationEventDispatcherDB
{

public:
  
  //! Get the appropriate dispatcher for the given cell id
  static Teuchos::RCP<ParticleGenerationEventDispatcher>& getDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver( 
		     const Geometry::ModuleTraits::InternalCellHandle cell_id,
		     const ModuleTraits::InternalEstimatorHandle estimator_id,
		     Teuchos::RCP<ParticleGenerationEventObserver>& observer );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleGenerationEventObserver* observer );

  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id,
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver( 
		    const ModuleTraits::InternalEstimatorHandle estimator_id );

  //! Dispatch the source event to the observers
  static void dispatchParticleGenerationEvent( const ParticleState& particle );

private:

  // Constructor
  ParticleGenerationEventDispatcherDB();

  // Typedef for the dispatcher map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			      Teuchos::RCP<ParticleGenerationEventDispatcher> >
  DispatcherMap;

  static DispatcherMap master_map;
};

// Attach an observer
/*! \details A non-owning Teuchos::RCP will be constructed from the raw 
 * pointer. This function should be used from inside of observer constructors.
 * The observer destructor should call the detachObserver method
 */
inline void ParticleGenerationEventDispatcherDB::attachObserver(
                      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const ModuleTraits::InternalEstimatorHandle estimator_id,
		      ParticleGenerationEventObserver* observer )
{
  Teuchos::RCP<ParticleGenerationEventObserver> safe_observer( observer, 
							       false );
    
  ParticleGenerationEventDispatcherDB::attachObserver( cell_id,
					   estimator_id,
					   safe_observer );
}

// Dispatch the source event to the observers
inline void 
ParticleGenerationEventDispatcherDB::dispatchParticleGenerationEvent( 
					        const ParticleState& particle )
{
  DispatcherMap::iterator it = 
    ParticleGenerationEventDispatcherDB::master_map.find( particle.getCell() );

  if( it != ParticleGenerationEventDispatcherDB::master_map.end() )
    it->second->dispatchParticleGenerationEvent( particle );
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_GENERATION_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleGenerationEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
