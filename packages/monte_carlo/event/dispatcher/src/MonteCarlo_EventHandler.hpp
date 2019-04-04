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
#include "MonteCarlo_ParticleHistorySimulationCompletionCriterion.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Geometry_AdvancedModel.hpp"
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

  //! Default constructor
  EventHandler();

  //! Constructor
  EventHandler( const MonteCarlo::SimulationGeneralProperties& properties );
  
  //! Constructor (model)
  EventHandler( const std::shared_ptr<const Geometry::Model>& model,
                const MonteCarlo::SimulationGeneralProperties& properties );

  //! Constructor (filled model)
  EventHandler( const std::shared_ptr<const MonteCarlo::FilledGeometryModel>& model,
                const MonteCarlo::SimulationGeneralProperties& properties );

  //! Destructor
  ~EventHandler()
  { /* ... */ }

  //! Set a custom simulation completion criterion
  void setSimulationCompletionCriterion( const std::shared_ptr<ParticleHistorySimulationCompletionCriterion>& criterion );

  //! Set a simulation completion criterion
  void setSimulationCompletionCriterion( const uint64_t number_of_histories );

  //! Set a simulation completion criterion
  void setSimulationCompletionCriterion( const double wall_time );

  //! Set a simulation completion criterion
  void setSimulationCompletionCriterion( const uint64_t number_of_histories,
                                         const double wall_time );

  //! Set a simulation completion criterion
  void setSimulationCompletionCriterion( const MonteCarlo::SimulationGeneralProperties& properties );

  //! Check if the simulation is complete
  bool isSimulationComplete() const;

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
  bool doesEstimatorExist( const Estimator::Id estimator_id ) const;

  //! Return the estimator
  Estimator& getEstimator( const Estimator::Id estimator_id );

  //! Return the estimator
  const Estimator& getEstimator( const Estimator::Id estimator_id ) const;

  //! Check if a particle tracker with the given id exists
  bool doesParticleTrackerExist( const ParticleTracker::Id particle_tracker_id ) const;

  //! Return the particle tracker
  ParticleTracker& getParticleTracker( const ParticleTracker::Id particle_tracker_id );

  //! Return the particle tracker
  const ParticleTracker& getParticleTracker( const ParticleTracker::Id particle_tracker_id ) const;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads );

  //! Update observers from particle simulation started event
  void updateObserversFromParticleSimulationStartedEvent();

  //! Update observers from particle simulation stopped event
  void updateObserversFromParticleSimulationStoppedEvent();

  //! Commit the history contributions to the observers
  void commitObserverHistoryContributions();

  //! Take a snapshot of the observer states
  void takeSnapshotOfObserverStates();

  //! Print the observer summaries
  void printObserverSummaries( std::ostream& os ) const;

  //! Log the observer summaries
  void logObserverSummaries() const;

  //! Reset observer data
  void resetObserverData();

  //! Reduce observer data on all processes in comm and collect on the root
  void reduceObserverData( const Utility::Communicator& comm,
                           const int root_process );

  //! Get the number of particle histories that have been committed
  uint64_t getNumberOfCommittedHistories() const;

  //! Get the number of particle histories committed since the last snapshot
  uint64_t getNumberOfCommittedHistoriesSinceLastSnapshot() const;

  //! Get the elapsed particle simulation time (s)
  double getElapsedTime() const;

  //! Get the elapsed time since the last snapshot
  double getElapsedTimeSinceLastSnapshot() const;

