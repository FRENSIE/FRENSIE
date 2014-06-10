//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SourceEventDispatcherDB.hpp
//! \author Alex Robinson
//! \brief  Source event dispatcher database declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SOURCE_EVENT_DISPATCHER_DB_HPP
#define FACEMC_SOURCE_EVENT_DISPATCHER_DB_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Teuchos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_SourceEventDispatcher.hpp"

namespace Facemc{

//! The source event dispatcher class 
class SourceEventDispatcherDB
{

public:
  
  //! Get the appropriate dispatcher for the given cell id
  static Teuchos::RCP<SourceEventDispatcher>& getDispatcher(
		    const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver( 
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const Estimator::idType estimator_id,
		      const Teuchos::RCP<SourceEventObserver>& observer );

  //! Attach an observer to the appropriate dispatcher
  static void attachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const Estimator::idType estimator_id,
		      const SourceEventObserver* observer );

  //! Detach an observer from the appropriate dispatcher
  static void detachObserver(
		      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const Estimator::idType estimator_id );

  //! Detach the observer from all dispatchers
  static void detachObserver( const Estimator::idType estimator_id );

  //! Dispatch the source event to the observers
  static void dispatchSourceEvent( const ParticleState& particle );

private:

  // Constructor
  SourceEventDispatcherDB();

  // Typedef for the dispatcher map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       Teuchos::RCP<SourceEventDispatcher> >
  DispatcherMap;

  static DispatcherMap master_map;
};

// Attach an observer
/*! \details A non-owning Teuchos::RCP will be constructed from the raw 
 * pointer. This function should be used from inside of observer constructors.
 * The observer destructor should call the detachObserver method
 */
inline void SourceEventDispatcherDB::attachObserver(
                      const Geometry::ModuleTraits::InternalCellHandle cell_id,
		      const Estimator::idType estimator_id,
		      const SourceEventObserver* observer )
{
  SourceEventDispatcherDB::attachObserver( cell_id,
					   estimator_id,
					   Teuchos::rcp( observer, false ) );
}

// Dispatch the source event to the observers
inline void SourceEventDispatcherDB::dispatchSourceEvent( 
					        const ParticleState& particle )
{
  DispatcherMap::iterator it = 
    SourceEventDispatcherDB::master_map.find( particle.getCell() );

  if( it != SourceEventDispatcherDB::master_map.end() )
    it->second->dispatchSourceEvent( particle );
}

} // end Facemc namespace

#endif // end FACEMC_SOURCE_EVENT_DISPATCHER_DB_HPP

//---------------------------------------------------------------------------//
// end Facemc_SourceEventDispatcherDB.hpp
//---------------------------------------------------------------------------//
