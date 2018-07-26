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

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventHandler.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventHandler.hpp"
#include "MonteCarlo_ParticleEnteringCellEventHandler.hpp"
#include "MonteCarlo_ParticleLeavingCellEventHandler.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventHandler.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventHandler.hpp"
#include "MonteCarlo_ParticleGoneGlobalEventHandler.hpp"
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"

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
                     public ParticleSubtrackEndingGlobalEventHandler,
                     public ParticleGoneGlobalEventHandler
{

public:

  //! Constructor
  EventHandler();

  //! Destructor
  ~EventHandler()
  { /* ... */ }

  //! Add an estimator to the handler
  template<typename EstimatorType>
  void addEstimator( const std::shared_ptr<EstimatorType>& estimator );

  //! Add a particle tracker to the handler
  void addParticleTracker( const std::shared_ptr<ParticleTracker>& particle_tracker );

  //! Return the number of estimators that have been added
  size_t getNumberOfEstimators() const;

  //! Return the number of particle trackers
  size_t getNumberOfParticleTrackers() const;

  //! Check if an estimator with the given id exists
  bool doesEstimatorExist( const uint32_t estimator_id ) const;

  //! Return the estimator
  Estimator& getEstimator( const uint32_t estimator_id );

  //! Return the estimator
  const Estimator& getEstimator( const uint32_t estimator_id ) const;

  //! Check if a particle tracker with the given id exists
  bool doesParticleTrackerExist( const uint32_t particle_tracker_id ) const;

  //! Return the particle tracker
  ParticleTracker& getParticleTracker( const uint32_t particle_tracker_id );

  //! Return the particle tracker
  const ParticleTracker& getParticleTracker( const uint32_t particle_tracker_id ) const;

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
  void reduceObserverData( const Utility::Communicator& comm,
                           const int root_process );

private:

  // Struct for registering estimator
  template<typename Estimator>
  struct EstimatorRegistrationHelper
  {
    static void registerEstimator( EventHandler& event_handler,
                                   const std::shared_ptr<EstimatorType>& estimator );
  };

  // Struct for registering estimator
  template<typename T>
  struct EstimatorRegistrationHelper<MeshTrackLengthFluxEstimator<T> >
  {
    static void registerEstimator( EventHandler& event_handler,
                                   const std::shared_ptr<MeshTrackLengthFluxEstimator<T> >& estimator );
  };

  // Add the estimator registration helper as a friend class
  template<typename T>
  friend class EstimatorRegistrationHelper;

  // Struct for iterating through all observer event tags
  template<typename BeginEventTagIterator, typename EndEventTagIterator>
  struct ObserverRegistrationHelper
  {
    //! Register the obs. with dispatchers associated with BeginEventTag tag
    template<typename Observer>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const std::set<uint64_t>& entity_ids );

    //! Register the obs. with dispatchers associated with BeginEventTag tag
    template<typename Observer>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const std::set<uint64_t>& entity_ids,
                              const std::set<ParticleType>& particle_types );

    /*! Register the global observer with the global dispatcher associated with
     * BeginEventTag tag
     */
    template<typename Observer>
    static void registerGlobalObserverWithTag(
                                   EventHandler& event_handler,
                                   const std::shared_ptr<Observer>& observer );

    /*! Register the global observer with the global dispatcher associated with
     * BeginEventTag tag
     */
    template<typename Observer>
    static void registerGlobalObserverWithTag(
                               EventHandler& event_handler,
                               const std::shared_ptr<Observer>& observer,
                               const std::set<ParticleTypes>& particle_types );
  };

  // Struct for ending iteration through all event tags
  template<typename EndEventTagIterator>
  struct ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>
  {
    //! End registration iteration
    template<typename Observer>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const std::vector<uint64_t>& entity_ids );

    //! End registration iteration
    template<typename Observer>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const std::set<uint64_t>& entity_ids,
                              const std::set<ParticleType>& particle_types );

    //! End global registration iteration
    template<typename Observer>
    static void registerGlobalObserverWithTag(
                                    EventHandler& event_handler,
                                    const std::shared_ptr<Observer>& observer);

    //! End global registration iteration
    template<typename Observer>
    static void registerGlobalObserverWithTag(
                               EventHandler& event_handler,
                               const std::shared_ptr<Observer>& observer,
                               const std::set<ParticleTypes>& particle_types );
  };

  // Add the observer registration helper as a friend class
  template<typename T1, typename T2>
  friend class ObserverRegistrationHelper;

  // Register an observer with the appropriate dispatcher
  template<typename Observer>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const std::set<uint64_t>& entity_ids );

  // Register an observer with the appropriate dispatcher
  template<typename Observer>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const std::set<uint64_t>& entity_ids,
                         const std::set<ParticleType>& particle_types );

  // Register a global observer with the appropriate dispatcher
  template<typename Observer>
  void registerGlobalObserver( const std::shared_ptr<Observer>& observer );

  // Register a global observer with the appropriate dispatcher
  template<typename Observer>
  void registerGlobalObserver( const std::shared_ptr<Observer>& observer,
                               const std::set<ParticleType>& particle_types );

  // Add the register observer with tag methods from the base classes
  // Unfortunately, base class methods with the same name will not be
  // seen by the compiler unless there is a using declaration
  using ParticleCollidingInCellEventHandler::registerObserverWithTag;
  using ParticleCrossingSurfaceEventHandler::registerObserverWithTag;
  using ParticleEnteringCellEventHandler::registerObserverWithTag;
  using ParticleLeavingCellEventHandler::registerObserverWithTag;
  using ParticleSubtrackEndingInCellEventHandler::registerObserverWithTag;
  using ParticleSubtrackEndingGlobalEventHandler::registerGlobalObserverWithTag;
  using ParticleGoneGlobalEventHandler::registerGlobalObserverWithTag;

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Typedef for the estimators container
  typedef std::unordered_map<uint32_t,std::shared<Estimator> > EstimatorIdMap;

  // Typedef for the particle tracker container
  typedef std::unordered_map<uint32_t,std::shared_ptr<ParticleTracker> > ParticleTrackerIdMap;

  // Typedef for the particle history observer array
  typedef std::set<std::shared_ptr<ParticleHistoryObserver> > ParticleHistoryObservers;

  // The estimators
  EstimatorIdMap d_estimators;

  // The particle trackers
  ParticleTrackerIdMap d_particle_trackers;

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