private:

  // Create a default simulation completion criterion
  static std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
  createDefaultCompletionCriterion( const MonteCarlo::SimulationGeneralProperties& properties );

  // Update the simulation completion criterion observer
  void updateSimulationCompletionCriterionObserver( const std::shared_ptr<ParticleHistorySimulationCompletionCriterion>& observer );

  // Reset the number of committed histories since the last snapshot
  void resetNumberOfCommittedHistoriesSinceLastSnapshot();

  // Reset the elapsed time since the last snapshot
  void resetElapsedTimeSinceLastSnapshot();

  // Struct for registering estimator
  template<typename EstimatorType>
  struct EstimatorRegistrationHelper
  {
    static void registerEstimator( EventHandler& event_handler,
                                   const std::shared_ptr<EstimatorType>& estimator );
  };

  // Struct for registering estimator
  template<typename T>
  struct EstimatorRegistrationHelper<MeshTrackLengthFluxEstimator<T> >
  {
    static void registerEstimator(
          EventHandler& event_handler,
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
    template<typename Observer, typename InputEntityId>
    static void registerObserverWithTag(
                                   EventHandler& event_handler,
                                   const std::shared_ptr<Observer>& observer,
			           const std::set<InputEntityId>& entity_ids );

    //! Register the obs. with dispatchers associated with BeginEventTag tag
    template<typename Observer, typename InputEntityId>
    static void registerObserverWithTag(
                                EventHandler& event_handler,
                                const std::shared_ptr<Observer>& observer,
                                const std::set<InputEntityId>& entity_ids,
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
                                const std::set<ParticleType>& particle_types );
  };

  // Struct for ending iteration through all event tags
  template<typename EndEventTagIterator>
  struct ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>
  {
    //! End registration iteration
    template<typename Observer, typename InputEntityId>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const std::set<InputEntityId>& entity_ids );

    //! End registration iteration
    template<typename Observer, typename InputEntityId>
    static void registerObserverWithTag(
                              EventHandler& event_handler,
			      const std::shared_ptr<Observer>& observer,
			      const std::set<InputEntityId>& entity_ids,
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
                                const std::set<ParticleType>& particle_types );
  };

  // Add the observer registration helper as a friend class
  template<typename T1, typename T2>
  friend class ObserverRegistrationHelper;

  // Register an observer with the appropriate dispatcher
  template<typename Observer, typename InputEntityId>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const std::set<InputEntityId>& entity_ids );

  // Register an observer with the appropriate dispatcher
  template<typename Observer, typename InputEntityId>
  void registerObserver( const std::shared_ptr<Observer>& observer,
                         const std::set<InputEntityId>& entity_ids,
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

  // Create and register cell estimator
  void createAndRegisterCellEstimator(
                                  const Estimator::Id estimator_id,
                                  const Geometry::EstimatorType estimator_type,
                                  const Geometry::ParticleType particle_type,
                                  const Geometry::Model::CellIdArray& cells,
                                  const Geometry::Model& model );

  // Create and register surface estimator
  void createAndRegisterSurfaceEstimator(
                   const Estimator::Id estimator_id,
                   const Geometry::EstimatorType estimator_type,
                   const Geometry::ParticleType particle_type,
                   const Geometry::AdvancedModel::SurfaceIdArray& surfaces,
                   const Geometry::Model& model );
                     
  // Set the particle type in a created estimator
  static void setParticleTypes( const Geometry::ParticleType particle_type,
                                const std::shared_ptr<Estimator>& estimator );

  // Verify that the estimator cell ids are valid
  void verifyValidEstimatorCellIds( const Estimator::Id estimator_id,
                                    const std::set<Estimator::EntityId>& cell_ids ) const;

  // Verify that the estimator surface ids are valid
  void verifyValidEstimatorSurfaceIds( const Estimator::Id estimator_id,
                                       const std::set<Estimator::EntityId>& surface_ids ) const;

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Typedef for the estimators container
  typedef std::unordered_map<Estimator::Id,std::shared_ptr<Estimator> > EstimatorIdMap;

  // Typedef for the particle tracker container
  typedef std::unordered_map<ParticleTracker::Id,std::shared_ptr<ParticleTracker> > ParticleTrackerIdMap;

  // Typedef for the particle history observer array
  typedef std::vector<std::shared_ptr<ParticleHistoryObserver> > ParticleHistoryObservers;

  // The geometry model
  std::shared_ptr<const Geometry::Model> d_model;

  // The simulation completion criterion
  std::shared_ptr<ParticleHistorySimulationCompletionCriterion> d_simulation_completion_criterion;

  // The number of simulated particle histories
  std::vector<uint64_t> d_number_of_committed_histories;

  // The number of simulation particle histories since the last snapshot
  std::vector<uint64_t> d_number_of_committed_histories_from_last_snapshot;

  // The simulation timer (s)
  std::shared_ptr<Utility::Timer> d_simulation_timer;

  // The snapshot timer
  std::shared_ptr<Utility::Timer> d_snapshot_timer;

  // The simulation time
  double d_elapsed_simulation_time;

  // The estimators
  EstimatorIdMap d_estimators;

  // The particle trackers
  ParticleTrackerIdMap d_particle_trackers;

  // The observers
  ParticleHistoryObservers d_particle_history_observers;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( EventHandler, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_EventHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler.hpp
//---------------------------------------------------------------------------//
