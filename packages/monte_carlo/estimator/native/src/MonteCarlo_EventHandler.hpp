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
#include "MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleLeavingCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The estimator handler class 
class EventHandler{

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
  void exportObserverData( const std::string& data_file_name,
                           const unsigned long long last_history_number,
                           const unsigned long long histories_completed,
                           const double start_time,
                           const double end_time,
                           const bool process_data );

  //! Update the observers from a particle generation event
  void updateObserversFromParticleGenerationEvent(
                                               const ParticleState& particle );

  //! Update the observers from a particle entering cell event
  void updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering );

  //! Update the observers from a particle leaving cell event
  void updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::ModuleTraits::InternalCellHandle cell_leaving );

  //! Update the observers from a particle subtrack ending in cell event
  void updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time );

  //! Update the observers from a particle colliding in cell event
  void updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section );

  //! Update the observers from a surface intersection event
  void updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] );

  //! Update the global estimators from a subtrack ending event
  void updateObserversFromParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );
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
  template<typename BeginEventTagIterator, typename EndEventTagIterator>
  friend ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>;

  // Register an observer with the appropriate dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const Teuchos::Array<EntityHandle>& entity_ids );

  // Register a global observer with the appropriate dispatcher
  template<typename Observer>
  void registerGlobalObserver( const std::shared_ptr<Observer>& observer );
  
  // Register an observer with the appropriate particle colliding in cell event
  // dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const Teuchos::Array<EntityHandle>& entity_ids,
                         ParticleCollidingInCellEventObserver::EventTag );

  // Register an observer with the appropriate particle crossing surface event
  // dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const Teuchos::Array<EntityHandle>& entity_ids,
                         ParticleCrossingSurfaceEventObserver::EventTag );

  // Register an observer with the appropriate particle entering cell event
  // dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const Teuchos::Array<EntityHandle>& entity_ids,
                         ParticleEnteringCellEventObserver::EventTag );

  // Register an observer with the appropriate particle leaving cell event
  // dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const Teuchos::Array<EntityHandle>& entity_ids,
                         ParticleLeavingCellEventObserver::EventTag );

  // Register an observer with the appropriate particle subtrack ending in cell
  // event dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserver( const std::shared_ptr<Observer>& observer,
			 const Teuchos::Array<EntityHandle>& entity_ids,
			 ParticleSubtrackEndingInCellEventObserver::EventTag );

  // Register a global observer with the appropraite particle subtrack ending
  // global event dispatcher
  template<typename Observer>
  void registerGlobalObserver( 
			 const std::shared_ptr<Observer>& observer,
			 ParticleSubtrackEndingGlobalEventObserver::EventTag );

  // Typedef for the observers container
  typedef boost::unordered_map<ParticleHistoryObserver::idType,
                               std::shared_ptr<ParticleHistoryObserver> > 
  ParticleHistoryObservers;

  // The observers
  ParticleHistoryObservers d_particle_history_observers;

  // The particle entering cell event dispatcher
  ParticleEnteringCellEventDispatcher 
  d_particle_entering_cell_event_dispatcher;

  // The particle leaving cell event dispatcher
  ParticleLeavingCellEventDispatcher
  d_particle_leaving_cell_event_dispatcher;

  // The particle subtrack ending in cell event dispatcher
  ParticleSubtrackEndingInCellEventDispatcher
  d_particle_subtrack_ending_in_cell_event_dispatcher;

  // The particle colliding in cell event dispatcher
  ParticleCollidingInCellEventDispatcher
  d_particle_colliding_in_cell_event_dispatcher;

  // The particle crossing surface event dispatcher
  ParticleCrossingSurfaceEventDispatcher
  d_particle_crossing_surface_event_dispatcher;

  // The particle subtrack ending global event dispatcher
  ParticleSubtrackEndingGlobalEventDispatcher
  d_particle_subtrack_ending_global_event_dispatcher;
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
