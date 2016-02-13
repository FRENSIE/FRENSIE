//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler_def.hpp
//! \author Alex Robinson
//! \brief  Event handler class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_HANDLER_DEF_HPP
#define FACEMC_ESTIMATOR_HANDLER_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ObserverRegistrationHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Add an entity observer to the handler
/*! \details The observer will be registered with the appropriate dispatchers.
 * It is important to pass a pointer to the class that maintains the event
 * tags associated with the observer (so that automatic dispatcher 
 * registration can occur).
 */
template<typename ObserverType, typename EntityHandle>
void EventHandler::addEntityEventObserver( 
                               const std::shared_ptr<ObserverType>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{
  // Make sure the observer is valid
  testPrecondition( observer.get() );
  // Make sure at least one entity id is specified
  testPrecondition( entity_ids.size() > 0 );
  
  // Register the observer with the particle event dispatchers
  REGISTER_OBSERVER_WITH_DISPATCHERS( observer, entity_ids );

  // Add the estimator to the master list
  d_particle_history_observers.push_back( observer );
}

// Add a global observer to the handler
/*! \details The estimator will be registered with the appropriate dispatchers.
 */
template<typename ObserverType>
void EventHandler::addGlobalEventObserver( 
                                const std::shared_ptr<ObserverType>& observer )
{
  // Make sure observer is valid
  testPrecondition( observer.get() );
 
  // Register the estimator with the particle global event dispatchers
  REGISTER_GLOBAL_OBSERVER_WITH_DISPATCHERS( observer );

  // Add the estimator to the master list
  d_particle_history_observers.push_back( observer );
}

} // end MonteCarlo namespace

#endif // end FACEMC_EVENT_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler_def.hpp
//---------------------------------------------------------------------------//
