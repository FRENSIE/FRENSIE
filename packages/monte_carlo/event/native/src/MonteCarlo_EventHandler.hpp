//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler.hpp
//! \author Alex Robinson
//! \brief  Event handler class declaration.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_HANDLER_HPP
#define MONTE_CARLO_EVENT_HANDLER_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventHandler.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventHandler.hpp"
#include "MonteCarlo_ParticleEnteringCellEventHandler.hpp"
#include "MonteCarlo_ParticleLeavingCellEventHandler.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventHandler.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventHandler.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

/*! The event handler class 
 * \details The event handler has been designed as a mix-in class so that
 * it is easier to add new events. In addition, the individual events are
 * better abstracted and easier to maintain when there is a handler for
 * each one.
 */
class EventHandler : public ParticleCollidingInCellEventHandler,
                     public ParticleCrossingSurfaceEventHandler,
                     public ParticleEnteringCellEventHandler,
                     public ParticleLeavingCellEventHandler,
                     public ParticleSubtrackEndingInCellEventHandler,
                     public ParticleSubtrackEndingGlobalEventHandler
{

public:

  //! Constructor
  EventHandler();
 
  //! Destructor
  ~EventHandler()
  { /* ... */ }
  
  //! Add an entity observer to the handler
  template<typename ObserverType, typename EntityHandle>
  void addEntityEventObserver( const std::shared_ptr<ObserverType>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids);

  //! Add a global observer to the handler
  template<typename ObserverType>
  void addGlobalEventObserver( const std::shared_ptr<ObserverType>& observer );

  //! Return the number of observers that have been added
  unsigned getNumberOfObservers() const;

  //! Check if an observer with the given id exists
  bool doesObserverExist( 
                     const ParticleHistoryObserver::idType observer_id ) const;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads );

  //! Commit the history contributions to the observers
  void commitObserverHistoryContributions();

  //! Print the observer summaries
  void printObserverSummaries( std::ostream& os,
                               const double num_histories,
                               const double start_time,
                               const double end_time ) const;

  //! Reset observer data
  void resetObserverData();

  //! Reduce observer data on all processes in comm and collect on the root
  void reduceObserverData( 
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the observer data and process
  void exportObserverData( 
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const unsigned long long last_history_number,
                    const unsigned long long histories_completed,
                    const double start_time,
                    const double end_time,
                    const bool process_data );
  
private:

  // Struct for iterating through all observer event tags
  template<typename BeginEventTagIterator, typename EndEventTagIterator>
  struct ObserverRegistrationHelper
  {
    //! Register the obs. with dispatchers associated with BeginEventTag tag
    template<typename Observer, typename EntityHandle>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids );

    /*! Register the global observer with the global dispatcher associated with
     * BeginEventTag tag
     */
    template<typename Observer>
    static void registerGlobalObserverWithTag( 
                                   EventHandler& event_handler,
                                   const std::shared_ptr<Observer>& observer );
  };

  // Struct for ending iteration through all event tags
  template<typename EndEventTagIterator>
  struct ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>
  {
    //! End registration iteration
    template<typename Observer, typename EntityHandle>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids );

    //! End global registration iteration
    template<typename Observer>
    static void registerGlobalObserverWithTag( 
                                    EventHandler& event_handler,
                                    const std::shared_ptr<Observer>& observer);
  };

  // Add the observer registration helper as a friend class
  template<typename T1, typename T2>
  friend class ObserverRegistrationHelper;

  // Register an observer with the appropriate dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const Teuchos::Array<EntityHandle>& entity_ids );

  // Register a global observer with the appropriate dispatcher
  template<typename Observer>
  void registerGlobalObserver( const std::shared_ptr<Observer>& observer );

  // Add the register observer with tag methods from the base classes
  // Unfortunately, base class methods with the same name will not be 
  // seen by the compiler unless there is a using declaration
  using ParticleCollidingInCellEventHandler::registerObserverWithTag;
  using ParticleCrossingSurfaceEventHandler::registerObserverWithTag;
  using ParticleEnteringCellEventHandler::registerObserverWithTag;
  using ParticleLeavingCellEventHandler::registerObserverWithTag;
  using ParticleSubtrackEndingInCellEventHandler::registerObserverWithTag;
  using ParticleSubtrackEndingGlobalEventHandler::registerGlobalObserverWithTag;

  // Typedef for the observers container
  typedef boost::unordered_map<ParticleHistoryObserver::idType,
                               std::shared_ptr<ParticleHistoryObserver> > 
  ParticleHistoryObservers;

  // The observers
  ParticleHistoryObservers d_particle_history_observers;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_EventHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler.hpp
//---------------------------------------------------------------------------//
